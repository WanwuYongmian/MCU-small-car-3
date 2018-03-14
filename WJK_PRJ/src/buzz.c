/*
 *   �ļ�����: ���������� 
 *   �ļ�����: ͨ���÷�����ģʽ����buzz_mode,�ı���������췽ʽ�������Թرշ�����
 *
 *   ��ǰ�汾: 1.1
 *   ����    : ������
 *   �������: 2016.3.1
 *
 *   ȡ���汾: 1.0
 *   ԭ����  : ������
 *   �������: 2016.1.17

 *   �޸�K60��׼  �޸ĳ���ģʽ
 */
 
#include "buzz.h"
  


#define   ALWAYS     1000
#define   FAST_TIME  30
#define   SLOW_TIME  100


 char     buzz_mode_flag;
 uint16      times;      //�����ʱ��   
 uint8     counter;    //���������   �������д���
 
 
void buzz_initial(void)
 {
    BUZZER_DIR_OUT ;
    counter = 0;
    times = 0;
 }
      
//================================================================================
//������  : buzz_run()
//��������: ���������ѣ�ģʽ1������������ģʽ2������������ģʽ3һֱ��,ģʽ0�ر�
//          FAST_TIMEΪ�������ʱ����
//          SLOW_TIMEΪ�������ʱ����
//          ALWAYSΪһֱ���ʱ����
//�������: ��������Ӧģʽ0,1,2,3
//�������: ��
//����ֵ  : ��
//================================================================================

void buzz_run (void) 
{
     if (buzz_mode_flag == 1)   //����������
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
    
    
      else if (buzz_mode_flag == 2)   //����������
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
      
      
      else if (buzz_mode_flag == 3)  //һֱ��
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
  
