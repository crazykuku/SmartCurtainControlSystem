//bsp：板级支持包
#include "bsp_led.h"  

void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitSTruct;
	RCC_APB2PeriphClockCmd(LED_G_GPIO_CLK|LED_R_GPIO_CLK, ENABLE);
	GPIO_InitSTruct.GPIO_Pin = LED_G_GPIO_PIN|LED_R_GPIO_PIN;
	GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSTruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_G_GPIO_Port,&GPIO_InitSTruct);
	GPIO_Init(LED_R_GPIO_Port,&GPIO_InitSTruct);
	GPIO_SetBits(LED_R_GPIO_Port, LED_R_GPIO_PIN );
	GPIO_SetBits(LED_G_GPIO_Port, LED_G_GPIO_PIN );


}

