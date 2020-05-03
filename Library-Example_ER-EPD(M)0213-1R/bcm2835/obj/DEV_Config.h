/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
****************************************************/
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

#include <bcm2835.h>
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
#define DEV_Digital_Write(_pin, _value) bcm2835_gpio_write(_pin, _value)
#define DEV_Digital_Read(_pin) bcm2835_gpio_lev(_pin)

/**
 * SPI
**/
#define DEV_SPI_WriteByte(__value) bcm2835_spi_transfer(__value)

/**
 * delay x ms
**/
#define DEV_Delay_ms(__xms) bcm2835_delay(__xms)

/*------------------------------------------------------------------------------------------------------*/
UBYTE DEV_ModuleInit(void);
void DEV_ModuleExit(void);


#endif
