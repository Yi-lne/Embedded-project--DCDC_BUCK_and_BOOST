#include "switches.h"
#include "oled_show.h"

uint8_t buck_adj_switch_last_state = SWITCH_CLOSE;
uint8_t boost_adj_switch_last_state = SWITCH_CLOSE;

extern uint8_t buck_adj_hide_flag;
extern uint8_t boost_adj_hide_flag;

//在初次上电时同步上一次和当前的开关状态，以正确驱动或关闭芯片
void switches_state_init(void)
{
    if(buck_adj_get_now_switch_state() == SWITCH_CLOSE){
        buck_adj_switch_last_state = SWITCH_CLOSE;
        buck_adj_hide_flag = HIDE_NOT;
        buck_adj_driver_off();
    }else{
        buck_adj_switch_last_state = SWITCH_OPEN;
        buck_adj_hide_flag = HIDE_OK;
        buck_adj_driver_on();
    }

    if(boost_adj_get_now_switch_state() == SWITCH_CLOSE){
        boost_adj_switch_last_state = SWITCH_CLOSE;
        boost_adj_hide_flag = HIDE_NOT;
        boost_adj_driver_off();
    }else{
        boost_adj_switch_last_state = SWITCH_OPEN;
        boost_adj_hide_flag = HIDE_OK;
        boost_adj_driver_on();
    }
}

/* -----------------------------------------BUCK_ADJ_SWITCH-----------------------------------------
 * 控制buck_adj芯片开关
 * */

//获取上一次buck_adj开关状态
uint8_t buck_adj_get_last_switch_state(void)
{
    return buck_adj_switch_last_state;
}

//获取当前buck_adj开关状态
uint8_t buck_adj_get_now_switch_state(void)
{
    return (uint8_t)HAL_GPIO_ReadPin(BUCK_ADJ_SWITCH_GPIO_Port, BUCK_ADJ_SWITCH_Pin);
}

// 设置当前buck_adj状态
void buck_adj_set_now_switch_state(uint8_t state)
{
    buck_adj_switch_last_state = state;
}

//驱动buck_adj芯片，低电平驱动buck_adj，高电平关闭buck_adj
void buck_adj_driver_on(void)
{
    HAL_GPIO_WritePin(BUCK_ADJ_DRIVER_GPIO_Port, BUCK_ADJ_DRIVER_Pin, GPIO_PIN_RESET);
}

//关闭buck_adj芯片
void buck_adj_driver_off(void)
{
    HAL_GPIO_WritePin(BUCK_ADJ_DRIVER_GPIO_Port, BUCK_ADJ_DRIVER_Pin, GPIO_PIN_SET);
}


/* -----------------------------------------BOOST_ADJ_SWITCH-----------------------------------------
 * 控制boost_adj芯片开关
 * */

//获取上一次boost_adj开关状态
uint8_t boost_adj_get_last_switch_state(void)
{
    return boost_adj_switch_last_state;
}

//获取当前boost_adj开关状态
uint8_t boost_adj_get_now_switch_state(void)
{
    return (uint8_t)HAL_GPIO_ReadPin(BOOST_ADJ_SWITCH_GPIO_Port, BOOST_ADJ_SWITCH_Pin);
}

// 设置当前boost_adj状态
void boost_adj_set_now_switch_state(uint8_t state)
{
    boost_adj_switch_last_state = state;
}

//驱动boost_adj芯片，高电平驱动boost_adj，低电平关闭boost_adj
void boost_adj_driver_on(void)
{
    HAL_GPIO_WritePin(BOOST_ADJ_DRIVER_GPIO_Port, BOOST_ADJ_DRIVER_Pin, GPIO_PIN_SET);
}

//关闭boost_adj芯片
void boost_adj_driver_off(void)
{
    HAL_GPIO_WritePin(BOOST_ADJ_DRIVER_GPIO_Port, BOOST_ADJ_DRIVER_Pin, GPIO_PIN_RESET);
}
