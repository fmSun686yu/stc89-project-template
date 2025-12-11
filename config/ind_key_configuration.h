/**
 * @file ind_key_configuration.h
 * @brief Independent key detection module configuration (macro settings)
 *
 * Place in: config/ind_key_configuration.h
 *
 * @version 1.1.0
 * @author fmSun686yu
 * @date 2025-12-11
 */

#ifndef _IND_KEY_CONFIGURATION_
#define _IND_KEY_CONFIGURATION_

/* =============== 按键配置区域 =============== */

/* Number of independent keys (1..16) */
#define KEY_NUM 16

/*****************************************************
 * @brief 最大按键数上限保护
 * @note 不超过 16
 *****************************************************/
#if (KEY_NUM<1) || (KEY_NUM > 16)
#error "KEY_NUM must be between 1 and 16"
#endif

/****************************************
 * @brief 单片机 I/O 口定义（独立按键）
 ****************************************/
#define KEY0   P2^0
#define KEY1   P2^1
#define KEY2   P2^2
#define KEY3   P2^3
#define KEY4   P2^4
#define KEY5   P2^5
#define KEY6   P2^6
#define KEY7   P2^7
#define KEY8   P3^0
#define KEY9   P3^1
#define KEY10  P3^2
#define KEY11  P3^3
#define KEY12  P3^4
#define KEY13  P3^5
#define KEY14  P3^6
#define KEY15  P3^7

 /***************************************
  * @brief 定义按键电平
  *        0 - 按下时是低电平（常见）
  *        1 - 按下时是高电平
  ***************************************/
#define KEY_ACTIVE_LEVEL  0

/******************************************************************************************************
 * @brief 时间参数配置（单位：ms）
 ******************************************************************************************************/
#define SCAN_INTERVAL_MS  10          /* 扫描间隔（ms），要求 key_scan() 被以此间隔调用 */
#define PRE_DEBOUNCE_MS  60           /* 按下去抖时间（ms），建议 20~50 ms */
#define REL_DEBOUNCE_MS  60           /* 释放去抖时间（ms），建议 0~50 ms */
#define LPRESS1_MS  3000              /* 1阶段长按阈值，可通过修改宏调整（单位：ms） */
#define LPRESS2_MS  6000              /* 2阶段长按阈值，可通过修改宏调整（单位：ms） */
#define LPRESS3_MS  10000             /* 3阶段长按阈值，可通过修改宏调整（单位：ms） */
#define DOUBLE_CLICK_MAX_MS  300      /* 最大双击间隔（释放后到第二次按下）（单位：ms） */

/*****************************************************
 * @brief tick 计算: 把 ms 换算为 tick 单位
 * @note 通过以上参数使用公式计算，不要轻易修改
 *****************************************************/
#define PRE_DEBOUNCE_TICK       PRE_DEBOUNCE_MS/SCAN_INTERVAL_MS     // 按下去抖所需 tick
#define REL_DEBOUNCE_TICK       REL_DEBOUNCE_MS/SCAN_INTERVAL_MS     // 释放去抖所需 tick
#define LPRESS1_TICK        LPRESS1_MS/SCAN_INTERVAL_MS          // 1阶段长按最小 tick
#define LPRESS2_TICK        LPRESS2_MS/SCAN_INTERVAL_MS          // 2阶段长按最小 tick
#define LPRESS3_TICK        LPRESS3_MS/SCAN_INTERVAL_MS          // 3阶段长按最小 tick
#define DOUBLE_CLICK_MAX_TICK        DOUBLE_CLICK_MAX_MS/SCAN_INTERVAL_MS   // 最大双击 tick

#endif  /* _IND_KEY_CONFIGURATION_H_ */