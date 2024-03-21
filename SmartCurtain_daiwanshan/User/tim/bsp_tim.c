#include "bsp_tim.h"

//中断优先级配置
static void BASIC_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ;	
		// 设置主优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // 设置抢占优先级为3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


static void BASIC_TIM_Config(void)
{
	//初始化结构体
   TIM_TimeBaseInitTypeDef TIM_InitStructure;
	
	//开TIM6时钟
	 RCC_APB1PeriphClockCmd(BASIC_TIM_CLK, ENABLE);
	
	//设置分频因子  为72-1 = 71   计数器计一个数为1us
	 TIM_InitStructure.TIM_Prescaler =  BASIC_TIM_Prescaler;
	//设置自动重装载寄存器的值    累积BASIC_TIM_Period+1次计数
	 TIM_InitStructure.TIM_Period = BASIC_TIM_Period;
	
	//初始化定时器
	 TIM_TimeBaseInit(BASIC_TIM, &TIM_InitStructure);
	
	//清楚标志位
	 TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);
	
	// 开启计数器中断
   TIM_ITConfig(BASIC_TIM,TIM_IT_Update,ENABLE);
	
	//使能计数器
	 TIM_Cmd(BASIC_TIM, ENABLE);
}

void BASIC_TIM_Init(void)
{
	BASIC_TIM_NVIC_Config();
	BASIC_TIM_Config();
}

