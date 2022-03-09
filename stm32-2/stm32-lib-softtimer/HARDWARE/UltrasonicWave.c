
#include "ultrasonicwave.h"
#include "sys.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
#include "delay.h"

float UltrasonicWave_Distance_ch1 = 0; //������ľ���
float UltrasonicWave_Distance_ch2 = 0; //������ľ���
float UltrasonicWave_Distance_ch3 = 0; //������ľ���
float UltrasonicWave_Distance_ch4 = 0; //������ľ���

/*
 * ͨ�ö�ʱ���жϳ�ʼ��
 * ����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
 * arr���Զ���װֵ��
 * psc��ʱ��Ԥ��Ƶ��
 * ����ʹ�õ��Ƕ�ʱ��3!
 */
void TIM3_UltrasonicWave_Init(u16 arr, u16 psc)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); /* ʱ��ʹ�� */

  TIM_TimeBaseStructure.TIM_Period = arr - 1;                 /* ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ   ������5000Ϊ500ms */
  TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;              /* ����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ�� */
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;                /* ����ʱ�ӷָ�:TDTS = Tck_tim */
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; /* TIM���ϼ���ģʽ */
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);             /* ����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ */

  TIM_ITConfig(      /* ʹ�ܻ���ʧ��ָ����TIM�ж� */
               TIM3, /* TIM2 */
               TIM_IT_Update,
               ENABLE /* ʹ�� */
  );
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;           /* TIM3�ж� */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; /* ��ռ���ȼ�0�� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        /* �����ȼ�3�� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           /* IRQͨ����ʹ�� */
  NVIC_Init(&NVIC_InitStructure);                           /* ����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� */

  //TIM_Cmd( TIM3, ENABLE );                                                /* ʹ��TIMx���� */
}

#if 1

void TIM3_IRQHandler(void) /* TIM3�ж� */
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) /* ���ָ����TIM�жϷ������:TIM �ж�Դ */
  {

    TIM_ClearITPendingBit(TIM3, TIM_IT_Update); /* ���TIMx���жϴ�����λ:TIM �ж�Դ */
  }
}
#endif

/*
 * ��������UltrasonicWave_Configuration
 * ����  ��������ģ��ĳ�ʼ��
 * ����  ����
 * ���  ����
 */
void UltrasonicWave_Configuration_channel(int channel)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  TIM3_UltrasonicWave_Init(60000, 72);

  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //�ر�jtag
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

  switch (channel)
  {
  case 1:
    GPIO_InitStructure.GPIO_Pin = TRIG_PIN_ch1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //��Ϊ�������ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TRIG_PORT_ch1, &GPIO_InitStructure); //��ʼ������GPIO

    GPIO_InitStructure.GPIO_Pin = ECHO_PIN_ch1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //��Ϊ����
    GPIO_Init(ECHO_PORT_ch1, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource7);
    EXTI_InitStructure.EXTI_Line = EXTI_Line7;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure); //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;        //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        //�����ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);                           //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

    break;

    //************************************************************//

  case 2:
    GPIO_InitStructure.GPIO_Pin = TRIG_PIN_ch2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //��Ϊ�������ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TRIG_PORT_ch2, &GPIO_InitStructure); //��ʼ������GPIO

    GPIO_InitStructure.GPIO_Pin = ECHO_PIN_ch2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //��Ϊ����
    GPIO_Init(ECHO_PORT_ch2, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);
    EXTI_InitStructure.EXTI_Line = EXTI_Line5;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure); //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;        //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        //�����ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);                           //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

    break;

    //************************************************************//

  case 3:
    GPIO_InitStructure.GPIO_Pin = TRIG_PIN_ch3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //��Ϊ�������ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TRIG_PORT_ch3, &GPIO_InitStructure); //��ʼ������GPIO

    GPIO_InitStructure.GPIO_Pin = ECHO_PIN_ch3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //��Ϊ����
    GPIO_Init(ECHO_PORT_ch3, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource3);
    EXTI_InitStructure.EXTI_Line = EXTI_Line3;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure); //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;          //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        //�����ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);                           //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

    break;

    //************************************************************//

  case 4:
    GPIO_InitStructure.GPIO_Pin = TRIG_PIN_ch4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //��Ϊ�������ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TRIG_PORT_ch4, &GPIO_InitStructure); //��ʼ������GPIO

    GPIO_InitStructure.GPIO_Pin = ECHO_PIN_ch1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //��Ϊ����
    GPIO_Init(ECHO_PORT_ch1, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
    EXTI_InitStructure.EXTI_Line = EXTI_Line1;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure); //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;          //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        //�����ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);                           //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

    break;

    //************************************************************//

  default:
    break;
  }
}

void EXTI9_5_IRQHandler(void)
{
#ifdef OS_TICKS_PER_SEC //ucosii
  OSIntEnter();
#endif

  delay_us(10); //��ʱ10us
  if (EXTI_GetITStatus(EXTI_Line7) != RESET)
  {
    TIM_SetCounter(TIM3, 0);
    TIM_Cmd(TIM3, ENABLE); //����ʱ��

    while (GPIO_ReadInputDataBit(ECHO_PORT_ch1, ECHO_PIN_ch1))
      ; //�ȴ��͵�ƽ

    TIM_Cmd(TIM3, DISABLE);                                           //��ʱ��2ʧ��
    UltrasonicWave_Distance_ch1 = TIM_GetCounter(TIM3) * 34 / 2000.0; //�������&&UltrasonicWave_Distance<150

    EXTI_ClearITPendingBit(EXTI_Line7); //���EXTI7��·����λ
  }

  if (EXTI_GetITStatus(EXTI_Line5) != RESET)
  {
    TIM_SetCounter(TIM3, 0);
    TIM_Cmd(TIM3, ENABLE); //����ʱ��

    while (GPIO_ReadInputDataBit(ECHO_PORT_ch2, ECHO_PIN_ch2))
      ; //�ȴ��͵�ƽ

    TIM_Cmd(TIM3, DISABLE);                                           //��ʱ��2ʧ��
    UltrasonicWave_Distance_ch2 = TIM_GetCounter(TIM3) * 34 / 2000.0; //�������&&UltrasonicWave_Distance<150

    EXTI_ClearITPendingBit(EXTI_Line5); //���EXTI7��·����λ
  }

#ifdef OS_TICKS_PER_SEC //ucosii
  OSIntExit();
#endif
}

