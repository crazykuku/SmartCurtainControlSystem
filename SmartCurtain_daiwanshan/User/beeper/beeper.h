#ifndef __BEEPER_H
#define __BEEPER_H	 
#include "stm32f10x.h"

#define Beeper BIT_ADDR(GPIOC_ODR_Addr,15)	//PC15

void BEEPER_Init(void);//��ʼ��
void beeperOnce(void);//����������һ��
		 				    
#endif
