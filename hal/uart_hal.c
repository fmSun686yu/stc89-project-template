/**
 *******************************************************************************************
 * @file    uart_hal.c
 * @brief   51单片机串口通信程序源文件（hal） — 适用于 STC89C516RD+ 型号单片机并兼容 STC89 系列单片机
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-22
 *******************************************************************************************
*/

#include <stdint.h>
#include "../bsp/uart_bsp.h"
#include "uart_hal.h"



/* ================== API 函数定义区域 ================== */

/**
 * @brief hal 串口初始化函数
 */
void uart_init_hal(void)
{
    uart_init_bsp();
}

/**
 * @brief 发送一个字节的数据
 * @param senddata 要发送的一个字节的数据
 * @return None
 */
void uart_send_byte_hal(unsigned char senddata)
{
    uart_send_byte_bsp(senddata);
}

/**
 * @brief 发送一个字符串
 * @param str 指向要发送的字符串的指针
 * @return None
 */
void uart_send_string_hal(unsigned char *str)
{
    while(*str)
    {
        uart_send_byte_bsp(*str++);
    }
}

/**
 * @brief 接收一个字节的数据
 * @param None
 * @return 接收到的一个字节的数据
 */
unsigned char uart_receive_byte_hal(void)
{
    return uart_receive_byte_bsp();
}

/**
 * @brief 接收一个字符串
 * @param str_r 用于存储接受到的字符串的数组（指向该数组的指针）
 * @param str_length 字符串长度（含有几个字符）
 * @return None
 * @attention 最多支持接收65536个字符
 */
void uart_receive_string_hal(unsigned char *str_r, uint16_t str_length)
{
    uint16_t i;

    for (i = 0; i < str_length; i++)
    {
        *(str_r + i) = uart_receive_byte_bsp();
    }
}