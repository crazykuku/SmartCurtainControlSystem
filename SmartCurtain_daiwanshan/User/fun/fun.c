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

int lightva = 100;  //��ʼ��������ֵ
extern float Light; //����ǿ��
float temp;
uint8_t BUF[8];
uint32_t dis_data;
uint32_t Value_GY_30;
uint8_t flag =0;   

char oledBuf[20];

extern uint8_t KeyNum;  //�������λ
extern u8 humidityH;	  //ʪ����������
extern u8 humidityL;	  //ʪ��С������
extern u8 temperatureH;   //�¶���������
extern u8 temperatureL;   //�¶�С������ 
extern unsigned char i;
extern u8 Led_Status;
extern u8 alarmFlag;
extern char PUB_BUF[256];




//extern char Lightvalue[10];


/*�ֶ�ģʽ*/
void Manual(void)
{
	
	/********** ��ʪ�ȴ�������ȡ����**************/
			DHT11_Read_Data(&humidityH,&humidityL,&temperatureH,&temperatureL);
			
			/********** ���նȴ�������ȡ����**************/
			if (!i2c_CheckDevice(BH1750_Addr))
			{
				Light = LIght_Intensity();
			}
			
			/********** ��ȡLED0��״̬ **************/
			Led_Status = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13);
	
		if (KeyNum == 3)  //�������3����
		{
			OLED_CLS();//����
			beeperOnce();								//����������
			OLED_ShowStr(40,4,"OPEN", 2);//��ʾOPEN
			motor_ccw();   //���չ��
			KeyNum = 0;    //�������
			
    }	
	else if (KeyNum == 4)  //�������4����
		{
			OLED_CLS();										//����
			beeperOnce();									//����������
			OLED_ShowStr(40,4,"CLOSE", 2);//��ʾCLOSE
			motor_cw();										//����պ�
			KeyNum = 0;										//�������
		
    }

//	else if (KeyNum == 7)		//��������
//		{
//			OLED_CLS();									 //����
//			beeperOnce();								 //����������
//			OLED_ShowStr(40,4,"OPEN", 2);//��ʾOPEN
//			motor_ccw();  							 //���չ��
//			KeyNum = 0;									 //�������

//    }	
//		else if (KeyNum == 8)		//��������
//		{
//			OLED_CLS();									 //����
//			beeperOnce();								 //����������
//			OLED_ShowStr(40,4,"CLOSE", 2);//��ʾCLOSE
//			motor_cw();										//����պ�
//			KeyNum = 0;										//�������
//		
//    }	
		
			DEBUG_LOG("lightva = %d\n",lightva);
			/********** ���������Ϣ **************/
			DEBUG_LOG(" | ʪ�ȣ�%d.%d C | �¶ȣ�%d.%d %% | ���նȣ�%.1f lx | ָʾ�ƣ�%s | ��������%s | ",humidityH,humidityL,temperatureH,temperatureL,Light,Led_Status?"�ر�":"��������",alarmFlag?"��������":"ֹͣ");
			

		
		/*UI���溯��*/
				sprintf(oledBuf,"Welcome");
				OLED_ShowStr(32,0,(u8*)oledBuf,2);//8*16 ��ABC��
				sprintf(oledBuf,"Hum:%d.%d %%",humidityH,humidityL);
				OLED_ShowStr(0,2,(u8*)oledBuf,2);//8*16 ��ABC��
				sprintf(oledBuf,"Temp:%d.%d C",temperatureH,temperatureL);
				OLED_ShowStr(0,4,(u8*)oledBuf,2);//8*16 ��ABC��
				sprintf(oledBuf,"Light:%.1f Lx",Light);
				OLED_ShowStr(0,6,(u8*)oledBuf,2);//8*16 ��ABC��
		DelayS(2);
}

/*�Զ�ģʽ*/
void automatic(void)
{
		char lightvalue[10];
	  SysTicks_Delay_ms(2000);   //�ӳ�����
		OLED_CLS();
		
	
	/********** ��ʪ�ȴ�������ȡ����**************/
			DHT11_Read_Data(&humidityH,&humidityL,&temperatureH,&temperatureL);
			
			/********** ���նȴ�������ȡ����**************/
			if (!i2c_CheckDevice(BH1750_Addr))
			{
				Light = LIght_Intensity();
			}
			
			/********** ��ȡLED0��״̬ **************/
			Led_Status = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13);
			
	
		if (KeyNum == 5)    //�жϰ����Ƿ���
		{
			OLED_CLS();
			for(i=23;i<27;i++) 
		{
			OLED_ShowCN(-368+i*16,1,i);//��ʾ������ֵ
		}
		
			lightva = lightva+20;     //������ֵ+25
			sprintf((char *)lightvalue,"%d",lightva);  //��������ֵд������
			OLED_ShowStr(45,5,(u8 *)lightvalue, 2);    //��ʾ��������
		  DelayMs(600);
			KeyNum = 0;									//���λ����
		
    }	
	if (KeyNum == 6)   //��ⰴ���Ƿ���
		{
			 OLED_CLS();
				for(i=23;i<27;i++)
				{
					OLED_ShowCN(-368+i*16,1,i);//��ʾ������ֵ
				}
			
				lightva = lightva-20;//������ֵ-25
					if(lightva<0)    //�ж���ֵ�Ƿ�С����
				{
					lightva = 0;
				}
				sprintf((char *)lightvalue,"%d",lightva);  //��������ֵд������
				OLED_ShowStr(45,5,(u8 *)lightvalue, 2);		 //��ʾ��������
				DelayMs(600);
			KeyNum = 0;			//���λ����
		
    }	

		if(Light<=lightva) //�жϹ���ǿ���Ƿ�С����ֵ
		{

				
			if(flag == 1) //�жϴ����Ƿ��Ѿ���
			{
				OLED_CLS();
		
				for(i=18;i<23;i++)
				{
					
					OLED_ShowCN(-268+i*16,4,i);//��ʾ  �����պ���
				}
				for(int i = 0;i < 10;i++)
				{
					beeperOnce();beeperOnce();DelayMs(100);
				}
				motor_ccw();
			}
			flag = 0; 
		}
		
		else //��֮�򿪴���
		{

			if(flag == 0)  //�жϴ����Ƿ��Ѿ��պ�
			{
				OLED_CLS();
				for(i=13;i<18;i++)
				{
					OLED_ShowCN(-180+i*16,4,i);//��ʾ ����չ����
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
			/********** ���������Ϣ **************/
			DEBUG_LOG(" | ʪ�ȣ�%d.%d C | �¶ȣ�%d.%d %% | ���նȣ�%.1f lx | ָʾ�ƣ�%s | ��������%s | ",humidityH,humidityL,temperatureH,temperatureL,Light,Led_Status?"�ر�":"��������",alarmFlag?"��������":"ֹͣ");

		

//		/*UI���溯��*/
				sprintf(oledBuf,"Welcome");
				OLED_ShowStr(32,0,(u8*)oledBuf,2);//8*16 ��ABC��
				sprintf(oledBuf,"Hum:%d.%d %%",humidityH,humidityL);
				OLED_ShowStr(0,2,(u8*)oledBuf,2);//8*16 ��ABC��
				sprintf(oledBuf,"Temp:%d.%d C",temperatureH,temperatureL);
				OLED_ShowStr(0,4,(u8*)oledBuf,2);//8*16 ��ABC��
				sprintf(oledBuf,"Light:%.1f Lx",Light);
				OLED_ShowStr(0,6,(u8*)oledBuf,2);//8*16 ��ABC��
		DelayS(1);//��ʱ��
//	
		
		
		
		
		
		
}
