/**
 * @file    segment_hal.C
 * @brief   数码管显示模块的 hal 驱动源文件
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-19
 *
 * @details 本文件用于数码管显示模块的硬件抽象层驱动
 */

#include <stdint.h>
#include "../config/segment_configuration.h"
#include "segment_hal.h"



//! 判断数码管类型
#if (SEG_TYPE == SEG_COMMON_ANODE)

    /** 
     * @brief 共阳极数码管段码查找表
     * @details 
     * |         表位置         |    表值   | 显示的数字 |
     * | :--------------------: | :------: | :--------: |
     * | segment_code_table[0]  |   0x03   |     0      |
     * | segment_code_table[1]  |   0x9f   |     1      |
     * | segment_code_table[2]  |   0x25   |     2      |
     * | segment_code_table[3]  |   0x0d   |     3      |
     * | segment_code_table[4]  |   0x99   |     4      |
     * | segment_code_table[5]  |   0x49   |     5      |
     * | segment_code_table[6]  |   0x41   |     6      |
     * | segment_code_table[7]  |   0x1f   |     7      |
     * | segment_code_table[8]  |   0x01   |     8      |
     * | segment_code_table[9]  |   0x09   |     9      |
     * | segment_code_table[10] |   0x02   |     0.     |
     * | segment_code_table[11] |   0x9e   |     1.     |
     * | segment_code_table[12] |   0x24   |     2.     |
     * | segment_code_table[13] |   0x0c   |     3.     |
     * | segment_code_table[14] |   0x98   |     4.     |
     * | segment_code_table[15] |   0x48   |     5.     |
     * | segment_code_table[16] |   0x40   |     6.     |
     * | segment_code_table[17] |   0x14   |     7.     |
     * | segment_code_table[18] |   0x00   |     8.     |
     * | segment_code_table[19] |   0x08   |     9.     |
     * | segment_code_table[20] |   0xff   |    全灭    |
     * | segment_code_table[21] |   0x00   |    全亮    |
     */
    static uint8_t code segment_code_table[21] = 
    {
        0x03, 0x9f, 0x25, 0x0d, 0x99,   //! 0 1 2 3 4
        0x49, 0x41, 0x1f, 0x01, 0x09,   //! 5 6 7 8 9
        0x02, 0x9e, 0x24, 0x0c, 0x98,   //! 0. 1. 2. 3. 4.
        0x48, 0x40, 0x14, 0x00, 0x08,   //! 5. 6. 7. 8. 9.
        0xff, 0x00                      //! 全灭 全亮
    };

#elif (SEG_TYPE == SEG_COMMON_CATHODE)

    /** 
     * @brief 共阴极数码管段码查找表
     * @details 
     * |         表位置         |    表值   | 显示的数字 |
     * | :--------------------: | :------: | :--------: |
     * | segment_code_table[0]  |   0xfc   |     0      |
     * | segment_code_table[1]  |   0x60   |     1      |
     * | segment_code_table[2]  |   0xda   |     2      |
     * | segment_code_table[3]  |   0xf2   |     3      |
     * | segment_code_table[4]  |   0x66   |     4      |
     * | segment_code_table[5]  |   0x9e   |     5      |
     * | segment_code_table[6]  |   0xbe   |     6      |
     * | segment_code_table[7]  |   0xe0   |     7      |
     * | segment_code_table[8]  |   0xfe   |     8      |
     * | segment_code_table[9]  |   0xf6   |     9      |
     * | segment_code_table[10] |   0xfd   |     0.     |
     * | segment_code_table[11] |   0x61   |     1.     |
     * | segment_code_table[12] |   0xdb   |     2.     |
     * | segment_code_table[13] |   0xf3   |     3.     |
     * | segment_code_table[14] |   0x67   |     4.     |
     * | segment_code_table[15] |   0x9f   |     5.     |
     * | segment_code_table[16] |   0xbf   |     6.     |
     * | segment_code_table[17] |   0xe1   |     7.     |
     * | segment_code_table[18] |   0xff   |     8.     |
     * | segment_code_table[19] |   0xf7   |     9.     |
     * | segment_code_table[20] |   0x00   |    全灭    |
     * | segment_code_table[21] |   0xff   |    全亮    |
     */
    static uint8_t code segment_code_table[21] = 
    {
        0xfc, 0x60, 0xda, 0xf2,0x66,    //! 0 1 2 3 4
        0x9e, 0xbe, 0xe0,0xfe, 0xf6,    //! 5 6 7 8 9
        0xfd, 0x61,0xdb, 0xf3, 0x67,    //! 0. 1. 2. 3. 4.
        0x9f,0xbf, 0xe1, 0xff, 0xf7,    //! 5. 6. 7. 8. 9.
        0x00, 0xff                      //! 全灭 全亮
    };

#endif



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
}

/**
 * @brief 设置要在 index 位上显示的整数数值
 * @param index 数码管位
 * @param value 要显示的数值
 * @return None
 */
void segment_set_number(uint8_t index, uint8_t value)
{
    seg_buffer[index] = value;
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
    segment_write_data(segment_code_table[seg_buffer[seg_scan_index]]);           //! 输出要显示的段码数据
    segment_select_digit(seg_scan_index);           //! 选择显示的数码管位

    seg_scan_index ++;           //! 切换到下一扫描位

    //! 扫描位归0
    if(seg_scan_index>= SEG_DIGIT_COUNT)    seg_scan_index = 0;
}