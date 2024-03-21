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
    BH1750_Start();                  //起始信号
    BH1750_SendByte(BH1750_Addr);   //发送设备地址+写信号
    BH1750_SendByte(REG_Address);    //内部寄存器地址
    BH1750_Stop();                   //发送停止信号
}


//BH1750复位
void BH1750_RESET(void)
{
	BH1750_SendByte(MODULE_RESET);
}

void BH1750_POWERON(void)
{
	BH1750_SendByte(POWER_ON);
}

//BH1750断电
void BH1750_POWEROFF(void)
{
	BH1750_SendByte(POWER_OFF);
}

//设置BH1750的模式  成功返回0
void BH1750_Set_Mode(void)
{
	BH1750_SendByte(CONTINUE_H_MODE);
}





//BH1750起始信号
void BH1750_Start(void)
{
    SDA_HIGH;                    //拉高数据线
    SCL_HIGH;                    //拉高时钟线
    delay_us(5);        //延时
    SDA_LOW ;                    //产生下降沿
    delay_us(5);        //延时
    SCL_LOW;                     //拉低时钟线   
}



//BH1750停止信号
void BH1750_Stop(void)
{
    SDA_LOW;                   //拉低数据线
    SCL_HIGH;                  //拉高时钟线
    delay_us(5);      //延时
    SDA_HIGH;                 //产生上升沿
    delay_us(5);      //延时
}


//BH1750发送应答信号  发送1为应答  发送0为非应答
void BH1750_SendACK(int ack)
{
	//重新初始GPIO
	GPIO_InitTypeDef GPIO_InitSTruct;
	
  GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSTruct.GPIO_Pin = BH1750_SDA_PIN|BH1750_SCL_PIN;
	GPIO_InitSTruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(BH1750_SDA_PORT,&GPIO_InitSTruct);
	
    if(ack == 1)   //写应答信号
			SDA_LOW;    //如果应答指令为1  拉低SDA线
		else if(ack == 0)
			SDA_HIGH;     //如果应答指令为0   拉高SDA线
		else
			return;
			
    SCL_HIGH;      //拉高时钟线
    delay_us(5);               //延时
    SCL_LOW;		  //拉低时钟线
    delay_us(5);                //延时
}


//BH1750接收应答信号  返回1为应答  返回0为非应答
uint8_t BH1750_RecvACK(void)
{
	  uint8_t mcy=0;
	  GPIO_InitTypeDef GPIO_InitSTruct;
	
	  GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_IPD;  //这里一定要设成输入上拉，否则不能读出数据
    GPIO_InitSTruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitSTruct.GPIO_Pin = BH1750_SDA_PIN|BH1750_SCL_PIN;
   	GPIO_Init(BH1750_SDA_PORT,&GPIO_InitSTruct);
	
    SCL_HIGH;                    //拉高时钟线
    delay_us(5);        //延时
	
	  if(GPIO_ReadInputDataBit ( BH1750_SDA_PORT, BH1750_SDA_PIN ) == 0 )//读应答信号
        mcy = 1 ;  
    else
        mcy = 0 ;			
	
    SCL_LOW ;                    //拉低时钟线
    delay_us(5);                 //延时
  
   GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(BH1750_SDA_PORT,&GPIO_InitSTruct);
	
    return mcy;
}


//BH1750向IIC总线发送一个字节
uint8_t BH1750_SendByte(unsigned char dat)
{
    uint8_t i;
    for (i=0; i<8; i++)         //8位计数器
      {
				//通过与运算判断 如果为1则拉高SDA线  如果为0则拉低SDA线
				if( 0X80 & dat )
				{
					SDA_HIGH;
				}
        else
				{
					SDA_LOW;
				}
				
        dat <<= 1; 							  //dat左移 为下一位腾出空间
        SCL_HIGH;                         //拉高时钟线
        delay_us(5);             //延时
        SCL_LOW;               					  //拉低时钟线  				
				delay_us(5);				
      }
		return BH1750_RecvACK();
}


//从IIC总线读取一个字节
unsigned char BH1750_RecvByte(void)
{
    uint16_t i;
    unsigned char data = 0;
		unsigned char bit;
	  
	 GPIO_InitTypeDef GPIO_InitSTruct;
	
	 GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_IPU;  //这里一定要设成输入上拉，否则不能读出数据
   GPIO_InitSTruct.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitSTruct.GPIO_Pin = BH1750_SDA_PIN;
   GPIO_Init(BH1750_SDA_PORT,&GPIO_InitSTruct);
	
   SDA_HIGH ;          //使能内部上拉,准备读取数据,
    for (i=0; i<8; i++)         //8位计数器
    {
        data <<= 1;
        SCL_HIGH;               //拉高时钟线
        delay_us(5);             //延时
	
			  if( SET == GPIO_ReadInputDataBit ( BH1750_SDA_PORT, BH1750_SDA_PIN ) )
             bit = 0X01;
       else
             bit = 0x00;  
			
        data |= bit;             //读数据    
			
        SCL_LOW;                //拉低时钟线
        delay_us(5);           //延时
    }
		
	 GPIO_InitSTruct.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(BH1750_SDA_PORT,&GPIO_InitSTruct);
	
    return data;
}


void Litght_Read(void)
{   
	  uint8_t i;	
    BH1750_Start();                          //起始信号
    BH1750_SendByte(BH1750_ReadAddr);        //发送设备地址+读信号
	
	 for (i=0; i<3; i++)                      //连续读取6个地址数据，存储中BUF
    {
        BUF[i] = BH1750_RecvByte();          //BUF[0]存储0x32地址中的数据
        if (i == 3)
        {
           BH1750_SendACK(0);                //最后一个数据需要回NOACK
        }
        else
        {		
          BH1750_SendACK(1);                //回应ACK
        }
   }
 
    BH1750_Stop();                          //停止信号
    delay_us(5);
}


uint16_t BH1750_Read_Measure(void)
{
	uint16_t receive_data = 0;
	
	BH1750_Start();
	//读地址
	BH1750_SendByte(BH1750_ReadAddr);
	
	//读高八位
	receive_data = BH1750_RecvByte();
	BH1750_SendACK(1);
	//读低八位
	receive_data = (receive_data<<8)+BH1750_RecvByte();
	BH1750_SendACK(0);
	BH1750_Stop(); 
	return receive_data;
}

float Light_Intensity(void)
{
	return (float)(BH1750_Read_Measure()/1.2f);
}

