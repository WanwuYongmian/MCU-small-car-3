/**************************************************************************
Module Name: Serial Digital Scope Module
Module Date:  2013/4/2
Module Auth:  XiaoGo_O Modulated
Description:   Serial Digital Scope For XS128
Others:      Modulate for S12XS128 112PINS.
           DEBUG SUCCESS IN 2013/4/7
           in 32M Bus Speed.
 Revision History:

WARN!
SRS.c depend on USART
please ensure that uart_putchar() has been implemented
Ensure that SCI has been configured in 9600bps mode.
**************************************************************************/
#ifndef SDS_outputdata_H
#define SDS_outputdata_H

#include "common.h"
#include "MK60_uart.h" //��֤sci��ͷ�ļ�ƥ��
#define SDS_UART UART3       

#define SDS_SCI_SEND_CHANNEL(x) uart_putchar (SDS_UART, x)  //��֤sci���ͺ��� SCI_send()��sci.c�ж���ƥ�� 
/*------------------------------------Extern Variables------------------------------------*/
//void SDS_OutPut_Data(float []);
void WirelessSerial(int q,int w,int e,int r);  //���ô˺�������λ����������
void putstr(unsigned char ch[],unsigned char f);
unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT);
#endif  
