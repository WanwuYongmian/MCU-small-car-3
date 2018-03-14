
#ifndef __WJK_SD_H
#define __WJK_SD_H     

//#define USEING_SD_CARD

#include "common.h"
#include "include.h"
#define SD_SPIn_x   SPI1      //ѡ���spiģ��
#define SD_CS_PIN   SPI1_PCS0_PIN   //Ƭѡ������
#define SD_CS       SPI_PCS0    //spiƬѡ  ����Ƭѡ��������


#define SD_select()    gpio_set(SD_CS_PIN,0)  //�͵�ƽ
#define SD_deselect()  gpio_set(SD_CS_PIN,1)  //�ߵ�ƽ


/* SD�����Ͷ��� */
#define SD_TYPE_MMC     4
#define SD_TYPE_V1      1
#define SD_TYPE_V2      2
#define SD_TYPE_V2HC    3



uint8 SPI_Byte(uint8 value);
void SD_Init(void);
uint8 SD_send_command(uint8 cmd, long arg);
uint8 SD_SendCommand_NoDeassert(uint8 cmd, long arg);
uint8 SD_Reset(void);
uint8 read_block(long sector, uint8* buffer);
uint8 write_block(long sector, uint8* buffer);
 


#endif