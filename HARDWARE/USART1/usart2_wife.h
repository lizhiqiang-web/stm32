#ifndef __USART2_WIFH_H_
#define __USART2_WIFH_H_

#include "stm32f4xx.h"
#include "Systick.h"
#include "stdio.h"
#include <string.h>
#include "usart1.h"


void usart2_init(void);
void uarst2_send_byte(uint8_t data);
void uarst2_send_str(uint8_t* str);
int get_uarst2_str(char *save_str, unsigned int strsize);
int recv_ack(char *ack);
int espWife_send_cmd(char *cmd, char *ack);
int set_wife(void);

#endif 