#ifndef __SYSTEM_SERVICE_H__
#define __SYSTEM_SERVICE_H__

#include "main.h"
#include "cmsis_os.h"
#include <stdbool.h>
#include <stdio.h>

/* ========================================================================================
 * SECTION: System Default Configurations
 * ======================================================================================== */
#define DEFAULT_ACTIVE_INTERVAL_S       30      /**< 10 giây khi di chuyển */
#define DEFAULT_STATIONARY_INTERVAL_S   30     /**< 5 phút khi đứng yên */
#define MAX_REPORT_INTERVAL_S           3600    /**< Tối đa 1 tiếng */
#define DEFAULT_SLEEP_DELAY_S           30      /**< 30 giây chờ trước khi ngủ */

/* Cấu hình lưu trữ Config vào Flash */
#define CONFIG_FLASH_SECTOR             1023    /**< Sector cuối cùng của W25Q32 (4MB) */
#define CONFIG_FLASH_MAGIC              0xC04F  /**< "CONF" Magic word */

/* Tính năng báo động tai nạn */
#define ENABLE_CRASH_SMS                0       /**< 1: Bật, 0: Tắt gửi SMS khi có tai nạn */

/* Abstraction cho chân khóa xe (Relay) */
#define VEHICLE_LOCK_PORT               GPIOA
#define VEHICLE_LOCK_PIN                GPIO_PIN_12

/**
 * @brief Macro điều khiển khóa xe (Dễ dàng thay đổi logic Active-High/Low tại đây)
 */
#define SYSTEM_LOCK_VEHICLE()           HAL_GPIO_WritePin(VEHICLE_LOCK_PORT, VEHICLE_LOCK_PIN, GPIO_PIN_SET)
#define SYSTEM_UNLOCK_VEHICLE()         HAL_GPIO_WritePin(VEHICLE_LOCK_PORT, VEHICLE_LOCK_PIN, GPIO_PIN_RESET)

typedef enum {
    SYS_MODE_INIT = 0,
    SYS_MODE_ACTIVE,      /**< Đang hoạt động, gửi dữ liệu thường xuyên */
    SYS_MODE_STATIONARY,  /**< Xe đứng yên, đếm ngược để đi ngủ */
    SYS_MODE_SLEEP        /**< Chế độ tiết kiệm điện sâu */
} SystemMode_t;
 
 /**
  * @brief Nguồn dữ liệu vị trí
  */
 typedef enum {
     POS_SOURCE_NONE = 0,
     POS_SOURCE_GPS,
     POS_SOURCE_LBS,
     POS_SOURCE_NO_FIX
 } PositionSource_t;
 
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
    uint16_t sleep_delay_s;         /**< Thời gian chờ đứng yên trước khi ngủ */
    char     sms_phone1[16];        /**< Số điện thoại nhận SMS 1 */
    char     sms_phone2[16];        /**< Số điện thoại nhận SMS 2 */
    char     sms_phone3[16];        /**< Số điện thoại nhận SMS 3 */
    uint16_t magic;                 /**< Luôn là CONFIG_FLASH_MAGIC để kiểm tra hợp lệ */
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
 
    PositionSource_t source;    /**< Nguồn dữ liệu vị trí: GPS hoặc LBS */
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
    bool        is_locked;      /**< Trạng thái vật lý của khóa xe (GPIO PA12) */
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
    
    /* Command từ Server (Lock/Unlock) */
    bool            lock_request_pending; /**< Cờ có yêu cầu đổi trạng thái khóa */
    bool            target_lock_state;    /**< Trạng thái mong muốn (true = Lock) */
    
    /* Trạng thái đặc biệt */
    bool            wakeup_pending;       /**< Cờ báo vừa thức dậy từ Sleep */
} SystemData_t;

/* --- API Prototype cho System Service --- */

void System_Service_Init(void);
void System_Service_GetSnapshot(SystemData_t *out);

void System_Service_UpdateGPS(float lat, float lon, float spd, uint8_t fix, uint8_t sats, 
                              uint8_t h, uint8_t m, uint8_t s, uint8_t day, uint8_t mon, uint8_t yr,
                              PositionSource_t source);
                              
void System_Service_UpdateTime(uint8_t h, uint8_t m, uint8_t s, uint8_t day, uint8_t mon, uint8_t yr);

void System_Service_UpdateSource(PositionSource_t source);

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
void System_Service_VisualNotify(uint8_t count);

bool System_Service_CheckWakeup(void);
void System_Service_SetWakeup(bool pending);

/* Flash Persistence & Config Update API */
void System_Service_SaveConfig(void);
void System_Service_LoadConfig(void);
bool System_Service_UpdateConfig_Compressed(const char *json);

/* Lock Control API */
void System_Service_RequestLock(bool lock);
void System_Service_UpdateLockStatus(bool locked);
void System_Service_ClearLockRequest(void);

int System_Service_ToJSON(char *buf, uint16_t len);

#endif /* __SYSTEM_SERVICE_H__ */
