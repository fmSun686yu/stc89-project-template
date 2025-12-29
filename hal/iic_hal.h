/**
 * @file    iic_hal.h
 * @brief   IIC 软件模拟 hal 接口
 * @version 1.0.2
 * @author  ForeverMySunyu
 * @date    2025-12-29
 */

#ifndef _IIC_HAL_H_
#define _IIC_HAL_H_

#include <stdbool.h>

/*==================== IIC 返回状态码（可按需扩展） ====================*/

typedef enum
{
    IIC_OK = 0,     //! 操作成功，一切正常

    IIC_ERR = 1,    //! 未定义错误
    IIC_ERR_NACK,   //! 从机无应答
    IIC_ERR_BUSY    //! IIC 总线忙
} iic_states_t;

/*==================== API 函数声明区域 ====================*/

iic_states_t IIC_Init_hal(void);                        //! IIC 初始化
iic_states_t IIC_Wait_Bus_Idle(void);                   //! 检测 IIC 总线是否空闲
iic_states_t IIC_Slave_Reset(void);                     //! 重置 IIC 总线及从机设备
iic_states_t IIC_Bus_Recovery(void);                    //! 释放（恢复） IIC 总线
iic_states_t IIC_Start(void);                           //! IIC 起始信号
iic_states_t IIC_Restart(void);                         //! 产生 IIC 重复起始信号
iic_states_t IIC_Stop(void);                            //! IIC 停止信号
iic_states_t IIC_Wait_ACK(void);                        //! 等待从机 ACK
iic_states_t IIC_Send_ACK(bool ack);                    //! 发送 ACK 或 NACK
iic_states_t IIC_SendByte(unsigned char sendbyte);      //! IIC 发送一个字节
iic_states_t IIC_ReceiveByte(unsigned char *receivebyte, bool ack);      //! IIC 接收一个字节

#endif      /* _IIC_HAL_H_ */