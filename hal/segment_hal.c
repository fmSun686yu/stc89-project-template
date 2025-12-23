/**
 * @file    segment_hal.C
 * @brief   数码管显示模块的 hal 驱动源文件
 * @details 本文件用于数码管显示模块的硬件抽象层驱动
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-22
 */

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
void segment_init_hal(void)
{
    segment_init_bsp();

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
 * @brief 设置要显示的**整数**数值
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

    //! 从低位到高位设置 seg_buffer 数组
    for (i = 0; i < SEG_DIGIT_COUNT; i++)
    {
        if(value)
        {
            seg_buffer[i] = value % 10;
        }
        else
        {
            //! 如果是负数且还未设置显示负号
            if (nagative_number)
            {
                seg_buffer[i] = 20;         //! 显示负号
                nagative_number = 0;
            }
            else
            {
                seg_buffer[i] = 21;         //! 设置全灭不显示
            }
        }

        value /= 10;
    }
    
}

/**
 * @brief 设置要显示的**浮点数**数值
 * @param value 要显示的浮点数数值
 * @param decimal_places 要显示的小数位数
 * @return None
 */
void segment_set_float_number(float value, uint8_t decimal_places)
{
    uint8_t i;
    uint32_t value_int;
    bool nagative_number = 0;

    //! 检查要显示的数字是否是负数
    if(value < 0)
    {
        nagative_number = 1;
        value = -value;
    }

    //! 转化为整数
    for (i = 0; i < decimal_places; i++)
    {
        value *= 10;
    }
    value_int = (uint32_t) value;
    
    #if 0   //! 控制是否启用超出最大值检测

        //! 如果要显示的十进制值超过8位数，则显示不下
        if (value > 99999999)
        {
            for(i=0;i<SEG_DIGIT_COUNT;i++)      seg_buffer[i] = 20;
        }
        else if ((nagative_number) && (value > 9999999))
        {
            for(i=0;i<SEG_DIGIT_COUNT;i++)      seg_buffer[i] = 20;
        }

    #endif

    //! 从低位到高位设置 seg_buffer 数组
    for (i = 0; i < SEG_DIGIT_COUNT; i++)
    {
        if(value_int)
        {
            seg_buffer[i] = value_int % 10;
        }
        else
        {
            //! 如果是负数且还未设置显示负号
            if (nagative_number)
            {
                seg_buffer[i] = 20;         //! 显示负号
                nagative_number = 0;
            }
            else
            {
                seg_buffer[i] = 21;         //! 设置全灭不显示
            }
        }

        value_int /= 10;
    }

    //! 显示小数点
    seg_buffer[decimal_places] += 10;

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