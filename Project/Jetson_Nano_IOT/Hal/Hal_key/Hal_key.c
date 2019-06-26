#include <hal_key.h>
#include "gizwits_protocol.h"


unsigned char	skeycount;		//设置按键时长计数器
unsigned char	skpttime;		//设置按键时长
unsigned char	longflag;		//设置长按标志
unsigned char	sflag;			//设置显示状态标志,0-普通运行,1-定时设置,2-日历时钟设置
bit		skpflag;				//设置按键按下标志



		
void delay1ms(unsigned char ms);//延时程序
void setkeyscan();				//设置键的扫描判断函数
void pro_sklp();				//长按设置功能键的处理函数
void pro_sksp();				//短按设置功能键的处理函数


 
//=======子程序==================================
/*检测及处理多功能设置按键k2*/
void setkeyscan()
{
	if (skpflag)										//判断是否已经有键按下未被处理
	{
		if(skeycount>LONGPRESS)							//如果是长按则执行长按键设置功能
		{
			pro_sklp();
			skpflag=0;
			longflag=1;
		}
		else if((skpttime>0) && (skpttime<=LONGPRESS))	//否则如果是短按则执行短按的功能,都不是直接跳过
		{
			pro_sksp();
			skpflag=0;
		}
	}
	else
	{
		if(!SETKEY)								//按下设置键
		{
			delay1ms(10);						//键盘防抖
			if((!SETKEY)&&longflag == 0)
			{
				skeycount=0;					//初始化按键时长计数器
				skpttime=0;						//初始化按键时长
				skpflag=1;						//标志已经有键被按下
				longflag=0;
			}
		}else{
                        longflag=0;
              	}
	}
}


/* 延时程序*/
void delay1ms(unsigned char ms)
{	while(ms--)						//每循环一次,约延迟1ms
	{	unsigned char i;
		for(i = 0; i< 250; i++)     //循环250次,在12M晶振时约延时1ms
		{
			_nop_();			   //执行一条_nop_()指令为一个机器周期
			_nop_();
			_nop_();
			_nop_();
		}
	}
}		
	

/*(短按k2)*/
void pro_sksp()
{
	sflag=0;								//设置状态标志
	//以下为短按键的处理程序
	gizwitsSetMode(WIFI_AIRLINK_MODE);//进入airlink配网模式
}


/*(长按k2)*/
void pro_sklp()
{
	sflag=0;								//设置状态标志
	//以下为长按键的处理程序
	gizwitsSetMode(WIFI_RESET_MODE);//reset模组

}

void key_init()
{
	skeycount=0;						//初始化功能键按下时长计数器
	skpttime=0;							//初始化功能键按下的总时长
	sflag=0;							//初始化显示状态标志,0-普通运行,1-定时设置,2-日历时钟设置
	SETKEY=1;							//k2,设置为输入端口
	longflag =0;
}

