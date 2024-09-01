#include "led.h"


void InitLed(void){
	
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_9|GPIO_Pin_8;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOE, &GPIO_InitStruct);
	GPIO_SetBits(GPIOE,GPIO_Pin_10|GPIO_Pin_9|GPIO_Pin_8);
	
}


void Led_Huama(void){
	led1_open;
	delay_50ms(5);
	led1_close;
	led2_open;
	delay_50ms(5);
	led2_close;
	led3_open;
	delay_50ms(5);
	led3_close;
	led2_open;
	delay_50ms(5);
	led2_close;
}

