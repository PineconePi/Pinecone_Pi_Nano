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

#ifndef _PWM_H_
#define _PWM_H_

#include	"system.h"

/*PWM通道*/
#define PWM_Channel1 0x00
#define PWM_Channel2 0x08
#define PWM_Channel3 0x10

/*PWM模块*/
#define PWM_0 0
#define PWM_1 1
#define PWM_2 2
#define PWM_3 3
#define PWM_4 4
#define PWM_5 5
#define PWM_6 6
#define PWM_7 7

//========================================================================
// 结构体:  PWM_InitTypeDef
// 描述: PWM 配置结构体。
// 参数: PWM_Channel	(PWM通道号	 参数范围：1~3)
// 			 PWM_Value		(PWM值			 参数范围：0~1000 [计算公式：占空比（高电平时间）/周期（频率）= PWM_Value/1000])
//       例如舵机控制占空比为2.5ms 周期为20ms，则2.5/20=125/1000(PWM_Value值应为 125)
// 		   PWM_Frequency(PWM频率		 参数范围：46~5882)
// 返回: none.
// 版本: VER1.0.0
// 日期: 2018-12-20
// 备注: 通过以下步骤控制舵机偏转到0度
//			 PWM_InitTypeDef PWM_Init;
//			 PWM_Init.PWM_Channelx=PWM_Channel1;
//			 PWM_Init.PWM_Value=25;
//			 PWM_Init.PWM_Frequency=50;
//			 PWM_Output(PWM_0,&PWM_Init);
//========================================================================
typedef struct{ 
	unsigned char	PWM_Channelx;
	float PWM_Value;
	float	PWM_Frequency;
} PWM_InitTypeDef;

/*PWM输出函数*/
void PWM_Output(unsigned char PWM_Number,PWM_InitTypeDef *PWMx);

#endif