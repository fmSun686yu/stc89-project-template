/**
 * @file matrix_key_hal.h
 * @brief Hardware Abstraction Layer of the Matrix Key and Matrix Key Detection Module
 * @note Target MCU: STC89C516RD+ (51-family)
 *
 * 功能：
 * - 矩阵按键检测：
 *     - 支持 8*8 矩阵按键的检测
 *     - 支持事件：短按、释放检测
 *     - 可配置扫描间隔（SCAN_INTERVAL_MS）和消抖时长（DEBOUNCE_MS）
 *     - 软件去抖动
 *     - 定时器扫描 + 按键状态机实现
 *
 * 使用方法：
 * - 在定时器中断或主循环中以 10ms 周期调用 matrix_key_scan();
 * 
 * @version 1.0.0
 * @author ForeverMySunyu
 * @date 2025-12-17
 */

#ifndef _MATRIX_KEY_HAL_H_
#define _MATRIX_KEY_HAL_H_

#include <stdint.h>
#include <stdbool.h>

/* ================ 按键状态定义 ================ */
typedef enum
{
    KEY_STATE_IDLE = 0,         //! 空闲状态
    KEY_STATE_PRE_DEBOUNCE,     //! 按下消抖状态
    KEY_STATE_PRESS,            //! 按下状态
    KEY_STATE_REL_DEBOUNCE,     //! 释放消抖状态
} key_state_t;

/* =================== 全局按键事件标志变量结构体（主循环中检查，并调用对应的按键事件处理函数） =================== */
struct
{
    uint8_t key_id;             //! 按键 ID （=行号*列号+列号）
    bool key_press;             //! 按下事件触发标志
    key_state_t key_state;      //! 当前按键所处状态
} key_event_flag;

/* ============================== API 函数声明区 ============================== */
void key_init_hal(void);            //! HAL 矩阵按键初始化函数
void key_clear_event(void);     //! 全局按键事件标志变量清除函数

#endif /* _MATRIX_KEY_HAL_H_ */