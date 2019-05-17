/**
  ******************************************************************************
  * @file    adc.h
  * @author  PineconePi(基于宏晶科技STC15库函数进行修改)
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This file is used to configure ADC
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
	
#ifndef	__ADC_H
#define	__ADC_H

#include	"system.h"

#define	ADC_P10		0x01	//IO Pin Px.0|IO引脚 Px.0
#define	ADC_P11		0x02	//IO Pin Px.1|IO引脚 Px.1
#define	ADC_P12		0x04	//IO Pin Px.2|IO引脚 Px.2
#define	ADC_P13		0x08	//IO Pin Px.3|IO引脚 Px.3
#define	ADC_P14		0x10	//IO Pin Px.4|IO引脚 Px.4
#define	ADC_P15		0x20	//IO Pin Px.5|IO引脚 Px.5
#define	ADC_P16		0x40	//IO Pin Px.6|IO引脚 Px.6
#define	ADC_P17		0x80	//IO Pin Px.7|IO引脚 Px.7
#define	ADC_P1_All	0xFF	//IO All Pin |IO所有引脚

#define ADC_90T		(3<<5)
#define ADC_180T	(2<<5)
#define ADC_360T	(1<<5)
#define ADC_540T	0
#define ADC_CH0		0
#define ADC_CH1		1
#define ADC_CH2		2
#define ADC_CH3		3
#define ADC_CH4		4
#define ADC_CH5		5
#define ADC_CH6		6
#define ADC_CH7		7

#define ADC_RES_H2L8	1
#define ADC_RES_H8L2	0

#define ENABLE  	1			//Enable|允许
#define DISABLE  	0			//Disable|关闭

#define PolityHigh  1	  //PolityHigh|高优先级
#define PolityLow  	0		//PolityLow|低优先级（默认）

typedef struct
{
	unsigned char	ADC_Px;			//Setting up IO for ADC|设置要做ADC的IO,	ADC_P10 ~ ADC_P17,ADC_P1_All
	unsigned char	ADC_Speed;		//ADC speed|ADC速度			ADC_90T,ADC_180T,ADC_360T,ADC_540T
	unsigned char	ADC_Power;		//ADC Power Allowance/Shutdown|ADC功率允许/关闭	ENABLE,DISABLE
	unsigned char	ADC_AdjResult;	//ADC Result Adjustment|ADC结果调整,	ADC_RES_H2L8,ADC_RES_H8L2
	unsigned char	ADC_Polity;		//Priority Setting|优先级设置	PolityHigh,PolityLow
	unsigned char	ADC_Interrupt;	//Interrupt enable|中断允许		ENABLE,DISABLE
} ADC_InitTypeDef;

void	ADC_Inilize(ADC_InitTypeDef *ADCx);
void	ADC_PowerControl(unsigned char pwr);
unsigned int		Get_ADC10bitResult(unsigned char channel);	//channel = 0~7

#endif
