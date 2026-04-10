#include "atgm336h_task.h"
#include "log.h"
#include "main.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include <string.h>




/* ======================== Configuration ======================== */

#define GPS_RX_BUF_SIZE         256     /**< Kích thước buffer DMA cho UART RX */
#define GPS_LISTEN_WINDOW_MS    1100    /**< Cửa sổ lắng nghe NMEA mỗi chu kỳ (GPS output 1Hz → 1.1s đủ bắt 1 burst) */
#define GPS_CYCLE_PERIOD_MS     5000    /**< Chu kỳ đọc GPS tổng thể (5 giây) */
#define GPS_TIMEZONE_OFFSET     7       /**< Múi giờ Việt Nam (UTC+7) */


/* ======================== External HAL Handle ======================== */

extern UART_HandleTypeDef huart1;       /**< USART1 — nối ATGM336H (9600 baud, RX DMA) */

/* ======================== Module State ======================== */

BSP_UART_Handle_t       gps_uart_bus;           /**< BSP handle cho GPS UART */
static TaskHandle_t     gps_task_handle = NULL;
static ATGM336H_Handle_t gps_handle;

/** Bộ đệm DMA cho UART RX */
static uint8_t gps_rx_buf[GPS_RX_BUF_SIZE];

/* ======================== Private Prototypes ======================== */

static void StartATGM336HTask(void const *argument);
static void prv_GpsUartCallback(BSP_UART_Event_t event, uint16_t size, BaseType_t *pxWoken);
// static void prv_GpsRawCallback(const char *sentence);
static void prv_GetLocalTime(const ATGM336H_Info_t *utc, ATGM336H_Info_t *local);

/* ======================== ISR Callback ======================== */

/**
 * @brief Callback được BSP_UART gọi từ ngắt khi nhận được sự kiện IDLE hoặc DMA TC.
 *        Gửi kích thước dữ liệu nhận được tới GPS task qua Task Notification.
 */
static void prv_GpsUartCallback(BSP_UART_Event_t event, uint16_t size, BaseType_t *pxWoken)
{
    if (gps_task_handle == NULL) return;

    if (event == BSP_UART_EVENT_IDLE || event == BSP_UART_EVENT_RX_DONE) {
        xTaskNotifyFromISR(gps_task_handle, (uint32_t)size, eSetValueWithOverwrite, pxWoken);
    } else if (event == BSP_UART_EVENT_ERROR) {
        /* Notify task that an error occurred (using 0xFFFFFFFF as error flag) */
        xTaskNotifyFromISR(gps_task_handle, 0xFFFFFFFFUL, eSetValueWithOverwrite, pxWoken);
    }
}

#if 0
/**
 * @brief Callback nhận câu NMEA thô từ driver để log debug.
 */
static void prv_GpsRawCallback(const char *sentence)
{
    /* Dùng LOG_RAW để giữ nguyên format, thêm prefix cho dễ lọc */
    LOG_RAW("[GPS-RAW] %s\r\n", sentence);
}
#endif


/**
 * @brief Chuyển đổi UTC Info sang Local Info (Việt Nam UTC+7)
 *        Tự động xử lý nhảy ngày/tháng/năm khi cộng giờ.
 */
static void prv_GetLocalTime(const ATGM336H_Info_t *utc, ATGM336H_Info_t *local)
{
    if (utc == NULL || local == NULL) return;

    /* Copy dữ liệu gốc (tọa độ, satellites...) */
    memcpy(local, utc, sizeof(ATGM336H_Info_t));

    /* Nếu chưa có dữ liệu thời gian (năm 0), thoát */
    if (utc->year == 0) return;

    static const uint8_t days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    /* 1. Cộng giờ */
    int hour = utc->utc_hour + GPS_TIMEZONE_OFFSET;

    /* 2. Xử lý tràn ngày (chỉ cần xử lý tiến vì offset VN luôn dương) */
    if (hour >= 24) {
        hour -= 24;
        local->day++;

        /* Xác định số ngày tối đa trong tháng hiện tại */
        uint8_t max_days = days_in_month[utc->month];
        if (utc->month == 2) {
            uint16_t full_year = 2000 + utc->year;
            if ((full_year % 4 == 0 && full_year % 100 != 0) || (full_year % 400 == 0)) {
                max_days = 29;
            }
        }

        /* Tràn tháng */
        if (local->day > max_days) {
            local->day = 1;
            local->month++;

            /* Tràn năm */
            if (local->month > 12) {
                local->month = 1;
                local->year++;
            }
        }
    }

    local->utc_hour = (uint8_t)hour;
}

/* ======================== GPS Task ======================== */

/**
 * @brief Task GPS chính.
 *        Mỗi chu kỳ 5 giây:
 *          1. Mở DMA + IDLE detection trong ~1.1 giây để bắt đủ 1 burst NMEA
 *          2. Parse tất cả câu NMEA nhận được
 *          3. Đóng UART, in kết quả
 *          4. Ngủ bù cho đủ chu kỳ (drift-free qua vTaskDelayUntil)
 */
