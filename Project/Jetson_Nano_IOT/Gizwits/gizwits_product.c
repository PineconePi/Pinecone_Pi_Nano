/**
************************************************************
* @file         gizwits_product.c
* @brief        Gizwits control protocol processing, and platform-related       hardware initialization 
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
* 
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值ֵ|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/

#include <stdio.h>
#include <string.h>
#include "Hal_Usart/hal_uart.h"
#include "gizwits_protocol.h"
#include "gizwits_product.h"
#include "common.h"
#include "delay.h"

/******************** 开/关机|重启引脚 ***************/
#define Power_on P01
#define Power_off P02
#define Reset P03
/******************** 开/关机|重启标志声明 ***************/
unsigned char flag_on;
unsigned char flag_off;
unsigned char flag_reset;

extern uint32_t timerMsCount;

/** User area the current device state structure*/
extern dataPoint_t currentDataPoint;

/**@} */
/**@name Gizwits User Interface
* @{
*/

/**
* @brief Event handling interface

* Description:

* 1. Users can customize the changes in WiFi module status

* 2. Users can add data points in the function of event processing logic, such as calling the relevant hardware peripherals operating interface

* @param [in] info: event queue
* @param [in] data: protocol data
* @param [in] len: protocol data length
* @return NULL
* @ref gizwits_protocol.h
*/
int8_t gizwitsEventProcess(eventInfo_t *info, uint8_t *gizdata, uint32_t len)
{
  uint8_t i = 0;
  dataPoint_t *dataPointPtr = (dataPoint_t *)gizdata;
  moduleStatusInfo_t *wifiData = (moduleStatusInfo_t *)gizdata;
  protocolTime_t *ptime = (protocolTime_t *)gizdata;
  
#if MODULE_TYPE
  gprsInfo_t *gprsInfoData = (gprsInfo_t *)gizdata;
#else
  moduleInfo_t *ptModuleInfo = (moduleInfo_t *)gizdata;
#endif

  if((NULL == info) || (NULL == gizdata))
  {
    return -1;
  }

  for(i=0; i<info->num; i++)
  {
    switch(info->event[i])
    {
      case EVENT_Power_on:
        currentDataPoint.valuePower_on = dataPointPtr->valuePower_on;
        GIZWITS_LOG("Evt: EVENT_Power_on %d \n", currentDataPoint.valuePower_on);
        if(0x01 == currentDataPoint.valuePower_on)
        {
          Power_on=0;
					User_Delay_Ms(800);
					Power_on=1;
					flag_on=1;
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_Power_off:
        currentDataPoint.valuePower_off = dataPointPtr->valuePower_off;
        GIZWITS_LOG("Evt: EVENT_Power_off %d \n", currentDataPoint.valuePower_off);
        if(0x01 == currentDataPoint.valuePower_off)
        {
          Power_off=0;
					User_Delay_Ms(800);
					Power_off=1;
					flag_off=1;
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_Reset:
        currentDataPoint.valueReset = dataPointPtr->valueReset;
        GIZWITS_LOG("Evt: EVENT_Reset %d \n", currentDataPoint.valueReset);
        if(0x01 == currentDataPoint.valueReset)
        {
          Reset=0;
					User_Delay_Ms(800);
					Reset=1;
					flag_reset=1;
        }
        else
        {
          //user handle    
        }
        break;




      case WIFI_SOFTAP:
        break;
      case WIFI_AIRLINK:
        break;
      case WIFI_STATION:
        break;
      case WIFI_CON_ROUTER:
 
        break;
      case WIFI_DISCON_ROUTER:
 
        break;
      case WIFI_CON_M2M:
 
        break;
      case WIFI_DISCON_M2M:
        break;
      case WIFI_RSSI:
        GIZWITS_LOG("RSSI %d\n", wifiData->rssi);
        break;
      case TRANSPARENT_DATA:
        GIZWITS_LOG("TRANSPARENT_DATA \n");
        //user handle , Fetch data from [data] , size is [len]
        break;
      case WIFI_NTP:
        GIZWITS_LOG("WIFI_NTP : [%d-%d-%d %02d:%02d:%02d][%d] \n",ptime->year,ptime->month,ptime->day,ptime->hour,ptime->minute,ptime->second,ptime->ntp);
        break;
      case MODULE_INFO:
            GIZWITS_LOG("MODULE INFO ...\n");
      #if MODULE_TYPE
            GIZWITS_LOG("GPRS MODULE ...\n");
            //Format By gprsInfo_t
      #else
            GIZWITS_LOG("WIF MODULE ...\n");
            //Format By moduleInfo_t
            GIZWITS_LOG("moduleType : [%d] \n",ptModuleInfo->moduleType);
      #endif
    break;
      default:
        break;
    }
  }

  return 0;
}

/**
* User data acquisition

* Here users need to achieve in addition to data points other than the collection of data collection, can be self-defined acquisition frequency and design data filtering algorithm

* @param none
* @return none
*/
void userHandle(void)
{
	if(flag_on==1){Power_on=1;flag_on=0;}else{currentDataPoint.valuePower_on=0;}
	if(flag_off==1){Power_off=1;flag_off=0;}else{currentDataPoint.valuePower_off=0;}
	if(flag_reset==1){Reset=1;flag_reset=0;}else{currentDataPoint.valueReset=0;}
 /*
    currentDataPoint.valueCPU_DATA = ;//Add Sensor Data Collection
    currentDataPoint.valueMemory_DATA = ;//Add Sensor Data Collection
    currentDataPoint.valueCPU2_DATA = ;//Add Sensor Data Collection
    currentDataPoint.valueCPU3_DATA = ;//Add Sensor Data Collection
    currentDataPoint.valueCPU4_DATA = ;//Add Sensor Data Collection

    */
    
}

/**
* Data point initialization function

* In the function to complete the initial user-related data
* @param none
* @return none
* @note The developer can add a data point state initialization value within this function
*/
void userInit(void)
{
    memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
    
    /** Warning !!! DataPoint Variables Init , Must Within The Data Range **/ 
    /*
      currentDataPoint.valuePower_on = ;
      currentDataPoint.valuePower_off = ;
      currentDataPoint.valueReset = ;
      currentDataPoint.valueCPU_DATA = ;
      currentDataPoint.valueMemory_DATA = ;
      currentDataPoint.valueCPU2_DATA = ;
      currentDataPoint.valueCPU3_DATA = ;
      currentDataPoint.valueCPU4_DATA = ;
    */

}


/**
* @brief Millisecond timing maintenance function, milliseconds increment, overflow to zero

* @param none
* @return none
*/
void gizTimerMs(void)
{
    timerMsCount++;
}

/**
* @brief Read millisecond count

* @param none
* @return millisecond count
*/
uint32_t gizGetTimerCount(void)
{
    return timerMsCount;
}

/**
* @brief MCU reset function

* @param none
* @return none
*/
void mcuRestart(void)
{
        IAP_CONTR &= ~0x40; //软件复位后直接执行用户代码
        IAP_CONTR |= 0x20;  //软件复位
}

/**@} */

/**

/**
* @brief Serial port write operation, send data to WiFi module
*
* @param buf      : buf address
* @param len      : buf length
*
* @return : Return effective data length;-1，return failure
*/
int32_t uartWrite(uint8_t *buf, uint32_t len)
{
    uint32_t i = 0;
    
    if(NULL == buf)
    {
        return -1;
    }

#ifdef PROTOCOL_DEBUG
    GIZWITS_LOG("MCU2WiFi[%lu:%lu]: ", gizGetTimerCount(), len);
    for(i=0; i<len; i++)
    {
        GIZWITS_LOG("%02x ", (uint16_t)buf[i]);

        if(i >=2 && buf[i] == 0xFF)
        {
            GIZWITS_LOG("%02x ", 0x55);
        }
    }

    GIZWITS_LOG("\n");
#endif
    
    for(i=0; i<len; i++)
    {
        UART1_TxByte(buf[i]);

        if(i >=2 && buf[i] == 0xFF)
        {
          UART1_TxByte(0x55);
        }
    }
        
    return len;
}


