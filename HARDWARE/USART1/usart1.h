#ifndef __USART1_H_
#define __USART1_H_
#include "stm32f4xx.h"
#include "Systick.h"
#include "stdio.h"
#include <string.h>
 


void usart1_init(void);
void uarst_send_byte(uint8_t data);
void uarst_send_str(uint8_t* str);
int get_uarst1_str(char *save_str, unsigned int strsize);
#endif
