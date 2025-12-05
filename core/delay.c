/**
 **********************************************************************
 * @file    delay.c
 * @brief   粗略软件延时实现（基于 NOP 循环）
 *
 * @note
 *  - 该延时程序主要通过 STC-ISP 的软件延时计算器生成，提供以下晶振频率的软件延时函数：
 *      - 11.0592 MHZ
 * 
 *  - 与以上晶振频率都不符合的软件延时函数，
 *    可以将实际晶振频率取近似值以符合以上提供的晶振频率，
 *    或请自行编写软件延时程序
 *  - 请根据单片机实际晶振频率修改 delay.h 文件中的宏定义 FOSC_HZ
 *    以自动选择匹配的软件延时函数
 * 
 *  - 精度：
 *      该实现更注重可移植性与可配置性（通过宏），而非亚微秒级精度。
 *      若需更精确延时（例如通信协议时序），请使用定时器或用汇编根据具体指令时序微调。
 * 
 * @attention 请将 C 语言代码优化级别设置为默认
 *
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-04
 **********************************************************************
*/

#include "delay.h"

/* ======根据单片机晶振频率来选择匹配的软件延时函数====== */

#if FOSC_HZ == 5529600     // @5.5296MHz

/**
 * @name delay_50us
 * @brief 粗略延时： n * 50 microsecond（大致）
 * @param n 延时倍数（单位 50 us）
 * @note 晶振频率 = 5.5296 MHz
 */
