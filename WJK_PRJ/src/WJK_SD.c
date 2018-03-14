#include "WJK_SD.h"

uint8 SD_Type=0;

uint8 SPI_Byte(uint8 buff)
{
  uint8 buff_put[1] = {buff};
  uint8 buff_get[1];
  
  spi_mosi (SD_SPIn_x,SD_CS,buff_put,buff_get,1);
  
  return buff_get[0];
  
}

/*************************************************************/
/*                        ��ʼ��SD��                         */
/*************************************************************/
void SD_Init(void)
{
        spi_init(SD_SPIn_x,SD_CS,MASTER,100*1000);
	SD_deselect();
        
        while(SD_Reset() != 0)
          DELAY_MS(5);
 
  spi_init(SD_SPIn_x,SD_CS,MASTER,4000*1000);

}


/*************************************************************/
/*                       ��SD��д������                      */
/*************************************************************/
uint8 SD_send_command(uint8 cmd, long arg)
{
        uint8 a;
        uint8 retry=0;
        uint8 temp;
        uint8 crc;
         SD_select(); 
        if(cmd==0) crc=0x95;  	    //CRC for CMD0(0)
        else if(cmd==8) crc=0x87;   //CRC for CMD8(0x1AA) 
        else crc=0x01;              //dummy CRC + Stop

	temp=SPI_Byte(cmd | 0x40); //�ֱ�д������
	temp=SPI_Byte(arg>>24);    //д���ַ
	temp=SPI_Byte(arg>>16);
	temp=SPI_Byte(arg>>8);
	temp=SPI_Byte(arg);
	temp=SPI_Byte(crc);
        
	SD_select();
	
        
	
  do
  {
        a = SPI_Byte(0xff);
      retry++;
  }
	while((a == 0xff)&&(retry < 10));//�ȴ���Ӧ��

	SD_deselect();
	
       temp = SPI_Byte(0xff);       //�������϶�������8��ʱ�ӣ���SD�����ʣ�µĹ���
	return a;//����״ֵ̬
}



/*************************************************************/
/*                       ��SD��д������                      */
/*  ��SD������һ������(����ʱ���ر�Ƭѡ�����к������ݴ�����  */
/*************************************************************/
uint8 SD_SendCommand_NoDeassert(uint8 cmd, long arg)
{
        uint8 a;
        uint8 retry=0;
        uint8 temp;
        uint8 crc;
        
        
        SD_select();
        
        if(cmd==0) crc=0x95;  	    //CRC for CMD0(0)
        else if(cmd==8) crc=0x87;   //CRC for CMD8(0x1AA) 
        else crc=0x01;              //dummy CRC + Stop

	temp=SPI_Byte(cmd | 0x40); //�ֱ�д������
	temp=SPI_Byte(arg>>24);    //д���ַ
	temp=SPI_Byte(arg>>16);
	temp=SPI_Byte(arg>>8);
	temp=SPI_Byte(arg);
	temp=SPI_Byte(crc);
        
        
	SD_select();
	

	
        do
        {
              a = SPI_Byte(0xff);
            retry++;
        }
              while((a == 0xff)&&(retry < 10));//�ȴ���Ӧ��


	
  
	return a;//����״ֵ̬
}



