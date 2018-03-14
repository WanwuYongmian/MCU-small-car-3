#include "sd_use.h"

#define TXT1   20736
uint8  sd_buff[2][512];
uint16 byte_pt;     //指向当前存储的字节位置
uint8  section_pt;  //指向当前存储的缓存区
uint16 next_section_pt; //指向实际存储的缓存区增量
uint8  buff_full_flag;
uint8  sd_read_buff[512];
//==============================================================
//函数名  ：  lide_to_buff
//功能描述： 将信号加载进缓存区
//输入参数:  buff 输入信号流地址  count 输入信号个数!!需要和上位机匹配
//返回值  ：无
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
//函数名  ：  SD_lowcomp_init
//功能描述： sd卡下位机初始化
//输入参数:  无
//返回值  ：无
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
//函数名  ：  save_sd
//功能描述： 存储sd卡
//输入参数:  无
//返回值  ：无
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
