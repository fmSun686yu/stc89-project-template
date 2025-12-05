/**
 **********************************************************************
 * @file    configuration.h
 * @brief   51单片机工程全局配置文件 — 适用于 STC89C516RD+ 型号单片机并兼容 STC89 系列单片机
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-05
 **********************************************************************
*/

#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

/**
 * @brief 单片机外部晶振频率
 *        常见值：11.0592MHz、12MHz、22.1184MHz 等
 * @note 同一频率不同单位的定义，二者需相互匹配
 */
#define FOSC_MHZ  11.0592    // 单位 MHz
#define FOSC_HZ  11059200    // 单位 Hz

/**
 * @brief 定义单片机1个机器周期包含多少个晶振周期
 *        值：12: 12T 工作模式, 6: 6T 工作模式
 */
#define MACHINE_CYCLE  12

/** 
 * @brief UART 波特率设置
 */
#define UART_BAUDRATE  28800    // UART 通信波特率

#endif  // _CONFIGURATION_H_