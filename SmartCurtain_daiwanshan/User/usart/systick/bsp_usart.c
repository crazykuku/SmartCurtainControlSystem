#include "bsp_usart.h"
#include "bsp_motor.h" 
#include "OLED_I2C.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "bsp_led.h"  

//static void NVIC_Configuration(void)
//{
//  NVIC_InitTypeDef NVIC_InitStructure;
//  
//  /* Ƕ�������жϿ�������ѡ�� */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//  
//  /* ����USARTΪ�ж�Դ */
//  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
//  /* �������ȼ�*/
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//  /* �����ȼ� */
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//  /* ʹ���ж� */
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  /* ��ʼ������NVIC */
//  NVIC_Init(&NVIC_InitStructure);
//}
//��ʼ��USART
extern int lightva;
extern uint8_t KeyNum;
uint8_t ucTemp;
uint8_t Temp;
extern double lightvalue;
extern unsigned char i;
char Lightvalue[10];


//void USART_Config(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;

//	// �򿪴���GPIO��ʱ��
//	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
//	
//	// �򿪴��������ʱ��
//	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

//	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
//	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

//  // ��USART Rx��GPIO����Ϊ��������ģʽ
//	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
//	
//	// ���ô��ڵĹ�������
//	// ���ò�����
//	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
//	// ���� �������ֳ�
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	// ����ֹͣλ
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	// ����У��λ
//	USART_InitStructure.USART_Parity = USART_Parity_No ;
//	// ����Ӳ��������
//	USART_InitStructure.USART_HardwareFlowControl = 
//	USART_HardwareFlowControl_None;
//	// ���ù���ģʽ���շ�һ��
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//	// ��ɴ��ڵĳ�ʼ������
//	USART_Init(DEBUG_USARTx, &USART_InitStructure);	
//		// �����ж����ȼ�����
////   NVIC_Configuration();
//	
//	// ʹ�ܴ��ڽ����ж�
//	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);	
//	
//	// ʹ�ܴ���
//	USART_Cmd(DEBUG_USARTx, ENABLE);	    
//}

void usart_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}

void uart2_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART2��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
  
	//USART1_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.2
   
  //USART1_RX	  GPIOA.3��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.3 

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART2, &USART_InitStructure); //��ʼ������2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���2 

}


void USART1_IRQHandler(void)
{

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //�����ж�
	{
		USART_ClearFlag(USART1, USART_FLAG_RXNE);
	}

}




//���������жϺ���
//void USART2_IRQHandler(void) 
//{ 
//	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
//	{		
//		ucTemp = USART_ReceiveData(USART2);
//	
////		USART_SendData(USART2,ucTemp);		
//	
//			if(ucTemp == '1')   //����1
//			{
//				OLED_CLS();
//			
//			for(i=23;i<27;i++)
//		{
//			OLED_ShowCN(-368+i*16,1,i);//������ֵ
//		}
//				lightva = lightva+25;
//				printf("guangzhao %d",lightva);
//				sprintf((char *)Lightvalue,"%d",lightva);
//				OLED_ShowStr(45,5,(u8 *)Lightvalue, 2);
//				
//			//	USART_SendData(USART2,lightvalue);		 
//			}			
//			
//			
//			if(ucTemp == '2')   //����2
//			{
//				OLED_CLS();
//				for(i=23;i<27;i++)
//				{
//					OLED_ShowCN(-368+i*16,1,i);//������ֵ
//				}
//				
//				lightva = lightva+50;
//				printf("guangzhao %d",lightva);
//				sprintf((char *)Lightvalue,"%d",lightva);
//				OLED_ShowStr(45,5,(u8 *)Lightvalue, 2);
////				USART_SendData(USART2,lightva);		 
//			}	

