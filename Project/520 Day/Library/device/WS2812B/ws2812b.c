/**
  ******************************************************************************
  * @file    ws2812b.c
  * @author  PineconePi
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This article will be used for  driving  ws2812b.
  * @License:GNU General Public License v3.0         
  ******************************************************************************
  * @attention
  *	The frequency of crystal oscillator is 24 Mhz
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
#include "ws2812b.h"
#include "intrins.h"
 //一个 nop 41.6666667 ns	(1T：1个机器周期=1个时钟周期）
unsigned char data_red[n_ws2812b] = {0};//普通模式颜色缓存
unsigned char data_green[n_ws2812b] = {0};
unsigned char data_blue[n_ws2812b] = {0};

unsigned char data_rollred[n_ws2812b+1] = {0};//roll模式颜色缓存
unsigned char data_rollgreen[n_ws2812b+1] = {0};
unsigned char data_rollblue[n_ws2812b+1] = {0};
//========================================================================
// 函数: void Delay50us()
// 描述: 复位延迟。
// 参数: none.
// 返回: none.
// 版本: VER1.0.0
// 日期: 2018-12-20
// 备注: 
//========================================================================
void Delay50us()		//复位延迟
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 140;
	do
	{
		while (--j);
	} while (--i);
}
//========================================================================
// 函数: void delay_ms(unsigned int ms)
// 描述: 延时函数。
// 参数: ms,要延时的ms数, 这里只支持1~10000 (10s) ms
// 返回: none.
// 版本: VER1.0.0
// 日期: 2018-12-20
// 备注: delay_ms(1000);//延迟1s
//========================================================================
void delay_ms_2812b(unsigned int ms){
  unsigned int k;
	unsigned char i, j;
	for(k=0;k<ms;k++)
	{
	_nop_();
	i = 32;
	j = 40;
		do
		{
		  while (--j);
		} while (--i);
	}
	}
//========================================================================
// 函数: void rgb_high()
// 描述: 1码，高电平850ns 低电平400ns （误差正负150ns）
// 参数: 
// 返回: none.
// 版本: VER1.0.0
// 日期: 2018-12-20
// 备注: 
//========================================================================													   
void rgb_high()
{
	 rgb_pin = 1;
	 _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();  
	 _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();   
     rgb_pin = 0;
	 _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
}
//========================================================================
// 函数: void rgb_down()
// 描述: 0码，高电平400ns 低电平850ns （误差正负150ns）
// 参数: 
// 返回: none.
// 版本: VER1.0.0
// 日期: 2018-12-20
// 备注: 
//========================================================================
void rgb_down()
{
	 rgb_pin = 1;
	 _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();    

	 rgb_pin = 0;
	 _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();  
	 _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();  
}
//========================================================================
// 函数: void rgb_reset()
// 描述: 复位WS2812B，开始一次新的命令
// 参数: 
// 返回: none.
// 版本: VER1.0.0
// 日期: 2018-12-20
// 备注: 
//========================================================================
void rgb_reset()
{
 rgb_pin = 0;
 Delay50us();
}
//========================================================================
// 函数: void ws2812b_display(unsigned char green,unsigned char red,unsigned char blue)
// 描述: 单个ws2812b控制
// 参数:  green：绿色 0-255，red：红色 0-255 ，blue：蓝色 0-255，
// 返回: none.
// 版本: VER1.0.0
// 日期: 2018-12-20
// 备注: 
//========================================================================
void ws2812b_display(unsigned char green,unsigned char red,unsigned char blue)

{
	  unsigned int n = 0;
	  //发送green位
		for(n=0;n<8;n++)
		{
			green<<=n;
			if(green&0x80 == 0x80)
			{
				rgb_high();
			}
			else  
			{
			  rgb_down();
			}
		}

		//发送red位
		for(n=0;n<8;n++)
		{
			red<<=n;
			if(red&0x80 == 0x80)
			{
				rgb_high();
			}
			else  
			{
				rgb_down();
			}		
		}
		//发送blue位
	  for(n=0;n<8;n++)
		{
			blue<<=n;
			if(blue&0x80 == 0x80)
			{
				rgb_high();
			}
			else  
			{
			  rgb_down();
			}
		}
}
//========================================================================
// 函数: void n_ws2812b_display(unsigned char display_mode,unsigned char green,unsigned char red,unsigned char blue)
// 描述: n个ws2812b控制(n取决于n_ws2812b)
// 参数: display_mode:模式选择，详情见ws2812b.h中定义 green：绿色 0-255，red：红色 0-255 ，blue：蓝色 0-255，
// 返回: none.
// 版本: VER1.0.0
// 日期: 2018-12-20
// 备注: 
//========================================================================
void n_ws2812b_display(unsigned char display_mode,unsigned char green,unsigned char red,unsigned char blue)
{
	 unsigned char j ;
	 unsigned char i ;
	 unsigned char roll_i = 0;	 //顺向流水
	 unsigned char rollback_i = 1;	 //反向流水

/********************* 普通模式控制相关 *************************/
	  if( display_mode == normal)
	  {
	  delay_ms_2812b(1);
		for(i=0;i<n_ws2812b;i++)
	  {
			  data_green[i] = green;
			  data_red[i] = red; 
			  data_blue[i] = blue;
		}
		for(i=0;i<n_ws2812b;i++)
		{
		ws2812b_display(data_green[i],data_red[i],data_blue[i]);
		}
		}
