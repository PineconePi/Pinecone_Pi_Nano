/**
  ******************************************************************************
  * @file    DL_LN33.c
  * @author  ThreeWater
  * @version V1.0.0
  * @date    17-June-2019
  * @brief  This article will be used for  driving  DL-33N.
  * @License:none         
  ******************************************************************************
  * @attention
  *	The frequency of crystal oscillator is 24 Mhz.
  * using Zigbee_Setup() to initialize.
  * Using the UART1 to do it.
  * Possibly with other libraries.
  * Using interrupt4.
  * 
  * 
  *
  * 
  ******************************************************************************
	**/

#include "DL_LN33.h"
static void Usart_Setup();
static void Usart_Send_Byte(unsigned int Data);
static void Zigbee_CMD(unsigned char *CMD,unsigned int len);

static unsigned int Zigbee_Count=0;
//Zigbee_CMD
static unsigned char CMD_Zigbee_Restart=0x10;//Don't change anything
static unsigned char CMD_Zigbee_ChangeIP[]={0x11,0x00,0x01};//change IP here. the last two is IP
static unsigned char CMD_Zigbee_Change_NetID[]={0x12,0x00,0x01};//change NetID here
static unsigned char CMD_Zigbee_Change_Channel[]={0x13,0x13};//Change the Channel here
static unsigned char CMD_Zigbee_Change_BRT[]={0x14,0x08};//Don't change anything

unsigned char UART_busy;
unsigned int Zigbee_Recevie[32];
//========================================================================
// name:  Uart_Isr() interrupt 4
// descrption:Use it to recevie infomation
// param: none.
// return: none.
// version: VER1.0.0
// date: 17-June-2019
// attention: none
//========================================================================
void Uart_Isr() interrupt 4
{
	if(TI)
	{
		TI=0;
		UART_busy=0;
	}
	if(RI)
	{
		Zigbee_Recevie[Zigbee_Count]=SBUF;
		if(Zigbee_Recevie[Zigbee_Count]==0xff&&Zigbee_Count==0)
		{
			Zigbee_Count=1;
			return;
		}
		if(Zigbee_Count!=0)
		{
			if(Zigbee_Recevie[Zigbee_Count]==0xfe){SBUF='f';Zigbee_Count=0;return;}
			Zigbee_Count++;
		}
		RI=0;
	}

}
																	
//========================================================================
// name: Usart_Send_Byte(unsigned char Data)
// descrption: Send message through UART1
// param: data.
// return: none.
// version: VER1.0.0
// date: 17-June-2019
// attention: none
//========================================================================
void Zigbee_Setup()
{
	Usart_Setup();
	Usart_Send_Byte('a');
	Zigbee_CMD(CMD_Zigbee_ChangeIP,sizeof(CMD_Zigbee_ChangeIP));
	Zigbee_CMD(CMD_Zigbee_Change_NetID,sizeof(CMD_Zigbee_Change_NetID));
	Zigbee_CMD(CMD_Zigbee_Change_Channel,sizeof(CMD_Zigbee_Change_Channel));
	//Zigbee_CMD(CMD_Zigbee_Change_BRT,sizeof(CMD_Zigbee_Change_BRT));
	Zigbee_CMD(&CMD_Zigbee_Restart,1);
}

//========================================================================
// name:Zigbee_Send(unsigned char *Data,unsigned int len,unsigned short ADDR)
// descrption: Send Information
// param: Data : message that you want to send
//        len : lenth of the data
//				ADDR: the traget's IP address
// return: none.
// version: VER1.0.0
// date: 17-June-2019
// attention: none
//========================================================================
void Zigbee_Send(unsigned char *Data,unsigned int len,int ADDR)
{
	unsigned char ADDR_H,ADDR_L;
	ADDR_H=(unsigned char)(ADDR>>8);
	ADDR_L=(unsigned char)(ADDR&0xff);
	Usart_Send_Byte(0xfe);
	Usart_Send_Byte(0x04+len);
	Usart_Send_Byte(0x90);
	Usart_Send_Byte(0x90);
	Usart_Send_Byte(ADDR_H);
	Usart_Send_Byte(ADDR_L);
	while(len--)
	{
		Usart_Send_Byte(*Data++);
	}
	Usart_Send_Byte(0xff);
}

//========================================================================
// name:Zigbee_CMD(unsigned char *CMD;)
// descrption: Setup UART1
// param: CMD: CMD_Control.
//        len : lenth of the CMD              
// return: none.
// version: VER1.0.0
// date: 17-June-2019
// attention: none
//========================================================================
static void Zigbee_CMD(unsigned char *CMD,unsigned int len)
{
	Usart_Send_Byte(0xfe);
	Usart_Send_Byte(0x04+len);
	Usart_Send_Byte(0x90);
	Usart_Send_Byte(0x21);
	Usart_Send_Byte(0x00);
	Usart_Send_Byte(0x00);
	while(len--)
	{
		Usart_Send_Byte(*CMD);
		CMD++;
	}
	Usart_Send_Byte(0xff);
}



//========================================================================
// name: Usart_Send_Byte(unsigned char Data)
// descrption: Send message through UART1
// param: Data.
// return: none.
// version: VER1.0.0
// date: 17-June-2019
// attention: none
//========================================================================
void Usart_Send_Byte(unsigned char Data)
{
	while(UART_busy);
	UART_busy=1;
	SBUF=Data;
}

//========================================================================
// name:Usart_Setup() 
// descrption: Setup UART1
// param: none
// return: none.
// version: VER1.0.0
// date: 17-June-2019
// attention: none
//========================================================================
void Usart_Setup()
{
	SCON=0x50;
	TMOD=0x00;
	TL1=BRT;
	TH1=BRT>>8;
	TR1=1;
	AUXR=0X40;
	ES=1;
	EA=1;
}





