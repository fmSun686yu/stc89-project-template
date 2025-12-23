/**
 *******************************************************************************************
 * @file    uart_bsp.c
 * @brief   51单片机串口通信程序源文件（bsp） — 适用于 STC89C516RD+ 型号单片机并兼容 STC89 系列单片机
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-22
 *******************************************************************************************
*/

#include "../core/stc89.h"
#include "../config/uart_configuration.h"
#include "uart_bsp.h"



/* ================== API 函数定义区域 ================== */

/**
 * @brief bsp 串口初始化函数
 */
void uart_init_bsp(void)
{
    Timer1_Init();      //! 初始化定时器1，用于产生串口通信波特率

    //! 设置 SCON 寄存器
    #if UART_MODE == 0
        SM0 = 0;
        SM1 = 0;
    #elif UART_MODE == 1
        SM0 = 0;
        SM1 = 1;
    #elif UART_MODE == 2
        SM0 = 1;
        SM1 = 0;
    #elif UART_MODE == 3
        SM0 = 1;
        SM1 = 1;
    #endif

    SM2 = SM2_C;
    REN = REN_C;
    TB8 = 0;
    TI = 0;
    RI = 0;

    //! 设置 PCON 寄存器
    #if SMOD_C
        PCON |= 0x80;
    #else
        PCON &= 0x7f;
    #endif

    #if SMOD0_C
        PCON |= 0x40;
    #else
        PCON &= 0xbf;
    #endif
}

/**
 * @brief 发送一个字节数据
 * @param senddata 要发送的一个字节的数据
 * @return None
 */
void uart_send_byte_bsp(unsigned char senddata)
{
    SBUF = senddata;
    while(!TI);         /* 等待发送完成 */
    TI = 0;
}

/**
 * @brief 接受一个字节数据
 * @param None
 * @return 接收到的一个字节的数据
 */
unsigned char uart_receive_byte_bsp(void)
{
    while(!RI);         /* 等待接收完成 */
    RI = 0;
    return SBUF;
}