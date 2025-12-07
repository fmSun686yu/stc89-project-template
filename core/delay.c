/**
 **********************************************************************
 * @file    delay.c
 * @brief   粗略软件延时实现（基于 NOP 循环）
 *
 * @note
 *  - 该延时程序主要通过 STC-ISP 的软件延时计算器生成，提供以下晶振频率的软件延时函数：
 *      - 5.5296 MHz
 *      - 6.000 MHz
 *      - 11.0592 MHz
 *      - 12.000 MHz
 *      - 18.432 MHz
 *      - 20.000 MHz
 *      - 22.1184 MHz
 *      - 24.000 MHz
 *      - 27.000 MHz
 *      - 30.000 MHz
 *      - 33.000 MHz
 *      - 33.1176 MHz
 *      - 35.000 MHz
 *      - 36.864 MHz
 *      - 40.000 MHz
 *      - 44.2368 MHz
 *      - 45.1584 MHz
 *      - 48.000 MHz
 *      - 50.8032 MHz
 *      - 52.000 MHz
 *      - 56.000 MHz
 * 
 *  - 与以上晶振频率都不符合的软件延时函数，
 *    可以将实际晶振频率取近似值以符合以上提供的晶振频率，
 *    或请自行编写软件延时程序
 *  - 请根据单片机实际晶振频率修改 "../config/configuration.h" 中的宏定义 FOSC_HZ
 *    以自动选择匹配的软件延时函数
 * 
 *  - 精度：
 *      该实现更注重可移植性与可配置性（通过宏），而非亚微秒级精度。
 *      若需更精确延时（例如通信协议时序），请使用定时器或用汇编根据具体指令时序微调。
 * 
 * @attention 请将 C 语言代码优化级别设置为默认
 *
 * @version 1.0.1
 * @author  ForeverMySunyu
 * @date    2025-12-07
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

#if FOSC_HZ == 20000000     // @20.000MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 = 20.000 MHz
 */
