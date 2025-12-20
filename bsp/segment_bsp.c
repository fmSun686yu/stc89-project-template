/**
 * @file    segment_bsp.C
 * @brief   数码管显示模块的 bsp 驱动源文件
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-19
 *
 * @details 本文件用于数码管显示模块的板级驱动
 */

#include "../config/segment_configuration.h"
#include "segment_bsp.h"

/* ================== API 函数定义区域 ================== */

/**
 * @brief 数码管显示初始化函数
 * @param None
 * @return None
 */
void segment_bsp_init(void)
{
    SEG_SEGMENT_PORT = 0x00;        //! 初始化数码管段选端口
    SEG_DIGIT_PORT = 0x00;          //! 初始化数码管位选端口
}

/**
 * @brief 输出要显示的段码数据
 * @param seg_data 段码数据
 * @return None
 */
void segment_write_data(uint8_t seg_data)
{
    SEG_SEGMENT_PORT = seg_data;
}

/**
 * @brief 选择显示的数码管位
 * @param index 位号（0 ~ SEG_DIGIT_COUNT-1）
 * @return None
 */
void segment_select_digit(uint8_t index)
{
    if(index >= SEG_DIGIT_COUNT)    return;     //! 如果 index >= 数码管个数，则直接返回

    //! 判断是否使用38译码器
    #if _74HC138
        
    #else
        //! 判断数码管类型
        #if (SEG_TYPE == SEG_COMMON_ANODE)
            SEG_DIGIT_PORT = (0x01 << index);   //! 共阳极
        #elif (SEG_TYPE == SEG_COMMON_CATHODE)
            SEG_DIGIT_PORT = ~(0x01 << index);   //! 共阴极
        #endif
    #endif
}

/**
 * @brief 关闭位选信号
 * @param None
 * @return None
 */
void segment_noselect_digit(void)
{
    //! 判断是否使用38译码器
    #if _74HC138
        
    #else
        //! 判断数码管类型
        #if (SEG_TYPE == SEG_COMMON_ANODE)
            SEG_DIGIT_PORT = 0x00;          //! 共阳极
        #elif (SEG_TYPE == SEG_COMMON_CATHODE)
            SEG_DIGIT_PORT = 0xff;          //! 共阴极
        #endif
    #endif
}