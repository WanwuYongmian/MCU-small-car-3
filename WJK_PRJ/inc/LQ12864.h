#ifndef _LQOLED_H
#define _LQOLED_H

#include "common.h"
#include "MK60_port.h"
#include "MK60_gpio.h"


#define LCD12864_SCL PTC18
#define LCD12864_SDA PTD0
#define LCD12864_RST PTC17
#define LCD12864_DC  PTD2

#define LCD12864_SCL_OUT             gpio_init ( LCD12864_SCL, GPO,0)
#define LCD12864_SDA_OUT             gpio_init ( LCD12864_SDA, GPO,0)
#define LCD12864_RST_OUT             gpio_init ( LCD12864_RST, GPO,0)
#define LCD12864_DC_OUT              gpio_init ( LCD12864_DC, GPO,0)   //方向输出

#define SET_SCL                 gpio_set (LCD12864_SCL,1)
#define CLEAR_SCL               gpio_set (LCD12864_SCL,0)
#define SET_SDA                 gpio_set (LCD12864_SDA,1)
#define CLEAR_SDA               gpio_set (LCD12864_SDA,0)
#define SET_RST                 gpio_set (LCD12864_RST,1)
#define CLEAR_RST               gpio_set (LCD12864_RST,0)
#define SET_DC                  gpio_set (LCD12864_DC,1)
#define CLEAR_DC                gpio_set (LCD12864_DC,0)


 /*-------------------------------------------------------------------------*/
/*                              函数声明                                   */
/*-------------------------------------------------------------------------*/

 void KEY_and_LCD12864_Iint(void);//屏幕初始化
 void display_menu (void);//显示菜单
 void display_line (unsigned char *p,int a,char y);//显示整行
 void number (int num,unsigned char x,unsigned char y); //显示数字
 extern uint8 longqiu96x64[768];
 void LCD12864_Init(void);
 void LCD12864_CLS(void);
 void LCD12864_P6x8Str(uint8 x,uint8 y,uint8 ch[]);
 void LCD12864_P8x16Str(uint8 x,uint8 y,uint8 ch[]);
 void LCD12864_P14x16Str(uint8 x,uint8 y,uint8 ch[]);
 void LCD12864_Print(uint8 x, uint8 y, uint8 ch[]);
 void LCD12864_PutPixel(uint8 x,uint8 y);
 void LCD12864_Rectangle(uint8 x1,uint8 y1,uint8 x2,uint8 y2,uint8 gif);
 void Draw_LQLogo(void);
 void Draw_LibLogo(void);
 void Draw_BMP(uint8 x0,uint8 y0,uint8 x1,uint8 y1,uint8 bmp[]); 
 void LCD12864_Fill(uint8 dat);
 void LCD12864_Array(unsigned char *array, unsigned int y_data_max, unsigned int usRowNum, unsigned int usColumnNum);

#endif

