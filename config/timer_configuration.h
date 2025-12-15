/**
 ********************************************************************************************
 * @file    timer_configuration.h
 * @brief   51单片机定时器配置文件 — 适用于 STC89C516RD+ 型号单片机并兼容 STC89 系列单片机
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-15
 ********************************************************************************************
*/

#ifndef _TIMER_CONFIGURATION_H_
#define _TIMER_CONFIGURATION_H_

#include "osc_configuration.h"
#include "ind_key_configuration.h"


/* ============================== Timer0 相关配置 ============================== */
/* ====================== Timer0 用于定时50us并产生中断，进入中断服务程序 ====================== */

/**
 * @def TIMER0_MS
 * @brief 定时器0的定时时间，单位：微妙(us)
 * @details 定义需要的定时时长
 * @note 最长定时时长（us）：
 *       模式0：8192*TIMER0_COUNT_RATE/FOSC_MHZ
 *       模式1：65536*TIMER0_COUNT_RATE/FOSC_MHZ
 *       模式2：256*TIMER0_COUNT_RATE/FOSC_MHZ
 *       模式3：256*TIMER0_COUNT_RATE/FOSC_MHZ
 */
#define TIMER0_US       50

/**
 * @def TIMER0_COUNT_RATE
 * @brief 定时器0的计数速率设置
 * @details 值：6  - 6T模式，每6个时钟加1
 *              12 - 12T模式，每12个时钟加1
 */
#define TIMER0_COUNT_RATE       12

/**
 * @def TIMER0_GATE
 * @brief 定时器0的 GATE 控制位
 * @details 值：0 - TR1 控制位置1即可开启该定时器/计数器
 *              1 - INT1 脚为高且 TR1 控制位置1时才可开启该定时器/计数器
 *              
 */
#define TIMER0_GATE     0

/**
 * @def TIMER0_CT
 * @brief 定时器0的 C/T 控制位
 * @details 值：0 - 用作定时器 (TIMER)
 *              1 - 用作计数器 (COUNTER)
 */
#define TIMER0_CT       0

/**
 * @def TIMER0_MODE
 * @brief 定时器0的 MODE 控制位
 * @details 值：0 - 模式0，13位定时器/计数器
 *              1 - 模式1，16位定时器/计数器
 *              2 - 模式2，8位自动重装模式
 *              3 - 模式3，两个8位计数器
 * @note 当使用模式3时，T0 被分为 TL0 和 TH0 两个定时器
 *       TL0 在 Timer0 相关配置中进行配置
 *       TH0 在 Timer1 相关配置中进行配置（此时限定为定时器功能，仅可配置定时时间 TIMER1_US）
 */
#define TIMER0_MODE       0


/* ============================== Timer1 相关配置 ============================== */
/* ====================== Timer1 用于产生串口通信波特率 ====================== */

/**
 * @def TIMER1_MS
 * @brief 定时器1的定时时间，单位：微妙(us)
 * @details 定义需要的定时时长
 * @note 最长定时时长（us）：
 *       模式0：8192*TIMER1_COUNT_RATE/FOSC_MHZ
 *       模式1：65536*TIMER1_COUNT_RATE/FOSC_MHZ
 *       模式2：256*TIMER1_COUNT_RATE/FOSC_MHZ
 */
#define TIMER1_US       10

/**
 * @def TIMER1_COUNT_RATE
 * @brief 定时器1的计数速率设置
 * @details 值：6  - 6T模式，每6个时钟加1
 *              12 - 12T模式，每12个时钟加1
 */
#define TIMER1_COUNT_RATE       12

/**
 * @def TIMER1_GATE
 * @brief 定时器1的 GATE 控制位
 * @details 值：0 - TR1 控制位置1即可开启该定时器/计数器
 *              1 - INT1 脚为高且 TR1 控制位置1时才可开启该定时器/计数器
 */
#define TIMER1_GATE     0

/**
 * @def TIMER1_CT
 * @brief 定时器1的 C/T 控制位
 * @details 值：0 - 用作定时器 (TIMER)
 *              1 - 用作计数器 (COUNTER)  
 */
#define TIMER1_CT       0

/**
 * @def TIMER1_MODE
 * @brief 定时器1的 MODE 控制位
 * @details 值：0 - 模式0，13位定时器/计数器
 *              1 - 模式1，16位定时器/计数器
 *              2 - 模式2，8位自动重装模式
 *              3 - 无效，停止计数
 */
#define TIMER1_MODE       0


/* ============================== Timer2 相关配置 ============================== */
/* ====================== Timer2 用于独立按键定时循环扫描 ====================== */

/**
 * @def TIMER2_MS
 * @brief 定时器2的定时时间，单位：微妙(us)
 * @details 定义需要的定时时长
 */
#define TIMER2_US       SCAN_INTERVAL_MS*1000

/**
 * @def TIMER2_EXEN2
 * @brief 定时器2的外部使能标志
 * @details 值：0 - T2EX 的跳变对定时器2无效
 *              1 - 定时器2未作为串行口时钟时，允许 T2EX 的负跳变产生捕获或重装
 */
#define TIMER2_EXEN2       0

/**
 * @def TIMER2_C_T
 * @brief 定时器2的 C/T 控制位
 * @details 值：0 - 用作定时器 (TIMER)
 *              1 - 用作计数器 (COUNTER)
 */
#define TIMER2_C_T       0

/**
 * @def TIMER2_CP_RL
 * @brief 定时器2的捕获/重装标志
 * @details 值：0 - TIMER2_EXEN2=0 时，T2EX 的负跳变或定时器2溢出都可使定时器自动重装
 *              1 - TIMER2_EXEN2=1 时，T2EX 的负跳变产生捕获
 * @note 当 RCLK=1 或 TCLK=1 时，该位无效且定时器强制为溢出时自动重装
 */
#define TIMER2_CP_RL       0

/**
 * @def TIMER2_T2OE
 * @brief 定时器2的输出使能位
 * @details 值：0 - 不输出
 *              1 - 使能输出
 */
#define TIMER2_T2OE       0

/**
 * @def TIMER2_DECN
 * @brief 定时器2的向下计数使能位
 * @details 值：0 - 向上计数
 *              1 - 向下计数
 */
#define TIMER2_DCEN       0

#endif /* _TIMER_CONFIGURATION_H_ */