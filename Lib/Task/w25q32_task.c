#include "w25q32_task.h"
#include "w25q32.h"
#include "bsp_spi.h"
#include "log.h"
#include "cmsis_os.h"
#include "storage_manager.h"
#include <string.h>

/* Physical Resources defined in main.c */
extern SPI_HandleTypeDef hspi1;

/* Log Struct definition */
typedef struct {
    uint32_t magic;
    uint32_t timestamp;
    float temperature;
    float humidity;
} Sensor_Data_t;

#define SENSOR_MAGIC 0xCAFEBABE

/* Storage Configs */
static Storage_Config_t sensor_storage_cfg = {
    .start_addr = 0x1000,       /* Start from Sector 1 */
    .end_addr = 0x11000,        /* Use 60KB for demo */
    .tracking_addr = 0x0000,    /* Sector 0 for tracking */
    .obj_size = sizeof(Sensor_Data_t),
    .magic_word = SENSOR_MAGIC,
    .n_step = 10                /* Mark every 10 records */
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
    /* Ensure all CS pins are HIGH to avoid bus contention */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);

    /* Initialize Handle for Flash on SPI1 (bus đã init trong main.c) */
    BSP_SPI_Handle_Init(&flash_spi_handle, &spi1_bus);

    osThreadDef(w25q32Task, StartW25Q32Task, osPriorityNormal, 0, 384);
    w25q32TaskHandle = osThreadCreate(osThread(w25q32Task), NULL);
}

void StartW25Q32Task(void const * argument)
{
    // LOG_INFO("--- Storage Manager Test Started ---");

    // /* 1. Init Flash Driver */
    // if (W25Q_Init(&flash_handle, &flash_spi_handle, GPIOB, GPIO_PIN_6) != W25Q_OK) {
    //     LOG_ERROR("W25Q32 Init Failed!");
    //     for(;;) osDelay(1000);
    // }

    // /* 2. Init Storage Service */
    // Storage_Init(&flash_handle, &sensor_storage_cfg, &sensor_ctx);

    // /* 3. Perform Recovery (Find last record using Binary Search) */
    // Storage_Recover(&flash_handle, &sensor_storage_cfg, &sensor_ctx);

    // /* 4. Continuous Logging (Simulate sensor data every 5s) */
    // Sensor_Data_t sample;
    // sample.magic = SENSOR_MAGIC;
    // sample.temperature = 25.5f;
    // sample.humidity = 60.0f;

    // LOG_INFO("Starting continuous logging (every 5s)...");


    for(;;) {

        //sample.timestamp = osKernelSysTick();
        //sample.temperature += 0.1f; /* Dummy variation */
        
        //Storage_Status_t status = Storage_Append(&flash_handle, &sensor_storage_cfg, &sensor_ctx, &sample);
        
        // if (status == STORAGE_OK) {
        //     LOG_INFO("Record #%d saved (Time: %d, Temp: %.1f)", sensor_ctx.current_index - 1, sample.timestamp, sample.temperature);
        // } else if (status == STORAGE_FULL) {
        //     LOG_WARN("Storage is FULL!");
        // } else {
        //     LOG_ERROR("Failed to write to storage!");
        // }
        
        // LOG_INFO("--- Bắt đầu đọc toàn bộ log (%d bản ghi) ---", sensor_ctx.current_index);
        // for (uint32_t i = 0; i < sensor_ctx.current_index; i++) {
        //     Sensor_Data_t temp_data;
        //     if (Storage_Read(&flash_handle, &sensor_storage_cfg, i, &temp_data) == STORAGE_OK) {
        //         LOG_INFO("[%d] Time: %d | Temp: %.1f | Hum: %.1f", 
        //                 i, temp_data.timestamp, temp_data.temperature, temp_data.humidity);
        //     }
        // }

        osDelay(1000);
    }
}
