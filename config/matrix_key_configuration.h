/**
 * @file matrix_key_configuration.h
 * @brief Matrix key detection module configuration (macro settings)
 *
 * Place in: config/matrix_key_configuration.h
 *
 * @version 1.0.0
 * @author fmSun686yu
 * @date 2025-12-16
 */

#ifndef _MATRIX_KEY_CONFIGURATION_H_
#define _MATRIX_KEY_CONFIGURATION_H_

#include "../core/stc89.h"

/* ================= 按键配置区域 ================= */

/** 矩阵按键行数 */
#define MATRIX_KEY_ROW_NUM   8

/** 矩阵按键列数 */
#define MATRIX_KEY_COL_NUM   8

/** 行线端口 */
#define ROW_PORT     P1

/** 列线端口 */
#define COL_PORT     P2

/** 扫描间隔，单位：毫秒（ms），要求 key_scan() 被以此间隔调用 */
#define SCAN_INTERVAL_MS  10          

/** 消抖时长，单位：毫秒（ms） */
#define DEBOUNCE_MS  50

/*****************************************************
 * @brief tick 计算: 把 ms 换算为 tick 单位
 * @note 通过以上参数使用公式计算，不要轻易修改
 *****************************************************/
#define DEBOUNCE_TICK       DEBOUNCE_MS/SCAN_INTERVAL_MS     // 去抖所需 tick

#endif      /* _MATRIX_KEY_CONFIGURATION_H_ */