/**
  ******************************************************************************
  * @file    LCD1602.h
  * @author  PineconePi(User)
  * @version V1.0.0
  * @date    17-June-2019
  * @brief  This document is used to drive LCD1602.
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
#ifndef _LCD1602_H_
#define _LCD1602_H_

#include "system.h"

#define Reg 0   //写入类型：命令
#define Data 1  //写入类型：数据

#define RS P21  //数据/命令选择
#define RW P22  //读取/写入选择
#define EN P24	//使能信号
#define DO P1		//数据口


void LCD1602_Write(unsigned char Write_Type,unsigned char Dat);//LCD1602写入命令

#endif