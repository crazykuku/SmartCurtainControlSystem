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
#include "onenet.h"
#include "esp8266.h"

int lightva = 100;  //初始化光照阈值
extern float Light; //光照强度
float temp;
uint8_t BUF[8];
uint32_t dis_data;
uint32_t Value_GY_30;
uint8_t flag =0;   

char oledBuf[20];

extern uint8_t KeyNum;  //按键标记位
extern u8 humidityH;	  //湿度整数部分
extern u8 humidityL;	  //湿度小数部分
extern u8 temperatureH;   //温度整数部分
extern u8 temperatureL;   //温度小数部分 
extern unsigned char i;
extern u8 Led_Status;
extern u8 alarmFlag;
extern char PUB_BUF[256];




//extern char Lightvalue[10];


/*手动模式*/
void Manual(void)
{
	
	/********** 温湿度传感器获取数据**************/
			DHT11_Read_Data(&humidityH,&humidityL,&temperatureH,&temperatureL);
			
			/********** 光照度传感器获取数据**************/
			if (!i2c_CheckDevice(BH1750_Addr))
			{
				Light = LIght_Intensity();
			}
			
			/********** 读取LED0的状态 **************/
			Led_Status = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13);
	
		if (KeyNum == 3)  //如果按键3按下
		{
			OLED_CLS();//清屏
			beeperOnce();								//蜂鸣器短鸣
			OLED_ShowStr(40,4,"OPEN", 2);//显示OPEN
			motor_ccw();   //电机展开
			KeyNum = 0;    //标记清零
			
    }	
	else if (KeyNum == 4)  //如果按键4按下
		{
			OLED_CLS();										//清屏
			beeperOnce();									//蜂鸣器短鸣
			OLED_ShowStr(40,4,"CLOSE", 2);//显示CLOSE
			motor_cw();										//电机闭合
			KeyNum = 0;										//标记清零
		
    }

//	else if (KeyNum == 7)		//蓝牙按键
//		{
//			OLED_CLS();									 //清屏
//			beeperOnce();								 //蜂鸣器短鸣
//			OLED_ShowStr(40,4,"OPEN", 2);//显示OPEN
//			motor_ccw();  							 //电机展开
//			KeyNum = 0;									 //标记清零

//    }	
//		else if (KeyNum == 8)		//蓝牙按键
//		{
//			OLED_CLS();									 //清屏
//			beeperOnce();								 //蜂鸣器短鸣
//			OLED_ShowStr(40,4,"CLOSE", 2);//显示CLOSE
//			motor_cw();										//电机闭合
//			KeyNum = 0;										//标记清零
//		
//    }	
		
			DEBUG_LOG("lightva = %d\n",lightva);
			/********** 输出调试信息 **************/
			DEBUG_LOG(" | 湿度：%d.%d C | 温度：%d.%d %% | 光照度：%.1f lx | 指示灯：%s | 报警器：%s | ",humidityH,humidityL,temperatureH,temperatureL,Light,Led_Status?"关闭":"【启动】",alarmFlag?"【启动】":"停止");
			

		
		/*UI界面函数*/
				sprintf(oledBuf,"Welcome");
				OLED_ShowStr(32,0,(u8*)oledBuf,2);//8*16 “ABC”
				sprintf(oledBuf,"Hum:%d.%d %%",humidityH,humidityL);
				OLED_ShowStr(0,2,(u8*)oledBuf,2);//8*16 “ABC”
				sprintf(oledBuf,"Temp:%d.%d C",temperatureH,temperatureL);
				OLED_ShowStr(0,4,(u8*)oledBuf,2);//8*16 “ABC”
				sprintf(oledBuf,"Light:%.1f Lx",Light);
				OLED_ShowStr(0,6,(u8*)oledBuf,2);//8*16 “ABC”
		DelayS(2);
}

