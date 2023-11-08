#include "bsp_systick.h"

void SysTicks_Delay_us(uint32_t us)
{
	uint32_t i;
	SysTick_Config(72);
	for(i=0;i<us;i++)
	{
		//一个循环1us
		while(!((SysTick->CTRL)&(1<<16)));
	}
	//取反使能位 关闭定时器
	SysTick->CTRL &= SysTick_CTRL_ENABLE_Msk;
}	


void SysTicks_Delay_ms(uint32_t ms)
{
	uint32_t i;
	SysTick_Config(72000);
	for(i=0;i<ms;i++)
	{
		while(!((SysTick->CTRL)&(1<<16)));
	}
	//取反使能位 关闭定时器
	SysTick->CTRL &= SysTick_CTRL_ENABLE_Msk;
}	