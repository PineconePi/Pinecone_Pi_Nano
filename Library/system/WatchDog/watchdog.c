/**
  ******************************************************************************
  * @file    watchdog.c
  * @author  PineconePi
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This file is used to Configure internal WATCHDOG 
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
#include "watchdog.h"

//========================================================================
// Function:void setup_watchdog(unsigned char WDT_MODE_x)|函数: void setup_watchdog(unsigned char WDT_MODE_x)
// Description:|描述: Set and make the dog visible.|设置并使能看门狗。
// Parameter: WDT_MODE_x: Setting Watchdog Overflow Time
// 参数: WDT_MODE_x:对看门狗溢出时间进行设置
//       
//       
// Return:返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2018-12-20|日期: 2018-12-20
// Author: Pinecone Pi作者: PineconePi
// Note:|备注:
//	
//	
//	
//	
//	
//========================================================================
void setup_watchdog(unsigned char WDT_MODE_x)
{
    WDT_CONTR = WDT_MODE_x;            //Enabling and setting watchdogs|使能并设置看门狗
}	
//========================================================================
// Function:off_watchdog()|函数: off_watchdog()
// Description:Close the watchdog|描述: 关闭看门狗。
// Parameter:|参数: 
//       
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2018-12-20||日期: 2018-12-20
// Author: Pinecone Pi|作者: PineconePi
// Note:|备注:
//	
//	
//	
//	
//	
//========================================================================
void off_watchdog()
{
	WDT_CONTR = 0x00; //Close the watchdog|关闭看门狗
}
//========================================================================
// Function:void feed_dog()|函数: void feed_dog()
// Description:Feed the watchdog, or the system will be reset.|描述: //喂看门狗,否则系统复位。
// Parameter:|参数:  
//       
//       
// Return:|返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2018-12-20||日期: 2018-12-20
// Author: Pinecone Pi|作者: PineconePi
// Note:|备注:
//	
//	
//	
//	
//	
//========================================================================
void feed_dog()
{
	WDT_CONTR |= 0x10;                      //Feed the watchdog, or the system will be reset.|喂看门狗,否则系统复位
}