#include "ring_buffer.h"
#include <string.h>

void RingBuffer_Init(RingBuffer_t *rb, uint8_t *mem, uint32_t size) {
    rb->buffer = mem;
    rb->size = size;
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
}

bool RingBuffer_Write(RingBuffer_t *rb, uint8_t data) {
    if (rb->count >= rb->size) return false;

    rb->buffer[rb->head] = data;
    rb->head = (rb->head + 1) % rb->size;
    rb->count++;
    return true;
}

bool RingBuffer_Read(RingBuffer_t *rb, uint8_t *data) {
    if (rb->count == 0) return false;

    *data = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % rb->size;
    rb->count--;
    return true;
}

uint32_t RingBuffer_ReadMulti(RingBuffer_t *rb, uint8_t *data, uint32_t len) {
    uint32_t read_bytes = 0;
    while (read_bytes < len && rb->count > 0) {
        RingBuffer_Read(rb, &data[read_bytes]);
        read_bytes++;
    }
    return read_bytes;
}

void RingBuffer_Flush(RingBuffer_t *rb) {
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
}

bool RingBuffer_ReadLine(RingBuffer_t *rb, char *line, uint32_t max_len) {
    if (rb == NULL || line == NULL || rb->count == 0) return false;

    /* Tìm kiếm ký tự \n */
    uint16_t n_pos = 0xFFFF;
    for (uint32_t i = 0; i < rb->count; i++) {
        uint32_t idx = (rb->tail + i) % rb->size;
        if (rb->buffer[idx] == '\n') {
            n_pos = i;
            break;
        }
    }

    if (n_pos == 0xFFFF) return false;

    /* Copy dòng ra line */
    uint32_t len_to_copy = (n_pos + 1 > max_len - 1) ? max_len - 1 : n_pos + 1;
    RingBuffer_ReadMulti(rb, (uint8_t*)line, len_to_copy);
    line[len_to_copy] = '\0';

    return true;
}

bool RingBuffer_Search(RingBuffer_t *rb, const char *str) {
    if (rb == NULL || str == NULL || rb->count == 0) return false;
    
    uint32_t len = strlen(str);
    if (len > rb->count) return false;
    
    for (uint32_t i = 0; i <= rb->count - len; i++) {
        bool found = true;
        for (uint32_t j = 0; j < len; j++) {
            uint32_t idx = (rb->tail + i + j) % rb->size;
            if (rb->buffer[idx] != (uint8_t)str[j]) {
                found = false;
                break;
            }
        }
        if (found) return true;
    }
    return false;
}

uint32_t RingBuffer_PeekMulti(RingBuffer_t *rb, uint8_t *data, uint32_t len) {
    if (rb == NULL || data == NULL || len == 0 || rb->count == 0) return 0;
    
    uint32_t read_len = (len < rb->count) ? len : rb->count;
    
    for (uint32_t i = 0; i < read_len; i++) {
        uint32_t idx = (rb->tail + i) % rb->size;
        data[i] = rb->buffer[idx];
    }
    
    return read_len;
}
