/**
  ******************************************************************************
  * @file    digitaltube.h
  * @author  PineconePi
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This file is used to set up  digital tubes 
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
#ifndef _DIGITALTUBE_H_
#define _DIGITALTUBE_H_

#include "system.h"

#define ENABLE 1  //使能
#define DISABLE 0 //关闭

#define SMG1 1  //Nixie tube 1|数码管1
#define SMG2 2  //Nixie tube 2|数码管2


void Digitaltube_Enable(unsigned char SMGx,unsigned char Enable_Disable);//Enabling digital tube|使能数码管
void Digitaltube_Display(unsigned char Decimal_point_Enable,unsigned char dat);//Enables decimal points to display numbers (0-9)|使能小数点，显示数字（0-9）
#endif