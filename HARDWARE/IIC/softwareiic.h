#ifndef __SOFTWAREIIC_H
#define __SOFTWAREIIC_H

#include "stm32f4xx.h"
#include "Systick.h"



//定义一些宏  方便使用
#define IIC_SCL_H GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define IIC_SCL_L GPIO_ResetBits(GPIOB,GPIO_Pin_6)

#define IIC_SDA_H GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define IIC_SDA_L GPIO_ResetBits(GPIOB,GPIO_Pin_7)

#define IIC_Delay_Time 2

//主机发送应答或非应答的宏
#define ACK 0  //表示发送应答
#define NO_ACK 1	//表示发送非应答

//引脚初始化函数
void Software_IIC_Init(void);

//主机发送起始信号
void Software_IIC_Start(void);

//主机发送停止信号
void Software_IIC_Stop(void);

//主机发送一个数据
void Software_IIC_Send_One_Byte_Data(uint8_t dat);

//主机读取从机发送的应答
uint8_t Software_IIC_Read_ACK(void);

//主机接收从机发送的数据
uint8_t Software_IIC_Receive_One_Byte_Data(void);

//主机发送应答或非应答
void Software_IIC_Send_ACK(uint8_t Ack);


#endif

