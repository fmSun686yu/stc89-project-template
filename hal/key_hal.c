/**
 * @file key_hal.c
 * @brief Hardware Abstraction Layer of the Independent Key and Matrix Key Detection Module
 * @note Target MCU: STC89C516RD+ (51-family)
 * 
 * - 独立按键状态机实现
 * 
 * 功能：
 *  - 支持 1~16 个独立按键的状态检测
 *  - 基于定时器 Tick 进行扫描（消抖、状态保持）
 *  - 检测事件：短按、1阶段长按、2阶段长按、3阶段长按、双击、组合键、释放
 *  - 通过回调将事件通知 APP 层
 * 
 * 设计说明：
 *  - 按键是否按下由 bsp/key_bsp.c 中的 ind_key_level_read(uint8_t key_id); 函数检测
 *  - HAL 在每个 tick 中读取所有按键并更新状态机
 * 
 * ======================================================================================
 * 
 * - 矩阵按键检测实现（待编写）
 * 功能：
 * 
 * 设计说明：
 * 
 * 
 * @version 1.0.0
 * @author fmSun686yu
 * @date 2025-12-8
 */

#include "key_hal.h"



/**
 * @brief hal 按键初始化函数
 * @note 包含 ind_key_hal_init() 和 mat_key_hal_init()
 * @param None
 * @return None
 */
void key_hal_init(void)
{
    ind_key_hal_init();
    mat_key_hal_init();
}

/**
 * @brief hal 独立按键初始化函数
 * @note 将关于独立按键硬件抽象层初始化相关的操作放在此函数当中
 * @param None
 * @return None
 */
void ind_key_hal_init(void)
{
    ind_key_bsp_init();     // bsp 独立按键初始化函数
}

/**
 * @brief hal 矩阵按键初始化函数
 * @note 将关于矩阵按键硬件抽象层初始化相关的操作放在此函数当中
 * @param None
 * @return None
 */
void mat_key_hal_init(void)
{
    mat_key_bsp_init();     // bsp 矩阵按键初始化函数
}

/**
 * @brief 获取当前处于 PRESSED 状态的按键掩码
 * @param None
 * @return 按键掩码(位 0-15 对应 KEY0-KEY16)
 */
uint16_t ind_key_get_pressed_mask(void)
{
    uint16_t mask = 0;
    uint8_t i;

    //! 循环扫描所有按键的状态机（KEY0 → KEY15）
    for(i=0;i<IND_KEY_NUM;i++)
    {
        //! 如果当前按键状态为 PRESSED
        if()
        {
            mask |= 0x8000;
        }

        mask >> 1;
    }

    return mask;
}

/**
 * @brief 独立按键扫描函数，调用独立按键状态机函数
 * @note 必须周期性调用：以 IND_SCAN_INTERVAL_MS 为周期调用（通常放在定时器中断中）
 * @param None
 * @return None
 */
void ind_key_scan(void)
{
    uint8_t i;

    //! 循环扫描所有按键并运行状态机，更新每个独立按键的状态
    for(i=0;i<IND_KEY_NUM;i++)
    {
        ind_key_state_machine(i);   //! 运行独立按键状态机
    }

    //! 检查组合键
    ind_key_check_combination();
}

/**
 * @brief 独立按键状态机
 * @note ind_key_scan(); 中循环调用，每次调用更新一次对应按键的状态
 */
void ind_key_state_machine(uint8_t key_id)
{

}