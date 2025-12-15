/**
 *******************************************************************************************
 * @file    uart_configuration.h
 * @brief   51单片机工程全局配置文件 — 适用于 STC89C516RD+ 型号单片机并兼容 STC89 系列单片机
 * @version 1.1.0
 * @author  ForeverMySunyu
 * @date    2025-12-15
 *******************************************************************************************
*/

#ifndef _UART_CONFIGURATION_H_
#define _UART_CONFIGURATION_H_

/** 
 * @def UART_BAUDRATE
 * @brief UART 波特率设置
 */
#define UART_BAUDRATE       28800    // UART 通信波特率

/**
 * @def TIMER2_RCLK
 * @brief 接收时钟标志，RCLK 控制位
 * @details 值：0 - 将定时器1的溢出脉冲作为串行口模式1和模式3的接受时钟
 *              1 - 将定时器2的溢出脉冲作为串行口模式1和模式3的接受时钟
 */
#define TIMER2_RCLK       0

/**
 * @def TIMER2_TCLK
 * @brief 发送时钟标志，TCLK 控制位
 * @details 值：0 - 将定时器1的溢出脉冲作为串行口模式1和模式3的发送时钟
 *              1 - 将定时器2的溢出脉冲作为串行口模式1和模式3的发送时钟
 */
#define TIMER2_TCLK       0

#endif  /* _UART_CONFIGURATION_H_ */