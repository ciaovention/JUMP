//////////////////////////////////////////////////////////////////////////////////	 
//******************************************************************************/

#include "ssd1306.h"
//#include "stdlib.h"	 
//#include "delay.h"
#include "nrf_gpio.h"

SSD1306_Init_Struct ssd1306_init_struct;
Screen_Pub_RAM   screen;

//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   
static void oled_delay_ms(unsigned int ms)
{                         
	unsigned int a;
	while(ms)
	{
		a=1800;
		while(a--);
		ms--;
	}
	return;
}

uint32_t ssd1306_Init()
{
  //nrf_gpio_cfg_output(ssd1306_init_struct.SCL);
  
  return 0;
}

uint32_t ssd1306_config(SSD1306_Init_Struct * Init_Struct)
{
  ssd1306_init_struct = *Init_Struct;
  
  return ssd1306_Init();
}


static void OLED_SCLK_Set()
{
  nrf_gpio_cfg_output(ssd1306_init_struct.SCL);
  nrf_gpio_pin_set(ssd1306_init_struct.SCL);
}

static void OLED_SDIN_Set()
{
  nrf_gpio_cfg_output(ssd1306_init_struct.SDA);
  nrf_gpio_pin_set(ssd1306_init_struct.SDA);
}

static void	OLED_SDIN_Clr()
{
  nrf_gpio_cfg_output(ssd1306_init_struct.SDA);
  nrf_gpio_pin_clear(ssd1306_init_struct.SDA);
}
	
static void OLED_SCLK_Clr()
{
  nrf_gpio_cfg_output(ssd1306_init_struct.SCL);
  nrf_gpio_pin_clear(ssd1306_init_struct.SCL);
}

/**********************************************
//IIC Start
**********************************************/
void IIC_Start()
{

	OLED_SCLK_Set() ;
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{

	OLED_SCLK_Clr();
	OLED_SDIN_Clr();
	OLED_SDIN_Set();
	OLED_SCLK_Set() ;
}
/**********************************************
// IIC Write byte
**********************************************/

void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m,da;
	da=IIC_Byte;
	for(i=0;i<8;i++)		
	{
			m=da;
			OLED_SCLK_Clr();
		m=m&0x80;
		if(m==0x80)
		{OLED_SDIN_Set();}
		else OLED_SDIN_Clr();
			da=da<<1;
		OLED_SCLK_Set();
		}

	OLED_SCLK_Clr();
	OLED_SCLK_Set() ;
}
/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   Write_IIC_Byte(0x78);            //Slave address,SA0=0
   Write_IIC_Byte(0x00);			//write command
   Write_IIC_Byte(IIC_Command); 
   IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
   IIC_Start();
   Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
   Write_IIC_Byte(0x40);			//write data
   Write_IIC_Byte(IIC_Data);
   IIC_Stop();
}
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
			{
   IIC_Start();
   Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
   Write_IIC_Byte(0x40);			//write data
   Write_IIC_Byte(dat);
   IIC_Stop();
		}
	else {
		IIC_Start();
   Write_IIC_Byte(0x78);            //Slave address,SA0=0
   Write_IIC_Byte(0x00);			//write command
   Write_IIC_Byte(dat); 
   IIC_Stop();
		
	}


}


/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,0);		//page0-page1
		OLED_WR_Byte(0x00,0);		//low column start address
		OLED_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED_WR_Byte(fill_Data,1);
			}
	}
}


/***********************Delay****************************************/
void Delay_50ms(unsigned int Del_50ms)
{
	unsigned int m;
	for(;Del_50ms>0;Del_50ms--)
		for(m=6245;m>0;m--);
}

void Delay_1ms(unsigned int Del_1ms)
{
	unsigned char j;
	while(Del_1ms--)
	{	
		for(j=0;j<123;j++);
	}
}

//坐标设置

void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}   	

//开启OLED显示    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<7;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		//for(n=0;n<128;n++)OLED_WR_Byte(0x50,OLED_DATA); 
    for(n=0;n<128;n++)
    {
      OLED_WR_Byte(0x00,OLED_DATA); 
    }
	} //更新显示
}
void OLED_On(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA); 
	} //更新显示
}

static const uint8_t code[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

void OLED_Refresh_all(void)
{
  uint8_t i,n;		  
  uint8_t data;
  uint8_t l,r;
  
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
    
		for(n=0;n<128;n++)
    {
      l = n/8;
      r = n%8;
      
      data = 0;
      
      data |= ((screen.ram_pixel[(i*8)+0][l]) & code[r])?0x80:0x00;
      data >>= 1;
      data |= ((screen.ram_pixel[(i*8)+1][l]) & code[r])?0x80:0x00;
      data >>= 1;
      data |= ((screen.ram_pixel[(i*8)+2][l]) & code[r])?0x80:0x00;
      data >>= 1;
      data |= ((screen.ram_pixel[(i*8)+3][l]) & code[r])?0x80:0x00;
      data >>= 1;
      data |= ((screen.ram_pixel[(i*8)+4][l]) & code[r])?0x80:0x00;
      data >>= 1;
      data |= ((screen.ram_pixel[(i*8)+5][l]) & code[r])?0x80:0x00;
      data >>= 1;
      data |= ((screen.ram_pixel[(i*8)+6][l]) & code[r])?0x80:0x00;
      data >>= 1;
      data |= ((screen.ram_pixel[(i*8)+7][l]) & code[r])?0x80:0x00;
      
      OLED_WR_Byte(data,OLED_DATA); 
    }
	} //更新显示
}


//初始化SSD1306					    
void OLED_Init(void)
{ 	
  oled_delay_ms(100);
  OLED_WR_Byte(0xAE,OLED_CMD);//关闭显示
	
	OLED_WR_Byte(0x40,OLED_CMD);//---set low column address
	OLED_WR_Byte(0xB0,OLED_CMD);//---set high column address

	OLED_WR_Byte(0xC8,OLED_CMD);//-not offset

	OLED_WR_Byte(0x81,OLED_CMD);//设置对比度
	OLED_WR_Byte(0xff,OLED_CMD);

	OLED_WR_Byte(0xa1,OLED_CMD);//段重定向设置

	OLED_WR_Byte(0xa6,OLED_CMD);//
	
	OLED_WR_Byte(0xa8,OLED_CMD);//设置驱动路数
	OLED_WR_Byte(0x1f,OLED_CMD);
	
	OLED_WR_Byte(0xd3,OLED_CMD);
	OLED_WR_Byte(0x00,OLED_CMD);
	
	OLED_WR_Byte(0xd5,OLED_CMD);
	OLED_WR_Byte(0xf0,OLED_CMD);
	
	OLED_WR_Byte(0xd9,OLED_CMD);
	OLED_WR_Byte(0x22,OLED_CMD);
	
	OLED_WR_Byte(0xda,OLED_CMD);
	OLED_WR_Byte(0x02,OLED_CMD);
	
	OLED_WR_Byte(0xdb,OLED_CMD);
	OLED_WR_Byte(0x49,OLED_CMD);
	
	OLED_WR_Byte(0x8d,OLED_CMD);
	OLED_WR_Byte(0x14,OLED_CMD);
	
	OLED_WR_Byte(0xaf,OLED_CMD);
	OLED_Clear();
}  





























