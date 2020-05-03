/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
****************************************************/
#include "ER-EPD0213-1R.h"
#include "Debug.h"


const unsigned char lut[] = {
0xAA,	0x99,	0x10,	0x00,	0x00,	0x00,	0x00,	0x55,	0x99,	0x80,	0x00,	0x00,	0x00,	0x00,	0x8A,	0xA8,
0x9B,	0x00,	0x00,	0x00,	0x00,	0x8A,	0xA8,	0x9B,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,
0x00,	0x00,	0x00,	0x0F,	0x0F,	0x0F,	0x0F,	0x02,	0x14,	0x14,	0x14,	0x14,	0x06,	0x14,	0x14,	0x0C,
0x82,	0x08,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,									

/*
0xA5,	0x89,	0x10,	0x00,	0x00,	0x00,	0x00,	0xA5,	0x19,	0x80,	0x00,	0x00,	0x00,	0x00,	0xA5,	0xA9,
0x9B,	0x00,	0x00,	0x00,	0x00,	0xA5,	0xA9,	0x9B,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,
0x00,	0x00,	0x00,	0x0F,	0x0F,	0x0F,	0x0F,	0x02,	0x10,	0x10,	0x0A,	0x0A,	0x03,	0x08,	0x08,	0x09,
0x43,	0x07,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,
0x00,	0x00,	0x00,	0x00,	0x00,	0x00,										
*/	
};





/******************************************************************************
function :	Software reset
parameter:
******************************************************************************/
static void EPD_Reset(void)
{
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(200);
    DEV_Digital_Write(EPD_RST_PIN, 0);
    DEV_Delay_ms(200);
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(200);
}

