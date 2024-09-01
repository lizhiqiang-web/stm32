#ifndef __SYSTICK_H
#define __SYSTICK_H
#include "stm32f4xx.h"  
#include "led.h"

void Systick_Init(uint8_t SYSCLK);
void Systick_delay_us(uint32_t time);
void Systick_delay_ms(uint32_t time);
void delay_50ms(uint16_t max);
#endif
