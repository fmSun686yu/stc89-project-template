/**
 * @file    iic_hal.c
 * @brief   IIC 软件模拟 hal 实现
 * @version 1.0.2
 * @author  ForeverMySunyu
 * @date    2025-12-29
 */

#include "../core/delay.h"
#include "../config/iic_configuration.h"
#include "../bsp/iic_bsp.h"
#include "iic_hal.h"

/*==================== API 函数定义区域 ====================*/

/**
 * @brief IIC 初始化函数
 * @param None
 * @return IIC 状态
 */
iic_states_t IIC_Init_hal(void)
{
    IIC_Init_bsp();

    SCL_Set(1);
    SDA_Set(1);
    delay_10us(10*IIC_DELAY_10US);

    /* 若总线异常，尝试1次恢复 */
    if (IIC_Wait_Bus_Idle() != IIC_OK)
    {
        IIC_Bus_Recover();
    }

    /* 检测 IIC 总线是否空闲，并返回 IIC 状态码 */
    return IIC_Wait_Bus_Idle();
}

/**
 * @brief 检测 IIC 总线是否空闲
 * @param None
 * @return IIC 状态
 */
iic_states_t IIC_Wait_Bus_Idle(void)
{
    uint16_t timeout = 0;

    /* 释放 SDA 与 SCL */
    SDA_Set(1);
    SCL_Set(1);

    while (!SCL_Read() || !SDA_Read())
    {
        timeout ++;

        if (timeout >= IIC_BUS_IDLE_TIMEOUT)
        {
            return IIC_ERR_BUSY;
        }
    }

    return IIC_OK;
}

/**
 * @brief 重置 IIC 总线及从机设备
 * @note  通过发送 1 个起始信号， 9 个 SCL 脉冲， 1 个起始信号， 1 个停止信号，尝试重置 IIC 总线及从机设备
 * @param None
 * @return IIC 状态（IIC_OK）
 */
iic_states_t IIC_Slave_Reset(void)
{
    uint8_t i;

    /* 释放 SDA 与 SCL */
    SDA_Set(1);
    delay_10us(IIC_DELAY_10US);
    SCL_Set(1);
    delay_10us(IIC_DELAY_10US);

    /* 产生 START 信号 */
    SDA_Set(0);
    delay_10us(IIC_DELAY_10US);
    SCL_Set(0);
    delay_10us(IIC_DELAY_10US);

    SDA_Set(1);
    delay_10us(IIC_DELAY_10US);

    /* 连续发送 9 个 SCL 脉冲 */
    for (i = 0; i < 9; i++)
    {
        SCL_Set(1);
        delay_10us(IIC_DELAY_10US);
        SCL_Set(0);
        delay_10us(IIC_DELAY_10US);
    }

    /* 产生 START 信号 */
    SCL_Set(1);
    delay_10us(IIC_DELAY_10US);
    SDA_Set(0);
    delay_10us(IIC_DELAY_10US);

    SCL_Set(0);
    delay_10us(IIC_DELAY_10US);
    
    /* 产生 STOP 信号 */
    SCL_Set(1);
    delay_10us(IIC_DELAY_10US);
    SDA_Set(1);
    delay_10us(IIC_DELAY_10US);

    return IIC_OK;
}

/**
 * @brief 释放（恢复） IIC 总线
 * @note  通过发送 9 个 SCL 脉冲，尝试释放被从机拉低的 SDA
 * @param None
 * @return IIC 状态（IIC_OK）
 */
iic_states_t IIC_Bus_Recover(void)
{
    uint8_t i;

    /* 保证 SCL 为低，释放 SDA */
    SCL_Set(0);
    delay_10us(IIC_DELAY_10US);
    SDA_Set(1);
    delay_10us(IIC_DELAY_10US);

    /* 连续发送 9 个 SCL 脉冲 */
    for (i = 0; i < 9; i++)
    {
        SCL_Set(1);
        delay_10us(IIC_DELAY_10US);
        SCL_Set(0);
        delay_10us(IIC_DELAY_10US);
    }
    
    /* 强制产生 STOP 信号 */
    SDA_Set(0);
    delay_10us(IIC_DELAY_10US);
    SCL_Set(1);
    delay_10us(IIC_DELAY_10US);
    SDA_Set(1);
    delay_10us(IIC_DELAY_10US);

    return IIC_OK;
}

/**
 * @brief IIC 起始信号
 * @param None
 * @return IIC 状态
 */
