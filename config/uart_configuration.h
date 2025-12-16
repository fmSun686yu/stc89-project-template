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

/**
 * @def UART_MODE
 * @brief UART 的工作方式配置
 * @details 值：0 - 方式0，同步移位串行方式，移位寄存器
 *              1 - 方式1，8位UART，波特率可变
 *              2 - 方式2，9位UART
 *              3 - 方式3，9位UART，波特率可变
 */
#define UART_MODE   1

/**
 * @def SM2_C
 * @brief UART 的 SCON 寄存器的 SM2 位配置（允许方式2或方式3多机通信控制位）
 * @details 值：0 - 非多机通信
 *              1 - 允许多机通信
 */
#define SM2_C   0

/**
 * @def REN_C
 * @brief UART 的 SCON 寄存器的 REN 位配置（允许/禁止串行接收控制位）
 * @details 值：0 - 禁止串行接收状态
 *              1 - 允许串行接收状态
 */
#define REN_C   1

/**
 * @def SMOD_C
 * @brief UART 的 PCON 寄存器的 SMOD 位配置（波特率选择位）
 * @details 值：0 - 波特率不加倍
 *              1 - 波特率加倍
 */
#define SMOD_C  0

/**
 * @def SMOD0_C
 * @brief UART 的 PCON 寄存器的 SMOD0 位配置（帧错误检测有效控制位）
 * @details 值：0 - SCON 寄存器中的 SM0/FE 位用于 SM0 功能，和 SM1 一起指定串行口的工作方式
 *              1 - SCON 寄存器中的 SM0/FE 位用于 FE （帧错误检测）功能
 */
#define SMOD0_C 0

#endif  /* _UART_CONFIGURATION_H_ */