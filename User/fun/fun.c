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

int lightva = 15;  //初始化光照阈值
double lightvalue  = 0; //光照强度
float temp;
uint8_t BUF[8];
uint32_t dis_data;
uint32_t Value_GY_30;
uint8_t flag =0;   

extern uint8_t KeyNum;  //按键标记位
double humidity;    //湿度
double temperature;  //温度
extern unsigned char i;
DHT11_Data_TypeDef DHT11_Data;
extern char Lightvalue[10];


/*手动模式*/
void Manual(void)
{
	
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

	else if (KeyNum == 7)		//蓝牙按键
		{
			OLED_CLS();									 //清屏
			beeperOnce();								 //蜂鸣器短鸣
			OLED_ShowStr(40,4,"OPEN", 2);//显示OPEN
			motor_ccw();  							 //电机展开
			KeyNum = 0;									 //标记清零
    }	
		else if (KeyNum == 8)		//蓝牙按键
		{
			OLED_CLS();									 //清屏
			beeperOnce();								 //蜂鸣器短鸣
			OLED_ShowStr(40,4,"CLOSE", 2);//显示CLOSE
			motor_cw();										//电机闭合
			KeyNum = 0;										//标记清零
		
    }	
}

/*自动模式*/
void automatic(void)
{
		char LightIntensity[10];  //光照强度数组
		char TemStr[6];    //温度数组
		char HumStr[6];    //湿度数组
		

		
		/*按键选择模式*/
	
			
		/*BH1750功能代码*/
	  SysTicks_Delay_ms(2000);   //延迟两秒
		OLED_CLS();
		
		Litght_Read();    //读取光照函数
		dis_data=BUF[0];
    dis_data=(dis_data<<8)+BUF[1];//合成数据，即光照数据
    temp=(float)dis_data/1.2;
		
	
		/*DHT11功能代码*/

		if ( DHT11_Read_TempAndHumidity ( & DHT11_Data ) == SUCCESS )       //读取 DHT11 温湿度信息
		{
				sprintf((char *)TemStr,"%d.%d",DHT11_Data .temp_int,DHT11_Data.temp_deci);
				sprintf((char *)HumStr,"%d.%d",DHT11_Data .humi_int,DHT11_Data .humi_deci);
		}
	
	
		if (KeyNum == 5)    //判断按键是否按下
		{
			OLED_CLS();
			for(i=23;i<27;i++) 
		{
			OLED_ShowCN(-368+i*16,1,i);//显示光照阈值
		}
		
			lightva = lightva+25;     //光照阈值+25
			sprintf((char *)Lightvalue,"%d",lightva);  //将光照阈值写入数组
			OLED_ShowStr(45,5,(u8 *)Lightvalue, 2);    //显示光照数组
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
			
				lightva = lightva-25;//光照阈值-25
					if(lightva<0)    //判断阈值是否小于零
				{
					lightva = 0;
				}
				sprintf((char *)Lightvalue,"%d",lightva);  //将光照阈值写入数组
				OLED_ShowStr(45,5,(u8 *)Lightvalue, 2);		 //显示光照数组
				DelayMs(600);
			KeyNum = 0;			//标记位清零
		
    }	
	
	
		if(Light_Intensity()<=lightva) //判断光照强度是否小于阈值
		{
			if(flag == 1) //判断窗帘是否已经打开
			{
				OLED_CLS();
		
		for(i=18;i<23;i++)
		{
			
			OLED_ShowCN(-268+i*16,4,i);//显示  窗帘闭合中
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
				
				motor_cw();
			}
			flag = 1;
		
		}
			


		/*UI界面函数*/
		OLED_CLS();
		printf("光强：%f lx\r\n",Light_Intensity());
		sprintf((char *)LightIntensity,"%1.2f",Light_Intensity());
	  
			for(i=10;i<12;i++)
		{
			OLED_ShowCN(-160+i*16,1,i);//显示光强
		}
		OLED_ShowStr(45,1,(u8 *)LightIntensity, 2); //显示光强字符串
		OLED_ShowStr(86,1,"lx", 2);//显示光强单位
  //	SysTicks_Delay_ms(2000);
		
		
			/*温度显示*/
			for(i=6;i<8;i++)
		{
			OLED_ShowCN(-96+i*16,4,i);//温度显示
		}
		OLED_ShowStr(45,4,(u8 *)TemStr, 2);//显示温度字符串
	
		OLED_ShowCN(86,4,12);//°C显示单位
	
		
		/*湿度显示*/
			for(i=8;i<10;i++)
		{
			OLED_ShowCN(-128+i*16,6,i);//湿度显示
		}
		OLED_ShowStr(45,6,(u8 *)HumStr, 2); //显示湿度字符串
	  OLED_ShowStr(86,6,"%", 2);//显示%单位
		printf("温度：%.2f   湿度： %.2f\n",temperature,humidity);
		DelayS(1);//延时秒
	
		
		
		
		
		
		
		}


		
	