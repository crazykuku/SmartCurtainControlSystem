#include "bsp_motor.h" 
#include "bsp_Systick.h"
#include "delay.h"
//**********************正向旋转相序表*****************************
unsigned char FFW[8]={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};

//**********************反向旋转相序表***************************** 

unsigned char REV[8]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};


void Motor_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitSTruct;
	RCC_APB2PeriphClockCmd(Motor_One_Clk,ENABLE);		  
	GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSTruct.GPIO_Pin = Motor_One_Pin|Motor_Two_Pin|Motor_Three_Pin|Motor_Four_Pin;
	GPIO_InitSTruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(Motor_One_Port,&GPIO_InitSTruct);
	GPIO_Init(Motor_Two_Port,&GPIO_InitSTruct);
	GPIO_Init(Motor_Three_Port,&GPIO_InitSTruct);
	GPIO_Init(Motor_Four_Port,&GPIO_InitSTruct);
}




void motor_cw2(void)
{
  uint32_t i=0;

		for(i=0;i<8;i++)
			{
					switch(i)
					{
						case 0:
						Motor_One_ON;Motor_Two_OFF;Motor_Three_OFF;Motor_Four_OFF;	DelayUs(2); 
						break;
						case 1:
						Motor_One_ON;Motor_Two_ON;Motor_Three_OFF;Motor_Four_OFF;	DelayUs(2); 
						break;
						case 2:
						Motor_One_OFF;Motor_Two_ON;Motor_Three_OFF;Motor_Four_OFF;	DelayUs(2); 
						break;
						case 3:
						Motor_One_OFF;Motor_Two_ON;Motor_Three_ON;Motor_Four_OFF;	DelayUs(2); 
						break;
						case 4:
						Motor_One_OFF;Motor_Two_OFF;Motor_Three_ON;Motor_Four_OFF;	DelayUs(2); 
						break;
						case 5:
						Motor_One_OFF;Motor_Two_OFF;Motor_Three_ON;Motor_Four_ON;	DelayUs(2); 
						break;
						case 6:
						Motor_One_OFF;Motor_Two_OFF;Motor_Three_OFF;Motor_Four_ON;	DelayUs(2); 
						break;
						case 7:
						Motor_One_OFF;Motor_Two_OFF;Motor_Three_OFF;Motor_Four_OFF;	DelayUs(2);  
						break;
						
					}
				}
}
	
 void motor_cw(void)
{
  uint32_t i,j;
	for(j=0;j<64;j++)
	{	
		for(i=0;i<8;i++) //电机内部转一周 外部5.625
			{
					
						Motor_One_ON;Motor_Two_OFF;Motor_Three_OFF;Motor_Four_OFF;	DelayUs(1500);
				
						Motor_One_ON;Motor_Two_ON;Motor_Three_OFF;Motor_Four_OFF;	DelayUs(1500);
			
						Motor_One_OFF;Motor_Two_ON;Motor_Three_OFF;Motor_Four_OFF;	DelayUs(1500);
					
						Motor_One_OFF;Motor_Two_ON;Motor_Three_ON;Motor_Four_OFF;DelayUs(1500);
				
						Motor_One_OFF;Motor_Two_OFF;Motor_Three_ON;Motor_Four_OFF;	DelayUs(1500);
				
						Motor_One_OFF;Motor_Two_OFF;Motor_Three_ON;Motor_Four_ON;	DelayUs(1500);
		
						Motor_One_OFF;Motor_Two_OFF;Motor_Three_OFF;Motor_Four_ON;DelayUs(1500);
					
						Motor_One_OFF;Motor_Two_OFF;Motor_Three_OFF;Motor_Four_OFF;DelayUs(1500);

			}
		}
}

 void motor_ccw(void)
{
  uint32_t i,j;
	for(j=0;j<64;j++)
	{	
		for(i=0;i<8;i++) //电机内部转一周 外部5.625
			{
				
				
					Motor_One_OFF;Motor_Two_OFF;Motor_Three_OFF;Motor_Four_ON;DelayUs(1500);
				
					Motor_One_OFF;Motor_Two_OFF;Motor_Three_ON;Motor_Four_ON;	DelayUs(1500);
				
					Motor_One_OFF;Motor_Two_OFF;Motor_Three_ON;Motor_Four_OFF;	DelayUs(1500);
				
					Motor_One_OFF;Motor_Two_ON;Motor_Three_ON;Motor_Four_OFF;DelayUs(1500);
				
					Motor_One_OFF;Motor_Two_ON;Motor_Three_OFF;Motor_Four_OFF;	DelayUs(1500);
				
					Motor_One_ON;Motor_Two_ON;Motor_Three_OFF;Motor_Four_OFF;	DelayUs(1500);
				
					Motor_One_ON;Motor_Two_OFF;Motor_Three_OFF;Motor_Four_OFF;	DelayUs(1500);

					Motor_One_OFF;Motor_Two_OFF;Motor_Three_OFF;Motor_Four_OFF;DelayUs(1500);
	
						
			}
		}
}


//void motor_cw3(void)
//{
//						Motor_One_ON;Motor_Two_OFF;Motor_Three_OFF;Motor_Four_OFF;	Delay(12000); 
//				
//						Motor_One_ON;Motor_Two_ON;Motor_Three_OFF;Motor_Four_OFF;	Delay(12000); 
//			
//						Motor_One_OFF;Motor_Two_ON;Motor_Three_OFF;Motor_Four_OFF;	Delay(12000); 
//					
//						Motor_One_OFF;Motor_Two_ON;Motor_Three_ON;Motor_Four_OFF;	Delay(12000); 
//				
//						Motor_One_OFF;Motor_Two_OFF;Motor_Three_ON;Motor_Four_OFF;	Delay(12000); 
//				
//						Motor_One_OFF;Motor_Two_OFF;Motor_Three_ON;Motor_Four_ON;	Delay(12000); 
//		
//						Motor_One_OFF;Motor_Two_OFF;Motor_Three_OFF;Motor_Four_ON;	Delay(12000); 
//					
//						Motor_One_OFF;Motor_Two_OFF;Motor_Three_OFF;Motor_Four_OFF;	Delay(12000);  
//}


