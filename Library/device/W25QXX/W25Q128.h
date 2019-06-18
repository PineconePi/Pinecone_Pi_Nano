/**
  ******************************************************************************
  * @file    W25Q128.h
  * @author  PineconePi(User)
  * @version V1.0.0
  * @date    17-June-2019
  * @brief  This document is used to drive W25Q128.
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
#ifndef _W25Q128_H_
#define _W25Q128_H_

#include "system.h"

#define CS P12

unsigned char SPI_Send_Reception(unsigned char Dat);
void ReadW25Q128Operation(unsigned long Addr);
void WriteW25Q128Operation(unsigned int Addr);
void EraseW25Q128Operation(unsigned int Addr);
void W25Q128_Write_SR(unsigned char Sr);
void ClearW25Q128WriteEnable();

#endif