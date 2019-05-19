/**
  ******************************************************************************
  * @file    PCA.c
  * @author  PineconePi(基于宏晶科技STC15库函数进行修改)
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This file is used to configure PAC
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
	
#include	"PCA.h"

bit		B_Capture0,B_Capture1,B_Capture2;
unsigned char		PCA0_mode,PCA1_mode,PCA2_mode;
unsigned int		CCAP0_tmp,PCA_Timer0;
unsigned int		CCAP1_tmp,PCA_Timer1;
unsigned int		CCAP2_tmp,PCA_Timer2;

unsigned int	PWM0_low;	//PWM0 output low level PCA clock pulse number, the user layer is invisible.|PWM输出低电平的PCA时钟脉冲个数, 用户层不可见。
unsigned int	PWM1_low;	//PWM1 output low level PCA clock pulse number, the user layer is invisible.|PWM输出低电平的PCA时钟脉冲个数, 用户层不可见。
unsigned int	PWM2_low;	//PWM2 output low level PCA clock pulse number, the user layer is invisible.|PWM输出低电平的PCA时钟脉冲个数, 用户层不可见。


/********************* PCA Interrupt Handling Function|PCA中断处理函数************************/
void	PCA_Handler (void) interrupt 7
{
	if(CCF0)		//PCA module 0 interrupt|PCA模块0中断
	{
		CCF0 = 0;		//Clear PCA module 0 interrupt flag|清PCA模块0中断标志
		if(P25)	CCAP0_tmp += PCA_Timer0;	//If the output is high level, the projection register is loaded with high level time length.|输出为高电平，则给影射寄存器装载高电平时间长度
		else	CCAP0_tmp += PWM0_low;	//If the output is low level, the projection register is loaded with low level time length.|输出为低电平，则给影射寄存器装载低电平时间长度
		CCAP0L = (unsigned char)CCAP0_tmp;			//Write the projection register to the capture register and write CCAP0L first.|将影射寄存器写入捕获寄存器，先写CCAP0L
		CCAP0H = (unsigned char)(CCAP0_tmp >> 8);	//Post write CCAP0H|后写CCAP0H
	}

	if(CCF1)	//PCA Module 1 Interruption|PCA模块1中断
	{
		CCF1 = 0;		//Clear the interrupt flag in PCA module 1|清PCA模块1中断标志
		if(P26)	CCAP1_tmp += PCA_Timer1;	//If the output is high level, the projection register is loaded with high level time length.|输出为高电平，则给影射寄存器装载高电平时间长度
		else	CCAP1_tmp += PWM1_low;	//If the output is low level, the projection register is loaded with low level time length.|输出为低电平，则给影射寄存器装载低电平时间长度
		CCAP1L = (unsigned char)CCAP1_tmp;			//Write the projection register to the capture register and write CCAP0L first.|将影射寄存器写入捕获寄存器，先写CCAP0L
		CCAP1H = (unsigned char)(CCAP1_tmp >> 8);	//Post write CCAP0H|后写CCAP0H
	}

	if(CCF2)	//PCA Module 2 Interruption|PCA模块2中断
	{
		CCF2 = 0;		//Clear the interrupt flag in PCA module 1|清PCA模块1中断标志
		if(P27)	CCAP2_tmp += PCA_Timer2;	//If the output is high level, the projection register is loaded with high level time length.|输出为高电平，则给影射寄存器装载高电平时间长度
		else	CCAP2_tmp += PWM2_low;	//If the output is low level, the projection register is loaded with low level time length.|输出为低电平，则给影射寄存器装载低电平时间长度
		CCAP2L = (unsigned char)CCAP2_tmp;			//Write the projection register to the capture register and write CCAP0L first.|将影射寄存器写入捕获寄存器，先写CCAP0L
		CCAP2H = (unsigned char)(CCAP2_tmp >> 8);	//Post write CCAP0H|后写CCAP0H
	}

/*	if(CF)	//PCA溢出中断
	{
		CF = 0;			//清PCA溢出中断标志
	}
*/
}
//========================================================================
// Function:void PWMn_Update(unsigned char PCA_id, unsigned int high)|函数: void PWMn_Update(unsigned char PCA_id, unsigned int high)
// Description:Update duty cycle data.|描述: 更新占空比数据。
// Parametric: high: duty cycle data, i.e. the number of PCA clock pulses with high level output from PWM.
// 参数: high: 	占空比数据，即PWM输出高电平的PCA时钟脉冲个数。    
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
void PWMn_Update(unsigned char PCA_id, unsigned int high)
{
	if(PCA_id == PCA0)
	{
		if(high > PWM0_HIGH_MAX)	high = PWM0_HIGH_MAX;	//If writing data larger than the maximum duty cycle, the maximum duty cycle is mandatory.|如果写入大于最大占空比数据，强制为最大占空比。
		if(high < PWM0_HIGH_MIN)	high = PWM0_HIGH_MIN;	//If less than the minimum duty cycle data is written, error code 2 is returned.|如果写入小于最小占空比数据，则返回错误代码2。
		CR = 0;							//Stop PCA.|停止PCA。
		PCA_Timer0 = high;				//When the data is in the correct range, the duty cycle register is loaded.|数据在正确范围，则装入占空比寄存器。
		PWM0_low = PWM0_DUTY - high;	//Calculate and save the number of PCA clock pulses with low PWM output level.|计算并保存PWM输出低电平的PCA时钟脉冲个数。
		CR = 1;							//Start PCA.|启动PCA。
	}
	else if(PCA_id == PCA1)
	{
		if(high > PWM1_HIGH_MAX)	high = PWM1_HIGH_MAX;	//If writing data larger than the maximum duty cycle, the maximum duty cycle is mandatory.|如果写入大于最大占空比数据，强制为最大占空比。
		if(high < PWM1_HIGH_MIN)	high = PWM1_HIGH_MIN;	//If less than the minimum duty cycle data is written, error code 2 is returned.如果写入小于最小占空比数据，则返回错误代码2。
		CR = 0;							//Stop PCA.|停止PCA。
		PCA_Timer1 = high;				//When the data is in the correct range, the duty cycle register is loaded.|数据在正确范围，则装入占空比寄存器。
		PWM1_low = PWM1_DUTY - high;	//Calculate and save the number of PCA clock pulses with low PWM output level.|计算并保存PWM输出低电平的PCA时钟脉冲个数。
		CR = 1;							//Start PCA.|启动PCA。
	}
	else if(PCA_id == PCA2)
	{
		if(high > PWM2_HIGH_MAX)		high = PWM2_HIGH_MAX;	//If writing data larger than the maximum duty cycle, the maximum duty cycle is mandatory.|如果写入大于最大占空比数据，强制为最大占空比。
		if(high < PWM2_HIGH_MIN)		high = PWM2_HIGH_MIN;	//If less than the minimum duty cycle data is written, error code 2 is returned.|如果写入小于最小占空比数据，则返回错误代码2。
		CR = 0;						//Stop PCA.|停止PCA。
		PCA_Timer2 = high;						//When the data is in the correct range, the duty cycle register is loaded.|数据在正确范围，则装入占空比寄存器。
		PWM2_low = PWM2_DUTY - high;				//Calculate and save the number of PCA clock pulses with low PWM output level.|计算并保存PWM输出低电平的PCA时钟脉冲个数。
		CR = 1;						//Start PCA.|启动PCA。
	}
}


