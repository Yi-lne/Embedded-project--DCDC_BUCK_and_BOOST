#ifndef DCDC_PROGRAM_SWITCHES_H
#define DCDC_PROGRAM_SWITCHES_H

#include "main.h"

//上一次开关状态，1：开关已打开，0：开关已关闭
#define SWITCH_OPEN     1U
#define SWITCH_CLOSE    0U

void switches_state_init(void);

uint8_t buck_adj_get_now_switch_state(void);
uint8_t buck_adj_get_last_switch_state(void);
void buck_adj_set_now_switch_state(uint8_t state);
void buck_adj_driver_on(void);
void buck_adj_driver_off(void);

uint8_t boost_adj_get_now_switch_state(void);
uint8_t boost_adj_get_last_switch_state(void);
void boost_adj_set_now_switch_state(uint8_t state);
void boost_adj_driver_on(void);
void boost_adj_driver_off(void);

#endif //DCDC_PROGRAM_SWITCHES_H
