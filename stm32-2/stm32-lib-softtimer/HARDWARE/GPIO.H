#ifndef __GPIO_H
#define __GPIO_H

#include "gpio.h"
#include "delay.h"   //根据时钟晶振配置的延时函数
#include "sys.h"			//基础配置（包括 gpio输入输出简化 及变量名的简化

void GPIO_Init_Mode(void);

 

void InitSensor_Voice(void);

unsigned char Get_Voice(void);

void InitSensor_Renti(void);

void InitSensor_Renti_2(void);

unsigned char Get_Renti(void);

unsigned char Get_Renti_2(void);

// void InitSensor_Key(void);
  
// unsigned char Get_Key(void);

// void InitSensor_Key_2(void);
  
// unsigned char Get_Key_2(void);


void InitSensor_Huoyan(void);

unsigned char Get_Huoyan(void);



#endif  
	 

