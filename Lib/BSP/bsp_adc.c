#include "bsp_adc.h"
#include <string.h>

/* VDDA mặc định nếu không có calibration */
#ifndef VDDA_VOLTAGE
#define VDDA_VOLTAGE 3.3f
#endif

BSP_ADC_Status_t BSP_ADC_Init(BSP_ADC_Handle_t *handle, ADC_HandleTypeDef *hadc, uint32_t channel) {
    if (handle == NULL || hadc == NULL) {
        return BSP_ADC_ERROR;
    }
    
    memset(handle, 0, sizeof(BSP_ADC_Handle_t));
    handle->hadc = hadc;
    handle->channel = channel;
    
    return BSP_ADC_OK;
}

BSP_ADC_Status_t BSP_ADC_Read_DMA(BSP_ADC_Handle_t *handle, uint32_t timeout_ms) {
    if (handle == NULL || handle->hadc == NULL) {
        return BSP_ADC_ERROR;
    }

    /* 1. Bật chế độ Continuous để đo nhanh 64 mẫu liên tục */
    handle->hadc->Instance->CFGR |= ADC_CFGR_CONT;

    /* 2. Bắt đầu đo DMA */
    handle->task_to_notify = xTaskGetCurrentTaskHandle();
    memset(handle->buffer, 0, sizeof(handle->buffer));

    if (HAL_ADC_Start_DMA(handle->hadc, (uint32_t*)handle->buffer, BSP_ADC_OVERSAMPLING_COUNT) != HAL_OK) {
        handle->hadc->Instance->CFGR &= ~ADC_CFGR_CONT;
        return BSP_ADC_ERROR;
    }

    /* 3. Đợi thông báo từ ISR (Timeout 200ms) */
    if (ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(200)) == 0) {
        HAL_ADC_Stop_DMA(handle->hadc);
        handle->hadc->Instance->CFGR &= ~ADC_CFGR_CONT;
        return BSP_ADC_TIMEOUT;
    }

    /* 4. Tắt chế độ Continuous sau khi đo xong */
    HAL_ADC_Stop_DMA(handle->hadc);
    handle->hadc->Instance->CFGR &= ~ADC_CFGR_CONT;

    /* 5. Tính trung bình phần mềm */
    uint32_t sum = 0;
    for (int i = 0; i < BSP_ADC_OVERSAMPLING_COUNT; i++) {
        sum += handle->buffer[i];
    }
    handle->last_raw_value = sum / BSP_ADC_OVERSAMPLING_COUNT;

    return BSP_ADC_OK;
}

float BSP_ADC_GetBatteryVoltage(BSP_ADC_Handle_t *handle) {
    if (BSP_ADC_Read_DMA(handle, 100) != BSP_ADC_OK) {
        return 0.0f;
    }

    /* Chuyển đổi Raw sang mV */
    /* Công thức: Voltage(mV) = (Raw * VDDA_mV / 4095) * Divider_Ratio + Diode_Drop */
    float voltage = ((float)handle->last_raw_value * (VDDA_VOLTAGE * 1000.0f) / 4095.0f) * BSP_ADC_BATTERY_DIVIDER_RATIO;
    voltage += BSP_ADC_DIODE_DROP_MV;
    
    return voltage;
}

void BSP_ADC_ConvCpltCallback(BSP_ADC_Handle_t *handle) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (handle != NULL && handle->task_to_notify != NULL) {
        vTaskNotifyGiveFromISR(handle->task_to_notify, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}
