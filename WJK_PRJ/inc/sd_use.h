#ifndef _SD_USE_H
#define _SD_USE_H
 
#include "common.h"
#include "WJK_SD.h"

//#define USEING_SD_CARD
extern uint8  buff_full_flag;


void lode_to_buff (uint8* buff,uint8 count);
void SD_lowcomp_init(void);
void save_sd (void);
#endif