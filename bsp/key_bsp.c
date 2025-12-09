/**
 * @file name: key_bsp.c
 * @brief Board Support Package Part of the Independent Key and Matrix Key Detection Module
 * @note Target MCU: STC89C516RD+ (51-family)
 * 
 * 功能：
 *  - 针对硬件电路，对独立按键和矩阵按键相关参数进行初始化
 *  - 声明读取按键连接的 I/O 口的电平的函数
 *
 * 使用方法：
 *  - 在系统初始化时调用 key_init();
 *  - 在 hal 中的按键扫描函数中调用 key_level_read(uint8_t key_id); 以获取 I/O 口电平高低
 * 
 * @version: 1.0.0
 * @author: ForeverMySunyu
 * @date: 2025-12-08
 */

 #include "key_bsp.h"

/**
 * @brief bsp 按键初始化函数
 * @note 包含 ind_key_init() 和 mat_key_init()
 * @param None
 * @return None
 */
 void key_bsp_init(void)
 {
    ind_key_init();
    mat_key_init();
 }

/**
 * @brief bsp 独立按键初始化函数
 * @note 将关于独立按键板级初始化相关的操作放在此函数当中
 * @param None
 * @return None
 */
void ind_key_bsp_init(void)
{

}

/**
 * @brief bsp 矩阵按键初始化函数
 * @note 将关于矩阵按键板级初始化相关的操作放在此函数当中
 * @param None
 * @return None
 */
void mat_key_bsp_init(void)
{

}

/**
 * @brief 检测独立按键是否被按下
 * @param key_id 按键连接的单片机 I/O 口引脚索引（0~15）
 * @retval 1 按键被按下
 *         0 按键未被按下
 * @note 若独立按键数量<16，此函数将会浪费一定的程序存储器。
 *       若想要优化此问题，可以根据 IND_KEY_NUM 的值，使用 #if 来选择编译需要的 case 语句
 * @code{.c}
 * // 程序存储器浪费问题优化示例
 * #if IND_KEY_NUM > 1
 *     case 1: return (IND_KEY1 == IND_KEY_ACTIVE_LEVEL)?1:0;
 * #endif
 * #if IND_KEY_NUM > 2
 *     case 2: return (IND_KEY2 == IND_KEY_ACTIVE_LEVEL)?1:0;
 * #endif
 * #if IND_KEY_NUM > 3
 *     case 3: return (IND_KEY3 == IND_KEY_ACTIVE_LEVEL)?1:0;
 * #endif
 * @endcode
 */
bool ind_key_level_read(uint8_t key_id)
{
    switch(key_id)
    {
        case 0: return (IND_KEY0 == IND_KEY_ACTIVE_LEVEL)?1:0;
        case 1: return (IND_KEY1 == IND_KEY_ACTIVE_LEVEL)?1:0;
        case 2: return (IND_KEY2 == IND_KEY_ACTIVE_LEVEL)?1:0;
        case 3: return (IND_KEY3 == IND_KEY_ACTIVE_LEVEL)?1:0;
        case 4: return (IND_KEY4 == IND_KEY_ACTIVE_LEVEL)?1:0;
        case 5: return (IND_KEY5 == IND_KEY_ACTIVE_LEVEL)?1:0;
        case 6: return (IND_KEY6 == IND_KEY_ACTIVE_LEVEL)?1:0;
        case 7: return (IND_KEY7 == IND_KEY_ACTIVE_LEVEL)?1:0;
        case 8: return (IND_KEY8 == IND_KEY_ACTIVE_LEVEL)?1:0;
        case 9: return (IND_KEY9 == IND_KEY_ACTIVE_LEVEL)?1:0;
        case 10: return (IND_KEY10 == IND_KEY_ACTIVE_LEVEL)?1:0;
        case 11: return (IND_KEY11 == IND_KEY_ACTIVE_LEVEL)?1:0;
        case 12: return (IND_KEY12 == IND_KEY_ACTIVE_LEVEL)?1:0;
        case 13: return (IND_KEY13 == IND_KEY_ACTIVE_LEVEL)?1:0;
        case 14: return (IND_KEY14 == IND_KEY_ACTIVE_LEVEL)?1:0;
        case 15: return (IND_KEY15 == IND_KEY_ACTIVE_LEVEL)?1:0;
        default: return 0;
    }
}

