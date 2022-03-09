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
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入引脚
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		break;

	case 1:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入引脚
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		break;

	case 2:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入引脚
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		break;

	case 3:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入引脚
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		break;

	case 4:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入引脚
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		break;

	case 5:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入引脚
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		break;

	case 6:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入引脚
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		break;

	case 7:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入引脚
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		break;

	case 8:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入引脚
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		break;

	case 9:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入引脚
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		break;

	case 10:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入引脚
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		break;

	case 11:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入引脚
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		break;

	case 12:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入引脚
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		break;

	case 13:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入引脚
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		break;

	case 14:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入引脚
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		break;

	case 15:
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入引脚
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		break;

	default:
		break;
	}
}





//初始化ADC
void Adc_Init_channel(int channel)
{
	ADC_InitTypeDef ADC_InitStructure;

	ADC_Init_GPIO_channel(channel); //GPIO初始化

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE); //使能ADC1通道时钟

	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	ADC_DeInit(ADC1); //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;					//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;						//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;					//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;				//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;								//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);									//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器

	ADC_Cmd(ADC1, ENABLE); //使能指定的ADC1

	ADC_ResetCalibration(ADC1); //使能复位校准

	while (ADC_GetResetCalibrationStatus(ADC1))
		; //等待复位校准结束

	ADC_StartCalibration(ADC1); //开启AD校准

	while (ADC_GetCalibrationStatus(ADC1))
		; //等待校准结束

	//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能
}




//获得ADC值
//ch:通道值 0~3
unsigned int  Get_ADC_channel(int channel)
{
	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_239Cycles5); //ADC1,ADC通道,采样时间为239.5周期

	ADC_SoftwareStartConvCmd(ADC1, ENABLE); //使能指定的ADC1的软件转换启动功能

	while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
		; //等待转换结束

	return ADC_GetConversionValue(ADC1); //返回最近一次ADC1规则组的转换结果
}
