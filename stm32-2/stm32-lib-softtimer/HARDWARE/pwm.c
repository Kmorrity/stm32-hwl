#include "pwm.h"
#include "led.h"

/********************************************	 
 TIMx 
TIM1_BKIN->PB12
TIM1_CH1N->PB13
TIM1_CH2N->PB14
TIM1_CH3N->PB15
TIM1_CH1->PA8
TIM1_CH2->PA9
TIM1_CH3->PA10
TIM1_CH4->PA11
TIM1_ETR->PA12
TIM2_CH1->PA0
TIM2_CH2->PA1
TIM2_CH3->PA2
TIM2_Ch4->PA3
TIM3_ETR->PD2
TIM3_CH1->PB4-PC6-Remap
TIM3_CH2->PB5-PC7-Remap
TIM3_CH3->PC8-Remap
TIM3_CH4->PC9-Remap
TIM4_CH1->PD12-Remap
TIM4_CH2->PD13-Remap
TIM4_CH3->PD14-Remap
TIM4_CH4->PD15-Remap
TIM5_CH1->PA0
TIM5_CH2->PA1
TIM5_CH3->PA2
TIM5_CH4->PA3
TIM8_ETR->PA0
TIM8_BKIN->PA6
TIM8_CH1N->PA7
TIM8_CH2N->PB0
TIM8_CH3N->PB1
TIM8_CH1->PC6
TIM8_CH2->PC7
TIM8_CH3->PC8
TIM8_CH4->PC9
*************************************************************/ 	  



//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
//TIM_SetCompare1(TIM1,NUM); --����TIM1 CH1 ռ�ձ�ΪNUM

// void TIM1_PWM_Init(u16 arr,u16 psc)
// {  
//    GPIO_InitTypeDef GPIO_InitStructure;
//   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//   TIM_OCInitTypeDef  TIM_OCInitStructure;

//   RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);		// 
//   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //ʹ��GPIO����ʱ��ʹ��
                                                                        

//    //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
//   GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_11 |GPIO_Pin_8; //TIM_CH1 TIM_CH4
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//   GPIO_Init(GPIOA, &GPIO_InitStructure);

  
//   TIM_TimeBaseStructure.TIM_Period = arr-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ  80K
//   TIM_TimeBaseStructure.TIM_Prescaler =psc-1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
//   TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
//   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
//   TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ



 
//   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
//   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
//   TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
//   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
//   TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	
	
// 	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx ----------- TIM_OC3 ͨ��1
//   TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx ----------- TIM_OC4 ͨ��4


//   TIM_CtrlPWMOutputs(TIM1,ENABLE);  //MOE �����ʹ�� 

// 	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��  
//   // TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��  
//   // TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��  
//   TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CHԤװ��ʹ��
  
//   TIM_ARRPreloadConfig(TIM1, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
  
//   TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1

//   TIM_SetCompare1(TIM1,99);
// 	TIM_SetCompare4(TIM1,99);


	
// }





void TIM1_PWM_Init(u16 arr,u16 psc)
{  
   GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);		// 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //ʹ��GPIO����ʱ��ʹ��
                                                                        

   //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
  GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_11; //TIM_CH1 TIM_CH4
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  
  TIM_TimeBaseStructure.TIM_Period = arr-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ  80K
  TIM_TimeBaseStructure.TIM_Prescaler =psc-1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ


 
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
  TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�

  TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx ----------- TIM_OC4 ͨ��4

  TIM_CtrlPWMOutputs(TIM1,ENABLE);  //MOE �����ʹ�� 


  TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CHԤװ��ʹ��
  
  TIM_ARRPreloadConfig(TIM1, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
  
  TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM
	
}




void SetSensor_Pwm10(unsigned char value)
{
  if(value > 99)
  {
    value = 99;
  }

  value = 99- value ;

  TIM_SetCompare4(TIM1,value);
  
}


void SetSensor_Pwm11(unsigned char value)
{
  if(value > 99)
  {
    value = 99;
  }

  value = 99- value ;

  TIM_SetCompare1(TIM1,value);
  
}
 










void TIM2_PWM_Init(u16 arr,u16 psc)
{

   GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//
   
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //ʹ��GPIO����ʱ��ʹ��
                                                                        

   //���ø�����Ϊ�����������,���TIM2 CH1��PWM���岨��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 ; //TIM_CH3-2 TIM_CH4-3

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  
  TIM_TimeBaseStructure.TIM_Period = arr-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ  80K
  TIM_TimeBaseStructure.TIM_Prescaler =psc-1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

 
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
  TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�

//  TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx ----------- TIM_OC3 ͨ��3
//  TIM_OC2Init(TIM2, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx ----------- TIM_OC3 ͨ��3
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx ----------- TIM_OC3 ͨ��3
  TIM_OC4Init(TIM2, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx ----------- TIM_OC4 ͨ��4

  TIM_CtrlPWMOutputs(TIM2,ENABLE);  //MOE �����ʹ�� 
//  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH3Ԥװ��ʹ��
//  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH3Ԥװ��ʹ��
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH3Ԥװ��ʹ��  
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH4Ԥװ��ʹ��

  TIM_ARRPreloadConfig(TIM2, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
  
  TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM2
	
	
	TIM_SetCompare3(TIM2,99);
	TIM_SetCompare4(TIM2,99);
 
   
}

