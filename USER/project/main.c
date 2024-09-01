#include "stm32f4xx.h"  // Device header
#include "Systick.h"
#include "led.h"
#include "KEY.h"
#include "bee.h"
#include "dht11.h"
#include "stdio.h"
#include "usart1.h"
#include "fan.h "
#include "adc.h "
#include "string.h"
#include "myoled.h"
#include "string.h"

extern  unsigned char data_recieve[64];
extern   uint8_t recieve_flag;
uint8_t* hnm_tem_date;
uint16_t gm_value,pc_value;
 char  hnm_char[4],tem_char[3],gm_char[5],pc_char[5];
 char  hnm_alarm_char[4],tem_alarm_char[3],light_alarm_char[5];

uint8_t is_menu_1or2=0;
uint8_t is_selected=0;
uint8_t selsect_number=0;
uint8_t tem_alarm_value=35;
uint8_t hnm_alarm_value=75;
uint16_t light_alarm_value=3700;

uint8_t key2_date=0,key3_date=0,
menue2_key3_date=0,return_menue1=0,fan_o_c=0;

void fill_sg(char *str,int g);

int main(void)
{  
	//uint8_t* hnm_tem_date;
	Systick_Init(168);
	
	Software_IIC_Init();
	Oled_Init();
	keys_init();
	dht11_pin_init();
	adc_gm_pc_init();
	usart1_init();
	InitLed();
	Initbee();
	fan_pin_init();
	timer7_init(8400 - 1, 5000 - 1);
	while(1)
	{
		if(key1_down==RESET)
		{
			Systick_delay_ms(20);
			while(key1_down==RESET);
			Systick_delay_ms(20); 
			led1_open;
			OLed_Showboot();
			delay_50ms(20);
			oled_clear();
			OLed_Show_menue1();
		
			while(1)
			{
				/*-------------键1操作--------------*/
				if(key1_down==RESET){
				Systick_delay_ms(20);
				while(key1_down==RESET);
				Systick_delay_ms(20);
				is_menu_1or2=0;
				is_selected=0;
				oled_clear();
				led1_close;led2_close;led3_close;fan_close;bee_close;
				break;
			}
			/*--数据菜单输出数据---*/
			if(is_menu_1or2==0 &&  get_timer7_status() == 1)
			{
				hnm_tem_date=get_dht11_hnm_tem();
				gm_value= get_gm_adc_value();
				pc_value= get_pc_adc_value();
				/* --------------对比数据，相应操作--------------------*/
				if(gm_value>light_alarm_value)
				{
					led3_open;
				}
				else
				{
					led3_close;
				}
	
				if(hnm_tem_date[0]>=hnm_alarm_value)
				{
					led2_open; 
					Systick_delay_ms(50);
					led2_close;
					Systick_delay_ms(100);
				}

				if(hnm_tem_date[2]>=tem_alarm_value)//wd
				{ 	
					fan_open;
					bee_open;
					Systick_delay_ms(50);
					bee_close;
					Systick_delay_ms(100);
		
				}
				else
				{		
					fan_close;
				}

	
				printf("tem:%d\r\n",hnm_tem_date[2]);
				printf("hnm:%d\r\n",hnm_tem_date[0]);
				printf("gm:%d\r\n",gm_value);
				printf("pc:%d\r\n",pc_value);

				sprintf(hnm_char,"%d",hnm_tem_date[0]);
				sprintf(tem_char,"%d",hnm_tem_date[2]);
				sprintf(gm_char,"%d",gm_value);
				sprintf(pc_char,"%d",pc_value);
		
				fill_sg(hnm_char,4);
				fill_sg(tem_char,3);
				fill_sg(gm_char,5);
				fill_sg(pc_char,5);
				OLed_Show_date_value(tem_char,hnm_char,gm_char,pc_char);
	
			}

				if(is_menu_1or2==1)
				{
					/*--------串口接收操作- ------*/
					if(recieve_flag==1)
					{
						if(strcmp((const char*)data_recieve,"bee_open")==0)
						{
							bee_open;
						}
						if(strcmp((const char*)data_recieve,"bee_close")==0)
						{
							bee_close;
						}
						if(strcmp((const char*)data_recieve,"fan_open")==0)
						{
							//fan_open;
						}
						if(strcmp((const char*)data_recieve,"fan_close")==0)
						{
							//fan_close;
						}
						if(strcmp((const char*)data_recieve,"led2_open")==0)
						{			
							led2_open;
						}
						if(strcmp((const char*)data_recieve,"led2_close")==0)
						{
							led2_close;
						}
						if(strcmp((const char*)data_recieve,"led3_open")==0)
						{
							led3_open;
						}
						if(strcmp((const char*)data_recieve,"led3_close")==0)
						{
							led3_close;
						}

						recieve_flag=0;
					}

					/*按键2菜单2输入操作*/
					if(menue2_key3_date==1)
					{
						if(is_selected!=0)
						{
							switch(selsect_number)
							{
								case 1:
										OLed_ShowASCII(56, 0,"N");
										break;
								case 2:
										OLed_ShowASCII(56, 2,"N");
										break;
								case 3:
										OLed_ShowASCII(56,4,"N");
										break;
								case 4:
										OLed_ShowASCII(56,6,"N");
										break;
							}
						}
						else
						{
							switch(selsect_number)
							{
								case 1:
										is_menu_1or2=0;
										led2_close;
										led3_close;
										fan_close;
										bee_close;
										oled_clear();
										OLed_Show_menue1();
										break;
								case 2:
										OLed_ShowASCII(56, 2,"Y");
										break;
								case 3:
										OLed_ShowASCII(56,4,"Y");
										break;
								case 4:
										OLed_ShowASCII(56,6,"Y");
										break;
     
							}
			 
						}

						is_selected=~is_selected;
						menue2_key3_date=0;
						
					}
					/*按键2输入操作*/
					if(key2_date==1)
					{
						if(is_selected==0)
						{
	   
							switch(selsect_number)
							{
								case 1:
										break;
								case 2:
										OLed_ShowASCII(48, 2,"1");
										OLed_ShowASCII(48,0," ");
										break;
								case 3:
										OLed_ShowASCII(48,4,"1");
										OLed_ShowASCII(48,2," ");
										break;
								case 4:
										OLed_ShowASCII(48,6,"1");
										OLed_ShowASCII(48,4," ");
										break;
							}
						}
						
						key2_date=0;
		
					}
					/*按键3输入操作*/
					if(key3_date==1)
					{
						if(is_selected==0)
						{
							switch(selsect_number)
							{
								case 1:
										OLed_ShowASCII(48, 0,"1");
										OLed_ShowASCII(48,2," ");
										break;
								case 2:
										OLed_ShowASCII(48, 2,"1");
										OLed_ShowASCII(48,4," ");
										break;
								case 3:
										OLed_ShowASCII(48,4,"1");
										OLed_ShowASCII(48,6," ");
										break;
								case 4:
										break;
							}
						}
		
						key3_date=0;
			
					}
					/*--------报警值输出-----------*/
					sprintf(hnm_alarm_char,"%d",hnm_alarm_value);
					sprintf(tem_alarm_char,"%d",tem_alarm_value);
					sprintf(light_alarm_char,"%d",light_alarm_value);
					fill_sg(hnm_alarm_char,4);
					fill_sg(tem_alarm_char,3);
					fill_sg(light_alarm_char,5);
					OLed_Show_alarm_value(tem_alarm_char,hnm_alarm_char,light_alarm_char);
	
		
		
					/*----按键2-----*/
					if(key2_down==RESET)
					{
						Systick_delay_ms(20);
						while(key2_down==RESET);
						Systick_delay_ms(20);
						if((selsect_number<4)&&(is_selected==0))
						{
							selsect_number++;
						}
						if(is_selected!=0)
						{
							switch(selsect_number)
							{
								case 1:
										break;
								case 2:tem_alarm_value--;
										break;
								case 3:
										hnm_alarm_value--;
										break;
								case 4:
										light_alarm_value-=100;
										break;
			
							}
						}
						
						key2_date=1;
					}
					/*----按键3-----*/
					if(key3_down==RESET)
					{
						Systick_delay_ms(20);
						while(key3_down==RESET);
						Systick_delay_ms(20);
						if((selsect_number>1)&&(is_selected==0))
						{
							selsect_number--;
						}
						if(is_selected!=0)
						{
							switch(selsect_number)
							{
								case 1:
										break;
								case 2:
										tem_alarm_value++;
										break;
								case 3:
										hnm_alarm_value++;
										break;
								case 4:
										light_alarm_value+=100;
										break;
			
							}
						}
						
						key3_date=1;
					}
				}

	
				/*--------------键4操作-------------*/
				if(key4_down==RESET)
				{
					Systick_delay_ms(20);
					while(key4_down==RESET);
					Systick_delay_ms(20);

					if(is_menu_1or2==1)
					{
						menue2_key3_date=1;
					}
					if(is_menu_1or2==0)
					{
				
						is_menu_1or2=1;
						selsect_number=1;
						is_selected=0;	
						led2_close;
						led3_close;
						fan_close;
						bee_close;
						printf("\r\nYou can use the following commands to control the system\r\n");
						printf("1: \"led2_open\" AND \"led2_close\"\r\n");
						printf("2: \"led3_open\" AND \"led3_close\"\r\n");
						printf("3: \"bee_open\" AND \"bee_close\"\r\n");
						printf("4: \"fan_open\" AND \"fan_close\"\r\n");
						oled_clear();
						OLed_Show_menue2();
					}
				}
			}
		}
	}
}	





void fill_sg(char *str,int g)
{
	uint8_t i=strlen(str);
	str[g-1]='\0';
	for(;i<=g-2;i++)
	{
		str[i]=' ';
	}


}
