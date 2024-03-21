#ifndef __BEEPER_H
#define __BEEPER_H	 
#include "stm32f10x.h"

#define Beeper BIT_ADDR(GPIOC_ODR_Addr,15)	//PC15

void BEEPER_Init(void);//初始化
void beeperOnce(void);//蜂鸣器短响一次
		 				    
#endif