/******************************************************************************
function :	send command
parameter:
     Reg : Command register
******************************************************************************/
static void EPD_SendCommand(UBYTE Reg)
{
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_SPI_WriteByte(Reg);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
static void EPD_SendData(UBYTE Data)
{
    DEV_Digital_Write(EPD_DC_PIN, 1);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_SPI_WriteByte(Data);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
function :	Wait until the busy_pin goes LOW
parameter:
******************************************************************************/
void EPD_WaitUntilIdle(void)
{
    Debug("e-Paper busy\r\n");
    while(DEV_Digital_Read(EPD_BUSY_PIN) == 1) {      //LOW: idle, HIGH: busy
        DEV_Delay_ms(100);
    }
    Debug("e-Paper busy release\r\n");
}

/******************************************************************************
function :	Setting the display window
parameter:
******************************************************************************/
static void EPD_SetWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend)
{
    EPD_SendCommand(SET_RAM_X_ADDRESS_START_END_POSITION);
    EPD_SendData((Xstart >> 3) & 0xFF);
    EPD_SendData((Xend >> 3) & 0xFF);

    EPD_SendCommand(SET_RAM_Y_ADDRESS_START_END_POSITION);
    EPD_SendData(Ystart & 0xFF);
    EPD_SendData((Ystart >> 8) & 0xFF);
    EPD_SendData(Yend & 0xFF);
    EPD_SendData((Yend >> 8) & 0xFF);
}

/******************************************************************************
function :	Set Cursor
parameter:
******************************************************************************/
static void EPD_SetCursor(UWORD Xstart, UWORD Ystart)
{
    EPD_SendCommand(SET_RAM_X_ADDRESS_COUNTER);
    EPD_SendData((Xstart >> 3) & 0xFF);

    EPD_SendCommand(SET_RAM_Y_ADDRESS_COUNTER);
    EPD_SendData(Ystart & 0xFF);
    EPD_SendData((Ystart >> 8) & 0xFF);

}

/******************************************************************************
function :	Turn On Display
parameter:
******************************************************************************/
static void EPD_TurnOnDisplay(void)
{
    EPD_SendCommand(DISPLAY_UPDATE_CONTROL_2);
    EPD_SendData(0xC4);
    EPD_SendCommand(MASTER_ACTIVATION);


    EPD_WaitUntilIdle();
}

/******************************************************************************
 function : set the look-up table register
******************************************************************************/
void EPD_SetLut() {
 UWORD i;
   EPD_SendCommand(WRITE_LUT_REGISTER);
    /* the length of look-up table is 70 bytes */
    for ( i = 0; i < 70; i++) {
    EPD_SendData(lut[i]);
    }
}


/******************************************************************************
function :	Initialize the e-Paper register
parameter:
******************************************************************************/
UBYTE EPD_Init(void)
{
    EPD_Reset();
 
 
    /////////////////// new EPD

    EPD_SendCommand(DRIVER_OUTPUT_CONTROL);  // Driver Output control
    EPD_SendData(0xD3);           
    EPD_SendData(0x00);
    EPD_SendData(0x00);     
        
    EPD_SendCommand(DATA_ENTRY_MODE_SETTING);  // Data Entry mode setting
    EPD_SendData(0x03);         
    EPD_SendCommand(SET_RAM_X_ADDRESS_START_END_POSITION); //Set RAM X - address Start / End position
    EPD_SendData(0x00); // RAM x address start at 0
    EPD_SendData(0x0C); //RAM x address end at 0Ch(12+1)*8->104
    EPD_SendCommand(SET_RAM_Y_ADDRESS_START_END_POSITION); //Set Ram Y- address Start / End position
    EPD_SendData(0xD3); // RAM y address start at 0D3h;  
    EPD_SendData(0x00);
    EPD_SendData(0x00); // RAM y address end at 00h;
    EPD_SendData(0x00);
               
    EPD_SendCommand(BORDER_WAVEFORM_CONTROL); // Border Waveform Control
    EPD_SendData(0x05); // HIZ

    EPD_SendCommand(DISPLAY_UPDATE_CONTROL_1);
    EPD_SendData(0x80);//Inverse RED RAM content
    EPD_SendData(0x80);        
	
    EPD_SendCommand(0x18);//Temperature Sensor Control
    EPD_SendData(0x80);  //Internal temperature sensor
    EPD_SendCommand(DISPLAY_UPDATE_CONTROL_2);//Display UpdateControl 2
    EPD_SendData(0xB1);	//Load Temperature and waveform setting.
    EPD_SendCommand(MASTER_ACTIVATION); //Master Activation
    EPD_WaitUntilIdle();	   
   
 
/*
  /////////////////// old EPD
    EPD_SendCommand(0x74);
    EPD_SendData(0x54);
    EPD_SendCommand(0x75);
    EPD_SendData(0x3b);
    EPD_SendCommand(0x01);		// Set MUX as 212
    EPD_SendData(0xD3);
    EPD_SendData(0x00);
    EPD_SendData(0x00);
    EPD_SendCommand(0x3A);		// Set 100Hz
    EPD_SendData(0x18);         // Set 120Hz
    EPD_SendCommand(0x3B);		// Set 100Hz
    EPD_SendData(0x05);         // Set 120Hz
    EPD_SendCommand(0x11);		// data enter mode
    EPD_SendData(0x03);		///01
    EPD_SendCommand(0x44);		// set RAM x address start/end, in page 36
    EPD_SendData(0x00);		// RAM x address start at 00h;
    EPD_SendData(0x0c);		// RAM x address end at 0fh(12+1)*8->104 
    EPD_SendCommand(0x45);		// set RAM y address start/end, in page 37
    EPD_SendData(0x00);		
    EPD_SendData(0x00);		// RAM y address startat 00h;
    EPD_SendData(0xD3);				// RAM y address end at 212
    EPD_SendData(0x00);	
    EPD_SendData(0x00);		
    EPD_SendCommand(0x04);		// set VSH,VSL value
    EPD_SendData(0x2D);		// 	    2D13  11v
    EPD_SendData(0xb2);		//	    2D13   6v 
    EPD_SendData(0x22);		//	    2D13  -11v
    EPD_SendCommand(0x2C);           // vcom
    EPD_SendData(0x50);           //-2.0V     
    EPD_SendCommand(0x3C);		// board
    EPD_SendData(0x33);		//GS1-->GS1
    
    EPD_SendCommand(DISPLAY_UPDATE_CONTROL_1);
    EPD_SendData(0x80);//Inverse RED RAM content
             
    EPD_SetLut();
 */  		
     
    return 0;
}

/******************************************************************************
function :	Clear screen
parameter:
******************************************************************************/
void EPD_Clear(void)
{
    UWORD Width, Height,j,i;
    Width = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
    Height = EPD_HEIGHT;
    EPD_SetWindows(0, 0, EPD_WIDTH, EPD_HEIGHT);
  
  for (j = 0; j < Height; j++) {
        EPD_SetCursor(0, j);
        EPD_SendCommand(WRITE_RAM);
        for (i = 0; i < Width; i++) {
            EPD_SendData(0XFF);
        }
    }

  for (j = 0; j < Height; j++) {
        EPD_SetCursor(0, j);
        EPD_SendCommand(WRITE_RAM_RED);
        for (i = 0; i < Width; i++) {
            EPD_SendData(0XFF);
        }
    }

    EPD_TurnOnDisplay();
}

/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void EPD_Display(const UBYTE *blackimage, const UBYTE *redimage)
{
    UWORD Width, Height,j,i;
    Width = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
    Height = EPD_HEIGHT;

    UDOUBLE Addr = 0;
    // UDOUBLE Offset = ImageName;
    EPD_SetWindows(0, 0, EPD_WIDTH, EPD_HEIGHT);
    for (j = 0; j < Height; j++) {
        EPD_SetCursor(0, j);
        EPD_SendCommand(WRITE_RAM);
        for (i = 0; i < Width; i++) {
            Addr = i + j * Width;
            EPD_SendData(blackimage[Addr]);
        }
    }

    for (j = 0; j < Height; j++) {
        EPD_SetCursor(0, j);
        EPD_SendCommand(WRITE_RAM_RED);
        for (i = 0; i < Width; i++) {
            Addr = i + j * Width;
            EPD_SendData(redimage[Addr]);
        }
    }

    EPD_TurnOnDisplay();
}

/******************************************************************************
function :	Enter sleep mode
parameter:
******************************************************************************/
void EPD_Sleep(void)
{
    EPD_SendCommand(DEEP_SLEEP_MODE);
    EPD_SendData(0x01);
   
}
