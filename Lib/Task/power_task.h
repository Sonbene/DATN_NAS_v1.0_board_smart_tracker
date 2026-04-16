#ifndef __POWER_TASK_H__
#define __POWER_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "cmsis_os.h"
#include <stdbool.h>
#include <stdint.h>

/* ========================================================================================
 * SECTION: Power Task Event Group Bits
 * ========================================================================================
 * Theo yêu cầu: khi task nào chạy thì CLEAR bit, khi rảnh (dừng) thì SET bit.
 * Tất cả các task đều SET bit thì hệ thống mới được phép vào trạng thái ngủ.
 */
#define POWER_BIT_SIM       (1 << 0)
#define POWER_BIT_GPS       (1 << 1)
#define POWER_BIT_SYS_MGR   (1 << 2)
#define POWER_BITS_ALL      (POWER_BIT_SIM | POWER_BIT_GPS | POWER_BIT_SYS_MGR)

/**
 * @brief  Khởi tạo Power Task và Event Group.
 */
void Power_Task_Init(void);

/**
 * @brief  Cập nhật trạng thái bận/rảnh của một Task.
 * @param  task_bit: Bit của task (ví dụ: POWER_BIT_SIM)
 * @param  is_idle:  true nếu Task rảnh (SET bit), false nếu Task đang bận (CLEAR bit).
 */
void Power_Task_SetState(uint32_t task_bit, bool is_idle);

#ifdef __cplusplus
}
#endif

#endif /* __POWER_TASK_H__ */
