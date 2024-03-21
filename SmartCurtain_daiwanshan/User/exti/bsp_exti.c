#include "bsp_exti.h"

static void EXTI_NVIC_Config(void)   //ֻ�ܱ�bsp_exti.c����
{
	NVIC_InitTypeDef NVIC_InitSTuct; //����ṹ�庯��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����
	
	//��ʼ��NVIC
	NVIC_InitSTuct.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitSTuct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitSTuct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitSTuct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitSTuct);

}

void EXTI_Key_Config(void)
{
	//����ṹ��Ҫ����������
	GPIO_InitTypeDef GPIO_InitSTruct;
	EXTI_InitTypeDef EXTI_InitSTruct;
	
	//�����ж����ȼ�
	EXTI_NVIC_Config();
	
	//��ʼ��GPIO KEY1
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK,ENABLE);
	GPIO_InitSTruct.GPIO_Pin = KEY1_INT_GPIO_PIN;
	GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_IPU;
	//GPIO_InitSTruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY1_INT_GPIO_Port,&GPIO_InitSTruct);
	
	//��ʼ��EXTI KEY1
	RCC_APB2PeriphClockCmd(KEY1_INT_AFIO_CLK,ENABLE);//��ʱ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource12);
	
	EXTI_InitSTruct.EXTI_Line = EXTI_Line12;
	EXTI_InitSTruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitSTruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitSTruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitSTruct);
	
	
	
	//��ʼ��GPIO KEY2
	RCC_APB2PeriphClockCmd(KEY2_INT_GPIO_CLK,ENABLE);
	GPIO_InitSTruct.GPIO_Pin = KEY2_INT_GPIO_PIN;
	GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_IPU;
	//GPIO_InitSTruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY2_INT_GPIO_Port,&GPIO_InitSTruct);
	
	//��ʼ��EXTI KEY2
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource13);
	RCC_APB2PeriphClockCmd(KEY2_INT_AFIO_CLK,ENABLE);//��ʱ��
	
	EXTI_InitSTruct.EXTI_Line = EXTI_Line13;
	EXTI_InitSTruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitSTruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitSTruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitSTruct);
	
		//��ʼ��GPIO KEY3
	RCC_APB2PeriphClockCmd(KEY3_INT_GPIO_CLK,ENABLE);
	GPIO_InitSTruct.GPIO_Pin = KEY3_INT_GPIO_PIN;
	GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_IPU;
	//GPIO_InitSTruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY3_INT_GPIO_Port,&GPIO_InitSTruct);
	
	//��ʼ��EXTI KEY3
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	RCC_APB2PeriphClockCmd(KEY3_INT_AFIO_CLK,ENABLE);//��ʱ��
	
	EXTI_InitSTruct.EXTI_Line = EXTI_Line14;
	EXTI_InitSTruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitSTruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitSTruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitSTruct);
	
	
		//��ʼ��GPIO KEY4
	RCC_APB2PeriphClockCmd(KEY4_INT_GPIO_CLK,ENABLE);
	GPIO_InitSTruct.GPIO_Pin = KEY4_INT_GPIO_PIN;
	GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_IPU;
	//GPIO_InitSTruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY4_INT_GPIO_Port,&GPIO_InitSTruct);
	
	//��ʼ��EXTI KEY4
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource15);
	RCC_APB2PeriphClockCmd(KEY4_INT_AFIO_CLK,ENABLE);//��ʱ��
	
	EXTI_InitSTruct.EXTI_Line = EXTI_Line15;
	EXTI_InitSTruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitSTruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitSTruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitSTruct);
}

