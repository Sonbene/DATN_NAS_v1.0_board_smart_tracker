#include "atgm336h.h"
#include <string.h>
#include <stdlib.h>

/* ======================== Private Prototypes ======================== */

static bool     prv_ValidateChecksum(const char *sentence);
static void     prv_ProcessSentence(ATGM336H_Handle_t *handle, const char *sentence);
static void     prv_GetField(const char *sentence, uint8_t idx, char *buf, uint8_t maxlen);
static float    prv_NmeaToDecimal(const char *coord, char dir);
static float    prv_Atof(const char *s);

/* ======================== Public API ======================== */

void ATGM336H_Init(ATGM336H_Handle_t *handle)
{
    if (handle == NULL) return;
    memset(handle, 0, sizeof(ATGM336H_Handle_t));
    handle->raw_callback = NULL;
}


void ATGM336H_ParseBuffer(ATGM336H_Handle_t *handle, const uint8_t *data, uint16_t len)
{
    if (handle == NULL || data == NULL) return;

    for (uint16_t i = 0; i < len; i++) {
        char c = (char)data[i];

        if (c == '$') {
            /* Bắt đầu câu NMEA mới → reset vị trí, bắt đầu tích lũy */
            handle->sentence_idx = 0;
            handle->sentence_buf[handle->sentence_idx++] = c;
            handle->receiving = true;
        }
        else if (handle->receiving) {
            if (c == '\r' || c == '\n') {
                /* Kết thúc câu → validate + giải mã */
                if (handle->sentence_idx > 6) {  /* Tối thiểu: $GxXXX,...*HH */
                    handle->sentence_buf[handle->sentence_idx] = '\0';
                    
                    /* Notify raw sentence before internal processing */
                    if (handle->raw_callback != NULL) {
                        handle->raw_callback(handle->sentence_buf);
                    }
                    
                    prv_ProcessSentence(handle, handle->sentence_buf);
                }

                handle->sentence_idx = 0;
                handle->receiving = false;
            }
            else if (handle->sentence_idx < ATGM336H_NMEA_MAX_LEN) {
                handle->sentence_buf[handle->sentence_idx++] = c;
            }
            else {
                /* Câu quá dài → bất thường (nhiễu), drop toàn bộ */
                handle->receiving = false;
                handle->sentence_idx = 0;
            }
        }
        /* Nếu !receiving và c != '$' → bỏ qua (noise, LF thừa giữa các câu) */
    }
}

void ATGM336H_GetInfo(const ATGM336H_Handle_t *handle, ATGM336H_Info_t *out)
{
    if (handle != NULL && out != NULL) {
        memcpy(out, &handle->info, sizeof(ATGM336H_Info_t));
    }
}

void ATGM336H_RegisterRawCallback(ATGM336H_Handle_t *handle, ATGM336H_RawCallback_t callback)
{
    if (handle != NULL) {
        handle->raw_callback = callback;
    }
}


/* ======================== Private: Checksum ======================== */

/**
 * @brief Validate NMEA XOR checksum.
 *        Format: $....*HH  →  XOR tất cả byte giữa '$' và '*', so sánh với HH (hex).
 */
static bool prv_ValidateChecksum(const char *sentence)
{
    if (sentence[0] != '$') return false;

    uint8_t calc = 0;
    uint16_t i = 1;

    while (sentence[i] != '\0' && sentence[i] != '*') {
        calc ^= (uint8_t)sentence[i];
        i++;
    }

    if (sentence[i] != '*') return false;

    /* Parse 2-digit hex sau dấu '*' */
    uint8_t expected = (uint8_t)strtol(&sentence[i + 1], NULL, 16);
    return (calc == expected);
}

/* ======================== Private: Field Extraction ======================== */

/**
 * @brief Trích field thứ `idx` (0-based) từ câu NMEA.
 *        Field 0 = Sentence ID (vd: "GNRMC"), field 1 = data field đầu tiên.
 *        Dấu phân cách: dấu ',' (comma). Kết thúc tại '*' hoặc '\0'.
 */
