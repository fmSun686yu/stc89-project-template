/**
 * @file    segment_hal.C
 * @brief   数码管显示模块的 hal 驱动头文件
 * @details 本文件用于数码管显示模块的硬件抽象层驱动
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-21
 */

#ifndef _SEGMENT_HAL_H_
#define _SEGMENT_HAL_H_

/* ================== API 函数声明区域 ================== */
void segment_hal_init(void);        //! 数码管显示初始化函数
void segment_set_number(uint8_t index, uint8_t value);      //! 设置要在 index 位上显示的整数数值
void segment_scan_task(void);       //! 动态扫描刷新函数（需周期调用）

#endif      /* _SEGMENT_HAL_H_ */