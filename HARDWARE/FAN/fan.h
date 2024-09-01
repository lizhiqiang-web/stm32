#ifndef __FAN_H_
#define __FAN_H_
#include "stm32f4xx.h"
#include "Systick.h"

#define  fan_open GPIO_SetBits(GPIOB,GPIO_Pin_15)
#define  fan_close GPIO_ResetBits(GPIOB,GPIO_Pin_15)
void fan_pin_init(/*uint16_t rlr,uint16_t per*/void);

#endif
