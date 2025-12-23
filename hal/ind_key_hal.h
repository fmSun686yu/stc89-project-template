/**
 * @file ind_key_hal.h
 * @brief Hardware Abstraction Layer of the Independent Key and Matrix Key Detection Module
 * @note Target MCU: STC89C516RD+ (51-family)
 *
 * 功能：
 *  - 独立按键检测：
 *      - 支持最多 16 个独立按键的检测
 *      - 支持事件：短按、1阶段长按、2阶段长按、3阶段长按、双击、组合键、释放检测
 *      - 可配置扫描间隔（SCAN_INTERVAL_MS）、长按阈值（LPRESS1_MS, LPRESS2_MS, LPRESS3_MS）、最长双击间隔阈值（DOUBLE_CLICK_MAX_MS）
 *      - 软件去抖动
 *      - 定时器扫描 + 按键状态机实现
 *
 * 使用方法：
 *  - 独立按键检测：
 *      - 在定时器中断或主循环中以 10ms 周期调用 key_scan();
 * 
 * @version 1.1.0
 * @author ForeverMySunyu
 * @date 2025-12-11
 */

#ifndef _IND_KEY_HAL_H_
#define _IND_KEY_HAL_H_

#include <stdint.h>
#include <stdbool.h>

/* ============= 按键事件类型定义 ============= */
typedef enum
{
    KEY_EVENT_NONE = 0,
    KEY_EVENT_SHORT_PRESS,      /* 短按 */
    KEY_EVENT_LPRESS1,          /* 1阶段长按 */
    KEY_EVENT_LPRESS2,          /* 2阶段长按 */
    KEY_EVENT_LPRESS3,          /* 3阶段长按 */
    KEY_EVENT_DOUBLE_CLICK,     /* 双击 */
    KEY_EVENT_COMBINED_CLICK    /* 组合键 */
} key_event_t;

/* ================ 按键状态定义 ================ */
typedef enum
{
    KEY_STATE_IDLE = 0,         //! 空闲状态
    KEY_STATE_PRE_DEBOUNCE,     //! 按下消抖状态
    KEY_STATE_PRESS,            //! 普通按下状态
    KEY_STATE_LPRESS1,          //! 1阶段长按状态
    KEY_STATE_LPRESS2,          //! 2阶段长按状态
    KEY_STATE_LPRESS3,          //! 3阶段长按状态
    KEY_STATE_COMBINED_CLICK,   //! 多个键同时按下状态
    KEY_STATE_REL_DEBOUNCE,     //! 释放消抖状态
    KEY_STATE_WAIT_PRE_AG       //! 等待双击状态
} key_state_t;

/* =================== 全局按键事件标志变量结构体（主循环中检查，并调用对应的按键事件处理函数） =================== */
struct
{
    uint8_t key_id;             //! 按键 ID
    key_event_t key_event;      //! 按键事件
    key_state_t key_state;      //! 当前按键所处状态
    uint16_t pressed_key_mask;  //! 被按下按键的掩码（用于组合键检测与处理）
} key_event_flag;

/* ================================= API 函数声明 ================================= */
void key_init_hal(void);        //! hal 按键初始化函数
void key_clear_event(void);     //! 全局按键事件标志变量清除函数

#endif  /* _IND_KEY_HAL_H_ */