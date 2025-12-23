/**
 * @file    iic_bsp.h
 * @brief   IIC 底层驱动接口
 * @note GPIO 模拟，软件模拟
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-23
 */

#ifndef _IIC_BSP_H_
#define _IIC_BSP_H_

#include <stdbool.h>

/*==================== API 函数声明区域 ====================*/

void iic_init_bsp(void);            //! IIC 初始化
void iic_start(void);            //! IIC 起始信号
void iic_stop(void);            //! IIC 停止信号
void iic_send_byte_bsp(unsigned char sendbyte);            //! IIC 发送一个字节
unsigned char iic_receive_byte_bsp(bool ack);            //! IIC 接收一个字节

#endif  /* _IIC_BSP_H_ */