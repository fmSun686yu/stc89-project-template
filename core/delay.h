/**
 **********************************************************************
 * @file    delay.h
 * @brief   粗略软件延时（busy-wait）接口 — 适用于 STC89C516RD+ 型号单片机并兼容 STC89 系列单片机
 *
 * @details
 *  - 提供四类延时接口（单位化）
 *      delay_10us(uint8_t n)  : 粗略延时 n * 10 us （仅 FOSC >= 11.0592 MHz 提供）
 *      delay_50us(uint8_t n)  : 粗略延时 n * 50 us （仅 FOSC <= 6.000 MHz 提供）
 *      delay_1ms(uint16_t n)   : 粗略延时 n * 1 ms
 *      delay_1s(uint16_t n)   : 粗略延时 n * 1 s
 *
 *  - **不使用定时器**，基于空循环实现，精度为粗略级别。
 *  - 根据单片机晶振频率修改 "../config/configuration.h" 中的宏定义 FOSC_HZ
 *
 *  - 注意：延时精度受编译器、优化等级、指令集以及循环开销影响。如需高精度请改用定时器或手写精确汇编循环。
 *
 * @version 1.0.1
 * @author  ForeverMySunyu
 * @date    2025-12-07
 **********************************************************************
*/

#ifndef _DELAY_H_
#define _DELAY_H_

#include <stdint.h>
#include <INTRINS.H>
#include "stc89.h"
#include "../config/configuration.h"

void delay_10us(uint8_t count);    /* 粗略延时： count * 10 microseconds （仅 FOSC >= 11.0592 MHz 提供） */
void delay_50us(uint8_t count);    /* 粗略延时： count * 50 microseconds （仅 FOSC <= 6.000 MHz 提供）*/
void delay_1ms(uint16_t count);    /* 粗略延时： count * 1 millisecond */
void delay_1s(uint16_t count);     /* 粗略延时： count * 1 second */

#endif /* _DELAY_H_ */