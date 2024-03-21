#ifndef __BSP_MOTOR_H
#define __BSP_MOTOR_H
#include "stm32f10x.h"

#define Motor_One_Pin      GPIO_Pin_4
#define Motor_One_Port    GPIOA
#define Motor_One_Clk   	RCC_APB2Periph_GPIOA

#define Motor_Two_Pin    GPIO_Pin_5
#define Motor_Two_Port    GPIOA
#define Motor_Two_Clk    	RCC_APB2Periph_GPIOA

#define Motor_Three_Pin     GPIO_Pin_6
#define Motor_Three_Port   GPIOA
#define Motor_Three_Clk   	RCC_APB2Periph_GPIOA

#define Motor_Four_Pin    GPIO_Pin_7
#define Motor_Four_Port   GPIOA
#define Motor_Four_Clk   	RCC_APB2Periph_GPIOA

#define Motor_One_ON       GPIO_SetBits(Motor_One_Port,Motor_One_Pin) 
#define Motor_Two_ON       GPIO_SetBits(Motor_Two_Port,Motor_Two_Pin) 
#define Motor_Three_ON     GPIO_SetBits(Motor_Three_Port,Motor_Three_Pin) 
#define Motor_Four_ON      GPIO_SetBits(Motor_Four_Port,Motor_Four_Pin) 

#define Motor_One_OFF       GPIO_ResetBits(Motor_One_Port,Motor_One_Pin) 
#define Motor_Two_OFF       GPIO_ResetBits(Motor_Two_Port,Motor_Two_Pin) 
#define Motor_Three_OFF     GPIO_ResetBits(Motor_Three_Port,Motor_Three_Pin) 
#define Motor_Four_OFF      GPIO_ResetBits(Motor_Four_Port,Motor_Four_Pin) 

void Motor_GPIO_Config(void);
void motor_cw(void);
void Delay(unsigned int i);//—” ±
void motor_cw2(void);
void motor_cw3(void);
void motor_ccw(void);

#endif /* __BSP_MOTOR_H*/


