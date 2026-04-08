/**
 * @file    secrets_template.h
 * @brief   TEMPLATE MẪU CHO CÁC THÔNG TIN NHẠY CẢM
 * @note    FILE NÀY ĐƯỢC ĐẨY LÊN GIT. 
 *          HƯỚNG DẪN: Ở máy mỗi dev, hãy copy file này, đổi tên thành "secrets.h" 
 *          và điền thông tin thật. File "secrets.h" đã được cấu hình ẩn khỏi Git.
 */

#ifndef __SECRETS_H__
#define __SECRETS_H__

/* --- MQTT Credentials --- */
#define SECRET_MQTT_BROKER     "mqtt.your-server.com"
#define SECRET_MQTT_PORT       "8883"
#define SECRET_MQTT_USER       "your_username"
#define SECRET_MQTT_PASS       "your_password"
#define SECRET_MQTT_CLIENT_ID  "tracker_001"

/* --- Viettel/Mobifone APN (nếu dùng SIM A7670C) --- */
#define SECRET_SIM_APN         "v-internet"

/* --- Các API Key khác (nếu có) --- */
// #define SECRET_GOOGLE_MAPS_API_KEY ""

#endif /* __SECRETS_H__ */
