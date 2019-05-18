/**
  ******************************************************************************
  * @file    Delay.c
  * @author  PineconePi(基于宏晶科技STC15库函数进行修改)
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This file is used to complete software Delay
  * @License:GNU General Public License v3.0         
  ******************************************************************************
  * @attention
  *The frequency of crystal oscillator is 24 Mhz
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
#include "delay.h"
#include "intrins.h"
//========================================================================
// Function:void delay_ms(unsigned int ms)|函数: void delay_ms(unsigned int ms)
// Description:Delay Function|描述: 延时函数。
// Parameter:Ms, the number of MS to be delayed, where only 1-10000 (10s) MS is supported|参数: ms,要延时的ms数, 这里只支持1~10000 (10s) ms
// Return:none|返回: none.
// Version VER1.0.0|版本: VER1.0.0
// Date:2018-12-20|日期: 2018-12-20
// Note:delay_ms(1000);//Delay 1s|备注: delay_ms(1000);//延迟1s
//========================================================================
void delay_ms(unsigned int ms){
  unsigned int k;
	unsigned char i, j;
	for(k=0;k<ms;k++)
	{
	_nop_();
	i = 32;
	j = 40;
		do
		{
		  while (--j);
		} while (--i);
	}
													   }
//========================================================================
// Function:delay_us(unsigned int us)|函数: delay_us(unsigned int us)
// Description:Delay Function|描述: 延时函数。
// Parameter:Us, the number of us delays, where only 1-10000 (10ms) us is supported|参数: us,要延时的us数, 这里只支持1~10000 (10ms) us
// Return:none|返回: none.
// Version:VER1.0.0|版本: VER1.0.0
// Date:2018-12-20|日期: 2018-12-20
// Note:delay_us(1000);//delay 1ms|备注: delay_us(1000);//延迟1ms
//========================================================================
void delay_us(unsigned int us){
  unsigned int k;
	unsigned char i;
	for(k=0;k<us;k++)
	{
	i = 6;
	while (--i);
	}
													    }
