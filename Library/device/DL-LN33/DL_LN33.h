/**
  ******************************************************************************
  * @file    DL_LN33.h
  * @author  ThreeWater
  * @version V1.0.0
  * @date    17-June-2019
  * @brief  This article will be used for  driving  DL-33N.
  * @License:none         
  ******************************************************************************
  * @attention
  *	The frequency of crystal oscillator is 24 Mhz.
  * using Zigbee_Setup() to initialize.
  * Using the UART1 to do it.
  * Possibly with other libraries.
  * Using interrupt4.
  * 
  * 
  *
  * 
  ******************************************************************************
	**/
#ifndef _DL_LN33_
#define _DL_LN33_

#include "system.h"
#include "intrins.h"

#define FOSC 24000000UL  //crystal oscillator
#define BRT (65536-FOSC/115200/4) //brt

extern unsigned int Zigbee_Recevie[32];
void Zigbee_Send(unsigned char *Data,unsigned int len,unsigned short ADDR);
void Zigbee_Setup();

#endif /* __DL_33N */
