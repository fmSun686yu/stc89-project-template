/**
 *******************************************************************************************
 * @file    uart_hal.h
 * @brief   51单片机串口通信程序头文件（hal） — 适用于 STC89C516RD+ 型号单片机并兼容 STC89 系列单片机
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-22
 *******************************************************************************************
*/

#ifndef _UART_HAL_H_
#define _UART_HAL_H_

/* ================== API 函数声明区域 ================== */
void uart_init_hal(void);           //! hal 串口初始化函数
void uart_send_byte_hal(unsigned char senddata);           //! 发送一个字节的数据
void uart_send_string_hal(unsigned char *str);           //! 发送一个字符串
unsigned char uart_receive_byte_hal(void);           //! 接收一个字节的数据
void uart_receive_string_hal(unsigned char *str_r, uint16_t str_length);           //! 接收一个字符串

#endif  /* _UART_HAL_H_ */