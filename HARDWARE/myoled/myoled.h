#ifndef __MYOLED_H
#define __MYOLED_H

#include "stm32f4xx.h"
#include "softwareiic.h"

#define OLED_SLAVE_ADDR 0x78 //OLED 从机地址

#define OLED_SLAVE_CMD 0x00		//0000 0000  下一次发送的字节为指令
#define OLED_SLAVE_DATA 0x40 // 0100 0000		下一次发送的字节为数据

/********通过IIC向OLED发送一个字节命令*********/
uint8_t Oled_Send_One_Byte_Cmd(uint8_t cmd);

/********通过IIC向OLED发送一个字节数据*********/
uint8_t Oled_Send_One_Byte_DATA(uint8_t Dat);

/*****************初始化OLED*****************/
void Oled_Init(void);

//填充缓存区中的数据
void OLed_Fill(unsigned char bmp_data);

//取消OLED初始化
void off_Init_OLed(void);

//设置显示字符位置的函数
void OLed_SetPos(unsigned char x, unsigned char y);

//显示一个中文
void OLed_ShowChina(uint8_t x,uint8_t y,uint8_t *buf);

//在指定位置显示ASCLL字符
void OLed_ShowASCII(uint8_t x, uint8_t y,char *str);

//在指定的位置显示连续的文字 "中国"
//void OLed_ShowTest(unsigned char x,unsigned char y);

//显示温度和 湿度
//void OLed_ShowTemp(void);

//显示 距离
//void OLed_ShowDist(void);

//显示 关照
//void OLed_ShowLight(void);

//显示一张图片 HQYJ
//void Oled_Show_BGM_HQYJ(void);

void OLed_Showboot(void);
void OLed_Show_menue1(void);
void OLed_Show_menue2(void);
void OLed_Show_date_value(char *w,char* s,char *g,char* d);
void OLed_Show_alarm_value(char *w,char *s,char *g);
void oled_clear(void);
#endif
