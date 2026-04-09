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
#define LOG_QUEUE_LEN   20

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

    /* 
     * If scheduler is not running yet, or queue is not initialized,
     * send directly to UART (blocking) so we don't lose early boot logs.
     */
    if (xTaskGetSchedulerState() != taskSCHEDULER_RUNNING || xLogQueue == NULL) {
        /* Before OS starts, Mutex and TaskNotify are not available. Use polling. */
        BSP_UART_Transmit(&debug_uart_handle, (uint8_t*)item.msg, len, 100);
    } else {
        /* Push to queue - non-blocking */
        xQueueSend(xLogQueue, &item, 0);
    }
}

void StartLogTask(void const * argument)
{
    LogMsg_t item;
    
    while(1) {
        /* Wait forever for a message in the queue */
        if (xQueueReceive(xLogQueue, &item, portMAX_DELAY) == pdPASS) {
            uint16_t len = strlen(item.msg);
            
            /* Lock the TX path -> only one task can send at a time */
            if (BSP_UART_LockTx(&debug_uart_handle, portMAX_DELAY) == BSP_UART_OK) {
                
                /* 
                 * Attempt to use DMA to free up CPU. 
                 * If DMA fails to start (e.g. DMA is not configured in CubeMX), fallback to Polling. 
                 * WARNING: If DMA is configured but NVIC Interrupt for DMA is NOT enabled, it will timeout here!
                 */
                if (debug_uart_handle.huart->hdmatx != NULL && 
                    BSP_UART_Transmit_DMA(&debug_uart_handle, (uint8_t*)item.msg, len) == BSP_UART_OK) {
                    /* Sleep and wait for DMA to finish (CPU usage = 0%) */
                    BSP_UART_WaitTxDone(&debug_uart_handle, 1000);
                } else {
                    /* Fallback to blocking polling method */
                    BSP_UART_Transmit(&debug_uart_handle, (uint8_t*)item.msg, len, 1000);
                }
                
                BSP_UART_UnlockTx(&debug_uart_handle);
            }
        }
    }
}

#endif /* DEBUG_ENABLE */
