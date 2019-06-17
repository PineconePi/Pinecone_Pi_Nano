/**
  ******************************************************************************
  * @file    DS3231.h
  * @author  PineconePi(User)
  * @version V1.0.0
  * @date    17-June-2019
  * @brief  This document is used to drive DS3231.
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
#ifndef _DS3231_H_
#define _DS3231_H_

#include "system.h"

unsigned char DS3231_Read(unsigned char Address);
void DS3231_Write(unsigned char Address,unsigned char dat);

#endif