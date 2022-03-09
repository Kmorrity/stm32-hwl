

#ifndef __PID_H__
#define __PID_H__

extern int s_L,s_R,s_U,s_D;
extern int P_DATA_ROW;
extern int D_DATA_ROW;
extern float I_DATA_ROW;

extern int P_DATA_LINE;
extern int D_DATA_LINE;
extern float I_DATA_LINE;

/***************************************************************************
*                              ����PID�ṹ��
****************************************************************************/
typedef struct PID
{
    int SetPoint;      //�趨Ŀ��Desired Value
    double Proportion; //��������Proportional Const
    double Integral; //���ֳ���Integral Const
    double Derivative; //΢�ֳ���Derivative Const
    int LastError;    //Error[-1]
    int PrevError;    //Error[-2]
} PID;


/***************************************************************************
*                              ����PIDʵ��
****************************************************************************/
static PID sPID;
static PID *sptr = &sPID;



//#define SETPOINT  500
//int ss=330;


void PID_Init(void);
float IncPIDCalc_L(int FanPoint,int s_L);
float IncPIDCalc_R(int FanPoint,int s_R);
float IncPIDCalc_U(int FanPoint,int s_U);
float IncPIDCalc_D(int FanPoint,int s_D);
#endif
