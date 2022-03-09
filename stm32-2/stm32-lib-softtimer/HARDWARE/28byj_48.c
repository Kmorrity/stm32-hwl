
#include "stdbool.h"
#include "sys.h"
#include "delay.h"
#include "28byj_48.h"
//IN4: PB6  d
//IN3: PB5  c
//IN2: PB4  b
//IN1: PB3   a
//�������
u8 phasecw[8] ={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};// ��ʱ��
//1000,1100,0100,0110,0010,0011,0001,1001
u8 phaseccw[8]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};// ˳ʱ��
//1001,0001,0011,0010,0110,0100,1100,1000

//���ų�ʼ��
void Step_Motor_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5;
    GPIO_Init(GPIOB,&GPIO_InitStructure);   
}
//����ӳ��
void SetMotor(unsigned char InputData)//���ݴ��͵�����Inputdata���������������
{//���ݴ��͵�����Inputdata����PB5-PB8�������
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
//�����5.625 360/5.625=64 ���ٱ�1/64 
//��64*64������תһȦ
//nȦ�� 
//position ����
void motorNcircle(int n, int position) //nΪ�������ת����Ȧ����positionΪ��ת���߷�ת
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
    { //4�൥˫8��
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
            delay_ms(2); //��ʱ���ٶȿ��ƣ���ֵԽ���ٶ�Խ��������0.65A
        }
    }

    for (i = 0; i < y; i++)
    // for(i=0;i<8;i++)
    { //4�൥˫8��
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
            delay_ms(2); //��ʱ���ٶȿ��ƣ���ֵԽ���ٶ�Խ��������0.65A
        }
    }
}
