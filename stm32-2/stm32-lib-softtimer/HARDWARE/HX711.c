/************************************************************************************
						
*************************************************************************************/
#include "HX711.h"
#include "delay.h"





static unsigned long Weight_calibration = 0;
static long Weight_physical = 0;



//У׼����
//��Ϊ��ͬ�Ĵ������������߲��Ǻ�һ�£���ˣ�ÿһ����������Ҫ�������������������ʹ����ֵ��׼ȷ��
//�����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ��
//������Գ���������ƫСʱ����С����ֵ��
//��ֵ����ΪС��
#define GapValue 106.5
// #define GapValue 430



void yali_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PF�˿�ʱ��

	//HX711_SCK
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB
	
	//HX711_DOUT
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);  
	
	GPIO_SetBits(GPIOB,GPIO_Pin_0);					//��ʼ������Ϊ0
}



//****************************************************
//��ȡHX711
//****************************************************
u32 HX711_Read(void)	//����128
{

	unsigned int ii = 0 ;

	unsigned long count; 
	unsigned char i; 
  	HX711_DOUT=1; 
	delay_us(1);
  	HX711_SCK=0; 
  	count=0; 
  	while(HX711_DOUT && ii++<500000 ); 
  	for(i=0;i<24;i++)
	{ 
	  	HX711_SCK=1; 
	  	count=count<<1; 
		delay_us(1);
		HX711_SCK=0; 
	  	if(HX711_DOUT)
			count++; 
		delay_us(1);
	} 
 	HX711_SCK=1; 
    count=count^0x800000;//��25�������½�����ʱ��ת������
	delay_us(1);
	HX711_SCK=0;  
	return(count);
}
 


void yali_Weight_calibration()
{
	Weight_calibration = HX711_Read();	
} 



int yali_Get_Weight()
{
    int result_value ;
	Weight_physical = HX711_Read();
	Weight_physical = Weight_physical - Weight_calibration;		
	if(Weight_physical > 0)			
	{	
		Weight_physical = (unsigned int)((float)Weight_physical/GapValue); 																		
	}
	else
	{
		Weight_physical = 0;		
	}

    result_value = (int)Weight_physical;
	return result_value;
}

