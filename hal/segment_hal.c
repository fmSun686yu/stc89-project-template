/**
 * @file    segment_hal.C
 * @brief   数码管显示模块的 hal 驱动源文件
 * @details 本文件用于数码管显示模块的硬件抽象层驱动
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-21
 */

#include <stdint.h>
#include <stdbool.h>
#include "../config/segment_configuration.h"
#include "segment_hal.h"



/** 显示缓冲区 */
static uint8_t seg_buffer[SEG_DIGIT_COUNT];

/** 当前扫描位 */
static uint8_t seg_scan_index = 0;



/* ================== API 函数定义区域 ================== */

/**
 * @brief 数码管显示初始化函数
 * @param None
 * @return None
 */
void segment_hal_init(void)
{
    segment_bsp_init();

    clear_seg_buffer();
}

/**
 * @brief 清空数码管显示缓冲区
 * @param None
 * @return None
 */
void clear_seg_buffer(void)
{
    uint8_t i;

    for(i=0;i<SEG_DIGIT_COUNT;i++)      seg_buffer[i] = 21;
}

/**
 * @brief 设置要在 index 位上显示的整数数值
 * @param value 要显示的整数数值
 * @return None
 */
void segment_set_int_number(int32_t value)
{
    uint8_t i;
    bool nagative_number = 0;

    #if 0   //! 控制是否启用超出最大值检测

        //! 如果要显示的十进制值超过8位数，则显示不下
        if (value > 99999999)
        {
            for(i=0;i<SEG_DIGIT_COUNT;i++)      seg_buffer[i] = 20;
        }
        else if (value < -9999999)
        {
            for(i=0;i<SEG_DIGIT_COUNT;i++)      seg_buffer[i] = 20;
        }

    #endif
    
    //! 检查要显示的数字是否是负数
    if(value < 0)
    {
        nagative_number = 1;
        value = -value;
    }





}

/**
 * @brief 动态扫描刷新函数（需周期调用）
 * @note 可以放在主循环中循环调用
 * @param None
 * @return None
 */
void segment_scan_task()
{
    segment_noselect_digit();           //! 关闭位选信号
    segment_write_data(seg_buffer[seg_scan_index]);           //! 输出要显示的段码数据
    segment_select_digit(seg_scan_index);           //! 选择显示的数码管位

    seg_scan_index ++;           //! 切换到下一扫描位

    //! 扫描位归0
    if(seg_scan_index>= SEG_DIGIT_COUNT)    seg_scan_index = 0;
}