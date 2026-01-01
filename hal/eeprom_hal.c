/**
 * @file    eeprom_hal.c
 * @brief   EEPROM HAL 驱动源文件
 * @author  ForeverMySunyu
 * @version 1.0.0
 * @date    2026-1-1
 */

#include "../config/eeprom_configuration.h"
#include "../core/delay.h"
#include "iic_hal.h"
#include "eeprom_hal.h"

/* ========================= API 函数定义区域 ========================= */

/**
 * @brief EEPROM 初始化函数
 * @details 初始化 EEPROM 设备，检查设备是否就绪
 * @return EEPROM 驱动程序错误码
 */
EEPROM_Error_T EEPROM_Init_hal()
{

}

/**
 * @brief 单字节写入
 * @param addr EEPROM 内部数据地址
 * @param write_byte 要写入的 1 字节数据
 * @return EEPROM 驱动程序错误码
 */
EEPROM_Error_T EEPROM_ByteWrite(uint8_t addr, uint8_t write_byte)
{
    iic_states_t iic_state;     //! 用于存储 IIC 状态码

    /* 内部数据地址参数检查 */
    if (addr >= EEPROM_TOTAL_SIZE_KB)
    {
        return EEPROM_ERR_WORD_ADDR;
    }
    
    /* 发送 START */
    iic_state = IIC_Start();
    if(iic_state != IIC_OK)
    {
        IIC_Stop();
        return EEPROM_ERR_IIC;
    }

    /* 发送设备地址 + 写 */
    iic_state = IIC_SendByte(EEPROM_IIC_ADDR);
    if(iic_state == IIC_ERR_NACK)
    {
        IIC_Stop();
        return EEPROM_ERR_SLAVE_NACK;
    }

    /* 发送 EEPROM 内部字节地址 */
    iic_state = IIC_SendByte(addr);
    if(iic_state == IIC_ERR_NACK)
    {
        IIC_Stop();
        return EEPROM_ERR_SLAVE_NACK;
    }

    /* 发送要写入的 8 bit 数据 */
    iic_state = IIC_SendByte(write_byte);
    if(iic_state == IIC_ERR_NACK)
    {
        IIC_Stop();
        return EEPROM_ERR_SLAVE_NACK;
    }

    /* 发送 STOP */
    iic_state = IIC_Stop();
    if (iic_state != IIC_OK)
    {
        IIC_Stop();
        return EEPROM_ERR_IIC;
    }
    
    /* 通过延时函数，等待 EEPROM 内部写周期完成（可升级） */
    // delay_1ms(EEPROM_WRITE_TIME_MS);

    /* 通过轮询，等待 EEPROM 内部写周期完成 */
    if (EEPROM_AckPolling() == EEPROM_OK)
    {
        return EEPROM_OK;
    }
    else if (EEPROM_AckPolling() == EEPROM_ERR_SLAVE_BUSY)
    {
        return EEPROM_ERR_WRITE;
    }
}

/**
 * @brief 页写入函数
 * @note 单页写入，不能跨页
 * @param page_num 页数，保存数据的页地址（从 0 开始计数）
 * @param row_num 行数，在该页的第几行中开始保存数据（从 0 开始计数）
 * @param buf 1 个指针，指向：存放要写入数据的变量
 * @param length 要写入的字节数
 * @return EEPROM 驱动程序错误码
 */
EEPROM_Error_T EEPROM_PageWrite(uint8_t page_num, uint8_t row_num, uint8_t *buf, uint8_t length)
{
    iic_states_t iic_state;     //! 用于存储 IIC 状态码

    /* ==================== 参数检查 ==================== */

    /* 页数检查 */
    if (page_num >= EEPROM_MAX_PAGE_NUM)
    {
        return EEPROM_ERR_PAGE_NUM;
    }
    
    /* 行数检查 */
    if (row_num >= EEPROM_PAGE_SIZE_KB)
    {
        return EEPROM_ERR_ROW_NUM;
    }
    
    /* 数据长度（字节数）检查 */
    /* 数据长度不能 >= 该页剩余字节数（该页剩余字节数 = 该页总字节数 - 起始行） */
    if (length >= EEPROM_PAGE_SIZE_KB-row_num)
    {
        return EEPROM_ERR_DATA_SIZE;
    }

    /* ==================== 开始页写入 ==================== */

    /* 发送 START */
    iic_state = IIC_Start();
    if(iic_state != IIC_OK)
    {
        IIC_Stop();
        return EEPROM_ERR_IIC;
    }

    /* 发送设备地址 + 写 */
    iic_state = IIC_SendByte(EEPROM_IIC_ADDR);
    if(iic_state == IIC_ERR_NACK)
    {
        IIC_Stop();
        return EEPROM_ERR_SLAVE_NACK;
    }

    /* 发送 EEPROM 内部字节地址 */
    /* 内部字节地址 addr = 0x08 * page_num + row_num */
    iic_state = IIC_SendByte(0x08 * page_num + row_num);
    if(iic_state == IIC_ERR_NACK)
    {
        IIC_Stop();
        return EEPROM_ERR_SLAVE_NACK;
    }

    /* 连续写入 length 个 8 bit 数据 */
    while (length)
    {
        iic_state = IIC_SendByte(*buf);
        if(iic_state == IIC_ERR_NACK)
        {
            IIC_Stop();
            return EEPROM_ERR_SLAVE_NACK;
        }

        /* 更新 buf 指针和待写入字节数 */
        buf ++;
        length --;
    }
    
    /* 发送 STOP */
    iic_state = IIC_Stop();
    if (iic_state != IIC_OK)
    {
        IIC_Stop();
        return EEPROM_ERR_IIC;
    }

    /* ==================== 通过轮询，等待 EEPROM 内部写周期完成 ==================== */
    if (EEPROM_AckPolling() == EEPROM_OK)
    {
        return EEPROM_OK;
    }
    else if (EEPROM_AckPolling() == EEPROM_ERR_SLAVE_BUSY)
    {
        return EEPROM_ERR_WRITE;
    }
}