static void StartATGM336HTask(void const *argument)
{
    (void)argument;
    LOG_INFO("[GPS] Task started. Cycle: %d ms, Listen: %d ms",
             GPS_CYCLE_PERIOD_MS, GPS_LISTEN_WINDOW_MS);

    /* Chờ hệ thống ổn định sau khi cấp nguồn (GPS module cần thời gian boot) */
    vTaskDelay(pdMS_TO_TICKS(500));

    TickType_t xLastWakeTime = xTaskGetTickCount();


    for (;;) {
        /* ---- 1. Bật DMA + IDLE detection ---- */
        /* Xóa sạch cờ lỗi (Overrun, Framing, Noise) trước khi bắt đầu */
        __HAL_UART_CLEAR_IT(gps_uart_bus.huart, UART_CLEAR_OREF | UART_CLEAR_NEF | UART_CLEAR_FEF | UART_CLEAR_PEF);
        
        HAL_UARTEx_ReceiveToIdle_DMA(gps_uart_bus.huart, gps_rx_buf, GPS_RX_BUF_SIZE);
        __HAL_DMA_DISABLE_IT(gps_uart_bus.huart->hdmarx, DMA_IT_HT);


        /* ---- 2. Lắng nghe trong cửa sổ ~1.1 giây ---- */
        TickType_t window_start = xTaskGetTickCount();
        TickType_t window_ticks = pdMS_TO_TICKS(GPS_LISTEN_WINDOW_MS);

        while ((xTaskGetTickCount() - window_start) < window_ticks) {
            TickType_t elapsed = xTaskGetTickCount() - window_start;
            TickType_t wait_ticks = (elapsed < window_ticks) ? (window_ticks - elapsed) : 0;
            if (wait_ticks == 0) break;

            uint32_t rx_size = 0;
            if (xTaskNotifyWait(0, 0xFFFFFFFFUL, &rx_size, wait_ticks) == pdPASS) {
                if (rx_size == 0xFFFFFFFFUL) {
                    /* UART Error occurred -> Abort and Restart */
                    LOG_WARN("[GPS] UART Error detected, restarting DMA...");
                    BSP_UART_AbortReceive(&gps_uart_bus);
                } else if (rx_size > 0 && rx_size <= GPS_RX_BUF_SIZE) {
                    ATGM336H_ParseBuffer(&gps_handle, gps_rx_buf, (uint16_t)rx_size);
                }

                /* Kích hoạt lại DMA để đón burst IDLE tiếp theo (nếu còn) */
                __HAL_UART_CLEAR_IT(gps_uart_bus.huart, UART_CLEAR_OREF | UART_CLEAR_NEF | UART_CLEAR_FEF | UART_CLEAR_PEF);
                HAL_UARTEx_ReceiveToIdle_DMA(gps_uart_bus.huart, gps_rx_buf, GPS_RX_BUF_SIZE);
                __HAL_DMA_DISABLE_IT(gps_uart_bus.huart->hdmarx, DMA_IT_HT);
            }

        }

        /* ---- 3. Dừng nhận — giữ UART im lặng cho đến chu kỳ kế ---- */
        BSP_UART_AbortReceive(&gps_uart_bus);

        /* ---- 4. In kết quả (đã áp dụng múi giờ) ---- */
        ATGM336H_Info_t info_utc, info;
        ATGM336H_GetInfo(&gps_handle, &info_utc);
        prv_GetLocalTime(&info_utc, &info);

        if (info.is_valid) {

            LOG_INFO("[GPS] FIX | %.6f, %.6f | Alt:%.1fm | Spd:%.1fkm/h | %02d-%02d-20%02d %02d:%02d:%02d | Sat:%d | HDOP:%.1f",
                     info.latitude, info.longitude, info.altitude,
                     info.speed_kmh,
                     info.day, info.month, info.year,
                     info.utc_hour, info.utc_min, info.utc_sec,
                     info.satellites, info.hdop);
        } else {

            LOG_INFO("[GPS] SEARCHING | Sat:%d | Fix:%d | %02d-%02d-20%02d %02d:%02d:%02d",
                     info.satellites, info.fix_quality,
                     info.day, info.month, info.year,
                     info.utc_hour, info.utc_min, info.utc_sec);
        }

        /* ---- 5. Ngủ bù cho đủ chu kỳ (drift-free) ---- */
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(GPS_CYCLE_PERIOD_MS));
        
    }
}

/* ======================== Public API ======================== */

void ATGM336H_Task_Init(void)
{
    LOG_INFO("[GPS] Initializing BSP UART + Parser...");

    /* 1. Khởi tạo BSP UART cho GPS (USART1) */
    BSP_UART_Init(&gps_uart_bus, &huart1);
    BSP_UART_RegisterCallback(&gps_uart_bus, prv_GpsUartCallback);

    /* 2. Khởi tạo GPS NMEA Parser */
    ATGM336H_Init(&gps_handle);
    // ATGM336H_RegisterRawCallback(&gps_handle, prv_GpsRawCallback);


    /* 3. Tạo FreeRTOS Task */

    osThreadDef(gpsTask, StartATGM336HTask, osPriorityNormal, 0, 512);
    gps_task_handle = osThreadCreate(osThread(gpsTask), NULL);

    if (gps_task_handle == NULL) {
        LOG_ERROR("[GPS] Failed to create task!");
    } else {
        LOG_INFO("[GPS] Task created successfully.");
    }
}

bool ATGM336H_Task_GetLatestInfo(ATGM336H_Info_t *out)
{
    if (out == NULL) return false;
    ATGM336H_GetInfo(&gps_handle, out);
    return out->is_valid;
}
