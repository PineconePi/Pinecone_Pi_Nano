/**
  ******************************************************************************
  * @file    uart.h
  * @author  PineconePi(基于宏晶科技STC15库函数进行修改)
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This file is used to configure the serial port 
  * @License:GNU General Public License v3.0         
  ******************************************************************************
  * @attention
  *
  *Serial Interrupt Processing Function in uart.c 
  *  
  * 
  * 
  * 
  * 
  *
  * 
  ******************************************************************************
	**/
#ifndef __UART_H
#define __UART_H	 

#include	"system.h"

#define	COM_TX1_Lenth	128
#define	COM_RX1_Lenth	128
#define	COM_TX2_Lenth	128
#define	COM_RX2_Lenth	128

#define	USART1	1
#define	USART2	2

#define	UART_ShiftRight	0		//Synchronized shift output|同步移位输出
#define	UART_8bit_BRTx	(1<<6)	//8-bit data, variable baud rate|8位数据,可变波特率
#define	UART_9bit		(2<<6)	//9-bit data, fixed baud rate|9位数据,固定波特率
#define	UART_9bit_BRTx	(3<<6)	//9-bit data, variable baud rate|9位数据,可变波特率

#define	UART1_SW_P30_P31	0
#define	UART1_SW_P36_P37	(1<<6)
#define	UART1_SW_P16_P17	(2<<6)	//Internal clock must be used|必须使用内部时钟
#define	UART2_SW_P10_P11	0
#define	UART2_SW_P46_P47	1


#define	TimeOutSet1		5
#define	TimeOutSet2		5

#define	BRT_Timer1	1
#define	BRT_Timer2	2

#define ENABLE  	1			//允许
#define DISABLE  	0			//关闭

#define PolityHigh  1	  //High priority|高优先级
#define PolityLow  	0		//Low priority (default)|低优先级（默认）

typedef struct
{ 
	unsigned char	id;				//Serial port number|串口号

	unsigned char	TX_read;		//Send Read Pointer|发送读指针
	unsigned char	TX_write;		//Send Write Pointer|发送写指针
	unsigned char	B_TX_busy;		//Busy sign忙标志

	unsigned char 	RX_Cnt;			//Received byte count|接收字节计数
	unsigned char	RX_TimeOut;		//Receiving timeout|接收超时
	unsigned char	B_RX_OK;		//Receiving Block Completion|接收块完成
} COMx_Define; 

typedef struct
{ 
	unsigned char	UART_Mode;			//Pattern|模式,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	unsigned char	UART_BRT_Use;		//Using baud rate|使用波特率,   BRT_Timer1,BRT_Timer2
	unsigned long	UART_BaudRate;		//baud rate|波特率,       ENABLE,DISABLE
	unsigned char	Morecommunicate;	//Multiprocessor Communication Allowance|多机通讯允许, ENABLE,DISABLE
	unsigned char	UART_RxEnable;		//Allow reception|允许接收,   ENABLE,DISABLE
	unsigned char	BaudRateDouble;		//Baud rate doubled|波特率加倍, ENABLE,DISABLE
	unsigned char	UART_Interrupt;		//Interrupt control|中断控制,   ENABLE,DISABLE
	unsigned char	UART_Polity;		//priority|优先级,     PolityLow,PolityHigh
	unsigned char	UART_P_SW;			//Switch port|切换端口,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17(必须使用内部时钟)
} COMx_InitDefine; 

extern	COMx_Define	COM1,COM2;
extern	unsigned char	xdata TX1_Buffer[COM_TX1_Lenth];	//Send buffer|发送缓冲
extern	unsigned char 	xdata RX1_Buffer[COM_RX1_Lenth];	//Receive buffer|接收缓冲
extern	unsigned char	xdata TX2_Buffer[COM_TX2_Lenth];	//Send buffer|发送缓冲
extern	unsigned char 	xdata RX2_Buffer[COM_RX2_Lenth];	//Receive buffer|接收缓冲

unsigned char	USART_Configuration(unsigned char UARTx, COMx_InitDefine *COMx);
void TX1_write2buff(unsigned char dat);	//Write send buffer, pointer + 1|写入发送缓冲，指针+1
void TX2_write2buff(unsigned char dat);	//Write send buffer, pointer + 1|写入发送缓冲，指针+1
void PrintString1(unsigned char *puts);
void PrintString2(unsigned char *puts);


#endif

