/**
 * @file    log.h
 * @brief   Debug Logging Module using UART1
 */

#ifndef __LOG_H__
#define __LOG_H__

#include <stdbool.h>
#include "main.h"

/* GLOBAL DEBUG ENABLE SWITCH 
 * Comment out this line to disable all debug logging code generation
 */
#define DEBUG_ENABLE   /* Enabled for testing RX flow */

#ifdef DEBUG_ENABLE
    
    #define LOG_MSG_MAX_LEN  256

    /**
     * @brief Initialize Debug UART (UART3) and Log Task/Queue
     */
    void Debug_Init(void);
    void Log_Task_Init(void);
    
    /**
     * @brief Print formatted debug message (Sends to queue)
     */
    void Debug_Log(const char *fmt, ...);
    
    /* Log wrapper macros */
    #define LOG_INFO(fmt, ...)  Debug_Log("[INFO] " fmt "\r\n", ##__VA_ARGS__)
    #define LOG_WARN(fmt, ...)  Debug_Log("[WARN] " fmt "\r\n", ##__VA_ARGS__)
    #define LOG_ERROR(fmt, ...) Debug_Log("[ERROR] " fmt "\r\n", ##__VA_ARGS__)
    #define LOG_RAW(fmt, ...)   Debug_Log(fmt, ##__VA_ARGS__)

#else
    /* Empty macros when disabled - code optimizes away completely */
    #define Debug_Init()        ((void)0)
    #define Log_Task_Init()     ((void)0)
    #define Debug_Log(fmt, ...) ((void)0)
    
    #define LOG_INFO(fmt, ...)  ((void)0)
    #define LOG_WARN(fmt, ...)  ((void)0)
    #define LOG_ERROR(fmt, ...) ((void)0)
    #define LOG_RAW(fmt, ...)   ((void)0)

#endif /* DEBUG_ENABLE */

#endif /* DEBUG_LOG_H */
