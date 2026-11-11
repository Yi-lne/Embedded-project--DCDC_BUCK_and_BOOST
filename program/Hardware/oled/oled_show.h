#ifndef DCDC_PROGRAM_OLED_SHOW_H
#define DCDC_PROGRAM_OLED_SHOW_H

#include "switches.h"
#include "oled.h"

//隐藏电压值，HIDE_OK：未隐藏，HIDE_NOT：已隐藏
#define HIDE_OK      1U
#define HIDE_NOT     0U

void voltage_conversion(void);
void voltage_display(void);

#endif //DCDC_PROGRAM_OLED_SHOW_H
