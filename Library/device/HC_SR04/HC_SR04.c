/**
  ******************************************************************************
  * @file    hc_sr04.c
  * @author  PineconePi
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This article will be used for  driving  hc_sr04.
  * @License:GNU General Public License v3.0         
  ******************************************************************************
  * @attention
  *	The frequency of crystal oscillator is 24 Mhz
  *
  *  
  * 
  * 
  * 
  * 
  *
  * 
  ******************************************************************************
	**/
#include"hc_sr04.h"

unsigned int time_start; //Time of sound wave generation|发出声波的时间
unsigned int time_end;   //Time to receive sound waves|收到声波的时间 
						 //Echo_Pin High Level Duration = Time to Receive Sound Wave - Time to Produce Sound Wave|Echo_Pin高电平持续的时间=收到声波的时间-发出声波的时间

//========================================================================
// Function:delay_us_hc_sr04(unsigned int us)|函数: delay_us_hc_sr04(unsigned int us)
// Description: Delay function.|描述: 延时函数。
// Parameter: us, the number of us to be delayed, where only 1-10000 (10ms) us is supported|参数: us,要延时的us数, 这里只支持1~10000 (10ms) us
// Return: none.|返回: none.
// Version：ver1.0.0|版本: VER1.0.0
// Date: 2018-12-20|日期: 2018-12-20
// Note: delay_us (1000);//delay 1US|备注: delay_us(1000);//延迟1us
//========================================================================
void delay_us_hcsr04(unsigned int us){
  unsigned int k;
	unsigned char i;
	for(k=0;k<us;k++)
	{
	i = 6;
	while (--i);
	}
}
//========================================================================
// Function:void timer_init()|函数: void timer_init()
// Description:Initialization timer 3 (16 bit automatic overload).|描述: 初始化定时器3 （16位自动重载）。
// Parameter:|参数: 
// Return: none.|返回: none.
// Version：ver1.0.0|版本: VER1.0.0
// Date: 2018-12-20|日期: 2018-12-20
// Note:|备注:
//========================================================================
void timer_init()
{
	T4T3M |= 0x02;		//Timer clock 1T mode|定时器时钟1T模式
	T3L = 0x00;		//Setting Timing Initial Value|设置定时初值
	T3H = 0x00;		//Setting Timing Initial Value|设置定时初值
	T4T3M |= 0x08;		//Timer 3 starts timing|定时器3开始计时
}
//========================================================================
// Function:HC_SR04_Init()|函数: HC_SR04_Init()
// Description:The hardware needed to initialize HC_SR04.|描述: 初始化HC_SR04所需硬件。
// Parameter:|参数: 
// Return: none.|返回: none.
// Version：ver1.0.0|版本: VER1.0.0
// Date: 2018-12-20|日期: 2018-12-20
// Note:|备注:
//========================================================================
void HC_SR04_Init()
{
	timer_init();
}
//========================================================================
// Function:HC_SR04_Start()|函数: HC_SR04_Start()
// Description:Start sending sound waves.|描述: 开始发送声波。
// Parameter:|参数: 
// Return: none.|返回: none.
// Version：ver1.0.0|版本: VER1.0.0
// Date: 2018-12-20|日期: 2018-12-20
// Note:|备注:
//========================================================================
void HC_SR04_Start()
{
	Trig_Pin = 0;
	delay_us_hcsr04(45);
	Trig_Pin = 1;
}
//========================================================================
// Function:int HC_SR04_Loop()|函数: int HC_SR04_Loop()
// Description:Return distance.|描述: 返回距离。
// Parameter:|参数:  
// Return: distance: distance (in centimeters).|返回: distance:距离（单位：厘米）.
// Version：ver1.0.0|版本: VER1.0.0
// Date: 2018-12-20|日期: 2018-12-20
// Note:|备注:
//========================================================================
int HC_SR04_Loop()
{
	int distance;//distance|距离
	HC_SR04_Start();
	 while(!Echo_Pin);		//Wait when RX is zero|当RX为零时等待
//	 TR0=1;			    //Opening count|开启计数
		 time_start=T3H*256+T3L;
	 while(Echo_Pin);			//When RX counts to 1 and waits|当RX为1计数并等待
//	 TR0=0;				//Closing count|关闭计数
	time_end=T3H*256+T3L;
  distance=((time_end-time_start)/24)/58;     //It's CM (int)|算出来是CM(int)
	return distance;
}
															
															
															
															
															