#ifndef __BSP_BH1750_H
#define __BSP_BH1750_H
#include "stm32f10x.h"

//SCL GPIO初始化
#define BH1750_SCL_PIN			GPIO_Pin_8
#define BH1750_SCL_PORT     GPIOB
#define BH1750_SCL_RCC      RCC_APB2Periph_GPIOB


//SDA GPIO初始化
#define BH1750_SDA_PIN      GPIO_Pin_9
#define BH1750_SDA_PORT 	  GPIOB
#define BH1750_SDA_RCC      RCC_APB2Periph_GPIOB

#define SCL_HIGH            GPIO_SetBits(BH1750_SCL_PORT,BH1750_SCL_PIN)
#define SCL_LOW             GPIO_ResetBits (BH1750_SCL_PORT,BH1750_SCL_PIN)

#define SDA_HIGH            GPIO_SetBits(BH1750_SDA_PORT,BH1750_SDA_PIN)
#define SDA_LOW             GPIO_ResetBits (BH1750_SDA_PORT,BH1750_SDA_PIN)


//BH1750写地址 01000110
#define BH1750_Addr				0x46

//BH1750读地址 01000111
#define BH1750_ReadAddr		0x47			

//BH1750指令码
#define POWER_OFF					0x00
#define POWER_ON					0x01
#define MODULE_RESET			0x07
#define	CONTINUE_H_MODE		0x10
#define CONTINUE_H_MODE2	0x11
#define CONTINUE_L_MODE		0x13
#define ONE_TIME_H_MODE		0x20
#define ONE_TIME_H_MODE2	0x21
#define ONE_TIME_L_MODE		0x23

void BH1750_Init(void);
void Single_Write_BH1750(unsigned char REG_Address);
void delay_us(uint16_t us);
void BH1750_Set_Mode(void);
void BH1750_RESET(void);
void BH1750_POWERON(void);
void BH1750_POWEROFF(void);
void BH1750_GPIO_Config(void);

void BH1750_Start(void);
void BH1750_Stop(void);
void BH1750_SendACK(int ack);
uint8_t BH1750_RecvACK(void);
uint8_t BH1750_SendByte(unsigned char dat);
unsigned char BH1750_RecvByte(void);
void Litght_Read(void);
uint16_t BH1750_Read_Measure(void);
float Light_Intensity(void);
#endif  /* __BSP_BH1750_H*/

