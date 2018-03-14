/********************************************************
��ƽ    ̨������K10/60DN/DX�๦�ܿ�����
����    д������
��Designed��by Chiu Sir
��E-mail  ��chiusir@yahoo.cn
������汾��V1.0
�������¡�2013��1��16��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��CodeWarrior IAR6.10,6.30
��Target  ��K60DX/DN
��Crystal ��50.000Mhz
��busclock��???.000MHz
��pllclock��100.000MHz
***************************
------------------------------------
  ʹ��˵����
OLED��Դʹ��3.3V��
----------------
G    ��Դ��
3.3V ��3.3V��Դ
CS   PORTc12
SCK  PORTc13
SDA  PORTc14
A0   PORTc15
RST  PORTc16  �ѽӵأ����ý�
��5V�ĵ�Ƭ����Ҫ���ź����ϴ���1K���裬��Դ���뱣֤3.3V��
********************************************************/

#ifndef __SGP18T_LCD_BASE_H__
#define __SGP18T_LCD_BASE_H__
#include "common.h"

/*******************�ӿڶ���******************************/

/*
    //����PORTA pin12-15ΪGPIO��
        PORTC_PCR12=(0|PORT_PCR_MUX(1));//CS
	PORTC_PCR13=(0|PORT_PCR_MUX(1));//SCK
	PORTC_PCR14=(0|PORT_PCR_MUX(1));//SDI
	PORTC_PCR15=(0|PORT_PCR_MUX(1));//A0
	PORTC_PCR16=(0|PORT_PCR_MUX(1));//RST
*/


#define byte uint8
#define word uint16
#define GPIO_PIN_MASK      0x1Fu    //0x1f=31,����λ��Ϊ0--31��Ч
#define GPIO_PIN(x)        (((1)<<(x & GPIO_PIN_MASK)))  //�ѵ�ǰλ��1

/*#define		RED		0xf800
#define		GREEN		0x07e0
#define		BLUE		0x001f
#define		PURPLE		0xf81f
#define		YELLOW		0xffe0
#define		CYAN		0x07ff 		//����ɫ
#define		ORANGE		0xfc08
#define		BLACK		0x0000
#define		WHITE		0xffff
                                       */
/*****************˽�к�������*********************************/

void LCD_init2(void);									//LCD��ʼ��

void LCD_write_command(uint8 cmd);						//���Ϳ�����

void LCD_write_para8(uint8 dat);						//�������ݲ���

void LCD_write_para16(uint16 dat);						//����������ʾ����

void LCD_address_rst(void);							    //DDRAM��ַ����

void LCD_SetPos(uint8 xs,uint8 ys,uint8 xe,uint8 ye);	//��λ��ʾ����λ��

void delay(uint16 t);									//��ʱ����

void LCD_display_full(uint16 color);					//ȫ����ʾĳ����ɫ


void LCD_draw_part(uint8 xs,uint8 ys,uint8 xe,uint8 ye,uint16 color_dat);
															//��������������ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ

void LCD_draw_line(uint8 xs,uint8 ys,uint8 xe,uint8 ye,uint16 color_dat);
															//���ߣ�����ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ

void LCD_draw_rectangle(uint8 xs,uint8 ys,uint8 xe,uint8 ye,uint16 color_dat);
															//�����α߿�����ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ

void LCD_draw_circle(uint8 x,uint8 y,uint8 r,uint16 color_dat);
															//��Բ�α߿�Բ�ĺ����ꡢ�����꣬�뾶����ɫ

void LCD_draw_dot(uint8 x,uint8 y,uint16 color_dat);	//���㣬�����꣬�����꣬��ɫ
void LCD_Img_Binary2( Size_t size, uint8 *img);
void display_pic();//��ʾͼƬ


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