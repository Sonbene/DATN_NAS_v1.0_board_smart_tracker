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

/* Mail Queue nhận yêu cầu từ các Task khác */
osMailQDef(flash_q, 10, W25Q_Msg_t);
static osMailQId flash_q_id = NULL;

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
    flash_q_id = osMailCreate(osMailQ(flash_q), NULL);

    /* 4. Tạo Task */
    osThreadDef(w25q32Task, StartW25Q32Task, osPriorityNormal, 0, 512);
    w25q32TaskHandle = osThreadCreate(osThread(w25q32Task), NULL);
}

void W25Q32_Task_Log(TrackerLog_t *log) {
    if (flash_q_id == NULL || log == NULL) return;
    
    W25Q_Msg_t *msg = (W25Q_Msg_t *)osMailAlloc(flash_q_id, 0);
    if (msg != NULL) {
        msg->cmd = W25Q_CMD_LOG;
        memcpy(&(msg->log), log, sizeof(TrackerLog_t));
        msg->sem = NULL; // Không cần đợi
        osMailPut(flash_q_id, msg);
    }
}

static bool prv_Flash_SyncRequest(W25Q_Cmd_t cmd) {
    if (flash_q_id == NULL) return false;

    osSemaphoreDef(syncSem);
    osSemaphoreId sem = osSemaphoreCreate(osSemaphore(syncSem), 1);
    osSemaphoreWait(sem, 0); // Đưa về 0

    W25Q_Msg_t *msg = (W25Q_Msg_t *)osMailAlloc(flash_q_id, 100);
    if (msg == NULL) {
        osSemaphoreDelete(sem);
        return false;
    }

    msg->cmd = cmd;
    msg->sem = sem;
    
    if (osMailPut(flash_q_id, msg) != osOK) {
        osMailFree(flash_q_id, msg);
        osSemaphoreDelete(sem);
        return false;
    }

    /* Chờ task Flash xử lý xong (Max 3s cho Erase-Write) */
    bool success = (osSemaphoreWait(sem, 3000) == osOK);
    osSemaphoreDelete(sem);
    return success;
}

bool W25Q32_Task_SaveConfig(void) {
    return prv_Flash_SyncRequest(W25Q_CMD_SAVE_CONFIG);
}

bool W25Q32_Task_LoadConfig(void) {
    return prv_Flash_SyncRequest(W25Q_CMD_LOAD_CONFIG);
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
        /* Chờ yêu cầu từ Queue */
        osEvent evt = osMailGet(flash_q_id, osWaitForever);
        
        if (evt.status == osEventMail) {
            W25Q_Msg_t *msg = (W25Q_Msg_t *)evt.value.p;
            
            switch (msg->cmd) {
                case W25Q_CMD_LOG: {
                    Storage_Append(&flash_handle, &tracker_storage_cfg, &sensor_ctx, &(msg->log));
                    LOG_INFO("[FLASH] Log #%d saved", sensor_ctx.current_index - 1);
                    break;
                }
                
                case W25Q_CMD_SAVE_CONFIG: {
                    SystemConfig_t cfg;
                    System_Service_GetConfig(&cfg);
                    cfg.magic = CONFIG_FLASH_MAGIC;
                    
                    LOG_INFO("[FLASH] Sector %d Erasing...", CONFIG_FLASH_SECTOR);
                    W25Q_EraseSector(&flash_handle, CONFIG_FLASH_SECTOR * W25Q_SECTOR_SIZE);
                    LOG_INFO("[FLASH] Sector %d Writing...", CONFIG_FLASH_SECTOR);
                    W25Q_Write(&flash_handle, CONFIG_FLASH_SECTOR * W25Q_SECTOR_SIZE, (uint8_t*)&cfg, sizeof(SystemConfig_t));
                    LOG_INFO("[FLASH] Config saved.");
                    break;
                }
                
                case W25Q_CMD_LOAD_CONFIG: {
                    SystemConfig_t temp_cfg;
                    W25Q_Read(&flash_handle, CONFIG_FLASH_SECTOR * W25Q_SECTOR_SIZE, (uint8_t*)&temp_cfg, sizeof(SystemConfig_t));
                    
                    if (temp_cfg.magic == CONFIG_FLASH_MAGIC) {
                        System_Service_UpdateConfig(&temp_cfg);
                        LOG_INFO("[FLASH] Config loaded from Sector %d.", CONFIG_FLASH_SECTOR);
                    } else {
                        LOG_WARN("[FLASH] No valid config in Sector %d (Magic: 0x%04X)", CONFIG_FLASH_SECTOR, temp_cfg.magic);
                    }
                    break;
                }
            }
            
            /* Nếu là lệnh đồng bộ, báo cho caller biết đã xong */
            if (msg->sem != NULL) {
                osSemaphoreRelease(msg->sem);
            }
            
            osMailFree(flash_q_id, msg);
        }
    }
}
