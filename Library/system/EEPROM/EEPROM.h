/**
  ******************************************************************************
  * @file    eeprom.h
  * @author  PineconePi(基于宏晶科技STC15库函数进行修改)
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This file is used to Configure internal EEPROM 
  * @License:GNU General Public License v3.0         
  ******************************************************************************
  * @attention
  *Pinecone Pi NANO: The size of EEPROM is set by STC-ISP
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
#ifndef	__EEPROM_H
#define	__EEPROM_H

#include	"system.h"

#define WT_30M          0x80
#define WT_24M          0x81   //NANO内部IRC晶振频率24Mhz
#define WT_20M          0x82
#define WT_12M          0x83
#define WT_6M           0x84
#define WT_3M           0x85
#define WT_2M           0x86
#define WT_1M           0x87


void	DisableEEPROM(void);//关闭IAP功能
char EEPROM_read(int addr);//向地址addr中读取一个字节数据
void EEPROM_write(int addr, char dat);//向地址addr中写入一个字节数据dat
void EEPROM_Erase(int addr);//对地址addr进行数据擦出


#endif