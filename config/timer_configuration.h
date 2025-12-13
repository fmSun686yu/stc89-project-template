/**
 ********************************************************************************************
 * @file    timer_configuration.h
 * @brief   51单片机定时器配置文件 — 适用于 STC89C516RD+ 型号单片机并兼容 STC89 系列单片机
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-13
 ********************************************************************************************
*/

#ifndef _TIMER_CONFIGURATION_H_
#define _TIMER_CONFIGURATION_H_

#include "osc_configuration.h"
#include "ind_key_configuration.h"

/* ============================== Timer0 相关配置 ============================== */
/* ====================== Timer0 用于 ====================== */

/**
 * @def TIMER0_MS
 * @brief 定时器0的定时时间，单位：微妙(us)
 * @details 定义需要的定时时长
 */
#define TIMER0_MS       10

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
 */
#define TIMER0_MODE       0

/**
 * @def TIMER0_COUNT_RATE
 * @brief 定时器0的计数速率设置
 * @details 值：6  - 6T模式，每6个时钟加1
 *              12 - 12T模式，每12个时钟加1
 */
#define TIMER0_COUNT_RATE       12

/* ============================== Timer1 相关配置 ============================== */
/* ====================== Timer1 用于产生串口通信波特率 ====================== */

/**
 * @def TIMER1_MS
 * @brief 定时器1的定时时间，单位：微妙(us)
 * @details 定义需要的定时时长
 */
#define TIMER1_MS       10

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

/**
 * @def TIMER1_COUNT_RATE
 * @brief 定时器1的计数速率设置
 * @details 值：6  - 6T模式，每6个时钟加1
 *              12 - 12T模式，每12个时钟加1
 */
#define TIMER1_COUNT_RATE       12

/* ============================== Timer2 相关配置 ============================== */
/* ====================== Timer2 用于独立按键定时循环扫描 ====================== */

/**
 * @def TIMER2_MS
 * @brief 定时器2的定时时间，单位：微妙(us)
 * @details 定义需要的定时时长
 */
#define TIMER2_MS       SCAN_INTERVAL_MS

/**
 * @def TIMER2_CT
 * @brief 定时器2的 C/T 控制位
 * @details 值：0 - 用作定时器 (TIMER)
 *              1 - 用作计数器 (COUNTER)
 */
#define TIMER2_CT       0

/* ==================== Timer0 相关配置（根据以上参数自动计算得出，不要轻易修改） ==================== */

/* ==================== Timer1 相关配置（根据以上参数自动计算得出，不要轻易修改） ==================== */

/* ==================== Timer2 相关配置（根据以上参数自动计算得出，不要轻易修改） ==================== */

#endif /* _TIMER_CONFIGURATION_H_ */