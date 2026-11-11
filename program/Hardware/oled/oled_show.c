#include "oled_show.h"
#include "switches.h"

//adc_data[0]: buck_adj, adc_data[1]: boost_adj, adc_data[2]: voltmeter
extern volatile uint16_t adc_data[3];

/* ADC 参考电压与满量程。VDDA 由 AMS1117-3.3 提供；
 * 如果实测 3.3V 轨不是 3.300V，把 ADC_VREF 改成实测值即可。 */
#define ADC_VREF            3.3f
#define ADC_FULL_SCALE      4095.0f

/* 板上分压电阻（见原理图） */
#define BUCK_R_TOP          10.0f
#define BUCK_R_BOTTOM       6.8f
#define BOOST_R_TOP         10.0f
#define BOOST_R_BOTTOM      1.3f
#define VOLT_R_TOP          10.0f
#define VOLT_R_BOTTOM       1.0f

/* 一阶低通滤波系数：0~1，越大跟随越快、越不稳。
 * 100ms 刷新时 0.2 约等于 0.5s 时间常数；觉得反应慢可改 0.3。 */
#define ADC_FILTER_ALPHA    0.2f

//存储滤波后的电压值
float buck_adj_ori_data = 0.0f, boost_adj_ori_data = 0.0f, voltmeter_ori_data = 0.0f;

//inter: 整数部分，decimal: 小数部分
uint8_t buck_adj_inter = 0, buck_adj_decimal = 0;
uint8_t boost_adj_inter = 0, boost_adj_decimal = 0;
uint8_t voltmeter_inter = 0, voltmeter_decimal = 0;

uint8_t buck_adj_hide_flag = HIDE_NOT;
uint8_t boost_adj_hide_flag = HIDE_NOT;

static uint8_t voltage_filter_inited = 0;

/* ADC 码值 -> 实际电压：code/4095 * VDDA * (Rtop+Rbottom)/Rbottom */
static float adc_to_voltage(uint16_t code, float r_top, float r_bottom)
{
    return (float)code / ADC_FULL_SCALE * ADC_VREF * (r_top + r_bottom) / r_bottom;
}

/* 一阶低通滤波 */
static float low_pass(float filtered, float raw)
{
    return filtered + (raw - filtered) * ADC_FILTER_ALPHA;
}

/* 四舍五入拆成整数/小数，避免直接截断造成末位跳变 */
static void split_voltage(float voltage, uint8_t *inter, uint8_t *decimal)
{
    uint32_t scaled = (uint32_t)(voltage * 100.0f + 0.5f);
    *inter = (uint8_t)(scaled / 100U);
    *decimal = (uint8_t)(scaled % 100U);
}

/*
 * 电压换算
 * */
void voltage_conversion(void)
{
    float buck_raw  = adc_to_voltage(adc_data[0], BUCK_R_TOP, BUCK_R_BOTTOM);
    float boost_raw = adc_to_voltage(adc_data[1], BOOST_R_TOP, BOOST_R_BOTTOM);
    float volt_raw  = adc_to_voltage(adc_data[2], VOLT_R_TOP, VOLT_R_BOTTOM);

    if (voltage_filter_inited == 0U) {
        buck_adj_ori_data = buck_raw;
        boost_adj_ori_data = boost_raw;
        voltmeter_ori_data = volt_raw;
        voltage_filter_inited = 1U;
    } else {
        buck_adj_ori_data = low_pass(buck_adj_ori_data, buck_raw);
        boost_adj_ori_data = low_pass(boost_adj_ori_data, boost_raw);
        voltmeter_ori_data = low_pass(voltmeter_ori_data, volt_raw);
    }

    split_voltage(buck_adj_ori_data, &buck_adj_inter, &buck_adj_decimal);
    split_voltage(boost_adj_ori_data, &boost_adj_inter, &boost_adj_decimal);
    split_voltage(voltmeter_ori_data, &voltmeter_inter, &voltmeter_decimal);
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
