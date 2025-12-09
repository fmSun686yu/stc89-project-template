/**
 * @file name: key_bsp.h
 * @brief Board Support Package Part of the Independent Key and Matrix Key Detection Module
 * @note Target MCU: STC89C516RD+ (51-family)
 *
 * 功能：
 *  - 针对硬件电路，对独立按键和矩阵按键相关参数进行初始化
 *  - 声明读取按键连接的 I/O 口的电平的函数
 *
 * 使用方法：
 *  - 在系统初始化时调用 key_init(void);
 *  - 在 hal 中的按键扫描函数中调用 key_level_read(uint8_t key_id); 以获取 I/O 口电平高低
 * 
 * @version: 1.0.0
 * @author: ForeverMySunyu
 * @date: 2025-12-08
 */

#ifndef _KEY_BSP_H_
#define _KEY_BSP_H_

#include <stdint.h>
#include <stdbool.h>
#include "../core/stc89.h"
#include "../config/configuration.h"

/* ============= API 函数声明 ============= */

void key_bsp_init(void);        // bsp 按键初始化函数，包含 ind_key_bsp_init() 和 mat_key_bsp_init()
void ind_key_bsp_init(void);    // bsp 独立按键初始化函数
void mat_key_bsp_init(void);    // bsp 矩阵按键初始化函数
bool ind_key_level_read(uint8_t key_id);    // 独立按键是否被按下检测函数


#endif  // _KEY_BSP_H_