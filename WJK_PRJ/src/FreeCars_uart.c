/**
  ******************************************************************************
  * @file    FreeCars_uart.c
  * @author  FreeCars�۸�
  * @version NULL
  * @date    2014/11/11
  * @brief 	 FreeCars_uart C file.(For XS128)
  *   site:   Http://FreeCars.taobao.com
  *   QQȺ��  384273254��149168724
  *   ��Ȩ��  �˴���ΪFreeCars��λ��Э����룬��������ʹ�ã�Ҳ����������ҵ��;�����뱣���˶����֣�
  *   tips:   ǿ�ҽ���С�����ʹ��FreeCars��Ʒ������ģ����װ��������λ�������￪ʼ��
  ******************************************************************************
  */
#include "FreeCars_uart.h"

/************һ���Ǹ���FreeCars��λ��Э���޸ĵģ�����ı�**************/
uint8 uSendBuf[UartDataNum*2]={0};
SerialPortType SerialPortRx;
double UartData[9] = {0};
uint8 FreeCarsDataNum=UartDataNum*2;
//uint8 FreeCarsCount=0;
/**************************/


/*
��ѯ������һ֡����
����ʱ�������ݳ����й�
�����Է����ж����������Ե���
*/
void sendDataToScope(void)
{
	uint8 i,sum=0; 

  FREECAES_SCI_SEND_CHANNEL(251);
	FREECAES_SCI_SEND_CHANNEL(109);
	FREECAES_SCI_SEND_CHANNEL(37);
	sum+=(251);      //ȫ�����ݼ���У��
	sum+=(109);
	sum+=(37);
	for(i=0;i<FreeCarsDataNum;i++)
	{
		FREECAES_SCI_SEND_CHANNEL(uSendBuf[i]);
		sum+=uSendBuf[i];         //ȫ�����ݼ���У��
	}
 	FREECAES_SCI_SEND_CHANNEL(sum);
}

/*
��ĳ��ͨ���������
adr��ͨ��
date������-32768~32767
*/
void push(uint8 chanel,uint16 dat)
{
  uSendBuf[chanel*2]=dat/256;
  uSendBuf[chanel*2+1]=dat%256;
}

