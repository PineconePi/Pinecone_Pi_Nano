/**
  ******************************************************************************
  * @file    timer.h
  * @author  PineconePi(基于宏晶科技STC15库函数进行修改)
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
#ifndef	__TIMER_H
#define	__TIMER_H

#include	"system.h"

#define	Timer0						0
#define	Timer1						1
#define	Timer2						2
#define	Timer3						3
#define	Timer4						4

#define	TIM_16BitAutoReload			0
#define	TIM_16Bit					1
#define	TIM_8BitAutoReload			2
#define	TIM_16BitAutoReloadNoMask	3

#define	TIM_CLOCK_1T				0
#define	TIM_CLOCK_12T				1
#define	TIM_CLOCK_Ext				2

#define ENABLE  	1			//允许
#define DISABLE  	0			//关闭

#define PolityHigh  1	  //高优先级
#define PolityLow  	0		//低优先级（默认）

typedef struct
{
	unsigned char	TIM_Mode;		//工作模式,  	TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	unsigned char	TIM_Polity;		//优先级设置	PolityHigh,PolityLow
	unsigned char	TIM_Interrupt;	//中断允许		ENABLE,DISABLE
	unsigned char	TIM_ClkSource;	//时钟源		TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	unsigned char	TIM_ClkOut;		//可编程时钟输出,	ENABLE,DISABLE
	unsigned int	TIM_Value;		//装载初值
	unsigned char	TIM_Run;		//是否运行		ENABLE,DISABLE
} TIM_InitTypeDef;

unsigned char	Timer_Inilize(unsigned char TIM, TIM_InitTypeDef *TIMx);

#endif
