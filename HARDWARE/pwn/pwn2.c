#include "pwn2.h"

void pwn2_init(u32 psc, u32 arr)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_PinAFConfig(GPIOB,  GPIO_PinSource10, GPIO_AF_TIM2);

	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period =	arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	//TIM_TimeBaseInitStruct.TIM_RepetitionCounter
	
	
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 0;
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	TIM_OC3Init(TIM2, &TIM_OCInitStruct);
	

	TIM_Cmd(TIM2, ENABLE);
}