iic_states_t IIC_Start(void)
{
    if (IIC_Wait_Bus_Idle() != IIC_OK)
    {
        /* 若总线异常，尝试1次恢复 */
        IIC_Bus_Recover();

        /* 若总线还是异常，返回总线忙错误状态 */
        if(IIC_Wait_Bus_Idle() != IIC_OK)       return IIC_Wait_Bus_Idle();
    }      
    
    SDA_Set(1);
    SCL_Set(1);
    delay_10us(IIC_DELAY_10US);
    SDA_Set(0);
    delay_10us(IIC_DELAY_10US);
    SCL_Set(0);

    return IIC_OK;
}

/**
 * @brief 产生 IIC 重复起始信号
 * @note 不释放总线，直接从 SCL=1, SDA=1 → SDA=0
 * @attention 使用该函数前提：使用该函数的主机已占有总线
 * @return IIC 状态（IIC_OK）
 */
iic_states_t IIC_Restart()
{
    /* 确保 SDA 为高（释放） */
    SDA_Set(1);
    delay_10us(IIC_DELAY_10US);
    
    /* 拉高 SCL，保持总线控制权 */
    SCL_Set(1);
    delay_10us(IIC_DELAY_10US);

    /* SDA 下降沿，产生 Repeated START */
    SDA_Set(0);
    delay_10us(IIC_DELAY_10US);

    /* 拉低 SCL，进入数据阶段 */
    SCL_Set(0);
    delay_10us(IIC_DELAY_10US);

    return IIC_OK;
}

/**
 * @brief IIC 停止信号
 * @param None
 * @return IIC 状态（IIC_OK）
 */
iic_states_t IIC_Stop(void)
{
    SDA_Set(0);
    SCL_Set(1);
    delay_10us(IIC_DELAY_10US);
    SDA_Set(1);
    delay_10us(IIC_DELAY_10US);

    return IIC_OK;
}

/**
 * @brief 等待从机 ACK
 * @param None
 * @return IIC 状态
 * @retval IIC_OK - 收到从机 ACK
 *         IIC_ERR_NACK - 未收到从机 ACK
 */
iic_states_t IIC_Wait_ACK(void)
{
    uint16_t timeout = 0;

    SDA_Set(1);     //! 释放 SDA 线
    delay_10us(IIC_DELAY_10US);

    SCL_Set(1);

    while (SDA_Read())
    {
        timeout ++;

        if(timeout >= IIC_ACK_TIMEOUT)
        {
            SCL_Set(0);
            return IIC_ERR_NACK;
        }
    }
    
    SCL_Set(0);

    return IIC_OK;
}

/**
 * @brief 发送 ACK 或 NACK
 * @param ack 0-发送 NACK，1-发送 ACK
 * @return IIC 状态（IIC_OK）
 */
iic_states_t IIC_Send_ACK(bool ack)
{
    SDA_Set(!ack);
    delay_10us(IIC_DELAY_10US);

    SCL_Set(1);
    delay_10us(IIC_DELAY_10US);
    SCL_Set(0);

    return IIC_OK;
}

/**
 * @brief IIC 发送一个字节
 * @note 包含等待从机 ACK 程序
 * @param sendbyte 要发送的一个字节的数据
 * @return 是否接收到从机的 ACK
 */
iic_states_t IIC_SendByte(unsigned char sendbyte)
{
    uint8_t i;

    /* 发送1个字节 */
    for (i = 0; i < 8; i++)
    {
        SDA_Set(sendbyte & 0x80);
        sendbyte <<= 1;

        SCL_Set(1);
        delay_10us(IIC_DELAY_10US);
        SCL_Set(0);
        delay_10us(IIC_DELAY_10US);
    }

    /* 等待、检测从机 ACK，并返回对应状态码 */
    return IIC_Wait_ACK();
}

/**
 * @brief IIC 接收一个字节
 * @note 包含发送 ACK 程序
 * @param receivebyte 用于保存接受到的1个字节的变量的地址
 * @param ack 是否发送 ACK（0=NACK，1=ACK）
 * @return IIC 状态（IIC_OK）
 */
iic_states_t IIC_ReceiveByte(unsigned char *receivebyte, bool ack)
{
    uint8_t i;

    *receivebyte = 0;

    SDA_Set(1);     //! 释放 SDA 线

    /* 读取1个字节 */
    for (i = 0; i < 8; i++)
    {
        SCL_Set(1);
        delay_10us(IIC_DELAY_10US);

        *receivebyte <<= 1;
        if (SDA_Read())
        {
            *receivebyte |= 0x01;
        }

        SCL_Set(0);
        delay_10us(IIC_DELAY_10US);
    }
    
    /* 发送 ACK / NACK，并返回状态码 */
    return IIC_Send_ACK(ack);
}