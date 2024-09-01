#ifndef __LED_H_
#define __LED_H_
#include "stm32f4xx.h"
#include "Systick.h"

#define  led3_close GPIO_SetBits(GPIOE,GPIO_Pin_10)
#define  led3_open GPIO_ResetBits(GPIOE,GPIO_Pin_10)
#define  led3_toggle	GPIO_ToggleBits(GPIOE,GPIO_Pin_10)

#define  led2_close GPIO_SetBits(GPIOE,GPIO_Pin_9)
#define  led2_open GPIO_ResetBits(GPIOE,GPIO_Pin_9)
#define  led2_toggle	GPIO_ToggleBits(GPIOE,GPIO_Pin_9)

#define  led1_close GPIO_SetBits(GPIOE,GPIO_Pin_8)
#define  led1_open GPIO_ResetBits(GPIOE,GPIO_Pin_8)
#define  led1_toggle	GPIO_ToggleBits(GPIOE,GPIO_Pin_8)

void InitLed(void);
void Led_Huama(void);
#endif
