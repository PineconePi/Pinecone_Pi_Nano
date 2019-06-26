#松果派NANO移植机智云 GAgent步骤（作者：xdd_core）
###  **Step** 
1.使用机智云自动生成代码工具生成“STC15F2K60S2”的代码
2.用以上文件夹中的文件替换原有文件，并将SYSTEM文件夹添加至工程目录下
3.将SYSTEM文件夹添加到INCLUDE PATH
4.修改KEIL MCU型号为"STC8A8K64S4A12"
5.在main.c中找到定时器初始化代码
``` C
/**************定时器初始化函数**********************/
void Timer0_Init(void)
{
	TMOD|=0x02;
	TL0=0x47;
	TH0=0x47;
	ET0=1;
	TR0=1;
}
``` 
将其更改为
``` C
/**************定时器初始化函数**********************/
void Timer0_Init(void)
{
	TMOD|=0x02;
	TL0=0x40;//0x47;
	TH0=0xa2;//0x47;
	ET0=1;
	TR0=1;
}
```
6.完成移植
###  **PS** 
1.晶振频率24Mhz
2.平台极限：松果派NANO内部有8K SRAM，理论数据点占用为60%（4.8K）以下是比较适合的。如果数据点太多，而超过这个RAM占用百分比，可能出现串口解析失败，程序跑死（/跑飞）等问题
3.串口1打印日志（波特率：115200）；串口2连接已经烧录好GAgent的ESP8266（波特率：9600）；
4.我之前写过一篇关于GAgent的代码逻辑分析见：http://club.gizwits.com/forum.php?mod=viewthread&tid=7217&highlight=%E9%AB%98%E4%B8%AD%E7%94%9F