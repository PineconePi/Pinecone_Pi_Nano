/**
  ******************************************************************************
  * @file    PWM.H
  * @author  PineconePi (BTA-16 And xdd_core)
  * @version V1.0.0
  * @date    20-February-2019
  * @brief  This document is used for PWM configuration
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
#include "PWM.h"

//========================================================================
// Function:void PWM_Output(unsigned char PWM_Number,PWM_InitTypeDef *PWMx)|函数: void PWM_Output(unsigned char PWM_Number,PWM_InitTypeDef *PWMx)
// Description:PWM module output function.|描述: PWM模块输出函数。
// Parameters: PWM_Number (PWM module number parameter range: 0-7)
//             * PWMx: See PWM.h for details
// 参数: PWM_Number		(PWM模块编号 参数范围：0~7)
//  	 *PWMx：详情见PWM.h
// Return: None.|返回: None.
// Version:VER1.0.0|版本: VER1.0.0
// Date:2018-12-20|日期: 2019-2-10
// Note:|备注: 
// 
//========================================================================
void PWM_Output(unsigned char PWM_Number,PWM_InitTypeDef *PWMx)
{ 
	float PWM_Buf = 0,PWM_Pre = 0,PWM_Value;
	PWM_Buf = ( 1500000 / PWMx->PWM_Frequency );
	PWM_Value = 1000 - PWMx->PWM_Value;
	PWM_Pre = (PWM_Value/1000);
	P_SW2 = 0x80;																//Allow access to extended RAM (STC added)|允许访问扩展RAM（STC新增）
	PWMCKS = 0x0f;															   //System Clock 16 Dividing Frequency|系统时钟16分频
	PWMC = PWM_Buf;	
	switch(PWM_Number)
	{
		case 0 : PWM0T1 = 0x0000;PWM0T2 = PWM_Buf*PWM_Pre;PWM0CR= 0x80|PWMx->PWM_Channelx;break;
		case 1 : PWM1T1 = 0x0000;PWM1T2 = PWM_Buf*PWM_Pre;PWM1CR= 0x80|PWMx->PWM_Channelx;break;
		case 2 : PWM2T1 = 0x0000;PWM2T2 = PWM_Buf*PWM_Pre;PWM2CR= 0x80|PWMx->PWM_Channelx;break;
		case 3 : PWM3T1 = 0x0000;PWM3T2 = PWM_Buf*PWM_Pre;PWM3CR= 0x80|PWMx->PWM_Channelx;break;
		case 4 : PWM4T1 = 0x0000;PWM4T2 = PWM_Buf*PWM_Pre;PWM4CR= 0x80|PWMx->PWM_Channelx;break;
		case 5 : PWM5T1 = 0x0000;PWM5T2 = PWM_Buf*PWM_Pre;PWM5CR= 0x80|PWMx->PWM_Channelx;break;
		case 6 : PWM6T1 = 0x0000;PWM6T2 = PWM_Buf*PWM_Pre;PWM6CR= 0x80|PWMx->PWM_Channelx;break;
		case 7 : PWM7T1 = 0x0000;PWM7T2 = PWM_Buf*PWM_Pre;PWM7CR= 0x80|PWMx->PWM_Channelx;break;
		default:break;
	}
	P_SW2 = 0x00;																//Disallow Access to Extended RAM (STC Added)|禁止访问扩展RAM（STC新增）
	PWMCR = 0x80;                               //Start PWM module|启动PWM模块
}

