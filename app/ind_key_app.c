/**
 * @file ind_key_app.c
 * @brief Application Layer of the Independent Key Detection Module
 * @note Target MCU: STC89C516RD+ (51-family)
 * 
 * - 独立按键事件处理程序
 * 
 * 功能：
 *  - 支持对 1~16 个独立按键的事件响应
 *  - 支持以下事件：短按、1阶段长按、2阶段长按、3阶段长按、双击、组合键、释放
 * 
 * 设计说明：
 *  - 在主循环中检测全局按键事件标志变量结构体 key_event_flag 来查询独立按键事件，进而对事件进行处理
 * 
 * @version 1.0.0
 * @author fmSun686yu
 * @date 2025-12-16
 */

 #include "ind_key_app.h"

 