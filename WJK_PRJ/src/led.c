/*
 *   文件名称: LED控制
 *   文件描述: 通过置标志位把LED灯点亮或者关闭
 *
 *   当前版本: 1.0
 *   作者    : 陈巧云
 *   完成日期: 2016.1.17
 *
 *   取代版本: 无
 *   原作者  : 无
 *   完成日期: 无
 */
 
#include "led.h"

#define   LED_dir    DDRA_DDRA0

char  led_flag;


void led_initial (void)
{
   LED_dir = 1;
   LED = LED_OFF;
}
//=========================================================================
//函数名  : led_on()
//功能描述: 判断点亮LED的标志位led_flag,如果标志位为1，点亮LED,清除标志位
//          如果标志位 led_flag == 0,关闭LED
//输入参数: 标志位on_flag
//输出参数: 无
//返回值  : 无
//==========================================================================

void led_control (void) 
{
   if (led_flag == 1) 
   {
       LED = LED_ON;
   } 
   else 
   {
       LED = LED_OFF;
   }
}


