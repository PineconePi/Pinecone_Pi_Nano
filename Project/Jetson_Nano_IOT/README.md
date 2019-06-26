#Jetson NANO 开机棒（IOT）（作者：xdd_core）
###  **PS** 
1. 晶振频率24Mhz
2. P0^1为开机引脚；P0^2为关机引脚；P0^3为重启引脚（可在main.c和gizwits_product.c中修改）
3. 支持回传CPU(1-4)的占用率以及内存占用率（4GB） ---待开发
4. 平台极限：松果派NANO内部有8K SRAM，理论数据点占用为60%（4.8K）以下是比较适合的。如果数据点太多，而超过这个RAM占用百分比，可能出现串口解析失败，程序跑死（/跑飞）等问题
5. 串口1打印日志（波特率：115200）；串口2连接已经烧录好GAgent的ESP8266（波特率：9600）；
6. 我之前写过一篇关于GAgent的代码逻辑分析见：http://club.gizwits.com/forum.php?mod=viewthread&tid=7217&highlight=%E9%AB%98%E4%B8%AD%E7%94%9F