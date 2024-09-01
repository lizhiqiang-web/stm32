#include "fan.h "

void fan_pin_init(/*uint16_t rlr,uint16_t per*/void){
	
	/*TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;*/
	GPIO_InitTypeDef GPIO_InitStruct;

	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
  GPIO_InitStruct.GPIO_Mode=  GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_15;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,  &GPIO_InitStruct);
	/*GPIO_PinAFConfig( GPIOB,  GPIO_PinSource15, GPIO_AF_TIM12);
 

    TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up  ;
	TIM_TimeBaseInitStruct.TIM_Period=per;
	TIM_TimeBaseInitStruct.TIM_Prescaler=rlr;
	TIM_TimeBaseInit( TIM12,  &TIM_TimeBaseInitStruct);
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High  ;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable ;
	TIM_OCInitStruct.TIM_Pulse=per/2;
	TIM_OC2Init(TIM12,&TIM_OCInitStruct);
	
	TIM_OC2PreloadConfig(TIM12,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM12,ENABLE);
	TIM_Cmd(TIM12,ENABLE);
	TIM_SetCompare2(TIM12,0);
	*/
	
}
