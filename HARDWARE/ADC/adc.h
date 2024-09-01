#ifndef __ADC_H_
#define __ADC_H_
#include "stm32f4xx.h"

void adc_gm_pc_init(void);
uint16_t get_pc_adc_value(void);
uint16_t get_gm_adc_value(void);

#endif
