
#ifndef __BEEP_H
#define __BEEP_H	 
#include "sys.h"

#define BEEP PAout(0)	// PA0
	

void BEEP_Init(void);//初始化

void beeperOnce(void);//蜂鸣器短响一次

		 				    
#endif
