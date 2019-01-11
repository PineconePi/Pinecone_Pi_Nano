/**
  ******************************************************************************
  * @file    iic.c
  * @author  PineconePi
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This file is used to Configure hardware IIC 
  * @License:GNU General Public License v3.0         
  ******************************************************************************
  * @attention
  *To operate IIC-related registers in host mode, P_SW2 = 0x80 is required. 
  *After  settings are completed, you must P_SW2 = 0x00
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
	/********************* 示例程序在iic.c文件末尾************************/
	
#include "iic.h"
#include "intrins.h"
/********************* IIC端口量************************/
sbit    SDA         =   P1^4;
sbit    SCL         =   P1^5;
/********************* IIC从机模式相关变量************************/
bit isda;                                       //设备地址标志
bit isma;                                       //存储地址标志
unsigned char addr;
unsigned char pdata buffer[256];
//========================================================================
// 函数: void IIC_host_Slave_machine(unsigned char host_Slave_machine)
// 描述: 设置IIC模式。
// 参数: host_Slave_machine：主机模式或从机模式
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
void IIC_host_Slave_machine(unsigned char host_Slave_machine)
{
	if(host_Slave_machine==host_machine)
	{
		I2CCFG = 0xe0;                              //使能I2C主机模式
    I2CMSST = 0x00;
	}
	else if(host_Slave_machine==Slave_machine)
	{
		 P_SW2 = 0x80; 				//操作硬件IIC寄存器必须置P_SW2为1
		I2CCFG = 0x81;                              //使能I2C从机模式
    I2CSLADR = IIC_Slave_machine_address;       //设置从机设备地址为5A
    I2CSLST = 0x00;
    I2CSLCR = 0x00;                             //禁止从机模式中断
	}
}
//========================================================================
// 函数: void handle_Slave_machine()
// 描述: IIC从机模式处理函数。
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
void handle_Slave_machine()
{
	  isda = 1;                                   //用户变量初始化
    isma = 1;
    addr = 0;
    I2CTXD = buffer[addr];
	     if (I2CSLST & 0x40)
        {
            I2CSLST &= ~0x40;                   //处理START事件
        }
        else if (I2CSLST & 0x20)
        {
            I2CSLST &= ~0x20;                   //处理RECV事件
            if (isda)
            {
                isda = 0;                       //处理RECV事件（RECV DEVICE ADDR）
            }
            else if (isma)
            {
                isma = 0;                       //处理RECV事件（RECV MEMORY ADDR）
                addr = I2CRXD;
                I2CTXD = buffer[addr];
            }
            else
            {
                buffer[addr++] = I2CRXD;        //处理RECV事件（RECV DATA）
            }
        }
        else if (I2CSLST & 0x10)
        {
            I2CSLST &= ~0x10;                   //处理SEND事件
            if (I2CSLST & 0x02)
            {
                I2CTXD = 0xff;
            }
            else
            {
                I2CTXD = buffer[++addr];
            }
        }
        else if (I2CSLST & 0x08)
        {
            I2CSLST &= ~0x08;                   //处理STOP事件
            isda = 1;
            isma = 1;
        }
	
}
//========================================================================
// 函数:  IIC主机模式相关处理函数
// 描述:  IIC主机模式相关处理函数。
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
void Wait()
{
    while (!(I2CMSST & 0x40));
    I2CMSST &= ~0x40;
}

void Start()
{
    I2CMSCR = 0x01;                             //发送START命令
    Wait();
}

void SendData(char dat)
{
    I2CTXD = dat;                               //写数据到数据缓冲区
    I2CMSCR = 0x02;                             //发送SEND命令
    Wait();
}

void RecvACK()
{
    I2CMSCR = 0x03;                             //发送读ACK命令
    Wait();
}

char RecvData()
{
    I2CMSCR = 0x04;                             //发送RECV命令
    Wait();
    return I2CRXD;
}

void SendACK()
{
    I2CMSST = 0x00;                             //设置ACK信号
    I2CMSCR = 0x05;                             //发送ACK命令
    Wait();
}

void SendNAK()
{
    I2CMSST = 0x01;                             //设置NAK信号
    I2CMSCR = 0x05;                             //发送ACK命令
    Wait();
}

void Stop()
{
    I2CMSCR = 0x06;                             //发送STOP命令
    Wait();
}

void wait_device()
{
    int i;

    for (i=0; i<3000; i++)
    {
        _nop_();
        _nop_();
        _nop_();
        _nop_();
    }
}
//========================================================================
// 函数:  IIC主机模式相关处理函数示例
// 描述:  IIC主机模式相关处理函数示例。
// 参数:     
// 返回: 
// 版本: VER1.0.0
// 日期: 2018-12-20
// 作者: PineconePi
// 示例：
//    P_SW2 = 0x80;																	
//    IIC_host_Slave_machine（host_machine);       //设置为主机模式
//    Start();                                    //发送起始命令
//    SendData(0xa0);                             //发送设备地址+写命令
//    RecvACK();
//    SendData(0x00);                             //发送存储地址高字节
//    RecvACK();
//    SendData(0x00);                             //发送存储地址低字节
//    RecvACK();
//    SendData(0x12);                             //写测试数据1
//    RecvACK();
//    SendData(0x78);                             //写测试数据2
//    RecvACK();
//    Stop();                                     //发送停止命令
//    Delay();                                    //等待设备写数据
//    Start();                                    //发送起始命令
//    SendData(0xa0);                             //发送设备地址+写命令
//    RecvACK();
//    SendData(0x00);                             //发送存储地址高字节
//    RecvACK();
//    SendData(0x00);                             //发送存储地址低字节
//    RecvACK();
//    Start();                                    //发送起始命令
//    SendData(0xa1);                             //发送设备地址+读命令
//    RecvACK();
//    P0 = RecvData();                            //读取数据1
//    SendACK();
//    P2 = RecvData();                            //读取数据2
//    SendNAK();
//    Stop();                                     //发送停止命令
//    P_SW2 = 0x00;
//========================================================================