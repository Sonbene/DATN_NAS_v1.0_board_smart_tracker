#ifndef __SIM_A7670C_H__
#define __SIM_A7670C_H__

#include "stm32l4xx_hal.h"
#include "bsp_uart.h"
#include <stdbool.h>

#include "ring_buffer.h"

#define SIM_RING_BUF_SIZE       1024
#define SIM_AT_TIMEOUT_DEFAULT  2000

typedef enum {
    SIM_OK = 0,
    SIM_ERROR,
    SIM_TIMEOUT,
    SIM_BUSY
} SIM_Status_t;

typedef enum {
    SIM_EVENT_NONE = 0,
    SIM_EVENT_MQTT_MSG,     /* Có tin nhắn MQTT mới */
    SIM_EVENT_SMS_MSG,      /* Có tin nhắn SMS mới */
    SIM_EVENT_NET_READY,    /* Đã có mạng */
    SIM_EVENT_NET_LOST,     /* Mất mạng */
    SIM_EVENT_MODEM_RESET   /* Modem vừa khởi động lại (nhận *ATREADY) */
} SIM_Event_t;

typedef struct {
    SIM_Event_t event;
    uint8_t *data;
    uint16_t len;
} SIM_Message_t;

typedef void (*SIM_EventCallback_t)(SIM_Message_t *msg);

typedef struct {
    BSP_UART_Handle_t *uart_handle;
    
    /* Control Pins */
    GPIO_TypeDef *pwr_port;
    uint16_t pwr_pin;
    GPIO_TypeDef *rst_port;
    uint16_t rst_pin;
    GPIO_TypeDef *dtr_port;
    uint16_t dtr_pin;
    GPIO_TypeDef *ri_port;
    uint16_t ri_pin;

    /* Ring Buffer for asynchronous RX data */
    RingBuffer_t rx_rb;
    uint8_t rb_mem[SIM_RING_BUF_SIZE];
    
    /* Event Handling */
    SIM_EventCallback_t event_cb;
    
    /* State */
    bool is_power_on;
    bool is_net_ready;
    bool is_waiting_resp;   /* Flag báo hiệu đang chờ phản hồi lệnh AT đồng bộ */
} SIM_Handle_t;

/**
 * @brief Khởi tạo Handle cho module SIM
 */
void SIM_Init(SIM_Handle_t *handle, BSP_UART_Handle_t *uart);

/**
 * @brief Đăng ký callback xử lý sự kiện (URC)
 */
void SIM_RegisterEventCallback(SIM_Handle_t *handle, SIM_EventCallback_t cb);

/**
 * @brief Task xử lý chính (Scan RingBuffer tìm URC)
 *        Nên gọi hàm này thường xuyên trong SIM Task
 */
void SIM_A7670C_Process(SIM_Handle_t *handle);

/**
 * @brief Điều khiển nguồn module SIM
 */
void SIM_PowerOn(SIM_Handle_t *handle);
void SIM_HardReset(SIM_Handle_t *handle);

/**
 * @brief Gửi lệnh AT, chờ ký tự '>', sau đó mới truyền payload
 * @param command: Chuỗi lệnh (vd: "AT+CMQPUB=0,\"topic\",1,60,0,0,10\r\n")
 * @param data: Con trỏ dữ liệu payload
 * @param data_len: Độ dài payload
 * @param expected_response: Ký tự phản hồi mong đợi sau khi gửi data (thường là "OK")
 * @param prompt_timeout_ms: Thời gian tối đa đợi dấu '>'
 * @param resp_timeout_ms: Thời gian tối đa đợi phản hồi sau khi gửi data
 */
SIM_Status_t SIM_MQTT_IsConnected(SIM_Handle_t *handle);
SIM_Status_t SIM_SendATWithData(SIM_Handle_t *handle, const char *command, const uint8_t *data, uint16_t data_len, const char *expected_response, uint32_t prompt_timeout_ms, uint32_t resp_timeout_ms);

/**
 * @brief Gửi lệnh AT và đợi phản hồi, có trả về chuỗi response
 */
SIM_Status_t SIM_SendATCommandEx(SIM_Handle_t *handle, const char *command, const char *expected_response, char *out_buf, uint16_t out_len, uint32_t timeout_ms);

/**
 * @brief Gửi lệnh AT và đợi phản hồi đơn giản (chỉ trả về trạng thái)
 */
SIM_Status_t SIM_SendATCommand(SIM_Handle_t *handle, const char *command, const char *expected_response, uint32_t timeout_ms);

/* --- Extended Functions --- */
SIM_Status_t SIM_TestAlive(SIM_Handle_t *handle);
SIM_Status_t SIM_EchoOff(SIM_Handle_t *handle);
SIM_Status_t SIM_GetIMEI(SIM_Handle_t *handle, char *out, uint16_t max_len);
SIM_Status_t SIM_GetCSQ(SIM_Handle_t *handle, int *rssi, int *ber);
SIM_Status_t SIM_CheckSIMCard(SIM_Handle_t *handle);
SIM_Status_t SIM_GetNetworkReg(SIM_Handle_t *handle, int *stat);
SIM_Status_t SIM_GetOperator(SIM_Handle_t *handle, char *out, uint16_t max_len);
SIM_Status_t SIM_SendSMS(SIM_Handle_t *handle, const char *phone, const char *msg);
SIM_Status_t SIM_ReadSMS(SIM_Handle_t *handle, int index, char *out_phone, char *out_time, char *out_msg, uint16_t max_len);
SIM_Status_t SIM_DeleteSMS(SIM_Handle_t *handle, int index);
SIM_Status_t SIM_PowerDown(SIM_Handle_t *handle);

/**
 * @brief Điều khiển chế độ ngủ của Modem (Light Sleep)
 * @param enable: true để cho phép ngủ (DTR High), false để thức dậy (DTR Low)
 */
SIM_Status_t SIM_SetSleepMode(SIM_Handle_t *handle, bool enable);
 
 /**
  * @brief Lấy vị trí từ cột sóng (LBS)
  * @param lat Pointer nhận vĩ độ
  * @param lon Pointer nhận kinh độ
  */
 SIM_Status_t SIM_GetLBSPosition(SIM_Handle_t *handle, float *lat, float *lon,
                                 uint8_t *y, uint8_t *mon, uint8_t *d,
                                 uint8_t *h, uint8_t *min, uint8_t *s);


/**
 * @brief Hàm xử lý dữ liệu nhận được từ UART (Gọi từ BSP UART Callback)
 */
void SIM_UART_Receive_Handler(SIM_Handle_t *handle, uint8_t *data, uint16_t size);

#endif /* __SIM_A7670C_H__ */
