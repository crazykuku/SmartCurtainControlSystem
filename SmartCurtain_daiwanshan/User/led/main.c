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
* Author : 小林
* Version: 1.00
* Date   : 2014.4.8
* Email  : hello14blog@gmail.com
* Modification: none
* 
* Description:128*64点阵的OLED显示屏测试文件，仅适用于惠特自动化(heltec.taobao.com)的SD1306驱动IIC通信方式显示屏
*
* Others: none;
*
* Function List:
*	1. int main(void);//主函数
*
* History: none;
*注意说明：CS脚需要接地
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

u8 alarmFlag = 0;//是否报警的标志
u8 alarm_is_free = 10;//报警器是否被手动操作，如果被手动操作即设置为0

extern int lightva;

u8 humidityH;	  //湿度整数部分
u8 humidityL;	  //湿度小数部分
u8 temperatureH;   //温度整数部分
u8 temperatureL;   //温度小数部分
extern char oledBuf[20];
float Light = 0; //光照度
u8 Led_Status = 0;

char PUB_BUF[256];//上传数据的buf
const char *devSubTopic[] = {"/mysmarthome/tsub"};
const char devPubTopic[] = "/mysmarthome/tpub";
u8 ESP8266_INIT_OK = 0;//esp8266初始化完成标志


int main(void)
{
unsigned short timeCount = 0;	//发送间隔变量
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
	OLED_Fill(0xFF);//全屏点亮
	Usart1_Init(115200);
	Usart2_Init(115200);
	ESP8266_Init();
	
	while(OneNet_DevLink()){//接入OneNET
		DelayMs(500);
	}		
	
		/*系统开机动画*/
	for(i=27;i<32;i++)
	{
		OLED_ShowCN(-406.+i*16,4,i);//系统加载中
	}
	DelayS(2);
	OLED_Fill(0x00);//全屏点亮
	
		/*打开BH1750*/
	
	SysTicks_Delay_ms(180);
	beeperOnce();    //蜂鸣器响
	
	 /*     开机界面     */
	for(i=0;i<6;i++)
		{
			OLED_ShowCN(18+i*16,0,i);//显示智能窗帘系统
		}
	SysTicks_Delay_ms(800);
		
			OLED_CLS();
		
		/*模式选择界面*/
	
		for(i=32;i<36;i++)
		{
			
			OLED_ShowCN(-512+i*16,2,i);//显示  自动模式
		}
		
		for(i=36;i<40;i++)
		{
			
			OLED_ShowCN(-576+i*16,5,i);//显示  手动模式
		}
		
		
		OneNet_Subscribe(devSubTopic, 1);
		
		/*模式选择函数*/
	while(1)
	{

		if(++timeCount >= 10)	// 5000ms / 25 = 200 发送间隔5000ms
		{
			DEBUG_LOG("==================================================================================");
			DEBUG_LOG("发布数据 ----- OneNet_Publish");
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


