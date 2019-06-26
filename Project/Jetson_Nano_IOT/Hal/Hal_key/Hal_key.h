#ifndef __HAL_KEY_H__
#define __HAL_KEY_H__
#include <stdint.h>
#include <intrins.h>
#define LONGPRESS 4				//定义长按设置键的时间	
sbit	SETKEY = P0^0;			//K2,多功能按键(短按,长按)

void delay1ms(unsigned char ms);//延时程序
void setkeyscan();				//设置键的扫描判断函数
void pro_sklp();				//长按设置功能键的处理函数
void pro_sksp();				//短按设置功能键的处理函数

#endif