/**
 * @file    iic_bsp.c
 * @brief   IIC 底层驱动接口
 * @note GPIO 模拟，软件模拟
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-23
 */

#include "iic_bsp.h"

/*==================== API 函数定义区域 ====================*/

/**
 * @brief IIC 初始化函数
 * @param None
 * @return None
 */
void iic_init_bsp(void)
{

}

/**
 * @brief IIC 起始信号
 * @param None
 * @return None
 */
void iic_start(void)
{

}

/**
 * @brief IIC 停止信号
 * @param None
 * @return None
 */
void iic_stop(void)
{

}

/**
 * @brief IIC 发送一个字节
 * @param sendbyte 要发送的一个字节的数据
 * @return None
 */
void iic_send_byte_bsp(unsigned char sendbyte)
{

}

/**
 * @brief IIC 接收一个字节
 * @param ack 是否发送 ACK（0=NACK，1=ACK）
 * @return 接收到的一个字节的数据
 */
unsigned char iic_receive_byte_bsp(bool ack)
{

}
