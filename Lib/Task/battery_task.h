#ifndef __BATTERY_TASK_H__
#define __BATTERY_TASK_H__

#include <stdint.h>
#include "stm32l4xx_hal.h"

/**
 * @brief Khởi tạo Task đo Pin
 * @param hadc: Handle ADC của HAL
 * @param channel: Channel ADC tương ứng (vd: ADC_CHANNEL_6)
 */
void Battery_Task_Init(ADC_HandleTypeDef *hadc, uint32_t channel);

/**
 * @brief Lấy điện áp pin hiện tại (mV)
 */
uint32_t Battery_GetVoltage(void);

/**
 * @brief Lấy phần trăm pin hiện tại (0-100%)
 */
uint8_t Battery_GetPercentage(void);

/**
 * @brief Hàm xử lý ngắt ADC hoàn tất (Gọi từ main.c callback)
 */
void Battery_Task_ADC_Callback(ADC_HandleTypeDef* hadc);

#endif /* __BATTERY_TASK_H__ */
