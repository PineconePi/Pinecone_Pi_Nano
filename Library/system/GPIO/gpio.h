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

#define	GPIO_PullUp		0	//Up-pull quasi-bidirectional port (default)|上拉准双向口(默认)
#define	GPIO_HighZ		1	//Floating input|浮空输入
#define	GPIO_OUT_OD		2	//Open drain output|开漏输出
#define	GPIO_OUT_PP		3	//push-pull|推挽输出

#define	GPIO_Pin_0		0x01	//IO pin Px.0|IO引脚 Px.0
#define	GPIO_Pin_1		0x02	//IO pin Px.1|IO引脚 Px.1
#define	GPIO_Pin_2		0x04	//IO pin Px.2|IO引脚 Px.2
#define	GPIO_Pin_3		0x08	//IO pin Px.3|IO引脚 Px.3
#define	GPIO_Pin_4		0x10	//IO pin Px.4|IO引脚 Px.4
#define	GPIO_Pin_5		0x20	//IO pin Px.5|IO引脚 Px.5
#define	GPIO_Pin_6		0x40	//IO pin Px.6|IO引脚 Px.6
#define	GPIO_Pin_7		0x80	//IO pin Px.7|IO引脚 Px.7
#define	GPIO_Pin_All	0xFF	//IO All pin |IO所有引脚
	
#define	GPIO_P0			0		
#define	GPIO_P1			1
#define	GPIO_P2			2
#define	GPIO_P3			3
#define	GPIO_P4			4
#define	GPIO_P5			5

//========================================================================
// Structures: GPIO_InitTypeDef|结构体: GPIO_InitTypeDef
// Description: GPIO configuration structure.|描述: GPIO配置结构体。
// Parameters: Mode, IO mode (GPIO_PullUp: pull-up quasi-bidirectional port, GPIO_HighZ: floating input, GPIO_OUT_OD: leak-out output, GPIO_OUT_PP: push-pull output)
//			 Pin, port, (GPIO_Pin_0: IO pin Px.0, PIO_Pin_1: IO pin Px.1, PIO_Pin_2: IO pin Px.2, PIO_Pin_3: IO pin Px.3,
// 			 PIO_Pin_4: IO pin Px.4, PIO_Pin_5: IO pin Px.5, PIO_Pin_6: IO pin Px.6, PIO_Pin_7: IO pin Px.7,
//			 PIO_Pin_All:IO All Pins 
// 参数: Mode,IO模式（GPIO_PullUp：上拉准双向口 , GPIO_HighZ：浮空输入 , GPIO_OUT_OD：开漏输出 , GPIO_OUT_PP：推挽输出
//			 Pin,端口,(GPIO_Pin_0 ：IO引脚 Px.0 ，PIO_Pin_1 ：IO引脚 Px.1 ，PIO_Pin_2 ：IO引脚 Px.2 ，PIO_Pin_3 ：IO引脚 Px.3 ，
// 			 PIO_Pin_4 ：IO引脚 Px.4 ，PIO_Pin_5 ：IO引脚 Px.5 ，PIO_Pin_6 ：IO引脚 Px.6 ，PIO_Pin_7 ：IO引脚 Px.7 ，
//			 PIO_Pin_All ：IO所有引脚 
// Return: none|返回: none.
// Version: VER1.0.0|版本: VER1.0.0
// Date: 2018-12-20|日期: 2018-12-20
// Note: Set P ^ 0 to two-way port by following steps
// GPIO_InitTypeDef GPIO_InitTypeDef;
// GPIO_InitTypeDef.Mode = GPIO_PullUp; //Up-pull quasi-bidirectional ports
// GPIO_InitTypeDef.Pin = GPIO_Pin_0 | GPIO_Pin_1; // Configure both IO pins Px.0 and Px.1
// GPIO_Inilize (GPIO_P, &amp; GPIO_InitTypeDef); //IO pin P 0.0
// 备注: 通过以下步骤将P0^0设置为上拉准双向口
//       GPIO_InitTypeDef GPIO_InitTypeDef;
//		 GPIO_InitTypeDef.Mode = GPIO_PullUp;//上拉准双向口
//       GPIO_InitTypeDef.Pin = GPIO_Pin_0|GPIO_Pin_1;//同时配置IO引脚 Px.0与Px.1
//		 GPIO_Inilize(GPIO_P0 ,&GPIO_InitTypeDef);//IO引脚 P0.0
//========================================================================
typedef struct
{
	unsigned char	Mode;		//IO Mode|IO模式
	unsigned char	Pin;		//Port|端口	
} GPIO_InitTypeDef;

unsigned char	GPIO_Inilize(unsigned char GPIO, GPIO_InitTypeDef *GPIOx);

#endif