#include "bsp_uart.h"
#include <string.h>

BSP_UART_Status_t BSP_UART_Init(BSP_UART_Handle_t *handle, UART_HandleTypeDef *huart)
{
    if(handle == NULL || huart == NULL) return BSP_UART_ERROR;

    handle->huart = huart;
    handle->tx_mutex = xSemaphoreCreateMutex();
    handle->rx_mutex = xSemaphoreCreateMutex();
    
    configASSERT(handle->tx_mutex != NULL);
    configASSERT(handle->rx_mutex != NULL);
    
    handle->tx_task_to_notify = NULL;
    handle->rx_task_to_notify = NULL;
    handle->callback = NULL;

    return BSP_UART_OK;
}

BSP_UART_Status_t BSP_UART_LockTx(BSP_UART_Handle_t *handle, uint32_t timeout)
{
    if(handle == NULL) return BSP_UART_ERROR;
    
    if(xSemaphoreTake(handle->tx_mutex, pdMS_TO_TICKS(timeout)) != pdTRUE){
        return BSP_UART_BUSY;
    }
    
    /* Ghi nhận task hiện tại đang lấy quyền TX (để notify khi dùng ngắt/DMA) */
    handle->tx_task_to_notify = xTaskGetCurrentTaskHandle();
    
    return BSP_UART_OK;
}

void BSP_UART_UnlockTx(BSP_UART_Handle_t *handle)
{
    if(handle == NULL) return;
    
    handle->tx_task_to_notify = NULL;
    xSemaphoreGive(handle->tx_mutex);
}

BSP_UART_Status_t BSP_UART_LockRx(BSP_UART_Handle_t *handle, uint32_t timeout)
{
    if(handle == NULL) return BSP_UART_ERROR;
    
    if(xSemaphoreTake(handle->rx_mutex, pdMS_TO_TICKS(timeout)) != pdTRUE){
        return BSP_UART_BUSY;
    }
    
    /* Ghi nhận task hiện tại đang lấy quyền RX (để notify khi dùng ngắt/DMA) */
    handle->rx_task_to_notify = xTaskGetCurrentTaskHandle();
    
    return BSP_UART_OK;
}

void BSP_UART_UnlockRx(BSP_UART_Handle_t *handle)
{
    if(handle == NULL) return;
    
    handle->rx_task_to_notify = NULL;
    xSemaphoreGive(handle->rx_mutex);
}

BSP_UART_Status_t BSP_UART_Transmit(BSP_UART_Handle_t *handle, uint8_t* tx_buf, uint16_t len, uint32_t timeout)
{
    if(handle == NULL || tx_buf == NULL || len == 0) return BSP_UART_ERROR;
    
    HAL_StatusTypeDef status = HAL_UART_Transmit(handle->huart, tx_buf, len, timeout);
    return (status == HAL_OK) ? BSP_UART_OK : BSP_UART_ERROR;
}

BSP_UART_Status_t BSP_UART_Receive(BSP_UART_Handle_t *handle, uint8_t* rx_buf, uint16_t len, uint32_t timeout)
{
    if(handle == NULL || rx_buf == NULL || len == 0) return BSP_UART_ERROR;
    
    HAL_StatusTypeDef status = HAL_UART_Receive(handle->huart, rx_buf, len, timeout);
    return (status == HAL_OK) ? BSP_UART_OK : BSP_UART_ERROR;
}

BSP_UART_Status_t BSP_UART_Transmit_IT(BSP_UART_Handle_t *handle, uint8_t* tx_buf, uint16_t len)
{
    if(handle == NULL || tx_buf == NULL || len == 0) return BSP_UART_ERROR;
    
    HAL_StatusTypeDef status = HAL_UART_Transmit_IT(handle->huart, tx_buf, len);
    return (status == HAL_OK) ? BSP_UART_OK : BSP_UART_ERROR;
}

BSP_UART_Status_t BSP_UART_Receive_IT(BSP_UART_Handle_t *handle, uint8_t* rx_buf, uint16_t len)
{
    if(handle == NULL || rx_buf == NULL || len == 0) return BSP_UART_ERROR;
    
    HAL_StatusTypeDef status = HAL_UART_Receive_IT(handle->huart, rx_buf, len);
    return (status == HAL_OK) ? BSP_UART_OK : BSP_UART_ERROR;
}

