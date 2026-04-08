#include "storage_manager.h"
#include "log.h"
#include <string.h>

/**
 * @brief Tìm kiếm nhị phân trên Tracking Sector để xác định số lượng mốc (marks) đã ghi.
 * 
 * Mỗi byte 0x00 trong Tracking Sector đánh dấu rằng đã có n_step bản ghi được lưu.
 * Hàm này tìm vị trí byte 0xFF đầu tiên (vùng chưa ghi) để biết ta đang ở "trang" nào.
 * 
 * @param flash Handle của chip Flash
 * @param tracking_addr Địa chỉ bắt đầu của Tracking Sector (4KB)
 * @return Số lượng byte 0x00 đã tìm thấy (tương ứng với số cụm n_step đã ghi full)
 */
static uint32_t Find_Last_Mark(W25Q_Handle_t *flash, uint32_t tracking_addr) {
    uint8_t val;
    int32_t low = 0, high = 4095;
    uint32_t last_zero_pos = 0;

    /* Bước 1: Kiểm tra nhanh hai đầu biên để tối ưu */
    W25Q_Read(flash, tracking_addr, &val, 1);
    if (val == 0xFF) return 0; /* Sector trống hoàn toàn */
    
    W25Q_Read(flash, tracking_addr + 4095, &val, 1);
    if (val != 0xFF) return 4096; /* Sector đã đầy hoàn toàn */

    /* Bước 2: Tìm kiếm nhị phân điểm chuyển giao giữa 0x00 và 0xFF */
    while (low <= high) {
        int32_t mid = low + (high - low) / 2;
        W25Q_Read(flash, tracking_addr + mid, &val, 1);
        
        if (val != 0xFF) {
            /* Nếu thấy dữ liệu khác 0xFF, nghĩa là vùng này đã ghi, tiếp tục tìm bên phải */
            last_zero_pos = mid + 1;
            low = mid + 1;
        } else {
            /* Nếu thấy 0xFF, nghĩa là vùng này chưa ghi, tìm sang bên trái */
            high = mid - 1;
        }
    }
    return last_zero_pos;
}

/**
 * @brief Tìm kiếm nhị phân bản ghi hợp lệ cuối cùng trong một vùng dữ liệu cụ thể.
 * 
 * Dựa trên Magic Word ở đầu mỗi bản ghi để xác định bản ghi đó đã có dữ liệu thực hay chưa.
 * 
 * @param start_idx Chỉ số bản ghi bắt đầu tìm kiếm
 * @param end_idx Chỉ số bản ghi kết thúc tìm kiếm
 */
static uint32_t Find_Last_Valid_Record(W25Q_Handle_t *flash, Storage_Config_t *config, uint32_t start_idx, uint32_t end_idx) {
    uint32_t magic;
    uint32_t last_valid = start_idx;
    int32_t low = start_idx, high = end_idx;

    while (low <= high) {
        int32_t mid = low + (high - low) / 2;
        /* Đọc 4 byte đầu (Magic Word) của bản ghi ở giữa */
        W25Q_Read(flash, config->start_addr + mid * config->obj_size, (uint8_t*)&magic, 4);
        
        if (magic == config->magic_word) {
            /* Nếu khớp Magic Word, bản ghi này hợp lệ, tìm tiếp các bản ghi mới hơn ở bên phải */
            last_valid = mid + 1;
            low = mid + 1;
        } else {
            /* Nếu không khớp, bản ghi này trống hoặc lỗi, tìm ngược lại bên trái */
            high = mid - 1;
        }
    }
    return last_valid;
}

/**
 * @brief Khởi tạo thông số quản lý vùng nhớ trên RAM.
 */
Storage_Status_t Storage_Init(W25Q_Handle_t *flash, Storage_Config_t *config, Storage_Context_t *ctx) {
    if (!flash || !config || !ctx) return STORAGE_ERROR;

    /* Tính toán tổng số bản ghi vùng này có thể chứa */
    uint32_t byte_capacity = config->end_addr - config->start_addr;
    ctx->total_capacity = byte_capacity / config->obj_size;
    
    /* Mặc định bắt đầu từ 0, sau đó hàm Recover sẽ cập nhật lại */
    ctx->current_index = 0;
    ctx->is_initialized = true;

    return STORAGE_OK;
}

/**
 * @brief Khôi phục trạng thái ghi cuối cùng từ Flash sau khi khởi động.
 * 
 * Sử dụng cơ chế tìm kiếm nhị phân 2 lớp (Tracking Sector -> Data Region) 
 * để tránh việc phải quét tuần tự toàn bộ chip Flash, giúp startup cực nhanh.
 */
