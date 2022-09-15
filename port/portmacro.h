#ifndef PORTMACRO_H
#define PORTMACRO_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * Implementation of functions defined in portable.h for the ARM CM3 port.
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
#define portCHAR		char
#define portFLOAT		float
#define portDOUBLE		double
#define portLONG		long
#define portSHORT		short
#define portSTACK_TYPE	uint32_t
#define portBASE_TYPE	long

typedef portSTACK_TYPE StackType_t;
typedef long BaseType_t;
typedef unsigned long UBaseType_t;

#if( configUSE_16_BIT_TICKS == 1 )
	typedef uint16_t TickType_t;
	#define portMAX_DELAY ( TickType_t ) 0xffff				////16位最大的整型数
#else
	typedef uint32_t TickType_t;
	#define portMAX_DELAY ( TickType_t ) 0xffffffffUL		////32位最大的整型数

	/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
	not need to be guarded with a critical section. */
	#define portTICK_TYPE_IS_ATOMIC 1
#endif
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#define portSTACK_GROWTH			( -1 )											////在“任务通知的数据结构”章节的typedef struct tskTaskControlBlock才提到
#define portTICK_PERIOD_MS			( ( TickType_t ) 1000 / configTICK_RATE_HZ )	////用于辅助计算真实的时间(阻塞等待)，单位为ms，在xQueueSend()函数中使用到
#define portBYTE_ALIGNMENT			8												////配置栈空间为按 8 字节对齐

/* Constants used with memory barrier intrinsics. */
#define portSY_FULL_READ_WRITE		( 15 )			////在portYIELD()函数中的__dsb和__isb调用中使用到

/*-----------------------------------------------------------*/

/* Scheduler utilities. */	
////portYIELD 的实现很简单，实际就是将 PendSV 的悬起位置 1，当没有其它中断运行的时候
////响应 PendSV 中断，去执行我们写好的 PendSV中断服务函数，在里面实现任务切换。

#define portYIELD()																\
{																				\
	/* Set a PendSV to request a context switch. */								\
	portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;								\
																				\
	/* Barriers are normally not required but do ensure the code is completely	\
	within the specified behaviour for the architecture. */						\
	__dsb( portSY_FULL_READ_WRITE );											\
	__isb( portSY_FULL_READ_WRITE );											\
}
/*-----------------------------------------------------------*/

#define portNVIC_INT_CTRL_REG		( * ( ( volatile uint32_t * ) 0xe000ed04 ) )	////控制寄存器Interrupt control and state register(SCB_ICSR)
#define portNVIC_PENDSVSET_BIT		( 1UL << 28UL )									////SCB_ICSR: bit28 -- 触发任务切换的寄存器的bit位 (PENDSVSET: PendSV set-pending bit)
#define portEND_SWITCHING_ISR( xSwitchRequired ) if( xSwitchRequired != pdFALSE ) portYIELD()	////用于根据某些(如xTaskResumeFromISR())函数的返回来判断是否需要执行上下文切换
#define portYIELD_FROM_ISR( x ) portEND_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
extern void vPortEnterCritical( void );
extern void vPortExitCritical( void );

#define portDISABLE_INTERRUPTS()				vPortRaiseBASEPRI()			////不带返回值的关中断函数，不能嵌套，不能在中断里面使用
#define portENABLE_INTERRUPTS()					vPortSetBASEPRI( 0 )		////不带中断保护的开中断函数
#define portENTER_CRITICAL()					vPortEnterCritical()		////进入临界段，不带中断保护版本，不能嵌套
#define portEXIT_CRITICAL()						vPortExitCritical()			////退出临界段，不带中断保护版本，不能嵌套
#define portSET_INTERRUPT_MASK_FROM_ISR()		ulPortRaiseBASEPRI()		////带返回值的关中断函数，可以嵌套，可以在中断里面使用
#define portCLEAR_INTERRUPT_MASK_FROM_ISR(x)	vPortSetBASEPRI(x)			////带中断保护的开中断函数

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#ifndef portSUPPRESS_TICKS_AND_SLEEP										////野火中没用到，与低功耗有关
	extern void vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime );
	#define portSUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime ) vPortSuppressTicksAndSleep( xExpectedIdleTime )
