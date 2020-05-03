/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
****************************************************/
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

#include <wiringPi.h>
#include <wiringPiSPI.h>

#include <string.h>
#include <stdint.h>
#include <stdio.h>

/**
 * data
**/
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

/**
 * GPIO config
**/
#define EPD_RST_PIN     17
#define EPD_DC_PIN      25
#define EPD_CS_PIN      8
#define EPD_BUSY_PIN    24

/**
 * GPIO read and write
**/
#define DEV_Digital_Write(_pin, _value) digitalWrite(_pin, _value)
#define DEV_Digital_Read(_pin) digitalRead(_pin)


/**
 * delay x ms
**/
#define DEV_Delay_ms(__xms) delay(__xms)

/*------------------------------------------------------------------------------------------------------*/
void DEV_SPI_WriteByte(UBYTE value);
UBYTE DEV_ModuleInit(void);
void DEV_ModuleExit(void);


#endif
