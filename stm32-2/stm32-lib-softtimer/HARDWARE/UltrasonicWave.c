
#include "ultrasonicwave.h"
#include "sys.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
#include "delay.h"

float UltrasonicWave_Distance_ch1 = 0; //计算出的距离
float UltrasonicWave_Distance_ch2 = 0; //计算出的距离
float UltrasonicWave_Distance_ch3 = 0; //计算出的距离
float UltrasonicWave_Distance_ch4 = 0; //计算出的距离

/*
 * 通用定时器中断初始化
 * 这里时钟选择为APB1的2倍，而APB1为36M
 * arr：自动重装值。
 * psc：时钟预分频数
 * 这里使用的是定时器3!
 */
void TIM3_UltrasonicWave_Init(u16 arr, u16 psc)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); /* 时钟使能 */

  TIM_TimeBaseStructure.TIM_Period = arr - 1;                 /* 设置在下一个更新事件装入活动的自动重装载寄存器周期的值   计数到5000为500ms */
  TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;              /* 设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率 */
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;                /* 设置时钟分割:TDTS = Tck_tim */
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; /* TIM向上计数模式 */
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);             /* 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位 */

  TIM_ITConfig(      /* 使能或者失能指定的TIM中断 */
               TIM3, /* TIM2 */
               TIM_IT_Update,
               ENABLE /* 使能 */
  );
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;           /* TIM3中断 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; /* 先占优先级0级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        /* 从优先级3级 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           /* IRQ通道被使能 */
  NVIC_Init(&NVIC_InitStructure);                           /* 根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 */

  //TIM_Cmd( TIM3, ENABLE );                                                /* 使能TIMx外设 */
}

#if 1

void TIM3_IRQHandler(void) /* TIM3中断 */
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) /* 检查指定的TIM中断发生与否:TIM 中断源 */
  {

    TIM_ClearITPendingBit(TIM3, TIM_IT_Update); /* 清除TIMx的中断待处理位:TIM 中断源 */
  }
}
#endif

/*
 * 函数名：UltrasonicWave_Configuration
 * 描述  ：超声波模块的初始化
 * 输入  ：无
 * 输出  ：无
 */
