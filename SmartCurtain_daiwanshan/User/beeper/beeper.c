#include "beeper.h"
#include "delay.h"

//������IO��ʼ��
void BEEPER_Init(void)
{
 
	GPIO_InitTypeDef GPIO_InitSTruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PB�˿�ʱ��
	
	//��ʼ�� ����������PB9	  �������
	GPIO_InitSTruct.GPIO_Pin  = GPIO_Pin_0;	
	GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitSTruct.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitSTruct);//��ʼ��GPIO
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);//����͵�ƽ
	//GPIO_SetBits(GPIOA,GPIO_Pin_0);//����͵�ƽ
}
//����������һ��
void beeperOnce(void)
{
		GPIO_SetBits(GPIOA, GPIO_Pin_0 );
		DelayMs(10);
		GPIO_ResetBits(GPIOA, GPIO_Pin_0 );
}

