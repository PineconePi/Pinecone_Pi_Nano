/**
  ******************************************************************************
  * @file    hc_sr04.h
  * @author  PineconePi
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This article will be used for  driving  hc_sr04.
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
#ifndef _HC_SR04_H_
#define _HC_SR04_H_

#include "system.h"

#define Echo_Pin P12   //Echo端口
#define Trig_Pin P13   //Trig端口

void HC_SR04_Init(void);//初始化HCSR04所需硬件
int HC_SR04_Loop(void); //获取当前距离值

#endif