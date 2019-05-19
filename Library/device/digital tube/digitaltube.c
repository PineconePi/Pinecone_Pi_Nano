/**
  ******************************************************************************
  * @file    digitaltube.c
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
#include "digitaltube.h"

unsigned char Segment_code[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};  //Digital Tube Segment Table|数码管段表

//========================================================================
// Function:void digitaltube_enable(unsigned char SMGx,unsigned char Enable_Disable)|函数: void digitaltube_enable(unsigned char SMGx,unsigned char Enable_Disable)
// Description:Enabling digital tube.|描述: 使能数码管。
// Parameters: SMGx: Digital Tube Sequence Number
//             Enable_Disable: Enable
// 参数: SMGx:数码管序号
//       Enable_Disable：是否使能
//       
// Return:|返回: 
// Version: ver1.0.0|版本: VER1.0.0
// Date: 2018-12-20|日期: 2018-12-20
// Author: Pinecone Pi|作者: PineconePi
// Note:|备注:
//	
//	
//	
//	
//	
//========================================================================
void Digitaltube_Enable(unsigned char SMGx,unsigned char Enable_Disable)
{
	if(SMGx==SMG1){
		if(Enable_Disable == ENABLE)
			P44 = 0;
		else if(Enable_Disable == DISABLE)
			P44 = 1;
	}
	else if(SMGx==SMG2)
	{
				if(Enable_Disable == ENABLE)
         P43 = 0;
		else if(Enable_Disable == DISABLE)
         P43 = 1;
	}
}
//========================================================================
// Function:void digitaltube_display(unsigned char Decimal_point_Enable,unsigned char dat)|函数: void digitaltube_display(unsigned char Decimal_point_Enable,unsigned char dat)
// Description:Whether to open decimal point, digital tube display.|描述: 是否开启小数点，数码管显示。
// Parameter: Decimal_point_Enable: Open decimal point or not
//            dat: Number of displays (0-9)
// 参数: Decimal_point_Enable:是否开启小数点
//       dat：显示的数 （0-9）
//       
// Return:|返回: 
// Version: ver1.0.0|版本: VER1.0.0
// Date: 2018-12-20|日期: 2018-12-20
// Author: Pinecone Pi|作者: PineconePi
// Note:|备注:
//	
//	
//	
//	
//	
//========================================================================
void Digitaltube_Display(unsigned char Decimal_point_Enable,unsigned char dat)
{
	if(Decimal_point_Enable == ENABLE)
	{
		P1 = (Segment_code[dat]|0x80);
	}
	else if(Decimal_point_Enable == DISABLE)
	{
		P1 = Segment_code[dat];
	}
}	