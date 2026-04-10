#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    uint8_t *buffer;
    uint32_t size;
    uint32_t head;
    uint32_t tail;
    uint32_t count;
} RingBuffer_t;

/**
 * @brief Khởi tạo Ring Buffer
 */
void RingBuffer_Init(RingBuffer_t *rb, uint8_t *mem, uint32_t size);

/**
 * @brief Ghi 1 byte vào buffer
 */
bool RingBuffer_Write(RingBuffer_t *rb, uint8_t data);

/**
 * @brief Đọc 1 byte từ buffer
 */
bool RingBuffer_Read(RingBuffer_t *rb, uint8_t *data);

/**
 * @brief Đọc nhiều byte từ buffer
 */
uint32_t RingBuffer_ReadMulti(RingBuffer_t *rb, uint8_t *data, uint32_t len);

/**
 * @brief Đọc 1 dòng từ buffer (kết thúc bằng \n)
 */
bool RingBuffer_ReadLine(RingBuffer_t *rb, char *line, uint32_t max_len);

/**
 * @brief Xóa sạch buffer
 */
void RingBuffer_Flush(RingBuffer_t *rb);

/**
 * @brief Đọc nhiều byte từ buffer mà không xóa dữ liệu (Peek)
 */
bool RingBuffer_Search(RingBuffer_t *rb, const char *str);

/**
 * @brief Đọc nhiều byte từ buffer mà không xóa dữ liệu (Peek)
 */
uint32_t RingBuffer_PeekMulti(RingBuffer_t *rb, uint8_t *data, uint32_t len);

#endif /* __RING_BUFFER_H__ */
