/**
  ******************************************************************************
  * @file    exti.c
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


#include "exti.h"



/********************* INT0中断函数 *************************/
void Ext_INT0 (void) interrupt EXT_INT0		//进中断时已经清除标志
{
	//此处添加用户逻辑
}

/********************* INT1中断函数 *************************/
void Ext_INT1 (void) interrupt EXT_INT1		//进中断时已经清除标志
{
	//此处添加用户逻辑
}

/********************* INT2中断函数 *************************/
void Ext_INT2 (void) interrupt EXT_INT2	//
{
	//此处添加用户逻辑
}

/********************* INT3中断函数 *************************/
void Ext_INT3 (void) interrupt EXT_INT3
{
	//此处添加用户逻辑
}

/********************* INT4中断函数 *************************/
void Ext_INT4 (void) interrupt EXT_INT4
{
	//此处添加用户逻辑
}

//========================================================================
// 函数: unsigned char Ext_Inilize(unsigned char EXT, EXTI_InitTypeDef *INTx)
// 描述: 外部中断初始化程序.
// 参数: EXT,中断序号（EXT_INT0：外部中断0 , EXT_INT1：外部中断1 , EXT_INT2：外部中断2 , 
//       EXT_INT3：外部中断3 ， EXT_INT4：外部中断4
//       INTx: 结构参数,请参考Exti.h里的定义.
// 返回: 成功返回0, 空操作返回1,错误返回2.
// 版本: VER1.0.0
// 日期: 2018-12-20
// 备注: 通过以下步骤使能INT0
//	EXTI_InitTypeDef EXTI_InitTypeDef;
//	EXTI_InitTypeDef.EXTI_Mode = EXT_MODE_RiseFall;//上升沿中断
//	EXTI_InitTypeDef.EXTI_Polity = PolityHigh;//高优先级
//	EXTI_InitTypeDef.EXTI_Interrupt = ENABLE;//使能
//	Ext_Inilize(EXT_INT0,&EXTI_InitTypeDef);//完成配置
//========================================================================
unsigned char Ext_Inilize(unsigned char EXT, EXTI_InitTypeDef *INTx)
{
	if(EXT >  EXT_INT4)	return 1;	//空操作
	
	if(EXT == EXT_INT0)	//外中断0
	{
		if(INTx->EXTI_Interrupt == ENABLE)		EX0 = 1;	//允许中断
		else									EX0 = 0;	//禁止中断
		if(INTx->EXTI_Polity == PolityHigh)		PX0 = 1;	//高优先级中断
		else									PX0 = 0;	//低优先级中断
		if(INTx->EXTI_Mode == EXT_MODE_Fall)	IT0 = 1;	//下降沿中断
		else									IT0 = 0;	//上升,下降沿中断
		return	0;		//成功
	}

	if(EXT == EXT_INT1)	//外中断1
	{
		if(INTx->EXTI_Interrupt == ENABLE)		EX1 = 1;	//允许中断
		else									EX1 = 0;	//禁止中断
		if(INTx->EXTI_Polity == PolityHigh)		PX1 = 1;	//高优先级中断
		else									PX1 = 0;	//低优先级中断
		if(INTx->EXTI_Mode == EXT_MODE_Fall)	IT1 = 1;	//下降沿中断
		else									IT1 = 0;	//上升,下降沿中断
		return	0;		//成功
	}

	if(EXT == EXT_INT2)		//外中断2, 固定为下降沿低优先级中断
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INTCLKO |=  (1 << 4);	//允许中断	
		else								INTCLKO &= ~(1 << 4);	//禁止中断
		return	0;		//成功
	}

	if(EXT == EXT_INT3)		//外中断3, 固定为下降沿低优先级中断
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INTCLKO |=  (1 << 5);	//允许中断	
		else								INTCLKO &= ~(1 << 5);	//禁止中断
		return	0;		//成功
	}

	if(EXT == EXT_INT4)		//外中断4, 固定为下降沿低优先级中断
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INTCLKO |=  (1 << 6);	//允许中断	
		else								INTCLKO &= ~(1 << 6);	//禁止中断
		return	0;		//成功
	}
	return 2;	//失败
}