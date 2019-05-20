/**
  ******************************************************************************
  * @file    watchdog.h
  * @author  PineconePi
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This file is used to Configure internal WATCHDOG 
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
#ifndef _WATCHDOG_H_
#define _WATCHDOG_H_

#include "system.h"

#define WDT_MODE_1 0x23 //使能看门狗,溢出时间约为0.3s
#define WDT_MODE_2 0x24 //使能看门狗,溢出时间约为0.5s
#define WDT_MODE_3 0x27 //使能看门狗,溢出时间约为4.5s

void setup_watchdog(unsigned char WDT_MODE_x);//设置并使能看门狗
void off_watchdog();//关闭看门狗
void feed_dog();//喂狗
	
#endif