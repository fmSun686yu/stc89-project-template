/**
 ******************************************************************************************************************
 * @file    timer.h
 * @brief   51单片机 core 层定时器初始化及中断服务程序头文件 — 适用于 STC89C516RD+ 型号单片机并兼容 STC89 系列单片机
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-15
 ******************************************************************************************************************
*/

#ifndef _TIMER_H_
#define _TIMER_H_

#include"stdint.h"
#include "../config/timer_configuration.h"
#include "../config/uart_configuration.h"
#include "../core/stc89.h"

/* ==================== Timer0 相关参数计算（根据 timer_configuration.h 中参数自动计算得出，不要轻易修改） ==================== */
#if TIMER0_MODE == 0
    #define TIMER0_VALUE    (uint16_t)((8192-FOSC_MHZ*TIMER0_US/TIMER0_COUNT_RATE)+0.5)
#elif TIMER0_MODE == 1
    #define TIMER0_VALUE    (uint16_t)((65536-FOSC_MHZ*TIMER0_US/TIMER0_COUNT_RATE)+0.5)
#elif TIMER0_MODE == 2
    #define TIMER0_VALUE    (uint16_t)(((256-FOSC_MHZ*TIMER0_US/TIMER0_COUNT_RATE)+(256-FOSC_MHZ*TIMER0_US/TIMER0_COUNT_RATE)*256)+0.5)
#elif TIMER0_MODE == 3
    #define TIMER0_VALUE    (uint16_t)(((256-FOSC_MHZ*TIMER0_US/TIMER0_COUNT_RATE)+(256-FOSC_MHZ*TIMER1_US/TIMER0_COUNT_RATE)*256)+0.5)
#else
    #error "The setting of TIMER0_MODE is incorrect."
#endif

/* ==================== Timer1 相关参数计算（根据 timer_configuration.h 中参数自动计算得出，不要轻易修改） ==================== */
#if TIMER1_MODE == 0
    #define TIMER1_VALUE    (uint16_t)((8192-FOSC_MHZ*TIMER1_US/TIMER1_COUNT_RATE)+0.5)
#elif TIMER1_MODE == 1
    #define TIMER1_VALUE    (uint16_t)((65536-FOSC_MHZ*TIMER1_US/TIMER1_COUNT_RATE)+0.5)
#elif TIMER1_MODE == 2
    #define TIMER1_VALUE    (uint16_t)(((256-FOSC_MHZ*TIMER1_US/TIMER1_COUNT_RATE)+(256-FOSC_MHZ*TIMER1_US/TIMER1_COUNT_RATE)*256)+0.5)
#else
    #error "The setting of TIMER1_MODE is incorrect."
#endif

/* ==================== Timer2 相关参数计算（根据 timer_configuration.h 中参数自动计算得出，不要轻易修改） ==================== */
#define TIMER2_VALUE    (uint16_t)((65536-FOSC_MHZ*TIMER2_US/MACHINE_CYCLE)+0.5)



/* ===================== 定时器初始化函数声明区 ======================== */
void Timer0_Init(void);         //! 定时器0初始化函数
void Timer1_Init(void);         //! 定时器1初始化函数
void Timer2_Init(void);         //! 定时器2初始化函数

#endif