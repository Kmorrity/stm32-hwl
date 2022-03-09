
#include "ws2812b.h"
	
unsigned long WsDat[nWs];   //�Դ�
unsigned long WsDat_RUN[nWs];   //��ˮ���Դ�


/**************************************************
* IO��ʼ������ֲʱ���޸ģ�
***************************************************/
void WS_GPIO_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;	

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );	  					//�˿�ʱ�ӣ�ʹ��																			
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13	;	// PIN
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 							// �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							// IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);										// �˿����ã������趨������ʼ�� 
		
}





void WS_GPIO_Init_2()
{
	GPIO_InitTypeDef  GPIO_InitStructure;	

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );	  					//�˿�ʱ�ӣ�ʹ��																			
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12	;	// PIN
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 							// �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							// IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);										// �˿����ã������趨������ʼ�� 
	
}




void WS_GPIO_Init_3()
{
	GPIO_InitTypeDef  GPIO_InitStructure;	

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );	  					//�˿�ʱ�ӣ�ʹ��																			
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13	;	// PIN
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 							// �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							// IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);										// �˿����ã������趨������ʼ�� 
	
}






void WS_GPIO_Init_4()
{
	GPIO_InitTypeDef  GPIO_InitStructure;	

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );	  					//�˿�ʱ�ӣ�ʹ��																			
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14	;	// PIN
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 							// �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							// IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);										// �˿����ã������趨������ʼ�� 
	
}



/**************************
* �ڲ���ʱ
***************************/

void WS_delay_us(__IO u32 nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
} 

void WS_delay2us()
{
	unsigned char i;
	for(i=0; i<11; i++);
}

void WS_delay05us()
{
//	unsigned char i;
//	for(i=0; i<1; i++);
}

void WS_delay_ms(uint32_t nms)
{	
	while(nms--)
	{
	  WS_delay_us(1670);	//��ͨ��ʽ��ʱ 		
	}
}


/***************************
* ����һ����
****************************/
void TX0(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)    	// ����0	
{
	GPIO_SetBits(GPIOx, GPIO_Pin); 
    WS_delay05us();
	GPIO_ResetBits(GPIOx, GPIO_Pin);
	WS_delay2us();
} 
void TX1(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin) 	  // ����1	
{ 							 	
	GPIO_SetBits(GPIOx, GPIO_Pin); 
	WS_delay2us();
	GPIO_ResetBits(GPIOx, GPIO_Pin);
	WS_delay05us();
} 
void WS_Reset(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)   //��λ
{
	GPIO_ResetBits(GPIOx, GPIO_Pin); 
	WS_delay_us(50); 
	GPIO_SetBits(GPIOx, GPIO_Pin);
	GPIO_ResetBits(GPIOx, GPIO_Pin); 
}

/************************************************
* ��������
*************************************************/
void WS_Set1(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin,unsigned long dat)
{
	unsigned char i;	
	for(i=0; i<24; i++)
	{
		if(0x800000 == (dat & 0x800000) )	
			TX1(GPIOx,GPIO_Pin);
		else								
			TX0(GPIOx,GPIO_Pin);
		dat<<=1;        //����һλ
	}
}


void WS_Set_Date(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin,unsigned char len,unsigned long dat) // ȫ������ͬ��������
{
   unsigned char i;
   for(i = 0; i <len; i++)
   {
		WS_Set1(GPIOx,GPIO_Pin,dat);	
   }
	WS_Reset(GPIOx,GPIO_Pin);
}


// void WS_SetAll(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)   //���������ֽ�
// {
// 	unsigned char i;
	
// 	for(i=0;i<nWs;i++)
// 	{
// 		WS_Set1(GPIOx,GPIO_Pin,WsDat_RUN[i]);  
// 	}
// 	WS_Reset(GPIOx,GPIO_Pin);
// 	WS_delay_ms(500);	
// }



///**************************��ɫ���亯��***************************/
///*
//����ʼ��ɫ---������ɫ
//*/
//unsigned char abs0(int num)//�����ֵ
//{
//	if(num>0) return num;
//	
//	num = -num;
//	return (unsigned char) num;
//}

