/**
  ******************************************************************************
  * @file    eeprom.c
  * @author  PineconePi
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
	
#include "system.h"
#include "eeprom.h"
#include "intrins.h"

//========================================================================
// 函数: void	DisableEEPROM(void)
// 描述: 关闭IAP功能。
// 参数: 
//       
//       
// 返回: 
// 版本: VER1.0.0
// 日期: 2018-12-20
// 作者: PineconePi
// 备注:
//	
//	
//	
//	
//	
//========================================================================
void	DisableEEPROM(void)
{
    IAP_CONTR = 0;                              //关闭IAP功能
    IAP_CMD = 0;                                //清除命令寄存器
    IAP_TRIG = 0;                               //清除触发寄存器
    IAP_ADDRH = 0x80;                           //将地址设置到非IAP区域
    IAP_ADDRL = 0;
}

//========================================================================
// 函数: char EEPROM_read(int addr)
// 描述: 向地址addr中读取一个字节数据。
// 参数: addr:读取地址
//       
//       
// 返回: addr地址中一个字节的数据
// 版本: VER1.0.0
// 日期: 2018-12-20
// 作者: PineconePi
// 备注:
//	
//	
//	
//	
//	
//========================================================================

char EEPROM_read(int addr)
{
    char dat;

    IAP_CONTR = WT_24M;                         //使能IAP
    IAP_CMD = 1;                                //设置IAP读命令
    IAP_ADDRL = addr;                           //设置IAP低地址
    IAP_ADDRH = addr >> 8;                      //设置IAP高地址
    IAP_TRIG = 0x5a;                            //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                            //写触发命令(0xa5)
    _nop_();
    dat = IAP_DATA;                             //读IAP数据
    DisableEEPROM();                                  //关闭IAP功能

    return dat;
}

//========================================================================
// 函数:void EEPROM_Erase(int addr)
// 描述: 对地址addr进行数据擦出。
// 参数: addr:要擦除的EEPROM的地址.
//       
//       
// 返回: 
// 版本: VER1.0.0
// 日期: 2018-12-20
// 作者: PineconePi
// 备注:
//	
//	
//	
//	
//	
//========================================================================
void EEPROM_Erase(int addr)
{
    IAP_CONTR = WT_24M;                         //使能IAP
    IAP_CMD = 3;                                //设置IAP擦除命令
    IAP_ADDRL = addr;                           //设置IAP低地址
    IAP_ADDRH = addr >> 8;                      //设置IAP高地址
    IAP_TRIG = 0x5a;                            //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                            //写触发命令(0xa5)
    _nop_();                                    //
    DisableEEPROM();                                   //关闭IAP功能
}

//========================================================================
// 函数:void EEPROM_write(int addr, char dat)
// 描述: 向地址addr中写入一个字节数据dat。
// 参数: addr:要写入的EEPROM的地址.
//       dat:写入的数据
//       
// 返回: 
// 版本: VER1.0.0
// 日期: 2018-12-20
// 作者: PineconePi
// 备注:
//	
//	
//	
//	
//	
//========================================================================
void EEPROM_write(int addr, char dat)
{
    IAP_CONTR = WT_24M;                         //使能IAP
    IAP_CMD = 2;                                //设置IAP写命令
    IAP_ADDRL = addr;                           //设置IAP低地址
    IAP_ADDRH = addr >> 8;                      //设置IAP高地址
    IAP_DATA = dat;                             //写IAP数据
    IAP_TRIG = 0x5a;                            //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                            //写触发命令(0xa5)
    _nop_();
    DisableEEPROM();                                  //关闭IAP功能
}

