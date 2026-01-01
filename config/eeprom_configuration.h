/**
 * @file    eeprom_configuration.h
 * @brief   EEPROM 全局配置文件
 * @author  ForeverMySunyu
 * @version 1.0.0
 * @date    2025-12-29
 *
 * @note
 *  - 通过修改本文件即可适配不同 EEPROM
 *  - 当前配置型号：AT24C02
 */

#ifndef _EEPROM_CONFIGURATION_H_
#define _EEPROM_CONFIGURATION_H_

/* ========================= EEPROM IIC 设备地址配置 ========================= */

#define EEPROM_IIC_ADDR_MANDATORY_SEQUENCE        0xA0
#define EEPROM_IIC_ADDR_A2      0
#define EEPROM_IIC_ADDR_A1      0
#define EEPROM_IIC_ADDR_A0      0
/* 根据以上4个宏计算得到 EEPROM 的 IIC 设备地址 */
#define EEPROM_IIC_ADDR         EEPROM_IIC_ADDR_MANDATORY_SEQUENCE + (EEPROM_IIC_ADDR_A2 * 2*2*2) + (EEPROM_IIC_ADDR_A1 * 2*2) + (EEPROM_IIC_ADDR_A0 * 2)

/* ========================= EEPROM 存储参数配置 ========================= */

#define EEPROM_TOTAL_SIZE_BIT   2048                                        //! EEPROM 总存储容量（单位：bit）
#define EEPROM_TOTAL_SIZE_KB    EEPROM_TOTAL_SIZE_BIT/8                     //! EEPROM 总存储容量（单位：KB）
#define EEPROM_PAGE_SIZE_KB     8                                           //! EEPROM 页存储容量（单位：KB）
#define EEPROM_MAX_PAGE_NUM     EEPROM_TOTAL_SIZE_KB/EEPROM_PAGE_SIZE_KB    //! EEPROM 总页数（单位：页）

/* ========================= EEPROM 内部写周期时间配置（单位：MS） ========================= */
#define EEPROM_WRITE_TIME_MS    5

/* ========================= ACK Polling 最大重试次数 ========================= */
#define EEPROM_ACK_POLLING_MAX_TRY   100

#endif      /* _EEPROM_CONFIGURATION_H_ */