/********************* 正向流水模式控制相关 *************************/
		else if( display_mode == roll)
		{
		delay_ms_2812b(1);
		for(i=0;i<=n_ws2812b;i++)
	    {
			  data_rollgreen[i] = green;
			  data_rollred[i] = red; 
			  data_rollblue[i] = blue;
		}

		for(i=0;i<=n_ws2812b;i++)
		{
		ws2812b_display(data_rollgreen[i],data_rollred[i],data_rollblue[i]);
		delay_ms_2812b(roll_delay);
		rgb_reset();
		for(i=0;i<roll_i;i++)
		{
		ws2812b_display(0,0,0);
		}
		roll_i++;
		}
		}

/********************* 反向流水模式控制相关 *************************/
		else if ( display_mode ==  roll_back_1)
		{
		 delay_ms_2812b(1);
				for(i=0;i<=n_ws2812b;i++)
	    {
			  data_rollgreen[i] = green;
			  data_rollred[i] = red; 
			  data_rollblue[i] = blue;
		}

		for(j=0;j<n_ws2812b;j++)
		{
		  for(i=(n_ws2812b-rollback_i);i>0;i--)
		  {
			ws2812b_display(0,0,0);
		  }
		  ws2812b_display(data_rollgreen[i],data_rollred[i],data_rollblue[i]);
		  delay_ms_2812b(roll_delay);
		  rollback_i++;
		  if(rollback_i>n_ws2812b){rollback_i=1;}
        }
	 delay_ms_2812b(1);	 
	 n_ws2812b_display(normal,0x00,0x00,0x00);
}
/********************* 反向间隔流水模式控制相关 *************************/
		else if ( display_mode ==  roll_back_2)
		{
		 delay_ms_2812b(1);
				for(i=0;i<=n_ws2812b;i++)
	    {
			  data_rollgreen[i] = green;
			  data_rollred[i] = red; 
			  data_rollblue[i] = blue;
		}

		for(j=n_ws2812b;j>0;j--)
		{
		  for(i=(n_ws2812b-rollback_i);i>0;i--)
		  {
			ws2812b_display(0,0,0);
		  }
		  ws2812b_display(data_rollgreen[i],data_rollred[i],data_rollblue[i]);
		  delay_ms_2812b(roll_delay);
		  rollback_i++;
		  for(i=(n_ws2812b-rollback_i+1);i>0;i--)
		  {
			ws2812b_display(0,0,0);
		  }
		  if(rollback_i>n_ws2812b){rollback_i=1;}
        }
	 delay_ms_2812b(1);	 
		for(i=0;i<clear_ws2812b;i++)
		{
		ws2812b_display(0,0,0);
		}
        }
/********************* 呼吸灯模式控制相关 *************************/
		else if ( display_mode == breathe)
		{
		//未完待续
        }
}



