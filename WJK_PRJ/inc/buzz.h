#ifndef _BUZZ_H
#define _BUZZ_H

#include "common.h"
#include "MK60_port.h"
#include "MK60_gpio.h"
#include "bluetooth_use.h"

#define   BUZZER         PTD3
#define   BUZZER_ON      1
#define   BUZZER_OFF     0
extern char     buzz_mode_flag;


#define BUZZER_DIR_OUT        gpio_init (BUZZER, GPO,BUZZER_OFF)
#define BUZZER_TURN           gpio_turn(BUZZER)
#define BUZZER_TURN_ON        gpio_set (BUZZER,BUZZER_ON)
#define BUZZER_TURN_OFF       gpio_set (BUZZER,BUZZER_OFF)

/*-------------------------------------------------------------------------*/
/*                              º¯ÊýÉùÃ÷                                   */
/*-------------------------------------------------------------------------*/
void buzz_run(void);
void buzz_initial(void);
#endif