void EXTI3_IRQHandler(void)
{
#ifdef OS_TICKS_PER_SEC //ucosii
  OSIntEnter();
#endif

  delay_us(10); //��ʱ10us
  if (EXTI_GetITStatus(EXTI_Line3) != RESET)
  {
    TIM_SetCounter(TIM3, 0);
    TIM_Cmd(TIM3, ENABLE); //����ʱ��

    while (GPIO_ReadInputDataBit(ECHO_PORT_ch3, ECHO_PIN_ch3))
      ; //�ȴ��͵�ƽ

    TIM_Cmd(TIM3, DISABLE);                                           //��ʱ��2ʧ��
    UltrasonicWave_Distance_ch3 = TIM_GetCounter(TIM3) * 34 / 2000.0; //�������&&UltrasonicWave_Distance<150

    EXTI_ClearITPendingBit(EXTI_Line3); //���EXTI7��·����λ
  }

#ifdef OS_TICKS_PER_SEC //ucosii
  OSIntExit();
#endif
}

void EXTI1_IRQHandler(void)
{
#ifdef OS_TICKS_PER_SEC //ucosii
  OSIntEnter();
#endif

  delay_us(10); //��ʱ10us
  if (EXTI_GetITStatus(EXTI_Line1) != RESET)
  {
    TIM_SetCounter(TIM3, 0);
    TIM_Cmd(TIM3, ENABLE); //����ʱ��

    while (GPIO_ReadInputDataBit(ECHO_PORT_ch4, ECHO_PIN_ch4))
      ; //�ȴ��͵�ƽ

    TIM_Cmd(TIM3, DISABLE);                                           //��ʱ��2ʧ��
    UltrasonicWave_Distance_ch4 = TIM_GetCounter(TIM3) * 34 / 2000.0; //�������&&UltrasonicWave_Distance<150

    EXTI_ClearITPendingBit(EXTI_Line1); //���EXTI7��·����λ
  }

#ifdef OS_TICKS_PER_SEC //ucosii
  OSIntExit();
#endif
}

/*
 * ��������UltrasonicWave_StartMeasure
 * ����  ����ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
 * ����  ����
 * ���  ����
 */
void UltrasonicWave_StartMeasure_ch1(void)
{
  GPIO_SetBits(TRIG_PORT_ch1, TRIG_PIN_ch1); //��>10US�ĸߵ�ƽ?TRIG_PORT,TRIG_PIN_ch1��������define����?
  delay_us(20);                              //��ʱ20US
  GPIO_ResetBits(TRIG_PORT_ch1, TRIG_PIN_ch1);
}

void UltrasonicWave_StartMeasure_ch2(void)
{
  GPIO_SetBits(TRIG_PORT_ch2, TRIG_PIN_ch2); //��>10US�ĸߵ�ƽ?TRIG_PORT,TRIG_PIN_ch1��������define����?
  delay_us(20);                              //��ʱ20US
  GPIO_ResetBits(TRIG_PORT_ch2, TRIG_PIN_ch2);
}

void UltrasonicWave_StartMeasure_ch3(void)
{
  GPIO_SetBits(TRIG_PORT_ch3, TRIG_PIN_ch3); //��>10US�ĸߵ�ƽ?TRIG_PORT,TRIG_PIN_ch1��������define����?
  delay_us(20);                              //��ʱ20US
  GPIO_ResetBits(TRIG_PORT_ch3, TRIG_PIN_ch3);
}

void UltrasonicWave_StartMeasure_ch4(void)
{
  GPIO_SetBits(TRIG_PORT_ch4, TRIG_PIN_ch4); //��>10US�ĸߵ�ƽ?TRIG_PORT,TRIG_PIN_ch1��������define����?
  delay_us(20);                              //��ʱ20US
  GPIO_ResetBits(TRIG_PORT_ch4, TRIG_PIN_ch4);
}

 

float UltrasonicWave_GetDistance_ch1(void)
{
  UltrasonicWave_StartMeasure_ch1();
  delay_us(1000 * 200);
  return UltrasonicWave_Distance_ch1;
}

float UltrasonicWave_GetDistance_ch2(void)
{
  UltrasonicWave_StartMeasure_ch2();
  delay_us(1000 * 200);
  return UltrasonicWave_Distance_ch2;
}

float UltrasonicWave_GetDistance_ch3(void)
{
  UltrasonicWave_StartMeasure_ch3();
  delay_us(1000 * 200);
  return UltrasonicWave_Distance_ch3;
}

float UltrasonicWave_GetDistance_ch4(void)
{
  UltrasonicWave_StartMeasure_ch4();
  delay_us(1000 * 200);
  return UltrasonicWave_Distance_ch4;
}
/******************* (C) 1209 Lab *****END OF FILE************/
