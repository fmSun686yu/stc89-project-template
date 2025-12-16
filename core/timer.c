/**
 ******************************************************************************************************************
 * @file    timer.c
 * @brief   51单片机 core 层定时器初始化及中断服务程序源文件 — 适用于 STC89C516RD+ 型号单片机并兼容 STC89 系列单片机
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-15
 ******************************************************************************************************************
*/

#include "timer.h"



/* =========================== 定时器初始化函数 ==============================*/

/**
 * @brief 定时器0初始化函数
 * @note Timer0 用于定时50us并产生中断，进入中断服务程序
 * @param None
 * @return None
 */
void Timer0_Init(void)
{
    //! 停止 T0
    TR0 = 0;

    //! 设置 GATE 控制位
    #if TIMER0_GATE
        TMOD |= 0x08; 
    #else
        TMOD &= 0xf7;
    #endif

    //! 设置 C/T 控制位
    #if TIMER0_CT
        TMOD |= 0x04;
    #else
        TMOD &= 0xfb;
    #endif

    //! 设置 MODE
    #if TIMER0_MODE == 0
        TMOD &= 0xfc;
    #elif TIMER0_MODE == 1
        TMOD |= 0x01;
        TMOD &= 0xfd;
    #elif TIMER0_MODE == 2
        TMOD &= 0xfe;
        TMOD |= 0x02;
    #elif TIMER0_MODE == 3
        TMOD |= 0xf3;
    #else
        #error "The setting of TIMER0_MODE is incorrect."
    #endif

    //! 设置定时器初值
    TL0 = TIMER0_VALUE & 0x00ff;
    TH0 = TIMER0_VALUE >> 8;

    #if TIMER0_MODE == 3
        TF0 = 0;            //! T0(TL0) 溢出中断标志清零
        TF1 = 0;            //! T1(TH0) 溢出中断标志清零

        TR0 = 1;            //! 启动 T0(TL0)
        TR1 = 1;            //! 启动 T1(TH0)

    #else
        TF0 = 0;            //! T0 溢出中断标志清零

        ET0 = 1;            //! 开 T2 中断

        TR0 = 1;            //! 启动 T0

    #endif
}

/**
 * @brief 定时器1初始化函数
 * @note Timer1 用于产生串口通信波特率
 * @param None
 * @return None
 */
void Timer1_Init(void)
{
    //! 停止 T1
    TR1 = 0;

    //! 设置 GATE 控制位
    #if TIMER1_GATE
        TMOD |= 0x80; 
    #else
        TMOD &= 0x7f;
    #endif

    //! 设置 C/T 控制位
    #if TIMER1_CT
        TMOD |= 0x40;
    #else
        TMOD &= 0xbf;
    #endif

    //! 设置 MODE
    #if TIMER1_MODE == 0
        TMOD &= 0xcf;
    #elif TIMER1_MODE == 1
        TMOD |= 0x10;
        TMOD &= 0xdf;
    #elif TIMER1_MODE == 2
        TMOD &= 0xef;
        TMOD |= 0x20;
    #else
        #error "The setting of TIMER1_MODE is incorrect."
    #endif

    //! 设置定时器初值
    TL1 = TIMER1_VALUE & 0x00ff;
    TH1 = TIMER1_VALUE >> 8;

    //! T1 溢出中断标志清零
    TF1 = 0;

    //! 启动 T1
    TR1 = 1;
}

/**
 * @brief 定时器2初始化函数
 * @note Timer2 用于独立按键定时循环扫描
 * @param None
 * @return None
 */
void Timer2_Init(void)
{
    TF2 = 0;            //! 清除 T2 溢出标志
    EXF2 = 0;           //! 清除 T2 外部标志
    RCLK = TIMER2_RCLK;         //! 接收时钟标志
    TCLK = TIMER2_TCLK;         //! 发送时钟标志
    EXEN2 = TIMER2_EXEN2;       //! T2 外部使能标志
    C_T2 = TIMER2_C_T;          //! 定时器/计数器选择
    CP_RL2 = TIMER2_CP_RL;      //! 捕获/重装标志

    //! 设置 T2MOD
    #if TIMER2_T2OE
        #if TIMER2_DCEN
            T2MOD = 0x03;
        #else
            T2MOD = 0x02;
        #endif
    #else
        #if TIMER2_DCEN
            T2MOD = 0x01;
        #else
            T2MOD = 0x00;
        #endif
    #endif

    //! 设置定时器初值
    RCAP2L = TIMER2_VALUE & 0x00ff;
    RCAP2H = TIMER2_VALUE >> 8;

    //! 开 T2 中断
    ET2 = 1;

    //! 启动 T2
    TR1 = 1;
}

/* =========================== 回调函数定义与注册 =========================== */

static Timer2_Routine_Callback_t timer2_routine_callback = NULL;            //! 定时器2中断回调函数指针，保存由上层（HAL）注册的回调接口

/**
 * @brief 定时器2中断服务程序中的回调函数注册接口
 * @note 供上层（HAL）调用注册
 * @param cb 回调函数指针
 * @return None
 */
void timer2_register_callback(Timer2_Routine_Callback_t cb)
{
    timer2_routine_callback = cb;
}



/* =========================== 定时器中断服务程序 ==============================*/

/**
 * @brief 定时器0中断服务程序
 * @note Timer0 用于定时50us并产生中断，进入该中断服务程序
 * @param None
 * @return None
 */
void Timer0_Routine(void) interrupt 1
{

}

/**
 * @brief 定时器1中断服务程序
 * @note Timer1 用于产生串口通信波特率，无需编写中断服务程序
 * @param None
 * @return None
 */
void Timer1_Routine(void) interrupt 3
{

}

/**
 * @brief 定时器2中断服务程序
 * @note Timer2 用于独立按键定时循环扫描
 * @param None
 * @return None
 */
void Timer2_Routine(void) interrupt 5
{
    if(timer2_routine_callback != NULL)
    {
        timer2_routine_callback();          //! 以回调函数形式调用独立按键检测程序
    }    
}