#endif
/*-----------------------------------------------------------*/

/* Port specific optimisations. */
#ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION					////置1：使用前置零法管理任务优先级；置0则为选择通用方法
	#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1
#endif

#if configUSE_PORT_OPTIMISED_TASK_SELECTION == 1				////这里使用前置零优化法

	/* Check the configuration. */
	#if( configMAX_PRIORITIES > 32 )							////可使用的最大优先级，在FreeRTOSConfig.h中配置为5
		#error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice.
	#endif

	/* Store/clear the ready priorities in a bit map. */
	#define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )	////标志优先级位
	#define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )	////清除优先级位

	/*-----------------------------------------------------------*/

	#define portGET_HIGHEST_PRIORITY( uxTopPriority, uxReadyPriorities ) uxTopPriority = ( 31UL - ( uint32_t ) __clz( ( uxReadyPriorities ) ) )

#endif /* taskRECORD_READY_PRIORITY */
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
not necessary for to use this port.  They are defined so the common demo files
(which build with all the ports) will build. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) void vFunction( void *pvParameters ) ////
#define portTASK_FUNCTION( vFunction, pvParameters ) void vFunction( void *pvParameters )		////task.c中L1791动态创建idle任务时用到
/*-----------------------------------------------------------*/

#ifdef configASSERT
	void vPortValidateInterruptPriority( void );
	#define portASSERT_IF_INTERRUPT_PRIORITY_INVALID() 	vPortValidateInterruptPriority()
#endif

/* portNOP() is not required by this port. */
#define portNOP()

#define portINLINE __inline

#ifndef portFORCE_INLINE
	#define portFORCE_INLINE __forceinline
#endif

/*-----------------------------------------------------------*/

static portFORCE_INLINE void vPortSetBASEPRI( uint32_t ulBASEPRI )
{
	__asm
	{
		/* Barrier instructions are not used as this function is only used to
		lower the BASEPRI value. */
		msr basepri, ulBASEPRI
	}
}
/*-----------------------------------------------------------*/

static portFORCE_INLINE void vPortRaiseBASEPRI( void )
{
uint32_t ulNewBASEPRI = configMAX_SYSCALL_INTERRUPT_PRIORITY;

	__asm
	{
		/* Set BASEPRI to the max syscall priority to effect a critical
		section. */
		msr basepri, ulNewBASEPRI
		dsb
		isb
	}
}
/*-----------------------------------------------------------*/

static portFORCE_INLINE void vPortClearBASEPRIFromISR( void )
{
	__asm
	{
		/* Set BASEPRI to 0 so no interrupts are masked.  This function is only
		used to lower the mask in an interrupt, so memory barriers are not 
		used. */
		msr basepri, #0
	}
}
/*-----------------------------------------------------------*/

static portFORCE_INLINE uint32_t ulPortRaiseBASEPRI( void )			////带返回值的关中断函数，可以嵌套，可以在中断里面使用
{
uint32_t ulReturn, ulNewBASEPRI = configMAX_SYSCALL_INTERRUPT_PRIORITY;

	__asm
	{
		/* Set BASEPRI to the max syscall priority to effect a critical
		section. */
		mrs ulReturn, basepri
		msr basepri, ulNewBASEPRI
		dsb
		isb
	}

	return ulReturn;
}
/*-----------------------------------------------------------*/

static portFORCE_INLINE BaseType_t xPortIsInsideInterrupt( void )
{
uint32_t ulCurrentInterrupt;
BaseType_t xReturn;

	/* Obtain the number of the currently executing interrupt. */
	__asm
	{
		mrs ulCurrentInterrupt, ipsr
	}

	if( ulCurrentInterrupt == 0 )
	{
		xReturn = pdFALSE;
	}
	else
	{
		xReturn = pdTRUE;
	}

	return xReturn;
}


#ifdef __cplusplus
}
#endif

#endif /* PORTMACRO_H */

