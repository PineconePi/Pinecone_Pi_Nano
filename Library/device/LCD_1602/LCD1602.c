/**
  ******************************************************************************
  * @file    LCD1602.c
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
#include "LCD1602.h"

//========================================================================
// 函数: void LCD1602_operation(unsigned char Dat)
// 描述: LCD1602写入。
// 参数: Dat,数据
// 返回: none.
// 版本: VER1.0.0
// 日期: 2019-06-17
// 备注: 
//========================================================================
void LCD1602_operation(unsigned char Dat){
	unsigned int delay;
	RW=0;
	EN=1;
	DO=Dat;
	EN=0;
	for(delay=800;--delay;);
}
//========================================================================
// 函数: void LCD1602_Write(unsigned char Write_Type,unsigned char Dat)
// 描述: LCD1602写入函数。
// 参数: Write_Type,命令/数据 Dat,写入的数据
// 返回: none.
// 版本: VER1.0.0
// 日期: 2019-06-17
// 备注: 	向第二行第一列写入 0
//    		LCD1602_Write(Reg,0x0c);
//      	LCD1602_Write(Data,'0');
//========================================================================
void LCD1602_Write(unsigned char Write_Type,unsigned char Dat){
	RS=Write_Type;
  LCD1602_operation(Dat);
}
