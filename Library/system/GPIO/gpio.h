/**
  ******************************************************************************
  * @file    gpio.h
  * @author  PineconePi(基于宏晶科技STC15库函数进行修改)
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This document is used for GPIO configuration
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
#ifndef	__GPIO_H_
#define	__GPIO_H_

#include	"system.h"

#define	GPIO_PullUp		0	//上拉准双向口(默认)
#define	GPIO_HighZ		1	//浮空输入
#define	GPIO_OUT_OD		2	//开漏输出
#define	GPIO_OUT_PP		3	//推挽输出

#define	GPIO_Pin_0		0x01	//IO引脚 Px.0
#define	GPIO_Pin_1		0x02	//IO引脚 Px.1
#define	GPIO_Pin_2		0x04	//IO引脚 Px.2
#define	GPIO_Pin_3		0x08	//IO引脚 Px.3
#define	GPIO_Pin_4		0x10	//IO引脚 Px.4
#define	GPIO_Pin_5		0x20	//IO引脚 Px.5
#define	GPIO_Pin_6		0x40	//IO引脚 Px.6
#define	GPIO_Pin_7		0x80	//IO引脚 Px.7
#define	GPIO_Pin_All	0xFF	//IO所有引脚
	
#define	GPIO_P0			0		
#define	GPIO_P1			1
#define	GPIO_P2			2
#define	GPIO_P3			3
#define	GPIO_P4			4
#define	GPIO_P5			5

//========================================================================
// 结构体: GPIO_InitTypeDef
// 描述: GPIO配置结构体。
// 参数: Mode,IO模式（GPIO_PullUp：上拉准双向口 , GPIO_HighZ：浮空输入 , GPIO_OUT_OD：开漏输出 , GPIO_OUT_PP：推挽输出
//			 Pin,端口,(GPIO_Pin_0 ：IO引脚 Px.0 ，PIO_Pin_1 ：IO引脚 Px.1 ，PIO_Pin_2 ：IO引脚 Px.2 ，PIO_Pin_3 ：IO引脚 Px.3 ，
// 			 PIO_Pin_4 ：IO引脚 Px.4 ，PIO_Pin_5 ：IO引脚 Px.5 ，PIO_Pin_6 ：IO引脚 Px.6 ，PIO_Pin_7 ：IO引脚 Px.7 ，
//			 PIO_Pin_All ：IO所有引脚 
// 返回: none.
// 版本: VER1.0.0
// 日期: 2018-12-20
// 备注: 通过以下步骤将P0^0设置为上拉准双向口
//       GPIO_InitTypeDef GPIO_InitTypeDef;
//			 GPIO_InitTypeDef.Mode = GPIO_PullUp;//上拉准双向口
//       GPIO_InitTypeDef.Pin = GPIO_Pin_0|GPIO_Pin_1;//同时配置IO引脚 Px.0与Px.1
//			 GPIO_Inilize(GPIO_P0 ,&GPIO_InitTypeDef);//IO引脚 P0.0
//========================================================================
typedef struct
{
	unsigned char	Mode;		//IO模式
	unsigned char	Pin;		//端口	
} GPIO_InitTypeDef;

unsigned char	GPIO_Inilize(unsigned char GPIO, GPIO_InitTypeDef *GPIOx);

#endif