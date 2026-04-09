#ifndef __ATGM336H_H__
#define __ATGM336H_H__

#include <stdint.h>
#include <stdbool.h>

/** @defgroup ATGM336H_Config Cấu hình Driver
 * @{
 */
#define ATGM336H_NMEA_MAX_LEN      82  /**< NMEA-0183 standard max (bao gồm $ và CR/LF) */

/**
 * @brief Callback function type for raw NMEA sentences.
 * @param sentence Public raw NMEA string (NULL-terminated).
 */
typedef void (*ATGM336H_RawCallback_t)(const char *sentence);
/** @} */

/** @} */

/**
 * @brief Dữ liệu GPS đã giải mã từ các câu NMEA (RMC + GGA + GSA)
 * @note  Sử dụng float thay vì double — Cortex-M4F chỉ có FPU đơn chính xác.
 *        Độ phân giải float (~7 chữ số) tương đương ~11cm cho tọa độ GPS,
 *        đủ dùng cho ứng dụng tracker (sai số GPS ≥ 2.5m CEP).
 */
typedef struct {
    /* --- Tọa độ & Di chuyển --- */
    float       latitude;       /**< Vĩ độ (DD.DDDDDD), âm = Nam bán cầu */
    float       longitude;      /**< Kinh độ (DDD.DDDDDD), âm = Tây bán cầu */
    float       altitude;       /**< Cao độ so với mực nước biển (m) — từ GGA */
    float       speed_knots;    /**< Tốc độ (knots) — từ RMC */
    float       speed_kmh;      /**< Tốc độ (km/h) — quy đổi từ knots */
    float       course;         /**< Hướng di chuyển (0–359.9°) — từ RMC */

    /* --- Thời gian UTC --- */
    uint8_t     utc_hour;
    uint8_t     utc_min;
    uint8_t     utc_sec;
    uint8_t     day;
    uint8_t     month;
    uint8_t     year;           /**< Năm tính từ 2000, vd: 26 = 2026 */

    /* --- Chất lượng tín hiệu --- */
    uint8_t     satellites;     /**< Số vệ tinh đang dùng — từ GGA */
    uint8_t     fix_quality;    /**< GGA: 0=No Fix, 1=GPS Fix, 2=DGPS Fix */
    uint8_t     fix_mode;       /**< GSA: 1=No Fix, 2=2D Fix, 3=3D Fix */
    float       hdop;           /**< Horizontal Dilution of Precision */
    float       pdop;           /**< Position DOP — từ GSA */
    float       vdop;           /**< Vertical DOP — từ GSA */

    bool        is_valid;       /**< true khi tọa độ đã chốt hợp lệ (có Fix) */
} ATGM336H_Info_t;

/**
 * @brief Handle instance cho ATGM336H
 * @note  Toàn bộ trạng thái parser nằm trong handle, KHÔNG dùng biến static global
 *        → hỗ trợ multi-instance, an toàn re-entrant.
 *        Đây là parser thuần NMEA — không phụ thuộc HAL hay BSP.
 */
typedef struct {
    ATGM336H_Info_t         info;                               /**< Kết quả parse mới nhất */
    char                    sentence_buf[ATGM336H_NMEA_MAX_LEN + 2]; /**< Buffer tích lũy 1 câu NMEA */
    uint16_t                sentence_idx;                       /**< Vị trí ghi hiện tại */
    bool                    receiving;                          /**< true = đang tích lũy (đã gặp '$') */
    ATGM336H_RawCallback_t  raw_callback;                       /**< Callback báo tin nhắn thô */
} ATGM336H_Handle_t;


/**
 * @brief Khởi tạo handle GPS (reset toàn bộ trạng thái parser + info)
 * @param handle Pointer tới struct ATGM336H_Handle_t
 */
void ATGM336H_Init(ATGM336H_Handle_t *handle);

/**
 * @brief Đẩy một khối byte thô vào parser.
 *        Hàm tự động tách các câu NMEA dựa trên ký tự '$' và CR/LF,
 *        validate checksum XOR, rồi giải mã RMC/GGA/GSA cập nhật handle->info.
 * @param handle  Pointer tới struct ATGM336H_Handle_t
 * @param data    Buffer chứa dữ liệu thô từ UART
 * @param len     Số byte cần xử lý
 */
void ATGM336H_ParseBuffer(ATGM336H_Handle_t *handle, const uint8_t *data, uint16_t len);

/**
 * @brief Sao chép dữ liệu GPS mới nhất ra ngoài (thread-safe copy)
 * @param handle  Pointer tới handle (const — không bị thay đổi)
 * @param out     Pointer nhận kết quả
 */
void ATGM336H_GetInfo(const ATGM336H_Handle_t *handle, ATGM336H_Info_t *out);

/**
 * @brief Đăng ký callback để nhận các câu NMEA thô (hữu ích cho debug).
 * @param handle   Pointer tới handle
 * @param callback Hàm callback (NULL để disable)
 */
void ATGM336H_RegisterRawCallback(ATGM336H_Handle_t *handle, ATGM336H_RawCallback_t callback);


#endif /* __ATGM336H_H__ */