/**
 * @brief  多字节连续写入
 * @note 自动分页
 * @param addr EEPROM 内部数据地址（起始存储地址）
 * @param buf 1 个指针，指向：存放要写入数据的变量
 * @param length 要写入的字节数
 * @return EEPROM 驱动程序错误码
 */
EEPROM_Error_T EEPROM_WriteMultiByte(uint8_t addr, uint8_t *buf, uint8_t length)
{
    EEPROM_Error_T eeprom_error;     //! 用于存储 EEPROM 错误码
    uint8_t page_num, row_num, write_length;

    /* ===================== 参数检查 ===================== */

    /* 内部数据起始地址检查 */
    if (addr > EEPROM_TOTAL_SIZE_KB)
    {
        return EEPROM_ERR_WORD_ADDR;
    }

    /* 写入字节数检查 */
    if ((length == 0) || (length > EEPROM_TOTAL_SIZE_KB))
    {
        return EEPROM_ERR_DATA_SIZE;
    }
    
    /* 待写入的内部数据地址范围检查 */
    if (addr + length > EEPROM_TOTAL_SIZE_KB)
    {
        return EEPROM_ERR_DATA_SIZE;
    }

    /* ===================== 开始自动分页连续写入 ===================== */

    while (length)
    {
        /* 计算当前页序数 */
        page_num = addr / EEPROM_PAGE_SIZE_KB;

        /* 计算当前行数 */
        row_num = addr % EEPROM_PAGE_SIZE_KB;

        /* 计算本页可写字节数 */
        write_length = EEPROM_PAGE_SIZE_KB - row_num;

        /* 如果本页可写字节数 > 需要写入的总字节数 */
        if (write_length > length)
        {
            write_length = length;
        }
        
        /* 页写入 */
        eeprom_error = EEPROM_PageWrite(page_num, row_num, buf, write_length);
        if (eeprom_error != EEPROM_OK)
        {
            return EEPROM_ERR_WRITE;
        }
        
        /* 更新地址、指针和待写入字节数 */
        addr += write_length;
        buf += write_length;
        length -= write_length;
    }
}

/**
 * @brief 从当前地址读取1字节
 * @param buf 1 个指针，指向：存放读取到的数据的变量
 * @return EEPROM 驱动程序错误码
 */
EEPROM_Error_T EEPROM_ReadCurrentByte(uint8_t *read_byte)
{
    iic_states_t iic_state;     //! 用于存储 IIC 状态码

    /* START */
    iic_state = IIC_Start();
    if(iic_state != IIC_OK)
    {
        IIC_Stop();
        return EEPROM_ERR_IIC;
    }

    /* EEPROM 设备地址 + 读 */
    iic_state = IIC_SendByte(EEPROM_IIC_ADDR | 0x01);
    if(iic_state == IIC_ERR_NACK)
    {
        IIC_Stop();
        return EEPROM_ERR_SLAVE_NACK;
    }

    /* 读取 1 字节数据，并发送 NACK */
    iic_state = IIC_ReceiveByte(read_byte, 0);
    if (iic_state != IIC_OK)
    {
        IIC_Stop();
        return EEPROM_ERR_IIC;
    }

    /* STOP */
    iic_state = IIC_Stop();
    if (iic_state != IIC_OK)
    {
        IIC_Stop();
        return EEPROM_ERR_IIC;
    }

    return EEPROM_OK;
}

