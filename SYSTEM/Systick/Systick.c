#include "Systick.h"
uint32_t _us;
void Systick_Init(uint8_t SYSCLK){
SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
_us=SYSCLK/8;

}
void Systick_delay_us(uint32_t time){
SysTick->VAL=0;
SysTick->LOAD=time*_us;	
SysTick->CTRL|=0X01;
while(((SysTick->CTRL>>16)&(0x01))==0);
	
SysTick->CTRL &=~0x01;
}
void Systick_delay_ms(uint32_t time){
SysTick->VAL=0;
SysTick->LOAD=time*_us*1000;	
SysTick->CTRL|=0X01;
while(((SysTick->CTRL>>16)&(0x01))==0);
	
SysTick->CTRL &=~0x01;
}
void delay_50ms(uint16_t max){

uint16_t i;
	for(i=0;i<max;i++)
	Systick_delay_ms(50);
}
