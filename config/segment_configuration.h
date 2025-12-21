/**
 * @file    segment_configuration.h
 * @brief   数码管显示模块的全局配置文件
 * @version 1.0.0
 * @author  ForeverMySunyu
 * @date    2025-12-19
 *
 * @details
 * 本文件用于配置数码管显示模块的所有可变参数，
 * 包括显示位数、共阳/共阴类型等。
 * 修改配置无需修改驱动源码。
 */

#ifndef _SEGMENT_CONFIGURATION_H_
#define _SEGMENT_CONFIGURATION_H_

#include "../core/stc89.h"

/** @brief 数码管显示位数（支持 1~8 位） */
#define SEG_DIGIT_COUNT        8

/** @brief 数码管类型定义（不要修改） */
typedef enum
{
    SEG_COMMON_CATHODE = 0,   /**< 共阴极 */
    SEG_COMMON_ANODE          /**< 共阳极 */
} seg_type_t;

/** @brief 当前数码管类型选择 */
#define SEG_TYPE               SEG_COMMON_ANODE

/** @brief 是否使用38译码器（0-不使用，1-使用） */
#define _74HC138               0

/** @brief 段码端口（a~g, dp） */
#define SEGMENT_PORT       P1

/** @brief 位选端口 */
#define DIGIT_PORT         P2

#endif  /* _SEGMENT_CONFIGURATION_H_ */