//unsigned long ColorToColor(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin,unsigned long color0, unsigned long color1,unsigned int speed)  
//{
//	unsigned char Red0, Green0, Blue0;  // ��ʼ��ԭɫ
//	unsigned char Red1, Green1, Blue1;  // �����ԭɫ
//	int			  RedMinus, GreenMinus, BlueMinus;	// ��ɫ�color1 - color0��
//	unsigned char NStep; 							// ��Ҫ����
//	float		  RedStep, GreenStep, BlueStep;		// ��ɫ����ֵ
//	unsigned long color;							// ���ɫ
//	unsigned char i;
//	
//	// �� �� �� ��ԭɫ�ֽ�
//	Red0   = color0>>8;
//	Green0 = color0>>16;
//	Blue0  = color0;
//	
//	Red1   = color1>>8;
//	Green1 = color1>>16;
//	Blue1  = color1;
//	
//	// ������Ҫ���ٲ���ȡ��ֵ�����ֵ��
//	RedMinus   = Red1 - Red0; 
//	GreenMinus = Green1 - Green0; 
//	BlueMinus  = Blue1 - Blue0;
//	
//	//�ж���������ֵ��С����a>bΪ�棬��=a������=b
//	NStep = ( abs0(RedMinus) > abs0(GreenMinus) ) ? abs0(RedMinus):abs0(GreenMinus); 
//	NStep = ( NStep > abs0(BlueMinus) ) ? NStep:abs0(BlueMinus);
//	
//	// �������ɫ����ֵ
//	RedStep   = (float)RedMinus   / NStep;
//	GreenStep = (float)GreenMinus / NStep;
//	BlueStep  = (float)BlueMinus  / NStep;
//	
//	// ���俪ʼ
//	for(i=0; i<NStep; i++)
//	{
//		Red1   = Red0   + (int)(RedStep   * i);
//		Green1 = Green0 + (int)(GreenStep * i);
//		Blue1  = Blue0  + (int)(BlueStep  * i);
//		
//		color  = Green1<<16 | Red1<<8 | Blue1; 	// �ϳ�  �̺���
//		
//		WS_Set_Date(GPIOx,GPIO_Pin,nWs,color); //������ɫ�����еƴ�ͬɫ
//		WS_delay_ms(speed);
//	}
//	return color;
//}


///*************�����****************
//000000000000000000000000
//111100000000000000000000
//000011110000000000000000
//000000001111000000000000
//111100000000111100000000
//000011110000000011110000
//***********************************/
//void LED_Init(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin,unsigned long color) //��ʼ���Դ�����
//{
//	unsigned char i;
//	for(i=0;i<50;i++)
//		WsDat_RUN[i]=color;
//	WS_SetAll(GPIOx,GPIO_Pin);
//}

////��ڲ���     color----speed----temp
////            ��ʾ��ɫ--��ˮ�ٶ�--�������
//void RUN_LED(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin,unsigned long color,unsigned int speed,unsigned char temp)//�����
//{
//	unsigned char i,j;
//	for(j=0;j<(nWs-1);j++)
//	{
//		for(i=nWs;i>0;i--)
//			WsDat_RUN[i] = WsDat_RUN[i-1];
//		
//		if(j%temp == 0)
//			WsDat_RUN[0] = color;		
//		else
//			WsDat_RUN[0] = Black;
//		
//		//WS_Set_Date(GPIO_PIN,nWs,WsDat_RUN[i]); 
//		WS_SetAll(GPIOx,GPIO_Pin);
//		WS_delay_ms(speed);
//	}
//}



static unsigned char rgb[3];
static unsigned char rgb_2[3];
static unsigned char rgb_3[3];
static unsigned char rgb_4[3];

void ws2812b_init(void)
{
		WS_GPIO_Init();
}






