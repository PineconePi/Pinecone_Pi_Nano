/**
  ******************************************************************************
  * @file    PCA.c
  * @author  PineconePi
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

unsigned int	PWM0_low;	//PWM输出低电平的PCA时钟脉冲个数, 用户层不可见。
unsigned int	PWM1_low;	//PWM输出低电平的PCA时钟脉冲个数, 用户层不可见。
unsigned int	PWM2_low;	//PWM输出低电平的PCA时钟脉冲个数, 用户层不可见。


/********************* PCA中断处理函数************************/
void	PCA_Handler (void) interrupt 7
{
	if(CCF0)		//PCA模块0中断
	{
		CCF0 = 0;		//清PCA模块0中断标志
		if(P25)	CCAP0_tmp += PCA_Timer0;	//输出为高电平，则给影射寄存器装载高电平时间长度
		else	CCAP0_tmp += PWM0_low;	//输出为低电平，则给影射寄存器装载低电平时间长度
		CCAP0L = (unsigned char)CCAP0_tmp;			//将影射寄存器写入捕获寄存器，先写CCAP0L
		CCAP0H = (unsigned char)(CCAP0_tmp >> 8);	//后写CCAP0H
	}

	if(CCF1)	//PCA模块1中断
	{
		CCF1 = 0;		//清PCA模块1中断标志
		if(P26)	CCAP1_tmp += PCA_Timer1;	//输出为高电平，则给影射寄存器装载高电平时间长度
		else	CCAP1_tmp += PWM1_low;	//输出为低电平，则给影射寄存器装载低电平时间长度
		CCAP1L = (unsigned char)CCAP1_tmp;			//将影射寄存器写入捕获寄存器，先写CCAP0L
		CCAP1H = (unsigned char)(CCAP1_tmp >> 8);	//后写CCAP0H
	}

	if(CCF2)	//PCA模块2中断
	{
		CCF2 = 0;		//清PCA模块1中断标志
		if(P27)	CCAP2_tmp += PCA_Timer2;	//输出为高电平，则给影射寄存器装载高电平时间长度
		else	CCAP2_tmp += PWM2_low;	//输出为低电平，则给影射寄存器装载低电平时间长度
		CCAP2L = (unsigned char)CCAP2_tmp;			//将影射寄存器写入捕获寄存器，先写CCAP0L
		CCAP2H = (unsigned char)(CCAP2_tmp >> 8);	//后写CCAP0H
	}

/*	if(CF)	//PCA溢出中断
	{
		CF = 0;			//清PCA溢出中断标志
	}
*/
}
//========================================================================
// 函数: void PWMn_Update(unsigned char PCA_id, unsigned int high)
// 描述: 更新占空比数据。
// 参数: high: 	占空比数据，即PWM输出高电平的PCA时钟脉冲个数。
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
void PWMn_Update(unsigned char PCA_id, unsigned int high)
{
	if(PCA_id == PCA0)
	{
		if(high > PWM0_HIGH_MAX)	high = PWM0_HIGH_MAX;	//如果写入大于最大占空比数据，强制为最大占空比。
		if(high < PWM0_HIGH_MIN)	high = PWM0_HIGH_MIN;	//如果写入小于最小占空比数据，则返回错误代码2。
		CR = 0;							//停止PCA。
		PCA_Timer0 = high;				//数据在正确范围，则装入占空比寄存器。
		PWM0_low = PWM0_DUTY - high;	//计算并保存PWM输出低电平的PCA时钟脉冲个数。
		CR = 1;							//启动PCA。
	}
	else if(PCA_id == PCA1)
	{
		if(high > PWM1_HIGH_MAX)	high = PWM1_HIGH_MAX;	//如果写入大于最大占空比数据，强制为最大占空比。
		if(high < PWM1_HIGH_MIN)	high = PWM1_HIGH_MIN;	//如果写入小于最小占空比数据，则返回错误代码2。
		CR = 0;							//停止PCA。
		PCA_Timer1 = high;				//数据在正确范围，则装入占空比寄存器。
		PWM1_low = PWM1_DUTY - high;	//计算并保存PWM输出低电平的PCA时钟脉冲个数。
		CR = 1;							//启动PCA。
	}
	else if(PCA_id == PCA2)
	{
		if(high > PWM2_HIGH_MAX)		high = PWM2_HIGH_MAX;	//如果写入大于最大占空比数据，强制为最大占空比。
		if(high < PWM2_HIGH_MIN)		high = PWM2_HIGH_MIN;	//如果写入小于最小占空比数据，则返回错误代码2。
		CR = 0;						//停止PCA。
		PCA_Timer2 = high;						//数据在正确范围，则装入占空比寄存器。
		PWM2_low = PWM2_DUTY - high;				//计算并保存PWM输出低电平的PCA时钟脉冲个数。
		CR = 1;						//启动PCA。
	}
}


