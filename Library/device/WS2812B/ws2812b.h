/**
  ******************************************************************************
  * @file    ws2812b.h
  * @author  PineconePi
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This article will be used for  driving  ws2812b.
  * @License:GNU General Public License v3.0         
  ******************************************************************************
  * @attention
  *	The frequency of crystal oscillator is 24 Mhz
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
#ifndef _WS2812B_H_
#define	_WS2812B_H_

#include "system.h"

#define rgb_pin P12   //RGB端口
#define n_ws2812b 12  //RGB灯珠数
#define clear_ws2812b 24  //roll_2清零 （保证完全清零，clear_ws2812b = 2*n_ws2812b)
#define normal 0  //普通模式
#define  roll 1	  //正向单数流水模式
#define roll_back_1 2 //反向流水模式
#define roll_back_2 3 //反向间隔流水模式
#define roll_delay 100	  //流水模式间隔（单位：ms）
#define breathe 4 //呼吸模式   
void delay_ms_2812b(unsigned int ms);
void n_ws2812b_display(unsigned char display_mode,unsigned char green,unsigned char red,unsigned char blue);//n颗ws2812b控制
#endif