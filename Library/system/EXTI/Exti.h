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

#define	EXT_INT0			0		//外部中断0
#define	EXT_INT1			2		//外部中断1
#define	EXT_INT2			10	//外部中断2
#define	EXT_INT3			11	//外部中断3
#define	EXT_INT4			16	//外部中断4

#define	EXT_MODE_RiseFall	0		//上升沿中断
#define	EXT_MODE_Fall		1			//下降沿中断

#define ENABLE  	1			//中断允许
#define DISABLE  	0			//中断关闭

#define PolityHigh  1	  //高优先级
#define PolityLow  	0		//低优先级（默认）

//========================================================================
// 结构体: EXTI_InitTypeDef
// 描述: EXTI配置结构体。
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
	unsigned char	EXTI_Mode;			//中断模式,  	EXT_MODE_RiseFall, EXT_MODE_Fall
	unsigned char	EXTI_Polity;		//优先级设置	PolityHigh,PolityLow
	unsigned char	EXTI_Interrupt;		//中断允许		ENABLE,DISABLE
} EXTI_InitTypeDef;

unsigned char	Ext_Inilize(unsigned char EXT, EXTI_InitTypeDef *INTx);

#endif
