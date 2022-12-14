#ifndef INC_FREERTOS_H
#define INC_FREERTOS_H

/*
 * Include the generic headers required for the FreeRTOS port being used.
 */
#include <stddef.h>

/*
 * If stdint.h cannot be located then:
 *   + If using GCC ensure the -nostdint options is *not* being used.
 *   + Ensure the project's include path includes the directory in which your
 *     compiler stores stdint.h.
 *   + Set any compiler options necessary for it to support C99, as technically
 *     stdint.h is only mandatory with C99 (FreeRTOS does not require C99 in any
 *     other way).
 *   + The FreeRTOS download includes a simple stdint.h definition that can be
 *     used in cases where none is provided by the compiler.  The files only
 *     contains the typedefs required to build FreeRTOS.  Read the instructions
 *     in FreeRTOS/source/stdint.readme for more information.
 */
#include <stdint.h> /* READ COMMENT ABOVE. */

#ifdef __cplusplus
extern "C" {
#endif

/* Application specific configuration options. */
#include "FreeRTOSConfig.h"

/* Basic FreeRTOS definitions. */
#include "projdefs.h"

/* Definitions specific to the port being used. */
#include "portable.h"

/* Must be defaulted before configUSE_NEWLIB_REENTRANT is used below. */
#ifndef configUSE_NEWLIB_REENTRANT		////不需要理会，这个宏定义没打开
	#define configUSE_NEWLIB_REENTRANT 0
#endif

/* Required if struct _reent is used. */
#if ( configUSE_NEWLIB_REENTRANT == 1 )
	#include <reent.h>
#endif
/*
 * Check all the required application specific macros have been defined.
 * These macros are application specific and (as downloaded) are defined
 * within FreeRTOSConfig.h.
 */

#ifndef configMINIMAL_STACK_SIZE		////空闲任务使用的堆栈大小
	#error Missing definition:  configMINIMAL_STACK_SIZE must be defined in FreeRTOSConfig.h.  configMINIMAL_STACK_SIZE defines the size (in words) of the stack allocated to the idle task.  Refer to the demo project provided for your port for a suitable value.
#endif

#ifndef configMAX_PRIORITIES		////可使用的最大优先级
	#error Missing definition:  configMAX_PRIORITIES must be defined in FreeRTOSConfig.h.  See the Configuration section of the FreeRTOS API documentation for details.
#endif

#ifndef configUSE_PREEMPTION		////置 1：RTOS 使用抢占式调度器；置 0：RTOS 使用协作式调度器（时间片）
	#error Missing definition:  configUSE_PREEMPTION must be defined in FreeRTOSConfig.h as either 1 or 0.  See the Configuration section of the FreeRTOS API documentation for details.
#endif

#ifndef configUSE_IDLE_HOOK			////置 1：使用空闲钩子（Idle Hook 类似于回调函数）；置 0：忽略空闲钩子
	#error Missing definition:  configUSE_IDLE_HOOK must be defined in FreeRTOSConfig.h as either 1 or 0.  See the Configuration section of the FreeRTOS API documentation for details.
#endif

#ifndef configUSE_TICK_HOOK			////置 1：使用时间片钩子（Tick Hook）；置 0：忽略时间片钩子
	#error Missing definition:  configUSE_TICK_HOOK must be defined in FreeRTOSConfig.h as either 1 or 0.  See the Configuration section of the FreeRTOS API documentation for details.
#endif

#ifndef configUSE_16_BIT_TICKS		////系统节拍计数器变量数据类型，1 表示为 16 位无符号整形，0 表示为 32 位无符号整形
	#error Missing definition:  configUSE_16_BIT_TICKS must be defined in FreeRTOSConfig.h as either 1 or 0.  See the Configuration section of the FreeRTOS API documentation for details.
#endif

#ifndef configMAX_PRIORITIES		////可使用的最大优先级
	#error configMAX_PRIORITIES must be defined to be greater than or equal to 1.
#endif

#ifndef configUSE_CO_ROUTINES		////启用协程，启用协程以后必须添加文件 croutine.c
	#define configUSE_CO_ROUTINES 0
#endif

#ifndef INCLUDE_vTaskPrioritySet	////INCLUDE打头的是“FreeRTOS可选函数配置选项”
	#define INCLUDE_vTaskPrioritySet 0
#endif

#ifndef INCLUDE_uxTaskPriorityGet
	#define INCLUDE_uxTaskPriorityGet 0
#endif

#ifndef INCLUDE_vTaskDelete
	#define INCLUDE_vTaskDelete 0
#endif

#ifndef INCLUDE_vTaskSuspend
	#define INCLUDE_vTaskSuspend 0
#endif

#ifndef INCLUDE_vTaskDelayUntil
	#define INCLUDE_vTaskDelayUntil 0
#endif

#ifndef INCLUDE_vTaskDelay
	#define INCLUDE_vTaskDelay 0
#endif

#ifndef INCLUDE_xTaskGetIdleTaskHandle			////设置为 0，则防止编译器警告，这意味着在其他任何地方都不使用 xIdleTaskHandle。暂时不用理会
	#define INCLUDE_xTaskGetIdleTaskHandle 0
#endif

#ifndef INCLUDE_xTaskAbortDelay					////在“任务通知的数据结构”章节的typedef struct tskTaskControlBlock才提到
	#define INCLUDE_xTaskAbortDelay 0
#endif

#ifndef INCLUDE_xQueueGetMutexHolder			////野火中没用到
	#define INCLUDE_xQueueGetMutexHolder 0
#endif

#ifndef INCLUDE_xSemaphoreGetMutexHolder		////野火中没用到
	#define INCLUDE_xSemaphoreGetMutexHolder INCLUDE_xQueueGetMutexHolder
#endif

#ifndef INCLUDE_xTaskGetHandle					////野火中没用到
	#define INCLUDE_xTaskGetHandle 0
#endif

#ifndef INCLUDE_uxTaskGetStackHighWaterMark		////野火中没用到
	#define INCLUDE_uxTaskGetStackHighWaterMark 0
#endif

#ifndef INCLUDE_eTaskGetState					////野火FreeRTOSConfig.h中置1
	#define INCLUDE_eTaskGetState 0
#endif

#ifndef INCLUDE_xTaskResumeFromISR				////置1时，xTaskResumeFromISR()才能用
	#define INCLUDE_xTaskResumeFromISR 1
#endif

#ifndef INCLUDE_xTimerPendFunctionCall			////野火FreeRTOSConfig.h中置1
	#define INCLUDE_xTimerPendFunctionCall 0
#endif

#ifndef INCLUDE_xTaskGetSchedulerState			////野火FreeRTOSConfig.h中置1
	#define INCLUDE_xTaskGetSchedulerState 0
#endif

#ifndef INCLUDE_xTaskGetCurrentTaskHandle		////启用一个可选函数（该函数被 Trace 源码使用，默认该值为 0 表示不用）
	#define INCLUDE_xTaskGetCurrentTaskHandle 0
#endif

#if configUSE_CO_ROUTINES != 0					////启用协程，启用协程以后必须添加文件 croutine.c
	#ifndef configMAX_CO_ROUTINE_PRIORITIES
		#error configMAX_CO_ROUTINE_PRIORITIES must be greater than or equal to 1.
	#endif
#endif

#ifndef configUSE_DAEMON_TASK_STARTUP_HOOK		////野火中没用到
	#define configUSE_DAEMON_TASK_STARTUP_HOOK 0
#endif

#ifndef configUSE_APPLICATION_TASK_TAG			////应用任务标签
	#define configUSE_APPLICATION_TASK_TAG 0
#endif

#ifndef configNUM_THREAD_LOCAL_STORAGE_POINTERS	////在“任务通知的数据结构”章节的typedef struct tskTaskControlBlock才提到
	#define configNUM_THREAD_LOCAL_STORAGE_POINTERS 0
#endif

#ifndef configUSE_RECURSIVE_MUTEXES				////使用递归互斥信号量，野火中置1
	#define configUSE_RECURSIVE_MUTEXES 0
#endif

#ifndef configUSE_MUTEXES						////使用互斥信号量，野火中置1
	#define configUSE_MUTEXES 1
#endif

#ifndef configUSE_TIMERS						////启用软件计时器，野火中置1
	#define configUSE_TIMERS 1
#endif

#ifndef configUSE_COUNTING_SEMAPHORES			////为1时使用计数信号量，野火中置1
	#define configUSE_COUNTING_SEMAPHORES 0
#endif

#ifndef configUSE_ALTERNATIVE_API				////野火中没用到
	#define configUSE_ALTERNATIVE_API 0
#endif

#ifndef portCRITICAL_NESTING_IN_TCB				////在“任务通知的数据结构”章节的typedef struct tskTaskControlBlock才提到
	#define portCRITICAL_NESTING_IN_TCB 0
#endif

#ifndef configMAX_TASK_NAME_LEN					
	#define configMAX_TASK_NAME_LEN 16
#endif

#ifndef configIDLE_SHOULD_YIELD
	#define configIDLE_SHOULD_YIELD		1
#endif

#if configMAX_TASK_NAME_LEN < 1
	#error configMAX_TASK_NAME_LEN must be set to a minimum of 1 in FreeRTOSConfig.h
#endif

#ifndef configASSERT							////断言
	#define configASSERT( x )					////野火中如此定义： if((x)==0) vAssertCalled(__FILE__,__LINE__)
	#define configASSERT_DEFINED 0
#else
	#define configASSERT_DEFINED 1
#endif

/* The timers module relies on xTaskGetSchedulerState(). */
#if configUSE_TIMERS == 1						////启用了软件定时器，才生效

	////软件计时器优先级
	#ifndef configTIMER_TASK_PRIORITY
		#error If configUSE_TIMERS is set to 1 then configTIMER_TASK_PRIORITY must also be defined.
	#endif /* configTIMER_TASK_PRIORITY */

	#ifndef configTIMER_QUEUE_LENGTH
		#error If configUSE_TIMERS is set to 1 then configTIMER_QUEUE_LENGTH must also be defined.
	#endif /* configTIMER_QUEUE_LENGTH */

	#ifndef configTIMER_TASK_STACK_DEPTH
		#error If configUSE_TIMERS is set to 1 then configTIMER_TASK_STACK_DEPTH must also be defined.
	#endif /* configTIMER_TASK_STACK_DEPTH */

#endif /* configUSE_TIMERS */

#ifndef portSET_INTERRUPT_MASK_FROM_ISR			////在portmacro.h中已定义 -- 带返回值的关中断函数，可以嵌套，可以在中断里面使用
	#define portSET_INTERRUPT_MASK_FROM_ISR() 0
#endif

#ifndef portCLEAR_INTERRUPT_MASK_FROM_ISR		////在portmacro.h中已定义 -- 设置basepri值
	#define portCLEAR_INTERRUPT_MASK_FROM_ISR( uxSavedStatusValue ) ( void ) uxSavedStatusValue
#endif

#ifndef portCLEAN_UP_TCB						////野火中没用到
	#define portCLEAN_UP_TCB( pxTCB ) ( void ) pxTCB
#endif

#ifndef portPRE_TASK_DELETE_HOOK				////任务删除钩子函数，任务删除函数 vTaskDelete()中用到
	#define portPRE_TASK_DELETE_HOOK( pvTaskToDelete, pxYieldPending )
#endif

#ifndef portSETUP_TCB							////野火中没用到
	#define portSETUP_TCB( pxTCB ) ( void ) pxTCB
#endif

#ifndef configQUEUE_REGISTRY_SIZE				////设置可以注册的信号量和消息队列个数，野火FreeRTOSConfig.h中置为10
	#define configQUEUE_REGISTRY_SIZE 0U
#endif

#if ( configQUEUE_REGISTRY_SIZE < 1 )
	#define vQueueAddToRegistry( xQueue, pcName )
	#define vQueueUnregisterQueue( xQueue )
	#define pcQueueGetName( xQueue )
#endif

#ifndef portPOINTER_SIZE_TYPE					////指针的类型 -- "栈空间地址对齐实现"中有用到
	#define portPOINTER_SIZE_TYPE uint32_t
#endif

/* Remove any unused trace macros. */			////trace打头的都跟"可视化跟踪调试"有关系
#ifndef traceSTART
	/* Used to perform any necessary initialisation - for example, open a file
	into which trace is to be written. */
	#define traceSTART()
#endif

#ifndef traceEND
	/* Use to close a trace, for example close a file into which trace has been
	written. */
	#define traceEND()
#endif

#ifndef traceTASK_SWITCHED_IN
	/* Called after a task has been selected to run.  pxCurrentTCB holds a pointer
	to the task control block of the selected task. */
	#define traceTASK_SWITCHED_IN()
#endif

#ifndef traceINCREASE_TICK_COUNT
	/* Called before stepping the tick count after waking from tickless idle
	sleep. */
	#define traceINCREASE_TICK_COUNT( x )
#endif

#ifndef traceLOW_POWER_IDLE_BEGIN
	/* Called immediately before entering tickless idle. */
	#define traceLOW_POWER_IDLE_BEGIN()
#endif

#ifndef	traceLOW_POWER_IDLE_END
	/* Called when returning to the Idle task after a tickless idle. */
	#define traceLOW_POWER_IDLE_END()
#endif

#ifndef traceTASK_SWITCHED_OUT
	/* Called before a task has been selected to run.  pxCurrentTCB holds a pointer
	to the task control block of the task being switched out. */
	#define traceTASK_SWITCHED_OUT()
#endif

#ifndef traceTASK_PRIORITY_INHERIT
	/* Called when a task attempts to take a mutex that is already held by a
	lower priority task.  pxTCBOfMutexHolder is a pointer to the TCB of the task
	that holds the mutex.  uxInheritedPriority is the priority the mutex holder
	will inherit (the priority of the task that is attempting to obtain the
	muted. */
	#define traceTASK_PRIORITY_INHERIT( pxTCBOfMutexHolder, uxInheritedPriority )
#endif

#ifndef traceTASK_PRIORITY_DISINHERIT
	/* Called when a task releases a mutex, the holding of which had resulted in
	the task inheriting the priority of a higher priority task.
	pxTCBOfMutexHolder is a pointer to the TCB of the task that is releasing the
	mutex.  uxOriginalPriority is the task's configured (base) priority. */
	#define traceTASK_PRIORITY_DISINHERIT( pxTCBOfMutexHolder, uxOriginalPriority )
#endif

#ifndef traceBLOCKING_ON_QUEUE_RECEIVE
	/* Task is about to block because it cannot read from a
	queue/mutex/semaphore.  pxQueue is a pointer to the queue/mutex/semaphore
	upon which the read was attempted.  pxCurrentTCB points to the TCB of the
	task that attempted the read. */
	#define traceBLOCKING_ON_QUEUE_RECEIVE( pxQueue )
#endif

#ifndef traceBLOCKING_ON_QUEUE_SEND
	/* Task is about to block because it cannot write to a
	queue/mutex/semaphore.  pxQueue is a pointer to the queue/mutex/semaphore
	upon which the write was attempted.  pxCurrentTCB points to the TCB of the
	task that attempted the write. */
	#define traceBLOCKING_ON_QUEUE_SEND( pxQueue )
#endif

#ifndef configCHECK_FOR_STACK_OVERFLOW
	#define configCHECK_FOR_STACK_OVERFLOW 0
#endif

/* The following event macros are embedded in the kernel API calls. */

#ifndef traceMOVED_TASK_TO_READY_STATE
	#define traceMOVED_TASK_TO_READY_STATE( pxTCB )
#endif

#ifndef tracePOST_MOVED_TASK_TO_READY_STATE
	#define tracePOST_MOVED_TASK_TO_READY_STATE( pxTCB )
#endif

#ifndef traceQUEUE_CREATE
	#define traceQUEUE_CREATE( pxNewQueue )
#endif

#ifndef traceQUEUE_CREATE_FAILED
	#define traceQUEUE_CREATE_FAILED( ucQueueType )
#endif

#ifndef traceCREATE_MUTEX
	#define traceCREATE_MUTEX( pxNewQueue )
#endif

#ifndef traceCREATE_MUTEX_FAILED
	#define traceCREATE_MUTEX_FAILED()
#endif

#ifndef traceGIVE_MUTEX_RECURSIVE
	#define traceGIVE_MUTEX_RECURSIVE( pxMutex )
#endif

#ifndef traceGIVE_MUTEX_RECURSIVE_FAILED
	#define traceGIVE_MUTEX_RECURSIVE_FAILED( pxMutex )
#endif

#ifndef traceTAKE_MUTEX_RECURSIVE
	#define traceTAKE_MUTEX_RECURSIVE( pxMutex )
#endif

#ifndef traceTAKE_MUTEX_RECURSIVE_FAILED
	#define traceTAKE_MUTEX_RECURSIVE_FAILED( pxMutex )
#endif

#ifndef traceCREATE_COUNTING_SEMAPHORE
	#define traceCREATE_COUNTING_SEMAPHORE()
#endif

#ifndef traceCREATE_COUNTING_SEMAPHORE_FAILED
	#define traceCREATE_COUNTING_SEMAPHORE_FAILED()
#endif

#ifndef traceQUEUE_SEND
	#define traceQUEUE_SEND( pxQueue )
#endif

#ifndef traceQUEUE_SEND_FAILED
	#define traceQUEUE_SEND_FAILED( pxQueue )
#endif

#ifndef traceQUEUE_RECEIVE
	#define traceQUEUE_RECEIVE( pxQueue )
#endif

#ifndef traceQUEUE_PEEK
	#define traceQUEUE_PEEK( pxQueue )
#endif

#ifndef traceQUEUE_PEEK_FROM_ISR
	#define traceQUEUE_PEEK_FROM_ISR( pxQueue )
#endif

#ifndef traceQUEUE_RECEIVE_FAILED
	#define traceQUEUE_RECEIVE_FAILED( pxQueue )
#endif

#ifndef traceQUEUE_SEND_FROM_ISR
	#define traceQUEUE_SEND_FROM_ISR( pxQueue )
#endif

#ifndef traceQUEUE_SEND_FROM_ISR_FAILED
	#define traceQUEUE_SEND_FROM_ISR_FAILED( pxQueue )
#endif

#ifndef traceQUEUE_RECEIVE_FROM_ISR
	#define traceQUEUE_RECEIVE_FROM_ISR( pxQueue )
#endif

#ifndef traceQUEUE_RECEIVE_FROM_ISR_FAILED
	#define traceQUEUE_RECEIVE_FROM_ISR_FAILED( pxQueue )
#endif

#ifndef traceQUEUE_PEEK_FROM_ISR_FAILED
	#define traceQUEUE_PEEK_FROM_ISR_FAILED( pxQueue )
#endif

#ifndef traceQUEUE_DELETE
	#define traceQUEUE_DELETE( pxQueue )
#endif

#ifndef traceTASK_CREATE
	#define traceTASK_CREATE( pxNewTCB )
#endif

#ifndef traceTASK_CREATE_FAILED
	#define traceTASK_CREATE_FAILED()
#endif

#ifndef traceTASK_DELETE
	#define traceTASK_DELETE( pxTaskToDelete )
#endif

#ifndef traceTASK_DELAY_UNTIL
	#define traceTASK_DELAY_UNTIL( x )
#endif

#ifndef traceTASK_DELAY
	#define traceTASK_DELAY()
#endif

#ifndef traceTASK_PRIORITY_SET
	#define traceTASK_PRIORITY_SET( pxTask, uxNewPriority )
#endif

#ifndef traceTASK_SUSPEND
	#define traceTASK_SUSPEND( pxTaskToSuspend )
#endif

#ifndef traceTASK_RESUME
	#define traceTASK_RESUME( pxTaskToResume )
#endif

#ifndef traceTASK_RESUME_FROM_ISR
	#define traceTASK_RESUME_FROM_ISR( pxTaskToResume )
#endif

#ifndef traceTASK_INCREMENT_TICK
	#define traceTASK_INCREMENT_TICK( xTickCount )
#endif

#ifndef traceTIMER_CREATE
	#define traceTIMER_CREATE( pxNewTimer )
#endif

#ifndef traceTIMER_CREATE_FAILED
	#define traceTIMER_CREATE_FAILED()
#endif

#ifndef traceTIMER_COMMAND_SEND
	#define traceTIMER_COMMAND_SEND( xTimer, xMessageID, xMessageValueValue, xReturn )
#endif

#ifndef traceTIMER_EXPIRED
	#define traceTIMER_EXPIRED( pxTimer )
#endif

#ifndef traceTIMER_COMMAND_RECEIVED
	#define traceTIMER_COMMAND_RECEIVED( pxTimer, xMessageID, xMessageValue )
#endif

#ifndef traceMALLOC
    #define traceMALLOC( pvAddress, uiSize )
#endif

#ifndef traceFREE
    #define traceFREE( pvAddress, uiSize )
#endif

#ifndef traceEVENT_GROUP_CREATE
	#define traceEVENT_GROUP_CREATE( xEventGroup )
#endif

#ifndef traceEVENT_GROUP_CREATE_FAILED
	#define traceEVENT_GROUP_CREATE_FAILED()
#endif

#ifndef traceEVENT_GROUP_SYNC_BLOCK
	#define traceEVENT_GROUP_SYNC_BLOCK( xEventGroup, uxBitsToSet, uxBitsToWaitFor )
#endif

#ifndef traceEVENT_GROUP_SYNC_END
	#define traceEVENT_GROUP_SYNC_END( xEventGroup, uxBitsToSet, uxBitsToWaitFor, xTimeoutOccurred ) ( void ) xTimeoutOccurred
#endif

#ifndef traceEVENT_GROUP_WAIT_BITS_BLOCK
	#define traceEVENT_GROUP_WAIT_BITS_BLOCK( xEventGroup, uxBitsToWaitFor )
#endif

#ifndef traceEVENT_GROUP_WAIT_BITS_END
	#define traceEVENT_GROUP_WAIT_BITS_END( xEventGroup, uxBitsToWaitFor, xTimeoutOccurred ) ( void ) xTimeoutOccurred
#endif

#ifndef traceEVENT_GROUP_CLEAR_BITS
	#define traceEVENT_GROUP_CLEAR_BITS( xEventGroup, uxBitsToClear )
#endif

#ifndef traceEVENT_GROUP_CLEAR_BITS_FROM_ISR
	#define traceEVENT_GROUP_CLEAR_BITS_FROM_ISR( xEventGroup, uxBitsToClear )
#endif

#ifndef traceEVENT_GROUP_SET_BITS
	#define traceEVENT_GROUP_SET_BITS( xEventGroup, uxBitsToSet )
#endif

#ifndef traceEVENT_GROUP_SET_BITS_FROM_ISR
	#define traceEVENT_GROUP_SET_BITS_FROM_ISR( xEventGroup, uxBitsToSet )
#endif

#ifndef traceEVENT_GROUP_DELETE
	#define traceEVENT_GROUP_DELETE( xEventGroup )
#endif

#ifndef tracePEND_FUNC_CALL
	#define tracePEND_FUNC_CALL(xFunctionToPend, pvParameter1, ulParameter2, ret)
#endif

#ifndef tracePEND_FUNC_CALL_FROM_ISR
	#define tracePEND_FUNC_CALL_FROM_ISR(xFunctionToPend, pvParameter1, ulParameter2, ret)
#endif

#ifndef traceQUEUE_REGISTRY_ADD
	#define traceQUEUE_REGISTRY_ADD(xQueue, pcQueueName)
#endif

#ifndef traceTASK_NOTIFY_TAKE_BLOCK
	#define traceTASK_NOTIFY_TAKE_BLOCK()
#endif

#ifndef traceTASK_NOTIFY_TAKE
	#define traceTASK_NOTIFY_TAKE()
#endif

#ifndef traceTASK_NOTIFY_WAIT_BLOCK
	#define traceTASK_NOTIFY_WAIT_BLOCK()
#endif

#ifndef traceTASK_NOTIFY_WAIT
	#define traceTASK_NOTIFY_WAIT()
#endif

#ifndef traceTASK_NOTIFY
	#define traceTASK_NOTIFY()
#endif

#ifndef traceTASK_NOTIFY_FROM_ISR
	#define traceTASK_NOTIFY_FROM_ISR()
#endif

#ifndef traceTASK_NOTIFY_GIVE_FROM_ISR
	#define traceTASK_NOTIFY_GIVE_FROM_ISR()
#endif

#ifndef configGENERATE_RUN_TIME_STATS				////启用运行时间统计功能，在“任务通知的数据结构”章节的typedef struct tskTaskControlBlock才提到
	#define configGENERATE_RUN_TIME_STATS 0
#endif

#if ( configGENERATE_RUN_TIME_STATS == 1 )

	#ifndef portCONFIGURE_TIMER_FOR_RUN_TIME_STATS
		#error If configGENERATE_RUN_TIME_STATS is defined then portCONFIGURE_TIMER_FOR_RUN_TIME_STATS must also be defined.  portCONFIGURE_TIMER_FOR_RUN_TIME_STATS should call a port layer function to setup a peripheral timer/counter that can then be used as the run time counter time base.
	#endif /* portCONFIGURE_TIMER_FOR_RUN_TIME_STATS */

	#ifndef portGET_RUN_TIME_COUNTER_VALUE
		#ifndef portALT_GET_RUN_TIME_COUNTER_VALUE
			#error If configGENERATE_RUN_TIME_STATS is defined then either portGET_RUN_TIME_COUNTER_VALUE or portALT_GET_RUN_TIME_COUNTER_VALUE must also be defined.  See the examples provided and the FreeRTOS web site for more information.
		#endif /* portALT_GET_RUN_TIME_COUNTER_VALUE */
	#endif /* portGET_RUN_TIME_COUNTER_VALUE */

#endif /* configGENERATE_RUN_TIME_STATS */

#ifndef portCONFIGURE_TIMER_FOR_RUN_TIME_STATS	////"CPU 利用率统计"章节中用到 -- 首先在FreeRTOSConfig.h 配置与系统运行时间和任务状态收集有关的配置选项
	#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()
#endif

#ifndef configUSE_MALLOC_FAILED_HOOK			////使用内存申请失败钩子函数，在最后一章的"内存申请函数pvPortMalloc()"中会判断用到
	#define configUSE_MALLOC_FAILED_HOOK 0
#endif

#ifndef portPRIVILEGE_BIT						////调用xTaskCreate函数传参(优先级)时，会或上这个参数
	#define portPRIVILEGE_BIT ( ( UBaseType_t ) 0x00 )
#endif

#ifndef portYIELD_WITHIN_API					////封装的portYIELD
	#define portYIELD_WITHIN_API portYIELD
#endif

#ifndef portSUPPRESS_TICKS_AND_SLEEP			////野火中没用到
	#define portSUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime )
#endif

#ifndef configEXPECTED_IDLE_TIME_BEFORE_SLEEP	////野火中没用到
	#define configEXPECTED_IDLE_TIME_BEFORE_SLEEP 2
#endif

#if configEXPECTED_IDLE_TIME_BEFORE_SLEEP < 2	////野火中没用到
	#error configEXPECTED_IDLE_TIME_BEFORE_SLEEP must not be less than 2
#endif

#ifndef configUSE_TICKLESS_IDLE				////置 1：使能低功耗tickless 模式；置 0：保持系统节拍（tick）中断一直运行
	#define configUSE_TICKLESS_IDLE 0
#endif

#ifndef configPRE_SLEEP_PROCESSING			////野火中没用到
	#define configPRE_SLEEP_PROCESSING( x )
#endif

#ifndef configPOST_SLEEP_PROCESSING			////野火中没用到
	#define configPOST_SLEEP_PROCESSING( x )
#endif

#ifndef configUSE_QUEUE_SETS				////启用队列，野火中置为1
	#define configUSE_QUEUE_SETS 0
#endif

#ifndef portTASK_USES_FLOATING_POINT		////野火中没用到
	#define portTASK_USES_FLOATING_POINT()
#endif

#ifndef configUSE_TIME_SLICING				////使能时间片调度
	#define configUSE_TIME_SLICING 1
#endif

#ifndef configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS		////野火中没用到
	#define configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS 0
#endif

#ifndef configUSE_STATS_FORMATTING_FUNCTIONS		////野火FreeRTOSConfig.h中置1
	#define configUSE_STATS_FORMATTING_FUNCTIONS 0
#endif

#ifndef portASSERT_IF_INTERRUPT_PRIORITY_INVALID	////xTaskResumeFromISR()函数中有用到
	#define portASSERT_IF_INTERRUPT_PRIORITY_INVALID()
#endif

#ifndef configUSE_TRACE_FACILITY					////野火FreeRTOSConfig.h中已置0
	#define configUSE_TRACE_FACILITY 0
#endif

#ifndef mtCOVERAGE_TEST_MARKER						////在引用else中都会加个这句？？
	#define mtCOVERAGE_TEST_MARKER()
#endif

#ifndef mtCOVERAGE_TEST_DELAY						////野火中没用到
	#define mtCOVERAGE_TEST_DELAY()
#endif

#ifndef portASSERT_IF_IN_ISR						////野火中没用到
	#define portASSERT_IF_IN_ISR()
#endif

#ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION		////在portmacro.h中已经置1：使用前置零法管理任务优先级；置0则为选择通用方法
	#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0
#endif

#ifndef configAPPLICATION_ALLOCATED_HEAP			////野火中没用到
	#define configAPPLICATION_ALLOCATED_HEAP 0
#endif

#ifndef configUSE_TASK_NOTIFICATIONS				////开启任务通知功能，默认开启
	#define configUSE_TASK_NOTIFICATIONS 1
#endif

#ifndef portTICK_TYPE_IS_ATOMIC						////野火中没用到
	#define portTICK_TYPE_IS_ATOMIC 0
#endif

#ifndef configSUPPORT_STATIC_ALLOCATION				////支持静态内存
	/* Defaults to 0 for backward compatibility. */
	#define configSUPPORT_STATIC_ALLOCATION 0
#endif

#ifndef configSUPPORT_DYNAMIC_ALLOCATION			////支持动态内存
	/* Defaults to 1 for backward compatibility. */
	#define configSUPPORT_DYNAMIC_ALLOCATION 1
#endif

/* Sanity check the configuration. */				////检查一些配置是否符合
#if( configUSE_TICKLESS_IDLE != 0 )					////是否使能低功耗tickless，在上面已置0
	#if( INCLUDE_vTaskSuspend != 1 )				////低功耗模式下，挂起函数一定要有定义
		#error INCLUDE_vTaskSuspend must be set to 1 if configUSE_TICKLESS_IDLE is not set to 0
	#endif /* INCLUDE_vTaskSuspend */
#endif /* configUSE_TICKLESS_IDLE */

#if( ( configSUPPORT_STATIC_ALLOCATION == 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 0 ) )		////动静态内存不能同时置0
	#error configSUPPORT_STATIC_ALLOCATION and configSUPPORT_DYNAMIC_ALLOCATION cannot both be 0, but can both be 1.
#endif

#if( ( configUSE_RECURSIVE_MUTEXES == 1 ) && ( configUSE_MUTEXES != 1 ) )							////开递归互斥锁要先开互斥锁
	#error configUSE_MUTEXES must be set to 1 to use recursive mutexes
#endif

#if( portTICK_TYPE_IS_ATOMIC == 0 )
	/* Either variables of tick type cannot be read atomically, or
	portTICK_TYPE_IS_ATOMIC was not set - map the critical sections used when
	the tick count is returned to the standard critical section macros. */
	#define portTICK_TYPE_ENTER_CRITICAL() portENTER_CRITICAL()
	#define portTICK_TYPE_EXIT_CRITICAL() portEXIT_CRITICAL()
	#define portTICK_TYPE_SET_INTERRUPT_MASK_FROM_ISR() portSET_INTERRUPT_MASK_FROM_ISR()
	#define portTICK_TYPE_CLEAR_INTERRUPT_MASK_FROM_ISR( x ) portCLEAR_INTERRUPT_MASK_FROM_ISR( ( x ) )
#else
	/* The tick type can be read atomically, so critical sections used when the						////进入或退出临界区的接口，定义在task.c中
	tick count is returned can be defined away. */
	#define portTICK_TYPE_ENTER_CRITICAL()
	#define portTICK_TYPE_EXIT_CRITICAL()
	#define portTICK_TYPE_SET_INTERRUPT_MASK_FROM_ISR() 0
	#define portTICK_TYPE_CLEAR_INTERRUPT_MASK_FROM_ISR( x ) ( void ) x
#endif

/* Definitions to allow backward compatibility with FreeRTOS versions prior to
V8 if desired. */
#ifndef configENABLE_BACKWARD_COMPATIBILITY				////野火中没用到
	#define configENABLE_BACKWARD_COMPATIBILITY 1
#endif

#if configENABLE_BACKWARD_COMPATIBILITY == 1			////为兼容旧版本的freertos
	#define eTaskStateGet eTaskGetState
	#define portTickType TickType_t
	#define xTaskHandle TaskHandle_t
	#define xQueueHandle QueueHandle_t
	#define xSemaphoreHandle SemaphoreHandle_t
	#define xQueueSetHandle QueueSetHandle_t
	#define xQueueSetMemberHandle QueueSetMemberHandle_t
	#define xTimeOutType TimeOut_t
	#define xMemoryRegion MemoryRegion_t
	#define xTaskParameters TaskParameters_t
	#define xTaskStatusType	TaskStatus_t
	#define xTimerHandle TimerHandle_t
	#define xCoRoutineHandle CoRoutineHandle_t
	#define pdTASK_HOOK_CODE TaskHookFunction_t
	#define portTICK_RATE_MS portTICK_PERIOD_MS
	#define pcTaskGetTaskName pcTaskGetName
	#define pcTimerGetTimerName pcTimerGetName
	#define pcQueueGetQueueName pcQueueGetName
	#define vTaskGetTaskInfo vTaskGetInfo

	/* Backward compatibility within the scheduler code only - these definitions
	are not really required but are included for completeness. */
	#define tmrTIMER_CALLBACK TimerCallbackFunction_t
	#define pdTASK_CODE TaskFunction_t
	#define xListItem ListItem_t
	#define xList List_t
#endif /* configENABLE_BACKWARD_COMPATIBILITY */

#if( configUSE_ALTERNATIVE_API != 0 )			////已废弃使用
	#error The alternative API was deprecated some time ago, and was removed in FreeRTOS V9.0 0
#endif

/* Set configUSE_TASK_FPU_SUPPORT to 0 to omit floating point support even
if floating point hardware is otherwise supported by the FreeRTOS port in use.
This constant is not supported by all FreeRTOS ports that include floating
point support. */
#ifndef configUSE_TASK_FPU_SUPPORT				////野火中没用到
	#define configUSE_TASK_FPU_SUPPORT 1
#endif

/*
 * In line with software engineering best practice, FreeRTOS implements a strict
 * data hiding policy, so the real structures used by FreeRTOS to maintain the
 * state of tasks, queues, semaphores, etc. are not accessible to the application
 * code.  However, if the application writer wants to statically allocate such
 * an object then the size of the object needs to be know.  Dummy structures
 * that are guaranteed to have the same size and alignment requirements of the
 * real objects are used for this purpose.  The dummy list and list item
 * structures below are used for inclusion in such a dummy structure.
 */
struct xSTATIC_LIST_ITEM
{
	TickType_t xDummy1;
	void *pvDummy2[ 4 ];
};
typedef struct xSTATIC_LIST_ITEM StaticListItem_t;

/* See the comments above the struct xSTATIC_LIST_ITEM definition. */
struct xSTATIC_MINI_LIST_ITEM
{
	TickType_t xDummy1;
	void *pvDummy2[ 2 ];
};
typedef struct xSTATIC_MINI_LIST_ITEM StaticMiniListItem_t;

/* See the comments above the struct xSTATIC_LIST_ITEM definition. */
typedef struct xSTATIC_LIST
{
	UBaseType_t uxDummy1;
	void *pvDummy2;
	StaticMiniListItem_t xDummy3;
} StaticList_t;

/*
 * In line with software engineering best practice, especially when supplying a
 * library that is likely to change in future versions, FreeRTOS implements a
 * strict data hiding policy.  This means the Task structure used internally by
 * FreeRTOS is not accessible to application code.  However, if the application
 * writer wants to statically allocate the memory required to create a task then
 * the size of the task object needs to be know.  The StaticTask_t structure
 * below is provided for this purpose.  Its sizes and alignment requirements are
 * guaranteed to match those of the genuine structure, no matter which
 * architecture is being used, and no matter how the values in FreeRTOSConfig.h
 * are set.  Its contents are somewhat obfuscated in the hope users will
 * recognise that it would be unwise to make direct use of the structure members.
 */
typedef struct xSTATIC_TCB
{
	void				*pxDummy1;
	#if ( portUSING_MPU_WRAPPERS == 1 )
		xMPU_SETTINGS	xDummy2;
	#endif
	StaticListItem_t	xDummy3[ 2 ];
	UBaseType_t			uxDummy5;
	void				*pxDummy6;
	uint8_t				ucDummy7[ configMAX_TASK_NAME_LEN ];
	#if ( portSTACK_GROWTH > 0 )
		void			*pxDummy8;
	#endif
	#if ( portCRITICAL_NESTING_IN_TCB == 1 )
		UBaseType_t		uxDummy9;
	#endif
	#if ( configUSE_TRACE_FACILITY == 1 )
		UBaseType_t		uxDummy10[ 2 ];
	#endif
	#if ( configUSE_MUTEXES == 1 )
		UBaseType_t		uxDummy12[ 2 ];
	#endif
	#if ( configUSE_APPLICATION_TASK_TAG == 1 )
		void			*pxDummy14;
	#endif
	#if( configNUM_THREAD_LOCAL_STORAGE_POINTERS > 0 )
		void			*pvDummy15[ configNUM_THREAD_LOCAL_STORAGE_POINTERS ];
	#endif
	#if ( configGENERATE_RUN_TIME_STATS == 1 )
		uint32_t		ulDummy16;
	#endif
	#if ( configUSE_NEWLIB_REENTRANT == 1 )
		struct	_reent	xDummy17;
	#endif
	#if ( configUSE_TASK_NOTIFICATIONS == 1 )
		uint32_t 		ulDummy18;
		uint8_t 		ucDummy19;
	#endif
	#if( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
		uint8_t			uxDummy20;
	#endif

} StaticTask_t;

/*
 * In line with software engineering best practice, especially when supplying a
 * library that is likely to change in future versions, FreeRTOS implements a
 * strict data hiding policy.  This means the Queue structure used internally by
 * FreeRTOS is not accessible to application code.  However, if the application
 * writer wants to statically allocate the memory required to create a queue
 * then the size of the queue object needs to be know.  The StaticQueue_t
 * structure below is provided for this purpose.  Its sizes and alignment
 * requirements are guaranteed to match those of the genuine structure, no
 * matter which architecture is being used, and no matter how the values in
 * FreeRTOSConfig.h are set.  Its contents are somewhat obfuscated in the hope
 * users will recognise that it would be unwise to make direct use of the
 * structure members.
 */
typedef struct xSTATIC_QUEUE
{
	void *pvDummy1[ 3 ];

	union
	{
		void *pvDummy2;
		UBaseType_t uxDummy2;
	} u;

	StaticList_t xDummy3[ 2 ];
	UBaseType_t uxDummy4[ 3 ];
	uint8_t ucDummy5[ 2 ];

	#if( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
		uint8_t ucDummy6;
	#endif

	#if ( configUSE_QUEUE_SETS == 1 )
		void *pvDummy7;
	#endif

	#if ( configUSE_TRACE_FACILITY == 1 )
		UBaseType_t uxDummy8;
		uint8_t ucDummy9;
	#endif

} StaticQueue_t;
typedef StaticQueue_t StaticSemaphore_t;

/*
 * In line with software engineering best practice, especially when supplying a
 * library that is likely to change in future versions, FreeRTOS implements a
 * strict data hiding policy.  This means the event group structure used
 * internally by FreeRTOS is not accessible to application code.  However, if
 * the application writer wants to statically allocate the memory required to
 * create an event group then the size of the event group object needs to be
 * know.  The StaticEventGroup_t structure below is provided for this purpose.
 * Its sizes and alignment requirements are guaranteed to match those of the
 * genuine structure, no matter which architecture is being used, and no matter
 * how the values in FreeRTOSConfig.h are set.  Its contents are somewhat
 * obfuscated in the hope users will recognise that it would be unwise to make
 * direct use of the structure members.
 */
typedef struct xSTATIC_EVENT_GROUP
{
	TickType_t xDummy1;
	StaticList_t xDummy2;

	#if( configUSE_TRACE_FACILITY == 1 )
		UBaseType_t uxDummy3;
	#endif

	#if( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
			uint8_t ucDummy4;
	#endif

} StaticEventGroup_t;

/*
 * In line with software engineering best practice, especially when supplying a
 * library that is likely to change in future versions, FreeRTOS implements a
 * strict data hiding policy.  This means the software timer structure used
 * internally by FreeRTOS is not accessible to application code.  However, if
 * the application writer wants to statically allocate the memory required to
 * create a software timer then the size of the queue object needs to be know.
 * The StaticTimer_t structure below is provided for this purpose.  Its sizes
 * and alignment requirements are guaranteed to match those of the genuine
 * structure, no matter which architecture is being used, and no matter how the
 * values in FreeRTOSConfig.h are set.  Its contents are somewhat obfuscated in
 * the hope users will recognise that it would be unwise to make direct use of
 * the structure members.
 */
typedef struct xSTATIC_TIMER
{
	void				*pvDummy1;
	StaticListItem_t	xDummy2;
	TickType_t			xDummy3;
	UBaseType_t			uxDummy4;
	void 				*pvDummy5[ 2 ];
	#if( configUSE_TRACE_FACILITY == 1 )
		UBaseType_t		uxDummy6;
	#endif

	#if( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
		uint8_t 		ucDummy7;
	#endif

} StaticTimer_t;

#ifdef __cplusplus
}
#endif

#endif /* INC_FREERTOS_H */

