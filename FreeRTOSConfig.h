#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H


#define configUSE_PREEMPTION		1                               ////置 1：RTOS 使用抢占式调度器；置 0：RTOS 使用协作式调度器（时间片）
#define configUSE_IDLE_HOOK			0                               ////置 1：使用空闲钩子（Idle Hook 类似于回调函数）；置 0：忽略空闲钩子
#define configUSE_TICK_HOOK			0                               ////置 1：使用时间片钩子（Tick Hook）；置 0：忽略时间片钩子
#define configCPU_CLOCK_HZ			( ( unsigned long ) 72000000 )	////写入实际的 CPU 内核时钟频率，也就是 CPU 指令执行频率，通常称为 Fclk
#define configTICK_RATE_HZ			( ( TickType_t ) 1000 )         ////RTOS 系统节拍中断的频率。即一秒中断的次数，每次中断 RTOS 都会进行任务调度
#define configMAX_PRIORITIES		( 5 )                           ////可使用的最大优先级
#define configMINIMAL_STACK_SIZE	( ( unsigned short ) 128 )      ////空闲任务使用的堆栈大小
#define configTOTAL_HEAP_SIZE		( ( size_t ) ( 17 * 1024 ) )    ////系统所有总的堆大小
#define configMAX_TASK_NAME_LEN		( 16 )                          ////任务名字字符串长度
#define configUSE_TRACE_FACILITY	0                               ////启用可视化跟踪调试
#define configUSE_16_BIT_TICKS		0                               ////系统节拍计数器变量数据类型，1 表示为 16 位无符号整形，0 表示为 32 位无符号整形
#define configIDLE_SHOULD_YIELD		1                               ////空闲任务放弃 CPU 使用权给其他同优先级的用户任务    

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 		0                               ////启用协程，启用协程以后必须添加文件 croutine.c
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )                       ////协程的有效优先级数目

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

#define INCLUDE_vTaskPrioritySet		1           ////INCLUDE打头的是“FreeRTOS可选函数配置选项”
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	0
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1

/* This is the raw value as per the Cortex-M3 NVIC.  Values can be 255
(lowest) to 0 (1?) (highest). */
#define configKERNEL_INTERRUPT_PRIORITY 		255     ////在port.c中会用到这个宏定义来配置SCB_SHPR3（系统处理优先级寄存器，地址为：0xE000 ED20）
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	191 /* equivalent to 0xb0, or priority 11. */


/* This is the value being used as per the ST library which permits 16
priority values, 0 to 15.  This must correspond to the
configKERNEL_INTERRUPT_PRIORITY setting.  Here 15 corresponds to the lowest
NVIC value of 255. */
#define configLIBRARY_KERNEL_INTERRUPT_PRIORITY	15      ////在野火FreeRTOSConfig.h中特有的configLIBRARY_LOWEST_INTERRUPT_PRIORITY (15) ？？

#endif /* FREERTOS_CONFIG_H */

