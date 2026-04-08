#include "storage_manager.h"
#include "log.h"
#include <string.h>

/**
 * @brief Kiểm tra số lượng byte 0x00 trong Tracking Sector bằng Binary Search
 * @return Số lượng byte 0x00 (từ 0 đến 4096)
 */
static uint32_t Find_Last_Mark(W25Q_Handle_t *flash, uint32_t tracking_addr) {
    uint8_t val;
    int32_t low = 0, high = 4095;
    uint32_t last_zero_pos = 0;

    /* Kiểm tra nhanh biên */
    W25Q_Read(flash, tracking_addr, &val, 1);
    if (val == 0xFF) return 0;
    
    W25Q_Read(flash, tracking_addr + 4095, &val, 1);
    if (val != 0xFF) return 4096;

    while (low <= high) {
        int32_t mid = low + (high - low) / 2;
        W25Q_Read(flash, tracking_addr + mid, &val, 1);
        
        if (val != 0xFF) {
            last_zero_pos = mid + 1;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return last_zero_pos;
}

/**
 * @brief Tìm bản ghi cuối cùng trong một vùng nghi vấn bằng Binary Search dựa trên Magic Word
 */
static uint32_t Find_Last_Valid_Record(W25Q_Handle_t *flash, Storage_Config_t *config, uint32_t start_idx, uint32_t end_idx) {
    uint32_t magic;
    uint32_t last_valid = start_idx;
    int32_t low = start_idx, high = end_idx;

    while (low <= high) {
        int32_t mid = low + (high - low) / 2;
        W25Q_Read(flash, config->start_addr + mid * config->obj_size, (uint8_t*)&magic, 4);
        
        if (magic == config->magic_word) {
            last_valid = mid + 1;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return last_valid;
}

Storage_Status_t Storage_Init(W25Q_Handle_t *flash, Storage_Config_t *config, Storage_Context_t *ctx) {
    if (!flash || !config || !ctx) return STORAGE_ERROR;

    uint32_t byte_capacity = config->end_addr - config->start_addr;
    ctx->total_capacity = byte_capacity / config->obj_size;
    ctx->current_index = 0;
    ctx->is_initialized = true;

    return STORAGE_OK;
}

Storage_Status_t Storage_Recover(W25Q_Handle_t *flash, Storage_Config_t *config, Storage_Context_t *ctx) {
    if (!ctx->is_initialized) return STORAGE_ERROR;

    LOG_INFO("Storage: Starting recovery for region 0x%08X...", config->start_addr);

    /* Vòng 1: Tìm mốc thô trên Tracking Sector */
    uint32_t marks = Find_Last_Mark(flash, config->tracking_addr);
    
    /* Vòng 2: Khoanh vùng nghi vấn (N_Step bản ghi) */
    uint32_t search_start = marks * config->n_step;
    uint32_t search_end = search_start + config->n_step - 1;
    
    if (search_end >= ctx->total_capacity) search_end = ctx->total_capacity - 1;

    ctx->current_index = Find_Last_Valid_Record(flash, config, search_start, search_end);
    
    LOG_INFO("Storage: Recovery complete. Current Index: %d", ctx->current_index);
    return STORAGE_OK;
}

Storage_Status_t Storage_Append(W25Q_Handle_t *flash, Storage_Config_t *config, Storage_Context_t *ctx, void *data) {
    if (!ctx->is_initialized) return STORAGE_ERROR;

    /* Kiểm tra tràn bộ nhớ (Simple Linear for now, could be Circular) */
    if (ctx->current_index >= ctx->total_capacity) {
        LOG_WARN("Storage: Region full! Auto-formatting...");
        Storage_Format(flash, config, ctx);
    }

    uint32_t addr = config->start_addr + ctx->current_index * config->obj_size;
    
    /* Ghi dữ liệu thực tế (Đã xử lý Page Boundary trong W25Q_Write) */
    if (W25Q_Write(flash, addr, (uint8_t*)data, config->obj_size) != W25Q_OK) {
        return STORAGE_ERROR;
    }

    /* Đánh dấu vào Tracking Sector nếu đến bước N */
    ctx->current_index++;
    if (ctx->current_index % config->n_step == 0) {
        uint32_t mark_pos = (ctx->current_index / config->n_step) - 1;
        if (mark_pos < 4096) {
            uint8_t zero = 0x00;
            W25Q_Write(flash, config->tracking_addr + mark_pos, &zero, 1);
        }
    }

    return STORAGE_OK;
}

Storage_Status_t Storage_Read(W25Q_Handle_t *flash, Storage_Config_t *config, uint32_t index, void *buffer) {
    uint32_t addr = config->start_addr + index * config->obj_size;
    if (W25Q_Read(flash, addr, (uint8_t*)buffer, config->obj_size) != W25Q_OK) {
        return STORAGE_ERROR;
    }
    return STORAGE_OK;
}

Storage_Status_t Storage_Format(W25Q_Handle_t *flash, Storage_Config_t *config, Storage_Context_t *ctx) {
    LOG_INFO("Storage: Formatting region 0x%08X...", config->start_addr);
    
    /* Xóa Tracking Sector */
    W25Q_EraseSector(flash, config->tracking_addr);
    
    /* Xóa vùng dữ liệu (xóa từng sector) */
    for (uint32_t addr = config->start_addr; addr < config->end_addr; addr += 4096) {
        W25Q_EraseSector(flash, addr);
    }
    
    ctx->current_index = 0;
    return STORAGE_OK;
}