/*************************************************************/
/*           ��SD����ʼ��   ����0���ʼ���ɹ�                */
/*************************************************************/
uint8 SD_Reset (void)
{
  
      unsigned char i;
      unsigned char retry;
      unsigned char a=0;
      uint8 temp;
      uint8 re_sdtype;
      uint8 buff[4];
      uint8 ocr[4];
	
      retry = 0;
  
      SD_deselect();
  
      for(i=0;i<10;i++) temp = SPI_Byte (0xff);
  

  	
	do
	{
                      SD_select();
                    temp = SPI_Byte (0xff);
                    temp = SPI_Byte (0xff);
		a = SD_send_command(0,0);  //����������
		retry++;
		if(retry>10) return 1;      //��ʱ�˳�
	} while(a != 0x01);

      //��ʶ�𼰳�ʼ����ʼ
      re_sdtype=SD_SendCommand_NoDeassert(8,0x1aa); //��ȡ��Ƭ��SD�汾��Ϣ   sd2.0����cmd8   ��ȷӦ������2.0  Ӧ��Ƿ�������Ϊ1.0��mmc
                                      //cmd8 ��4���ֽڲ���Ϊ  ������Ч��Ӧд��0��һ��VSH��Ӧд��1�� һ��check pattern( �Ƽ�10101010)
     //2.0��ʶ�𼰳�ʼ����ʼ
      if(re_sdtype==0x01) // V2.0�Ŀ�����Ҫ����OCR���ݣ��ж���SD2.0����SD2.0HC��                        
      { 
                                   //CMD8�ᴫ��4�ֽ�����
        buff[0]=SPI_Byte(0xff);//should be 0x00
        buff[1]=SPI_Byte(0xff);//should be 0x00        
        buff[2]=SPI_Byte(0xff);//should be 0x01    ���� cmd8 ��VHS����    
        buff[3]=SPI_Byte(0xff);//should be 0xAA    ���� cmd8 ��check pattern����
        
            SD_deselect();
         temp=SPI_Byte(0xff);


       // �жϸÿ��Ƿ�֧��2.7V-3.6V�ĵ�ѹ��Χ 
        if((buff[2]==0x01)&&(buff[3]==0xAA)) //֧�ֵ�ѹ��Χ�����Բ���
        {
            retry=0;
            do 
            {            //������ʼ��ָ��CMD55+ACMD41
                a=SD_send_command(55,0);
                if(a!=0x01)
                {
                  return a;
                } 
                
                a=SD_send_command(41, 0x40000000);
                
                retry++;
                if(retry>50)
                {
                  return a ;//��ʱ�򷵻�r1״̬  
                }
            }
            while(a!=0);  //��ʼ��ָ�����ɣ���������ȡOCR��Ϣ
          
          
            //-----------����SD2.0���汾��ʼ-----------
           
            a=SD_SendCommand_NoDeassert(58,0);
            if(a!=0x00)
            {
                return a ;//�������û�з�����ȷӦ��ֱ���˳�������Ӧ��
            }
             //��OCRָ����󣬽�������4�ֽڵ�OCR��Ϣ
            ocr[0]=SPI_Byte(0xff);
            ocr[1]=SPI_Byte(0xff);
            ocr[2]=SPI_Byte(0xff);
            ocr[3]=SPI_Byte(0xff);           
        //    spi_mosi(SD_SPIn_x,SD_CS,ocr,NULL,4); 
              
            SD_deselect();  //OCR������ɣ�Ƭѡ�ø�
            spi_mosi (SD_SPIn_x,SD_CS,NULL,NULL,1);

            //�����յ���OCR�е�bit30λ��CCS����ȷ����ΪSD2.0����SDHC
            //���CCS=1��SDHC   CCS=0��SD2.0
            //���CCS
            if(ocr[0]&0x40)
                SD_Type=SD_TYPE_V2HC ;
            else 
                SD_Type=SD_TYPE_V2 ; 
            //-----------����SD2.0���汾����-----------
        }//֧�ֵ�ѹ��Χ      
      } //2.0��ʶ�𼰳�ʼ�����
      /*--------------------------------2.0��ʶ�𼰳�ʼ�����------------------------------------------*/
      else if(re_sdtype==0x05) //��Ƭ�汾��Ϣ��v1.0�汾��,SD1.0����MMC
      {                  //�����V1.0����CMD8ָ���û�к�������
          temp=SPI_Byte(0xff);

  //-----------------SD1.0����MMC����ʼ����ʼ-----------------

  //������ʼ��ָ��CMD55+ACMD41
  // �����Ӧ��˵����SD�����ҳ�ʼ�����
  // û�л�Ӧ��˵����MMC�������������Ӧ��ʼ��
      retry=0 ;
      do 
      {
          a=SD_send_command(55,0);//�ȷ�CMD55��Ӧ����0x01���������
          if(a!=0x01)
          {
              return a ;
          }
          //�õ���ȷ��Ӧ�󣬷�ACMD41��Ӧ�õ�����ֵ0x00����������100��
          a=SD_send_command(41,0);
          retry++;
          
      }
      while((a!=0x00)&&(retry<100));
    // �ж��ǳ�ʱ���ǵõ���ȷ��Ӧ
    
      if(retry>=100) //��ʱ����˵����MMC����Ҫ��MMC�������ʼ��
      {
          retry=0 ;
          //����MMC����ʼ������
          do 
          { 
              a=SD_send_command(1,0);
              retry++;
          }
          while((a!=0x00)&&(retry<100));
          if(retry>=100)
          {
            return 1 ;  //MMC����ʼ����ʱ
          }
        
          SD_Type=SD_TYPE_MMC ;//д�뿨����
      }
      else SD_Type=SD_TYPE_V1;  //�������ʱ��Ϊ����ֵ��ȷ��ΪSD1.0��
  }   
  //----------SD1.0����MMC����ʼ����������------------
  /*---------------------1.0����MMC��ʶ�𼰳�ʼ�����-----------------*/


    temp=SPI_Byte(0xff); // Dummy SPI cycle

      if(SD_Type<3) //MMC��SD1.0��SD2.0���ֿ���Ҫ���ÿ��С��512
      {
          retry=0;
          do
          {
              retry++;
              a=SD_send_command(16,0x00000200);
         
          }while((a!=0x00)&&(retry<20));
      }
              
            return a;  //����
}



