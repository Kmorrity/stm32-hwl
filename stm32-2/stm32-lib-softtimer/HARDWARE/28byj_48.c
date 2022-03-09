
#include "stdbool.h"
#include "sys.h"
#include "delay.h"
#include "28byj_48.h"
//IN4: PB6  d
//IN3: PB5  c
//IN2: PB4  b
//IN1: PB3   a
//四相八拍
u8 phasecw[8] ={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};// 逆时针
//1000,1100,0100,0110,0010,0011,0001,1001
u8 phaseccw[8]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};// 顺时针
//1001,0001,0011,0010,0110,0100,1100,1000

//引脚初始化
void Step_Motor_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5;
    GPIO_Init(GPIOB,&GPIO_InitStructure);   
}
//引脚映射
void SetMotor(unsigned char InputData)//根据传送的数据Inputdata设置脉冲引脚输出
{//根据传送的数据Inputdata设置PB5-PB8引脚输出
    if(InputData&0x01)
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_5);
    }
    else
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_5);
    }
    if(InputData&0x02)
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_6);
    }
    else
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_6);

    }
    if(InputData&0x04)
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_7);
    }
    else
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_7);
    }
    if(InputData&0x08)
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_8);
    }
    else
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_8);
    }
}
//步距角5.625 360/5.625=64 减速比1/64 
//故64*64个脉冲转一圈
//n圈数 
//position 方向
void motorNcircle(int n, int position) //n为步进电机转动的圈数，position为正转或者反转
{
    unsigned int i, k = 0;
    unsigned int x, y;
    x = 0;
    if (n >= 360)
    {
        x = n / 360;
    }

    y = n % 360;
    y = 36000 / y;
    y = 64 * 800 / y;

    for (i = 0; i < 64 * 8 * x; i++)
    // for(i=0;i<8;i++)
    { //4相单双8拍
        for (k = 0; k < 8; k++)
        {
            if (1 == position)
            {
                SetMotor(phasecw[k]);
            }
            else
            {
                SetMotor(phaseccw[k]);
            }
            delay_ms(2); //延时：速度控制，数值越大速度越慢。电流0.65A
        }
    }

    for (i = 0; i < y; i++)
    // for(i=0;i<8;i++)
    { //4相单双8拍
        for (k = 0; k < 8; k++)
        {
            if (1 == position)
            {
                SetMotor(phasecw[k]);
            }
            else
            {
                SetMotor(phaseccw[k]);
            }
            delay_ms(2); //延时：速度控制，数值越大速度越慢。电流0.65A
        }
    }
}