void delay_10us(uint8_t n)
{
    unsigned char data i;

    while(n--)
    {
	    _nop_();
        i = 5;
        while (--i);
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 = 20.000 MHz
 */
void delay_1ms(uint16_t n)
{
    unsigned char data i, j;

    while(n--)
    {
        i = 4;
        j = 58;
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
 * @note 晶振频率 = 20.000 MHz
 */
void delay_1s(uint16_t n)
{
    unsigned char data i, j, k;

    while(n--)
    {
        _nop_();
        i = 13;
        j = 171;
        k = 121;
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

#if FOSC_HZ == 22118400     // @22.1184MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 = 22.1184 MHz
 */
void delay_10us(uint8_t n)
{
    unsigned char data i;

    while(n--)
    {
	    _nop_();
        i = 6;
        while (--i);
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 = 22.1184 MHz
 */
void delay_1ms(uint16_t n)
{
    unsigned char data i, j;

    while(n--)
    {
        _nop_();
        i = 4;
        j = 146;
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
 * @note 晶振频率 = 22.1184 MHz
 */
void delay_1s(uint16_t n)
{
    unsigned char data i, j, k;

    while(n--)
    {
        _nop_();
        i = 15;
        j = 2;
        k = 235;
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

#if FOSC_HZ == 24000000     // @24.000MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 = 24.000 MHz
 */
void delay_10us(uint8_t n)
{
    unsigned char data i;

    while(n--)
    {
	    _nop_();
        i = 7;
        while (--i);
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 = 24.000 MHz
 */
void delay_1ms(uint16_t n)
{
    unsigned char data i, j;

    while(n--)
    {
        i = 4;
        j = 225;
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
 * @note 晶振频率 = 24.000 MHz
 */
void delay_1s(uint16_t n)
{
    unsigned char data i, j, k;

    while(n--)
    {
        _nop_();
        i = 16;
        j = 51;
        k = 249;
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

#if FOSC_HZ == 27000000     // @27.000MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 = 27.000 MHz
 */
void delay_10us(uint8_t n)
{
    unsigned char data i;

    while(n--)
    {
	    _nop_();
        i = 8;
        while (--i);
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 = 27.000 MHz
 */
void delay_1ms(uint16_t n)
{
    unsigned char data i, j;

    while(n--)
    {
        i = 5;
        j = 93;
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
 * @note 晶振频率 = 27.000 MHz
 */
void delay_1s(uint16_t n)
{
    unsigned char data i, j, k;

    while(n--)
    {
        _nop_();
        i = 18;
        j = 26;
        k = 88;
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

#if FOSC_HZ == 30000000     // @30.000MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 = 30.000 MHz
 */
void delay_10us(uint8_t n)
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
 * @note 晶振频率 = 30.000 MHz
 */
void delay_1ms(uint16_t n)
{
    unsigned char data i, j;

    while(n--)
    {
        i = 5;
        j = 218;
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
 * @note 晶振频率 = 30.000 MHz
 */
void delay_1s(uint16_t n)
{
    unsigned char data i, j, k;

    while(n--)
    {
        _nop_();
        i = 19;
        j = 0;
        k = 185;
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

#if FOSC_HZ == 33000000     // @33.000MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 = 33.000 MHz
 */
void delay_10us(uint8_t n)
{
    unsigned char data i;

    while(n--)
    {
	    i = 11;
	    while (--i);
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 = 33.000 MHz
 */
void delay_1ms(uint16_t n)
{
    unsigned char data i, j;

    while(n--)
    {
        i = 6;
        j = 86;
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
 * @note 晶振频率 = 33.000 MHz
 */
void delay_1s(uint16_t n)
{
    unsigned char data i, j, k;

    while(n--)
    {
        _nop_();
        i = 21;
        j = 231;
        k = 24;
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

#if FOSC_HZ == 33177600     // @33.1776MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 = 33.1776 MHz
 */
void delay_10us(uint8_t n)
{
    unsigned char data i;

    while(n--)
    {
	    i = 11;
	    while (--i);
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 = 33.1776 MHz
 */
void delay_1ms(uint16_t n)
{
    unsigned char data i, j;

    while(n--)
    {
        i = 6;
        j = 93;
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
 * @note 晶振频率 = 33.1776 MHz
 */
void delay_1s(uint16_t n)
{
    unsigned char data i, j, k;

    while(n--)
    {
        _nop_();
        i = 22;
        j = 3;
        k = 227;
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

#if FOSC_HZ == 35000000     // @35.000MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 = 35.000 MHz
 */
void delay_10us(uint8_t n)
{
    unsigned char data i;

    while(n--)
    {
	    i = 12;
	    while (--i);
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 = 35.000 MHz
 */
void delay_1ms(uint16_t n)
{
    unsigned char data i, j;

    while(n--)
    {
        i = 6;
        j = 169;
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
 * @note 晶振频率 = 35.000 MHz
 */
void delay_1s(uint16_t n)
{
    unsigned char data i, j, k;

    while(n--)
    {
        _nop_();
        i = 23;
        j = 43;
        k = 87;
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

#if FOSC_HZ == 36864000     // @36.864MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 = 36.864 MHz
 */
void delay_10us(uint8_t n)
{
    unsigned char data i;

    while(n--)
    {
        _nop_();
	    i = 12;
	    while (--i);
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 = 36.864 MHz
 */
void delay_1ms(uint16_t n)
{
    unsigned char data i, j;

    while(n--)
    {
        i = 6;
        j = 247;
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
 * @note 晶振频率 = 36.864 MHz
 */
void delay_1s(uint16_t n)
{
    unsigned char data i, j, k;

    while(n--)
    {
        _nop_();
        i = 24;
        j = 89;
        k = 139;
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

#if FOSC_HZ == 40000000     // @40.000MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 = 40.000 MHz
 */
void delay_10us(uint8_t n)
{
    unsigned char data i;

    while(n--)
    {
	    i = 14;
	    while (--i);
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 = 40.000 MHz
 */
void delay_1ms(uint16_t n)
{
    unsigned char data i, j;

    while(n--)
    {
        _nop_();
        i = 7;
        j = 120;
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
 * @note 晶振频率 = 40.000 MHz
 */
void delay_1s(uint16_t n)
{
    unsigned char data i, j, k;

    while(n--)
    {
        i = 26;
        j = 85;
        k = 248;
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

#if FOSC_HZ == 44236800     // @44.2368MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 = 44.2368 MHz
 */
void delay_10us(uint8_t n)
{
    unsigned char data i;

    while(n--)
    {
        _nop_();
	    i = 15;
	    while (--i);
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 = 44.2368 MHz
 */
void delay_1ms(uint16_t n)
{
    unsigned char data i, j;

    while(n--)
    {
        i = 8;
        j = 40;
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
 * @note 晶振频率 = 44.2368 MHz
 */
void delay_1s(uint16_t n)
{
    unsigned char data i, j, k;

    while(n--)
    {
        _nop_();
        i = 29;
        j = 4;
        k = 219;
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

#if FOSC_HZ == 45158400     // @45.1584MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 = 45.1584 MHz
 */
void delay_10us(uint8_t n)
{
    unsigned char data i;

    while(n--)
    {
	    i = 16;
	    while (--i);
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 = 45.1584 MHz
 */
void delay_1ms(uint16_t n)
{
    unsigned char data i, j;

    while(n--)
    {
        _nop_();
        i = 8;
        j = 78;
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
 * @note 晶振频率 = 45.1584 MHz
 */
void delay_1s(uint16_t n)
{
    unsigned char data i, j, k;

    while(n--)
    {
        _nop_();
        i = 29;
        j = 154;
        k = 69;
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

#if FOSC_HZ == 48000000     // @48.000MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 = 48.000 MHz
 */
void delay_10us(uint8_t n)
{
    unsigned char data i;

    while(n--)
    {
        _nop_();
	    i = 17;
	    while (--i);
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 = 48.000 MHz
 */
void delay_1ms(uint16_t n)
{
    unsigned char data i, j;

    while(n--)
    {
        i = 8;
        j = 197;
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
 * @note 晶振频率 = 48.000 MHz
 */
void delay_1s(uint16_t n)
{
    unsigned char data i, j, k;

    while(n--)
    {
        _nop_();
        i = 31;
        j = 102;
        k = 247;
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

#if FOSC_HZ == 50803200     // @50.8032MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 = 50.8032 MHz
 */
void delay_10us(uint8_t n)
{
    unsigned char data i;

    while(n--)
    {
        _nop_();
	    i = 18;
	    while (--i);
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 = 50.8032 MHz
 */
void delay_1ms(uint16_t n)
{
    unsigned char data i, j;

    while(n--)
    {
        _nop_();
        i = 9;
        j = 56;
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
 * @note 晶振频率 = 50.8032 MHz
 */
void delay_1s(uint16_t n)
{
    unsigned char data i, j, k;

    while(n--)
    {
        _nop_();
        i = 33;
        j = 45;
        k = 110;
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

#if FOSC_HZ == 52000000     // @52.000MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 = 52.000 MHz
 */
void delay_10us(uint8_t n)
{
    unsigned char data i;

    while(n--)
    {
	    i = 19;
	    while (--i);
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 = 52.000 MHz
 */
void delay_1ms(uint16_t n)
{
    unsigned char data i, j;

    while(n--)
    {
        _nop_();
        i = 9;
        j = 106;
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
 * @note 晶振频率 = 52.000 MHz
 */
void delay_1s(uint16_t n)
{
    unsigned char data i, j, k;

    while(n--)
    {
        i = 33;
        j = 239;
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

#if FOSC_HZ == 56000000     // @56.000MHz

/**
 * @name delay_10us
 * @brief 粗略延时： n * 10 microsecond（大致）
 * @param n 延时倍数（单位 10 us）
 * @note 晶振频率 = 56.000 MHz
 */
void delay_10us(uint8_t n)
{
    unsigned char data i;

    while(n--)
    {
        _nop_();
	    i = 20;
	    while (--i);
    }
}

/**
 * @name delay_1ms
 * @brief 粗略延时： n * 1 millisecond（大致）
 * @param n 延时倍数（单位 1 ms）
 * @note 晶振频率 = 56.000 MHz
 */
void delay_1ms(uint16_t n)
{
    unsigned char data i, j;

    while(n--)
    {
        i = 10;
        j = 16;
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
 * @note 晶振频率 = 56.000 MHz
 */
void delay_1s(uint16_t n)
{
    unsigned char data i, j, k;

    while(n--)
    {
        _nop_();
        i = 36;
        j = 119;
        k = 246;
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