//			
//				if(ucTemp == '3')  //����3
//			{
//				OLED_CLS();
//				for(i=23;i<27;i++)
//				{
//					OLED_ShowCN(-368+i*16,1,i);//������ֵ
//				}
//				
//					lightva = lightva-25;
//				if(lightva<0)
//				{
//					lightva = 0;
//				}
//				printf("guangzhao %d",lightva);
//				sprintf((char *)Lightvalue,"%d",lightva);
//				OLED_ShowStr(45,5,(u8 *)Lightvalue, 2);
////				USART_SendData(USART2,lightva);	
//			}			
//			
//			
//			
//			if(ucTemp == '4') //����4
//			{
//				OLED_CLS();
//				for(i=23;i<27;i++)
//				{
//					OLED_ShowCN(-368+i*16,1,i);//������ֵ
//				}
//				
//					lightva = lightva-50;
//				if(lightva<0)
//				{
//					lightva = 0;
//				}
//				printf("guangzhao %d",lightva);
//				sprintf((char *)Lightvalue,"%d",lightva);
//				OLED_ShowStr(45,5,(u8 *)Lightvalue, 2); 
//			}		
//			
//			
//				if(ucTemp == '5') //����5�򿪴���
//			{
//				KeyNum = 7;
//			}		
//			
//			if(ucTemp == '6') //����5�򿪴���
//			{
//				KeyNum = 8;
//			}		
//			
//				if(ucTemp == 'a')  //�򿪵ƹ�
//			{
//				OLED_CLS();
//				for(i=45;i<50;i++)
//				{
//					OLED_ShowCN(-700+i*16,1,i);//�ƹ��Ѵ�
//				}
//				GPIO_ResetBits(LED_R_GPIO_Port, LED_R_GPIO_PIN );
//	
////				USART_SendData(USART2,lightva);	
//			}			
//			
//			
//					if(ucTemp == 'b') //�رյƹ�
//			{
//				OLED_CLS();
//				for(i=40;i<45;i++)
//				{
//					OLED_ShowCN(-620+i*16,1,i);//�ƹ��ѹر�
//				}
//				GPIO_SetBits(LED_R_GPIO_Port, LED_R_GPIO_PIN );
//			}		
//			
//   }    
// }

 
 
 
 
//����һ���ֽ�
void Usart_SendByte(USART_TypeDef * pUSARTx,uint8_t data)
{
	USART_SendData(pUSARTx, data);
	// ���TXEλ
	while(USART_GetFlagStatus(pUSARTx ,USART_FLAG_TXE)== RESET);
}


//���������ֽ�
void Usart_HalfByte(USART_TypeDef * pUSARTx,uint16_t data)
{
	uint8_t temp_h,temp_l;
	//�߰�λ�����ұ� �Ͱ�λֱ�ӵ���
	temp_h = (data&0xff00)>>8;
	temp_l = data&0xff;
	
// ���TXEλ
	USART_SendData(pUSARTx, temp_h);
	while(USART_GetFlagStatus(pUSARTx ,USART_FLAG_TXE)== RESET);
	
	USART_SendData(pUSARTx, temp_l);
	while(USART_GetFlagStatus(pUSARTx ,USART_FLAG_TXE)== RESET);
}


//��������
void Usart_SendArray(USART_TypeDef * pUSARTx,uint8_t *array, uint16_t num)
{
	uint8_t i;
	for(i=0;i<num;i++)
	{
		Usart_SendByte(pUSARTx, array[i]);
			
	}
		//���������TC
	while(USART_GetFlagStatus(pUSARTx ,USART_FLAG_TC)== RESET);
}


//�����ַ���
void Usart_SendStr(USART_TypeDef * pUSARTx ,uint8_t *str)
{
	uint8_t i=0;
	do
	{
		Usart_SendByte(pUSARTx , *(str+i));
		i++;
	}while(*(str+i)!='\0');
	while(USART_GetFlagStatus(pUSARTx ,USART_FLAG_TC)== RESET);
}

///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
}


/*
************************************************************
*	�������ƣ�	Usart_SendString
*
*	�������ܣ�	�������ݷ���
*
*	��ڲ�����	USARTx��������
*				str��Ҫ���͵�����
*				len�����ݳ���
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len)
{

	unsigned short count = 0;
	
	for(; count < len; count++)
	{
		USART_SendData(USARTx, *str++);									//��������
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);		//�ȴ��������
	}

}


/*
************************************************************
*	�������ƣ�	UsartPrintf
*
*	�������ܣ�	��ʽ����ӡ
*
*	��ڲ�����	USARTx��������
*				fmt����������
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...)
{

	unsigned char UsartPrintfBuf[296];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf;
	
	va_start(ap, fmt);
	vsnprintf((char *)UsartPrintfBuf, sizeof(UsartPrintfBuf), fmt, ap);							//��ʽ��
	va_end(ap);
	
	while(*pStr != 0)
	{
		USART_SendData(USARTx, *pStr++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	}
}

/*
************************************************************
*	�������ƣ�	DEBUG_LOG
*
*	�������ܣ�	��ʽ�����������Ϣ
*
*	��ڲ�����	fmt����������

*	���ز�����	��
*
*	˵����		
************************************************************
*/
void DEBUG_LOG(char *fmt,...)
{
	unsigned char UsartPrintfBuf[296];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf;
	
	va_start(ap, fmt);
	vsnprintf((char *)UsartPrintfBuf, sizeof(UsartPrintfBuf), fmt, ap);							//��ʽ��
	va_end(ap);
	UsartPrintf(USART1, "[LOG] /> ");
	while(*pStr != 0)
	{
		USART_SendData(USART1, *pStr++);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	}
	UsartPrintf(USART1, "\r\n");
}



