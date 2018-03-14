
#include "include.h"
#include "calculation.h"


/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：CCD_init
*  功能说明：CCD初始化
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
void CCD_init1(void)
{
  gpio_init (PTE4, GPO,HIGH);
  gpio_init (PTE5, GPO,HIGH);
  adc_init( ADC1_SE4b) ;
  
}

/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：StartIntegration
*  功能说明：CCD启动程序
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
void StartIntegration(void) {

    unsigned char i;

    SI_SetVal();            /* SI  = 1 */
    SamplingDelay();
    CLK_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SI_ClrVal();            /* SI  = 0 */
    SamplingDelay();
    CLK_ClrVal();           /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK_SetVal();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        CLK_ClrVal();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK_ClrVal();           /* CLK = 0 */
}


/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：ImageCapture
*  功能说明：CCD采样程序
*  参数说明：* ImageData   采样数组
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*ImageData =  ad_once(ADC1, AD6a, ADC_8bit);
*************************************************************************/

void ImageCapture(unsigned char * ImageData) {

    unsigned char i;
    extern unsigned 	char AtemP ;

    SI_SetVal();            /* SI  = 1 */
    SamplingDelay();
    CLK_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SI_ClrVal();            /* SI  = 0 */
    SamplingDelay();

    //Delay 10us for sample the first pixel
    /**/
    for(i = 0; i < 200; i++) {                    //更改250，让CCD的图像看上去比较平滑，
      SamplingDelay() ;  //200ns                  //把该值改大或者改小达到自己满意的结果。
    }

    //Sampling Pixel 1

    *ImageData =  adc_once( ADC1_SE4b, ADC_8bit);
    ImageData ++ ;
    CLK_ClrVal();           /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK_SetVal();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        //Sampling Pixel 2~128

       *ImageData =  adc_once(ADC1_SE4b, ADC_8bit);
        ImageData ++ ;
        CLK_ClrVal();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK_ClrVal();           /* CLK = 0 */
}


/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：CalculateIntegrationTime
*  功能说明：计算曝光时间
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/

/* 曝光时间，单位ms */
unsigned char IntegrationTime = 80;
void CalculateIntegrationTime(void) {
extern unsigned 	char Pixel[128];
/* 128个像素点的平均AD值 */
unsigned 	char PixelAverageValue;
/* 128个像素点的平均电压值的10倍 */
unsigned 	char PixelAverageVoltage;
/* 设定目标平均电压值，实际电压的10倍 */
short int TargetPixelAverageVoltage = 25;
/* 设定目标平均电压值与实际值的偏差，实际电压的10倍 */
short int PixelAverageVoltageError = 0;
/* 设定目标平均电压值允许的偏差，实际电压的10倍 */
short int TargetPixelAverageVoltageAllowError = 2;

    /* 计算128个像素点的平均AD值 */
    PixelAverageValue = PixelAverage(128,Pixel);
    /* 计算128个像素点的平均电压值,实际值的10倍 */
    PixelAverageVoltage = (unsigned char)((int)PixelAverageValue * 25 / 194);

    PixelAverageVoltageError = TargetPixelAverageVoltage - PixelAverageVoltage;
    if(PixelAverageVoltageError < -TargetPixelAverageVoltageAllowError)
    {
     PixelAverageVoltageError = 0- PixelAverageVoltageError ;
      PixelAverageVoltageError /= 2;
      if(PixelAverageVoltageError > 10 )
         PixelAverageVoltageError = 10 ;
       IntegrationTime -= PixelAverageVoltageError;
    }
    if(PixelAverageVoltageError > TargetPixelAverageVoltageAllowError)
    { 
        PixelAverageVoltageError /= 2;
        if(PixelAverageVoltageError > 10 )
           PixelAverageVoltageError = 10 ;
        IntegrationTime += PixelAverageVoltageError;}
 
    
  //  uart_putchar(UART0,0XAA) ;
    
 //   uart_putchar(UART0,PixelAverageVoltage) ;
 //   uart_putchar(UART0,PixelAverageVoltageError) ;
//    uart_putchar(UART0,IntegrationTime) ;
    if(IntegrationTime <= 1)
      IntegrationTime = 1;
  if(IntegrationTime >= 80)
       IntegrationTime = 80;
   
     IntegrationTime=80;
    
 
}


