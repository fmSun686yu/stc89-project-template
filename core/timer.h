/**
 ******************************************************************************************************************
 * @file    timer.h
 * @brief   51单片机 core 层定时器初始化及中断服务程序头文件 — 适用于 STC89C516RD+ 型号单片机并兼容 STC89 系列单片机
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-13
 ******************************************************************************************************************
*/

#ifndef _TIMER_H_
#define _TIMER_H_

#include "../config/timer_configuration.h"

void Timer0_Init(void);         //! 定时器0初始化函数
void Timer1_Init(void);         //! 定时器1初始化函数
void Timer2_Init(void);         //! 定时器2初始化函数

void Timer0_Routine(void);      //! 定时器0中断服务程序
void Timer1_Routine(void);      //! 定时器1中断服务程序
void Timer2_Routine(void);      //! 定时器2中断服务程序

#endif