/**
 * @file key_hal.h
 * @brief Hardware Abstraction Layer of the Independent Key and Matrix Key Detection Module
 * @note Target MCU: STC89C516RD+ (51-family)
 *
 * 功能：
 *  - 独立按键检测：
 *      - 支持最多 16 个独立按键的检测
 *      - 支持事件：短按、1阶段长按、2阶段长按、3阶段长按、双击、组合键、释放检测
 *      - 可配置扫描间隔（IND_SCAN_INTERVAL_MS）、长按阈值（IND_LPRESS1_MS, LPRESS2_MS, LPRESS3_MS）、最长双击间隔阈值（IND_DOUBLE_CLICK_MAX_MS）
 *      - 软件去抖动
 *      - 定时器扫描 + 按键状态机实现
 *      - 使用回调函数对独立按键事件进行处理
 *
 * 使用方法：
 *  - 独立按键检测：
 *      - 在定时器中断或主循环中以 10ms 周期调用 ();
 * 
 * @version 1.0.0
 * @author ForeverMySunyu
 * @date 2025-12-08
 */

#ifndef _KEY_HAL_H_
#define _KEY_HAL_H_

#include <stdint.h>
#include <stdbool.h>
#include "../core/stc89.h"
#include "../config/configuration.h"
#include "../bsp/key_bsp.h"



/* ========== 每个按键的状态数据结构体 ========== */


/* ============= 独立按键事件类型 ============= */
typedef enum {
    KEY_EVENT_NONE = 0,
    KEY_EVENT_SHORT_PRESS,      /* 短按 */
    KEY_EVENT_LPRESS1,          /* 1阶段长按 */
    KEY_EVENT_LPRESS2,          /* 2阶段长按 */
    KEY_EVENT_LPRESS3,          /* 3阶段长按 */
    KEY_EVENT_DOUBLE_CLICK,     /* 双击 */
    KEY_EVENT_COMBINED_CLICK,   /* 组合键 */
    KEY_RELEASE
} key_event_t;

/* ================================= 函数定义 ================================= */

void key_hal_init(void);        //！ hal 按键初始化函数，包含 ind_key_hal_init() 和 mat_key_hal_init()
void ind_key_hal_init(void);    //！ hal 独立按键初始化函数
void mat_key_hal_init(void);    //！ hal 矩阵按键初始化函数

uint16_t ind_key_get_pressed_mask(void);    //! 获取当前处于 PRESSED 状态的按键掩码
void ind_key_scan(void);        //！ 独立按键扫描函数，处理独立按键状态机，必须周期性调用：以 IND_SCAN_INTERVAL_MS 为周期调用（通常放在定时器中断）

#endif  /* _KEY_HAL_H_ */