/**
  ******************************************************************************
  * @file    mp3player.c
  * @author  PineconePi
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This article will be used for  driving  MP3 Player.
  * @License:GNU General Public License v3.0         
  ******************************************************************************
  * @attention
  *	include library/system/uart uart.c & uaet.h
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
#include "mp3player.h"
#define BRT             (65536 - MAIN_Fosc / 9600 / 4)
static unsigned char Send_buf[10] = {0};
bit busy;
char wptr;
char rptr;

//========================================================================
// 函数: void Mp3_Init()
// 描述: 初始化MP3控制串口（串口2）.
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
void Mp3_Init()	//初始化串口2
{
    S2CON = 0x10;
    T2L = BRT;
    T2H = BRT >> 8;
    AUXR = 0x14;
    wptr = 0x00;
    rptr = 0x00;
    busy = 0;
}

//========================================================================
// 函数: void DoSum( unsigned char *Str, unsigned char len)
// 描述: 求和校验.
// 参数:  
//       
//       
// 返回: 
// 版本: VER1.0.0
// 日期: 2018-12-20
// 作者: PineconePi
// 备注:
//		 和校验的思路如下
//            发送的指令，去掉起始和结束。将中间的6个字节进行累加，最后取反码
//             接收端就将接收到的一帧数据，去掉起始和结束。将中间的数据累加，再加上接收到的校验
//             字节。刚好为0.这样就代表接收到的数据完全正确。	
//		
//========================================================================
void DoSum( unsigned char *Str, unsigned char len)
{
    unsigned int xorsum = 0;
    unsigned char i;

    for(i=0; i<len; i++)
    {
        xorsum  = xorsum + Str[i];
    }
	xorsum     = 0 -xorsum;
	*(Str+i)   = (unsigned char)(xorsum >>8);
	*(Str+i+1) = (unsigned char)(xorsum & 0x00ff);
}

//========================================================================
// 函数: void sendacmd(unsigned char len)
// 描述: 串口发送一帧数据（串口2）.
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
void Uart2Send(char dat)
{
    while (busy);
    busy = 1;
    S2BUF = dat;
	  while((S2CON & S2TI)==0);
	  S2CON &=~S2TI;
	  busy = 0;
}
void sendacmd(unsigned char len)
{
    unsigned char i = 0 ;

    Uart2Send(0x7E); //起始
    for(i=0; i<len; i++)//数据
    {
		Uart2Send(Send_buf[i]) ;
    }
    Uart2Send(0xEF) ;//结束
}
//========================================================================
// 函数: void sendacmd(unsigned char len)
// 描述: 串口向外发送命令（串口2）.
// 参数:   CMD:表示控制指令，请查阅指令表，还包括查询的相关指令
//         feedback:是否需要应答[DISABLE:不需要应答，ENABLE:需要应答]
//         data:传送的参数
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
void SendCMD(unsigned char CMD ,unsigned char feedback , unsigned int dat)
{
    Send_buf[0] = 0xff;    //保留字节 
    Send_buf[1] = 0x06;    //长度
    Send_buf[2] = CMD;     //控制指令
    Send_buf[3] = feedback;//是否需要反馈
    Send_buf[4] = (unsigned char)(dat >> 8);//datah
    Send_buf[5] = (unsigned char)(dat);     //datal
    DoSum(&Send_buf[0],6);        //校验
	sendacmd(8);       //发送此帧数据
}
