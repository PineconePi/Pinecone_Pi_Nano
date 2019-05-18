/**
  ******************************************************************************
  * @file    exti.h
  * @author  PineconePi(基于宏晶科技STC15库函数进行修改)
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This file is used for external interrupt configuration
  * @License:GNU General Public License v3.0         
  ******************************************************************************
  * @attention
  
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
#ifndef	__EXTI_H
#define	__EXTI_H

#include	"system.h"

#define	EXT_INT0			0	//External interrupt 0|外部中断0
#define	EXT_INT1			2	//External interrupt 1|外部中断1
#define	EXT_INT2			10	//External interrupt 2|外部中断2
#define	EXT_INT3			11	//External interrupt 3|外部中断3
#define	EXT_INT4			16	//External interrupt 4|外部中断4

#define	EXT_MODE_RiseFall	0		//Rising edge interruption|上升沿中断
#define	EXT_MODE_Fall		1			//Falling edge interruption|下降沿中断

#define ENABLE  	1			//Interrupt enable|中断允许
#define DISABLE  	0			//Interrupt disable|中断关闭

#define PolityHigh  1	  //High priority|高优先级
#define PolityLow  	0		//Low priority (default)|低优先级（默认）

//========================================================================
// Structure:EXTI_InitTypeDef|结构体: EXTI_InitTypeDef
// Description:EXTI configuration structure|描述: EXTI配置结构体。
// Parameters:EXTI_Mode（EXT_MODE_RiseFall：Rising edge interruption ，EXT_MODE_Fall: Falling edge interruption)
//            EXTI_Polity(PolityHigh:High priority , PolityLow:Low priority (default))
//            EXTI_Interrupt(ENABLE:， DISABLE：）
// 参数: EXTI_Mode（EXT_MODE_RiseFall：上升沿中断 ，EXT_MODE_Fall: 下降沿中断)
//       EXTI_Polity(PolityHigh:高优先级 , PolityLow:低优先级（默认）)
//       EXTI_Interrupt(ENABLE:允许 ， DISABLE：不使能）
// 返回: none.
// 版本: VER1.0.0
// 日期: 2018-12-20
// 备注: 通过以下步骤使能INT0
//	EXTI_InitTypeDef EXTI_InitTypeDef;
//	EXTI_InitTypeDef.EXTI_Mode = EXT_MODE_RiseFall;//上升沿中断
//	EXTI_InitTypeDef.EXTI_Polity = PolityHigh;//高优先级
//	EXTI_InitTypeDef.EXTI_Interrupt = ENABLE;//使能
//	Ext_Inilize(EXT_INT0,&EXTI_InitTypeDef);//完成配置
//========================================================================
typedef struct
{
	unsigned char	EXTI_Mode;			//Interrupt mode|中断模式,  	EXT_MODE_RiseFall, EXT_MODE_Fall
	unsigned char	EXTI_Polity;		//Priority Setting|优先级设置	PolityHigh,PolityLow
	unsigned char	EXTI_Interrupt;		//Interrupt enable|中断允许		ENABLE,DISABLE
} EXTI_InitTypeDef;

unsigned char	Ext_Inilize(unsigned char EXT, EXTI_InitTypeDef *INTx);

#endif
