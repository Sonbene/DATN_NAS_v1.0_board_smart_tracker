#ifndef __MQTT_SERVICE_H__
#define __MQTT_SERVICE_H__

#include "sim_a7670c.h"
#include <stdint.h>

typedef enum {
    MQTT_OK = 0,
    MQTT_ERROR,
    MQTT_NOT_CONNECTED,
    MQTT_ERR_NETWORK,
    MQTT_ERR_SSL,
    MQTT_ERR_TIMEOUT,
    MQTT_ERR_PROMPT
} MQTT_Status_t;

typedef enum {
    MQTT_QOS0 = 0,
    MQTT_QOS1 = 1,
    MQTT_QOS2 = 2
} MQTT_QoS_t;

typedef struct {
    uint8_t client_index;      /* Thường là 0 */
    const char *host;
    uint16_t port;
    const char *client_id;
    const char *username;
    const char *password;
    uint16_t keepalive_sec;
    uint32_t timeout_ms;       /* Timeout cho kết nối */
} MQTT_Config_t;

typedef struct {
    char topic[64];
    uint8_t *payload;
    uint16_t payload_len;
    MQTT_QoS_t qos;
} MQTT_Message_t;

typedef void (*MQTT_DataCallback_t)(MQTT_Message_t *msg);

#include "cmsis_os.h"

/**
 * @brief Cấu trúc tin nhắn gửi qua Mail Queue (Bất đồng bộ)
 */
typedef struct {
    char topic[64];      /**< Topic đầy đủ (vd: Son/IMEI/data) */
    char payload[160];   /**< Nội dung JSON */
} MQTT_Mail_t;

/**
 * @brief Cấu hình SSL và tham số MQTT
 */
MQTT_Status_t MQTT_Service_Init(SIM_Handle_t *sim, const MQTT_Config_t *config);

/**
 * @brief Thiết lập ID định danh (IMEI) để tự động tạo topic
 */
void MQTT_Service_SetDeviceID(const char *imei);

/**
 * @brief Gửi yêu cầu Publish MQTT vào hàng đợi
 * @param type: Loại dữ liệu (vd: "data", "alarm", "crash")
 * @param json_payload: Chuỗi JSON
 */
void MQTT_Service_QueuePublish(const char *type, const char *json_payload);

/**
 * @brief Lấy tin nhắn tiếp theo từ hàng đợi (Dùng cho SIM Task)
 */
osEvent MQTT_Service_GetMail(uint32_t timeout_ms);

/**
 * @brief Kiểm tra xem hàng đợi MQTT có đang trống không
 */
bool MQTT_Service_IsQueueEmpty(void);

/**
 * @brief Giải phóng bộ nhớ của Mail sau khi xử lý xong
 */
void MQTT_Service_FreeMail(void *mail_ptr);

/**
 * @brief Kết nối tới Broker (HiveMQ Cloud)
 */
MQTT_Status_t MQTT_Service_Connect(SIM_Handle_t *sim);

/**
 * @brief Ngắt kết nối khỏi Broker
 */
MQTT_Status_t MQTT_Service_Disconnect(SIM_Handle_t *sim);

/**
 * @brief Đăng tin nhắn
 */
MQTT_Status_t MQTT_Service_Publish(SIM_Handle_t *sim, const char *topic, const uint8_t *payload, uint16_t len, MQTT_QoS_t qos);

/**
 * @brief Đăng ký nhận tin nhắn từ topic
 */
MQTT_Status_t MQTT_Service_Subscribe(SIM_Handle_t *sim, const char *topic, MQTT_QoS_t qos, MQTT_DataCallback_t cb);

/**
 * @brief Hàm xử lý khi có dữ liệu MQTT đổ từ Driver về
 */
MQTT_Status_t MQTT_Service_IsConnected(SIM_Handle_t *sim);
void MQTT_Service_HandleURC(SIM_Handle_t *sim, char *line);

/**
 * @brief Kiểm tra xem MQTT có đang bận thực hiện lệnh mạng không
 * @return true nếu đang rảnh (không bận kết nối/gửi)
 */
bool MQTT_Service_IsStable(void);

#endif /* __MQTT_SERVICE_H__ */
