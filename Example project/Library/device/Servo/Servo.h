/**
  ******************************************************************************
  * @file    Servo.h
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
#ifndef _SERVO_H_
#define _SERVO_H_

#include "system.h"

#define Servo_Frequency 50 //50HZ 即20ms

/*PWM通道(舵机)*/
#define Servo_Channel1 0x00
#define Servo_Channel2 0x08
#define Servo_Channel3 0x10

/*舵机序号*/
#define Servo1 0
#define Servo2 1
#define Servo3 2
#define Servo4 3
#define Servo5 4
#define Servo6 5
#define Servo7 6
#define Servo8 7

//========================================================================
// 结构体:  Servo_Channelx
// 描述: 舵机 配置结构体。
// 参数: Servo_Channelx	(PWM通道号	 参数范围：1~3)
// 			 Servo_Angle		(舵机角度值			 参数范围：0~180 )
// 返回: none.
// 版本: VER1.0.0
// 日期: 2018-12-20
// 备注: 
//
//========================================================================
typedef struct{ 
	unsigned char	Servo_Channelx;
	float Servo_Angle;
} Servo_InitTypeDef;

void Servo_Control(unsigned char Servo_Number,Servo_InitTypeDef *Servox);

#endif
