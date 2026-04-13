#include "w25q32_task.h"
#include "w25q32.h"
#include "bsp_spi.h"
#include "log.h"
#include "cmsis_os.h"
#include "storage_manager.h"
#include <string.h>

/* Physical Resources defined in main.c */
extern SPI_HandleTypeDef hspi1;

#include "system_service.h"

#define TRACKER_LOG_MAGIC 0x534F4E42  /* "SONB" */

/* Mail Queue nhận yêu cầu ghi Log */
osMailQDef(log_q, 8, TrackerLog_t);
static osMailQId log_q_id = NULL;

static Storage_Config_t tracker_storage_cfg = {
    .start_addr = 0x1000,       /* Start from Sector 1 */
    .end_addr = 0x100000,       /* Use 1MB for journey logs */
    .tracking_addr = 0x0000,    /* Sector 0 for tracking index */
    .obj_size = sizeof(TrackerLog_t),
    .magic_word = TRACKER_LOG_MAGIC,
    .n_step = 10
};

static Storage_Context_t sensor_ctx;

/* BSP Resources */
extern BSP_SPI_Bus_t spi1_bus;      /* Defined in main.c */
static BSP_SPI_Handle_t flash_spi_handle;
static W25Q_Handle_t flash_handle;

/* Task Resources */
osThreadId w25q32TaskHandle;
void StartW25Q32Task(void const * argument);

void W25Q32_Task_Init(void)
{
    /* 1. Init CS Pin */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);

    /* 2. Init SPI Handle */
    BSP_SPI_Handle_Init(&flash_spi_handle, &spi1_bus);

    /* 3. Tạo Mail Queue */
    log_q_id = osMailCreate(osMailQ(log_q), NULL);

    /* 4. Tạo Task */
    osThreadDef(w25q32Task, StartW25Q32Task, osPriorityNormal, 0, 512);
    w25q32TaskHandle = osThreadCreate(osThread(w25q32Task), NULL);
}

void W25Q32_Task_Log(TrackerLog_t *log) {
    if (log_q_id == NULL || log == NULL) return;
    
    TrackerLog_t *mail = (TrackerLog_t *)osMailAlloc(log_q_id, 0);
    if (mail != NULL) {
        memcpy(mail, log, sizeof(TrackerLog_t));
        osMailPut(log_q_id, mail);
    }
}

void StartW25Q32Task(void const * argument)
{
    LOG_INFO("--- Storage Manager Test Started ---");

    /* 1. Init Flash Driver */
    if (W25Q_Init(&flash_handle, &flash_spi_handle, GPIOB, GPIO_PIN_6) != W25Q_OK) {
        LOG_ERROR("W25Q32 Init Failed!");
        for(;;) osDelay(1000);
    }

    /* 2. Init Storage Service */
    Storage_Init(&flash_handle, &tracker_storage_cfg, &sensor_ctx);

    /* 3. Thực hiện Recovery */
    Storage_Recover(&flash_handle, &tracker_storage_cfg, &sensor_ctx);

    LOG_INFO("[FLASH] Storage ready. Current logs: %d", sensor_ctx.current_index);

    for(;;) {
        /* Chờ yêu cầu ghi log từ Queue */
        osEvent evt = osMailGet(log_q_id, osWaitForever);
        
        if (evt.status == osEventMail) {
            TrackerLog_t *log_data = (TrackerLog_t *)evt.value.p;
            
            Storage_Status_t status = Storage_Append(&flash_handle, &tracker_storage_cfg, &sensor_ctx, log_data);
            
            if (status == STORAGE_OK) {
                LOG_INFO("[FLASH] Log #%d saved speed=%.1f", sensor_ctx.current_index - 1, log_data->speed);
            } else if (status == STORAGE_FULL) {
                LOG_WARN("[FLASH] Storage FULL!");
            }
            
            osMailFree(log_q_id, log_data);
        }
    }
}
