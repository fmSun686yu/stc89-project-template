/**
 * @file matrix_key_bsp.h
 * @brief Board Support Package Part of the Matrix Key Detection Module
 * @note Target MCU: STC89C516RD+ (51-family)
 *
 * 功能：
 *  - 针对硬件电路，对矩阵按键相关参数进行初始化
 *  - 声明读取按键连接的 I/O 口的电平的函数
 *  - 支持 8*8 的矩阵按键检测
 * 
 * @version: 1.0.0
 * @author: ForeverMySunyu
 * @date: 2025-12-17
 */

#ifndef _MATRIX_KEY_BSP_H_
#define _MATRIX_KEY_BSP_H_

#include <stdint.h>

/* ================= 函数声明区域 ================= */

void key_init_bsp(void);            //! BSP 矩阵按键初始化函数
void key_set_row(uint8_t row);      //! 设置第 row 行为低电平，其余行为高电平
uint8_t key_read_columns(void);     //! 读取所有列电平

#endif     /* _MATRIX_KEY_BSP_H_ */