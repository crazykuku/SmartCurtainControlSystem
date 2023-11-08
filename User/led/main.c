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
#include "bsp_dht11.h"
#include "bsp_SysTick.h"
#include "bsp_usart.h"
#include <stdio.h>  
#include <string.h>  
#include "bsp_tim.h"
#include <stdbool.h>
#include "bsp_exti.h"  
#include "bsp_bh1750.h"
#include "bsp_motor.h" 
#include "bsp_led.h"  
#include "bsp_key.h"
#include "fun.h"
#include "beeper.h"
unsigned char i;
uint8_t KeyNum = 0;
uint8_t flag1 = 0;

int main(void)
{

	LED_GPIO_Config();
//	USART_Config (); 
	usart_init(115200);
	uart2_init(9600);
	BASIC_TIM_Init();  
	DelayInit();
	I2C_Configuration();
	DHT11_Init();
	OLED_Init();
	BH1750_GPIO_Config();
	Single_Write_BH1750(POWER_ON);
  Motor_GPIO_Config();  
//	KEY_GPIO_Config();
	EXTI_Key_Config();
	BEEPER_Init();
	DelayMs(180);
	OLED_Fill(0xFF);//全屏点亮
	
		/*系统开机动画*/
	for(i=27;i<32;i++)
	{
		OLED_ShowCN(-406.+i*16,4,i);//系统加载中
	}
	DelayS(2);
	OLED_Fill(0x00);//全屏点亮
	
		/*打开BH1750*/
	Single_Write_BH1750(POWER_ON);
	Single_Write_BH1750(CONTINUE_H_MODE);
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
		
		/*模式选择函数*/
	while(1)
	{
		switch(flag1){
		case 1: automatic();break;
		case 2: Manual();break;

		default:break;
	

									}
	}
	
}


