#include "pwn1.h"

void pwn1_init(u32 psc, u32 arr)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;//|GPIO_Pin_8 | GPIO_Pin_10;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	//GPIO_PinAFConfig(GPIOE,  GPIO_PinSource10, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE,  GPIO_PinSource9, GPIO_AF_TIM1);
	//GPIO_PinAFConfig(GPIOE,  GPIO_PinSource8, GPIO_AF_TIM1);
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period =	arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	//TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	
	
	
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 0;
	
	GPIO_Init(GPIOE, &GPIO_InitStruct);

	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);
	TIM_OC1Init(TIM1, &TIM_OCInitStruct);
	TIM_SetCompare1(TIM1, 5000);
	TIM_Cmd(TIM1, ENABLE);
}
