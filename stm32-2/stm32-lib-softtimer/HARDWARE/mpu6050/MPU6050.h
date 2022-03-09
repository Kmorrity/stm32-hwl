#ifndef __MPU6050_H
#define __MPU6050_H

#include "delay.h"
#include "STM32_I2C.h"
#include "usart.h"


#define DEFAULT_MPU_HZ  (100)

extern float Pose[3];//姿态
extern short Gyro[3];//陀螺仪
extern short Accel[3];//加速度
	
	
	
//供外部调用的API
void MPU6050_initialize(void); //初始化


void MPU6050_Pose(float *pose ,short *gyro,short *accel);

#endif
