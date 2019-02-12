/**
  ******************************************************************************
  * @file    Servo.c
  * @author  PineconePi
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This file is used to control Servo
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
  * 
  ******************************************************************************
	**/
#include "Servo.h"
//========================================================================
// 函数: void Servo_Control(unsigned char Servo_Number,Servo_InitTypeDef *Servox)
// 描述: 舵机控制函数。
// 参数: Servo_Number		(舵机编号 参数范围：1~8)
//  	   *Servox：详情见Servo.h
// 返回: None.
// 版本: VER1.0.0
// 日期: 2019-2-10
// 备注: 通过以下步骤控制舵机偏转到0度
// 	Servo_InitTypeDef Servo_Init;
//  Servo_Init.Servo_Channelx=Servo_Channel1;	
//  Servo_Init.Servo_Angle=0;
//  Servo_Control(Servo1,&Servo_Init);
//========================================================================
void Servo_Control(unsigned char Servo_Number,Servo_InitTypeDef *Servox)
{ 
	float PWM_Buf = 0,PWM_Pre = 0,PWM_Value;
	float i;//转换系数，将角度转换为占空比
	i = 100/180;
	PWM_Buf = ( 1500000 / Servo_Frequency );
	PWM_Value = 1000 - ( 25+(0.55*Servox->Servo_Angle));
	PWM_Pre = (PWM_Value/1000);
	P_SW2 = 0x80;																//允许访问扩展RAM（STC新增）
	PWMCKS = 0x0f;															//系统时钟16分频
	PWMC = PWM_Buf;	
	switch(Servo_Number)
	{
		case 0 : PWM0T1 = 0x0000;PWM0T2 = PWM_Buf*PWM_Pre;PWM0CR= 0x80|Servox->Servo_Channelx;break;
		case 1 : PWM1T1 = 0x0000;PWM1T2 = PWM_Buf*PWM_Pre;PWM1CR= 0x80|Servox->Servo_Channelx;break;
		case 2 : PWM2T1 = 0x0000;PWM2T2 = PWM_Buf*PWM_Pre;PWM2CR= 0x80|Servox->Servo_Channelx;break;
		case 3 : PWM3T1 = 0x0000;PWM3T2 = PWM_Buf*PWM_Pre;PWM3CR= 0x80|Servox->Servo_Channelx;break;
		case 4 : PWM4T1 = 0x0000;PWM4T2 = PWM_Buf*PWM_Pre;PWM4CR= 0x80|Servox->Servo_Channelx;break;
		case 5 : PWM5T1 = 0x0000;PWM5T2 = PWM_Buf*PWM_Pre;PWM5CR= 0x80|Servox->Servo_Channelx;break;
		case 6 : PWM6T1 = 0x0000;PWM6T2 = PWM_Buf*PWM_Pre;PWM6CR= 0x80|Servox->Servo_Channelx;break;
		case 7 : PWM7T1 = 0x0000;PWM7T2 = PWM_Buf*PWM_Pre;PWM7CR= 0x80|Servox->Servo_Channelx;break;
		default:break;
	}
	P_SW2 = 0x00;																//禁止访问扩展RAM（STC新增）
	PWMCR = 0x80;                               //启动PWM模块
}