#ifndef __BSP_LED_H
#define __BSP_LED_H
#include "stm32f10x.h"
#define LED_G_GPIO_PIN        GPIO_Pin_13
#define LED_G_GPIO_Port 			GPIOC 
#define LED_G_GPIO_CLK			  RCC_APB2Periph_GPIOC    

#define LED_R_GPIO_PIN        GPIO_Pin_14
#define LED_R_GPIO_Port 			GPIOC 
#define LED_R_GPIO_CLK			  RCC_APB2Periph_GPIOC       


#define LED_G_TOGGLE          {LED_G_GPIO_Port->ODR ^= GPIO_Pin_13;}
#define LED_R_TOGGLE          {LED_G_GPIO_Port->ODR ^= GPIO_Pin_14;}
void LED_GPIO_Config(void);
#endif  /*__BSP_LED_H*/