static void prv_GetField(const char *sentence, uint8_t idx, char *buf, uint8_t maxlen)
{
    uint8_t cur_field = 0;
    uint16_t si = 0;
    uint16_t bi = 0;

    buf[0] = '\0';

    /* Bỏ qua ký tự '$' mở đầu */
    if (sentence[si] == '$') si++;

    while (sentence[si] != '\0' && sentence[si] != '*') {
        if (sentence[si] == ',') {
            cur_field++;
            if (cur_field > idx) break;  /* Đã qua field cần lấy → dừng */
        } else if (cur_field == idx) {
            if (bi < (uint16_t)(maxlen - 1)) {
                buf[bi++] = sentence[si];
            }
        }
        si++;
    }
    buf[bi] = '\0';
}

/* ======================== Private: Coordinate Conversion ======================== */

/**
 * @brief Chuyển tọa độ NMEA dạng DDmm.mmmm → Decimal Degrees (float).
 *        Ví dụ: "2106.78432" với dir='N' → 21.113072
 * @param coord Chuỗi tọa độ NMEA (latitude DDmm.mmmm hoặc longitude DDDmm.mmmm)
 * @param dir   Hướng: 'N'/'S' (lat), 'E'/'W' (lon)
 */
static float prv_NmeaToDecimal(const char *coord, char dir)
{
    if (coord[0] == '\0') return 0.0f;

    const char *dot = strchr(coord, '.');
    if (dot == NULL) return 0.0f;

    /* Trong NMEA, phần phút (mm.mmmm) luôn bắt đầu 2 ký tự trước dấu chấm */
    int min_start = (int)(dot - coord) - 2;
    if (min_start < 0 || min_start > 3) return 0.0f;  /* Max 3 chữ số cho Degrees (longitude) */

    /* Tách phần Degrees */
    char deg_str[4] = {0};
    strncpy(deg_str, coord, (size_t)min_start);
    deg_str[min_start] = '\0';

    /* Tách phần Minutes và chuyển đổi */
    float degrees = (float)atoi(deg_str);
    float minutes = prv_Atof(&coord[min_start]);
    float decimal = degrees + (minutes / 60.0f);

    /* Nam bán cầu hoặc Tây bán cầu → giá trị âm */
    if (dir == 'S' || dir == 'W') {
        decimal = -decimal;
    }

    return decimal;
}

/**
 * @brief Wrapper atof → float (tránh dùng double trực tiếp trên Cortex-M4F)
 */
static float prv_Atof(const char *s)
{
    if (s == NULL || s[0] == '\0') return 0.0f;
    return (float)atof(s);
}

/* ======================== Private: Sentence Processors ======================== */

/**
 * @brief Phân phối câu NMEA đã validate sang bộ giải mã tương ứng.
 *        Hỗ trợ: RMC (tọa độ, tốc độ, thời gian), GGA (fix, vệ tinh, cao độ), GSA (DOP).
 *        Prefix linh hoạt: GN/GP/GB/GA/GL/BD đều được nhận diện.
 */