void delay_50us(uint8_t n)
{
    unsigned char data i;

    while(n--)
    {
	    i = 9;
	    while (--i);
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 = 5.5296 MHz
 */
void delay_1ms(uint16_t n)
{
    unsigned char data i;

    while(n--)
    {
        _nop_();
        i = 227;
        while (--i);
    }
}

/**
 * @name delay_1s
 * @brief 粗略延时： n * 1 second（大致）
 * @param n 延时倍数（单位 1 s）
 * @note 晶振频率 = 5.5296 MHz
 */
void delay_1s(uint16_t n)
{
    unsigned char data i, j, k;

    while(n--)
    {
        _nop_();
        i = 4;
        j = 129;
        k = 119;
        do
        {
            do
            {
                while (--k);
            } while (--j);
        } while (--i);
    }
}

#endif

#if FOSC_HZ == 6000000     // @6.000MHz

/**
 * @name delay_50us
 * @brief 粗略延时： n * 50 microsecond（大致）
 * @param n 延时倍数（单位 50 us）
 * @note 晶振频率 = 6.000 MHz
 */
void delay_50us(uint8_t n)
{
	unsigned char data i;

    while(n--)
    {
        i = 10;
	    while (--i);
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 = 6.000 MHz
 */
void delay_1ms(uint16_t n)
{
    unsigned char data i;

    while(n--)
    {
        _nop_();
        i = 247;
        while (--i);
    }
}

/**
 * @name delay_1s
 * @brief 粗略延时： n * 1 second（大致）
 * @param n 延时倍数（单位 1 s）
 * @note 晶振频率 =  MHz
 */
void delay_1s(uint16_t n)
{
	unsigned char data i, j, k;

    while(n--)
    {
        _nop_();
        i = 4;
        j = 205;
        k = 187;
        do
        {
            do
            {
                while (--k);
            } while (--j);
        } while (--i);
    }
}

#endif

#if FOSC_HZ == 11059200     // @11.0592MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 = 11.0592 MHz
 */
void delay_10us(uint8_t n)
{
    unsigned char data i;

    while(n--)
    {
	    i = 2;
	    while (--i);
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 = 11.0592 MHz
 */
void delay_1ms(uint16_t n)
{
    unsigned char data i, j;

    while(n--)
    {
        _nop_();
        i = 2;
        j = 199;
        do
        {
            while (--j);
        } while (--i);
    }
}

/**
 * @name delay_1s
 * @brief 粗略延时： n * 1 second（大致）
 * @param n 延时倍数（单位 1 s）
 * @note 晶振频率 = 11.0592 MHz
 */
void delay_1s(uint16_t n)
{
	unsigned char data i, j, k;

    while(n--)
    {
        _nop_();
        i = 8;
        j = 1;
        k = 243;
        do
        {
            do
            {
                while (--k);
            } while (--j);
        } while (--i);
    }
}

#endif

#if FOSC_HZ == 12000000     // @12.000MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 = 12.000 MHz
 */
void delay_10us(uint8_t n)
{

    while(n--)
    {
	    
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 = 12.000 MHz
 */
void delay_1ms(uint16_t n)
{

    while(n--)
    {
        
    }
}

/**
 * @name delay_1s
 * @brief 粗略延时： n * 1 second（大致）
 * @param n 延时倍数（单位 1 s）
 * @note 晶振频率 = 12.000 MHz
 */
void delay_1s(uint16_t n)
{

    while(n--)
    {
        
    }
}

#endif

#if FOSC_HZ == 18432000     // @18.432MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 = 18.432 MHz
 */
void delay_10us(uint8_t n)
{
    unsigned char data i;

    while(n--)
    {
	    i = 5;
	    while (--i);

    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 = 18.432 MHz
 */
void delay_1ms(uint16_t n)
{
    unsigned char data i, j;

    while(n--)
    {
        i = 3;
        j = 250;
        do
        {
            while (--j);
        } while (--i);

    }
}

/**
 * @name delay_1s
 * @brief 粗略延时： n * 1 second（大致）
 * @param n 延时倍数（单位 1 s）
 * @note 晶振频率 = 18.432 MHz
 */
void delay_1s(uint16_t n)
{
    unsigned char data i, j, k;

    while(n--)
    {
        _nop_();
        i = 12;
        j = 173;
        k = 67;
        do
        {
            do
            {
                while (--k);
            } while (--j);
        } while (--i);
    }
}

#endif

#if FOSC_HZ ==      // @MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 =  MHz
 */
void delay_10us(uint8_t n)
{

    while(n--)
    {
	    
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 =  MHz
 */
void delay_1ms(uint16_t n)
{

    while(n--)
    {
        
    }
}

/**
 * @name delay_1s
 * @brief 粗略延时： n * 1 second（大致）
 * @param n 延时倍数（单位 1 s）
 * @note 晶振频率 =  MHz
 */
void delay_1s(uint16_t n)
{

    while(n--)
    {
        
    }
}

#endif

#if FOSC_HZ ==      // @MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 =  MHz
 */
void delay_10us(uint8_t n)
{

    while(n--)
    {
	    
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 =  MHz
 */
void delay_1ms(uint16_t n)
{

    while(n--)
    {
        
    }
}

/**
 * @name delay_1s
 * @brief 粗略延时： n * 1 second（大致）
 * @param n 延时倍数（单位 1 s）
 * @note 晶振频率 =  MHz
 */
void delay_1s(uint16_t n)
{

    while(n--)
    {
        
    }
}

#endif

#if FOSC_HZ ==      // @MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 =  MHz
 */
void delay_10us(uint8_t n)
{

    while(n--)
    {
	    
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 =  MHz
 */
void delay_1ms(uint16_t n)
{

    while(n--)
    {
        
    }
}

/**
 * @name delay_1s
 * @brief 粗略延时： n * 1 second（大致）
 * @param n 延时倍数（单位 1 s）
 * @note 晶振频率 =  MHz
 */
void delay_1s(uint16_t n)
{

    while(n--)
    {
        
    }
}

#endif

#if FOSC_HZ ==      // @MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 =  MHz
 */
void delay_10us(uint8_t n)
{

    while(n--)
    {
	    
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 =  MHz
 */
void delay_1ms(uint16_t n)
{

    while(n--)
    {
        
    }
}

/**
 * @name delay_1s
 * @brief 粗略延时： n * 1 second（大致）
 * @param n 延时倍数（单位 1 s）
 * @note 晶振频率 =  MHz
 */
void delay_1s(uint16_t n)
{

    while(n--)
    {
        
    }
}

#endif

#if FOSC_HZ ==      // @MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 =  MHz
 */
void delay_10us(uint8_t n)
{

    while(n--)
    {
	    
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 =  MHz
 */
void delay_1ms(uint16_t n)
{

    while(n--)
    {
        
    }
}

/**
 * @name delay_1s
 * @brief 粗略延时： n * 1 second（大致）
 * @param n 延时倍数（单位 1 s）
 * @note 晶振频率 =  MHz
 */
void delay_1s(uint16_t n)
{

    while(n--)
    {
        
    }
}

#endif

#if FOSC_HZ ==      // @MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 =  MHz
 */
void delay_10us(uint8_t n)
{

    while(n--)
    {
	    
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 =  MHz
 */
void delay_1ms(uint16_t n)
{

    while(n--)
    {
        
    }
}

/**
 * @name delay_1s
 * @brief 粗略延时： n * 1 second（大致）
 * @param n 延时倍数（单位 1 s）
 * @note 晶振频率 =  MHz
 */
void delay_1s(uint16_t n)
{

    while(n--)
    {
        
    }
}

#endif

#if FOSC_HZ ==      // @MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 =  MHz
 */
void delay_10us(uint8_t n)
{

    while(n--)
    {
	    
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 =  MHz
 */
void delay_1ms(uint16_t n)
{

    while(n--)
    {
        
    }
}

/**
 * @name delay_1s
 * @brief 粗略延时： n * 1 second（大致）
 * @param n 延时倍数（单位 1 s）
 * @note 晶振频率 =  MHz
 */
void delay_1s(uint16_t n)
{

    while(n--)
    {
        
    }
}

#endif