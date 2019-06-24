/**
  ******************************************************************************
  * @file    sht20.c
  * @author  ThreeWater
  * @version V1.0.0
  * @date    17-June-2019
  * @brief  This article will be used for  driving sht20.
  * @License:none         
  ******************************************************************************
  * @attention
  *	The frequency of crystal oscillator is 12 Mhz.
  * using OLED_IIC_Setup() to initialize.
  * 
  * 
  *
  * 
  ******************************************************************************
	**/

#include "sht20.h"

 unsigned char sndata1[8];
 unsigned char sndata2[6];
 unsigned int SN1; 
 unsigned int SN2; 



 /**
  * @file   I2C_delay
  * @brief  延迟时间
  * @param  无
  * @retval 无
  */
void I2C_delay(void)
{	
   unsigned int i=6; /* 这里可以优化速度,经测试最低到5还能写入 */
   while(i--);
}

 /**
  * @file   I2C_Start
  * @brief  起始信号
  * @param  无
  * @retval 无
  */
FunctionalState I2C_Start(void)
{
	SDA_H;
	SCL_H;
	I2C_delay();
	if(!SDA_read)return DISABLE;	/* SDA线为低电平则总线忙,退出 */
        SDA_L;
	I2C_delay();
       
	if(SDA_read) return DISABLE;	/* SDA线为高电平则总线出错,退出 */
	SDA_L;
	I2C_delay();
	return ENABLE;
}

 /**
  * @file   I2C_Stop
  * @brief  停止信号
  * @param  无
  * @retval 无
  */
void I2C_Stop(void)
{
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SDA_H;
	I2C_delay();
}

 /**
  * @file   I2C_Ack
  * @brief  应答信号
  * @param  无
  * @retval 无
  */
void I2C_Ack(void)
{	
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}

 /**
  * @file   I2C_NoAck
  * @brief  无应答信号
  * @param  无
  * @retval 无
  */
void I2C_NoAck(void)
{	
	SCL_L;
	I2C_delay();
	SDA_H;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}

 /**
  * @file   I2C_WaitAck
  * @brief  等待Ack
  * @param  无
  * @retval 返回为:=1有ACK,=0无ACK
  */
FunctionalState I2C_WaitAck(void) 	
{
	SCL_L;
	I2C_delay();
	SDA_H;			
	I2C_delay();
	SCL_H;
	I2C_delay();
	if(SDA_read)
	{
           SCL_L;
          return DISABLE;
	}
	SCL_L;
	return ENABLE;
}

 /**
  * @file   I2C_SendByte
  * @brief  数据从高位到低位
  * @param  - SendByte: 发送的数据
  * @retval 无
  */
void I2C_SendByte(unsigned char SendByte) 
{
    unsigned char i=8;
    while(i--)
    {
	SCL_L;
	I2C_delay();
	if(SendByte&0x80)
	SDA_H;  
	else 
	SDA_L;   
	SendByte<<=1;
	I2C_delay();
	SCL_H;
	I2C_delay();
    }
    SCL_L;
}


 /**
  * @file   I2C_ReceiveByte
  * @brief  数据从高位到低位
  * @param  无
  * @retval I2C总线返回的数据
  */
unsigned char I2C_ReceiveByte(void)  
{ 
    unsigned char i=8;
    unsigned char ReceiveByte=0;
    SDA_H;				
    while(i--)
    {
      ReceiveByte<<=1;      
      SCL_L;
      I2C_delay();
	    SCL_H;
      I2C_delay();	
      if(SDA_read)
      {
        ReceiveByte|=0x01;
      }
    }
    SCL_L;
    return ReceiveByte;
} 



 /**
  * @file   Delay_us(不精确)
  * @brief  微妙延时 time_ms ms
  * @param  time_us 延时时间
  * @retval NO
  */
static void delay_us( unsigned short int time_us )
{
  unsigned short int i,j;
  for( i=0;i<time_us;i++ )
  {
	for(j=0;j<4;j++);
  }
}
 /**
  * @file   Delay_Ms(不精确)
  * @brief  毫秒延时 time_ms ms
  * @param  time_ms 延时时间
  * @retval NO
  */
static void delay_ms(unsigned short int time_ms)
{
	 unsigned short int i;
  for( i=0;i<time_ms;i++ )
  {
		delay_us(11000);
  }
	
}


 /**
  * @file   SHT2x_Calc_T
  * @brief  计算温度
  * @param  NO
  * @retval 返回温度值
  */
float SHT2x_Calc_T(void)
{
	float temperatureC;
  //  unsigned char timeout=30;
    unsigned char length=0;
    unsigned char Tdata[3]={0};
    I2C_Start();
    I2C_SendByte(I2C_ADR_W); 
    I2C_WaitAck();
    I2C_SendByte(TRIG_T_MEASUREMENT_POLL);      
    I2C_WaitAck();
    delay_us(20);
    I2C_Stop();
    do
    {
	I2C_Start();
        I2C_SendByte(I2C_ADR_R);
  //      timeout--;
    }
    while(!I2C_WaitAck());
    for(length=0;length<=3;length++)
    {
	Tdata[length]=I2C_ReceiveByte();
	I2C_Ack(); 		
    };
    I2C_NoAck();		
    I2C_Stop();		
    temperatureC= (-46.85 + (175.72/65536 )*((float)((((unsigned short int)Tdata[0]<<8)+(unsigned short int)Tdata[1])&0xfffc)));
    return temperatureC;
}


 /**
  * @file   SHT2x_Calc_RH
  * @brief  计算湿度
  * @param  NO
  * @retval 返回湿度值
  */
float SHT2x_Calc_RH(void)
{
	float humidityRH;
  //unsigned char timeout=30;
   unsigned char length=0;
   unsigned char RHdata[3]={0};
   I2C_Start();
   I2C_SendByte(I2C_ADR_W); 
   I2C_WaitAck();
   I2C_SendByte(TRIG_RH_MEASUREMENT_POLL);      
   I2C_WaitAck();
   delay_us(20);
   I2C_Stop();
    do
    {
    I2C_Start();
    I2C_SendByte(I2C_ADR_R);
   // timeout--;
    }
    while(!I2C_WaitAck());
    for(length=0;length<=3;length++)
    {
	RHdata[length]=I2C_ReceiveByte();
	I2C_Ack(); 		
    };
    I2C_NoAck();		
    I2C_Stop();	
    humidityRH = -6.0 + 125.0/65536 * ((float)((((unsigned short int)RHdata[0]<<8)+(unsigned short int)RHdata[1])&0xfff0)); 
    return humidityRH;
}
 /**
  * @file   SHT2x_SoftReset
  * @brief  软件复位
  * @param  NO
  * @retval NO
  */
FunctionalState SHT2x_SoftReset(void)
{
    if(!I2C_Start())return DISABLE;
    I2C_SendByte(0x80); 
    if(!I2C_WaitAck()){I2C_Stop(); return DISABLE;}
    I2C_SendByte(SOFT_RESET);       
    I2C_WaitAck();	  
    I2C_Stop(); 
    delay_ms(1500);
    return ENABLE;	
}



