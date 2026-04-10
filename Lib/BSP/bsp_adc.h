#ifndef __BSP_ADC_H__
#define __BSP_ADC_H__

#include "stm32l4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"

/* Cấu hình đo lường */
#define BSP_ADC_OVERSAMPLING_COUNT    64    /* Số mẫu lấy trung bình phần mềm */
#define BSP_ADC_BATTERY_DIVIDER_RATIO 4.0f  /* Cầu chia 300k/100k => (300+100)/100 = 4.0 */
#define BSP_ADC_DIODE_DROP_MV         300.0f /* Bù sụt áp qua diode SS34 (~0.3V) */

typedef enum {
    BSP_ADC_OK = 0,
    BSP_ADC_ERROR,
    BSP_ADC_BUSY,
    BSP_ADC_TIMEOUT
} BSP_ADC_Status_t;

typedef struct {
    ADC_HandleTypeDef *hadc;
    uint32_t channel;
    uint16_t buffer[BSP_ADC_OVERSAMPLING_COUNT];
    TaskHandle_t task_to_notify;
    uint32_t last_raw_value;
} BSP_ADC_Handle_t;

/**
 * @brief Khởi tạo Handle cho ADC
 */
BSP_ADC_Status_t BSP_ADC_Init(BSP_ADC_Handle_t *handle, ADC_HandleTypeDef *hadc, uint32_t channel);

/**
 * @brief Đọc giá trị ADC thông qua DMA (Block task cho đến khi xong)
 */
BSP_ADC_Status_t BSP_ADC_Read_DMA(BSP_ADC_Handle_t *handle, uint32_t timeout_ms);

/**
 * @brief Lấy điện áp tính bằng mV (đã tính qua cầu chia áp và hiệu chuẩn VrefInt)
 * @note Hàm này sẽ thực hiện Read_DMA bên trong
 */
float BSP_ADC_GetBatteryVoltage(BSP_ADC_Handle_t *handle);

/**
 * @brief Callback gọi từ HAL_ADC_ConvCpltCallback
 */
void BSP_ADC_ConvCpltCallback(BSP_ADC_Handle_t *handle);

#endif /* __BSP_ADC_H__ */
