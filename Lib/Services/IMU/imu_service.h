/**
 * @file    imu_service.h
 * @brief   IMU Service Layer — Quản lý chế độ hoạt động và phát hiện tai nạn
 * @details Hai chế độ chính:
 *          - PARKED: Chống trộm bằng Wake-on-Motion (INT1)
 *          - DRIVING: Phát hiện tai nạn bằng Accel+Gyro qua FIFO (INT2)
 *
 * @author  DATN_NAS
 * @version 1.0
 * @date    2026-04-09
 */

#ifndef __IMU_SERVICE_H__
#define __IMU_SERVICE_H__

#include "icm42605.h"
#include <stdint.h>
#include <stdbool.h>

/* ========================================================================================
 * SECTION: Configuration Constants
 * ======================================================================================== */

/** @defgroup CrashThresholds Crash Detection Thresholds */
/** @{ */
#define IMU_CRASH_ACCEL_TRIGGER_G       2.0f    /**< [TEST] Gia tốc trigger (2.0g) */
#define IMU_CRASH_ACCEL_SEVERE_G        4.0f    /**< [TEST] Gia tốc severe (4.0g) */
#define IMU_CRASH_ACCEL_MAX_G           6.0f    /**< [TEST] Gia tốc vỡ nát (6.0g) */
#define IMU_CRASH_GYRO_CONFIRM_DPS      150.0f  /**< [TEST] Gyro xoay xác nhận crash (150dps) */
#define IMU_CRASH_GYRO_MEDIUM_DPS       250.0f  /**< [TEST] Gyro xoay medium (250dps) */
#define IMU_CRASH_GYRO_SEVERE_DPS       350.0f  /**< [TEST] Gyro xoay severe (350dps) */
/** @} */

/** @defgroup CrashWindow Crash Detection Window */
/** @{ */
#define IMU_CRASH_WINDOW_SAMPLES        10      /**< Số samples trong cửa sổ xác nhận (50ms @200Hz) */
#define IMU_CRASH_DEBOUNCE_MS           3000    /**< Debounce: không trigger lại trong 3 giây */
/** @} */

/** @defgroup FilterConfig Moving Average Filter */
/** @{ */
#define IMU_FILTER_SIZE                 4       /**< Kích thước bộ lọc Moving Average */
/** @} */

/** @defgroup FIFOConfig FIFO Configuration */
/** @{ */
#define IMU_FIFO_WATERMARK              20      /**< Số records FIFO watermark */
#define IMU_FIFO_RECORD_SIZE            16      /**< Bytes per FIFO record (header+accel+gyro+temp+ts) */
#define IMU_FIFO_BUFFER_SIZE            (IMU_FIFO_WATERMARK * IMU_FIFO_RECORD_SIZE)  /**< 320 bytes */
/** @} */

/** @defgroup WOMConfig Wake-on-Motion Config */
/** @{ */
#define IMU_WOM_THRESHOLD_LSB           15     /**< WOM threshold ~48mg (@±4g, 4mg/LSB) - More sensitive */
/** @} */

/* ========================================================================================
 * SECTION: Enumerations
 * ======================================================================================== */

/**
 * @brief Trạng thái trả về của Service
 */
typedef enum {
    IMU_SVC_OK = 0,
    IMU_SVC_ERROR,
    IMU_SVC_BUSY
} IMU_Status_t;

/**
 * @brief Chế độ hoạt động IMU
 */
typedef enum {
    IMU_MODE_PARKED = 0,    /**< Xe đứng yên — WOM chống trộm */
    IMU_MODE_DRIVING        /**< Xe chạy — FIFO crash detection */
} IMU_Mode_t;

/**
 * @brief Loại sự kiện IMU
 */
typedef enum {
    IMU_EVENT_NONE = 0,
    IMU_EVENT_WOM_DETECTED,     /**< Rung lắc bất thường (chống trộm) */
    IMU_EVENT_CRASH_DETECTED    /**< Va chạm (tai nạn) */
} IMU_Event_t;

/**
 * @brief Mức độ nghiêm trọng crash
 */
typedef enum {
    CRASH_SEVERITY_NONE = 0,
    CRASH_SEVERITY_LIGHT,       /**< 5g < a < 8g, 400dps < gyro < 600dps */
    CRASH_SEVERITY_MEDIUM,      /**< 8g < a < 12g, hoặc gyro 600-800dps */
    CRASH_SEVERITY_SEVERE       /**< a > 12g hoặc gyro > 800dps */
} CrashSeverity_t;

/* ========================================================================================
 * SECTION: Data Structures
 * ======================================================================================== */

/**
 * @brief Thông tin chi tiết sự kiện IMU (truyền qua callback)
 */
typedef struct {
    IMU_Event_t         event;          /**< Loại sự kiện */
    CrashSeverity_t     severity;       /**< Mức nghiêm trọng (chỉ khi CRASH) */
    float               peak_accel_g;   /**< Gia tốc đỉnh (g) */
    float               peak_gyro_dps;  /**< Gyro đỉnh (dps) */
} IMU_EventData_t;

/**
 * @brief Callback thông báo sự kiện IMU lên tầng App
 */
typedef void (*IMU_EventCallback_t)(IMU_EventData_t *data, void *user_data);

/* ========================================================================================
 * SECTION: Public API
 * ======================================================================================== */

/**
 * @brief   Khởi tạo IMU Service
 * @details Đăng ký với driver, cấu hình mặc định PARKED mode
 * @param   imu Pointer tới ICM42605 handle đã init
 * @param   callback Hàm callback báo sự kiện lên App
 * @param   user_data Tham số tuỳ chọn truyền vào callback
 * @return  IMU_SVC_OK nếu thành công
 */
IMU_Status_t IMU_Service_Init(ICM42605_Handle_t *imu,
                               IMU_EventCallback_t callback,
                               void *user_data);

/**
 * @brief   Chuyển chế độ hoạt động
 * @details Cấu hình lại toàn bộ sensor parameters + interrupt routing
 * @param   mode PARKED hoặc DRIVING
 * @return  IMU_SVC_OK nếu thành công
 */
IMU_Status_t IMU_Service_SetMode(IMU_Mode_t mode);

/**
 * @brief   Lấy chế độ hoạt động hiện tại
 * @return  IMU_MODE_PARKED hoặc IMU_MODE_DRIVING
 */
IMU_Mode_t IMU_Service_GetMode(void);

/**
 * @brief   Xử lý ngắt INT1 (WOM / Anti-theft)
 * @details Gọi từ Task context khi nhận notification từ EXTI ISR.
 *          Đọc INT_STATUS2 để xác nhận WOM, gọi callback nếu có.
 */
void IMU_Service_HandleINT1(void);

/**
 * @brief   Xử lý ngắt INT2 (FIFO Watermark / Crash Detection)
 * @details Gọi từ Task context. DMA đọc FIFO → parse → crash algorithm.
 */
void IMU_Service_HandleINT2(void);

/**
 * @brief   Lấy dữ liệu sensor mới nhất (polling, test only)
 * @param   data Output: sensor data
 * @return  IMU_SVC_OK nếu thành công
 */
IMU_Status_t IMU_Service_ReadAll(ICM42605_AllData_t *data);

#endif /* __IMU_SERVICE_H__ */