BSP_UART_Status_t BSP_UART_Transmit_DMA(BSP_UART_Handle_t *handle, uint8_t* tx_buf, uint16_t len)
{
    if(handle == NULL || tx_buf == NULL || len == 0) return BSP_UART_ERROR;
    
    if(handle->huart->gState != HAL_UART_STATE_READY) return BSP_UART_BUSY;
    
    HAL_StatusTypeDef status = HAL_UART_Transmit_DMA(handle->huart, tx_buf, len);
    return (status == HAL_OK) ? BSP_UART_OK : BSP_UART_ERROR;
}

BSP_UART_Status_t BSP_UART_Receive_DMA(BSP_UART_Handle_t *handle, uint8_t* rx_buf, uint16_t len)
{
    if(handle == NULL || rx_buf == NULL || len == 0) return BSP_UART_ERROR;
    
    if(handle->huart->RxState != HAL_UART_STATE_READY) return BSP_UART_BUSY;
    
    HAL_StatusTypeDef status = HAL_UART_Receive_DMA(handle->huart, rx_buf, len);
    return (status == HAL_OK) ? BSP_UART_OK : BSP_UART_ERROR;
}

BSP_UART_Status_t BSP_UART_WaitTxDone(BSP_UART_Handle_t *handle, uint32_t timeout)
{
    if(handle == NULL) return BSP_UART_ERROR;
    
    if(ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(timeout)) == 0) {
        return BSP_UART_TIMEOUT;
    }
    
    return BSP_UART_OK;
}

BSP_UART_Status_t BSP_UART_WaitRxDone(BSP_UART_Handle_t *handle, uint32_t timeout)
{
    if(handle == NULL) return BSP_UART_ERROR;
    
    if(ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(timeout)) == 0) {
        return BSP_UART_TIMEOUT;
    }
    
    return BSP_UART_OK;
}

void BSP_UART_RegisterCallback(BSP_UART_Handle_t *handle, BSP_UART_Callback_t callback)
{
    if(handle != NULL) {
        handle->callback = callback;
    }
}

void BSP_UART_TxCpltCallback(BSP_UART_Handle_t *handle)
{
    if(handle != NULL){
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        
        if(handle->tx_task_to_notify != NULL) {
            vTaskNotifyGiveFromISR(handle->tx_task_to_notify, &xHigherPriorityTaskWoken);
        }

        if(handle->callback != NULL){
            handle->callback(BSP_UART_EVENT_TX_DONE, 0, &xHigherPriorityTaskWoken);
        }
        
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

void BSP_UART_RxCpltCallback(BSP_UART_Handle_t *handle, uint16_t size)
{
    if(handle != NULL){
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        
        if(handle->rx_task_to_notify != NULL) {
            vTaskNotifyGiveFromISR(handle->rx_task_to_notify, &xHigherPriorityTaskWoken);
        }

        if(handle->callback != NULL){
            handle->callback(BSP_UART_EVENT_RX_DONE, size, &xHigherPriorityTaskWoken);
        }
        
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

void BSP_UART_ErrorCallback(BSP_UART_Handle_t *handle)
{
    if(handle != NULL){
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        
        /* Notify any task waiting on TX or RX */
        if(handle->tx_task_to_notify != NULL) {
            vTaskNotifyGiveFromISR(handle->tx_task_to_notify, &xHigherPriorityTaskWoken);
        }
        if(handle->rx_task_to_notify != NULL) {
            vTaskNotifyGiveFromISR(handle->rx_task_to_notify, &xHigherPriorityTaskWoken);
        }

        if(handle->callback != NULL){
            handle->callback(BSP_UART_EVENT_ERROR, 0, &xHigherPriorityTaskWoken);
        }
        
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

void BSP_UART_RxEventCallback(BSP_UART_Handle_t *handle, uint16_t size)
{
    if(handle != NULL){
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        
        if(handle->rx_task_to_notify != NULL) {
            vTaskNotifyGiveFromISR(handle->rx_task_to_notify, &xHigherPriorityTaskWoken);
        }

        if(handle->callback != NULL){
            handle->callback(BSP_UART_EVENT_IDLE, size, &xHigherPriorityTaskWoken);
        }
        
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

void BSP_UART_Abort(BSP_UART_Handle_t *handle)
{
    if(handle != NULL && handle->huart != NULL) {
        HAL_UART_Abort(handle->huart);
    }
}

void BSP_UART_AbortReceive(BSP_UART_Handle_t *handle)
{
    if(handle != NULL && handle->huart != NULL) {
        HAL_UART_AbortReceive(handle->huart);
    }
}

void BSP_UART_AbortTransmit(BSP_UART_Handle_t *handle)
{
    if(handle != NULL && handle->huart != NULL) {
        HAL_UART_AbortTransmit(handle->huart);
    }
}
