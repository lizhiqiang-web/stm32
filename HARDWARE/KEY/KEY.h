#ifndef __KEY_H
#define __KEY_H
#include "stm32f4xx.h" 
#include "Systick.h"
#include "stdio.h"
#include "myoled.h"
#include "led.h"
#include "bee.h"
#define  key1_down  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define  key2_down  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)
#define  key3_down  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)
#define  key4_down  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)
void Key1_Exit_Init(void);
void Key2_Exit_Init(void);
void Key3_Exit_Init(void);
void Key4_Exit_Init(void);
void keys_exit_init(void);
void Keys_Exit_funtion(void);



void key1_init(void);
void key2_init(void);
void key3_init(void);
void key4_init(void);
void keys_init(void);
int scan_keys(void);


#endif
