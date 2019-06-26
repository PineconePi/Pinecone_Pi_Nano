/**
************************************************************
* @file         main.c
* @brief        MCU版 入口文件
* @author       Gizwits
* @date         2016-09-05
* @version      V03010101
* @copyright    Gizwits
* 
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值?|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/
/********************************************************
** 代码移植说明
*
* 1、实现与模组通信串口驱动（1、中断收数据写入环形缓冲区;2、实现uartWrite()串口发送函数）
* 2、实现串口打印函数printf()
* 3、实现ms定时器，gizTimerMs()维护系统时间
* 4、实现MCU复位函数,模组可请求MCU复位
* 5、实现配置入网功能,调用gizwitsSetMode()函数实现模组配网功能
* 6、实现userHandle()数据的采集（上行逻辑）
* 7、实现gizwitsEventProcess()控制命令的具体执行(下行逻辑)
* 8、实现mcuRestart()复位函数
* 
*
*********************************************************/
#include <stdint.h>
#include <string.h>
#include <hal_uart.h>
#include <hal_key.h>
#include "gizwits_protocol.h"
#include "gizwits_product.h"

/******************** 开/关机|重启引脚 ***************/
#define Power_on P01
#define Power_off P02
#define Reset P03

/** 用户区当前设备状态结构体*/
dataPoint_t currentDataPoint;
uint32_t timerMsCount = 0 ;
unsigned int Time = 0;
unsigned int sec1000 = 0;
extern unsigned char	skeycount;		//设置按键时长计数器
extern unsigned char	skpttime;		//设置按键时长
extern bit		skpflag;				//设置按键按下标志
/******************** 本地函数声明 ***************/
void 	Timer0_Init(void);
void 	Delay_ms(unsigned int n);
void Pin_Init(void);
/******************** 重写putchar函数 ***************/
char putchar(char c)
{
    UART2_TxByte(c);//printf映射到串口1的发送函数
    return c;
}





/**
* @brief程序入口函数

* 在该函数中完成用户相关的初始化,及主逻辑循环
* @param none
* @return none
*/
int main(void)
{  
	Pin_Init();
	uart1_init();
	uart2_init();
	Timer0_Init();

    userInit();
    gizwitsInit();
    
    while(1)
    {
		setkeyscan();					//检测功能键

        userHandle();
 
        gizwitsHandle((dataPoint_t *)&currentDataPoint);
		
		
		
    }
}
/**************引脚初始化函数**********************/
void Pin_Init()
{
	Power_on=1;
	Power_off=1;
	Reset=1;
}
/**************定时器初始化函数**********************/
void Timer0_Init(void)
{
	TMOD|=0x02;
	TL0=0x40;//0x47;
	TH0=0xa2;//0x47;
	ET0=1;
	TR0=1;
}
/*************定时器中断函数******************/
void Timer0_Tsr(void) interrupt 1
{
	Time ++;
	if(Time == 5)
	{
		Time = 0;
		gizTimerMs();
	}
	sec1000++;
	if(sec1000 >= 1000)	//1秒时间 (1000*1ms=1000ms=1s)
	{
		sec1000 = 0;
		//以下为设置功能键的按键时长计数部分
		if(skpflag)
		{
		 	skeycount++;
			if(SETKEY) skpttime=skeycount;
		}
	}
}
/**************计时器延时函数*******************/
void Delay_ms(unsigned int n)
{
	unsigned int  i,j;	
	for(i=0;i<n;i++)
		for(j=0;j<123;j++);
}
