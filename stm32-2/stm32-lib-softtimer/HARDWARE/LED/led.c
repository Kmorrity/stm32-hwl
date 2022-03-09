#include "led.h"

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE, ENABLE);	 //使能PA,PD端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PG.8 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOG, &GPIO_InitStructure);					 //根据设定参数初始化GPIOG.8
 GPIO_SetBits(GPIOG,GPIO_Pin_8);						 //PG.8 输出高

 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz

}


 