/**
 * @brief 单字节读取（随机读取）
 * @param addr EEPROM 内部数据地址
 * @param read_byte 1 个指针，指向用于存储读取到的 1 字节数据的变量
 * @return EEPROM 驱动程序错误码
 */
EEPROM_Error_T EEPROM_ByteRead(uint8_t addr, uint8_t *read_byte)
{
    iic_states_t iic_state;          //! 用于存储 IIC 状态码
    EEPROM_Error_T eeprom_error;     //! 用于存储 EEPROM 错误码

    /* ==================== 参数检查 ==================== */

    /* 内部数据地址检查 */
    if (addr >= EEPROM_TOTAL_SIZE_KB)
    {
        return EEPROM_ERR_WORD_ADDR;
    }

    /* ==================== 开始读取 1 个字节 ==================== */

    /* START */
    iic_state = IIC_Start();
    if(iic_state != IIC_OK)
    {
        IIC_Stop();
        return EEPROM_ERR_IIC;
    }

    /* 发送 EEPROM 设备地址 + 写 */
    iic_state = IIC_SendByte(EEPROM_IIC_ADDR);
    if(iic_state == IIC_ERR_NACK)
    {
        IIC_Stop();
        return EEPROM_ERR_SLAVE_NACK;
    }

    /* 发送 EEPROM 内部数据地址 */
    iic_state = IIC_SendByte(addr);
    if(iic_state == IIC_ERR_NACK)
    {
        IIC_Stop();
        return EEPROM_ERR_SLAVE_NACK;
    }

    /* 调用 EEPROM_ReadCurrentByte(); 函数 */
    eeprom_error = EEPROM_ReadCurrentByte(read_byte);

    return eeprom_error;
}

/**
 * @brief 页读取函数
 * @note 单页读取，不能跨页
 * @param page_num 页数，读取数据的页地址（从 0 开始计数）
 * @param row_num 行数，在该页的第几行中开始读取数据（从 0 开始计数）
 * @param buf 1 个指针，指向：存放读取到的数据的变量
 * @param length 要读取的字节数
 * @return EEPROM 驱动程序错误码
 */
EEPROM_Error_T EEPROM_PageRead(uint8_t page_num, uint8_t row_num, uint8_t *buf, uint8_t length)
{
    iic_states_t iic_state;     //! 用于存储 IIC 状态码
    uint8_t i;

    /* ==================== 参数检查 ==================== */

    /* 页数检查 */
    if (page_num >= EEPROM_MAX_PAGE_NUM)
    {
        return EEPROM_ERR_PAGE_NUM;
    }
    
    /* 行数检查 */
    if (row_num >= EEPROM_PAGE_SIZE_KB)
    {
        return EEPROM_ERR_ROW_NUM;
    }
    
    /* 数据长度（字节数）检查 */
    /* 数据长度不能 >= 该页剩余字节数（该页剩余字节数 = 该页总字节数 - 起始行） */
    if (length >= EEPROM_PAGE_SIZE_KB-row_num)
    {
        return EEPROM_ERR_DATA_SIZE;
    }

    /* ==================== 开始页读取 ==================== */

    /* 发送 START */
    iic_state = IIC_Start();
    if(iic_state != IIC_OK)
    {
        IIC_Stop();
        return EEPROM_ERR_IIC;
    }

    /* 发送设备地址 + 写 */
    iic_state = IIC_SendByte(EEPROM_IIC_ADDR);
    if(iic_state == IIC_ERR_NACK)
    {
        IIC_Stop();
        return EEPROM_ERR_SLAVE_NACK;
    }

    /* 发送 EEPROM 内部字节地址 */
    /* 内部字节地址 addr = 0x08 * page_num + row_num */
    iic_state = IIC_SendByte(0x08 * page_num + row_num);
    if(iic_state == IIC_ERR_NACK)
    {
        IIC_Stop();
        return EEPROM_ERR_SLAVE_NACK;
    }

    /* RESTART */
    iic_state = IIC_Restart();
    if(iic_state != IIC_OK)
    {
        IIC_Stop();
        return EEPROM_ERR_IIC;
    }

    /* 发送 EEPROM 设备地址 + 读 */
    iic_state = IIC_SendByte(EEPROM_IIC_ADDR | 0x01);
    if(iic_state == IIC_ERR_NACK)
    {
        IIC_Stop();
        return EEPROM_ERR_SLAVE_NACK;
    }

    /* 读取 (length-1) 个字节的数据，并在每次读取后发送 ACK */
    for (i = 0; i < length-1; i++)
    {
        iic_state = IIC_ReceiveByte(buf + i, 1);
        if (iic_state != IIC_OK)
        {
            IIC_Stop();
            return EEPROM_ERR_IIC;
        }
    }

    /* 读取最后 1 个字节的数据，并发送 NACK */
    iic_state = IIC_ReceiveByte(buf + length - 1, 0);
    if (iic_state != IIC_OK)
    {
        IIC_Stop();
        return EEPROM_ERR_IIC;
    }

    /* STOP */
    iic_state = IIC_Stop();
    if (iic_state != IIC_OK)
    {
        IIC_Stop();
        return EEPROM_ERR_IIC;
    }

    return EEPROM_OK;
}

