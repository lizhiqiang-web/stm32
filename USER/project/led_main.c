#include "stm32f4xx.h"  // Device header
#include "Systick.h"
#include "led.h"
#include "bee.h"
#include "KEY.h"
#include "usart1.h"
#include "timer.h"
#include "pwn2.h"
#include "pwn1.h"
#include "dht11.h"
#include "string.h"
#include "adc.h"
#include "usart2_wife.h"
 uint8_t data_recieve[64];
int gm_value = 0;



void fill_sg(char *str,int g){
	uint8_t i=strlen(str);
	str[g-1]='\0';
	for(;i<=g-2;i++)
	{
		str[i]=' ';
	}


}
int main(void)
{
	
	unsigned char *p_dht11_data;
	char tem[10] = {0};
	char hnm[10] = {0};
	char gm[10] = {0};
	
	
	unsigned int pulse = 0;
	
	
	Systick_Init(168);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Software_IIC_Init();
	usart1_init();
	usart2_init();
	InitLed();
	Initbee();
	dht11_pin_init(); 
	adc_gm_pc_init();
	keys_init();
	Oled_Init();
	set_wife();
	OLed_Show_menue1();
	pwn2_init(8400, 10000);
	timer7_init(8400,5000);
	
	
	while(1)
	{	

		
		switch(scan_keys())
		{	
			case 1: led1_toggle;
					printf("hncs湖南城市学院\n\r");
				
					printf("led打开\n\r");
				break;
			case 2: led2_toggle;
					printf("hqyj华清远见\n\r");
				break;
			case 3: led3_toggle; 
					printf("hello good\n\r");
				break;		
			case 4: //bee_toggle;
				pulse = (pulse+2000)%12000;
				TIM_SetCompare3(TIM2, pulse);
				//TIM_SetCompare1(TIM1, pulse);
				printf("牛逼\n\r");
				printf("bee打开\n\r");
				break;		
		}
		if(get_uarst1_str(data_recieve,sizeof(data_recieve)) == 1)
		{	
			if(strcmp("open_bee",data_recieve)==0)
			{
				//bee_open;
			}
			if(strcmp("close_bee",data_recieve)==0)
			{
				//bee_close;
			}
			if(strcmp("open_led1",data_recieve)==0)
			{
				led1_open;
			}
			if(strcmp("close_led1",data_recieve)==0)
			{
				led1_close;
			}
			printf("%s\n", data_recieve);
			
		}
		if(get_timer7_status() == 1)
		{
			p_dht11_data = get_dht11_hnm_tem();
			gm_value = get_gm_adc_value();
			sprintf(tem, "%d.%d",p_dht11_data[0],p_dht11_data[1]);
			sprintf(hnm, "%d.%d",p_dht11_data[2],p_dht11_data[3]);
			sprintf(gm, "%d", gm_value);
			fill_sg(tem,7);
			fill_sg(hnm,7);
			fill_sg(gm,7);
			OLed_ShowASCII(56, 2, tem);
			OLed_ShowASCII(56, 0, hnm);
			OLed_ShowASCII(56, 4, gm);
	
		}
		/*if(get_uarst2_str(data_recieve,sizeof(data_recieve)) == 1)
		{	
			printf("111%s\r\n", data_recieve);
			
		}*/
	}
	return 0;
}

