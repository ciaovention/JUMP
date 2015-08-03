#ifndef _N51822_SSD1306_H_
#define _N51822_SSD1306_H_

#include "nrf51.h"
#include "nrf51_bitfields.h"

#define u8 uint8_t
#define u32 uint32_t

typedef struct
{
  uint32_t SCL;
  uint32_t SDA;
}SSD1306_Init_Struct;


#define SCREEN_LINE_MAX 32
#define SCREEN_ROW_MAX  128

typedef union
{
	unsigned char ram_pixel[SCREEN_LINE_MAX][(SCREEN_ROW_MAX-1)/8 +1];
	unsigned char image_data[(SCREEN_LINE_MAX) * ((SCREEN_ROW_MAX-1)/8 +1)];
}Screen_Pub_RAM;

extern Screen_Pub_RAM   screen;

#define OLED_CMD  0	
#define OLED_DATA 1
#define OLED_MODE 0

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED????----------------  					   

uint32_t ssd1306_Init(void);
uint32_t ssd1306_config(SSD1306_Init_Struct * Init_Struct);


//OLED
void OLED_WR_Byte(unsigned dat,unsigned cmd);  
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_Refresh_all(void);

void IIC_Start(void);
void IIC_Stop(void);
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);





#endif //_N51822_SSD1306_H_
