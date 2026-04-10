#ifndef __SIM_TASK_H__
#define __SIM_TASK_H__

#include "stm32l4xx_hal.h"

/**
 * @brief Khởi tạo Task quản lý Modem SIM (MQTT + Network)
 * @param huart: Handle UART của HAL (vd: &huart2)
 */
void SIM_Task_Init(UART_HandleTypeDef *huart);

/**
 * @brief Hàm xử lý nhận dữ liệu UART (Gọi từ main.c callback)
 */
void SIM_Task_UART_RxCallback(UART_HandleTypeDef *huart, uint16_t Size);

/**
 * @brief Thông báo sự kiện ngắt từ chân RI (Ring Indicator)
 */
void SIM_Task_NotifyRIFromISR(void);

#endif /* __SIM_TASK_H__ */
