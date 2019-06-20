松果派NANO移植机智云 GAgent步骤（作者：xdd_core）
1.使用机智云自动生成代码工具生成“STC15F2K60S2”的代码
2.用以上文件夹中的文件替换原有文件
3.修改KEIL MCU型号为"STC8A8K64S4A12"
4.完成移植
PS:
晶振频率24Mhz
平台极限：松果派NANO内部有8K SRAM，理论数据点占用为60%（4.8K）以下是比较适合的。如果数据点太多，而超过这个RAM占用百分比，可能出现串口解析失败，程序跑死（/跑飞）等问题
串口1打印日志（波特率：115200）；串口2连接已经烧录好GAgent的ESP8266（波特率：9600）；
我之前写过一篇关于GAgent的代码逻辑分析见：http://club.gizwits.com/forum.php?mod=viewthread&tid=7217&highlight=%E9%AB%98%E4%B8%AD%E7%94%9F