/*************************************************************/
/*                     ��SD����ȡһ������                    */
/*************************************************************/
uint8 read_block(long sector, uint8* buffer)
{
	uint8 a;          
	uint16 i;
	
  //�������SDHC����sector��ַת��byte��ַ
  if(SD_Type!=SD_TYPE_V2HC)
  {
      sector=sector<<9 ;
  }


	a = SD_send_command(17, sector);  //������ 	
	if(a != 0x00) 		return a;

	SD_select();
	//�����ݵĿ�ʼ
	while(SPI_Byte(0xff) != 0xfe);

	for(i=0; i<512; i++)              //��512������
	{
		*buffer++ = SPI_Byte(0xff);
	}

	SPI_Byte(0xff);              
	SPI_Byte(0xff);  	
	SD_deselect();
  SPI_Byte(0xff);              
	return 0;
} 


/*************************************************************/
/*                     ��SD��д��һ������                    */
/*************************************************************/
uint8 write_block(long sector, uint8* buffer)
{
	uint8 a;
	uint16 i;
  if(sector<1) return 0xff;     //Ϊ�˱���SD������������������
  
  //�������SDHC����sector��ַת��byte��ַ
  if(SD_Type!=SD_TYPE_V2HC)
  {
     sector=sector<<9 ;
  }

	a = SD_send_command(24, sector);//д����
	if(a != 0x00) return a;

	SD_select();
	
	SPI_Byte(0xff);
	SPI_Byte(0xff);
	SPI_Byte(0xff);

	SPI_Byte(0xfe);//����ʼ��
	
	for(i=0; i<512; i++)//��512�ֽ�����
	{
		SPI_Byte(*buffer++);
	}
	
	SPI_Byte(0xff);
	SPI_Byte(0xff);
	
	a = SPI_Byte(0xff); 	
	if( (a&0x1f) != 0x05)
	{
	  SD_deselect();
		return a;
	}
	//�ȴ�������
	while(!SPI_Byte(0xff));

  SD_deselect();

	return 0;
} 

