//==============================================================================
// ÎÄ¼þÃû£ºmma845x.h
//
//
//==============================================================================



#ifndef MMA845X_H_
#define MMA845X_H_

#include "common.h"
#include "MK60_i2c.h"

#define  MMA845x_I2CN I2C1

//#define MMA845x_I2C_ADDRESS     0x1D   // SA0 = 1
#define MMA845x_I2C_ADDRESS    0x1C   // SA0 = 0

// MMA8451 Register address
#define  DATA_STATUS_REG                0x00
#define  OUT_X_MSB_REG              	0x01
#define  OUT_X_LSB_REG              	0x02
#define  OUT_Y_MSB_REG              	0x03
#define  OUT_Y_LSB_REG                  0x04
#define  OUT_Z_MSB_REG                  0x05
#define  OUT_Z_LSB_REG                  0x06
#define  F_STATUS_REG                   0x08
#define  F_SETUP_REG                    0x09
#define  TRIG_CFG_REG                   0x0A
#define  SYSMOD_REG                     0x0B
#define  INT_SOURCE_REG                 0x0C
#define  WHO_AM_I_REG                   0x0D
#define  XYZ_DATA_CFG_REG               0x0E
#define  HP_FILTER_CUTOFF_REG           0x0F
#define  PL_STATUS_REG                  0x10
#define  PL_CFG_REG                     0x11
#define  PL_COUNT_REG                   0x12
#define  PL_BF_ZCOMP_REG                0x13
#define  PL_P_L_THS_REG_REG             0x14
#define  FF_MT_CFG_REG                  0x15
#define  FF_MT_SRC_REG                  0x16
#define  FF_MT_THS_REG                  0x17
#define  FF_MT_COUNT_REG                0x18
#define  TRANSIENT_CFG_REG              0x1D
#define  TRANSIENT_SRC_REG              0x1E
#define  TRANSIENT_THS_REG              0x1F
#define  TRANSIENT_COUNT_REG            0x20
#define  PULSE_CFG_REG                  0x21
#define  PULSE_SRC_REG                  0x22
#define  PULSE_THSX_REG                 0x23
#define  PULSE_THSY_REG                 0x24
#define  PULSE_THSZ_REG                 0x25
#define  PULSE_TMLT_REG                 0x26
#define  PULSE_LTCY_REG                 0x27
#define  PULSE_WIND_REG                 0x28
#define  ASLP_COUNT_REG                 0x29
#define  CTRL_REG1                      0x2A
#define  CTRL_REG2                      0x2B
#define  CTRL_REG3                      0x2C
#define  CTRL_REG4                      0x2D
#define  CTRL_REG5                      0x2E
#define  OFF_X_REG                      0x2F
#define  OFF_Y_REG                      0x30
#define  OFF_Z_REG                      0x31


// const values
#define FS_MASK                         0x03
#define HPF_OUT_MASK                    0x10
#define FULL_SCALE_2G                   0x00
#define FULL_SCALE_4G                   0x01
#define FULL_SCALE_8G                   0x02

#define ODR_MASK                        0x07
#define ODR_SHIFT                       0x03
#define OUTPUT_DATA_RATE_800HZ          (0x00 << ODR_SHIFT)
#define OUTPUT_DATA_RATE_400HZ          (0x01 << ODR_SHIFT)
#define OUTPUT_DATA_RATE_200HZ          (0x02 << ODR_SHIFT)
#define OUTPUT_DATA_RATE_100HZ          (0x03 << ODR_SHIFT)
#define OUTPUT_DATA_RATE_50HZ           (0x04 << ODR_SHIFT)
#define OUTPUT_DATA_RATE_12_5HZ         (0x05 << ODR_SHIFT)
#define OUTPUT_DATA_RATE_6_25HZ         (0x06 << ODR_SHIFT)
#define OUTPUT_DATA_RATE_1_56HZ         (0x07 << ODR_SHIFT)

#define ACTIVE_MASK                     0x01
#define DR_MASK                         0x38
#define FREAD_MASK                      0x02

#define SEL_MASK                        0x03

#define ST_MASK                         0x80

#define SRC_DRDY_MASK                   0x01
#define SRC_FF_MT_MASK                  0x04
#define SRC_PULSE_MASK                  0x08
#define SRC_LNDPRT_MASK                 0x10
#define SRC_TRANS_MASK                  0x20
#define SRC_FIFO_MASK                   0x40

#define DATA_STATUS_ZYXDR_MASK          0x04u


#define MMA845xWriteRegister(regAddr, regValue)		i2c_write_reg(MMA845x_I2CN,MMA845x_I2C_ADDRESS, regAddr, regValue)
#define MMA845xReadRegister(regAddr)			i2c_read_reg(MMA845x_I2CN,MMA845x_I2C_ADDRESS, regAddr)
//#define MMA845xReadMultiRegisters(regStartAddr, pBuffer, len)  I2C0_ReadMultiRegisters8(MMA845x_I2C_ADDRESS, regStartAddr, pBuffer, len)
#define MMA845xReadDoubleRegisters(regStartAddr)  i2c_read_double_reg(MMA845x_I2CN,MMA845x_I2C_ADDRESS, regAddr)
// functions
void MMA845x_Init(void);
void MMA845x_Standby (void);
void MMA845x_Active (void);
void MMA845x_SetFullScaleRange(unsigned char fsValue);
void MMA845x_SetOutputDataRate(unsigned char odrValue);

#endif // MMA845X_H_
