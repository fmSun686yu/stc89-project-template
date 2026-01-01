/**
 * @file    eeprom_hal.h
 * @brief   EEPROM HAL 驱动接口
 * @author  ForeverMySunyu
 * @version 1.0.0
 * @date    2025-12-29
 */


#ifndef _EEPROM_HAL_H_
#define _EEPROM_HAL_H_

#include "stdint.h"
#include "stdbool.h"

/* ================== 错误码定义 ================== */

typedef enum
{
    EEPROM_OK = 0,              //! 操作成功
    EEPROM_ERR_IIC,             //! IIC 通信错误
    EEPROM_ERR_DEVICE_ADDR,     //! EEPROM 设备地址错误
    EEPROM_ERR_WORD_ADDR,       //! EEPROM 内部数据地址错误
    EEPROM_ERR_PAGE_NUM,        //! EEPROM 内部页数错误
    EEPROM_ERR_ROW_NUM,         //! EEPROM 内部行数错误
    EEPROM_ERR_DATA_SIZE,       //! 数据大小错误
    EEPROM_ERR_WRITE,           //! 写操作失败
    EEPROM_ERR_READ,            //! 读操作失败
    EEPROM_ERR_TIMEOUT,         //! 操作超时
    EEPROM_ERR_SLAVE_BUSY,      //! EEPROM 设备忙
    EEPROM_ERR_SLAVE_NACK,      //! EEPROM 设备无应答
    EEPROM_ERR_VERIFY,          //! 校验失败
    EEPROM_ERR_UNKNOWN          //! 未知错误
} EEPROM_Error_T;

/* ========================= API 函数声明区域 ========================= */

/**
 * @brief EEPROM 初始化函数
 * @details 初始化 EEPROM 设备，检查设备是否就绪
 * @return EEPROM 驱动程序错误码
 */
EEPROM_Error_T EEPROM_Init_hal(void);

/**
 * @brief 单字节写入
 * @param addr EEPROM 内部数据地址
 * @param write_byte 要写入的 1 字节数据
 * @return EEPROM 驱动程序错误码
 */
EEPROM_Error_T EEPROM_ByteWrite(uint8_t addr, uint8_t write_byte);

/**
 * @brief 页写入函数
 * @note 单页写入，不能跨页
 * @param page_num 页数，保存数据的页地址（从 0 开始计数）
 * @param row_num 行数，在该页的第几行中开始保存数据（从 0 开始计数）
 * @param buf 1 个指针，指向：存放要写入数据的变量
 * @param length 要写入的字节数
 * @return EEPROM 驱动程序错误码
 */
EEPROM_Error_T EEPROM_PageWrite(uint8_t page_num, uint8_t row_num, uint8_t *buf, uint8_t length);

/**
 * @brief  多字节连续写入
 * @note 自动分页
 * @param addr EEPROM 内部数据地址（起始存储地址）
 * @param buf 1 个指针，指向：存放要写入数据的变量
 * @param length 要写入的字节数
 * @return EEPROM 驱动程序错误码
 */
EEPROM_Error_T EEPROM_WriteMultiByte(uint8_t addr, uint8_t *buf, uint8_t length);

/**
 * @brief 从当前地址读取1字节
 * @param buf 1 个指针，指向：存放读取到的数据的变量
 * @return EEPROM 驱动程序错误码
 */
EEPROM_Error_T EEPROM_ReadCurrentByte(uint8_t *buf);

/**
 * @brief 单字节读取（随机读取）
 * @param addr EEPROM 内部数据地址
 * @param read_byte 1 个指针，指向用于存储读取到的 1 字节数据的变量
 * @return EEPROM 驱动程序错误码
 */
EEPROM_Error_T EEPROM_ByteRead(uint8_t addr, uint8_t *read_byte);

/**
 * @brief 页读取函数
 * @note 单页读取，不能跨页
 * @param page_num 页数，读取数据的页地址（从 0 开始计数）
 * @param row_num 行数，在该页的第几行中开始读取数据（从 0 开始计数）
 * @param buf 1 个指针，指向：存放读取到的数据的变量
 * @param length 要读取的字节数
 * @return EEPROM 驱动程序错误码
 */
EEPROM_Error_T EEPROM_PageRead(uint8_t page_num, uint8_t row_num, uint8_t *buf, uint8_t length);

/**
 * @brief 多字节连续读取
 * @param addr EEPROM 内部数据地址（起始读取地址）
 * @param buf 1 个指针，指向：存放读取到的数据的变量
 * @param length 要读取的字节数
 * @return EEPROM 驱动程序错误码
 */
EEPROM_Error_T EEPROM_ReadMultiByte(uint8_t addr, uint8_t *buf, uint8_t length);

/**
 * @brief ACK 轮询函数，等待内部写完成
 * @param None
 * @return EEPROM 驱动程序错误码
 */
EEPROM_Error_T EEPROM_AckPolling(void);

#endif      /* _EEPROM_HAL_H_ */