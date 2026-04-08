#include "bsp_spi.h"
#include <string.h>

BSP_SPI_Status_t BSP_SPI_Bus_Init(BSP_SPI_Bus_t *bus, SPI_HandleTypeDef *hspi)
{
    if(bus == NULL || hspi == NULL) return BSP_SPI_ERROR;

    bus->hspi = hspi;
    bus->mutex = xSemaphoreCreateMutex();
    configASSERT(bus->mutex != NULL);
    bus->active_handle = NULL;

    return BSP_SPI_OK;
}

BSP_SPI_Status_t BSP_SPI_Handle_Init(BSP_SPI_Handle_t *handle, BSP_SPI_Bus_t *bus)
{
    if(handle == NULL || bus == NULL) return BSP_SPI_ERROR;

    handle->bus = bus;
    handle->callback = NULL;
    handle->task_to_notify = NULL;

    return BSP_SPI_OK;
}

BSP_SPI_Status_t BSP_SPI_LockBus(BSP_SPI_Handle_t *handle, uint32_t timeout)
{
    if(handle == NULL || handle->bus == NULL) return BSP_SPI_ERROR;
    
    if(xSemaphoreTake(handle->bus->mutex, pdMS_TO_TICKS(timeout)) != pdTRUE){
        return BSP_SPI_BUSY;
    }
    
    /* Mark this handle as the active one on the bus */
    handle->bus->active_handle = handle;
    handle->task_to_notify = xTaskGetCurrentTaskHandle();
    
    return BSP_SPI_OK;
}

void BSP_SPI_UnlockBus(BSP_SPI_Handle_t *handle)
{
    if(handle == NULL || handle->bus == NULL) return;
    
    handle->bus->active_handle = NULL;
    handle->task_to_notify = NULL;
    xSemaphoreGive(handle->bus->mutex);
}

BSP_SPI_Status_t BSP_SPI_Transmit(BSP_SPI_Handle_t *handle, uint8_t* tx_buf, uint16_t len, uint32_t timeout)
{
    if(handle == NULL || handle->bus == NULL || tx_buf == NULL || len == 0) return BSP_SPI_ERROR;
    HAL_StatusTypeDef status = HAL_SPI_Transmit(handle->bus->hspi, tx_buf, len, timeout);
    return (status == HAL_OK) ? BSP_SPI_OK : BSP_SPI_ERROR;
}

BSP_SPI_Status_t BSP_SPI_Receive(BSP_SPI_Handle_t *handle, uint8_t* rx_buf, uint16_t len, uint32_t timeout)
{
    if(handle == NULL || handle->bus == NULL || rx_buf == NULL || len == 0) return BSP_SPI_ERROR;
    HAL_StatusTypeDef status = HAL_SPI_Receive(handle->bus->hspi, rx_buf, len, timeout);
    return (status == HAL_OK) ? BSP_SPI_OK : BSP_SPI_ERROR;
}

BSP_SPI_Status_t BSP_SPI_TransmitReceive(BSP_SPI_Handle_t *handle, uint8_t* tx_buf, uint8_t* rx_buf, uint16_t len, uint32_t timeout)
{
    if(handle == NULL || handle->bus == NULL || tx_buf == NULL || rx_buf == NULL || len == 0) return BSP_SPI_ERROR;
    
    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(handle->bus->hspi, tx_buf, rx_buf, len, timeout);
    return (status == HAL_OK) ? BSP_SPI_OK : BSP_SPI_ERROR;
}

BSP_SPI_Status_t BSP_SPI_TransmitReceive_IT(BSP_SPI_Handle_t *handle, uint8_t* tx_buf, uint8_t* rx_buf, uint16_t len)
{
    if(handle == NULL || handle->bus == NULL || tx_buf == NULL || rx_buf == NULL || len == 0) return BSP_SPI_ERROR;
    
    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_IT(handle->bus->hspi, tx_buf, rx_buf, len);
    return (status == HAL_OK) ? BSP_SPI_OK : BSP_SPI_ERROR;
}

BSP_SPI_Status_t BSP_SPI_TransmitReceive_DMA(BSP_SPI_Handle_t *handle, uint8_t* tx_buf, uint8_t* rx_buf, uint16_t len)
{
    if(handle == NULL || handle->bus == NULL || tx_buf == NULL || rx_buf == NULL || len == 0) return BSP_SPI_ERROR;
    
    if(HAL_SPI_GetState(handle->bus->hspi) != HAL_SPI_STATE_READY) return BSP_SPI_BUSY;
    
    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_DMA(handle->bus->hspi, tx_buf, rx_buf, len);
    return (status == HAL_OK) ? BSP_SPI_OK : BSP_SPI_ERROR;
}

BSP_SPI_Status_t BSP_SPI_WaitDone(BSP_SPI_Handle_t *handle, uint32_t timeout)
{
    if(handle == NULL) return BSP_SPI_ERROR;
    
    if(ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(timeout)) == 0) {
        return BSP_SPI_TIMEOUT;
    }
    
    return BSP_SPI_OK;
}

void BSP_SPI_RegisterCallback(BSP_SPI_Handle_t *handle, BSP_SPI_Callback_t callback)
{
    if(handle != NULL) handle->callback = callback;
}

void BSP_SPI_TxRxCpltCallback(BSP_SPI_Handle_t *handle)
{
    if(handle != NULL){
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        
        if(handle->task_to_notify != NULL) {
            vTaskNotifyGiveFromISR(handle->task_to_notify, &xHigherPriorityTaskWoken);
        }

        if(handle->callback != NULL){
            handle->callback(BSP_SPI_EVENT_DONE, &xHigherPriorityTaskWoken);
        }
        
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

void BSP_SPI_ErrorCallback(BSP_SPI_Handle_t *handle)
{
    if(handle != NULL){
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        
        if(handle->task_to_notify != NULL) {
            vTaskNotifyGiveFromISR(handle->task_to_notify, &xHigherPriorityTaskWoken);
        }

        if(handle->callback != NULL){
            handle->callback(BSP_SPI_EVENT_ERROR, &xHigherPriorityTaskWoken);
        }
        
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

void BSP_SPI_Abort(BSP_SPI_Handle_t *handle)
{
    if(handle != NULL && handle->bus != NULL) HAL_SPI_Abort(handle->bus->hspi);
}
