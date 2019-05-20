/**
  ******************************************************************************
  * @file    timer.c
  * @author  PineconePi
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This document is used for timer configuration 
  * @License:GNU General Public License v3.0         
  ******************************************************************************
  * @attention
  *
  *Timer Interrupt Processing Function in timer.c
  *  
  * 
  * 
  * 
  * 
  *
  * 
  ******************************************************************************
	**/

#include	"timer.h"

/********************* Timer0中断函数************************/
void timer0_int (void) interrupt 1
{

}

/********************* Timer1中断函数************************/
void timer1_int (void) interrupt 3
{

}

/********************* Timer2中断函数************************/
void timer2_int (void) interrupt 12
{

}


//========================================================================
// 函数: unsigned char	Timer_Inilize(unsigned char TIM, TIM_InitTypeDef *TIMx)
// 描述: 定时器初始化程序.
// 参数:  请参考timer.c里面的结构体定义
//       
//       
// 返回: 
// 版本: VER1.0.0
// 日期: 2018-12-20
// 作者: PineconePi
// 备注:
//	
//	
//	
//	
//	
//========================================================================
unsigned char	Timer_Inilize(unsigned char TIM, TIM_InitTypeDef *TIMx)
{
	if(TIM > Timer2)	return 1;	//空操作

	if(TIM == Timer0)
	{
		TR0 = 0;		//停止计数
		if(TIMx->TIM_Interrupt == ENABLE)		ET0 = 1;	//允许中断
		else									ET0 = 0;	//禁止中断
		if(TIMx->TIM_Polity == PolityHigh)		PT0 = 1;	//高优先级中断
		else									PT0 = 0;	//低优先级中断
		if(TIMx->TIM_Mode >  TIM_16BitAutoReloadNoMask)	return 2;	//错误
		TMOD = (TMOD & ~0x03) | TIMx->TIM_Mode;	//工作模式,0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装, 3: 16位自动重装, 不可屏蔽中断
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x80;	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x80;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x04;	//对外计数或分频
		else										TMOD &= ~0x04;	//定时
		if(TIMx->TIM_ClkOut == ENABLE)	INTCLKO |=  0x01;	//输出时钟
		else							INTCLKO &= ~0x01;	//不输出时钟
		
		TH0 = (unsigned char)(TIMx->TIM_Value >> 8);
		TL0 = (unsigned char)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR0 = 1;	//开始运行
		return	0;		//成功
	}

	if(TIM == Timer1)
	{
		TR1 = 0;		//停止计数
		if(TIMx->TIM_Interrupt == ENABLE)		ET1 = 1;	//允许中断
		else									ET1 = 0;	//禁止中断
		if(TIMx->TIM_Polity == PolityHigh)		PT1 = 1;	//高优先级中断
		else									PT1 = 0;	//低优先级中断
		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return 2;	//错误
		TMOD = (TMOD & ~0x30) | TIMx->TIM_Mode;	//工作模式,0: 16位自动重装, 1: 16位定时/计数, 2: 8位自动重装
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x40;	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x40;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x40;	//对外计数或分频
		else										TMOD &= ~0x40;	//定时
		if(TIMx->TIM_ClkOut == ENABLE)	INTCLKO |=  0x02;	//输出时钟
		else							INTCLKO &= ~0x02;	//不输出时钟
		
		TH1 = (unsigned char)(TIMx->TIM_Value >> 8);
		TL1 = (unsigned char)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR1 = 1;	//开始运行
		return	0;		//成功
	}

	if(TIM == Timer2)		//Timer2,固定为16位自动重装, 中断无优先级
	{
		AUXR &= ~(1<<4);	//停止计数
		if(TIMx->TIM_Interrupt == ENABLE)			IE2  |=  (1<<2);	//允许中断
		else										IE2  &= ~(1<<2);	//禁止中断
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~(1<<2);	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  (1<<2);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	AUXR |=  (1<<3);	//对外计数或分频
		else										AUXR &= ~(1<<3);	//定时
		if(TIMx->TIM_ClkOut == ENABLE)	INTCLKO |=  0x04;	//输出时钟
		else							INTCLKO &= ~0x04;	//不输出时钟

		TH2 = (unsigned char)(TIMx->TIM_Value >> 8);
		TL2 = (unsigned char)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	AUXR |=  (1<<4);	//开始运行
		return	0;		//成功
	}
	return 2;	//错误
}
