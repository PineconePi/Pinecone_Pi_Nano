/**
  ******************************************************************************
  * @file    gpio.c
  * @author  PineconePi(基于宏晶科技STC15库函数进行修改)
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This document is used for GPIO configuration
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
  ******************************************************************************
	**/
	
#include	"GPIO.h"


//========================================================================
// Function:unsigned char	GPIO_Inilize(unsigned char GPIO, GPIO_InitTypeDef *GPIOx)|函数: unsigned char	GPIO_Inilize(unsigned char GPIO, GPIO_InitTypeDef *GPIOx)
// Description:Initialize the IO port.|描述: 初始化IO口.
// Parameter:: GPIO：GPIO_P0:P0 pins (8)，GPIO_P1:P1 pins (8)，GPIO_P2:P2 pins (8)，GPIO_P3:P3 pins (8)，
//             GPIO_P4:P4 pins (8)，GPIO_P5:P5 pins (8)，
//			   GPIOx: For structural parameters, please refer to the structure description in gpio.h..
// 参数: GPIO：GPIO_P0:P0引脚（8个），GPIO_P1:P1引脚（8个），GPIO_P2:P2引脚（8个），GPIO_P3:P3引脚（8个），
//             GPIO_P4:P4引脚（8个），GPIO_P5:P5引脚（8个），
//       GPIOx: 结构参数,请参考gpio.h里的结构体说明.
// Return:Successful return 0, empty return 1, error return 2.|返回: 成功返回0, 空操作返回1,错误返回2.
// Version:VER1.0.0|版本: VER1.0.0
// Date:2018-12-20|日期: 2018-12-20
// Note: Set P ^ 0 and P ^ 1 as up-pull quasi-bidirectional ports by following steps
//       GPIO_InitTypeDef GPIO_InitTypeDef;
//		 GPIO_InitTypeDef.Mode = GPIO_PullUp;//Up-drawing alignment bi-directional port
//       GPIO_InitTypeDef.Pin = GPIO_Pin_0|GPIO_Pin_1;//Configuration of IO pins Px.0 and Px.1 at the same time.1
//		 GPIO_Inilize(GPIO_P0 ,&GPIO_InitTypeDef);//IO pin P 0.0
// 备注: 通过以下步骤将P0^0和P0^1设置为上拉准双向口
//       GPIO_InitTypeDef GPIO_InitTypeDef;
//		 GPIO_InitTypeDef.Mode = GPIO_PullUp;//上拉准双向口
//       GPIO_InitTypeDef.Pin = GPIO_Pin_0|GPIO_Pin_1;//同时配置IO引脚 Px.0与Px.1
//		 GPIO_Inilize(GPIO_P0 ,&GPIO_InitTypeDef);//IO引脚 P0.0
//========================================================================
unsigned char	GPIO_Inilize(unsigned char GPIO, GPIO_InitTypeDef *GPIOx)
{
	if(GPIO > GPIO_P5)				return 1;	//Empty operation
	if(GPIOx->Mode > GPIO_OUT_PP)	return 2;	//error
	if(GPIO == GPIO_P0)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P0M1 &= ~GPIOx->Pin,	P0M0 &= ~GPIOx->Pin;	 //Up-drawing alignment bi-directional port|上拉准双向口
		if(GPIOx->Mode == GPIO_HighZ)		P0M1 |=  GPIOx->Pin,	P0M0 &= ~GPIOx->Pin;	 //Floating input|浮空输入
		if(GPIOx->Mode == GPIO_OUT_OD)		P0M1 |=  GPIOx->Pin,	P0M0 |=  GPIOx->Pin;	 //Open drain output|开漏输出
		if(GPIOx->Mode == GPIO_OUT_PP)		P0M1 &= ~GPIOx->Pin,	P0M0 |=  GPIOx->Pin;	 //push-pull|推挽输出
	}
	if(GPIO == GPIO_P1)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P1M1 &= ~GPIOx->Pin,	P1M0 &= ~GPIOx->Pin;	 //Up-drawing alignment bi-directional port|上拉准双向口
		if(GPIOx->Mode == GPIO_HighZ)		P1M1 |=  GPIOx->Pin,	P1M0 &= ~GPIOx->Pin;	 //Floating input|浮空输入
		if(GPIOx->Mode == GPIO_OUT_OD)		P1M1 |=  GPIOx->Pin,	P1M0 |=  GPIOx->Pin;	 //Open drain output|开漏输出
		if(GPIOx->Mode == GPIO_OUT_PP)		P1M1 &= ~GPIOx->Pin,	P1M0 |=  GPIOx->Pin;	 //push-pull|推挽输出
	}
	if(GPIO == GPIO_P2)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P2M1 &= ~GPIOx->Pin,	P2M0 &= ~GPIOx->Pin;	 //Up-drawing alignment bi-directional port|上拉准双向口
		if(GPIOx->Mode == GPIO_HighZ)		P2M1 |=  GPIOx->Pin,	P2M0 &= ~GPIOx->Pin;	 //Floating input|浮空输入
		if(GPIOx->Mode == GPIO_OUT_OD)		P2M1 |=  GPIOx->Pin,	P2M0 |=  GPIOx->Pin;	 //Open drain output|开漏输出
		if(GPIOx->Mode == GPIO_OUT_PP)		P2M1 &= ~GPIOx->Pin,	P2M0 |=  GPIOx->Pin;	 //push-pull|推挽输出
	}
	if(GPIO == GPIO_P3)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P3M1 &= ~GPIOx->Pin,	P3M0 &= ~GPIOx->Pin;	 //Up-drawing alignment bi-directional port|上拉准双向口
		if(GPIOx->Mode == GPIO_HighZ)		P3M1 |=  GPIOx->Pin,	P3M0 &= ~GPIOx->Pin;	 //Floating input|浮空输入
		if(GPIOx->Mode == GPIO_OUT_OD)		P3M1 |=  GPIOx->Pin,	P3M0 |=  GPIOx->Pin;	 //Open drain output|开漏输出
		if(GPIOx->Mode == GPIO_OUT_PP)		P3M1 &= ~GPIOx->Pin,	P3M0 |=  GPIOx->Pin;	 //push-pull|推挽输出
	}
	if(GPIO == GPIO_P4)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P4M1 &= ~GPIOx->Pin,	P4M0 &= ~GPIOx->Pin;	 //Up-drawing alignment bi-directional port|上拉准双向口
		if(GPIOx->Mode == GPIO_HighZ)		P4M1 |=  GPIOx->Pin,	P4M0 &= ~GPIOx->Pin;	 //Floating input|浮空输入
		if(GPIOx->Mode == GPIO_OUT_OD)		P4M1 |=  GPIOx->Pin,	P4M0 |=  GPIOx->Pin;	 //Open drain output|开漏输出
		if(GPIOx->Mode == GPIO_OUT_PP)		P4M1 &= ~GPIOx->Pin,	P4M0 |=  GPIOx->Pin;	 //push-pull|推挽输出
	}
	if(GPIO == GPIO_P5)
	{
		if(GPIOx->Mode == GPIO_PullUp)		P5M1 &= ~GPIOx->Pin,	P5M0 &= ~GPIOx->Pin;	 //Up-drawing alignment bi-directional port|上拉准双向口
		if(GPIOx->Mode == GPIO_HighZ)		P5M1 |=  GPIOx->Pin,	P5M0 &= ~GPIOx->Pin;	 //Floating input|浮空输入
		if(GPIOx->Mode == GPIO_OUT_OD)		P5M1 |=  GPIOx->Pin,	P5M0 |=  GPIOx->Pin;	 //Open drain output|开漏输出
		if(GPIOx->Mode == GPIO_OUT_PP)		P5M1 &= ~GPIOx->Pin,	P5M0 |=  GPIOx->Pin;	 //push-pull|推挽输出
	}
	return 0;	//Success|成功
}
