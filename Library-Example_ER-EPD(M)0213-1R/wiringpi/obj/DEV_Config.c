/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
****************************************************/
#include "DEV_Config.h"
#include <errno.h>

/******************************************************************************
function:	Initialization pin
parameter:
Info:
******************************************************************************/
static void DEV_GPIOConfig(void)
{
    //output
    pinMode(EPD_RST_PIN, OUTPUT);
    pinMode(EPD_DC_PIN, OUTPUT);
    pinMode(EPD_CS_PIN, OUTPUT);
	
    //intput
	pinMode(EPD_BUSY_PIN, INPUT);	
}


void DEV_SPI_WriteByte(UBYTE value)
{
    int read_data;
    read_data = wiringPiSPIDataRW(0,&value,1);
    if(read_data < 0)
        perror("wiringPiSPIDataRW failed\r\n");
}

/******************************************************************************
function:	Module Initialize, the BCM2835 library and initialize the pins, SPI protocol
parameter:
Info:
******************************************************************************/
UBYTE DEV_ModuleInit(void)
{
    //if(wiringPiSetup() < 0)//use wiringpi Pin number table
    if(wiringPiSetupGpio() < 0) { //use BCM2835 Pin number table
        printf("set wiringPi lib failed	!!! \r\n");
        return 1;
    } else {
        printf("set wiringPi lib success !!! \r\n");
    }
    
	DEV_GPIOConfig();

    //wiringPiSPISetup(0,9000000);
    wiringPiSPISetupMode(0, 32000000, 0);

    return 0;
}

/******************************************************************************
function:	Module exits, closes SPI and BCM2835 library
parameter:
Info:
******************************************************************************/
void DEV_ModuleExit(void)
{

}
