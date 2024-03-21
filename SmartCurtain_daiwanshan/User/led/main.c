/************************************************************************************
*  Copyright (c), 2014, HelTec Automatic Technology co.,LTD.
*            All rights reserved.
*
* Http:    www.heltec.cn
* Email:   cn.heltec@gmail.com
* WebShop: heltec.taobao.com
*
* File name: main.c
* Project  : HelTec.uvprij
* Processor: STM32F103C8T6
* Compiler : MDK fo ARM
* 
* Author : С��
* Version: 1.00
* Date   : 2014.4.8
* Email  : hello14blog@gmail.com
* Modification: none
* 
* Description:128*64�����OLED��ʾ�������ļ����������ڻ����Զ���(heltec.taobao.com)��SD1306����IICͨ�ŷ�ʽ��ʾ��
*
* Others: none;
*
* Function List:
*	1. int main(void);//������
*
* History: none;
*ע��˵����CS����Ҫ�ӵ�
*************************************************************************************/
#include "stm32f10x.h"
#include "OLED_I2C.h"
#include "delay.h"
#include "dht11.h"
#include "bsp_SysTick.h"
#include "usart.h"
#include <stdio.h>  
#include <string.h>  
#include "bsp_tim.h"
#include <stdbool.h>
#include "bsp_exti.h"  
#include "bh1750.h"
#include "bsp_motor.h" 
#include "led.h"  
#include "bsp_key.h"
#include "fun.h"
#include "beep.h"

#include "esp8266.h"
#include "onenet.h"
#include <stdio.h>

unsigned char i;
uint8_t KeyNum = 0;
uint8_t flag1 = 0;

u8 alarmFlag = 0;//�Ƿ񱨾��ı�־
u8 alarm_is_free = 10;//�������Ƿ��ֶ�������������ֶ�����������Ϊ0

extern int lightva;

u8 humidityH;	  //ʪ����������
u8 humidityL;	  //ʪ��С������
u8 temperatureH;   //�¶���������
u8 temperatureL;   //�¶�С������
extern char oledBuf[20];
float Light = 0; //���ն�
u8 Led_Status = 0;

char PUB_BUF[256];//�ϴ����ݵ�buf
const char *devSubTopic[] = {"/mysmarthome/tsub"};
const char devPubTopic[] = "/mysmarthome/tpub";
u8 ESP8266_INIT_OK = 0;//esp8266��ʼ����ɱ�־


int main(void)
{
unsigned short timeCount = 0;	//���ͼ������
unsigned char *dataPtr = NULL;
static u8 lineNow;
	
	LED_Init();
	
	BASIC_TIM_Init();  
	DelayInit();
	I2C_Configuration();
	DHT11_Init();
	OLED_Init();
	BH1750_Init();
	
  Motor_GPIO_Config();  
//	KEY_GPIO_Config();
	EXTI_Key_Config();
	BEEP_Init();
	DelayMs(180);
	OLED_Fill(0xFF);//ȫ������
	Usart1_Init(115200);
	Usart2_Init(115200);
	ESP8266_Init();
	
	while(OneNet_DevLink()){//����OneNET
		DelayMs(500);
	}		
	
		/*ϵͳ��������*/
	for(i=27;i<32;i++)
	{
		OLED_ShowCN(-406.+i*16,4,i);//ϵͳ������
	}
	DelayS(2);
	OLED_Fill(0x00);//ȫ������
	
		/*��BH1750*/
	
	SysTicks_Delay_ms(180);
	beeperOnce();    //��������
	
	 /*     ��������     */
	for(i=0;i<6;i++)
		{
			OLED_ShowCN(18+i*16,0,i);//��ʾ���ܴ���ϵͳ
		}
	SysTicks_Delay_ms(800);
		
			OLED_CLS();
		
		/*ģʽѡ�����*/
	
		for(i=32;i<36;i++)
		{
			
			OLED_ShowCN(-512+i*16,2,i);//��ʾ  �Զ�ģʽ
		}
		
		for(i=36;i<40;i++)
		{
			
			OLED_ShowCN(-576+i*16,5,i);//��ʾ  �ֶ�ģʽ
		}
		
		
		OneNet_Subscribe(devSubTopic, 1);
		
		/*ģʽѡ����*/
	while(1)
	{

		if(++timeCount >= 10)	// 5000ms / 25 = 200 ���ͼ��5000ms
		{
			DEBUG_LOG("==================================================================================");
			DEBUG_LOG("�������� ----- OneNet_Publish");
			sprintf(PUB_BUF,"{\"Hum\":%d.%d,\"Temp\":%d.%d,\"Light\":%.1f,\"Led\":%s,\"Beep\":%s,\"LightMax\":%d}",
			humidityH,humidityL,temperatureH,temperatureL,Light,Led_Status?"\"false\"":"\"true\"",alarmFlag?"\"true\"":"\"false\"",lightva);
			OneNet_Publish(devPubTopic, PUB_BUF);
			DEBUG_LOG("==================================================================================");
			timeCount = 0;
			ESP8266_Clear();
		}
//		
		dataPtr = ESP8266_GetIPD(3);
		if(dataPtr != NULL)
			OneNet_RevPro(dataPtr);
		DelayMs(10);
		
		switch(flag1)
			{
				case 1: automatic();break;
				case 2: Manual();break;
				
				default:break;
	

			}
			
		
	}
	
}


