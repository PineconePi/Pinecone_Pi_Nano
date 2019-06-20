//xdd_core于2019-6-18修改本文件以用于在松果派NANO（STC8A8K64S4A12）上运行
#include <stdio.h>
#include <hal_uart.h>
#include "gizwits_protocol.h"

bit		B_TI;
bit		B_TI2;
/****************串口2发送函数（函数名不变，功能对调了）**********************/
void	UART1_TxByte(unsigned char dat)
{
		B_TI2 = 0;	//发送标志
	S2BUF = dat;	//SBUF在这里是一个可写发送缓冲寄存器，把需要发送的数据放在寄存器中
	while(!B_TI2);	//等待数据传送，传送结束后B_TI2置1
	B_TI2 = 0;	//发送标志
}
/****************串口1发送函数（函数名不变，功能对调了）**********************/
void	UART2_TxByte(unsigned char dat)
{
	B_TI = 0;		//发送标志
	SBUF = dat;		//SBUF在这里是一个可写发送缓冲寄存器，把需要发送的数据放在寄存器中
	while(!B_TI);	//等待数据传送，传送结束后B_TI置1	
	B_TI = 0;		//发送标志
}

void PrintString1(unsigned char code *puts)		//发送一串字符串
{
    for (; *puts != 0;	puts++)  UART1_TxByte(*puts); 	//遇到停止符0结束
}

void PrintString2(unsigned char code *puts)		//发送一串字符串
{
    for (; *puts != 0;	puts++)  UART2_TxByte(*puts); 	//遇到停止符0结束
}

/****************串口1初始化函数**********************/
//打印日志
void	uart1_init(void)//115200bps@24.000MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设定定时器1为16位自动重装方式
	TL1 = 0xCC;		//设定定时初值
	TH1 = 0xFF;		//设定定时初值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}

/****************串口1中断函数**********************/
void UART1_RCV (void) interrupt 4	//串口1我们没有用到接收，这里可以删除。
{
	if(TI)	//等待发送完成
	{
		TI = 0;		//发送中断标志位,必须通过软件清零
		B_TI = 1;	//数据发送完成的标志
	}
}


/****************串口2初始化************************/
void	uart2_init(void)	//9600bps@24.000MHz
{
		S2CON = 0x50;		//8位数据,可变波特率
		AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
		T2L = 0x8F;		//设定定时初值
		T2H = 0xFD;		//设定定时初值
		AUXR |= 0x10;		//启动定时器2
    IE2 = 0x01;                 //使能串口2中断
		IE2 |=  1;			//允许串口2中断
		ES  = 1;			//串行口中断允许（ES=1允许，ES=0禁止）		
		EA = 1;				//中断总开关
}

/**************串口2中断函数**********************/
void UART2_RCV (void) interrupt 8
{
	
	uint8_t gizbuf;
		if(S2CON & S2RI)	//等待串口2接收完成
	{
		CLR_RI2();	//接收中断请求标志位清0	
		gizbuf = S2BUF;	//SBUF在这里是一个接收缓冲寄存器，把接收到数据放到我们的自定义的接收缓冲区
		gizPutData(&gizbuf,1);//把接收到的数据放到环形缓冲区
	}
	if(S2CON & S2TI)		//等待串口2发送完成
	{
		CLR_TI2();	//发送中断请求标志位清0
		B_TI2 = 1;	//数据发送完成的标志
	}
}