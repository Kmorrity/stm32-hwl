#ifndef __28BYJ48_H
#define __28BYJ48_H
#include "stdbool.h"
void Step_Motor_GPIO_Init(void);
void SetMotor(unsigned char InputData);//根据传送的数据Inputdata设置脉冲引脚输出
void motorNcircle(int n,int position);//n为步进电机转动的圈数，position为正转或者反转


#endif
