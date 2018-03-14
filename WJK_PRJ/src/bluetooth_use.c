#include "bluetooth_use.h"

#define READ_HEAD_1      1
#define READ_HEAD_2      2

#define WRITE_HEAD_1     10
#define WRITE_HEAD_2     11

#define GO_HEAD_1        20
#define GO_HEAD_2        21


#define PARAMETER_COUNT  14


uint8  bluetooth_buff[2 * PARAMETER_COUNT];

void lower_computer_handler (void)
{
      int head[2];

//      UARTn_e uratn = CH_UART;//定义uart通道



    if(UART_S1_REG(UARTN[CH_UART]) & UART_S1_RDRF_MASK)   //接收数据寄存器满
    {
        //用户需要处理接收数据
      head[0] = uart_getchar(CH_UART);//帧头
      head[1] = uart_getchar(CH_UART);
      
      
      //write command
      if(head[0] ==  WRITE_HEAD_1   && head[1] ==  WRITE_HEAD_2)
      {
        int i;
        uint8 buff[2] = {WRITE_HEAD_1,WRITE_HEAD_2}; //定义帧尾
        
        
        for(i = 0; i < 2 * PARAMETER_COUNT; i++)
        {
          bluetooth_buff[i] = uart_getchar(CH_UART);
        }
        
        uart_putbuff (CH_UART, buff,2);//发送帧尾
        //直立环
        //acc_middle_volt   = (bluetooth_buff[0] + (bluetooth_buff[1]<<8));
        //gyro_middle_volt  = (bluetooth_buff[2] + (bluetooth_buff[3]<<8));
        gyro_integral     = (bluetooth_buff[4] + (bluetooth_buff[5]<<8));
        tg                = (bluetooth_buff[6] + (bluetooth_buff[7]<<8));
        left_dead         = (bluetooth_buff[8] + (bluetooth_buff[9]<<8));
        right_dead        = (bluetooth_buff[10] + (bluetooth_buff[11]<<8));
        k_acc             = (bluetooth_buff[12] + (bluetooth_buff[13]<<8));
        k_gyro            = (bluetooth_buff[14] + (bluetooth_buff[15]<<8));
        //方向环
        gyro_turn_middle  = (bluetooth_buff[16] + (bluetooth_buff[17]<<8));
        turn_kp           = (bluetooth_buff[18] + (bluetooth_buff[19]<<8));
        turn_kd           = (bluetooth_buff[20] + (bluetooth_buff[21]<<8));
        //速度环
        speed_goal        = (bluetooth_buff[22] + (bluetooth_buff[23]<<8));
        speed_kp          = (bluetooth_buff[24] + (bluetooth_buff[25]<<8));
        speed_ki          = (bluetooth_buff[26] + (bluetooth_buff[27]<<8));
        
      }
      //read command
      else if(head[0] == READ_HEAD_1   && head[1] == READ_HEAD_2 )
      {
        uint8 buff[2] = {READ_HEAD_1,READ_HEAD_2}; //定义帧头
        
        //bluetooth_buff[0] = acc_middle_volt;
        //bluetooth_buff[1] = acc_middle_volt>>8;
        
        //bluetooth_buff[2] = gyro_middle_volt;
        //bluetooth_buff[3] = gyro_middle_volt>>8;
        
        bluetooth_buff[4] = gyro_integral;
        bluetooth_buff[5] = gyro_integral>>8;
        
        bluetooth_buff[6] = tg;
        bluetooth_buff[7] = tg>>8;
        
        bluetooth_buff[8] = left_dead;
        bluetooth_buff[9] = left_dead>>8;
        
        bluetooth_buff[10] = right_dead;
        bluetooth_buff[11] = right_dead>>8;
        
        bluetooth_buff[12] = k_acc;
        bluetooth_buff[13] = k_acc>>8;
        
        bluetooth_buff[14] = k_gyro;
        bluetooth_buff[15] = k_gyro>>8;
        
        //方向环
        bluetooth_buff[16] = gyro_turn_middle;
        bluetooth_buff[17] = gyro_turn_middle>>8;
        
        bluetooth_buff[18] = turn_kp;
        bluetooth_buff[19] = turn_kp>>8;
        
        bluetooth_buff[20] = turn_kd;
        bluetooth_buff[21] = turn_kd>>8;
        
        //速度环
        bluetooth_buff[22] = speed_goal;
        bluetooth_buff[23] = speed_goal>>8;
        
        bluetooth_buff[24] = speed_kp;
        bluetooth_buff[25] = speed_kp>>8;
        
        bluetooth_buff[26] = speed_ki;
        bluetooth_buff[27] = speed_ki>>8;
        
        uart_putbuff (CH_UART, buff,2);//发送帧头
        uart_putbuff (CH_UART, bluetooth_buff,2 * PARAMETER_COUNT);//发送数据
        
      }
      //发车命令
      else if (head[0] == GO_HEAD_1   && head[1] == GO_HEAD_2 )
      {
        uint8 buff;
        
        buff = uart_getchar(CH_UART);
        
        if(buff == 0)
        {
          run_mode = starting_mode;
          stop_flag = 0;
        }
        else if(buff == 1)
          run_mode = stand_mode;
        else if(buff == 2)
          run_mode = normoallization_mode;
        else if(buff == 3)
          stop_flag = 1;
        
        
          buzz_mode_flag = 1;
      }     
    }

}