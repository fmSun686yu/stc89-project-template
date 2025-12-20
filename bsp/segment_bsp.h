/**
 * @file    segment_bsp.h
 * @brief   数码管显示模块的 bsp 驱动头文件
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-19
 *
 * @details 本文件用于数码管显示模块的板级驱动
 */

#ifndef _SEGMENT_BSP_H_
#define _SEGMENT_BSP_H_

#include <stdint.h>

/* ================== API 函数声明区域 ================== */
void segment_bsp_init(void);        //! 数码管显示初始化函数
void segment_write_data(uint8_t seg_data);        //! 输出段码数据
void segment_select_digit(uint8_t index);           //! 选择显示的数码管位

#endif      /* _SEGMENT_BSP_H_ */