/**
  ******************************************************************************
  * @file    Delay.h
  * @author  PineconePi
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This file is used to complete software Delay
  *          
  ******************************************************************************
  * @attention
  *The frequency of crystal oscillator is 24 Mhz
  *Input parameter range: 0 to 2^16-1
  * Usage: 
  * delayms(1000); //Delay 1 second
  * delayus(1000);//delay 1 ms
  * 
  * 
  *
  * 
  ******************************************************************************
	**/
#ifndef __DELAY_H_
#define __DELAY_H_
void delayms(unsigned int ms);//毫秒定时
void delayus(unsigned int us);//微秒定时