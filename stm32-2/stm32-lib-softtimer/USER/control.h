#ifndef __CONTROL_H__
#define __CONTROL_H__


/******************ͨ����Ӧ��ϵ************************
CH0 ----> RIGHT
CH1 ----> FORWARD
CH2 ---->LEFT
CH3----->BEHIND
*******************************************************/


//��ʼ����ȡ���
void Get_Average_Init(void);




//��ȡ����ͨ����ƫ����

int Get_Offset_right(void);

int Get_Offset_forward(void);

int Get_Offset_left(void);

int Get_Offset_behind(void);



//��ȡ����ͨ����ƫ��������ֵ
int Get_ABS_Offset_right(void);

int Get_ABS_Offset_forward(void);

int Get_ABS_Offset_left(void);

int Get_ABS_Offset_behind(void);



//����С��  ������Χ -100 -1000
void Turn_Car(int left , int right);





#endif
