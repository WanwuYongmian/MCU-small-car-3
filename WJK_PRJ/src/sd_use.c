#include "sd_use.h"

#define TXT1   20736
uint8  sd_buff[2][512];
uint16 byte_pt;     //ָ��ǰ�洢���ֽ�λ��
uint8  section_pt;  //ָ��ǰ�洢�Ļ�����
uint16 next_section_pt; //ָ��ʵ�ʴ洢�Ļ���������
uint8  buff_full_flag;
uint8  sd_read_buff[512];
//==============================================================
//������  ��  lide_to_buff
//���������� ���źż��ؽ�������
//�������:  buff �����ź�����ַ  count �����źŸ���!!��Ҫ����λ��ƥ��
//����ֵ  ����
//==============================================================
void lode_to_buff (uint8* buff,uint8 count)
{
  uint8 i;
  for(i = 0; i < count; i++)
  {
    sd_buff[section_pt][byte_pt] = buff[i];
    
    byte_pt++;
    if(byte_pt>511)
    {
      byte_pt = 0;
      buff_full_flag = 1;
      
      section_pt++;
      if(section_pt > 1)
        section_pt = 0;
    }
  }
}


//==============================================================
//������  ��  SD_lowcomp_init
//���������� sd����λ����ʼ��
//�������:  ��
//����ֵ  ����
//==============================================================

void SD_lowcomp_init(void)
{
  SD_Init();
  byte_pt = 0;
  section_pt = 0;
  buff_full_flag = 0;
  next_section_pt = 0;
}

//==============================================================
//������  ��  save_sd
//���������� �洢sd��
//�������:  ��
//����ֵ  ����
//==============================================================

void save_sd (void)
{
  uint8 sect;
  
  if(section_pt == 1)
    sect = 0;
  else 
    sect = 1;

   write_block(TXT1 + next_section_pt,sd_buff[sect]);
   next_section_pt++;
//    read_block(TXT1,sd_read_buff);
}
