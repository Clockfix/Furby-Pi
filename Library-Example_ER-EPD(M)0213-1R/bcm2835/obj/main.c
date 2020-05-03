/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
Examples for ER-EPD0213-1R
Display is Hardward SPI 4-Wire SPI Interface 
Tested and worked with: 
Works with Raspberry pi
****************************************************/
#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include <time.h>
#include "GUI_Paint.h"
#include "GUI_BMPfile.h"
#include "ImageData.h"
#include "ER-EPD0213-1R.h"

void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:Goto Sleep mode\r\n");
    EPD_Sleep();
    DEV_ModuleExit();

    exit(0);
}

int main(void)
{
    printf("2.13inch e-Paper demo\r\n");
    DEV_ModuleInit();

    // Exception handling:ctrl + c
    signal(SIGINT, Handler);

    if(EPD_Init() != 0) {
        printf("e-Paper init failed\r\n");
    }
    printf("epd  clear\r\n");
    EPD_Clear();
    DEV_Delay_ms(200);

    //Create a new image cache named IMAGE_BW and fill it with white
     UBYTE *BlackImage, *RedImage;
    UWORD Imagesize = ((EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1)) * EPD_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        exit(0);
    }
    if((RedImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for red memory...\r\n");
        exit(0);
    }
    printf("NewImage:BlackImage and RedImage\r\n");
    Paint_NewImage(BlackImage, EPD_WIDTH, EPD_HEIGHT, 0, WHITE);
    Paint_NewImage(RedImage, EPD_WIDTH, EPD_HEIGHT, 0, WHITE);
   //Select Image
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    Paint_SelectImage(RedImage);
    Paint_Clear(WHITE);

#if 1
    /* show bmp */
  /*  printf("show bmp\r\n");    
    Paint_SelectImage(BlackImage);    
    Paint_Clear(WHITE); 
    GUI_ReadBmp("./pic/100x100.bmp", 0, 0);

    printf("read red bmp\r\n");
    Paint_SelectImage(RedImage);
    Paint_Clear(WHITE);
    
    EPD_Display(BlackImage, RedImage);
    DEV_Delay_ms(2000);
    */

  
    printf("show bmp\r\n");
    printf("read black bmp\r\n");
    Paint_SelectImage(BlackImage);
    GUI_ReadBmp("./pic/213-1rb1.bmp", 0, 0);
    printf("read red bmp\r\n");
    Paint_SelectImage(RedImage);
    GUI_ReadBmp("./pic/213-1rr1.bmp", 0, 0);
    EPD_Display(BlackImage, RedImage);
    DEV_Delay_ms(2000);

  
    printf("show bmp\r\n");
    printf("read black bmp\r\n");
    Paint_SelectImage(BlackImage);
    GUI_ReadBmp("./pic/213-1rb2.bmp", 0, 0);
    printf("read red bmp\r\n");
    Paint_SelectImage(RedImage);
    GUI_ReadBmp("./pic/213-1rr2.bmp", 0, 0);
    EPD_Display(BlackImage, RedImage);
    DEV_Delay_ms(2000);

#endif

#if 1
    /*show image for array*/
    printf("show image for array\r\n");
    Paint_SelectImage(BlackImage);
    Paint_DrawBitMap(IMAGE_BLACK);

    Paint_SelectImage(RedImage);
    Paint_DrawBitMap(IMAGE_RED);

    EPD_Display(BlackImage, RedImage);
    DEV_Delay_ms(2000);
#endif

    printf("Paint_NewImage\r\n");
    Paint_NewImage(BlackImage, EPD_WIDTH, EPD_HEIGHT, 90, WHITE);
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);

#if 1   // Drawing on the image
    printf("Drawing\r\n");
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    Paint_DrawLine(130, 70, 160, 100, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawLine(160, 70, 130, 100, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);             
    Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawLine(45, 85, 75, 85, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawLine(60, 70, 60, 100, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawRectangle(170, 70, 200, 100, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    Paint_DrawCircle(100, 85, 15, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    Paint_DrawString_EN(10, 20, "hello world", &Font12, WHITE, BLACK);
    Paint_DrawNum(10, 50, 987654321, &Font16, BLACK,WHITE );

    Paint_SelectImage(RedImage);
    Paint_Clear(WHITE);   

    Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);      
    Paint_DrawRectangle(130, 70, 160, 100, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawCircle(60, 85, 15, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);       
    Paint_DrawString_EN(10, 2, "www.buydisplay.com", &Font16, BLACK, WHITE);
    Paint_DrawNum(10, 33, 123456789, &Font12, WHITE,BLACK );

    EPD_Display(BlackImage, RedImage);
    DEV_Delay_ms(2000);
#endif

    DEV_Delay_ms(15000);
    printf("epd  clear\r\n");
    EPD_Clear();

    printf("Goto Sleep mode...\r\n");
    EPD_Sleep();
    free(BlackImage);
    return 0;
}
