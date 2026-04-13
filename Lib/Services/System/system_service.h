#ifndef __SYSTEM_SERVICE_H__
#define __SYSTEM_SERVICE_H__

#include "main.h"
#include "cmsis_os.h"
#include <stdbool.h>
#include <stdio.h>

/**
 * @brief Các trạng thái vận hành chính của hệ thống
 */
typedef enum {
    SYS_MODE_INIT = 0,
    SYS_MODE_ACTIVE,      /**< Đang hoạt động, gửi dữ liệu thường xuyên */
    SYS_MODE_STATIONARY,  /**< Xe đứng yên, đếm ngược để đi ngủ */
    SYS_MODE_SLEEP        /**< Chế độ tiết kiệm điện sâu */
} SystemMode_t;

/**
 * @brief Loại cảnh báo hệ thống
 */
typedef enum {
    ALERT_NONE = 0,
    ALERT_THEFT,        /**< Cảnh báo mất trộm (phát hiện rung khi đang khóa) */
    ALERT_CRASH,        /**< Cảnh báo tai nạn (va chạm mạnh khi đang chạy) */
    ALERT_LOW_BAT       /**< Cảnh báo pin yếu */
} AlertType_t;

/**
 * @brief Mức độ nghiêm trọng của va chạm (tương ứng IMU Service)
 */
typedef enum {
    SEVERITY_NONE = 0,
    SEVERITY_LIGHT,
    SEVERITY_MEDIUM,
    SEVERITY_SEVERE
} Severity_t;

/**
 * @brief Loại sự kiện để lưu Log
 */
typedef enum {
    LOG_EVENT_PERIODIC = 0,
    LOG_EVENT_ALARM,
    LOG_EVENT_CRASH,
    LOG_EVENT_CONFIG_CHANGE
} LogEvent_t;

/**
 * @brief Cấu hình hệ thống (Có thể thay đổi từ App)
 */
typedef struct {
    uint16_t active_interval_s;     /**< Chu kỳ gửi data khi đang chạy */
    uint16_t stationary_interval_s; /**< Chu kỳ gửi data khi đứng yên (nếu không ngủ) */
    bool     is_armed;              /**< Trạng thái chống trộm (Bật/Tắt) */
    bool     gps_enable;            /**< Cho phép/Cấm GPS */
    bool     alert_enable;          /**< Cho phép/Cấm gửi cảnh báo */
} SystemConfig_t;

/**
 * @brief Bản ghi lịch sử lưu vào Flash W25Q32
 */
typedef struct {
    uint32_t timestamp;
    float    lat;
    float    lon;
    float    speed;
    uint8_t  mode;          /**< SystemMode_t */
    uint8_t  event;         /**< LogEvent_t */
    uint8_t  mqtt_status;   /**< 0: Fail, 1: Success */
} TrackerLog_t;

/**
 * @brief Cấu trúc lưu trữ dữ liệu GPS chi tiết
 */
typedef struct {
    float       lat;            /**< Vĩ độ */
    float       lon;            /**< Kinh độ */
    float       speed;          /**< Tốc độ (km/h) */
    uint8_t     fix_quality;    /**< 0: No Fix, 1: Fix, 2: DGPS */
    uint8_t     satellites;     /**< Số vệ tinh */
    
    /* Dữ liệu thời gian thực từ GPS */
    uint8_t     hour, min, sec;
    uint8_t     day, month, year;
    uint32_t    utc_epoch;      /**< Unix Timestamp (seconds since 1970) */

    /* Thời điểm cập nhật cuối cùng của GPS */
    uint32_t    last_update_tick; 
} System_GPS_t;

/**
 * @brief Cấu trúc lưu trữ thông tin năng lượng và cảm biến khác
 */
typedef struct {
    uint8_t     battery_pct;    /**< Phần trăm pin (0-100) */
    uint16_t    battery_mv;     /**< Điện áp pin (mV) */
    uint32_t    bat_update_tick;
    
    bool        is_moving;      /**< Trạng thái rung/di chuyển */
    uint32_t    imu_update_tick;

    /* Nhóm Cảnh báo & An ninh */
    bool        is_armed;       /**< Chế độ chống trộm đang bật/tắt */
    AlertType_t alert_type;     /**< Loại cảnh báo hiện tại */
    Severity_t  alert_remain;   /**< Mức độ nghiêm trọng (nếu có) */
    uint32_t    alert_tick;     /**< Thời điểm xảy ra cảnh báo */
} System_Sensor_t;

/**
 * @brief Cấu trúc dữ liệu TỔNG HỢP của toàn hệ thống
 */
typedef struct {
    osMutexId       mutex;      /**< Mutex bảo vệ dữ liệu khi nhiều Task cùng truy cập */
    SystemMode_t    mode;       /**< Chế độ hiện tại của hệ thống */
    char            imei[20];   /**< Mã định danh thiết bị (IMEI) */
    
    System_GPS_t    gps;        /**< Dữ liệu vị trí */
    System_Sensor_t sensor;     /**< Dữ liệu cảm biến & năng lượng */
    
    uint32_t        sys_uptime; /**< Thời gian hoạt động của hệ thống (giây) */
    bool            force_report; /**< Cờ yêu cầu gửi báo cáo tức thì */
} SystemData_t;

/* --- API Prototype cho System Service --- */

void System_Service_Init(void);
void System_Service_GetSnapshot(SystemData_t *out);

void System_Service_UpdateGPS(float lat, float lon, float spd, uint8_t fix, uint8_t sats, 
                              uint8_t h, uint8_t m, uint8_t s, uint8_t day, uint8_t mon, uint8_t yr);

void System_Service_UpdateBattery(uint8_t pct, uint16_t mv);
void System_Service_UpdateMotion(bool moving);
void System_Service_UpdateState(void);

void System_Service_SetAlert(AlertType_t type, Severity_t severity);
void System_Service_ClearAlert(void);
void System_Service_SetIMEI(const char *imei);

void System_Service_GetConfig(SystemConfig_t *out);
void System_Service_UpdateConfig(SystemConfig_t *new_cfg);
bool System_Service_CheckForceReport(void);
void System_Service_SetForceReport(bool force);

int System_Service_ToJSON(char *buf, uint16_t len);

#endif /* __SYSTEM_SERVICE_H__ */
