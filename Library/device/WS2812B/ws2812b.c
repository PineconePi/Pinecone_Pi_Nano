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
 //One NOP 41.6666667 ns (1T: 1 machine cycle = 1 clock cycle)|一个 nop 41.6666667 ns	(1T：1个机器周期=1个时钟周期）
unsigned char data_red[n_ws2812b] = {0};//Common mode color buffer|普通模式颜色缓存
unsigned char data_green[n_ws2812b] = {0};
unsigned char data_blue[n_ws2812b] = {0};

unsigned char data_rollred[n_ws2812b+1] = {0};//Roll mode color cache|roll模式颜色缓存
unsigned char data_rollgreen[n_ws2812b+1] = {0};
unsigned char data_rollblue[n_ws2812b+1] = {0};
//========================================================================
// Function:void Delay50us()|函数: void Delay50us()
// Description:Reset delay.|描述: 复位延迟。
// Parameter: none.|参数: none.
// Return: none.|返回: none.
// Version:VER1.0.0|版本: VER1.0.0
// Date: 2018-12-20|日期: 2018-12-20
// Note:|备注: 
//========================================================================
void Delay50us()		//Reset delay|复位延迟
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
// Function:void delay_ms(unsigned int ms)|函数: void delay_ms(unsigned int ms)
// Description:Delay function.|描述: 延时函数。
// Parameter: ms, the number of MS to be delayed, where only 1-10000 (10s) MS is supported
// 参数: ms,要延时的ms数, 这里只支持1~10000 (10s) ms
// Return: none.|返回: none.
// Version:VER1.0.0|版本: VER1.0.0
// Date: 2018-12-20|日期: 2018-12-20
// Note: delay_ms (1000); //delay 1s|备注: delay_ms(1000);//延迟1s
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
// Function:void rgb_high()|函数: void rgb_high()
// Description:|描述: 1 yard, 850ns high level, 400ns low level (error plus or minus 150ns)
// Parameter:|参数: 
// Return: none.|返回: none.
// Version:VER1.0.0|版本: VER1.0.0
// Date: 2018-12-20|日期: 2018-12-20
// Note:|备注: 
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
// Function:void rgb_down()|函数: void rgb_down()
// Description: 0 yard, 400 ns high level, 850 ns low level (error plus or minus 150 ns)|描述: 0码，高电平400ns 低电平850ns （误差正负150ns）
// Parameter:|参数: 
// Return: none.|返回: none.
// Version:VER1.0.0|版本: VER1.0.0
// Date: 2018-12-20|日期: 2018-12-20
// Note:|备注: 
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
// Function:void rgb_reset()|函数: void rgb_reset()
// Description:Reset WS2812B and start a new command|描述: 复位WS2812B，开始一次新的命令
// Parameter:|参数: 
// Return: none.|返回: none.
// Version:VER1.0.0|版本: VER1.0.0
// Date: 2018-12-20|日期: 2018-12-20
// Note:|备注: 
//========================================================================
void rgb_reset()
{
 rgb_pin = 0;
 Delay50us();
}
//========================================================================
// Function:void ws2812b_display(unsigned char green,unsigned char red,unsigned char blue)|函数: void ws2812b_display(unsigned char green,unsigned char red,unsigned char blue)
// Description:Single ws2812b control|描述: 单个ws2812b控制
// Parameters: green: green 0-255, red: red 0-255, blue: blue 0-255,|参数:  green：绿色 0-255，red：红色 0-255 ，blue：蓝色 0-255，
// Return: none.|返回: none.
// Version:VER1.0.0|版本: VER1.0.0
// Date: 2018-12-20|日期: 2018-12-20
// Note:|备注: 
//========================================================================
void ws2812b_display(unsigned char green,unsigned char red,unsigned char blue)

{
	  unsigned int n = 0;
	  //Sending green bits|发送green位
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

		//Sending red bits|发送red位
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
		//Sending blue bits|发送blue位
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
// Function:void n_ws2812b_display(unsigned char display_mode,unsigned char green,unsigned char red,unsigned char blue)|函数: void n_ws2812b_display(unsigned char display_mode,unsigned char green,unsigned char red,unsigned char blue)
// Description:n个ws2812b控制(n取决于n_ws2812b)|描述: n个ws2812b控制(n取决于n_ws2812b)
// Parameters:Display_mode: Mode selection. See ws2812b.h for details on defining green: 0-255 green, red: 0-255 red, blue: 0-255 blue.
// 参数: display_mode:模式选择，详情见ws2812b.h中定义 green：绿色 0-255，red：红色 0-255 ，blue：蓝色 0-255，
// Return: none.|返回: none.
// Version:VER1.0.0|版本: VER1.0.0
// Date: 2018-12-20|日期: 2018-12-20
// Note:|备注: 
//========================================================================
void n_ws2812b_display(unsigned char display_mode,unsigned char green,unsigned char red,unsigned char blue)
{
	 unsigned char j ;
	 unsigned char i ;
	 unsigned char roll_i = 0;	 //Consequent flow|顺向流水
	 unsigned char rollback_i = 1;	 //Reverse flow|反向流水

/********************* General mode control correlation|普通模式控制相关 *************************/
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
/********************* Control correlation of forward flow pattern|正向流水模式控制相关 *************************/
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

/********************* Reverse Pipeline Mode Control Relevance|反向流水模式控制相关 *************************/
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
/********************* Reverse Interval Pipeline Mode Control Relevance|反向间隔流水模式控制相关 *************************/
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
/********************* Respiratory lamp mode control correlation|呼吸灯模式控制相关 *************************/
		else if ( display_mode == breathe)
		{
		//未完待续
        }
}