void ws2812b_rgb(unsigned char red , unsigned char green , unsigned char blue)
{
    unsigned long temp_data=0;
	
	rgb[0] = red;
  rgb[1] = green;
  rgb[2] = blue;

    temp_data &= ~(0xff<<16);
    temp_data |= (green<<16);

    temp_data &= ~(0xff<<8);
    temp_data |= (red<<8);

    temp_data &= ~(0xff<<0);
    temp_data |= (blue<<0);
    

    WS_Set1(GPIOC, GPIO_Pin_13,temp_data);
}







void ws2812b_red(unsigned char red )
{
  ws2812b_rgb(red, rgb[1], rgb[2]);
}

void ws2812b_green(unsigned char green)
{
  ws2812b_rgb(rgb[0], green, rgb[2]);
}

void ws2812b_blue(unsigned char blue)
{
  ws2812b_rgb(rgb[0], rgb[1], blue);
}







void ws2812b_init_2(void)
{
		WS_GPIO_Init_2();
}


void ws2812b_rgb_2(unsigned char red , unsigned char green , unsigned char blue)
{
    unsigned long temp_data=0;
	
	rgb_2[0] = red;
    rgb_2[1] = green;
    rgb_2[2] = blue;

    temp_data &= ~(0xff<<16);
    temp_data |= (green<<16);

    temp_data &= ~(0xff<<8);
    temp_data |= (red<<8);

    temp_data &= ~(0xff<<0);
    temp_data |= (blue<<0);
    

    WS_Set1(GPIOB, GPIO_Pin_12,temp_data);
}



void ws2812b_red_2(unsigned char red )
{
  ws2812b_rgb_2(red, rgb_2[1], rgb_2[2]);
}

void ws2812b_green_2(unsigned char green)
{
  ws2812b_rgb_2(rgb_2[0], green, rgb_2[2]);
}

void ws2812b_blue_2(unsigned char blue)
{
  ws2812b_rgb_2(rgb_2[0], rgb_2[1], blue);
}





















void ws2812b_init_3(void)
{
		WS_GPIO_Init_3();
}


void ws2812b_rgb_3(unsigned char red , unsigned char green , unsigned char blue)
{
    unsigned long temp_data=0;
	
	rgb_3[0] = red;
    rgb_3[1] = green;
    rgb_3[2] = blue;

    temp_data &= ~(0xff<<16);
    temp_data |= (green<<16);

    temp_data &= ~(0xff<<8);
    temp_data |= (red<<8);

    temp_data &= ~(0xff<<0);
    temp_data |= (blue<<0);
    

    WS_Set1(GPIOB, GPIO_Pin_13,temp_data);
}



void ws2812b_red_3(unsigned char red )
{
  ws2812b_rgb_3(red, rgb_3[1], rgb_3[2]);
}

void ws2812b_green_3(unsigned char green)
{
  ws2812b_rgb_3(rgb_3[0], green, rgb_3[2]);
}

void ws2812b_blue_3(unsigned char blue)
{
  ws2812b_rgb_3(rgb_3[0], rgb_3[1], blue);
}








void ws2812b_init_4(void)
{
		WS_GPIO_Init_4();
}


void ws2812b_rgb_4(unsigned char red , unsigned char green , unsigned char blue)
{
    unsigned long temp_data=0;
	
	rgb_4[0] = red;
    rgb_4[1] = green;
    rgb_4[2] = blue;

    temp_data &= ~(0xff<<16);
    temp_data |= (green<<16);

    temp_data &= ~(0xff<<8);
    temp_data |= (red<<8);

    temp_data &= ~(0xff<<0);
    temp_data |= (blue<<0);
    

    WS_Set1(GPIOB, GPIO_Pin_14,temp_data);
}



void ws2812b_red_4(unsigned char red )
{
  ws2812b_rgb_4(red, rgb_4[1], rgb_4[2]);
}

void ws2812b_green_4(unsigned char green)
{
  ws2812b_rgb_4(rgb_4[0], green, rgb_4[2]);
}

void ws2812b_blue_4(unsigned char blue)
{
  ws2812b_rgb_4(rgb_4[0], rgb_4[1], blue);
}





