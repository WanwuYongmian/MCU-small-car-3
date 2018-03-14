#include "key.h"

/*

  *文件名称：key.c
  *文件描述：完成智能车相关参数的显示，要求至少三页，可以通过按键翻页。
  *当前版本：1.1
  *作者：    王敬凯
  *完成日期：2016/3/1
  *取代版本：1.0
  *原作者：  马鹏飞
  *完成日期：2016/1/16
   

  *修改内容 增加兼容性 取消延时 改为跳变沿检测
*/

#define  PRESSED     0
#define  UNPRESSED   1
/***************************************************/ 
/*函数名称：按键扫描                               */
/*功能描述：扫描是否有按键按下                     */
/*输入参数：无                                     */
/*返回值：0表示无按键 1表示一号按键按下            */
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