/**
 * @file matrix_key_hal.C
 * @brief Hardware Abstraction Layer of the Matrix Key and Matrix Key Detection Module
 * @note Target MCU: STC89C516RD+ (51-family)
 *
 * 功能：
 * - 矩阵按键检测：
 *     - 支持 8*8 矩阵按键的检测
 *     - 支持事件：短按、释放检测
 *     - 可配置扫描间隔（SCAN_INTERVAL_MS）和消抖时长（DEBOUNCE_MS）
 *     - 软件去抖动
 *     - 定时器扫描 + 按键状态机实现
 *
 * 使用方法：
 * - 在定时器中断或主循环中以 10ms 周期调用 matrix_key_scan();
 * 
 * @version 1.0.0
 * @author ForeverMySunyu
 * @date 2025-12-17
 */

#include "matrix_key_hal.h"
#include "../bsp/matrix_key_bsp.h"
#include "../config/matrix_key_configuration.h"

/* ================ 按键数据结构体 ================ */
typedef struct
{
    key_state_t state;        //! 当前状态
    uint16_t tick;            //! 当前状态持续 tick
} key_data_t;

/* ===================== 静态变量 ===================== */
static key_data_t key_data[MATRIX_KEY_ROW_NUM][MATRIX_KEY_COL_NUM];    //! 按键数据数组

/* ===================================== API 函数定义 ===================================== */

/**
 * @brief  HAL 矩阵按键初始化函数
 */
void key_hal_init(void)
{
    uint8_t i, j;

    key_bsp_init();

    //! 初始化所有按键状态
    for(i=0;i<MATRIX_KEY_ROW_NUM;i++)
    {
        for(j=0;j<MATRIX_KEY_COL_NUM;j++)
        {
            key_data[i][j].state = KEY_STATE_IDLE;
            key_data[i][j].tick = 0;
        }
    }
}

/**
 * @brief 全局按键事件标志变量清除函数
 * @param None
 * @return None
 */
void key_clear_event(void)
{
    key_event_flag.key_id = 0xff;
    key_event_flag.key_press = 0;
    key_event_flag.key_state = KEY_STATE_IDLE;
}

/* ===================================== 内部函数定义 ===================================== */

/**
 * @brief 按键扫描函数，调用按键状态机函数
 * @note 必须周期性调用：以 SCAN_INTERVAL_MS 为周期调用（通常放在定时器中断中）
 * @param None
 * @return None
 */
static void key_scan(void)
{
    uint8_t i, j, full_col_level_states;

    //! 逐行扫描
    for(i=0;i<MATRIX_KEY_ROW_NUM;i++)
    {
        key_set_row(i);         //! 设置第i行为低电平
        full_col_level_states = key_read_columns();           //! 获取所有列的电平状态

        //! 逐列运行按键状态机
        for(j=0;j<MATRIX_KEY_COL_NUM;j++)
        {
            key_state_machine(i, j, full_col_level_states & (0x01<<j));
        }
    }
}

/**
 * @brief 按键状态机
 * @note key_scan(); 中循环调用，每次调用更新一次对应按键的状态
 * @param i 按键行号
 * @param j 按键列号
 * @param key_level 按键电平，0-低电平，1-高电平
 * @return None
 */
static void key_state_machine(uint8_t i, uint8_t j, bool key_level)
{
    key_data_t *key = &key_data[i][j];        //! 定义一个指针，指向对应的按键数据数组

    switch (key->state)
    {
    case KEY_STATE_IDLE:
        
        break;

    case KEY_STATE_PRE_DEBOUNCE:
        
        break;

    case KEY_STATE_PRESS:
        
        break;

    case KEY_STATE_REL_DEBOUNCE:
        
        break;
    
    default:
        break;
    }
}

/**
 * @brief 通知触发的按键事件
 * @note 设置标志结构体变量，在主循环中检查该结构体以调用对应的按键事件处理函数
 *       - 通知非组合键事件时，按要求传入前三个参数，第四个参数传入 0 即可
 *       - 通知组合键事件时，按要求传入后三个参数，第一个参数传入 0 即可
 * @param key_id 按键 ID
 * @param key_event 触发的按键事件
 * @param key_state 按键当前所处的状态
 * @param pressed_key_mask 被按下按键的掩码（用于组合键检测与处理）
 * @return None
 */
static void notify_event(uint8_t key_id, key_event_t key_event, key_state_t key_state, uint16_t pressed_key_mask)
{
    
}