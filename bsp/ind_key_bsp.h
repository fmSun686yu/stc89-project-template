/**
 * @file name: ind_key_bsp.h
 * @brief Board Support Package Part of the Independent Key Detection Module
 * @note Target MCU: STC89C516RD+ (51-family)
 *
 * 功能：
 *  - 针对硬件电路，对独立按键相关参数进行初始化
 *  - 声明读取按键连接的 I/O 口的电平的函数
 *
 * 使用方法：
 *  - 在系统初始化时调用 key_bsp_init(void);
 *  - 在 hal 中的按键扫描函数中调用 key_pressed_detect(uint8_t key_id); 以检测按键是否被按下
 * 
 * @version: 1.1.0
 * @author: ForeverMySunyu
 * @date: 2025-12-11
 */

#ifndef _IND_KEY_BSP_H_
#define _IND_KEY_BSP_H_

#include <stdint.h>
#include <stdbool.h>

/* ============= API 函数声明 ============= */

void key_init_bsp(void);        // bsp 按键初始化函数
bool key_pressed_detect(uint8_t key_id);    // 按键是否被按下检测函数

#endif  // _IND_KEY_BSP_H_