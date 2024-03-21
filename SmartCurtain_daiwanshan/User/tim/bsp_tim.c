#include "bsp_tim.h"

//�ж����ȼ�����
static void BASIC_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ;	
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


static void BASIC_TIM_Config(void)
{
	//��ʼ���ṹ��
   TIM_TimeBaseInitTypeDef TIM_InitStructure;
	
	//��TIM6ʱ��
	 RCC_APB1PeriphClockCmd(BASIC_TIM_CLK, ENABLE);
	
	//���÷�Ƶ����  Ϊ72-1 = 71   ��������һ����Ϊ1us
	 TIM_InitStructure.TIM_Prescaler =  BASIC_TIM_Prescaler;
	//�����Զ���װ�ؼĴ�����ֵ    �ۻ�BASIC_TIM_Period+1�μ���
	 TIM_InitStructure.TIM_Period = BASIC_TIM_Period;
	
	//��ʼ����ʱ��
	 TIM_TimeBaseInit(BASIC_TIM, &TIM_InitStructure);
	
	//�����־λ
	 TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);
	
	// �����������ж�
   TIM_ITConfig(BASIC_TIM,TIM_IT_Update,ENABLE);
	
	//ʹ�ܼ�����
	 TIM_Cmd(BASIC_TIM, ENABLE);
}

void BASIC_TIM_Init(void)
{
	BASIC_TIM_NVIC_Config();
	BASIC_TIM_Config();
}

