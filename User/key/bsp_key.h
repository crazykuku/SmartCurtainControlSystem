#ifndef __BSP_KEY_H
#define __BSP_KEY_H
#include "stm32f10x.h"
//#define KEY1_GPIO_PIN       GPIO_Pin_12
//#define KEY1_GPIO_Port 			GPIOB 
//#define KEY1_GPIO_CLK			  RCC_APB2Periph_GPIOB   

//#define KEY2_GPIO_PIN       GPIO_Pin_13
//#define KEY2_GPIO_Port 			GPIOB
//#define KEY2_GPIO_CLK			  RCC_APB2Periph_GPIOB    

#define KEY3_GPIO_PIN       GPIO_Pin_14
#define KEY3_GPIO_Port 			GPIOB
#define KEY3_GPIO_CLK			  RCC_APB2Periph_GPIOB    

#define KEY4_GPIO_PIN       GPIO_Pin_15
#define KEY4_GPIO_Port 			GPIOB
#define KEY4_GPIO_CLK			  RCC_APB2Periph_GPIOB    

#define KEY_ON     1
#define KEY_OFF    0


uint8_t Key_GetNum(void);
void KEY_GPIO_Config(void);



#endif 

