/**
 * @file ind_key_hal.c
 * @brief Hardware Abstraction Layer of the Independent Key Detection Module
 * @note Target MCU: STC89C516RD+ (51-family)
 * 
 * - 独立按键状态机实现
 * 
 * 功能：
 *  - 支持 1~16 个独立按键的状态检测
 *  - 基于定时器 Tick 进行扫描（消抖、状态保持）
 *  - 检测事件：短按、1阶段长按、2阶段长按、3阶段长按、双击、组合键、释放
 * 
 * 设计说明：
 *  - 按键是否按下由 bsp/key_bsp.c 中的 key_pressed_detect(uint8_t key_id); 函数检测
 *  - HAL 在每个 tick 中读取所有按键信息并更新状态机
 * 
 * @version 1.2.0
 * @author fmSun686yu
 * @date 2025-12-16
 */

#include "ind_key_hal.h"
#include "../core/stc89.h"
#include "../config/ind_key_configuration.h"
#include "../bsp/ind_key_bsp.h"

/* ================ 按键数据结构体 ================ */
typedef struct
{
    key_state_t state;        //! 当前状态
    key_state_t last_state;   //! 上一个状态
    uint16_t tick;            //! 非按下状态持续 tick
    uint16_t pressed_tick;    //! 稳定按下状态（包括短按和所有长按）持续 tick
    uint16_t click_count;     //! 连续按下次数
} key_data_t;

/* ===================== 静态变量 ===================== */
static key_data_t key_data[KEY_NUM];    //! 按键数据数组

/* ================================= 内部函数声明 ================================= */
static void key_scan(void);            //！ 按键扫描函数，处理独立按键状态机，必须周期性调用：以 SCAN_INTERVAL_MS 为周期调用（通常放在定时器中断）
static void key_state_machine(uint8_t key_id);  //! 按键状态机
static void key_check_combination(void);        //! 检查并通知组合键
static uint16_t key_get_pressed_mask(uint8_t *pressed_key_count, uint16_t *pressed_key_mask);     //! 获取当前处于 PRESSED 状态的按键掩码
static void notify_event(uint8_t key_id, key_event_t key_event, key_state_t key_state, uint16_t pressed_key_mask);     //! 通知触发的按键事件

/* ================================ API 函数定义 ================================ */

/**
 * @brief hal 按键初始化函数
 * @param None
 * @return None
 */
void key_hal_init(void)
{
    uint8_t i;

    key_bsp_init();

    timer2_register_callback(key_scan);         //! 将本层的函数 key_scan(); 注册到Core层
    
    //! 初始化所有按键的按键数据结构体
    for(i=0;i<KEY_NUM;i++)
    {
        key_data[i].state = KEY_STATE_IDLE;
        key_data[i].last_state = KEY_STATE_IDLE;
        key_data[i].tick = 0;
        key_data[i].pressed_tick = 0;
        key_data[i].click_count = 0;
    }

    key_clear_event();          //! 清除按键事件标志变量
}

/**
 * @brief 全局按键事件标志变量清除函数
 * @param None
 * @return None
 */
void key_clear_event(void)
{
    key_event_flag.key_id = 0xff;
    key_event_flag.key_event = KEY_EVENT_NONE;
    key_event_flag.key_state = KEY_STATE_IDLE;
    key_event_flag.pressed_key_mask = 0;
}



/* ================================ 内部函数定义 ================================ */

/**
 * @brief 按键扫描函数，调用按键状态机函数和组合键检查函数
 * @note 必须周期性调用：以 SCAN_INTERVAL_MS 为周期调用（通常放在定时器中断中）
 * @param None
 * @return None
 */
static void key_scan(void)
{
    uint8_t i;

    //! 循环扫描所有按键并运行状态机，更新每个独立按键的状态
    for(i=0;i<KEY_NUM;i++)
    {
        key_state_machine(i);   //! 运行按键状态机
    }

    //! 检查并通知组合键
    key_check_combination();
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
    key_event_flag.key_id = key_id;                        //! 按键 ID
    key_event_flag.key_event = key_event;                  //! 按键事件
    key_event_flag.key_state = key_state;                  //! 按键当前所处的状态
    key_event_flag.pressed_key_mask = pressed_key_mask;    //! 被按下按键的掩码（用于组合键检测与处理）
}

