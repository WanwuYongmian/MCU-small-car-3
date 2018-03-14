/*
 *   文件名称: 蜂鸣器控制 
 *   文件描述: 通过置蜂鸣器模式变量buzz_mode,改变蜂鸣器鸣响方式，还可以关闭蜂鸣器
 *
 *   当前版本: 1.1
 *   作者    : 王敬凯
 *   完成日期: 2016.3.1
 *
 *   取代版本: 1.0
 *   原作者  : 陈巧云
 *   完成日期: 2016.1.17

 *   修改K60标准  修改长鸣模式
 */
 
#include "buzz.h"
  


#define   ALWAYS     1000
#define   FAST_TIME  30
#define   SLOW_TIME  100


 char     buzz_mode_flag;
 uint16      times;      //定义计时器   
 uint8     counter;    //定义计数器   计算鸣叫次数
 
 
void buzz_initial(void)
 {
    BUZZER_DIR_OUT ;
    counter = 0;
    times = 0;
 }
      
//================================================================================
//函数名  : buzz_run()
//功能描述: 蜂鸣器鸣笛，模式1快速响三声，模式2慢速响三声，模式3一直响,模式0关闭
//          FAST_TIME为快速响的时间间隔
//          SLOW_TIME为慢速响的时间间隔
//          ALWAYS为一直响的时间间隔
//输入参数: 蜂鸣器响应模式0,1,2,3
//输出参数: 无
//返回值  : 无
//================================================================================

void buzz_run (void) 
{
     if (buzz_mode_flag == 1)   //快速响三声
      {
          times++;
         if (times == FAST_TIME )    
         {
            BUZZER_TURN;
             times = 0;
             counter++;
             if (counter == 6)  //6
             {
               buzz_mode_flag = 0;
               counter = 0;
               BUZZER_TURN_OFF;
             }
         }
      }
    
    
      else if (buzz_mode_flag == 2)   //慢速响三声
      {
         times++;
         if (times == SLOW_TIME )    //33000
         {
             counter++;
             times = 0;
             BUZZER_TURN;
             
             
             if (counter == 6)  //6
             {
               buzz_mode_flag = 0;
               counter = 0;
               BUZZER_TURN_OFF;
             }
         }
      }
      
      
      else if (buzz_mode_flag == 3)  //一直响
      {
        
               if (times == ALWAYS/10)
               {
                   BUZZER_TURN_OFF;
               }
               else if (times == 0)
               {
                   BUZZER_TURN_ON;
               }
               
               
               times++;
               if(times == ALWAYS)
               {
                   times = 0;
               }
               
      } 
  
  
      else if (buzz_mode_flag == 0) 
      {
              BUZZER_TURN_OFF;
      }
     
}
  