Storage_Status_t Storage_Recover(W25Q_Handle_t *flash, Storage_Config_t *config, Storage_Context_t *ctx) {
    if (!ctx->is_initialized) return STORAGE_ERROR;

    LOG_INFO("Storage: Starting recovery for region 0x%08X...", config->start_addr);

    /* Vòng 1: Tìm mốc thô trên Tracking Sector (Xác định trang hiện tại) */
    uint32_t marks = Find_Last_Mark(flash, config->tracking_addr);
    
    /* Vòng 2: Khoanh vùng nghi vấn (trong phạm vi N_Step bản ghi kể từ dấu mốc cuối) */
    uint32_t search_start = marks * config->n_step;
    uint32_t search_end = search_start + config->n_step - 1;
    
    /* Đảm bảo không tìm kiếm vượt quá tổng dung lượng vùng nhớ */
    if (search_end >= ctx->total_capacity) search_end = ctx->total_capacity - 1;

    /* Tìm chính xác vị trí trống tiếp theo trong vùng nghi vấn */
    ctx->current_index = Find_Last_Valid_Record(flash, config, search_start, search_end);
    
    LOG_INFO("Storage: Recovery complete. Current Index: %d", ctx->current_index);
    return STORAGE_OK;
}

/**
 * @brief Thêm một bản ghi dữ liệu mới vào Flash.
 */
Storage_Status_t Storage_Append(W25Q_Handle_t *flash, Storage_Config_t *config, Storage_Context_t *ctx, void *data) {
    if (!ctx->is_initialized) return STORAGE_ERROR;

    /* Nếu bộ nhớ đã đầy, thực hiện xóa sạch để ghi lại từ đầu (Vòng lặp đơn giản) */
    if (ctx->current_index >= ctx->total_capacity) {
        LOG_WARN("Storage: Region full! Auto-formatting...");
        Storage_Format(flash, config, ctx);
    }

    /* Tính địa chỉ ghi dựa trên index hiện tại */
    uint32_t addr = config->start_addr + ctx->current_index * config->obj_size;
    
    /* Ghi dữ liệu thực vào Flash (Thư viện W25Q đã xử lý chia nhỏ theo Page 256 byte) */
    if (W25Q_Write(flash, addr, (uint8_t*)data, config->obj_size) != W25Q_OK) {
        LOG_ERROR("Storage: Flash write error at 0x%08X", addr);
        /* NOTE: Báo lỗi nếu có callback được đăng ký */
        if (config->callback) config->callback(STORAGE_EVENT_ERROR, config->user_data);
        return STORAGE_ERROR;
    }

    /* Sau mỗi n_step bản ghi, ghi một byte 0x00 vào Tracking Sector để duy trì dấu vết */
    ctx->current_index++;
    if (ctx->current_index % config->n_step == 0) {
        uint32_t mark_pos = (ctx->current_index / config->n_step) - 1;
        if (mark_pos < 4096) {
            uint8_t zero = 0x00;
            W25Q_Write(flash, config->tracking_addr + mark_pos, &zero, 1);
        }
    }

    /* NOTE: Sau khi ghi xong và cập nhật Tracking, báo cho Task khác thông qua Callback */
    if (config->callback) {
        config->callback(STORAGE_EVENT_WRITE_DONE, config->user_data);
    }

    return STORAGE_OK;
}

/**
 * @brief Đọc bản ghi tại một chỉ số (index) bất kỳ.
 */
Storage_Status_t Storage_Read(W25Q_Handle_t *flash, Storage_Config_t *config, uint32_t index, void *buffer) {
    /* Tính toán địa chỉ của bản ghi cần đọc */
    uint32_t addr = config->start_addr + index * config->obj_size;
    if (W25Q_Read(flash, addr, (uint8_t*)buffer, config->obj_size) != W25Q_OK) {
        /* NOTE: Báo lỗi đọc cho Task khác */
        if (config->callback) config->callback(STORAGE_EVENT_ERROR, config->user_data);
        return STORAGE_ERROR;
    }

    /* NOTE: Báo hoàn tất đọc dữ liệu cho Task khác thông qua Callback */
    if (config->callback) {
        config->callback(STORAGE_EVENT_READ_DONE, config->user_data);
    }

    return STORAGE_OK;
}

/**
 * @brief Xóa toàn bộ vùng nhớ (bao gồm cả dữ liệu và thông tin theo dõi).
 */
Storage_Status_t Storage_Format(W25Q_Handle_t *flash, Storage_Config_t *config, Storage_Context_t *ctx) {
    LOG_INFO("Storage: Formatting region 0x%08X...", config->start_addr);
    
    /* Xóa sector theo dõi (về trạng thái 0xFF) */
    W25Q_EraseSector(flash, config->tracking_addr);
    
    /* Xóa tuần tự từng sector (4KB) trong vùng dữ liệu */
    for (uint32_t addr = config->start_addr; addr < config->end_addr; addr += 4096) {
        W25Q_EraseSector(flash, addr);
    }
    
    /* Reset lại chỉ số ghi về 0 */
    ctx->current_index = 0;
    return STORAGE_OK;
}