//========================================================================
// Function:UpdatePwm(unsigned char PCA_id, unsigned char pwm_value)|函数: UpdatePwm(unsigned char PCA_id, unsigned char pwm_value)
// Description:Update PWM values.|描述: 更新PWM值.
// Parameters: PCA_id: PCA serial number. Values PCA0, PCA1, PCA2, PCA_Counter
// 			   pwm_value: PWM value, which is the time when the low level is output. 
// 参数: PCA_id: PCA序号. 取值 PCA0,PCA1,PCA2,PCA_Counter
//       pwm_value: pwm值, 这个值是输出低电平的时间.
//       
// Return:返回: 
// Version:VER1.0.0|版本: VER1.0.0
// Date:2018-12-20|日期: 2018-12-20
// Author: Pinecone Pi|作者: PineconePi
// Note:备注:
//	
//	
//	
//	
//	
//========================================================================
void	UpdatePwm(unsigned char PCA_id, unsigned char pwm_value)
{
	if(PCA_id == PCA0)		CCAP0H = pwm_value;
	else if(PCA_id == PCA1)	CCAP1H = pwm_value;
	else if(PCA_id == PCA2)	CCAP2H = pwm_value;
}

//========================================================================
// Function:void	PCA_Init(PCA_id, PCA_InitTypeDef *PCAx)|函数: void	PCA_Init(PCA_id, PCA_InitTypeDef *PCAx)
// Description:PCA initialization program.|描述: PCA初始化程序. 
// Parameters: PCA_id: PCA serial number. Values PCA0, PCA1, PCA2, PCA_Counter
//             PCAx: Structural parameters, please refer to the structure definition in PCA.h.
// 参数: PCA_id: PCA序号. 取值 PCA0,PCA1,PCA2,PCA_Counter
//       PCAx: 结构参数,请参考PCA.h里的结构体定义.
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
void	PCA_Init(unsigned char PCA_id, PCA_InitTypeDef *PCAx)
{
	if(PCA_id > PCA_Counter)	return;		//ID error|id错误

	if(PCA_id == PCA_Counter)			//Setting up Public Counter|设置公用Counter
	{
		CR = 0;
		CH = 0;
		CL = 0;
		P_SW1 = PCAx->PCA_IoUse;			//Toggle IO port|切换IO口
		CMOD  = (CMOD  & ~(7<<1)) | PCAx->PCA_Clock;			//Selecting Clock Source|选择时钟源
		CMOD  = (CMOD  & ~1) | (PCAx->PCA_Interrupt_Mode & 1);	//ECF
		if(PCAx->PCA_Polity == PolityHigh)		PPCA = 1;	//High priority interrupt|高优先级中断
		else									PPCA = 0;	//Low priority interrupt|低优先级中断
		CR = 1;
		return;
	}

	PCAx->PCA_Interrupt_Mode &= (3<<4) + 1;
	if(PCAx->PCA_Mode >= PCA_Mode_SoftTimer)	PCAx->PCA_Interrupt_Mode &= ~(3<<4);

	if(PCA_id == PCA0)
	{
		CCAPM0    = PCAx->PCA_Mode | PCAx->PCA_Interrupt_Mode;	//Work mode, interrupt mode|工作模式, 中断模式
		PCA_PWM0  = (PCA_PWM0 & ~(3<<6)) | PCAx->PCA_PWM_Wide;	//PWM width|PWM宽度

		PCA_Timer0 = PCAx->PCA_Value;
		B_Capture0 = 0;
		PCA0_mode = PCAx->PCA_Mode;
		CCAP0_tmp = PCA_Timer0;
		CCAP0L = (unsigned char)CCAP0_tmp;			//Write the projection register to the capture register and write CCAP0L first.|将影射寄存器写入捕获寄存器，先写CCAP0L
		CCAP0H = (unsigned char)(CCAP0_tmp >> 8);	//Post write CCAP0H|后写CCAP0H
	}
	if(PCA_id == PCA1)
	{
		CCAPM1    = PCAx->PCA_Mode | PCAx->PCA_Interrupt_Mode;
		PCA_PWM1  = (PCA_PWM1 & ~(3<<6)) | PCAx->PCA_PWM_Wide;

		PCA_Timer1 = PCAx->PCA_Value;
		B_Capture1 = 0;
		PCA1_mode = PCAx->PCA_Mode;
		CCAP1_tmp = PCA_Timer1;
		CCAP1L = (unsigned char)CCAP1_tmp;			//Write the projection register to the capture register and write CCAP0L first.|将影射寄存器写入捕获寄存器，先写CCAP0L
		CCAP1H = (unsigned char)(CCAP1_tmp >> 8);	//Post write CCAP0H|后写CCAP0H
	}
	if(PCA_id == PCA2)
	{
		CCAPM2    = PCAx->PCA_Mode | PCAx->PCA_Interrupt_Mode;
		PCA_PWM2  = (PCA_PWM2 & ~(3<<6)) | PCAx->PCA_PWM_Wide;

		PCA_Timer2 = PCAx->PCA_Value;
		B_Capture2 = 0;
		PCA2_mode = PCAx->PCA_Mode;
		CCAP2_tmp = PCA_Timer2;
		CCAP2L = (unsigned char)CCAP2_tmp;			//Write the projection register to the capture register and write CCAP0L first.|将影射寄存器写入捕获寄存器，先写CCAP0L
		CCAP2H = (unsigned char)(CCAP2_tmp >> 8);	//Post write CCAP0H|后写CCAP0H
	}
}