void WirelessDateSend (void)
{
 


// /////////////////////////////////////////////////// ֱ����������
  
  push(0,raw_acc_gyro.acc_x_raw);  //push(0,real_angle);
  push(1,gesture.gyro_x_std);//push(1,weight_sum);
  push(2,gesture.real_angle);

  push(3,gesture.acc_std);
  
  push(4,raw_acc_gyro.gyro_x_raw);
  push(5,0);                         
  
  push(6,k_gyro);
  push(7,k_acc);
  push(8,v_stand);
  
  push(9,left_dead);     
 
  push(10,right_dead);
  
  //////////////////////////////////////////////////����Ѱ�߹۲�
    //////////////////////////////////////////////////////////////////////
//  push(0,real_angle);  //push(0,real_angle);
//  push(1,middle_normol);//direction_error);//push(1,weight_sum);
//  push(2,left_normol);
//  
//  push(3,right_normol);
//  
//  push(4,middle_level);
//  push(5,weight_sum * 10);                         
//  
//  push(6,direction_error);
//  push(7,(long)1000*(left_normol - right_normol)/(left_normol + right_normol));
//     if (direction_error <=0)
//    {
//       push(8, -(long)(900 - left_normol));
//    }
//    else if (direction_error > 0)
//    {
//        push(8, (long)(900 - right_normol));
//    }
// 
//  
//  push(9,left_speed);     
//  
//  push(10,right_speed);
    //////////////////////////////////////////////////����Ѱ�߹۲�222
    //////////////////////////////////////////////////////////////////////
//  push(0,real_angle);  //push(0,real_angle);
//  push(1,middle_normol);//direction_error);//push(1,weight_sum);
//  push(2,left_normol);
//  
//  push(3,right_normol);
//  
//  push(4,direction_error);
//  push(5,weight_sum*10);                         
//  
//  push(6,gyro_y_ad/12);
//  push(7,direction_differential);
//  push(8,left_speed);
//  
//  push(9,right_speed);     
//  
//  push(10,forward_speed);
  
      //////////////////////////////////////////////////����ϵ��
    //////////////////////////////////////////////////////////////////////
  
  //push(0,real_angle);  //push(0,real_angle);
  //push(1,direction_error);//direction_error);//push(1,weight_sum);
 // push(2,gyro_y_ad/30);
  
  //push(3,left_normol);
  
  //push(4,v_turn_p);
  //push(5,v_turn_d);                         
  
  //push(6,v_turn_d_signal);
  //push(7,turn_kd*10);
  //push(8,v_turn);
  
  //push(9,forward_speed*10);     
  
  //push(10,turn_kp);
  
      //////////////////////////////////////////////////�ٶȻ�
    //////////////////////////////////////////////////////////////////////
//  push(0,real_angle);  //push(0,real_angle);
//  push(1,start_race_flag *1000);//direction_error);//push(1,weight_sum);
//  push(2,direction_error);
//  
//  push(3,forward_speed*10);
//  
//  push(4,left_speed*10);
//  push(5,speed_kp);                         
//  
//  push(6,-v_speed_k);
//  push(7,-v_speed_i);
//  push(8,speed_ki);
//  
//  push(9,v_speed);     
//  
// push(10,v_turn);
        //////////////////////////////////////////////////�۲����ҶԳ�
    //////////////////////////////////////////////////////////////////////
//  push(0,real_angle);  //push(0,real_angle);
//  push(1,direction_error);//direction_error);//push(1,weight_sum);
//  push(2,gyro_y_ad/30);
//  
//  push(3,v_stand);
//  
//  push(4,v_turn);
//  push(5,left_out);                         
//  
//  push(6,right_out);
//  push(7,left_speed*10);
//  push(8,right_speed*10);
//  
//  push(9,forward_speed*10);     
//  
//  push(10,v_stand);
  ///////////////////////////////////////////////////
//  push(0,real_angle);  //push(0,real_angle);
//  push(1,direction_error);//push(1,weight_sum);
//  push(2,forward_speed);
//  
//  push(3,direction_differential);
//  
//  push(4,(gyro_y_ad - gyro_turn_middle)/12);
//  push(5,turn_kd_signal);                         
//  
//  push(6,turn_kp);
//  push(7,v_turn);
//  push(8,v_turn_d_signal);
//  
//  push(9,v_turn_p);     
//  
//  push(10,left_normol);
  //////////////////////////////////////////////////////
//   push(0,real_angle);  //push(0,real_angle);
//  push(1,left_out);//push(1,weight_sum);
//  push(2,right_out);
//  
//  push(3,direction_error);
//  
//  push(4,(gyro_y_ad - gyro_turn_middle)/12);
//  push(5,v_turn);                         
//  
//  push(6,left_speed*10);
//  push(7,right_speed*10);
//  push(8,forward_speed*10);
//  
//  push(9,v_speed);     
//  
//  push(10,direction_differential);
  
  
  ///////////////////////////////////////////////////
//  push(0,real_angle);  //push(0,real_angle);
//  push(1,gyro_deg);//push(1,weight_sum);
//  push(2,v_stand);
//  
//  push(3,direction_error);
//  
//  push(4,(gyro_y_ad - gyro_turn_middle)/12);
//  push(5,v_turn);                         
//  
//  push(6,left_speed*10);
//  push(7,right_speed*10);
//  push(8,forward_speed*10);
//  
//  push(9,v_speed);     
//  
//  push(10,v_turn_d);
  //////////////////////////////////////////////////////////////////////
//    push(0,ramp_level);//real_angle);  //push(0,real_angle);
//  push(1,middle_normol);//direction_error);//push(1,weight_sum);
//  push(2,direction_error);
//  
//  push(3,ramp_flag*1000);
//  
//  push(4,real_angle);
//  push(5,right_normol);                         
//  
//  push(6,weight_sum*10);
//  push(7,left_normol);
//  push(8,v_turn_d_signal);
//  
//  push(9,speed_kp);     
//  
//  push(10,v_speed_k);
//  
  sendDataToScope();
  
}









