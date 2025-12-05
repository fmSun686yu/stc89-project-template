/**
 * file name: bsp_key.c
 *
 * Board Support Package Layer
 * Independent Key and Matrix Key Detection Modules
 * Target MCU: STC89C516RD+ (51-family)
 *
 * 功能：
 *  - 针对硬件电路，对独立按键和矩阵按键相关参数进行初始化
 *  - 支持最多 KEY_COUNT 个独立按键（此处实现为 10 个）
 *
 * 使用方法：
 *  - 在系统初始化时调用 key_init();
 * 
 * 说明：
 *  - 默认按键为低电平有效（KEY_ACTIVE_LEVEL == 0），若你的硬件为高电平有效，请修改头文件 bsp_key.h 中的宏
 *  - 若需改变引脚映射，请修改头文件 bsp_key.h 中的位定义 sbit KEYx
 * 
 * version: 1.0.0
 * author: ForeverMySunyu
 * date: 2025-12-05
 */

 #include "bsp_key.h"

 