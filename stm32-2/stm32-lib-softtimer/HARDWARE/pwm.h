#ifndef __PWM_H
#define __PWM_H
#include "sys.h"



void TIM1_PWM_Init(u16 arr,u16 psc);  //A10 A11

void TIM2_PWM_Init(u16 arr,u16 psc);



void SetSensor_Pwm10(unsigned char value);
void SetSensor_Pwm11(unsigned char value);


#endif
