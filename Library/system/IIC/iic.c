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
	/********************* The sample program is at the end of the iic.c file|示例程序在iic.c文件末尾************************/
	
#include "iic.h"
#include "intrins.h"
/********************* IIC port|IIC端口量************************/
sbit    SDA         =   P1^4;
sbit    SCL         =   P1^5;
/********************* IIC slave mode related variables|IIC从机模式相关变量************************/
bit isda;                                       //Equipment Address Mark|设备地址标志
bit isma;                                       //Storage address flag|存储地址标志
unsigned char addr;
unsigned char pdata buffer[256];
//========================================================================
// Function:void IIC_host_Slave_machine(unsigned char host_Slave_machine)|函数: void IIC_host_Slave_machine(unsigned char host_Slave_machine)
// Description:Set IIC mode.|描述: 设置IIC模式。
// Parameter:Host_Slave_machine: Host mode or slave mode|参数: host_Slave_machine：主机模式或从机模式
//       
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2018-12-20|日期: 2018-12-20
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
		I2CCFG = 0xe0;                              //Enabling I2C host mode|使能I2C主机模式
    I2CMSST = 0x00;
	}
	else if(host_Slave_machine==Slave_machine)
	{
		 P_SW2 = 0x80; 				//Operating hardware IIC register must set P_SW2 to 1|操作硬件IIC寄存器必须置P_SW2为1
		I2CCFG = 0x81;                              //Enabling I2C slave mode|使能I2C从机模式
    I2CSLADR = IIC_Slave_machine_address;       //Set the slave device address to 5A|设置从机设备地址为5A
    I2CSLST = 0x00;
    I2CSLCR = 0x00;                             //Prohibit slave mode interruption|禁止从机模式中断
	}
}
//========================================================================
// Function:void handle_Slave_machine()|函数: void handle_Slave_machine()
// Description:IIC slave mode processing function.|描述: IIC从机模式处理函数。
// Parameter:|参数:
//       
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2018-12-20|日期: 2018-12-20
// Author: Pinecone Pi|作者: PineconePi
// Note:|备注:
//	
//	
//	
//	
//	
//========================================================================
void handle_Slave_machine()
{
	  isda = 1;                                   //Initialization of user variables|用户变量初始化
    isma = 1;
    addr = 0;
    I2CTXD = buffer[addr];
	     if (I2CSLST & 0x40)
        {
            I2CSLST &= ~0x40;                   //Handling START events|处理START事件
        }
        else if (I2CSLST & 0x20)
        {
            I2CSLST &= ~0x20;                   //Handling RECV events|处理RECV事件
            if (isda)
            {
                isda = 0;                       //Handling RECV events (RECV DEVICE ADDR)|处理RECV事件（RECV DEVICE ADDR）
            }
            else if (isma)
            {
                isma = 0;                       //Handling RECV events (RECV MEMORY ADDR)|处理RECV事件（RECV MEMORY ADDR）
                addr = I2CRXD;
                I2CTXD = buffer[addr];
            }
            else
            {
                buffer[addr++] = I2CRXD;        //Handling RECV events (RECV DATA)|处理RECV事件（RECV DATA）
            }
        }
        else if (I2CSLST & 0x10)
        {
            I2CSLST &= ~0x10;                   //Handling SEND events|处理SEND事件
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
            I2CSLST &= ~0x08;                   //Handling STOP events|处理STOP事件
            isda = 1;
            isma = 1;
        }
	
}
//========================================================================
// Function:IIC Host Mode Related Processing Function|函数:  IIC主机模式相关处理函数
// Description:IIC host mode correlation processing function.|描述:  IIC主机模式相关处理函数。
// Parameter:|参数:
//       
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2018-12-20|日期: 2018-12-20
// Author: Pinecone Pi|作者: PineconePi
// Note:|备注:
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
    I2CMSCR = 0x01;                             //Send START command|发送START命令
    Wait();
}

void SendData(char dat)
{
    I2CTXD = dat;                               //Write data to data buffer|写数据到数据缓冲区
    I2CMSCR = 0x02;                             //Send SEND command|发送SEND命令
    Wait();
}

void RecvACK()
{
    I2CMSCR = 0x03;                             //发送读ACK命令
    Wait();
}

char RecvData()
{
    I2CMSCR = 0x04;                             //Send read ACK command|发送RECV命令
    Wait();
    return I2CRXD;
}

void SendACK()
{
    I2CMSST = 0x00;                             //Setting ACK Signal|设置ACK信号
    I2CMSCR = 0x05;                             //Send ACK commands|发送ACK命令
    Wait();
}

void SendNAK()
{
    I2CMSST = 0x01;                             //Setting NAK Signal|设置NAK信号
    I2CMSCR = 0x05;                             //Send ACK commands|发送ACK命令
    Wait();
}

void Stop()
{
    I2CMSCR = 0x06;                             //Send STOP command|发送STOP命令
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
// Function:IIC Host Mode Related Processing Function Example|函数:  IIC主机模式相关处理函数示例
// Description: IIC host mode correlation processing function example.|描述:  IIC主机模式相关处理函数示例。
// Parameter:|参数:     
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2018-12-20|日期: 2018-12-20
// Author: Pinecone Pi|作者: PineconePi
// Example:|示例：
//    P_SW2 = 0x80;																	
//    IIC_host_Slave_machine（host_machine);       //Setting up host mode|设置为主机模式
//    Start();                                    //Send Start Command|发送起始命令
//    SendData(0xa0);                             //Send Device Address + Write Command|发送设备地址+写命令
//    RecvACK();
//    SendData(0x00);                             //Send high bytes of storage address|发送存储地址高字节
//    RecvACK();
//    SendData(0x00);                             //Send Storage Address Low Byte|发送存储地址低字节
//    RecvACK();
//    SendData(0x12);                             //Write test data 1|写测试数据1
//    RecvACK();
//    SendData(0x78);                             //Write test data 2|写测试数据2
//    RecvACK();
//    Stop();                                     //Send stop command|发送停止命令
//    Delay();                                    //Waiting for the device to write data|等待设备写数据
//    Start();                                    //Send Start Command|发送起始命令
//    SendData(0xa0);                             //Send Device Address + Write Command|发送设备地址+写命令
//    RecvACK();
//    SendData(0x00);                             //Send high bytes of storage address|发送存储地址高字节
//    RecvACK();
//    SendData(0x00);                             //Send Storage Address Low Byte|发送存储地址低字节
//    RecvACK();
//    Start();                                    //Send Start Command|发送起始命令
//    SendData(0xa1);                             //Send device address + read command|发送设备地址+读命令
//    RecvACK();
//    P0 = RecvData();                            //Read data 1|读取数据1
//    SendACK();
//    P2 = RecvData();                            //读取数据2|读取数据2
//    SendNAK();
//    Stop();                                     //Send stop command|发送停止命令
//    P_SW2 = 0x00;
//========================================================================