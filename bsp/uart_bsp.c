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

    
}