/********************************************************
【平    台】龙丘K10/60DN/DX多功能开发板
【编    写】龙丘
【Designed】by Chiu Sir
【E-mail  】chiusir@yahoo.cn
【软件版本】V1.0
【最后更新】2013年1月16日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
------------------------------------------------
【dev.env.】CodeWarrior IAR6.10,6.30
【Target  】K60DX/DN
【Crystal 】50.000Mhz
【busclock】???.000MHz
【pllclock】100.000MHz
***************************
------------------------------------
  使用说明：
OLED电源使用3.3V。
----------------
G    电源地
3.3V 接3.3V电源
CS   PORTc12
SCK  PORTc13
SDA  PORTc14
A0   PORTc15
RST  PORTc16  已接地，不用接
（5V的单片机需要在信号线上串接1K电阻，电源必须保证3.3V）
********************************************************/

#ifndef __SGP18T_LCD_BASE_H__
#define __SGP18T_LCD_BASE_H__
#include "common.h"

/*******************接口定义******************************/

/*
    //设置PORTA pin12-15为GPIO口
        PORTC_PCR12=(0|PORT_PCR_MUX(1));//CS
	PORTC_PCR13=(0|PORT_PCR_MUX(1));//SCK
	PORTC_PCR14=(0|PORT_PCR_MUX(1));//SDI
	PORTC_PCR15=(0|PORT_PCR_MUX(1));//A0
	PORTC_PCR16=(0|PORT_PCR_MUX(1));//RST
*/


#define byte uint8
#define word uint16
#define GPIO_PIN_MASK      0x1Fu    //0x1f=31,限制位数为0--31有效
#define GPIO_PIN(x)        (((1)<<(x & GPIO_PIN_MASK)))  //把当前位置1

/*#define		RED		0xf800
#define		GREEN		0x07e0
#define		BLUE		0x001f
#define		PURPLE		0xf81f
#define		YELLOW		0xffe0
#define		CYAN		0x07ff 		//蓝绿色
#define		ORANGE		0xfc08
#define		BLACK		0x0000
#define		WHITE		0xffff
                                       */
/*****************私有函数声名*********************************/

void LCD_init2(void);									//LCD初始化

void LCD_write_command(uint8 cmd);						//发送控制字

void LCD_write_para8(uint8 dat);						//发送数据参数

void LCD_write_para16(uint16 dat);						//发送像素显示参数

void LCD_address_rst(void);							    //DDRAM地址重置

void LCD_SetPos(uint8 xs,uint8 ys,uint8 xe,uint8 ye);	//定位显示像素位置

void delay(uint16 t);									//延时函数

void LCD_display_full(uint16 color);					//全屏显示某种颜色


void LCD_draw_part(uint8 xs,uint8 ys,uint8 xe,uint8 ye,uint16 color_dat);
															//填充矩形区域，行起始、终止坐标，列起始、终止坐标，颜色

void LCD_draw_line(uint8 xs,uint8 ys,uint8 xe,uint8 ye,uint16 color_dat);
															//画线，行起始、终止坐标，列起始、终止坐标，颜色

void LCD_draw_rectangle(uint8 xs,uint8 ys,uint8 xe,uint8 ye,uint16 color_dat);
															//画矩形边框，行起始、终止坐标，列起始、终止坐标，颜色

void LCD_draw_circle(uint8 x,uint8 y,uint8 r,uint16 color_dat);
															//画圆形边框，圆心横坐标、纵坐标，半径，颜色

void LCD_draw_dot(uint8 x,uint8 y,uint16 color_dat);	//画点，横坐标，纵坐标，颜色
void LCD_Img_Binary2( Size_t size, uint8 *img);
void display_pic();//显示图片


void LCD_P8X16(uint8 x, uint8 y, uint8 c_dat,uint16 word_color,uint16 back_color);

void LCD_P8X16Str(uint8 x, uint8 y, uint8 *s_dat,uint16 word_color,uint16 back_color);

void LCD_LCD_P6X8(uint8 x, uint8 y, uint8 c_dat,uint16 word_color,uint16 back_color);

void LCD_P6X8Str(uint8 x, uint8 y, uint8 *s_dat,uint16 word_color,uint16 back_color);

void LCD_P6X8NUM(uint8 x, uint8 y, uint16 num, uint8 num_bit,uint16 word_color,uint16 back_color);

void LCD_P8X8(uint8 x, uint8 y, uint8 c_dat,uint16 word_color,uint16 back_color);

void LCD_P8X8Str(uint8 x, uint8 y, uint8 *s_dat,uint16 word_color,uint16 back_color);

void LCD_P8X8NUM(uint8 x, uint8 y, uint16 num, uint8 num_bit,uint16 word_color,uint16 back_color);

void LCD_P16x16Str(unsigned char x,unsigned char y,uint8 *s_dat,uint16 word_color,uint16 back_color);
void LCD_P16x12Str(unsigned char x,unsigned char y,uint8 *s_dat,uint16 word_color,uint16 back_color);
void show_pic(uint8 xs,uint8 ys,uint8 xe,uint8 ye,uint8 pic[]);

#endif /*SGP18T_ILI9163B.h*/