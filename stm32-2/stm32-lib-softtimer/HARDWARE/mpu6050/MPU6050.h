#ifndef __MPU6050_H
#define __MPU6050_H

#include "delay.h"
#include "STM32_I2C.h"
#include "usart.h"


#define DEFAULT_MPU_HZ  (100)

extern float Pose[3];//��̬
extern short Gyro[3];//������
extern short Accel[3];//���ٶ�
	
	
	
//���ⲿ���õ�API
void MPU6050_initialize(void); //��ʼ��


void MPU6050_Pose(float *pose ,short *gyro,short *accel);

#endif
