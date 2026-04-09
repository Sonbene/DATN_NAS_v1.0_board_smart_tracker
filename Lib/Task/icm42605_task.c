/**
 * @file    icm42605_task.c
 * @brief   FreeRTOS Task cho ICM-42605 IMU
 * @details - Phase 1 (hiện tại): Polling test đọc sensor data
 *          - Phase 2 (bật sau): Interrupt-driven với EXTI → Task Notify
 *          - Bao gồm weak EXTI callback để bridge ngắt GPIO vào Task
 *
 * @author  DATN_NAS
 * @version 1.0
 * @date    2026-04-09
 */

#include "icm42605_task.h"
#include "icm42605.h"
#include "imu_service.h"
#include "bsp_spi.h"
#include "log.h"
#include "cmsis_os.h"
#include "main.h"

/* ========================================================================================
 * SECTION: Configuration — Chân kết nối phần cứng
 * ======================================================================================== */

/** @brief GPIO CS cho ICM-42605 */
#define IMU_CS_PORT             GPIOB
#define IMU_CS_PIN              GPIO_PIN_7



/* ========================================================================================
 * SECTION: Task Notification Bits
 * ======================================================================================== */

#define IMU_NOTIFY_INT1         (1UL << 0)  /**< Bit 0: INT1 triggered (WOM) */
#define IMU_NOTIFY_INT2         (1UL << 1)  /**< Bit 1: INT2 triggered (FIFO WM) */

/* ========================================================================================
 * SECTION: Private Variables
 * ======================================================================================== */

/** @brief ICM-42605 driver handle */
static ICM42605_Handle_t imu_handle;

/** @brief SPI handle riêng cho IMU (chia sẻ bus với W25Q32) */
static BSP_SPI_Handle_t imu_spi_handle;

/** @brief Task handle cho notification từ ISR */
static TaskHandle_t imu_task_handle = NULL;

/** @brief SPI bus đã khởi tạo trong main.c */
extern BSP_SPI_Bus_t spi1_bus;

/* ========================================================================================
 * SECTION: Private — Event Callback (App-level handler)
 * ======================================================================================== */

/**
 * @brief Callback khi IMU Service phát hiện sự kiện
 *        (WOM chống trộm hoặc Crash tai nạn)
 */
static void prv_IMU_EventHandler(IMU_EventData_t *data, void *user_data)
{
    (void)user_data;

    switch (data->event) {
    case IMU_EVENT_WOM_DETECTED:
        LOG_WARN("[IMU_TASK] === ANTI-THEFT ALERT! Vehicle moved! ===");
        /* TODO: Bật còi, gửi SMS/MQTT, bật GPS tracking... */
        break;

    case IMU_EVENT_CRASH_DETECTED:
        LOG_ERROR("[IMU_TASK] === CRASH DETECTED! Severity=%d ===", data->severity);
        LOG_ERROR("[IMU_TASK]   Peak Accel: %.1f g", data->peak_accel_g);
        LOG_ERROR("[IMU_TASK]   Peak Gyro:  %.0f dps", data->peak_gyro_dps);
        /* TODO: Ghi log GPS, gửi SOS, bật recording... */
        // LOG_ERROR("[IMU_TASK] Dừng mọi hoạt động 5s để test...");
        // osDelay(5000);
        // LOG_INFO("[IMU_TASK] Task IMU đã hoạt động trở lại sau tai nạn!");
        break;

    default:
        break;
    }
}

/* ========================================================================================
 * SECTION: Task Function
 * ======================================================================================== */

/**
 * @brief FreeRTOS Task chính cho IMU
 * @details Phase 1: Polling test → đọc sensor mỗi 500ms và log ra terminal
 *          Phase 2: Uncomment phần interrupt-driven bên dưới
 */
