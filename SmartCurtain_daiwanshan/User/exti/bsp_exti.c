#include "bsp_exti.h"

static void EXTI_NVIC_Config(void)   //只能被bsp_exti.c调用
{
	NVIC_InitTypeDef NVIC_InitSTuct; //定义结构体函数
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//分组
	
	//初始化NVIC
	NVIC_InitSTuct.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitSTuct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitSTuct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitSTuct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitSTuct);

}

void EXTI_Key_Config(void)
{
	//定义结构体要放在最上面
	GPIO_InitTypeDef GPIO_InitSTruct;
	EXTI_InitTypeDef EXTI_InitSTruct;
	
	//配置中断优先级
	EXTI_NVIC_Config();
	
	//初始化GPIO KEY1
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK,ENABLE);
	GPIO_InitSTruct.GPIO_Pin = KEY1_INT_GPIO_PIN;
	GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_IPU;
	//GPIO_InitSTruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY1_INT_GPIO_Port,&GPIO_InitSTruct);
	
	//初始化EXTI KEY1
	RCC_APB2PeriphClockCmd(KEY1_INT_AFIO_CLK,ENABLE);//开时钟
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource12);
	
	EXTI_InitSTruct.EXTI_Line = EXTI_Line12;
	EXTI_InitSTruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitSTruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitSTruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitSTruct);
	
	
	
	//初始化GPIO KEY2
	RCC_APB2PeriphClockCmd(KEY2_INT_GPIO_CLK,ENABLE);
	GPIO_InitSTruct.GPIO_Pin = KEY2_INT_GPIO_PIN;
	GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_IPU;
	//GPIO_InitSTruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY2_INT_GPIO_Port,&GPIO_InitSTruct);
	
	//初始化EXTI KEY2
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource13);
	RCC_APB2PeriphClockCmd(KEY2_INT_AFIO_CLK,ENABLE);//开时钟
	
	EXTI_InitSTruct.EXTI_Line = EXTI_Line13;
	EXTI_InitSTruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitSTruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitSTruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitSTruct);
	
		//初始化GPIO KEY3
	RCC_APB2PeriphClockCmd(KEY3_INT_GPIO_CLK,ENABLE);
	GPIO_InitSTruct.GPIO_Pin = KEY3_INT_GPIO_PIN;
	GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_IPU;
	//GPIO_InitSTruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY3_INT_GPIO_Port,&GPIO_InitSTruct);
	
	//初始化EXTI KEY3
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	RCC_APB2PeriphClockCmd(KEY3_INT_AFIO_CLK,ENABLE);//开时钟
	
	EXTI_InitSTruct.EXTI_Line = EXTI_Line14;
	EXTI_InitSTruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitSTruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitSTruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitSTruct);
	
	
		//初始化GPIO KEY4
	RCC_APB2PeriphClockCmd(KEY4_INT_GPIO_CLK,ENABLE);
	GPIO_InitSTruct.GPIO_Pin = KEY4_INT_GPIO_PIN;
	GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_IPU;
	//GPIO_InitSTruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY4_INT_GPIO_Port,&GPIO_InitSTruct);
	
	//初始化EXTI KEY4
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource15);
	RCC_APB2PeriphClockCmd(KEY4_INT_AFIO_CLK,ENABLE);//开时钟
	
	EXTI_InitSTruct.EXTI_Line = EXTI_Line15;
	EXTI_InitSTruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitSTruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitSTruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitSTruct);
}

