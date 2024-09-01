#include "dht11.h"


void dht11_pin_init(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=  GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_3);

}
void send_start_to_dht11(void){
	out_dht11_low;
	Systick_delay_ms(20);
	out_dht11_high;
  Systick_delay_us(30);
}

uint8_t get_dht11_signal(void){
    uint8_t wait_time=0;
	while(read_dht11_date==1){
		Systick_delay_us(2);
	   wait_time++;
	  if(wait_time==5){
			return 0;
		}
	}
    wait_time=0;
	while(read_dht11_date==0){
		Systick_delay_us(2);
	   wait_time++;
	  if(wait_time==50){
			return 0;
		}
	}
	wait_time=0;
	while(read_dht11_date==1){
		Systick_delay_us(2);
	   wait_time++;
	  if(wait_time==50)
		{
		return 0;
		}
}
      return 1;
}


uint8_t read_dht11_bit(void){
      uint8_t date=0;
	while(read_dht11_date==0);
	    Systick_delay_us(40);
	if(read_dht11_date==1)
	{
		date=1;
	}
	else
		{
		date=0;
		}
   while(read_dht11_date==1);
	return date;

}


uint8_t read_dht11_byte(void){
	uint8_t temp=0 ,i;
	for(i=0;i<8;i++){
	   temp<<=1;
		 temp|=read_dht11_bit();
	}
   return temp;
}
	

uint8_t* get_dht11_hnm_tem(void){ 	
	static uint8_t dht11_date[5];
	uint8_t i=0;
	send_start_to_dht11();
	if(get_dht11_signal()==0)
	{
		return NULL;
	}
	for(i=0;i<5;i++)
	{
		dht11_date[i]=read_dht11_byte();
	}
	if(dht11_date[0]+dht11_date[1]+dht11_date[2]+dht11_date[3]==dht11_date[4])
		return dht11_date;
	else {
		return NULL;
	}
	
}



