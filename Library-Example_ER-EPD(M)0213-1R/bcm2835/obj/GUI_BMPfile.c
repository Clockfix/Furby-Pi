/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
****************************************************/

#include "GUI_BMPfile.h"
#include "GUI_Paint.h"
#include "Debug.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>	//exit()
#include <string.h> //memset()
#include <math.h> //memset()

UBYTE GUI_ReadBmp(const char *path, UWORD Xstart, UWORD Ystart)
{
    FILE *fp;                     //Define a file pointer
    BMPFILEHEADER bmpFileHeader;  //Define a bmp file header structure
    BMPINFOHEADER bmpInfoHeader;  //Define a bmp info header structure
    
    
    // Binary file open
    if((fp = fopen(path, "rb")) == NULL) {
        Debug("Cann't open the file!\n");
        exit(0);
    }

    // Set the file pointer from the beginning
    fseek(fp, 0, SEEK_SET);
    fread(&bmpFileHeader, sizeof(BMPFILEHEADER), 1, fp);    //sizeof(BMPFILEHEADER) must be 14
    fread(&bmpInfoHeader, sizeof(BMPINFOHEADER), 1, fp);    //sizeof(BMPFILEHEADER) must be 50
    printf("pixel = %d * %d\r\n", bmpInfoHeader.biWidth, bmpInfoHeader.biHeight);
    
    UWORD Image_Width_Byte = (bmpInfoHeader.biWidth % 8 == 0)? (bmpInfoHeader.biWidth / 8): (bmpInfoHeader.biWidth / 8 + 1);
    UWORD Bmp_Width_Byte = (Image_Width_Byte % 4 == 0) ? Image_Width_Byte: ((Image_Width_Byte / 4 + 1) * 4);    
    UBYTE Image[Image_Width_Byte * bmpInfoHeader.biHeight];
    memset(Image, 0xFF, Image_Width_Byte * bmpInfoHeader.biHeight);
    
    // Determine if it is a monochrome bitmap
    int readbyte = bmpInfoHeader.biBitCount;
    if(readbyte != 1){
        Debug("the bmp Image is not a monochrome bitmap!\n");
        exit(0);
    }
    
    // Determine black and white based on the palette
    UWORD i;
    UWORD Bcolor, Wcolor;
    UWORD bmprgbquadsize = pow(2, bmpInfoHeader.biBitCount);// 2^1 = 2
    BMPRGBQUAD bmprgbquad[bmprgbquadsize];        //palette
    
    for(i = 0; i < bmprgbquadsize; i++){
        fread(&bmprgbquad[i * 4], sizeof(BMPRGBQUAD), 1, fp);
    }
    if(bmprgbquad[0].rgbBlue == 0xff && bmprgbquad[0].rgbGreen == 0xff && bmprgbquad[0].rgbRed == 0xff){
        Bcolor = BLACK;
        Wcolor = WHITE;
    }else{
        Bcolor = WHITE;
        Wcolor = BLACK;
    }
    
    // Read image data into the cache
    UWORD x, y;
    UBYTE Rdata; 
    fseek(fp, bmpFileHeader.bOffset, SEEK_SET);
    for(y = 0; y < bmpInfoHeader.biHeight; y++) {//Total display column
        for(x = 0; x < Bmp_Width_Byte; x++) {//Show a line in the line
            if(fread((char *)&Rdata, 1, readbyte, fp) != readbyte) {
                perror("get bmpdata:\r\n");
                break;
            }
            if(x < Image_Width_Byte) { //bmp
                Image[x + (bmpInfoHeader.biHeight - y - 1) * Image_Width_Byte] =  Rdata;
                // printf("rdata = %d\r\n", Rdata);
            }
        }
    }    
    fclose(fp);
    
    // Refresh the image to the display buffer based on the displayed orientation
    UBYTE color, temp;
    for(y = 0; y < bmpInfoHeader.biHeight; y++){
        for(x = 0; x < bmpInfoHeader.biWidth; x++){
            if(x > Paint.Width || y > Paint.Height){
                break;
            }
            temp = Image[(x / 8) + (y * Image_Width_Byte)];
            color = (((temp << (x%8)) & 0x80) == 0x80) ?Bcolor:Wcolor;      
            Paint_SetPixel(Xstart + x, Ystart + y, color);
        }
    }
    return 0;
}