/**
 * @brief 按键状态机
 * @note key_scan(); 中循环调用，每次调用更新一次对应按键的状态
 * @param key_id 按键ID
 * @return None
 */
static void key_state_machine(uint8_t key_id)
{
    key_data_t *key = &key_data[key_id];        //! 定义一个指针，指向对应的按键数据数组
    bool pressed = key_pressed_detect(key_id);  //! 获取对应按键是否被按下（未消抖的原始数据）

    switch (key->state)
    {
        case KEY_STATE_IDLE:
            if(pressed)
            {
                key->last_state = key->state;
                key->state = KEY_STATE_PRE_DEBOUNCE;
                key->tick = 0;
            }

            break;

        case KEY_STATE_PRE_DEBOUNCE:
            if(pressed)
            {
                key->tick ++;

                if(key->tick >= PRE_DEBOUNCE_TICK)
                {
                    key->tick = 0;
                    key->pressed_tick = 0;
                    key->click_count ++;
                    key->last_state = key->state;
                    key->state = KEY_STATE_PRESS;
                    notify_event(key_id, KEY_EVENT_SHORT_PRESS, KEY_STATE_PRESS, 0);     //! 通知短按事件触发，且按键处于按下状态未释放
                }
            }
            else
            {
                //! 回到消抖前的状态
                key->state = key->last_state;
            }

            break;

        case KEY_STATE_PRESS:
            if(pressed)
            {
                key->pressed_tick ++;

                //! 检查1阶段长按事件
                if((key->click_count == 1) && (key->pressed_tick == LPRESS1_TICK))
                {
                    key->last_state = key->state;
                    key->state = KEY_STATE_LPRESS1;
                    notify_event(key_id, KEY_EVENT_LPRESS1, KEY_STATE_LPRESS1, 0);     //! 通知1阶段长按事件触发，且按键处于按下状态未释放
                }
            }
            else
            {
                key->last_state = key->state;
                key->state = KEY_STATE_REL_DEBOUNCE;
                key->tick = 0;
            }

            break;

        case KEY_STATE_LPRESS1:
            if(pressed)
            {
                key->pressed_tick ++;

                //! 检查2阶段长按事件
                if(key->pressed_tick == LPRESS2_TICK)
                {
                    key->last_state = key->state;
                    key->state = KEY_STATE_LPRESS2;
                    notify_event(key_id, KEY_EVENT_LPRESS2, KEY_STATE_LPRESS2, 0);     //! 通知2阶段长按事件触发，且按键处于按下状态未释放
                }
            }
            else
            {
                key->last_state = key->state;
                key->state = KEY_STATE_REL_DEBOUNCE;
                key->tick = 0;
            }

            break;

        case KEY_STATE_LPRESS2:
            if(pressed)
            {
                key->pressed_tick ++;

                //! 检查3阶段长按事件
                if(key->pressed_tick == LPRESS3_TICK)
                {
                    key->last_state = key->state;
                    key->state = KEY_STATE_LPRESS3;
                    notify_event(key_id, KEY_EVENT_LPRESS3,KEY_STATE_LPRESS3, 0);
                }
            }
            else
            {
                key->last_state = key->state;
                key->state = KEY_STATE_REL_DEBOUNCE;
                key->tick = 0;
            }

            break;

        case KEY_STATE_LPRESS3:
            if(!pressed)
            {
                key->last_state = key->state;
                key->state = KEY_STATE_REL_DEBOUNCE;
                key->tick = 0;
            }

            break;

        case KEY_STATE_COMBINED_CLICK:
            if(!pressed)
            {
                key->last_state = key->state;
                key->state = KEY_STATE_REL_DEBOUNCE;
                key->tick = 0;
            }

            break;

        case KEY_STATE_REL_DEBOUNCE:
            if(!pressed)
            {
                key->tick ++;

                //! 如果消抖完成
                if(key->tick >= REL_DEBOUNCE_TICK)
                {
                    //! 如果上一状态是组合键状态，则直接回到 IDLE
                    if (key->last_state == KEY_STATE_COMBINED_CLICK)
                    {
                        key->tick = 0;
                        key->pressed_tick = 0;
                        key->click_count = 0;
                        key->last_state = key->state;
                        key->state = KEY_STATE_IDLE;
                    }
                    else
                    {
                        key->last_state = key->state;
                        key->state = KEY_STATE_WAIT_PRE_AG;
                        key->tick = 0;
                    }
                }
            }
            else
            {
                //! 恢复到消抖前的状态
                key->state = key->last_state;
                key->tick = 0;
            }

            break;

        case KEY_STATE_WAIT_PRE_AG:
            if(pressed)
            {
                key->last_state = key->state;
                key->state = KEY_STATE_PRE_DEBOUNCE;
                key->tick = 0;
            }
            else
            {
                key->tick ++;

                //! 如果等待超时
                if(key->tick > DOUBLE_CLICK_MAX_TICK)
                {
                    //! 如果连续按下次数为1
                    if(key->click_count = 1)
                    {
                        //! 判断长短按
                        if(key->pressed_tick < LPRESS1_TICK)    notify_event(key_id, KEY_EVENT_SHORT_PRESS, KEY_STATE_IDLE, 0);
                        else if(key->pressed_tick < LPRESS2_TICK)    notify_event(key_id, KEY_EVENT_LPRESS1, KEY_STATE_IDLE, 0);
                        else if(key->pressed_tick < LPRESS3_TICK)    notify_event(key_id, KEY_EVENT_LPRESS2, KEY_STATE_IDLE, 0);
                        else    notify_event(key_id, KEY_EVENT_LPRESS3, KEY_STATE_IDLE, 0);
                    }
                    //! 如果连续按下次数>=2
                    else if (key->click_count >= 2)
                    {
                        notify_event(key_id, KEY_EVENT_DOUBLE_CLICK, KEY_STATE_IDLE, 0);
                    }

                    key->tick = 0;
                    key->pressed_tick = 0;
                    key->click_count = 0;
                    key->last_state = key->state;
                    key->state = KEY_STATE_IDLE;
                }
            }

            break;
        
        default:
            break;
    }
}

