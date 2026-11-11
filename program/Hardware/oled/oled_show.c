#include "oled_show.h"

extern uint16_t adc_data[3]; //adc_data[0]: buck_adj, adc_data[1]: boost_adj, adc_data[2]: voltmeter
float buck_adj_transformed_data = 0.0f, boost_adj_transformed_data = 0.0f, voltmeter_transformed_data = 0.0f;
uint8_t buck_adj_inter = 0, buck_adj_decimal = 0;
uint8_t boost_adj_inter = 0, boost_adj_decimal = 0;
uint8_t voltmeter_inter = 0, voltmeter_decimal = 0;
uint8_t buck_adj_symbol_flag = 0;
uint8_t boost_adj_symbol_flag = 0;

void voltage_calculation(void)
{
    buck_adj_transformed_data = (float) adc_data[0] / 4095.0f * 7.38f;
    boost_adj_transformed_data = (float) adc_data[1] / 4095.0f * 25.2f;
    voltmeter_transformed_data = (float) adc_data[2] / 4095.0f * 33.0f;

    buck_adj_inter = (uint16_t) buck_adj_transformed_data;
    buck_adj_decimal = (uint16_t) (buck_adj_transformed_data * 100.0f) % 100;

    boost_adj_inter = (uint16_t) boost_adj_transformed_data;
    boost_adj_decimal = (uint16_t) (boost_adj_transformed_data * 100.0f) % 100;

    voltmeter_inter = (uint16_t) voltmeter_transformed_data;
    voltmeter_decimal = (uint16_t) (voltmeter_transformed_data * 100.0f) % 100;
}

void voltage_display(void)
{
    //展示buck_adj的电压值
    if(buck_adj_get_last_switch_state() == 1) {
        OLED_ShowNum(2, 11, (uint32_t) buck_adj_inter, 2);
        OLED_ShowNum(2, 14, (uint32_t) buck_adj_decimal, 2);
        if(buck_adj_symbol_flag == 1) {
            buck_adj_symbol_flag = 0;
            OLED_ShowString(2, 13, ".");
            OLED_ShowString(2, 16, "v");
        }
    }else{
        if(buck_adj_symbol_flag == 0) {
            buck_adj_symbol_flag = 1;
            OLED_ShowString(2, 11, "------");
        }
    }

    //展示boost_adj的电压值
    if(boost_adj_get_last_switch_state() == 1) {
        OLED_ShowNum(3, 11, (uint32_t) boost_adj_inter, 2);
        OLED_ShowNum(3, 14, (uint32_t) boost_adj_decimal, 2);
        if(boost_adj_symbol_flag == 1) {
            boost_adj_symbol_flag = 0;
            OLED_ShowString(3, 13, ".");
            OLED_ShowString(3, 16, "v");
        }
    }else{
        if(boost_adj_symbol_flag == 0){
            boost_adj_symbol_flag = 1;
            OLED_ShowString(3, 11, "------");
        }
    }

    //展示voltmeter电压值
    OLED_ShowNum(4, 11, (uint32_t) voltmeter_inter, 2);
    OLED_ShowNum(4, 14, (uint32_t) voltmeter_decimal, 2);
    OLED_ShowString(4, 13, ".");
    OLED_ShowString(4, 16, "v");
}