/*自动模式*/
void automatic(void)
{
		char lightvalue[10];
	  SysTicks_Delay_ms(2000);   //延迟两秒
		OLED_CLS();
		
	
	/********** 温湿度传感器获取数据**************/
			DHT11_Read_Data(&humidityH,&humidityL,&temperatureH,&temperatureL);
			
			/********** 光照度传感器获取数据**************/
			if (!i2c_CheckDevice(BH1750_Addr))
			{
				Light = LIght_Intensity();
			}
			
			/********** 读取LED0的状态 **************/
			Led_Status = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13);
			
	
		if (KeyNum == 5)    //判断按键是否按下
		{
			OLED_CLS();
			for(i=23;i<27;i++) 
		{
			OLED_ShowCN(-368+i*16,1,i);//显示光照阈值
		}
		
			lightva = lightva+20;     //光照阈值+25
			sprintf((char *)lightvalue,"%d",lightva);  //将光照阈值写入数组
			OLED_ShowStr(45,5,(u8 *)lightvalue, 2);    //显示光照数组
		  DelayMs(600);
			KeyNum = 0;									//标记位清零
		
    }	
	if (KeyNum == 6)   //检测按键是否按下
		{
			 OLED_CLS();
				for(i=23;i<27;i++)
				{
					OLED_ShowCN(-368+i*16,1,i);//显示光照阈值
				}
			
				lightva = lightva-20;//光照阈值-25
					if(lightva<0)    //判断阈值是否小于零
				{
					lightva = 0;
				}
				sprintf((char *)lightvalue,"%d",lightva);  //将光照阈值写入数组
				OLED_ShowStr(45,5,(u8 *)lightvalue, 2);		 //显示光照数组
				DelayMs(600);
			KeyNum = 0;			//标记位清零
		
    }	

		if(Light<=lightva) //判断光照强度是否小于阈值
		{

				
			if(flag == 1) //判断窗帘是否已经打开
			{
				OLED_CLS();
		
				for(i=18;i<23;i++)
				{
					
					OLED_ShowCN(-268+i*16,4,i);//显示  窗帘闭合中
				}
				for(int i = 0;i < 10;i++)
				{
					beeperOnce();beeperOnce();DelayMs(100);
				}
				motor_ccw();
			}
			flag = 0; 
		}
		
		else //反之打开窗帘
		{

			if(flag == 0)  //判断窗帘是否已经闭合
			{
				OLED_CLS();
				for(i=13;i<18;i++)
				{
					OLED_ShowCN(-180+i*16,4,i);//显示 窗帘展开中
				}	
				for(int i = 0;i < 10;i++)
				{
					beeperOnce();beeperOnce();DelayMs(100);
				}
				motor_cw();
			}
			flag = 1;
		
		}
			
			DEBUG_LOG("lightva = %d\n",lightva);
			/********** 输出调试信息 **************/
			DEBUG_LOG(" | 湿度：%d.%d C | 温度：%d.%d %% | 光照度：%.1f lx | 指示灯：%s | 报警器：%s | ",humidityH,humidityL,temperatureH,temperatureL,Light,Led_Status?"关闭":"【启动】",alarmFlag?"【启动】":"停止");

		

//		/*UI界面函数*/
				sprintf(oledBuf,"Welcome");
				OLED_ShowStr(32,0,(u8*)oledBuf,2);//8*16 “ABC”
				sprintf(oledBuf,"Hum:%d.%d %%",humidityH,humidityL);
				OLED_ShowStr(0,2,(u8*)oledBuf,2);//8*16 “ABC”
				sprintf(oledBuf,"Temp:%d.%d C",temperatureH,temperatureL);
				OLED_ShowStr(0,4,(u8*)oledBuf,2);//8*16 “ABC”
				sprintf(oledBuf,"Light:%.1f Lx",Light);
				OLED_ShowStr(0,6,(u8*)oledBuf,2);//8*16 “ABC”
		DelayS(1);//延时秒
//	
		
		
		
		
		
		
}