/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：AccommodFondLine
*  功能说明：求数组的均值程序
*  参数说明：
*  函数返回：无
*  修改时间：2012-11-20
*  备    注：自己适应算黑线位置算法
*************************************************************************/
#define LINEBREADTH    10 
#define LINECONCAT     8
void AccommodFondLine(char *PixelAryy ,unsigned 	char PixelCount , short int *LastLeftPixelStation,short int *LastRingtPixelStation,unsigned 	char FAVAULE)
{
  static unsigned 	char NOLeftCount,NORingtCout ;
  short int temp0B ,temp1B,temp2B,temp3B;
  unsigned 	char *LineStation ,LineCount ,*LineLeftStation,*LineRingtStation;
  short int LeftMIN,LeftMAX,RingtMIN,RingtMAX;
  LineCount = 0 ;
  for(temp0B = 0 ; temp0B < PixelCount ; temp0B ++)
  {
    temp1B = temp0B ;
    temp2B = 0 ;
    /***********
    查找左边凹槽
    ***********/
    while(temp2B <= LINEBREADTH) {
      temp1B -- ;
      if(temp1B < 0)
        break ;
      if( PixelAryy[temp1B] -  PixelAryy[temp0B] > FAVAULE )
      { temp2B ++ ;}
      else if(temp2B)
      { break ; }
   
    }
     
    /***********
    查找右边凹槽
    ***********/
    temp1B = temp0B ;
    temp3B = 0 ;
    while(temp3B <= LINEBREADTH)
    {
      temp1B ++ ;
      if(temp1B > PixelCount)
      { break ; }
      if( PixelAryy[temp1B] -  PixelAryy[temp0B] > FAVAULE )
      { temp3B ++ ;}
      else if(temp3B)
      { break ; }
    }
    /***********
    记录黑线位置
    ***********/    
    if(temp2B >= LINEBREADTH ){
      *LineStation = temp0B ;
      LineCount ++ ;
    }else if(temp3B >= LINEBREADTH ){
      *LineStation = temp0B ;
      LineCount ++ ;
    }
    
    
  }
  /**********
  根据连续性查找左右黑线位置
  **********/
  if(LineCount)
  {
    temp2B = PixelCount >> 1 ;
    temp1B = NOLeftCount << 1;
    temp1B += LINECONCAT;
    LeftMIN = *LastLeftPixelStation - temp1B ;
    LeftMAX = *LastRingtPixelStation + temp1B ;
    if(LeftMIN < 0)
      LeftMIN = 0 ;

    if(LeftMAX > (temp2B + 1))
      LeftMAX  = temp2B + 1 ;
    
    RingtMIN = *LastRingtPixelStation - temp1B ;
    RingtMAX = *LastRingtPixelStation + temp1B ;
    if(RingtMAX > PixelCount)
       RingtMAX = PixelCount ;
    if(RingtMIN < (temp2B - 1)){
       RingtMIN = temp2B - 1 ;
    }
    temp2B = 0 ;
    temp3B = 0 ;
   for(temp1B = 0 ;temp1B < LineCount ;temp1B ++ )
   {
     if( (LeftMIN < LineStation[temp1B])&&(LineStation[temp1B]<LeftMAX))
     {
       LineLeftStation[temp2B] = LineStation[temp1B] ;
       temp2B ++ ;
     }else if( (RingtMIN < LineStation[temp1B])&&(LineStation[temp1B]<RingtMAX))
     {
       LineRingtStation[temp3B] = LineStation[temp1B] ;
       temp3B ++ ;
     }
     
   }
    
  }else 
  {
    NOLeftCount ++ ;
    NORingtCout ++ ;
  }
  
  if(temp2B)
  {
    NOLeftCount = 0 ;
    
  }
     
}
/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：PixelAverage
*  功能说明：求数组的均值程序
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
unsigned 	char PixelAverage(unsigned 	char len, unsigned 	char *data) {
  unsigned char i;
  unsigned int sum = 0;
  for(i = 0; i<len; i++) {
    sum = sum + *data++;
  }
  return ((unsigned char)(sum/len));
}
/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：SendHex
*  功能说明：采集发数程序
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
void SendHex(unsigned char hex) {
  unsigned char temp;
  temp = hex >> 4;
  if(temp < 10) {
    uart_putchar(UART0,temp + '0');
  } else {
    uart_putchar(UART0,temp - 10 + 'A');
  }
  temp = hex & 0x0F;
  if(temp < 10) {
    uart_putchar(UART0,temp + '0');
  } else {
   uart_putchar(UART0,temp - 10 + 'A');
  }
}
/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：SendImageData
*  功能说明：
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
void SendImageData(unsigned char * ImageData) {

    unsigned char i;
    unsigned char crc = 0;

    /* Send Data */
    uart_putchar(UART0,'*');
    uart_putchar(UART0,'L');
    uart_putchar(UART0,'D');

    SendHex(0);
    SendHex(0);
    SendHex(0);
    SendHex(0);

    for(i=0; i<128; i++) {
      SendHex(*ImageData++);
    }

    SendHex(crc);
    uart_putchar(UART0,'#');
}
/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：SamplingDelay
*  功能说明：CCD延时程序 200ns
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
 void SamplingDelay(void){
   volatile unsigned 	char i ;
   for(i=0;i<1;i++) {
    asm("nop");
    asm("nop");}
 }
/***********************************************************************
*
*函数名称：GetBlackLine
*功能说明：黑线提取程序
*参数说明：* ImageData采集数组
*函数返回：
*修改时间：2016-2-16
*备    注：
***********************************************************************/
int  GetBlackLine(unsigned char * ImageData){
  unsigned int Left=0;
  unsigned int Right=0;
  unsigned int Lastmid=64;
  for(int i=0;i<128;i++)
  {
  
   if( *(ImageData+i)+4<=*(ImageData+i+1))
   {
    if(*(ImageData+i+1)+4<=*(ImageData+i+2))
       if(*(ImageData+i+2)+4<=*(ImageData+3))
         if(*(ImageData+i+3)-*(ImageData+i)>=22)
             if(0<i<=Lastmid)
             Left=i;
   }
     if( *(ImageData+i)+4<=*(ImageData+i-1))
   {
    if(*(ImageData+i-1)+4<=*(ImageData+i-2))
       if(*(ImageData+i-2)+4<=*(ImageData-3))
         if(*(ImageData+i-3)-*(ImageData+i)>=22)
             if(0<i<=Lastmid)
              Right=i;
    
       Lastmid=(Left+Right)/2;
   }
    
  
  }
   return Lastmid;
}