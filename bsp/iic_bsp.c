/**
 * @file    iic_bsp.c
 * @brief   IIC 底层驱动接口
 * @note GPIO 模拟，软件模拟
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-27
 */



#include "../config/iic_configuration.h"
#include "iic_bsp.h"

/*==================== API 函数定义区域 ====================*/

/**
 * @brief IIC 初始化函数
 * @param None
 * @return None
 */
void IIC_Init_bsp(void)
{
    
}

/**
 * @brief 设置 SCL 电平
 * @param level 0-低电平，1-高电平
 * @return None
 */
void SCL_Set(bool level)
{
    if (level)
    {
        IIC_SCL = 1;
    }
    else
    {
        IIC_SCL = 0;
    }
}

/**
 * @brief 读取 SCL 电平
 * @param None
 * @retval 0-低电平，1-高电平
 */
bool SCL_Read(void)
{
    return IIC_SCL;
}

/**
 * @brief 设置 SDA 电平
 * @param level 0-低电平，1-高电平
 * @return None
 */
void SDA_Set(bool level)
{
    if (level)
    {
        IIC_SDA = 1;
    }
    else
    {
        IIC_SDA = 0;
    }
}

/**
 * @brief 读取 SDA 电平
 * @param None
 * @retval 0-低电平，1-高电平
 */
bool SDA_Read(void)
{
    return IIC_SDA;
}