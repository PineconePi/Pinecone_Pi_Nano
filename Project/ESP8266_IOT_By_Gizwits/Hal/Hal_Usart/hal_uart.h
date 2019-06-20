/**
************************************************************
* @file         hal_uart.h
* @brief        串口驱动头文件
* @author       Gizwits（//xdd_core于2019-6-18修改本文件以用于在松果派NANO（STC8A8K64S4A12）上运行）
* @date         2016-09-05
* @version      V03010101
* @copyright    Gizwits
* 
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值ֵ|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/
#ifndef _HAL_UART_H
#define _HAL_UART_H
#include <intrins.h>

/*************** 函数外部引用声明 *****************************/
void	uart1_init(void);
void	uart2_init(void);
void	UART1_TxByte(unsigned char dat);
void	UART2_TxByte(unsigned char dat);
void	PrintString1(unsigned char code *puts);
void	PrintString2(unsigned char code *puts);
/*************** 用户定义参数 *****************************/

#define	TI2				(S2CON & 0x02) != 0	//发送中断请求标志位为0时，则TI2为0
#define	RI2				(S2CON & 0x01) != 0	//接收中断请求标志位为0时，则RI2为0
#define	CLR_TI2()		S2CON &= ~0x02	//发送中断请求标志位清0
#define	CLR_RI2()		S2CON &= ~0x01	//接收中断请求标志位清0
#define FOSC 11059200L          //系统频率			 
#define BAUD1 9600             //串口1波特率
#define BAUD2 115200             //串口2波特率

/**********************************************************/
#endif