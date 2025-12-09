/**
 * @file key_configuration.h
 * @brief Key detection module configuration (macro settings)
 * @note Includes independent keys and matrix keys
 *
 * Place in: config/key_config.h
 *
 * @version 1.0.0
 * @author fmSun686yu
 * @date 2025-12-08
 */

#ifndef _KEY_CONFIGURATION_
#define _KEY_CONFIGURATION_

/* =============== 独立按键配置区域 =============== */

/* Number of independent keys (1..16) */
#define IND_KEY_NUM 16

/*****************************************************
 * @brief 最大按键数上限保护
 * @note 不超过 16
 *****************************************************/
#if (IND_KEY_NUM<1) || (IND_KEY_NUM > 16)
#error "IND_KEY_NUM must be between 1 and 16"
#endif

/****************************************
 * @brief 单片机 I/O 口定义（独立按键）
 ****************************************/
#define IND_KEY0   P2^0
#define IND_KEY1   P2^1
#define IND_KEY2   P2^2
#define IND_KEY3   P2^3
#define IND_KEY4   P2^4
#define IND_KEY5   P2^5
#define IND_KEY6   P2^6
#define IND_KEY7   P2^7
#define IND_KEY8   P3^0
#define IND_KEY9   P3^1
#define IND_KEY10  P3^2
#define IND_KEY11  P3^3
#define IND_KEY12  P3^4
#define IND_KEY13  P3^5
#define IND_KEY14  P3^6
#define IND_KEY15  P3^7

 /***************************************
  * @brief 定义按键电平
  *        0 - 按下时是低电平（常见）
  *        1 - 按下时是高电平
  ***************************************/
#define IND_KEY_ACTIVE_LEVEL  0

/******************************************************************************************************
 * @brief 时间参数配置（单位：ms）
 ******************************************************************************************************/
#define IND_SCAN_INTERVAL_MS  10          /* 扫描间隔（ms），要求 ind_key_scan() 被以此间隔调用 */
#define IND_DEBOUNCE_MS  60               /* 去抖时间（ms），建议 20~50 ms */
#define IND_LPRESS1_MS  3000              /* 1阶段长按阈值，可通过修改宏调整（单位：ms） */
#define IND_LPRESS2_MS  6000              /* 2阶段长按阈值，可通过修改宏调整（单位：ms） */
#define IND_LPRESS3_MS  10000             /* 3阶段长按阈值，可通过修改宏调整（单位：ms） */
#define IND_DOUBLE_CLICK_MAX_MS  300      /* 最大双击间隔（释放后到第二次按下）（单位：ms） */

/*****************************************************
 * @brief tick 计算: 把 ms 换算为 tick 单位
 * @note 通过以上参数使用公式计算，不要轻易修改
 *****************************************************/
#define IND_DEBOUNCE_TICK        IND_DEBOUNCE_MS/IND_SCAN_INTERVAL_MS     // 去抖所需 tick
#define IND_LPRESS1_TICK        IND_LPRESS1_MS/IND_SCAN_INTERVAL_MS       // 1阶段长按最小 tick
#define IND_LPRESS2_TICK        IND_LPRESS2_MS/IND_SCAN_INTERVAL_MS       // 2阶段长按最小 tick
#define IND_LPRESS3_TICK        IND_LPRESS3_MS/IND_SCAN_INTERVAL_MS       // 3阶段长按最小 tick
#define IND_DOUBLE_CLICK_MAX_TICK        IND_DOUBLE_CLICK_MAX_MS/IND_SCAN_INTERVAL_MS   // 最大双击 tick

/* =============== 矩阵按键配置区域 =============== */



#endif