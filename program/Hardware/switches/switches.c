#include "switches.h"

//上一次开关状态，1：开关已打开，0：开关已关闭
uint8_t buck_adj_switch_last_state = 0;
uint8_t boost_adj_switch_last_state = 0;

extern uint8_t buck_adj_symbol_flag;

//在初次上电时同步上一次和当前的状态，以正确驱动或关闭芯片
void switches_state_init(void)
{
    if(buck_adj_get_now_switch_state() == 0){
        buck_adj_switch_last_state = 0;
        buck_adj_symbol_flag = 0;
    }else{
        buck_adj_switch_last_state = 1;
        buck_adj_symbol_flag = 1;
        buck_adj_driver_on();
    }

    if(boost_adj_get_now_switch_state() == 0){
        boost_adj_switch_last_state = 0;
    }else{
        boost_adj_switch_last_state = 1;
        boost_adj_driver_on();
    }
}

//---------------------------BUCK_ADJ_SWITCH-----------------------------------------

//获取上一次buck_adj开关状态
uint8_t buck_adj_get_last_switch_state(void)
{
    return buck_adj_switch_last_state;
}

//获取当前buck_adj开关状态
uint8_t buck_adj_get_now_switch_state(void)
{
    return (uint8_t)HAL_GPIO_ReadPin(buck_adj_switch_GPIO_Port, buck_adj_switch_Pin);
}

// 设置当前buck_adj状态
void buck_adj_set_now_switches_state(uint8_t state)
{
    buck_adj_switch_last_state = state;
}

//驱动buck_adj芯片，低电平驱动buck_adj，高电平关闭buck_adj
void buck_adj_driver_on(void)
{
    HAL_GPIO_WritePin(buck_adj_driver_GPIO_Port, buck_adj_driver_Pin, GPIO_PIN_RESET);
}

//关闭buck_adj芯片
void buck_adj_driver_off(void)
{
    HAL_GPIO_WritePin(buck_adj_driver_GPIO_Port, buck_adj_driver_Pin, GPIO_PIN_SET);
}


//---------------------------BOOST_ADJ_SWITCH-----------------------------------------

//获取上一次boost_adj开关状态
uint8_t boost_adj_get_last_switch_state(void)
{
    return boost_adj_switch_last_state;
}

//获取当前boost_adj开关状态
uint8_t boost_adj_get_now_switch_state(void)
{
    return (uint8_t)HAL_GPIO_ReadPin(boost_adj_switch_GPIO_Port, boost_adj_switch_Pin);
}

// 设置当前boost_adj状态
void boost_adj_set_now_switches_state(uint8_t state)
{
    boost_adj_switch_last_state = state;
}

//驱动boost_adj芯片，高电平驱动boost_adj，低电平关闭boost_adj
void boost_adj_driver_on(void)
{
    HAL_GPIO_WritePin(boost_adj_driver_GPIO_Port, boost_adj_driver_Pin, GPIO_PIN_SET);
}

//关闭boost_adj芯片
void boost_adj_driver_off(void)
{
    HAL_GPIO_WritePin(boost_adj_driver_GPIO_Port, boost_adj_driver_Pin, GPIO_PIN_RESET);
}
