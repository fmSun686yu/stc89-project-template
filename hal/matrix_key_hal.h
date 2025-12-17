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



#endif /* _MATRIX_KEY_HAL_H_ */