#ifndef __HDT11_H_
#define __HDT11_H_
#include "stm32f4xx.h"
#include "Systick.h"
#include "stdio.h"

#define   read_dht11_date  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)
#define   out_dht11_low  GPIO_ResetBits(GPIOA,GPIO_Pin_3)
#define   out_dht11_high  GPIO_SetBits(GPIOA,GPIO_Pin_3)

void dht11_pin_init(void);
void send_start_to_dht11(void);
uint8_t get_dht11_signal(void);
uint8_t read_dht11_bit(void);
uint8_t read_dht11_byte(void);
uint8_t* get_dht11_hnm_tem(void);

#endif
