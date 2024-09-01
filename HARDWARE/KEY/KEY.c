#include "KEY.h"
#define INXT 
#ifdef INXT 
int key1_exit_flag = 0;
int key2_exit_flag = 0;
int key3_exit_flag = 0;
int key4_exit_flag = 0;
#endif
void key1_init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		
		GPIO_Init(GPIOE, &GPIO_InitStruct);
		
}
void key2_init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		
		GPIO_Init(GPIOE, &GPIO_InitStruct);
		
}

void key3_init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		
		GPIO_Init(GPIOE, &GPIO_InitStruct);
		
}


void key4_init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		
		GPIO_Init(GPIOC, &GPIO_InitStruct);
		
}
void keys_init(void)
{
	key1_init();
	key2_init();
	key3_init();
	key4_init();

}
int scan_keys()
{
	static int is_down = 0;
	unsigned int key_value=0;
	if((key1_down == 0 || key2_down == 0 || key3_down == 0 || key4_down ==0))
	{	
		if(is_down == 0 )
		{
 
			is_down	= 1;
			Systick_delay_ms(20);
			if( key1_down == 0 || key2_down == 0 || key3_down == 0 || key4_down ==0)
			{	
				if(key1_down == 0)
				{
					key_value = 1;
				}
				else if(key2_down == 0)
				{
					key_value = 2;
				}
				else if(key3_down == 0)
				{
					key_value = 3;
				}
				else if(key4_down == 0)
				{
					key_value = 4;
				}
			}
		}
		
	}
	else
	{
		if(is_down == 1)
		{
			is_down = 0;
		}
	}
	return key_value;
}
//-------KEY1-------------

void Key1_Exit_Init(void)
{	
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	key1_init();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);
	
	EXTI_InitStruct.EXTI_Line = EXTI_Line4;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode =	EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_Init(&NVIC_InitStruct);
	

}
void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4)==SET)
	{
		EXTI_ClearITPendingBit(EXTI_Line4);


		led1_toggle;

	}
}
//-------KEY2-------------
void Key2_Exit_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	key2_init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource5);
	EXTI_InitStruct.EXTI_Line = EXTI_Line5;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode =	EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	EXTI_Init(&EXTI_InitStruct);
	NVIC_Init(&NVIC_InitStruct);

}


//-------KEY3-------------
void Key3_Exit_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	key3_init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource6);
	EXTI_InitStruct.EXTI_Line = EXTI_Line6;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode =	EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	EXTI_Init(&EXTI_InitStruct);
	NVIC_Init(&NVIC_InitStruct);

}

void EXTI9_5_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line5)==SET)
	{
		EXTI_ClearITPendingBit(EXTI_Line5);

		led2_toggle;
    
			
	}
	
	if(EXTI_GetITStatus(EXTI_Line6)==SET)
	{
		EXTI_ClearITPendingBit(EXTI_Line6);
	
		bee_toggle;
				
	}
		
		
}


//-------KEY1-------------
void Key4_Exit_Init(void)
{
		EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	key1_init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);
	EXTI_InitStruct.EXTI_Line = EXTI_Line13;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode =	EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	EXTI_Init(&EXTI_InitStruct);
	NVIC_Init(&NVIC_InitStruct);
	
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line13)==SET)
	{EXTI_ClearITPendingBit(EXTI_Line13);
		
		led3_toggle;
	}
}
void Keys_Exit_funtion(void)
{
	if(key4_exit_flag == 1)
	{	
	
	}

}





void keys_exit_init(void)
{
	Key1_Exit_Init();
	Key2_Exit_Init();
	Key3_Exit_Init();
	Key4_Exit_Init();
}
