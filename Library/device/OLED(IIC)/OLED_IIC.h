/**
  ******************************************************************************
  * @file    OLED_IIC.h
  * @author  ThreeWater
  * @version V1.0.0
  * @date    17-June-2019
  * @brief  This article will be used for  driving  OLED_IIC.
  * @License:none         
  ******************************************************************************
  * @attention
  *	The frequency of crystal oscillator is 12 Mhz.
  * 
  * 
  *
  * 
  ******************************************************************************
	**/

#ifndef __OLED_IIC_H
#define __OLED_IIC_H	
#include "system.h"
#include "intrins.h"
#include "stdlib.h"	    	

//libaries
extern const unsigned char code F6x8[][6] ;
extern const unsigned char code F8X16[];
extern char code Hzk[][16];



sbit OLED_SCL = P1^0;
sbit OLED_SDA = P1^1;
#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED OLED_IIC端口定义----------------  					   

#define OLED_SCLK_CLR() OLED_SCL=0//SCL
#define OLED_SCLK_SET() OLED_SCL=1

#define OLED_SDIN_CLR() OLED_SDA=0//SDA
#define OLED_SDIN_SET() OLED_SDA=1

 		     
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


//OLED控制用函数
void OLED_WR_Byte(unsigned dat,unsigned cmd);  
void OLED_Display_On(void);
void OLED_Display_Off(void);	   				
void OLED_Clear(void);
void OLED_DrawPoint(unsigned char x,unsigned char y,unsigned char t);
void OLED_Fill(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char dot);
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr,unsigned char Char_Size);
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size);
void OLED_ShowString(unsigned char x,unsigned char y, unsigned char *p,unsigned char Char_Size);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void fill_picture(unsigned char fill_Data);
void OLED_IIC_Setup(void);


#endif  
