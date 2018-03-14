#ifndef _BOTTON_H
#define _BOTTON_H

 
#include "common.h"
#include "MK60_port.h"
#include "MK60_gpio.h"


#define KEY_1         PTC9
//#define KEY_2         PTD12
//#define KEY_3         PTD10
//#define KEY_4         PTD8
//#define KEY_5         PTD6


//#define KEY_RIGHT  PORTA_PA2
//#define KET_PULL_UP_ENABLE  PUCR_PUPAE = 1

#define key_Init()               port_init(KEY_1, ALT1 | PULLUP );gpio_ddr(KEY_1, GPI)        //;\
                                 port_init(KEY_2, ALT1 | PULLUP );gpio_ddr(KEY_2, GPI);\
                                 port_init(KEY_3, ALT1 | PULLUP );gpio_ddr(KEY_3, GPI);\
                                 port_init(KEY_4, ALT1 | PULLUP );gpio_ddr(KEY_4, GPI);\
                                   port_init(KEY_5, ALT1 | PULLUP );gpio_ddr(KEY_5, GPI)
                                    
#define Key_get(key)            gpio_get(key)
/*-------------------------------------------------------------------------*/
/*                              º¯ÊýÉùÃ÷                                   */
/*-------------------------------------------------------------------------*/
 char button_scan(void);   //°´¼üÉ¨Ãè

#endif