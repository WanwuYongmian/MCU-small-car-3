#ifndef _LED_H
#define _LED_H

#include <hidef.h> 
#include "derivative.h"

#define   LED_ON     0
#define   LED_OFF    1
#define   LED        PORTA_PA0 

/*-------------------------------------------------------------------------*/
/*                              º¯ÊýÉùÃ÷                                   */
/*-------------------------------------------------------------------------*/

void led_control (void);
void led_initial(void);


#endif