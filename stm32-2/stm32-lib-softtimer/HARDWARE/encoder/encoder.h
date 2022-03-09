#ifndef __ENCODER_H
#define __ENCODER_H
#include "sys.h"


#define MAX_COUNT 1000  //单位时间内编码器转过的最大值极限


void TIM3_Encoder_Init( void );

void TIM5_Encoder_Init( void );


//读取编码器寄存器数据
unsigned short int TIM3_Encoder_Read_Prototype( void );


//读取编码器寄存器数据
unsigned short int TIM5_Encoder_Read_Prototype( void );



/****************************************************************
//此模式优化了STM32编码器返回值为无符号16位整形的弊端
//使用方法：  建议将此函数放在 定时器中执行，可以算出角速度 及 距离
***************************************************************/
signed int  TIM3_Encoder_Read( void );


/****************************************************************
//此模式优化了STM32编码器返回值为无符号16位整形的弊端
//使用方法：  建议将此函数放在 定时器中执行，可以算出角速度 及 距离
***************************************************************/
signed int  TIM5_Encoder_Read( void );

//直接读取编码器的位移量
signed int TIM5_Encoder_Distance( void );

//直接读取编码器的位移量
signed int TIM3_Encoder_Distance( void );




#endif
