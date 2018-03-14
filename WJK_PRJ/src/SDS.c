
#include "SDS.h"
//#include "uart.h"  //LINK TO UART

float SDS_OutData[4] = { 0 };

unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
{
    unsigned short CRC_Temp;
    unsigned char i,j;
    CRC_Temp = 0xffff;

    for (i=0;i<CRC_CNT; i++){      
        CRC_Temp ^= Buf[i];
        for (j=0;j<8;j++) {
            if (CRC_Temp & 0x01)
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
    return(CRC_Temp);
}
/* //原版的虚拟示波器程序
void SDS_OutPut_Data(float S_Out[])
{
  int temp[4] = {0};
  unsigned int temp1[4] = {0};
  unsigned char databuf[10] = {0};
  unsigned char i;
  unsigned short CRC16 = 0; 
  float SDS_OutData[4];
  for(i=0;i<4;i++) {
  SDS_OutData[i]=S_Out[i];
  }
  for(i=0;i<4;i++)
   {
    
    temp[i]  = (int)SDS_OutData[i];
    temp1[i] = (unsigned int)temp[i];
    
   }
   
  for(i=0;i<4;i++) 
  {
    databuf[i*2]   = (unsigned char)(temp1[i]%256);
    databuf[i*2+1] = (unsigned char)(temp1[i]/256);
  }
  
  CRC16 = CRC_CHECK(databuf,8);
  databuf[8] = CRC16%256;
  databuf[9] = CRC16/256;
  
  for(i=0;i<10;i++)
    uart_putchar(databuf[i]);  //LINK TO UART 
}

 */




//////////////////////////////////
void WirelessSerial(int q,int w,int e,int r)
{
  int num;
  unsigned char TxBuf[10];

  TxBuf[0] = (char)q;        
  TxBuf[1] = q>>8;     
       
  TxBuf[2] = (char)w;             
  TxBuf[3] =w>>8;       
     
  TxBuf[4] = (char)e;
  TxBuf[5] = e>>8;             
  
  TxBuf[6] = (char)r;               
  TxBuf[7] = r>>8;             

  
  num = CRC_CHECK(TxBuf,8);       
  TxBuf[8] = num & 0xFF;           
  TxBuf[9] = num >> 8;             
                                 
  putstr(TxBuf,10); 
}

//////////////////////////////////////

 void putstr(unsigned char ch[],unsigned char f)
{
  unsigned char i=0;
  for(i=0;i<f;i++)
  {
      SDS_SCI_SEND_CHANNEL((unsigned char)ch[i]);
  }     
  
}


