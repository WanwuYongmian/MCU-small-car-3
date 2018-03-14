//==============================================================================
// 文件名：mma845x.c
//
// 创建时间：2013-03-19
//
//==============================================================================
#include "mma845x.h"

//==============================================================================
// 函数名称：MMA845x_Init
// 函数功能：MMA845x待机
// 入口参数：无
// 出口参数：无
// 返回值：无
//
//I2C0( PTE24, PTE25 )
//
//==============================================================================
void MMA845x_Init(void)
{
    MMA845x_Standby ();
    
    //数据输出速率100Hz - Set the device in 800 Hz ODR, Standby
    MMA845xWriteRegister(CTRL_REG1, OUTPUT_DATA_RATE_800HZ); 
    
    //量程范围2g
    MMA845xWriteRegister(XYZ_DATA_CFG_REG, FULL_SCALE_2G);
    
    MMA845x_Active();
}

//==============================================================================
// 函数名称：MMA845x_Standby
// 函数功能：MMA845x待机
// 入口参数：无
// 出口参数：无
// 返回值：无
//
//==============================================================================
void MMA845x_Standby (void)
{
    unsigned char regVal;
    
    //读取当前系统控制寄存器1(CTRL_REG1)的值
    regVal = MMA845xReadRegister(CTRL_REG1);
    
    //清除MMA845x活动(Active)位
    MMA845xWriteRegister(CTRL_REG1, regVal & ~ACTIVE_MASK);
}

//==============================================================================
// 函数名称：MMA845x_Active
// 函数功能：MMA845x进入工作状态（激活）
// 入口参数：无
// 出口参数：无
// 返回值：无
//
//==============================================================================
void MMA845x_Active (void)
{
    unsigned char regVal;
    
    //读取当前系统控制寄存器1(CTRL_REG1)的值
    regVal = MMA845xReadRegister(CTRL_REG1);
    
    //设置活动位
    MMA845xWriteRegister(CTRL_REG1, regVal | ACTIVE_MASK);
}

//==============================================================================
// 函数名称：MMA845x_SetFullScaleRange
// 函数功能：设置MMA845x量程(2g, 4g, 8g)
// 入口参数：fsValue - 量程范围
//      	FULL_SCALE_2G - 2g
//		FULL_SCALE_4G - 4g
//		FULL_SCALE_4G - 8g
// 出口参数：无
// 返回值：无
//
//==============================================================================
void MMA845x_SetFullScaleRange(unsigned char fsValue)
{
    unsigned char regVal;
    
    //先进待机模式
    MMA845x_Standby();
    
    //读出当前配置值
    regVal = MMA845xReadRegister(XYZ_DATA_CFG_REG);
    
    //设置量程范围
    //FULL_SCALE_2G - 2g
    //FULL_SCALE_4G - 4g
    //FULL_SCALE_4G - 8g
    MMA845xWriteRegister(XYZ_DATA_CFG_REG, (regVal | fsValue));
    
    //重新进入工作状态
    MMA845x_Active();	
}

//==============================================================================
// 函数名称：MMA845x_SetOutputDataRate
// 函数功能：设置MMA845x数据输出速率
// 入口参数：odrValue - 数据输出速率
//              OUTPUT_DATA_RATE_800HZ  - 1.25ms
//              OUTPUT_DATA_RATE_400HZ  - 2.5ms
//              OUTPUT_DATA_RATE_200HZ  - 5ms
//              OUTPUT_DATA_RATE_100HZ  - 10ms
//              OUTPUT_DATA_RATE_50HZ   - 20ms
//              OUTPUT_DATA_RATE_12_5HZ - 80ms
//              OUTPUT_DATA_RATE_6_25HZ - 160ms
//              OUTPUT_DATA_RATE_1_56HZ - 640ms
// 出口参数：无
// 返回值：无
//
//==============================================================================
void MMA845x_SetOutputDataRate(unsigned char odrValue)
{
    unsigned char regVal;
    
    //先进待机模式
    MMA845x_Standby();
    
    //读出当前配置值
    regVal = MMA845xReadRegister(CTRL_REG1);
    
    //设置量程范围
    //FULL_SCALE_2G - 2g
    //FULL_SCALE_4G - 4g
    //FULL_SCALE_4G - 8g
    MMA845xWriteRegister(CTRL_REG1, (regVal | odrValue));
    
    //重新进入工作状态
    MMA845x_Active();	
}



