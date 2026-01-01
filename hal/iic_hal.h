/**
 * @file    iic_hal.h
 * @brief   IIC 软件模拟 hal 接口
 * @version 1.0.3
 * @author  ForeverMySunyu
 * @date    2025-12-31
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

/**
 * @brief IIC 初始化函数
 * @param None
 * @return IIC 状态
 */
iic_states_t IIC_Init_hal(void);

/**
 * @brief 检测 IIC 总线是否空闲
 * @param None
 * @return IIC 状态
 */
iic_states_t IIC_Wait_Bus_Idle(void);

/**
 * @brief 重置 IIC 总线及从机设备
 * @note  通过发送 1 个起始信号， 9 个 SCL 脉冲， 1 个起始信号， 1 个停止信号，尝试重置 IIC 总线及从机设备
 * @param None
 * @return IIC 状态（IIC_OK）
 */
iic_states_t IIC_Slave_Reset(void);

/**
 * @brief 释放（恢复） IIC 总线
 * @note  通过发送 9 个 SCL 脉冲，尝试释放被从机拉低的 SDA
 * @param None
 * @return IIC 状态（IIC_OK）
 */
iic_states_t IIC_Bus_Recovery(void);

/**
 * @brief IIC 起始信号
 * @param None
 * @return IIC 状态
 */
iic_states_t IIC_Start(void);

/**
 * @brief 产生 IIC 重复起始信号
 * @note 不释放总线，直接从 SCL=1, SDA=1 → SDA=0
 * @attention 使用该函数前提：使用该函数的主机已占有总线
 * @return IIC 状态（IIC_OK）
 */
iic_states_t IIC_Restart(void);

/**
 * @brief IIC 停止信号
 * @param None
 * @return IIC 状态（IIC_OK）
 */
iic_states_t IIC_Stop(void);

/**
 * @brief 等待从机 ACK
 * @param None
 * @return IIC 状态
 */
iic_states_t IIC_Wait_ACK(void);

/**
 * @brief 发送 ACK 或 NACK
 * @param ack 0-发送 NACK，1-发送 ACK
 * @return IIC 状态（IIC_OK）
 */
iic_states_t IIC_Send_ACK(bool ack);

/**
 * @brief IIC 发送一个字节
 * @note 包含等待从机 ACK 程序
 * @param sendbyte 要发送的一个字节的数据
 * @return 是否接收到从机的 ACK
 */
iic_states_t IIC_SendByte(unsigned char sendbyte);

/**
 * @brief IIC 接收一个字节
 * @note 包含发送 ACK 程序
 * @param receivebyte 用于保存接受到的1个字节的变量的地址
 * @param ack 是否发送 ACK（0=NACK，1=ACK）
 * @return IIC 状态（IIC_OK）
 */
iic_states_t IIC_ReceiveByte(unsigned char *receivebyte, bool ack);

#endif      /* _IIC_HAL_H_ */