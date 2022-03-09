#ifndef __CONTROL_H__
#define __CONTROL_H__


/******************通道对应关系************************
CH0 ----> RIGHT
CH1 ----> FORWARD
CH2 ---->LEFT
CH3----->BEHIND
*******************************************************/


//初始化获取多个
void Get_Average_Init(void);




//获取各个通道的偏移量

int Get_Offset_right(void);

int Get_Offset_forward(void);

int Get_Offset_left(void);

int Get_Offset_behind(void);



//获取各个通道的偏移量绝对值
int Get_ABS_Offset_right(void);

int Get_ABS_Offset_forward(void);

int Get_ABS_Offset_left(void);

int Get_ABS_Offset_behind(void);



//控制小吃  参数范围 -100 -1000
void Turn_Car(int left , int right);





#endif
