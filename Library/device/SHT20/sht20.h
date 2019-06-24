/**
  ******************************************************************************
  * @file    sht20.h
  * @author  ThreeWater
  * @version V1.0.0
  * @date    17-June-2019
  * @brief  This article will be used for  driving sht20.
  * @License:none         
  ******************************************************************************
  * @attention
  *	The frequency of crystal oscillator is 12 Mhz.
  * using OLED_IIC_Setup() to initialize.
  * 
  * 
  *
  * 
  ******************************************************************************
	**/
#ifndef __SHT20_H
#define __SHT20_H
#include <stdio.h>
#include "system.h"


typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
sbit P1_6=P1^6;
sbit P1_7=P1^7;

#define SCL_H P1_6=1
#define SCL_L P1_6=0
#define SDA_H P1_7=1
#define SDA_L P1_7=0
#define SDA_read P1_7
#define CHECKSUM_ERROR 0x04


typedef enum{
  TRIG_T_MEASUREMENT_HM    = 0xE3, // command trig. temp meas. hold master
  TRIG_RH_MEASUREMENT_HM   = 0xE5, // command trig. humidity meas. hold master
  TRIG_T_MEASUREMENT_POLL  = 0xF3, // command trig. temp meas. no hold master
  TRIG_RH_MEASUREMENT_POLL = 0xF5, // command trig. humidity meas. no hold master
  USER_REG_W               = 0xE6, // command writing user register
  USER_REG_R               = 0xE7, // command reading user register
  SOFT_RESET               = 0xFE  // command soft reset
}SHT2xCommand;

typedef enum {
  SHT2x_RES_12_14BIT       = 0x00, // RH=12bit, T=14bit
  SHT2x_RES_8_12BIT        = 0x01, // RH= 8bit, T=12bit
  SHT2x_RES_10_13BIT       = 0x80, // RH=10bit, T=13bit
  SHT2x_RES_11_11BIT       = 0x81, // RH=11bit, T=11bit
  SHT2x_RES_MASK           = 0x81  // Mask for res. bits (7,0) in user reg.
} SHT2xResolution;

typedef enum {
  SHT2x_EOB_ON             = 0x40, // end of battery
  SHT2x_EOB_MASK           = 0x40, // Mask for EOB bit(6) in user reg.
} SHT2xEob;

typedef enum {
  SHT2x_HEATER_ON          = 0x04, // heater on
  SHT2x_HEATER_OFF         = 0x00, // heater off
  SHT2x_HEATER_MASK        = 0x04, // Mask for Heater bit(2) in user reg.
} SHT2xHeater;


typedef enum{
  HUMIDITY,
  TEMP
}SHT2xMeasureType;

typedef enum{
  I2C_ADR_W                = 128,   // sensor I2C address + write bit
  I2C_ADR_R                = 129    // sensor I2C address + read bit
}I2cHeader;

float SHT2x_Calc_T(void);
float SHT2x_Calc_RH(void);


#endif /* __SHT20_H */
