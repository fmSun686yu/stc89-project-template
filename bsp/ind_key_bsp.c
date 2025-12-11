/**
 * @file name: ind_key_bsp.c
 * @brief Board Support Package Part of the Independent Key Detection Module
 * @note Target MCU: STC89C516RD+ (51-family)
 * 
 * 功能：
 *  - 针对硬件电路，对独立按键相关参数进行初始化
 *  - 声明读取按键连接的 I/O 口的电平的函数
 *
 * 使用方法：
 *  - 在系统初始化时调用 key_bsp_init();
 *  - 在 hal 中的按键扫描函数中调用 key_pressed_detect(uint8_t key_id); 以检测按键是否被按下
 * 
 * @version: 1.1.0
 * @author: ForeverMySunyu
 * @date: 2025-12-11
 */

#include "ind_key_bsp.h"

/**
 * @brief bsp 按键初始化函数
 * @param None
 * @return None
 */
 void key_bsp_init(void)
 {

 }

/**
 * @brief 检测独立按键是否被按下（未消抖的原始数据）
 * @param key_id 按键连接的单片机 I/O 口引脚索引（0~15）
 * @retval 1 按键被按下
 *         0 按键未被按下
 * @note 若独立按键数量<16，此函数将会浪费一定的程序存储器。
 *       若想要优化此问题，可以根据 KEY_NUM 的值，使用 #if 来选择编译需要的 case 语句
 * @code{.c}
 * // 程序存储器浪费问题优化示例
 * #if KEY_NUM > 1
 *     case 1: return (KEY1 == KEY_ACTIVE_LEVEL)?1:0;
 * #endif
 * #if KEY_NUM > 2
 *     case 2: return (KEY2 == KEY_ACTIVE_LEVEL)?1:0;
 * #endif
 * #if KEY_NUM > 3
 *     case 3: return (KEY3 == KEY_ACTIVE_LEVEL)?1:0;
 * #endif
 * @endcode
 */
bool key_pressed_detect(uint8_t key_id)
{
    switch(key_id)
    {
        case 0: return (KEY0 == KEY_ACTIVE_LEVEL)?1:0;
        case 1: return (KEY1 == KEY_ACTIVE_LEVEL)?1:0;
        case 2: return (KEY2 == KEY_ACTIVE_LEVEL)?1:0;
        case 3: return (KEY3 == KEY_ACTIVE_LEVEL)?1:0;
        case 4: return (KEY4 == KEY_ACTIVE_LEVEL)?1:0;
        case 5: return (KEY5 == KEY_ACTIVE_LEVEL)?1:0;
        case 6: return (KEY6 == KEY_ACTIVE_LEVEL)?1:0;
        case 7: return (KEY7 == KEY_ACTIVE_LEVEL)?1:0;
        case 8: return (KEY8 == KEY_ACTIVE_LEVEL)?1:0;
        case 9: return (KEY9 == KEY_ACTIVE_LEVEL)?1:0;
        case 10: return (KEY10 == KEY_ACTIVE_LEVEL)?1:0;
        case 11: return (KEY11 == KEY_ACTIVE_LEVEL)?1:0;
        case 12: return (KEY12 == KEY_ACTIVE_LEVEL)?1:0;
        case 13: return (KEY13 == KEY_ACTIVE_LEVEL)?1:0;
        case 14: return (KEY14 == KEY_ACTIVE_LEVEL)?1:0;
        case 15: return (KEY15 == KEY_ACTIVE_LEVEL)?1:0;
        default: return 0;
    }
}

