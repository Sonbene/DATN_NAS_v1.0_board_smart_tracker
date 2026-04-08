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
    .end_addr = 0x10000,        /* Use 60KB for demo */
    .tracking_addr = 0x0000,    /* Sector 0 for tracking */
    .obj_size = sizeof(Sensor_Data_t),
    .magic_word = SENSOR_MAGIC,
    .n_step = 10                /* Mark every 10 records */
};

static Storage_Context_t sensor_ctx;

/* BSP Resources */
static BSP_SPI_Bus_t spi1_bus;
static BSP_SPI_Handle_t flash_spi_handle;
static W25Q_Handle_t flash_handle;

/* Task Resources */
osThreadId w25q32TaskHandle;
void StartW25Q32Task(void const * argument);

void W25Q32_Task_Init(void)
{
    /* Ensure all CS pins are HIGH to avoid bus contention */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6 | GPIO_PIN_7, GPIO_PIN_SET);

    /* Initialize BSP SPI Bus for SPI1 */
    BSP_SPI_Bus_Init(&spi1_bus, &hspi1);
    
    /* Initialize Handle for Flash on SPI1 */
    BSP_SPI_Handle_Init(&flash_spi_handle, &spi1_bus);

    osThreadDef(w25q32Task, StartW25Q32Task, osPriorityNormal, 0, 384);
    w25q32TaskHandle = osThreadCreate(osThread(w25q32Task), NULL);
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
    Storage_Init(&flash_handle, &sensor_storage_cfg, &sensor_ctx);

    /* 3. Perform Recovery (Find last record using Binary Search) */
    Storage_Recover(&flash_handle, &sensor_storage_cfg, &sensor_ctx);

    /* 4. Demo Append (Simulate some sensor data) */
    Sensor_Data_t sample;
    sample.magic = SENSOR_MAGIC;
    sample.timestamp = osKernelSysTick();
    sample.temperature = 25.5f;
    sample.humidity = 60.0f;

    LOG_INFO("Appending 12 records to see Tracking Sector update...");
    for(int i = 0; i < 12; i++) {
        sample.timestamp = osKernelSysTick();
        sample.temperature += 0.1f;
        Storage_Append(&flash_handle, &sensor_storage_cfg, &sensor_ctx, &sample);
        osDelay(10);
    }

    LOG_INFO("New Current Index: %d", sensor_ctx.current_index);

    /* 5. Read back last written record */
    Sensor_Data_t read_back;
    if (sensor_ctx.current_index > 0) {
        Storage_Read(&flash_handle, &sensor_storage_cfg, sensor_ctx.current_index - 1, &read_back);
        LOG_INFO("Last Record: Time=%d, Temp=%.1f", read_back.timestamp, read_back.temperature);
    }

    LOG_INFO("Storage Test Complete. Try resetting board to verify Recovery.");

    for(;;) {
        osDelay(5000);
    }
}
