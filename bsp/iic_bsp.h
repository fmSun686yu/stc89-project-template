/**
 * @file    iic_bsp.h
 * @brief   IIC 底层驱动接口
 * @note GPIO 模拟，软件模拟
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-27
 */

#ifndef _IIC_BSP_H_
#define _IIC_BSP_H_

#include <stdbool.h>

/*==================== API 函数声明区域 ====================*/

void IIC_Init_bsp(void);            //! IIC 初始化

//! GPIO 操作接口
void SCL_Set(bool level);
bool SCL_Read(void);
void SDA_Set(bool level);
bool SDA_Read(void);

#endif  /* _IIC_BSP_H_ */