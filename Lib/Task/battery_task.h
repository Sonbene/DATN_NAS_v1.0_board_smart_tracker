#ifndef __BATTERY_TASK_H__
#define __BATTERY_TASK_H__

#include <stdint.h>

/**
 * @brief Khởi tạo task đo Pin
 */
void Battery_Task_Init(void);

/**
 * @brief Lấy điện áp pin hiện tại (mV)
 */
uint32_t Battery_GetVoltage(void);

/**
 * @brief Lấy phần trăm pin hiện tại (0-100%)
 */
uint8_t Battery_GetPercentage(void);

#endif /* __BATTERY_TASK_H__ */
