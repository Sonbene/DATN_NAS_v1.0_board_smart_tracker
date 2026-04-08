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

typedef struct {
    char msg[LOG_MSG_MAX_LEN];
} LogMsg_t;

static QueueHandle_t xLogQueue = NULL;

void StartLogTask(void const * argument);

void Debug_Init(void)
{
    /* UART is initialized in main.c */
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
        HAL_UART_Transmit(DEBUG_UART, (uint8_t*)item.msg, len, 100);
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
            /* Output to UART using the content length */
            HAL_UART_Transmit(DEBUG_UART, (uint8_t*)item.msg, strlen(item.msg), 1000);
        }
    }
}

#endif /* DEBUG_ENABLE */
