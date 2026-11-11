#include "oled_show.h"
#include "switches.h"

//adc_data[0]: buck_adj, adc_data[1]: boost_adj, adc_data[2]: voltmeter
extern volatile uint16_t adc_data[3];

//存储未被换算的电压原始值
float buck_adj_ori_data = 0.0f, boost_adj_ori_data = 0.0f, voltmeter_ori_data = 0.0f;

//inter: 整数部分，decimal: 小数部分
uint8_t buck_adj_inter = 0, buck_adj_decimal = 0;
uint8_t boost_adj_inter = 0, boost_adj_decimal = 0;
uint8_t voltmeter_inter = 0, voltmeter_decimal = 0;

uint8_t buck_adj_hide_flag = HIDE_NOT;
uint8_t boost_adj_hide_flag = HIDE_NOT;

/*
 * 电压换算
 * */
void voltage_conversion(void)
{
    buck_adj_ori_data = (float) adc_data[0] / 4095.0f * 7.38f;
    boost_adj_ori_data = (float) adc_data[1] / 4095.0f * 25.2f;
    voltmeter_ori_data = (float) adc_data[2] / 4095.0f * 33.0f;

    buck_adj_inter = (uint16_t) buck_adj_ori_data;
    buck_adj_decimal = (uint16_t) (buck_adj_ori_data * 100.0f) % 100;

    boost_adj_inter = (uint16_t) boost_adj_ori_data;
    boost_adj_decimal = (uint16_t) (boost_adj_ori_data * 100.0f) % 100;

    voltmeter_inter = (uint16_t) voltmeter_ori_data;
    voltmeter_decimal = (uint16_t) (voltmeter_ori_data * 100.0f) % 100;
}

/*
 * 展示测到的可调降压、可调升压和电压表的电压值
 * */
void voltage_display(void)
{
    //展示buck_adj的电压值
    if(buck_adj_get_last_switch_state() == SWITCH_OPEN) {
        //当前buck_adj芯片处于开启状态，若已隐藏电压值则显示电压值
        if(buck_adj_hide_flag == HIDE_OK) {
            buck_adj_hide_flag = HIDE_NOT;
            OLED_ShowString(2, 13, ".");
            OLED_ShowString(2, 16, "v");
        }
        OLED_ShowNum(2, 11, (uint32_t) buck_adj_inter, 2);
        OLED_ShowNum(2, 14, (uint32_t) buck_adj_decimal, 2);
    }else{
        //当前buck_adj芯片处于关闭状态，若未隐藏电压值则隐藏电压值
        if(buck_adj_hide_flag == HIDE_NOT) {
            buck_adj_hide_flag = HIDE_OK;
            OLED_ShowString(2, 11, "------");
        }
    }

    //展示boost_adj的电压值
    if(boost_adj_get_last_switch_state() == SWITCH_OPEN) {
        //当前boost_adj芯片处于开启状态，若已隐藏电压值则显示电压值
        if(boost_adj_hide_flag == HIDE_OK) {
            boost_adj_hide_flag = HIDE_NOT;
            OLED_ShowString(3, 13, ".");
            OLED_ShowString(3, 16, "v");
        }
        OLED_ShowNum(3, 11, (uint32_t) boost_adj_inter, 2);
        OLED_ShowNum(3, 14, (uint32_t) boost_adj_decimal, 2);
    }else{
        //当前boost_adj芯片处于关闭状态，若未隐藏电压值则隐藏电压值
        if(boost_adj_hide_flag == HIDE_NOT){
            boost_adj_hide_flag = HIDE_OK;
            OLED_ShowString(3, 11, "------");
        }
    }

    //展示voltmeter电压值
    OLED_ShowNum(4, 11, (uint32_t) voltmeter_inter, 2);
    OLED_ShowNum(4, 14, (uint32_t) voltmeter_decimal, 2);
    OLED_ShowString(4, 13, ".");
    OLED_ShowString(4, 16, "v");
}
