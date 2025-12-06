/**
 * @file key_hal.h
 *
 * @brief Independent Key and Matrix Key Detection Modules
 * Hardware Abstraction Layer
 * Target MCU: STC89C516RD+ (51-family)
 *
 * 功能：
 *  - 支持最多 10 个独立按键的检测，使用 KEY_COUNT 设置需要检测的独立按键个数
 *  - 支持事件：短按、1阶段长按、2阶段长按、3阶段长按、双击、组合键、释放检测
 *  - 可配置扫描间隔（SCAN_INTERVAL_MS）、长按阈值（LPRESS_MS1, LPRESS_MS2, LPRESS_MS3）、最长双击间隔阈值（DOUBLE_CLICK_MAX_MS）
 *  - 软件去抖动
 *  - 定时器扫描 + 按键状态机实现
 *
 * 使用方法：
 *  - 在系统初始化时调用 key_init();
 *  - 在定时器中断或主循环中以 10ms 周期调用 key_scan();
 *  - 在需要读取事件处调用 key_getevent(key_id);
 *  - 或通过 key_getevent_all(events_array) 批量获取所有键事件
 * 
 * @version 1.0.0
 * @author ForeverMySunyu
 * @date 2025-12-06
 */

#ifndef _KEY_HAL_H_
#define _KEY_HAL_H_

#include <stdint.h>
#include "../core/delay.h"

/* ========== 配置区（按需调整） ========== */

/* 按键数量 */
#define KEY_COUNT  10

/* 扫描间隔（ms），要求 key_scan() 被以此间隔调用 */
#define SCAN_INTERVAL_MS  10    /* 默认 10 ms */

/* 去抖时间（ms），建议 20~50 ms */
#define DEBOUNCE_MS  30

/* 1阶段长按阈值，可通过修改宏调整（单位：ms） */
#define LPRESS_MS1  3000  /* 3 秒长按事件 */
/* 2阶段长按阈值，可通过修改宏调整（单位：ms） */
#define LPRESS_MS2  6000  /* 6 秒长按事件 */
/* 3阶段长按阈值，可通过修改宏调整（单位：ms） */
#define LPRESS_MS3  10000  /* 10 秒长按事件 */

/* 最大双击间隔（释放后到第二次按下）（单位：ms） */
#define DOUBLE_CLICK_MAX_MS  250

/* 最大按键数上限保护（不超过 10）*/
#if (HAL_KEY_NUM_KEYS > 10)
#error "KEY_COUNT too large (max 10)"
#endif

/* ============= 事件类型定义 ============= */
typedef enum {
    KEY_EVENT_NONE = 0,
    KEY_EVENT_PRESS,       /* 按下（去抖稳定后的第一次按下） */
    KEY_EVENT_RELEASE,     /* 释放（去抖稳定后的释放） */
    KEY_EVENT_SHORT,       /* 短按（按下 -> 释放，且持续时间 < LONG_PRESS_MS1） */
    KEY_EVENT_LONG_1,     /* 到达 LONG_PRESS_MS1（例如 3s） */
    KEY_EVENT_LONG_2      /* 到达 LONG_PRESS_MS2（例如 6s） */
} KEY_EVENT;

/* ============= API 函数声明 ============= */

void key_scan(void);        // 按键扫描函数，必须周期性调用：以 SCAN_INTERVAL_MS 为周期调用（通常放在定时器中断）
KEY_EVENT key_getevent(uint8_t key_id);        // 获取并清除指定按键的事件（key_id: 0 .. KEY_COUNT-1）
void key_getevent_all(KEY_EVENT events[]);     // 批量获取所有按键事件并清除（events 数组长度必须 >= KEY_COUNT）

 #endif  // _KEY_HAL_H_