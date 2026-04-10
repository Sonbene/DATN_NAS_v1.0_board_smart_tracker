#include "log.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "queue.h"

#ifdef DEBUG_ENABLE

/* External handles from main.c */
extern UART_HandleTypeDef huart3;

/* Config */
#define DEBUG_UART      &huart3
#define LOG_QUEUE_LEN   30

BSP_UART_Handle_t debug_uart_handle;

typedef struct {
    char msg[LOG_MSG_MAX_LEN];
} LogMsg_t;

static QueueHandle_t xLogQueue = NULL;

void StartLogTask(void const * argument);

void Debug_Init(void)
{
    /* UART is initialized in main.c, initialize BSP handle here */
    BSP_UART_Init(&debug_uart_handle, DEBUG_UART);
}

void Log_Task_Init(void)
{
    /* Create Queue to hold log messages */
    xLogQueue = xQueueCreate(LOG_QUEUE_LEN, sizeof(LogMsg_t));
    
    if (xLogQueue != NULL) {
        /* Create Logging Task */
        osThreadDef(logTask, StartLogTask, osPriorityBelowNormal, 0, 512);
        osThreadCreate(osThread(logTask), NULL);
        
        LOG_INFO("Task-Based Logging Initialized (Buf: %d, Que: %d)", LOG_MSG_MAX_LEN, LOG_QUEUE_LEN);
    }
}

void Debug_Log(const char *fmt, ...)
{
    LogMsg_t item;
    va_list args;
    int len;
    
    va_start(args, fmt);
    len = vsnprintf(item.msg, LOG_MSG_MAX_LEN, fmt, args);
    va_end(args);

    if (len <= 0) return;

    if (xTaskGetSchedulerState() != taskSCHEDULER_RUNNING || xLogQueue == NULL) {
        BSP_UART_Transmit(&debug_uart_handle, (uint8_t*)item.msg, len, 100);
    } else {
        if ((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0) {
            BaseType_t xHigherPriorityTaskWoken = pdFALSE;
            xQueueSendFromISR(xLogQueue, &item, &xHigherPriorityTaskWoken);
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        } else {
            xQueueSend(xLogQueue, &item, 0);
        }
    }
}

void StartLogTask(void const * argument)
{
    LogMsg_t item;
    while(1) {
        if (xQueueReceive(xLogQueue, &item, portMAX_DELAY) == pdPASS) {
            uint16_t len = strlen(item.msg);
            if (BSP_UART_LockTx(&debug_uart_handle, portMAX_DELAY) == BSP_UART_OK) {
                if (debug_uart_handle.huart->hdmatx != NULL && 
                    BSP_UART_Transmit_DMA(&debug_uart_handle, (uint8_t*)item.msg, len) == BSP_UART_OK) {
                    BSP_UART_WaitTxDone(&debug_uart_handle, 1000);
                } else {
                    BSP_UART_Transmit(&debug_uart_handle, (uint8_t*)item.msg, len, 1000);
                }
                BSP_UART_UnlockTx(&debug_uart_handle);
            }
        }
    }
}

/* ========================================================================================
 * SECTION: Run-Time Stats Timer (Using HAL Tick)
 * ======================================================================================== */

void configureTimerForRunTimeStats(void) {
    /* Không cần timer phần cứng riêng, dùng SysTick của HAL */
}

unsigned long getRunTimeCounterValue(void) {
    /* Trả về đơn vị 0.1ms (100us) để có độ phân giải tốt hơn Tick chuẩn (1ms) */
    return HAL_GetTick() * 10;
}

/* ========================================================================================
 * SECTION: System Monitor Implementation
 * ======================================================================================== */

void Log_PrintSystemStats(void) {
#if LOG_ENABLE_SYS_MONITOR
    static char stats_buffer[1024];

    LOG_INFO("--- [SYSTEM MONITOR] ---");
    LOG_INFO("Task Name       Stat  Prio  Stack   ID");
    LOG_INFO("--------------------------------------");
    vTaskList(stats_buffer);
    
    /* Căn chỉnh bảng: Thay mỗi Tab bằng 2 space và thêm padding */
    for(int i=0; i<1024 && stats_buffer[i] != '\0'; i++) {
        if(stats_buffer[i] == '\t') stats_buffer[i] = ' ';
    }
    LOG_INFO("\n%s", stats_buffer);

    LOG_INFO("--- [CPU USAGE] ---");
    vTaskGetRunTimeStats(stats_buffer);
    for(int i=0; i<1024 && stats_buffer[i] != '\0'; i++) {
        if(stats_buffer[i] == '\t') stats_buffer[i] = ' ';
    }
    LOG_INFO("\n%s", stats_buffer);

    LOG_INFO("--- [MEMORY] ---");
    LOG_INFO("Heap Free: %d bytes", (int)xPortGetFreeHeapSize());
    LOG_INFO("Heap Min Free: %d bytes", (int)xPortGetMinimumEverFreeHeapSize());
    LOG_INFO("--------------------------------------");
#endif
}

#endif /* DEBUG_ENABLE */