static void prv_ProcessSentence(ATGM336H_Handle_t *handle, const char *sentence)
{
    /* Kiểm tra tính toàn vẹn — câu bị nhiễu UART sẽ bị drop tại đây */
    if (!prv_ValidateChecksum(sentence)) return;

    char field[20];

    /* Lấy Sentence ID (field 0): GNRMC, GPGGA, GNGSA, ... */
    prv_GetField(sentence, 0, field, sizeof(field));

    /* ======= xxRMC — Recommended Minimum Navigation ======= */
    if (strstr(field, "RMC") != NULL) {

        /* Status: A = Active (có fix), V = Void (không có fix) */
        prv_GetField(sentence, 2, field, sizeof(field));
        handle->info.is_valid = (field[0] == 'A');

        /* UTC Time: hhmmss.sss */
        prv_GetField(sentence, 1, field, sizeof(field));
        if (strlen(field) >= 6) {
            handle->info.utc_hour = (uint8_t)((field[0] - '0') * 10 + (field[1] - '0'));
            handle->info.utc_min  = (uint8_t)((field[2] - '0') * 10 + (field[3] - '0'));
            handle->info.utc_sec  = (uint8_t)((field[4] - '0') * 10 + (field[5] - '0'));
        }

        /* Chỉ cập nhật tọa độ và tốc độ khi có fix hợp lệ */
        if (handle->info.is_valid) {
            char coord[16], dir[4];

            /* Latitude (field 3,4) */
            prv_GetField(sentence, 3, coord, sizeof(coord));
            prv_GetField(sentence, 4, dir, sizeof(dir));
            handle->info.latitude = prv_NmeaToDecimal(coord, dir[0]);

            /* Longitude (field 5,6) */
            prv_GetField(sentence, 5, coord, sizeof(coord));
            prv_GetField(sentence, 6, dir, sizeof(dir));
            handle->info.longitude = prv_NmeaToDecimal(coord, dir[0]);

            /* Speed over ground (field 7) → knots + km/h */
            prv_GetField(sentence, 7, field, sizeof(field));
            handle->info.speed_knots = prv_Atof(field);
            handle->info.speed_kmh   = handle->info.speed_knots * 1.852f;

            /* Course over ground (field 8) */
            prv_GetField(sentence, 8, field, sizeof(field));
            handle->info.course = prv_Atof(field);
        }

        /* Date: ddmmyy (field 9) — parse cả khi chưa fix (vẫn có thời gian từ vệ tinh) */
        prv_GetField(sentence, 9, field, sizeof(field));
        if (strlen(field) >= 6) {
            handle->info.day   = (uint8_t)((field[0] - '0') * 10 + (field[1] - '0'));
            handle->info.month = (uint8_t)((field[2] - '0') * 10 + (field[3] - '0'));
            handle->info.year  = (uint8_t)((field[4] - '0') * 10 + (field[5] - '0'));
        }
    }

    /* ======= xxGGA — Global Positioning System Fix Data ======= */
    else if (strstr(field, "GGA") != NULL) {

        /* Fix Quality (field 6): 0=Invalid, 1=GPS, 2=DGPS */
        prv_GetField(sentence, 6, field, sizeof(field));
        handle->info.fix_quality = (uint8_t)atoi(field);

        if (handle->info.fix_quality > 0) {
            handle->info.is_valid = true;
            char coord[16], dir[4];

            /* Latitude (field 2,3) */
            prv_GetField(sentence, 2, coord, sizeof(coord));
            prv_GetField(sentence, 3, dir, sizeof(dir));
            handle->info.latitude = prv_NmeaToDecimal(coord, dir[0]);

            /* Longitude (field 4,5) */
            prv_GetField(sentence, 4, coord, sizeof(coord));
            prv_GetField(sentence, 5, dir, sizeof(dir));
            handle->info.longitude = prv_NmeaToDecimal(coord, dir[0]);
        } else {
            handle->info.is_valid = false;
        }

        /* Number of satellites in use (field 7) */
        prv_GetField(sentence, 7, field, sizeof(field));
        handle->info.satellites = (uint8_t)atoi(field);

        /* HDOP (field 8) */
        prv_GetField(sentence, 8, field, sizeof(field));
        handle->info.hdop = prv_Atof(field);

        /* Altitude above sea level (field 9) */
        prv_GetField(sentence, 9, field, sizeof(field));
        handle->info.altitude = prv_Atof(field);
    }

    /* ======= xxGSA — DOP and Active Satellites ======= */
    else if (strstr(field, "GSA") != NULL) {

        /* Fix Mode (field 2): 1=No fix, 2=2D, 3=3D */
        prv_GetField(sentence, 2, field, sizeof(field));
        handle->info.fix_mode = (uint8_t)atoi(field);

        /* Field 3–14: PRN của 12 vệ tinh (bỏ qua)
         * Field 15: PDOP, Field 16: HDOP, Field 17: VDOP */
        prv_GetField(sentence, 15, field, sizeof(field));
        handle->info.pdop = prv_Atof(field);

        prv_GetField(sentence, 16, field, sizeof(field));
        handle->info.hdop = prv_Atof(field);

        prv_GetField(sentence, 17, field, sizeof(field));
        handle->info.vdop = prv_Atof(field);
    }
}
