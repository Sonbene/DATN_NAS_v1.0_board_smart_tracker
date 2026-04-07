#include "bsp_spi.h"
#include <string.h>

static SPI_HandleTypeDef *spi_handle;
static SemaphoreHandle_t spi_mutex;
static BSP_SPI_Callback_t spi_callback;

void BSP_SPI_Init(SPI_HandleTypeDef *hspi)
{
    spi_handle = hspi;
    spi_mutex = xSemaphoreCreateMutex();
    configASSERT(spi_mutex != NULL);
    spi_callback = NULL;
}

void BSP_SPI_Select(GPIO_TypeDef *cs_port, uint16_t cs_pin)
{
    HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_RESET);
}

void BSP_SPI_Deselect(GPIO_TypeDef *cs_port, uint16_t cs_pin)
{
    HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_SET);
}

BSP_SPI_Status_t BSP_SPI_TransmitReceive(uint8_t* tx_buf, uint8_t* rx_buf, uint16_t len, uint32_t spi_timeout, uint32_t mutex_timeout)
{
    if(tx_buf == NULL || rx_buf == NULL || len == 0){
        return BSP_SPI_ERROR;
    }

    if(xSemaphoreTake(spi_mutex, pdMS_TO_TICKS(mutex_timeout)) != pdTRUE){
        return BSP_SPI_BUSY;
    }
    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(spi_handle, tx_buf, rx_buf, len, spi_timeout);
    xSemaphoreGive(spi_mutex);
    return (status == HAL_OK) ? BSP_SPI_OK : BSP_SPI_ERROR;
}

BSP_SPI_Status_t BSP_SPI_TransmitReceive_IT(uint8_t* tx_buf, uint8_t* rx_buf, uint16_t len, uint32_t mutex_timeout)
{
    if(tx_buf == NULL || rx_buf == NULL || len == 0){
        return BSP_SPI_ERROR;
    }

    if(xSemaphoreTake(spi_mutex, pdMS_TO_TICKS(mutex_timeout)) != pdTRUE){
        return BSP_SPI_BUSY;
    }
    
    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_IT(spi_handle, tx_buf, rx_buf, len);
    if(status == HAL_OK){
        return BSP_SPI_OK;
    }
    else{
        xSemaphoreGive(spi_mutex);
        return BSP_SPI_ERROR;
    }
}

BSP_SPI_Status_t BSP_SPI_TransmitReceive_DMA(uint8_t* tx_buf, uint8_t* rx_buf, uint16_t len, uint32_t mutex_timeout)
{
    if(tx_buf == NULL || rx_buf == NULL || len == 0){
        return BSP_SPI_ERROR;
    }

    if(xSemaphoreTake(spi_mutex, pdMS_TO_TICKS(mutex_timeout)) != pdTRUE){
        return BSP_SPI_BUSY;
    }

    if(HAL_SPI_GetState(spi_handle) != HAL_SPI_STATE_READY){
        return BSP_SPI_BUSY;
    }
    
    HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_DMA(spi_handle, tx_buf, rx_buf, len);
    if(status == HAL_OK){
        return BSP_SPI_OK;
    }
    else{
        xSemaphoreGive(spi_mutex);
        return BSP_SPI_ERROR;
    }
}

void BSP_SPI_RegisterCallback(BSP_SPI_Callback_t callback)
{
    spi_callback = callback;
}

void BSP_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if(hspi == spi_handle){
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;

        xSemaphoreGiveFromISR(spi_mutex, &xHigherPriorityTaskWoken);

        if(spi_callback != NULL){
            spi_callback(BSP_SPI_EVENT_DONE, &xHigherPriorityTaskWoken);
        }

        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

void BSP_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
    if(hspi == spi_handle){
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;

        if(spi_callback != NULL){
            spi_callback(BSP_SPI_EVENT_ERROR, &xHigherPriorityTaskWoken);
        }

        xSemaphoreGiveFromISR(spi_mutex, &xHigherPriorityTaskWoken);

        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

void BSP_SPI_Abort(void)
{
    HAL_SPI_Abort(spi_handle);
    xSemaphoreGive(spi_mutex);
}
