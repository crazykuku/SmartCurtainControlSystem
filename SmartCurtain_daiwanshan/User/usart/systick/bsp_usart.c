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
//  /* 嵌套向量中断控制器组选择 */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//  
//  /* 配置USART为中断源 */
//  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
//  /* 抢断优先级*/
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//  /* 子优先级 */
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//  /* 使能中断 */
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  /* 初始化配置NVIC */
//  NVIC_Init(&NVIC_InitStructure);
//}
//初始化USART
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

//	// 打开串口GPIO的时钟
//	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
//	
//	// 打开串口外设的时钟
//	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

//	// 将USART Tx的GPIO配置为推挽复用模式
//	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

//  // 将USART Rx的GPIO配置为浮空输入模式
//	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
//	
//	// 配置串口的工作参数
//	// 配置波特率
//	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
//	// 配置 针数据字长
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	// 配置停止位
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	// 配置校验位
//	USART_InitStructure.USART_Parity = USART_Parity_No ;
//	// 配置硬件流控制
//	USART_InitStructure.USART_HardwareFlowControl = 
//	USART_HardwareFlowControl_None;
//	// 配置工作模式，收发一起
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//	// 完成串口的初始化配置
//	USART_Init(DEBUG_USARTx, &USART_InitStructure);	
//		// 串口中断优先级配置
////   NVIC_Configuration();
//	
//	// 使能串口接收中断
//	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);	
//	
//	// 使能串口
//	USART_Cmd(DEBUG_USARTx, ENABLE);	    
//}

void usart_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 

}

void uart2_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能USART2，GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
  
	//USART1_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.2
   
  //USART1_RX	  GPIOA.3初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.3 

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART2, &USART_InitStructure); //初始化串口2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口2 

}


void USART1_IRQHandler(void)
{

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //接收中断
	{
		USART_ClearFlag(USART1, USART_FLAG_RXNE);
	}

}




//蓝牙串口中断函数
//void USART2_IRQHandler(void) 
//{ 
//	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
//	{		
//		ucTemp = USART_ReceiveData(USART2);
//	
////		USART_SendData(USART2,ucTemp);		
//	
//			if(ucTemp == '1')   //按键1
//			{
//				OLED_CLS();
//			
//			for(i=23;i<27;i++)
//		{
//			OLED_ShowCN(-368+i*16,1,i);//光照阈值
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
//			if(ucTemp == '2')   //按键2
//			{
//				OLED_CLS();
//				for(i=23;i<27;i++)
//				{
//					OLED_ShowCN(-368+i*16,1,i);//光照阈值
//				}
//				
//				lightva = lightva+50;
//				printf("guangzhao %d",lightva);
//				sprintf((char *)Lightvalue,"%d",lightva);
//				OLED_ShowStr(45,5,(u8 *)Lightvalue, 2);
////				USART_SendData(USART2,lightva);		 
//			}	

//			
//				if(ucTemp == '3')  //按键3
//			{
//				OLED_CLS();
//				for(i=23;i<27;i++)
//				{
//					OLED_ShowCN(-368+i*16,1,i);//光照阈值
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
//			if(ucTemp == '4') //按键4
//			{
//				OLED_CLS();
//				for(i=23;i<27;i++)
//				{
//					OLED_ShowCN(-368+i*16,1,i);//光照阈值
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
//				if(ucTemp == '5') //按键5打开窗帘
//			{
//				KeyNum = 7;
//			}		
//			
//			if(ucTemp == '6') //按键5打开窗帘
//			{
//				KeyNum = 8;
//			}		
//			
//				if(ucTemp == 'a')  //打开灯光
//			{
//				OLED_CLS();
//				for(i=45;i<50;i++)
//				{
//					OLED_ShowCN(-700+i*16,1,i);//灯光已打开
//				}
//				GPIO_ResetBits(LED_R_GPIO_Port, LED_R_GPIO_PIN );
//	
////				USART_SendData(USART2,lightva);	
//			}			
//			
//			
//					if(ucTemp == 'b') //关闭灯光
//			{
//				OLED_CLS();
//				for(i=40;i<45;i++)
//				{
//					OLED_ShowCN(-620+i*16,1,i);//灯光已关闭
//				}
//				GPIO_SetBits(LED_R_GPIO_Port, LED_R_GPIO_PIN );
//			}		
//			
//   }    
// }

 
 
 
 
//发送一个字节
void Usart_SendByte(USART_TypeDef * pUSARTx,uint8_t data)
{
	USART_SendData(pUSARTx, data);
	// 检测TXE位
	while(USART_GetFlagStatus(pUSARTx ,USART_FLAG_TXE)== RESET);
}


//发送两个字节
void Usart_HalfByte(USART_TypeDef * pUSARTx,uint16_t data)
{
	uint8_t temp_h,temp_l;
	//高八位调到右边 低八位直接调用
	temp_h = (data&0xff00)>>8;
	temp_l = data&0xff;
	
// 检测TXE位
	USART_SendData(pUSARTx, temp_h);
	while(USART_GetFlagStatus(pUSARTx ,USART_FLAG_TXE)== RESET);
	
	USART_SendData(pUSARTx, temp_l);
	while(USART_GetFlagStatus(pUSARTx ,USART_FLAG_TXE)== RESET);
}


//发送数组
void Usart_SendArray(USART_TypeDef * pUSARTx,uint8_t *array, uint16_t num)
{
	uint8_t i;
	for(i=0;i<num;i++)
	{
		Usart_SendByte(pUSARTx, array[i]);
			
	}
		//数组检测的是TC
	while(USART_GetFlagStatus(pUSARTx ,USART_FLAG_TC)== RESET);
}


//发送字符串
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

///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
}


/*
************************************************************
*	函数名称：	Usart_SendString
*
*	函数功能：	串口数据发送
*
*	入口参数：	USARTx：串口组
*				str：要发送的数据
*				len：数据长度
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len)
{

	unsigned short count = 0;
	
	for(; count < len; count++)
	{
		USART_SendData(USARTx, *str++);									//发送数据
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);		//等待发送完成
	}

}


/*
************************************************************
*	函数名称：	UsartPrintf
*
*	函数功能：	格式化打印
*
*	入口参数：	USARTx：串口组
*				fmt：不定长参
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...)
{

	unsigned char UsartPrintfBuf[296];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf;
	
	va_start(ap, fmt);
	vsnprintf((char *)UsartPrintfBuf, sizeof(UsartPrintfBuf), fmt, ap);							//格式化
	va_end(ap);
	
	while(*pStr != 0)
	{
		USART_SendData(USARTx, *pStr++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	}
}

/*
************************************************************
*	函数名称：	DEBUG_LOG
*
*	函数功能：	格式化输出调试信息
*
*	入口参数：	fmt：不定长参

*	返回参数：	无
*
*	说明：		
************************************************************
*/
void DEBUG_LOG(char *fmt,...)
{
	unsigned char UsartPrintfBuf[296];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf;
	
	va_start(ap, fmt);
	vsnprintf((char *)UsartPrintfBuf, sizeof(UsartPrintfBuf), fmt, ap);							//格式化
	va_end(ap);
	UsartPrintf(USART1, "[LOG] /> ");
	while(*pStr != 0)
	{
		USART_SendData(USART1, *pStr++);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	}
	UsartPrintf(USART1, "\r\n");
}



