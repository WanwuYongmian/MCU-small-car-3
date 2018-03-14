//==============================================================================
// �ļ�����mma845x.c
//
// ����ʱ�䣺2013-03-19
//
//==============================================================================
#include "mma845x.h"

//==============================================================================
// �������ƣ�MMA845x_Init
// �������ܣ�MMA845x����
// ��ڲ�������
// ���ڲ�������
// ����ֵ����
//
//I2C0( PTE24, PTE25 )
//
//==============================================================================
void MMA845x_Init(void)
{
    MMA845x_Standby ();
    
    //�����������100Hz - Set the device in 800 Hz ODR, Standby
    MMA845xWriteRegister(CTRL_REG1, OUTPUT_DATA_RATE_800HZ); 
    
    //���̷�Χ2g
    MMA845xWriteRegister(XYZ_DATA_CFG_REG, FULL_SCALE_2G);
    
    MMA845x_Active();
}

//==============================================================================
// �������ƣ�MMA845x_Standby
// �������ܣ�MMA845x����
// ��ڲ�������
// ���ڲ�������
// ����ֵ����
//
//==============================================================================
void MMA845x_Standby (void)
{
    unsigned char regVal;
    
    //��ȡ��ǰϵͳ���ƼĴ���1(CTRL_REG1)��ֵ
    regVal = MMA845xReadRegister(CTRL_REG1);
    
    //���MMA845x�(Active)λ
    MMA845xWriteRegister(CTRL_REG1, regVal & ~ACTIVE_MASK);
}

//==============================================================================
// �������ƣ�MMA845x_Active
// �������ܣ�MMA845x���빤��״̬�����
// ��ڲ�������
// ���ڲ�������
// ����ֵ����
//
//==============================================================================
void MMA845x_Active (void)
{
    unsigned char regVal;
    
    //��ȡ��ǰϵͳ���ƼĴ���1(CTRL_REG1)��ֵ
    regVal = MMA845xReadRegister(CTRL_REG1);
    
    //���ûλ
    MMA845xWriteRegister(CTRL_REG1, regVal | ACTIVE_MASK);
}

//==============================================================================
// �������ƣ�MMA845x_SetFullScaleRange
// �������ܣ�����MMA845x����(2g, 4g, 8g)
// ��ڲ�����fsValue - ���̷�Χ
//      	FULL_SCALE_2G - 2g
//		FULL_SCALE_4G - 4g
//		FULL_SCALE_4G - 8g
// ���ڲ�������
// ����ֵ����
//
//==============================================================================
void MMA845x_SetFullScaleRange(unsigned char fsValue)
{
    unsigned char regVal;
    
    //�Ƚ�����ģʽ
    MMA845x_Standby();
    
    //������ǰ����ֵ
    regVal = MMA845xReadRegister(XYZ_DATA_CFG_REG);
    
    //�������̷�Χ
    //FULL_SCALE_2G - 2g
    //FULL_SCALE_4G - 4g
    //FULL_SCALE_4G - 8g
    MMA845xWriteRegister(XYZ_DATA_CFG_REG, (regVal | fsValue));
    
    //���½��빤��״̬
    MMA845x_Active();	
}

//==============================================================================
// �������ƣ�MMA845x_SetOutputDataRate
// �������ܣ�����MMA845x�����������
// ��ڲ�����odrValue - �����������
//              OUTPUT_DATA_RATE_800HZ  - 1.25ms
//              OUTPUT_DATA_RATE_400HZ  - 2.5ms
//              OUTPUT_DATA_RATE_200HZ  - 5ms
//              OUTPUT_DATA_RATE_100HZ  - 10ms
//              OUTPUT_DATA_RATE_50HZ   - 20ms
//              OUTPUT_DATA_RATE_12_5HZ - 80ms
//              OUTPUT_DATA_RATE_6_25HZ - 160ms
//              OUTPUT_DATA_RATE_1_56HZ - 640ms
// ���ڲ�������
// ����ֵ����
//
//==============================================================================
void MMA845x_SetOutputDataRate(unsigned char odrValue)
{
    unsigned char regVal;
    
    //�Ƚ�����ģʽ
    MMA845x_Standby();
    
    //������ǰ����ֵ
    regVal = MMA845xReadRegister(CTRL_REG1);
    
    //�������̷�Χ
    //FULL_SCALE_2G - 2g
    //FULL_SCALE_4G - 4g
    //FULL_SCALE_4G - 8g
    MMA845xWriteRegister(CTRL_REG1, (regVal | odrValue));
    
    //���½��빤��״̬
    MMA845x_Active();	
}



