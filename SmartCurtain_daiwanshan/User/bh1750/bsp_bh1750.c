#include "bsp_bh1750.h"
#include "bsp_systick.h"
#include  "usart.h"
extern uint8_t BUF[8];
void BH1750_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitSTruct;
	
	RCC_APB2PeriphClockCmd(BH1750_SDA_RCC,ENABLE);
	GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSTruct.GPIO_Pin = BH1750_SDA_PIN|BH1750_SCL_PIN;
	GPIO_InitSTruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(BH1750_SDA_PORT,&GPIO_InitSTruct);

}



void delay_us(uint16_t us)
{
	while(us--)
	{
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();
	}
}

void Single_Write_BH1750(unsigned char REG_Address)
{
    BH1750_Start();                  //��ʼ�ź�
    BH1750_SendByte(BH1750_Addr);   //�����豸��ַ+д�ź�
    BH1750_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ
    BH1750_Stop();                   //����ֹͣ�ź�
}


//BH1750��λ
void BH1750_RESET(void)
{
	BH1750_SendByte(MODULE_RESET);
}

void BH1750_POWERON(void)
{
	BH1750_SendByte(POWER_ON);
}

//BH1750�ϵ�
void BH1750_POWEROFF(void)
{
	BH1750_SendByte(POWER_OFF);
}

//����BH1750��ģʽ  �ɹ�����0
void BH1750_Set_Mode(void)
{
	BH1750_SendByte(CONTINUE_H_MODE);
}





//BH1750��ʼ�ź�
void BH1750_Start(void)
{
    SDA_HIGH;                    //����������
    SCL_HIGH;                    //����ʱ����
    delay_us(5);        //��ʱ
    SDA_LOW ;                    //�����½���
    delay_us(5);        //��ʱ
    SCL_LOW;                     //����ʱ����   
}



//BH1750ֹͣ�ź�
void BH1750_Stop(void)
{
    SDA_LOW;                   //����������
    SCL_HIGH;                  //����ʱ����
    delay_us(5);      //��ʱ
    SDA_HIGH;                 //����������
    delay_us(5);      //��ʱ
}


//BH1750����Ӧ���ź�  ����1ΪӦ��  ����0Ϊ��Ӧ��
void BH1750_SendACK(int ack)
{
	//���³�ʼGPIO
	GPIO_InitTypeDef GPIO_InitSTruct;
	
  GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSTruct.GPIO_Pin = BH1750_SDA_PIN|BH1750_SCL_PIN;
	GPIO_InitSTruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(BH1750_SDA_PORT,&GPIO_InitSTruct);
	
    if(ack == 1)   //дӦ���ź�
			SDA_LOW;    //���Ӧ��ָ��Ϊ1  ����SDA��
		else if(ack == 0)
			SDA_HIGH;     //���Ӧ��ָ��Ϊ0   ����SDA��
		else
			return;
			
    SCL_HIGH;      //����ʱ����
    delay_us(5);               //��ʱ
    SCL_LOW;		  //����ʱ����
    delay_us(5);                //��ʱ
}


//BH1750����Ӧ���ź�  ����1ΪӦ��  ����0Ϊ��Ӧ��
uint8_t BH1750_RecvACK(void)
{
	  uint8_t mcy=0;
	  GPIO_InitTypeDef GPIO_InitSTruct;
	
	  GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_IPD;  //����һ��Ҫ������������������ܶ�������
    GPIO_InitSTruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitSTruct.GPIO_Pin = BH1750_SDA_PIN|BH1750_SCL_PIN;
   	GPIO_Init(BH1750_SDA_PORT,&GPIO_InitSTruct);
	
    SCL_HIGH;                    //����ʱ����
    delay_us(5);        //��ʱ
	
	  if(GPIO_ReadInputDataBit ( BH1750_SDA_PORT, BH1750_SDA_PIN ) == 0 )//��Ӧ���ź�
        mcy = 1 ;  
    else
        mcy = 0 ;			
	
    SCL_LOW ;                    //����ʱ����
    delay_us(5);                 //��ʱ
  
   GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(BH1750_SDA_PORT,&GPIO_InitSTruct);
	
    return mcy;
}


//BH1750��IIC���߷���һ���ֽ�
uint8_t BH1750_SendByte(unsigned char dat)
{
    uint8_t i;
    for (i=0; i<8; i++)         //8λ������
      {
				//ͨ���������ж� ���Ϊ1������SDA��  ���Ϊ0������SDA��
				if( 0X80 & dat )
				{
					SDA_HIGH;
				}
        else
				{
					SDA_LOW;
				}
				
        dat <<= 1; 							  //dat���� Ϊ��һλ�ڳ��ռ�
        SCL_HIGH;                         //����ʱ����
        delay_us(5);             //��ʱ
        SCL_LOW;               					  //����ʱ����  				
				delay_us(5);				
      }
		return BH1750_RecvACK();
}


//��IIC���߶�ȡһ���ֽ�
unsigned char BH1750_RecvByte(void)
{
    uint16_t i;
    unsigned char data = 0;
		unsigned char bit;
	  
	 GPIO_InitTypeDef GPIO_InitSTruct;
	
	 GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_IPU;  //����һ��Ҫ������������������ܶ�������
   GPIO_InitSTruct.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitSTruct.GPIO_Pin = BH1750_SDA_PIN;
   GPIO_Init(BH1750_SDA_PORT,&GPIO_InitSTruct);
	
   SDA_HIGH ;          //ʹ���ڲ�����,׼����ȡ����,
    for (i=0; i<8; i++)         //8λ������
    {
        data <<= 1;
        SCL_HIGH;               //����ʱ����
        delay_us(5);             //��ʱ
	
			  if( SET == GPIO_ReadInputDataBit ( BH1750_SDA_PORT, BH1750_SDA_PIN ) )
             bit = 0X01;
       else
             bit = 0x00;  
			
        data |= bit;             //������    
			
        SCL_LOW;                //����ʱ����
        delay_us(5);           //��ʱ
    }
		
	 GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(BH1750_SDA_PORT,&GPIO_InitSTruct);
	
    return data;
}


void Litght_Read(void)
{   
	  uint8_t i;	
    BH1750_Start();                          //��ʼ�ź�
    BH1750_SendByte(BH1750_ReadAddr);        //�����豸��ַ+���ź�
	
	 for (i=0; i<3; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
    {
        BUF[i] = BH1750_RecvByte();          //BUF[0]�洢0x32��ַ�е�����
        if (i == 3)
        {
           BH1750_SendACK(0);                //���һ��������Ҫ��NOACK
        }
        else
        {		
          BH1750_SendACK(1);                //��ӦACK
        }
   }
 
    BH1750_Stop();                          //ֹͣ�ź�
    delay_us(5);
}


uint16_t BH1750_Read_Measure(void)
{
	uint16_t receive_data = 0;
	
	BH1750_Start();
	//����ַ
	BH1750_SendByte(BH1750_ReadAddr);
	
	//���߰�λ
	receive_data = BH1750_RecvByte();
	BH1750_SendACK(1);
	//���Ͱ�λ
	receive_data = (receive_data<<8)+BH1750_RecvByte();
	BH1750_SendACK(0);
	BH1750_Stop(); 
	return receive_data;
}

float Light_Intensity(void)
{
	return (float)(BH1750_Read_Measure()/1.2f);
}

