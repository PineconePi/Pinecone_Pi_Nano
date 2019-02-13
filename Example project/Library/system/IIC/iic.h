/**
  ******************************************************************************
  * @file    iic.h
  * @author  PineconePi
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This file is used to Configure hardware IIC 
  * @License:GNU General Public License v3.0         
  ******************************************************************************
  * @attention
  *To operate IIC-related registers in host mode, P_SW2 = 0x80 is required. 
  *After  settings are completed, you must P_SW2 = 0x00
  *The sample program is at the end of the file iic.c
  *  
  * 
  * 
  * 
  * 
  *
  * 
  ******************************************************************************
	**/
	/********************* 示例程序在iic.c文件末尾************************/
#ifndef _IIC_H_
#define _IIC_H_

#include "system.h"


#define host_machine 0  //主机模式
#define Slave_machine 1 //从机模式

#define IIC_Slave_machine_address 0x5a //从机设备地址为5A

 void IIC_host_Slave_machine(unsigned char host_Slave_machine);//设置IIC模式（主机模式，从机模式）
 void handle_Slave_machine();//从机模式处理函数
 /********************* IIC主机模式相关处理函数************************/
 void Wait();
 void Start();
 void SendData(char dat);
 void RecvACK();
 char RecvData();
 void SendACK();
 void SendNAK();
 void Stop();
 void wait_device();
#endif