#include "bsp_systick.h"

void SysTicks_Delay_us(uint32_t us)
{
	uint32_t i;
	SysTick_Config(72);
	for(i=0;i<us;i++)
	{
		//һ��ѭ��1us
		while(!((SysTick->CTRL)&(1<<16)));
	}
	//ȡ��ʹ��λ �رն�ʱ��
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
	//ȡ��ʹ��λ �رն�ʱ��
	SysTick->CTRL &= SysTick_CTRL_ENABLE_Msk;
}	