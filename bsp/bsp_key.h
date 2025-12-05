/**
 * file name: bsp_key.h
 *
 * Board Support Package Layer
 * Independent Key and Matrix Key Detection Modules
 * Target MCU: STC89C516RD+ (51-family)
 *
 * 功能：
 *  - 针对硬件电路，对独立按键和矩阵按键相关参数进行初始化
 *
 * 使用方法：
 *  - 在系统初始化时调用 key_init();
 * 
 * 说明：
 *  - 默认按键为低电平有效（KEY_ACTIVE_LEVEL == 0），若你的硬件为高电平有效，请修改宏
 *  - 若需改变引脚映射，请修改下方的宏定义 #define KEYx
 * 
 * version: 1.0.0
 * author: ForeverMySunyu
 * date: 2025-12-06
 */

#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_

#include <stdint.h>
#include "../core/stc89.h"
#include "../core/delay.h"

 /* ========== 配置区（按需调整） ========== */

 /*
 * 按键电平：
 * 0 - 按下时是低电平（常见）
 * 1 - 按下时是高电平
 */
#define KEY_ACTIVE_LEVEL  0

/* === 在此处定义各按键对应的物理端口（按需修改） ===
 * 示例映射：按键 0..9 分别映射到 P3.0 ... P3.7 以及 P1.0, P1.1
 * 根据你的硬件电路把宏定义改为对应的位表达（使用 Keil 的位寻址）
 *
 * 例如：
 *   #define KEY0  P3^0
 *   #define KEY1  P3^1
 *   ...
 */
#define KEY0  P3^0
#define KEY1  P3^1
#define KEY2  P3^2
#define KEY3  P3^3
#define KEY4  P3^4
#define KEY5  P3^5
#define KEY6  P3^6
#define KEY7  P3^7
#define KEY8  P1^0
#define KEY9  P1^1

/* ============= API 函数声明 ============= */

void key_init(void);        // 按键初始化函数

#endif  // _BSP_KEY_H_