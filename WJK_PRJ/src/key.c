#include "key.h"

/*

  *�ļ����ƣ�key.c
  *�ļ�������������ܳ���ز�������ʾ��Ҫ��������ҳ������ͨ��������ҳ��
  *��ǰ�汾��1.1
  *���ߣ�    ������
  *������ڣ�2016/3/1
  *ȡ���汾��1.0
  *ԭ���ߣ�  ������
  *������ڣ�2016/1/16
   

  *�޸����� ���Ӽ����� ȡ����ʱ ��Ϊ�����ؼ��
*/

#define  PRESSED     0
#define  UNPRESSED   1
/***************************************************/ 
/*�������ƣ�����ɨ��                               */
/*����������ɨ���Ƿ��а�������                     */
/*�����������                                     */
/*����ֵ��0��ʾ�ް��� 1��ʾһ�Ű�������            */
/***************************************************/
char key1_last_scan_value,key2_last_scan_value,key3_last_scan_value,key4_last_scan_value,key5_last_scan_value;
char button_scan(void)
{
    char key_back_value = 0,buff;
  
  
    buff = Key_get(KEY_1);
    (buff == PRESSED && key1_last_scan_value==UNPRESSED) ? (key_back_value += 1) : (key_back_value += 0); 
    key1_last_scan_value = buff;
    
//    buff = Key_get(KEY_2);
//    (buff==PRESSED && key2_last_scan_value==UNPRESSED) ? (key_back_value += 2) : (key_back_value += 0); 
//    key2_last_scan_value = buff;
//    
//    buff = Key_get(KEY_3);
//    (buff==PRESSED && key3_last_scan_value==UNPRESSED) ? (key_back_value += 3) : (key_back_value += 0); 
//    key3_last_scan_value = buff;
//    
//    buff = Key_get(KEY_4);
//    (buff==PRESSED && key4_last_scan_value==UNPRESSED) ? (key_back_value += 4) : (key_back_value += 0); 
//    key4_last_scan_value = buff;
//    
//    buff = Key_get(KEY_5);
//    (buff==PRESSED && key5_last_scan_value==UNPRESSED) ? (key_back_value += 5) : (key_back_value += 0); 
//    key5_last_scan_value = buff;
    
    return key_back_value;
    
}                             