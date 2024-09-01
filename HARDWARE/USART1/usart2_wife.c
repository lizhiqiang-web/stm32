#include "usart2_wife.h"
#define  USART2_MAX_DATA_SIZE   64

static uint8_t wife_recv[64];
static uint8_t wife_recv_flag=0;



void usart2_init()
{	
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6; 
	GPIO_InitStruct.GPIO_PuPd =	GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(GPIOD,  &GPIO_InitStruct);
	

	
	
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2, &USART_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	
	
	
	
	
	GPIO_PinAFConfig( GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
    GPIO_PinAFConfig( GPIOD, GPIO_PinSource6, GPIO_AF_USART2);
	//USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	//NVIC_Init(&NVIC_InitStruct);
	  
	USART_Cmd(USART2,ENABLE);
	
	

	
	
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


void  USART2_IRQHandler(void)
{
	static uint8_t count = 0;
	if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET)
	{USART_ClearITPendingBit(USART2, USART_FLAG_RXNE);
		
		if(wife_recv_flag == 0)
		{
			wife_recv[count++] = USART_ReceiveData(USART2);
			if(count >= USART2_MAX_DATA_SIZE)
			{	
				count = 0;
			}
			else if(wife_recv[count-1] == '\n' && wife_recv[count-2] == '\r')
			{
				wife_recv[count-1] = '\0';
				wife_recv[count-2] = '\0';
				count = 0;
				wife_recv_flag = 1;
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

int get_uarst2_str(char *save_str, unsigned int strsize)
{
	if(wife_recv_flag == 1)
	{	
		
		if(strsize >= USART2_MAX_DATA_SIZE)
		{
			strcpy(save_str, wife_recv);
		}
		else
		{
			strncpy(save_str, wife_recv, strsize-1);
			save_str[strsize-1] = '\0';
		}
		
		wife_recv_flag = 0;
		return 1;
	}
	else
	{
		return -1;
	}
}

void uarst2_send_byte(uint8_t data){
   while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==0);
	  USART_SendData(USART2,data);
}
void uarst2_send_str(uint8_t* str){
   while(*str!='\0')
	  uarst2_send_byte(*str++);
}

int recv_ack(char *ack)
{	
	unsigned char count = 0;
   while(wife_recv_flag != 1 && count <= 50)
   {
		Systick_delay_ms(2);
		count++;
   }
	wife_recv_flag = 0;
	if(strcmp(wife_recv,ack) == 0)
	{	
		return 1;
	}
	return -1;
}		

int espWife_send_cmd(char *cmd, char *ack)
{	
	
	char temp_str[64];
	sprintf(temp_str, "%s\r\n", cmd);
	uarst2_send_str(temp_str);
	if(recv_ack(ack) <= 0)
	{
		return -1;
	}
	return 1;


	
	//uarst2_send_str();
}
int set_wife()
{
	/*espWife_send_cmd("AT","OK");
	espWife_send_cmd("ATE0","OK");
	espWife_send_cmd("AT+CWMODE=2","OK");
	espWife_send_cmd("AT+CWSAP=\"6666\",\"12345678\",6,4","OK");
	espWife_send_cmd("AT+CIPMUX=1","OK");
	espWife_send_cmd("AT+CIPSERVER=1,8089","OK");
	Systick_delay_ms(500);*/
	
	
	
	uarst2_send_str("AT\r\n");
	Systick_delay_ms(50);
	uarst2_send_str("ATE0\r\n");
	Systick_delay_ms(50);
	uarst2_send_str("AT+CWMODE=2\r\n");
	Systick_delay_ms(50);
	uarst2_send_str( "AT+CWSAP=\"6666\",\"12345678\",6,4\r\n");
	Systick_delay_ms(50);
	uarst2_send_str("AT+CIPMUX=1\r\n");
	Systick_delay_ms(50);
	uarst2_send_str("AT+CIPSERVER=1,8089\r\n");
	Systick_delay_ms(500);
	return 1;
}
