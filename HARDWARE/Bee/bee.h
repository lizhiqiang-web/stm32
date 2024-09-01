#ifndef __BEE_H_
#define __BEE_H_
#include "stm32f4xx.h" 


void Initbee(void);
#define   bee_open		GPIO_SetBits(GPIOB,GPIO_Pin_10)
#define   bee_close		GPIO_ResetBits(GPIOB,GPIO_Pin_10)
#define	 bee_toggle		GPIO_ToggleBits(GPIOB,GPIO_Pin_10)
#endif
