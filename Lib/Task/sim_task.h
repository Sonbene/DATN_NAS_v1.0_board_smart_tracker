#ifndef __SIM_TASK_H__
#define __SIM_TASK_H__

#include "stm32l4xx_hal.h"
#include "stdbool.h"

/**
 * @brief Khởi tạo Task quản lý Modem SIM (MQTT + Network)
 * @param huart: Handle UART của HAL (vd: &huart2)
 */
void SIM_Task_Init(UART_HandleTypeDef *huart);

/**
 * @brief Điều khiển chế độ ngủ của Modem (DTR pin + AT+CSCLK)
 * @param enable true để đi ngủ, false để thức dậy
 */
void SIM_Task_SetSleep(bool enable);

/**
 * @brief Hàm xử lý nhận dữ liệu UART (Gọi từ main.c callback)
 */
void SIM_Task_UART_RxCallback(UART_HandleTypeDef *huart, uint16_t Size);

/**
 * @brief Thông báo sự kiện ngắt từ chân RI (Ring Indicator)
 */
void SIM_Task_NotifyRIFromISR(void);

/**
 * @brief Khôi phục ngoại vi UART của SIM (Dùng sau khi thức dậy)
 */
void SIM_Task_RestoreUART(void);

/**
 * @brief Kiểm tra xem SIM Task có đang bận xử lý lệnh quan trọng không
 */
bool SIM_Task_IsBusy(void);

#endif /* __SIM_TASK_H__ */