/**
 * @brief 多字节连续读取
 * @note 自动分页
 * @param addr EEPROM 内部数据地址（起始读取地址）
 * @param buf 1 个指针，指向：存放读取到的数据的变量
 * @param length 要读取的字节数
 * @return EEPROM 驱动程序错误码
 */
EEPROM_Error_T EEPROM_ReadMultiByte(uint8_t addr, uint8_t *buf, uint8_t length)
{
    iic_states_t iic_state;     //! 用于存储 IIC 状态码
    uint8_t i;

    /* ===================== 参数检查 ===================== */

    /* 内部数据起始地址检查 */
    if (addr > EEPROM_TOTAL_SIZE_KB)
    {
        return EEPROM_ERR_WORD_ADDR;
    }

    /* 读取字节数检查 */
    if ((length == 0) || (length > EEPROM_TOTAL_SIZE_KB))
    {
        return EEPROM_ERR_DATA_SIZE;
    }

    /* 待读取的内部数据地址范围检查 */
    if (addr + length > EEPROM_TOTAL_SIZE_KB)
    {
        return EEPROM_ERR_DATA_SIZE;
    }

    /* ===================== 开始连续读取 ===================== */

    /* START */
    iic_state = IIC_Start();
    if(iic_state != IIC_OK)
    {
        IIC_Stop();
        return EEPROM_ERR_IIC;
    }

    /* 发送 EEPROM 设备地址 + 写 */
    iic_state = IIC_SendByte(EEPROM_IIC_ADDR);
    if(iic_state == IIC_ERR_NACK)
    {
        IIC_Stop();
        return EEPROM_ERR_SLAVE_NACK;
    }

    /* 发送 EEPROM 内部数据地址 */
    iic_state = IIC_SendByte(addr);
    if(iic_state == IIC_ERR_NACK)
    {
        IIC_Stop();
        return EEPROM_ERR_SLAVE_NACK;
    }

    /* RESTART */
    iic_state = IIC_Restart();
    if(iic_state != IIC_OK)
    {
        IIC_Stop();
        return EEPROM_ERR_IIC;
    }

    /* 发送 EEPROM 设备地址 + 读 */
    iic_state = IIC_SendByte(EEPROM_IIC_ADDR | 0x01);
    if(iic_state == IIC_ERR_NACK)
    {
        IIC_Stop();
        return EEPROM_ERR_SLAVE_NACK;
    }

    /* 读取 (length-1) 个字节的数据，并在每次读取后发送 ACK */
    for (i = 0; i < length-1; i++)
    {
        iic_state = IIC_ReceiveByte(buf + i, 1);
        if (iic_state != IIC_OK)
        {
            IIC_Stop();
            return EEPROM_ERR_IIC;
        }
    }

    /* 读取最后 1 个字节的数据，并发送 NACK */
    iic_state = IIC_ReceiveByte(buf + length - 1, 0);
    if (iic_state != IIC_OK)
    {
        IIC_Stop();
        return EEPROM_ERR_IIC;
    }

    /* STOP */
    iic_state = IIC_Stop();
    if (iic_state != IIC_OK)
    {
        IIC_Stop();
        return EEPROM_ERR_IIC;
    }

    return EEPROM_OK;
}

/**
 * @brief ACK 轮询函数，等待内部写完成
 * @param None
 * @return EEPROM 驱动程序错误码
 */
EEPROM_Error_T EEPROM_AckPolling(void)
{
    uint8_t retry = 0;

    while (retry < EEPROM_ACK_POLLING_MAX_TRY)
    {
        //! START
        IIC_Start();

        //! 发送设备地址 + 写
        IIC_SendByte(EEPROM_IIC_ADDR);

        //! 如果收到 ACK，说明写完成
        if (IIC_Wait_ACK() == IIC_OK)
        {
            IIC_Stop();
            return EEPROM_OK;
        }
        
        //! 未收到 ACK，内部写未完成，停止本次通信，继续轮询
        IIC_Stop();
        delay_10us(10);       //! 短暂延时
        retry ++;
    }

    /* 超时仍未收到 ACK，返回错误码 */
    return EEPROM_ERR_SLAVE_BUSY;
}

/* ========================= 内部函数声明区域 ========================= */