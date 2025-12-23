/**
 * @file    segment_hal.C
 * @brief   数码管显示模块的 hal 驱动头文件
 * @details 本文件用于数码管显示模块的硬件抽象层驱动
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-22
 */

#ifndef _SEGMENT_HAL_H_
#define _SEGMENT_HAL_H_

#include <stdint.h>

/* ================== API 函数声明区域 ================== */
void segment_init_hal(void);        //! 数码管显示初始化函数
void clear_seg_buffer(void);        //!
void segment_set_int_number(int32_t value);      //! 设置要显示的**整数**数值
void segment_set_float_number(float value, uint8_t decimal_places);         //! 设置要显示的**浮点数**数值
void segment_scan_task(void);       //! 动态扫描刷新函数（需周期调用）

#endif      /* _SEGMENT_HAL_H_ */