/**
 * @file matrix_key_bsp.c
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

#include "matrix_key_bsp.h"
#include "../config/matrix_key_configuration.h"

/**
 * @brief  BSP 矩阵按键初始化函数
 */
void key_bsp_init(void)
{
    
}

/**
 * @brief 设置第 row 行为低电平，其余为高电平
 * @param row 行号
 * @return None
 */
void key_set_row(uint8_t row)
{
    ROW_PORT = ~(1 << row);
}

/**
 * @brief 读取列电平
 * @param None
 * @return 8位列电平
 */
uint8_t key_read_columns(void)
{
    return COL_PORT;
}