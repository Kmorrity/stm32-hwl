#include "PID.h"

int P_DATA_ROW=4;
int D_DATA_ROW=4;
float I_DATA_ROW=20;

int P_DATA_LINE=4;
int D_DATA_LINE=4;
float I_DATA_LINE=20;


int s_L,s_R,s_U,s_D;

float thiserror_L,lasterror_L,preverror_L,thiserror_R,lasterror_R,preverror_R,
      thiserror_U,lasterror_U,preverror_U,thiserror_D,lasterror_D,preverror_D;
/*************************************************************************
*                         
*
*  函数名称：PID_Init
*  功能说明：PID参数初始化
*  参数说明：无
*  函数返回：无
*************************************************************************/
void PID_Init(void)
{
  sptr->LastError = 0;       //Error[-1]
  sptr->PrevError = 0;       //Error[-2]
  sptr->Proportion =P_DATA_LINE;  //比例常数Proportional Const
  sptr->Integral  = I_DATA_LINE;     //积分常数Integral Const
  sptr->Derivative =D_DATA_LINE;  //微分常数Derivative Const
  //sptr->SetPoint =ss;       //目标脉冲数
  
}


/*************************************************************************
*
*  函数名称：IncPIDCalc
*  功能说明：PID运算得出增量值
*  参数说明：FanPoin--当前数值  S_L--期望数值
*  函数返回：返回增量值
*************************************************************************/

float IncPIDCalc_L(int FanPoint,int s_L)
{


   float pError,iError,dError;
   float iIncpid;


  sptr->Proportion =P_DATA_ROW;  //比例常数Proportional Const
  sptr->Integral  = I_DATA_ROW;     //积分常数Integral Const
  sptr->Derivative =D_DATA_ROW;  //微分常数Derivative Const


   thiserror_L=s_L- FanPoint;            //增量计算
   pError = thiserror_L-lasterror_L;
   iError = thiserror_L;
   dError = (thiserror_L-lasterror_L)-(lasterror_L-preverror_L);
   iIncpid = sptr->Proportion * pError + sptr->Integral * iError + sptr->Derivative * dError;      
   preverror_L = lasterror_L; 
   lasterror_L = thiserror_L;

    return(iIncpid);                    //返回增量值
}


float IncPIDCalc_R(int FanPoint,int s_R)
{

   float pError,iError,dError;
   float iIncpid;


  sptr->Proportion =P_DATA_ROW;  //比例常数Proportional Const
  sptr->Integral  = I_DATA_ROW;     //积分常数Integral Const
  sptr->Derivative =D_DATA_ROW;  //微分常数Derivative Const


   thiserror_R=s_R- FanPoint;            //增量计算
   pError = thiserror_R-lasterror_R;
   iError = thiserror_R;
   dError = (thiserror_R-lasterror_R)-(lasterror_R-preverror_R);
   iIncpid = sptr->Proportion * pError + sptr->Integral* iError + sptr->Derivative * dError;    
   preverror_R = lasterror_R;
   lasterror_R = thiserror_R;

    return(iIncpid);                    //返回增量值
}


float IncPIDCalc_U(int FanPoint,int s_U)
{


   float pError,iError,dError;
   float iIncpid;


  sptr->Proportion =P_DATA_LINE;  //比例常数Proportional Const
  sptr->Integral  = I_DATA_LINE;     //积分常数Integral Const
  sptr->Derivative =D_DATA_LINE;  //微分常数Derivative Const


   thiserror_L=s_U- FanPoint;            //增量计算
   pError = thiserror_U-lasterror_U;
   iError = thiserror_U;
   dError = (thiserror_U-lasterror_U)-(lasterror_U-preverror_U);
   iIncpid = sptr->Proportion * pError + sptr->Integral * iError + sptr->Derivative * dError;      
   preverror_U = lasterror_U; 
   lasterror_U = thiserror_U;

    return(iIncpid);                    //返回增量值
}

float IncPIDCalc_D(int FanPoint,int s_D)
{


   float pError,iError,dError;
   float iIncpid;


  sptr->Proportion =P_DATA_LINE;  //比例常数Proportional Const
  sptr->Integral  = I_DATA_LINE;     //积分常数Integral Const
  sptr->Derivative =D_DATA_LINE;  //微分常数Derivative Const


   thiserror_L=s_D- FanPoint;            //增量计算
   pError = thiserror_D-lasterror_D;
   iError = thiserror_D;
   dError = (thiserror_U-lasterror_D)-(lasterror_D-preverror_D);
   iIncpid = sptr->Proportion * pError + sptr->Integral * iError + sptr->Derivative * dError;      
   preverror_D = lasterror_D; 
   lasterror_D = thiserror_D;

    return(iIncpid);                    //返回增量值
}



