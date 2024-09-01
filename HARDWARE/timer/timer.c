#include "timer.h"
static int timer_exit_flag = 0;

void timer7_init(u32 psc, u32 arr)
{	
	NVIC_InitTypeDef NVIC_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period =	arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	//TIM_TimeBaseInitStruct.TIM_RepetitionCounter
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	
	
	NVIC_Init(&NVIC_InitStruct);

	TIM_Cmd(TIM7, ENABLE);
}




void TIM7_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM7, TIM_IT_Update) == SET)
	{TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
		timer_exit_flag = 1;
		
	}

}

int get_timer7_status(void)
{
	if(timer_exit_flag == 1)
	{
		timer_exit_flag = 0;
		return 1;
	}
	else
		return -1;
} 
