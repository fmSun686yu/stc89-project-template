/**
 * @file    iic_configuration.h
 * @brief   IIC（I2C）通信参数配置文件
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-23
 *
 * @details
 * 本文件用于统一配置 IIC 通信所需的参数，
 * 包括 IIC 使用的 IO 口及时序延时。
 */

#ifndef _IIC_CONFIGURATION_H_
#define _IIC_CONFIGURATION_H_

#include "../core/stc89.h"

/*==================== IIC 引脚配置 ====================*/

#define IIC_SCL P2^0            //! IIC 时钟线 SCL
#define IIC_SDA P2^1            //! IIC 数据线 SDA

/*==================== IIC 时序配置 ====================*/

#define IIC_DELAY_US   5        //! IIC 时序延时（单位：微秒（us））

#endif      /* _IIC_CONFIGURATION_H_ */