//========================================================================
// 函数: UpdatePwm(unsigned char PCA_id, unsigned char pwm_value)
// 描述: 更新PWM值. 
// 参数: PCA_id: PCA序号. 取值 PCA0,PCA1,PCA2,PCA_Counter
//       pwm_value: pwm值, 这个值是输出低电平的时间.
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
void	UpdatePwm(unsigned char PCA_id, unsigned char pwm_value)
{
	if(PCA_id == PCA0)		CCAP0H = pwm_value;
	else if(PCA_id == PCA1)	CCAP1H = pwm_value;
	else if(PCA_id == PCA2)	CCAP2H = pwm_value;
}

//========================================================================
// 函数: void	PCA_Init(PCA_id, PCA_InitTypeDef *PCAx)
// 描述: PCA初始化程序. 
// 参数: PCA_id: PCA序号. 取值 PCA0,PCA1,PCA2,PCA_Counter
//       PCAx: 结构参数,请参考PCA.h里的结构体定义.
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
void	PCA_Init(unsigned char PCA_id, PCA_InitTypeDef *PCAx)
{
	if(PCA_id > PCA_Counter)	return;		//id错误

	if(PCA_id == PCA_Counter)			//设置公用Counter
	{
		CR = 0;
		CH = 0;
		CL = 0;
		P_SW1 = PCAx->PCA_IoUse;			//切换IO口
		CMOD  = (CMOD  & ~(7<<1)) | PCAx->PCA_Clock;			//选择时钟源
		CMOD  = (CMOD  & ~1) | (PCAx->PCA_Interrupt_Mode & 1);	//ECF
		if(PCAx->PCA_Polity == PolityHigh)		PPCA = 1;	//高优先级中断
		else									PPCA = 0;	//低优先级中断
		CR = 1;
		return;
	}

	PCAx->PCA_Interrupt_Mode &= (3<<4) + 1;
	if(PCAx->PCA_Mode >= PCA_Mode_SoftTimer)	PCAx->PCA_Interrupt_Mode &= ~(3<<4);

	if(PCA_id == PCA0)
	{
		CCAPM0    = PCAx->PCA_Mode | PCAx->PCA_Interrupt_Mode;	//工作模式, 中断模式
		PCA_PWM0  = (PCA_PWM0 & ~(3<<6)) | PCAx->PCA_PWM_Wide;	//PWM宽度

		PCA_Timer0 = PCAx->PCA_Value;
		B_Capture0 = 0;
		PCA0_mode = PCAx->PCA_Mode;
		CCAP0_tmp = PCA_Timer0;
		CCAP0L = (unsigned char)CCAP0_tmp;			//将影射寄存器写入捕获寄存器，先写CCAP0L
		CCAP0H = (unsigned char)(CCAP0_tmp >> 8);	//后写CCAP0H
	}
	if(PCA_id == PCA1)
	{
		CCAPM1    = PCAx->PCA_Mode | PCAx->PCA_Interrupt_Mode;
		PCA_PWM1  = (PCA_PWM1 & ~(3<<6)) | PCAx->PCA_PWM_Wide;

		PCA_Timer1 = PCAx->PCA_Value;
		B_Capture1 = 0;
		PCA1_mode = PCAx->PCA_Mode;
		CCAP1_tmp = PCA_Timer1;
		CCAP1L = (unsigned char)CCAP1_tmp;			//将影射寄存器写入捕获寄存器，先写CCAP0L
		CCAP1H = (unsigned char)(CCAP1_tmp >> 8);	//后写CCAP0H
	}
	if(PCA_id == PCA2)
	{
		CCAPM2    = PCAx->PCA_Mode | PCAx->PCA_Interrupt_Mode;
		PCA_PWM2  = (PCA_PWM2 & ~(3<<6)) | PCAx->PCA_PWM_Wide;

		PCA_Timer2 = PCAx->PCA_Value;
		B_Capture2 = 0;
		PCA2_mode = PCAx->PCA_Mode;
		CCAP2_tmp = PCA_Timer2;
		CCAP2L = (unsigned char)CCAP2_tmp;			//将影射寄存器写入捕获寄存器，先写CCAP0L
		CCAP2H = (unsigned char)(CCAP2_tmp >> 8);	//后写CCAP0H
	}
}

