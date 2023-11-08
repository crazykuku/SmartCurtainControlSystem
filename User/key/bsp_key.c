#include "bsp_key.h"
#include "delay.h"

void KEY_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitSTruct;
	RCC_APB2PeriphClockCmd(KEY3_GPIO_CLK|KEY4_GPIO_CLK, ENABLE);
	GPIO_InitSTruct.GPIO_Pin = KEY3_GPIO_CLK|KEY4_GPIO_CLK;
	GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_Init(KEY1_GPIO_Port,&GPIO_InitSTruct); 
//	GPIO_Init(KEY2_GPIO_Port,&GPIO_InitSTruct);
	GPIO_Init(KEY3_GPIO_Port,&GPIO_InitSTruct);
	GPIO_Init(KEY4_GPIO_Port,&GPIO_InitSTruct);
}

uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	if(GPIO_ReadInputDataBit(KEY3_GPIO_Port,KEY3_GPIO_PIN)== KEY_OFF)
	{
		DelayMs(20);
		//À… ÷ºÏ≤‚
		while(GPIO_ReadInputDataBit(KEY3_GPIO_Port,KEY3_GPIO_PIN)== KEY_OFF);
		DelayMs(20);
		KeyNum = 3;	
	}
	
	if(GPIO_ReadInputDataBit(KEY4_GPIO_Port,KEY4_GPIO_PIN)== KEY_OFF)
	{
		DelayMs(20);
		//À… ÷ºÏ≤‚
		while(GPIO_ReadInputDataBit(KEY4_GPIO_Port,KEY4_GPIO_PIN)== KEY_OFF);
		DelayMs(20);
		KeyNum = 4;	
	}
	

		return KeyNum;
}