static void StartICM42605Task(void const *argument)
{
    (void)argument;

    LOG_INFO("[IMU_TASK] Task started — Phase 1: Polling test");

    ICM42605_AllData_t data;

    /* ====================================================================
     * PHASE 1: Polling Test — Đọc sensor liên tục để verify hardware
     * ==================================================================== */
    // for (;;) {
    //     ICM42605_Status_t ret = ICM42605_ReadAllData(&imu_handle, &data);

    //     if (ret == ICM42605_OK) {
    //         LOG_INFO("[IMU_TASK] Accel: X=%.2fg Y=%.2fg Z=%.2fg",
    //                  data.accel.x, data.accel.y, data.accel.z);
    //         LOG_INFO("[IMU_TASK] Gyro:  X=%.1f Y=%.1f Z=%.1f dps",
    //                  data.gyro.x, data.gyro.y, data.gyro.z);
    //         LOG_INFO("[IMU_TASK] Temp:  %.1f C", data.temp_degC);
    //         LOG_INFO("[IMU_TASK] ---");
    //     } else {
    //         LOG_ERROR("[IMU_TASK] ReadAllData FAILED (err=%d)", ret);
    //     }

    //     osDelay(500);
    // }

    /* ====================================================================
     * PHASE 2: Interrupt-Driven Mode (uncomment khi Phase 1 OK)
     * ==================================================================== */
     
    LOG_INFO("[IMU_TASK] Switching to interrupt-driven mode...");
    
    /* Dọn dẹp các cờ ngắt ngoại vi (EXTI) có thể vô tình bị kích hoạt trong lúc config sensor */
    __HAL_GPIO_EXTI_CLEAR_IT(IMU_INT1_PIN);
    __HAL_GPIO_EXTI_CLEAR_IT(IMU_INT2_PIN);
    
    /* Dọn sạch các notification có thể bị pending trước khi bắt đầu lắng nghe thực sự */
    ulTaskNotifyTake(pdTRUE, 0);

    /* ====================================================================
     * CHỌN CHẾ ĐỘ TEST (1 = PARKED / Chống trộm, 0 = DRIVING / Tai nạn)
     * ==================================================================== */
    #define TEST_PHASE_3_PARKED 1

    #if TEST_PHASE_3_PARKED
        LOG_INFO("[IMU_TASK] --- BẮT ĐẦU PHASE 3: TEST CHỐNG TRỘM (PARKED MODE) ---");
        IMU_Service_SetMode(IMU_MODE_PARKED);
    #else
        LOG_INFO("[IMU_TASK] --- BẮT ĐẦU PHASE 2: TEST TAI NẠN (DRIVING MODE) ---");
        /* Cấu hình Sensor vào chế độ DRIVING để bắt đầu đẩy data vào FIFO và bắn ngắt */
        IMU_Service_SetMode(IMU_MODE_DRIVING);
    #endif

    for (;;) {
        uint32_t notify_flags = 0;
    
        // Block vô thời hạn chờ notification từ EXTI ISR
        xTaskNotifyWait(0,                  // Không clear bits on entry
                        0xFFFFFFFF,          // Clear tất cả bits on exit
                        &notify_flags,       // Giá trị notification nhận được
                        portMAX_DELAY);      // Đợi vô thời hạn
    
        if (notify_flags & IMU_NOTIFY_INT1) {
            LOG_INFO("[IMU_TASK] INT1 notification received");
            IMU_Service_HandleINT1();
        }
    
        if (notify_flags & IMU_NOTIFY_INT2) {
            LOG_INFO("[IMU_TASK] INT2 notification received");
            IMU_Service_HandleINT2();
        }
    }
}

/* ========================================================================================
 * SECTION: Public API — Init
 * ======================================================================================== */

void ICM42605_Task_Init(void)
{
    LOG_INFO("[IMU_TASK] Initializing...");

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);

    /* 1. Init SPI Handle cho IMU (chia sẻ bus với W25Q32) */
    BSP_SPI_Handle_Init(&imu_spi_handle, &spi1_bus);
    LOG_INFO("[IMU_TASK] SPI Handle initialized (shared bus)");

    /* 2. Init ICM-42605 Driver */
    ICM42605_Status_t ret = ICM42605_Init(&imu_handle, &imu_spi_handle, IMU_CS_PORT, IMU_CS_PIN);
    if (ret != ICM42605_OK) {
        LOG_ERROR("[IMU_TASK] ICM42605 Init FAILED (err=%d)! Task will NOT start.", ret);
        return; /* Không tạo task nếu init fail */
    }

    /* 3. Init IMU Service (mặc định mode PARKED) */
    IMU_Service_Init(&imu_handle, prv_IMU_EventHandler, NULL);
    LOG_INFO("[IMU_TASK] IMU Service initialized");

    /* 4. Tạo FreeRTOS Task */
    osThreadDef(imuTask, StartICM42605Task, osPriorityAboveNormal, 0, 512);
    imu_task_handle = osThreadCreate(osThread(imuTask), NULL);

    if (imu_task_handle == NULL) {
        LOG_ERROR("[IMU_TASK] Failed to create task!");
    } else {
        LOG_INFO("[IMU_TASK] Task created (priority: AboveNormal, stack: 512 words)");
    }
}

/* ========================================================================================
 * SECTION: Public API — ISR Bridge (gọi từ EXTI callback)
 * ======================================================================================== */

void ICM42605_Task_NotifyINT1FromISR(void)
{
    if (imu_task_handle == NULL) return;

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xTaskNotifyFromISR(imu_task_handle, IMU_NOTIFY_INT1, eSetBits, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void ICM42605_Task_NotifyINT2FromISR(void)
{
    if (imu_task_handle == NULL) return;

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xTaskNotifyFromISR(imu_task_handle, IMU_NOTIFY_INT2, eSetBits, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/* ========================================================================================
 * SECTION: Weak EXTI Callback — Bridge GPIO Interrupt → Task Notification
 * ======================================================================================== */

/**
 * @brief   HAL GPIO EXTI Callback (weak function override)
 * @details Hàm này được gọi bởi HAL khi có ngắt EXTI trên bất kỳ chân nào.
 *          Ta kiểm tra GPIO_Pin để xác định INT1 hay INT2 và notify task tương ứng.
 *
 * @note    Đây là override của __weak function trong stm32l4xx_hal_gpio.c.
 *          Nếu bạn cần xử lý thêm EXTI cho peripheral khác,
 *          hãy di chuyển hàm này sang main.c và gọi cả hai handler.
 *
 * @param   GPIO_Pin Pin đã trigger ngắt (GPIO_PIN_0, GPIO_PIN_9, ...)
 */