/**
 * @brief 获取当前处于按下状态（包括所有长短按）的按键掩码
 * @param pressed_key_count 指向 “计数同时被按下的按键的数量” 变量的指针
 * @param pressed_key_mask 指向 “保存被按下的按键掩码” 变量的指针
 * @return None
 */
static uint16_t key_get_pressed_mask(uint8_t *pressed_key_count, uint16_t *pressed_key_mask)
{
    uint8_t i;

    //! 循环扫描所有按键的状态机（KEY0 → KEY15）
    for(i=0;i<KEY_NUM;i++)
    {
        //! 如果当前按键状态为 PRESSED
        if(key_data[i].state == KEY_STATE_PRESS || key_data[i].state == KEY_STATE_LPRESS1 || key_data[i].state == KEY_STATE_LPRESS2 || key_data[i].state == KEY_STATE_LPRESS3)
        {
            *pressed_key_count ++;
            *pressed_key_mask |= 0x8000;
        }

        *pressed_key_mask = *pressed_key_mask >> 1;
    }
}

/**
 * @brief 检查并通知组合键
 * @param None
 * @return None
 */
static void key_check_combination(void)
{
    uint8_t i;
    static bool f = 0;                      //! 组合键事件触发标志
    uint8_t pressed_key_count = 0;          //! 计数同时被按下的按键的数量
    static uint16_t pressed_key_mask = 0;   //! 保存被按下的按键掩码

    key_get_pressed_mask(&pressed_key_count, &pressed_key_mask);

    //! 如果有被同时按下的独立按键
    if (pressed_key_count >= 2)
    {
        f = 1;  //! 触发组合键事件

        notify_event(0, KEY_EVENT_COMBINED_CLICK, KEY_STATE_COMBINED_CLICK, pressed_key_mask);

        //! 将同时按下的按键状态设置为组合键状态
        for(i=0;i<KEY_NUM;i++)
        {
            if(pressed_key_mask & 0x01)
            {
                key_data[i].state = KEY_STATE_COMBINED_CLICK;
            }
            pressed_key_mask = pressed_key_mask >> 1;
        }
    }
    //! 如果已经触发了组合键事件，且当前处于按下状态的按键数量为0，则代表组合键已经完成了按下到释放的全过程
    else if ((f == 1) && (pressed_key_count == 0))
    {
        f = 0;
        pressed_key_mask = 0;

        //! 通知最终确定的组合键掩码
        notify_event(0, KEY_EVENT_COMBINED_CLICK, KEY_STATE_IDLE, pressed_key_mask);
    }
}