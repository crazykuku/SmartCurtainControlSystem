#ifndef __BSP_EXTI_H
#define __BSP_EXTI_H

#include "stm32f10x.h"

#define KEY1_INT_GPIO_PIN        GPIO_Pin_12
#define KEY1_INT_GPIO_Port 		   GPIOB 
#define KEY1_INT_GPIO_CLK			   RCC_APB2Periph_GPIOB    
#define KEY1_INT_AFIO_CLK				 RCC_APB2Periph_AFIO

#define KEY2_INT_GPIO_PIN        GPIO_Pin_13
#define KEY2_INT_GPIO_Port 		   GPIOB 
#define KEY2_INT_GPIO_CLK			   RCC_APB2Periph_GPIOB    
#define KEY2_INT_AFIO_CLK				 RCC_APB2Periph_AFIO

#define KEY3_INT_GPIO_PIN        GPIO_Pin_14
#define KEY3_INT_GPIO_Port 		   GPIOB 
#define KEY3_INT_GPIO_CLK			   RCC_APB2Periph_GPIOB    
#define KEY3_INT_AFIO_CLK				 RCC_APB2Periph_AFIO

#define KEY4_INT_GPIO_PIN        GPIO_Pin_15
#define KEY4_INT_GPIO_Port 		   GPIOB 
#define KEY4_INT_GPIO_CLK			   RCC_APB2Periph_GPIOB    
#define KEY4_INT_AFIO_CLK				 RCC_APB2Periph_AFIO

void EXTI_Key_Config(void);

#endif
