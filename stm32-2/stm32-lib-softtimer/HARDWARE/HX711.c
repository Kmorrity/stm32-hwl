/************************************************************************************
						
*************************************************************************************/
#include "HX711.h"
#include "delay.h"





static unsigned long Weight_calibration = 0;
static long Weight_physical = 0;



//校准参数
//因为不同的传感器特性曲线不是很一致，因此，每一个传感器需要矫正这里这个参数才能使测量值很准确。
//当发现测试出来的重量偏大时，增加该数值。
//如果测试出来的重量偏小时，减小改数值。
//该值可以为小数
#define GapValue 106.5
// #define GapValue 430



void yali_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PF端口时钟

	//HX711_SCK
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB
	
	//HX711_DOUT
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//输入上拉
    GPIO_Init(GPIOB, &GPIO_InitStructure);  
	
	GPIO_SetBits(GPIOB,GPIO_Pin_0);					//初始化设置为0
}



//****************************************************
//读取HX711
//****************************************************
u32 HX711_Read(void)	//增益128
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
    count=count^0x800000;//第25个脉冲下降沿来时，转换数据
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

