#include "beeper.h"
#include "delay.h"

//蜂鸣器IO初始化
void BEEPER_Init(void)
{
 
	GPIO_InitTypeDef GPIO_InitSTruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PB端口时钟
	
	//初始化 蜂鸣器引脚PB9	  推挽输出
	GPIO_InitSTruct.GPIO_Pin  = GPIO_Pin_0;	
	GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitSTruct.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitSTruct);//初始化GPIO
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);//输出低电平
	//GPIO_SetBits(GPIOA,GPIO_Pin_0);//输出低电平
}
//蜂鸣器短响一次
void beeperOnce(void)
{
		GPIO_SetBits(GPIOA, GPIO_Pin_0 );
		DelayMs(10);
		GPIO_ResetBits(GPIOA, GPIO_Pin_0 );
}

