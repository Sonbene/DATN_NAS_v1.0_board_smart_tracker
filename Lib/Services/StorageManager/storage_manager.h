#ifndef STORAGE_MANAGER_H
#define STORAGE_MANAGER_H

#include "w25q32.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Định nghĩa các sự kiện sau khi hoàn tất thao tác bộ nhớ
 */
typedef enum {
    STORAGE_EVENT_WRITE_DONE = 0,
    STORAGE_EVENT_READ_DONE,
    STORAGE_EVENT_ERROR
} Storage_Event_t;

/**
 * @brief Hàm callback để người dùng tự định nghĩa cách báo cho Task khác
 * (Ví dụ: xTaskNotify, xSemaphoreGive, hoặc set Event Group...)
 */
typedef void (*Storage_Callback_t)(Storage_Event_t event, void* user_data);

/**
 * @brief Cấu hình cho một vùng lưu trữ chuyên dụng
 */
typedef struct {
    uint32_t start_addr;        /* Địa chỉ bắt đầu vùng dữ liệu (phải là bội số 4096) */
    uint32_t end_addr;          /* Địa chỉ kết thúc vùng dữ liệu */
    uint32_t tracking_addr;     /* Địa chỉ Tracking Sector (phải là bội số 4096) */
    uint16_t obj_size;          /* Kích thước mỗi bản ghi (Byte) */
    uint32_t magic_word;        /* Mã nhận diện bản ghi hợp lệ (4 byte đầu) */
    uint16_t n_step;            /* Sau bao nhiêu bản ghi thì ghi 1 cell 0x00 vào Tracking Sector */
    
    /* Hook để báo cho Task khác khi xong việc */
    Storage_Callback_t callback; 
    void *user_data;            /* Tham số tùy chọn truyền vào callback */
} Storage_Config_t;

/**
 * @brief Biến RAM theo dõi trạng thái Runtime của vùng lưu trữ
 */
typedef struct {
    uint32_t current_index;     /* Chỉ số bản ghi tiếp theo sẽ ghi (0, 1, 2...) */
    uint32_t total_capacity;    /* Tổng số bản ghi tối đa vùng này chứa được */
    bool is_initialized;        /* Đã được khôi phục/khởi tạo thành công */
} Storage_Context_t;

typedef enum {
    STORAGE_OK = 0,
    STORAGE_ERROR,
    STORAGE_FULL,
    STORAGE_NOT_FOUND
} Storage_Status_t;

/**
 * @brief Khởi tạo tham số vùng lưu trữ
 */
Storage_Status_t Storage_Init(W25Q_Handle_t *flash, Storage_Config_t *config, Storage_Context_t *ctx);

/**
 * @brief Khôi phục vị trí ghi cuối cùng từ Flash (Dùng Binary Search)
 */
Storage_Status_t Storage_Recover(W25Q_Handle_t *flash, Storage_Config_t *config, Storage_Context_t *ctx);

/**
 * @brief Ghi một bản ghi mới vào vùng lưu trữ
 * @param data Con trỏ đến struct dữ liệu (phải có magic_word ở đầu)
 */
Storage_Status_t Storage_Append(W25Q_Handle_t *flash, Storage_Config_t *config, Storage_Context_t *ctx, void *data);

/**
 * @brief Đọc bản ghi tại một chỉ số bất kỳ
 */
Storage_Status_t Storage_Read(W25Q_Handle_t *flash, Storage_Config_t *config, uint32_t index, void *buffer);

/**
 * @brief Xóa sạch dữ liệu của vùng (Erase data sectors and tracking sector)
 */
Storage_Status_t Storage_Format(W25Q_Handle_t *flash, Storage_Config_t *config, Storage_Context_t *ctx);

#endif /* STORAGE_MANAGER_H */
