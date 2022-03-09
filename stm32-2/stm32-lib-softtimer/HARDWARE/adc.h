#ifndef __ADC_H
#define __ADC_H	


 
/***************************使用说明******************************

考虑到不同型号stm32F103的引脚差别，我们这里默认使用所有板子都有的ADC1模块
使用的时候 先参照通道引脚对应引脚图 打开需要的通道宏定义
***************************使用说明******************************/


/*************************通道对应引脚图***************************

ADC123_IN0->PA0
ADC123_IN1->PA1
ADC123_IN2->PA2
ADC123_IN3->PA3
ADC12_IN4->PA4
ADC12_IN5->PA5
ADC12_IN6->PA6
ADC12_IN7->PA7
ADC12_IN8->PB0
ADC12_IN9->PB1
ADC123_IN10->PC0
ADC123_IN11->PC1
ADC123_IN12->PC2
ADC123_IN13->PC3
ADC12_IN14->PC4
ADC12_IN15->PC5

*************************通道对应引脚图****************************/



//初始化ADC
void Adc_Init_channel(int channel);  //参数对应着通道号（ch ：0~15 之间）

//获得ADC值
unsigned int  Get_ADC_channel(int channel);  //参数对应着通道号（ch ：0~15 之间）

 
#endif 
