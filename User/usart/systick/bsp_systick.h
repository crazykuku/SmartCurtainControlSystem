#ifndef __BSP_SYSTICK_H
#define __BSP_SYSTICK_H
#include   "stm32f10x.h"
#include   "core_cm3.h"

void SysTicks_Delay_us(uint32_t us);
void SysTicks_Delay_ms(uint32_t ms);

#endif