void UltrasonicWave_Configuration_channel(int channel)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  TIM3_UltrasonicWave_Init(60000, 72);

  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //关闭jtag
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

  switch (channel)
  {
  case 1:
    GPIO_InitStructure.GPIO_Pin = TRIG_PIN_ch1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设为推挽输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TRIG_PORT_ch1, &GPIO_InitStructure); //初始化外设GPIO

    GPIO_InitStructure.GPIO_Pin = ECHO_PIN_ch1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设为输入
    GPIO_Init(ECHO_PORT_ch1, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource7);
    EXTI_InitStructure.EXTI_Line = EXTI_Line7;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure); //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;        //使能按键所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        //子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);                           //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

    break;

    //************************************************************//

  case 2:
    GPIO_InitStructure.GPIO_Pin = TRIG_PIN_ch2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设为推挽输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TRIG_PORT_ch2, &GPIO_InitStructure); //初始化外设GPIO

    GPIO_InitStructure.GPIO_Pin = ECHO_PIN_ch2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设为输入
    GPIO_Init(ECHO_PORT_ch2, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);
    EXTI_InitStructure.EXTI_Line = EXTI_Line5;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure); //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;        //使能按键所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        //子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);                           //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

    break;

    //************************************************************//

  case 3:
    GPIO_InitStructure.GPIO_Pin = TRIG_PIN_ch3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设为推挽输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TRIG_PORT_ch3, &GPIO_InitStructure); //初始化外设GPIO

    GPIO_InitStructure.GPIO_Pin = ECHO_PIN_ch3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设为输入
    GPIO_Init(ECHO_PORT_ch3, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource3);
    EXTI_InitStructure.EXTI_Line = EXTI_Line3;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure); //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;          //使能按键所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        //子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);                           //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

    break;

    //************************************************************//

  case 4:
    GPIO_InitStructure.GPIO_Pin = TRIG_PIN_ch4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设为推挽输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TRIG_PORT_ch4, &GPIO_InitStructure); //初始化外设GPIO

    GPIO_InitStructure.GPIO_Pin = ECHO_PIN_ch1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设为输入
    GPIO_Init(ECHO_PORT_ch1, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
    EXTI_InitStructure.EXTI_Line = EXTI_Line1;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure); //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;          //使能按键所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        //子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);                           //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

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

  delay_us(10); //延时10us
  if (EXTI_GetITStatus(EXTI_Line7) != RESET)
  {
    TIM_SetCounter(TIM3, 0);
    TIM_Cmd(TIM3, ENABLE); //开启时钟

    while (GPIO_ReadInputDataBit(ECHO_PORT_ch1, ECHO_PIN_ch1))
      ; //等待低电平

    TIM_Cmd(TIM3, DISABLE);                                           //定时器2失能
    UltrasonicWave_Distance_ch1 = TIM_GetCounter(TIM3) * 34 / 2000.0; //计算距离&&UltrasonicWave_Distance<150

    EXTI_ClearITPendingBit(EXTI_Line7); //清除EXTI7线路挂起位
  }

  if (EXTI_GetITStatus(EXTI_Line5) != RESET)
  {
    TIM_SetCounter(TIM3, 0);
    TIM_Cmd(TIM3, ENABLE); //开启时钟

    while (GPIO_ReadInputDataBit(ECHO_PORT_ch2, ECHO_PIN_ch2))
      ; //等待低电平

    TIM_Cmd(TIM3, DISABLE);                                           //定时器2失能
    UltrasonicWave_Distance_ch2 = TIM_GetCounter(TIM3) * 34 / 2000.0; //计算距离&&UltrasonicWave_Distance<150

    EXTI_ClearITPendingBit(EXTI_Line5); //清除EXTI7线路挂起位
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

  delay_us(10); //延时10us
  if (EXTI_GetITStatus(EXTI_Line3) != RESET)
  {
    TIM_SetCounter(TIM3, 0);
    TIM_Cmd(TIM3, ENABLE); //开启时钟

    while (GPIO_ReadInputDataBit(ECHO_PORT_ch3, ECHO_PIN_ch3))
      ; //等待低电平

    TIM_Cmd(TIM3, DISABLE);                                           //定时器2失能
    UltrasonicWave_Distance_ch3 = TIM_GetCounter(TIM3) * 34 / 2000.0; //计算距离&&UltrasonicWave_Distance<150

    EXTI_ClearITPendingBit(EXTI_Line3); //清除EXTI7线路挂起位
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

  delay_us(10); //延时10us
  if (EXTI_GetITStatus(EXTI_Line1) != RESET)
  {
    TIM_SetCounter(TIM3, 0);
    TIM_Cmd(TIM3, ENABLE); //开启时钟

    while (GPIO_ReadInputDataBit(ECHO_PORT_ch4, ECHO_PIN_ch4))
      ; //等待低电平

    TIM_Cmd(TIM3, DISABLE);                                           //定时器2失能
    UltrasonicWave_Distance_ch4 = TIM_GetCounter(TIM3) * 34 / 2000.0; //计算距离&&UltrasonicWave_Distance<150

    EXTI_ClearITPendingBit(EXTI_Line1); //清除EXTI7线路挂起位
  }

#ifdef OS_TICKS_PER_SEC //ucosii
  OSIntExit();
#endif
}

/*
 * 函数名：UltrasonicWave_StartMeasure
 * 描述  ：开始测距，发送一个>10us的脉冲，然后测量返回的高电平时间
 * 输入  ：无
 * 输出  ：无
 */
void UltrasonicWave_StartMeasure_ch1(void)
{
  GPIO_SetBits(TRIG_PORT_ch1, TRIG_PIN_ch1); //送>10US的高电平?TRIG_PORT,TRIG_PIN_ch1这两个在define中有?
  delay_us(20);                              //延时20US
  GPIO_ResetBits(TRIG_PORT_ch1, TRIG_PIN_ch1);
}

void UltrasonicWave_StartMeasure_ch2(void)
{
  GPIO_SetBits(TRIG_PORT_ch2, TRIG_PIN_ch2); //送>10US的高电平?TRIG_PORT,TRIG_PIN_ch1这两个在define中有?
  delay_us(20);                              //延时20US
  GPIO_ResetBits(TRIG_PORT_ch2, TRIG_PIN_ch2);
}

void UltrasonicWave_StartMeasure_ch3(void)
{
  GPIO_SetBits(TRIG_PORT_ch3, TRIG_PIN_ch3); //送>10US的高电平?TRIG_PORT,TRIG_PIN_ch1这两个在define中有?
  delay_us(20);                              //延时20US
  GPIO_ResetBits(TRIG_PORT_ch3, TRIG_PIN_ch3);
}

void UltrasonicWave_StartMeasure_ch4(void)
{
  GPIO_SetBits(TRIG_PORT_ch4, TRIG_PIN_ch4); //送>10US的高电平?TRIG_PORT,TRIG_PIN_ch1这两个在define中有?
  delay_us(20);                              //延时20US
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
