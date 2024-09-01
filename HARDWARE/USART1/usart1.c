#include "usart1.h"
#define  MAX_DATA_SIZE   64

uint8_t data_recieve[64];
uint8_t recieve_flag=0;


void usart1_init()
{	
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1, ENABLE);


	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_9; 
	GPIO_InitStruct.GPIO_PuPd =	GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,  &GPIO_InitStruct);
	

	
	
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	
	
	
	
	
	GPIO_PinAFConfig( GPIOA,  GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig( GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	NVIC_Init(&NVIC_InitStruct);
	  
	USART_Cmd(USART1,ENABLE);
	
	

	
	
	/*
	GPIO_InitTypeDef GPIO_InitStruct;
	 NVIC_InitTypeDef NVIC_InitStruct;
	 USART_InitTypeDef USART_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	
	
	GPIO_InitStruct.GPIO_Mode=  GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,  &GPIO_InitStruct);
	
	GPIO_PinAFConfig( GPIOA,  GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig( GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	
	
	USART_InitStruct.USART_BaudRate=115200;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity=USART_Parity_No   ;
	USART_InitStruct.USART_StopBits=USART_StopBits_1  ;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b ;
	USART_Init( USART1, &USART_InitStruct);
	
	USART_ITConfig( USART1, USART_IT_RXNE,ENABLE );
	
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn ; 
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStruct);
	
	USART_Cmd(USART1,ENABLE);
	*/
}


void USART1_IRQHandler (void)
{
	static uint8_t count = 0;
	if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
	{USART_ClearITPendingBit(USART1, USART_FLAG_RXNE);
		
		if(recieve_flag == 0)
		{
			data_recieve[count++] = USART_ReceiveData(USART1);
			if(count >= MAX_DATA_SIZE)
			{	
				count = 0;
			}
			else if(data_recieve[count-1] == '\n' && data_recieve[count-2] == '\r')
			{
				data_recieve[count-1] = '\0';
				data_recieve[count-2] = '\0';
				count = 0;
				recieve_flag = 1;
			}
		}
		
	}
	
	
	
	
 /*static uint8_t count=0;
	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==SET){
		USART_ClearITPendingBit(USART1,USART_FLAG_RXNE);
		if(count>=64){//会卡死 因为接收器的值没有读取，卡死
		  recieve_flag=1;
			count=0;
	
		}
		if(recieve_flag==0)
		{
		data_recieve[count++]=USART_ReceiveData(USART1);
		}
		if(data_recieve[count-1]=='\n'&&data_recieve[count-2]=='\r')
		{
		  recieve_flag=1;
			data_recieve[count-1]='\0';
			data_recieve[count-2]='\0';
			count=0;
		}
	
	}
	
*/

}


int get_uarst1_str(char *save_str, unsigned int strsize)
{
	if(recieve_flag == 1)
	{	
		
		if(strsize >= MAX_DATA_SIZE)
		{
			strcpy(save_str, data_recieve);
		}
		else
		{
			strncpy(save_str, data_recieve, strsize-1);
			save_str[strsize-1] = '\0';
		}
		
		recieve_flag = 0;
		return 1;
	}
	else
	{
		return -1;
	}
}

void uarst_send_byte(uint8_t data){
   while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==0);
	  USART_SendData(USART1,data);
}
void uarst_send_str(uint8_t* str){
   while(*str!='\0')
	  uarst_send_byte(*str++);
}

		

#if 1
#pragma import(__use_no_semihosting)
struct __FILE
{
	int handle ;
};

FILE __stdout;

void _sys_exit(int x)
{
	x=x;
}

int fputc(int ch, FILE *f)
{
	while ( (USART1->SR&0x40)==0);
    USART1->DR = (u8) ch;
	return ch;
}
#endif
