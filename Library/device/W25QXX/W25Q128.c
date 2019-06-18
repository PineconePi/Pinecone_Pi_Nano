/**
  ******************************************************************************
  * @file    W25Q128.c
  * @author  PineconePi(User)
  * @version V1.0.0
  * @date    17-June-2019
  * @brief  This document is used to drive W25Q128.
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
#include <W25Q128.h>

//========================================================================
// 函数: unsigned char SPI_Send_Reception(unsigned char Dat)
// 描述: SPI发送与接受字节。
// 参数: Dat,发送数据
// 返回: SPDAT,接收数据.
// 版本: VER1.0.0
// 日期: 2019-06-17
// 备注: 
//========================================================================
unsigned char SPI_Send_Reception(unsigned char Dat){
	SPDAT=Dat;
	while(!(SPSTAT&0x80));
	SPSTAT=0xC0;
	return SPDAT;
}
//========================================================================
// 函数: void SetW25Q128WriteEnable()
// 描述: W25Q128写使能。
// 参数: none.
// 返回: none.
// 版本: VER1.0.0
// 日期: 2019-06-17
// 备注: 
//========================================================================
void SetW25Q128WriteEnable(){
	CS=0;
	SPI_Send_Reception(0x06);
	CS=1;
}
//========================================================================
// 函数: ClearW25Q128WriteEnable()
// 描述: W25Q128写禁能。
// 参数: none.
// 返回: none.
// 版本: VER1.0.0
// 日期: 2019-06-17
// 备注: 
//========================================================================
void ClearW25Q128WriteEnable(){
	CS=0;
	SPI_Send_Reception(0x04);
	CS=1;
}
//========================================================================
// 函数: unsigned char ReadW25Q128StatusRegister()
// 描述: 读取W25Q128字节状态，判断busy。
// 参数: none.
// 返回: temp，是否繁忙.
// 版本: VER1.0.0
// 日期: 2019-06-17
// 备注: 
//========================================================================
unsigned char ReadW25Q128StatusRegister(){
	unsigned char temp;
	CS=0;
	SPI_Send_Reception(0x05);
	temp=SPI_Send_Reception(0xFF);
	CS=1;
	return temp;
}
//========================================================================
// 函数: await_busy()
// 描述: 等待busy完成。
// 参数: none.
// 返回: none.
// 版本: VER1.0.0
// 日期: 2019-06-17
// 备注: 
//========================================================================
void await_busy(){
	while(ReadW25Q128StatusRegister()&1);
}
//========================================================================
// 函数: ReadW25Q128Operation(unsigned long addr)
// 描述: 读取W25Q128内容。
// 参数: Addr,读取地址.
// 返回: none.
// 版本: VER1.0.0
// 日期: 2019-06-17
// 备注: 
//========================================================================
void ReadW25Q128Operation(unsigned long Addr){
	await_busy();
	CS=0;
	SPI_Send_Reception(0x03);
	SPI_Send_Reception(Addr>>16);
	SPI_Send_Reception(Addr>>8);
	SPI_Send_Reception(Addr);
}
//========================================================================
// 函数: WriteW25Q128Operation(unsigned int Addr)
// 描述: W25Q128写入，一次256字节。
// 参数: Addr,写入地址.
// 返回: none.
// 版本: VER1.0.0
// 日期: 2019-06-17
// 备注: 
//========================================================================
void WriteW25Q128Operation(unsigned int Addr){
	await_busy();
	SetW25Q128WriteEnable();
	CS=0;
	SPI_Send_Reception(0x02);
	SPI_Send_Reception(Addr>>8);
	SPI_Send_Reception(Addr);
	SPI_Send_Reception(0);
}
//========================================================================
// 函数: EraseW25Q128Operation(unsigned int Addr)
// 描述: 对W25Q128擦除。
// 参数: Addr,擦除地址.
// 返回: none.
// 版本: VER1.0.0
// 日期: 2019-06-17
// 备注: 
//========================================================================
void EraseW25Q128Operation(unsigned int Addr){//对W25Q128擦除
	await_busy();
	SetW25Q128WriteEnable();
	CS=0;
  SPI_Send_Reception(0x20);
	SPI_Send_Reception(Addr/16);
	SPI_Send_Reception(Addr*16);
	SPI_Send_Reception(0);
	CS=1;
}
//========================================================================
// 函数: W25Q128_Write_SR(unsigned char Sr)
// 描述: W25Q128写状态寄存器。
// 参数: Sr,寄存器状态.
// 返回: none.
// 版本: VER1.0.0
// 日期: 2019-06-17
// 备注: 
//========================================================================
void W25Q128_Write_SR(unsigned char Sr){
	SetW25Q128WriteEnable();
	CS=0;
	SPI_Send_Reception(0x01);
	SPI_Send_Reception(Sr);
	CS=1;
}