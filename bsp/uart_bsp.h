/**
 *******************************************************************************************
 * @file    uart_bsp.h
 * @brief   51单片机串口通信程序头文件（bsp） — 适用于 STC89C516RD+ 型号单片机并兼容 STC89 系列单片机
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-22
 *******************************************************************************************
*/

#ifndef _UART_BSP_H_
#define _UART_BSP_H_

/* ================== API 函数声明区域 ================== */
void uart_init_bsp(void);           //! bsp 串口初始化函数
void uart_send_byte_bsp(unsigned char senddata);          //! 发送一个字节数据
unsigned char uart_receive_byt_bsp(void);                //! 接受一个字节的数据

#endif  /* _UART_BSP_H_ */