/**
  ******************************************************************************
  * @file    Delay.c
  * @author  PineconePi
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
// 函数: void delay_ms(unsigned int ms)
// 描述: 延时函数。
// 参数: ms,要延时的ms数, 这里只支持1~10000 (10s) ms
// 返回: none.
// 版本: VER1.0.0
// 日期: 2018-12-20
// 备注: delay_ms(1000);//延迟1s
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
// 函数: delay_us(unsigned int us)
// 描述: 延时函数。
// 参数: us,要延时的us数, 这里只支持1~10000 (10ms) us
// 返回: none.
// 版本: VER1.0.0
// 日期: 2018-12-20
// 备注: delay_us(1000);//延迟1us
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
