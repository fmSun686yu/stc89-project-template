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

/** @brief 数码管显示位数（支持 1~8 位） */
#define SEG_DIGIT_COUNT        4

/** @brief 数码管类型定义（不要修改） */
#define SEG_COMMON_CATHODE     0   /** 共阴极数码管 */
#define SEG_COMMON_ANODE       1   /** 共阳极数码管 */

/** @brief 当前数码管类型选择 */
#define SEG_TYPE               SEG_COMMON_CATHODE

#endif  /* _SEGMENT_CONFIGURATION_H_ */