#ifndef __TIMER_H_
#define __TIMER_H_
#include "stm32f4xx.h"
#include <stdio.h>
#include "usart1.h"

int get_timer7_status(void);   
 
void timer7_init(u32 psc, u32 arr);



#endif