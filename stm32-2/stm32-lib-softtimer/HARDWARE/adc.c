#include "adc.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_gpio.h"
#include "sys.h"


static void ADC_Init_GPIO_channel(int channel)
{

	GPIO_InitTypeDef GPIO_InitStructure;

	switch (channel)
	{
	case 0:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		break;

	case 1:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		break;

	case 2:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		break;

	case 3:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		break;

	case 4:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		break;

	case 5:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		break;

	case 6:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		break;

	case 7:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		break;

	case 8:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		break;

	case 9:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		break;

	case 10:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		break;

	case 11:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		break;

	case 12:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		break;

	case 13:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		break;

	case 14:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		break;

	case 15:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		break;

	default:
		break;
	}
}





//��ʼ��ADC
void Adc_Init_channel(int channel)
{
	ADC_InitTypeDef ADC_InitStructure;

	ADC_Init_GPIO_channel(channel); //GPIO��ʼ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE); //ʹ��ADC1ͨ��ʱ��

	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	ADC_DeInit(ADC1); //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;					//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;						//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;					//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //ת���������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;				//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;								//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);									//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���

	ADC_Cmd(ADC1, ENABLE); //ʹ��ָ����ADC1

	ADC_ResetCalibration(ADC1); //ʹ�ܸ�λУ׼

	while (ADC_GetResetCalibrationStatus(ADC1))
		; //�ȴ���λУ׼����

	ADC_StartCalibration(ADC1); //����ADУ׼

	while (ADC_GetCalibrationStatus(ADC1))
		; //�ȴ�У׼����

	//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1������ת����������
}




//���ADCֵ
//ch:ͨ��ֵ 0~3
unsigned int  Get_ADC_channel(int channel)
{
	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_239Cycles5); //ADC1,ADCͨ��,����ʱ��Ϊ239.5����

	ADC_SoftwareStartConvCmd(ADC1, ENABLE); //ʹ��ָ����ADC1������ת����������

	while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
		; //�ȴ�ת������

	return ADC_GetConversionValue(ADC1); //�������һ��ADC1�������ת�����
}