#ifndef __WS2812B_H
#define __WS2812B_H	

#include <stm32f10x.h>


//#define   Time_D	   400
 
#define nWs 1		// �ж��ٿ�WS2811����


//B-R-G
#define   White        0xFFFFFF  // ��ɫ
#define   Black        0x000000  // ��ɫ ��������
#define   Blue         0xFF0000  // ��ɫ
#define   Red          0x00FF00  // ��ɫ
#define   Green        0x0000FF  // ��ɫ
#define   Gray         0x22ee22


extern void WS_GPIO_Init(void);//WS2811�˿ڳ�ʼ��

extern void WS_Set1(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin,unsigned long dat);

extern unsigned long WsDat_RUN[nWs];
extern unsigned long WsDat[nWs];

//extern void WS_Reset(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);    //��λ
//extern void WS_Set1(GPIO_TypeDef *GPIOx,uint16_t GPIO_PIN,unsigned long dat); //����1���ֽ�

extern void WS_Set_Date(GPIO_TypeDef *GPIOx,uint16_t GPIO_PIN,unsigned char len,unsigned long dat); //
extern void WS_SetAll(GPIO_TypeDef *GPIOx,uint16_t GPIO_PIN);	 //���������ֽ�

///*******/
////�ƴ����Ʒ���
//extern unsigned long ColorToColor(GPIO_TypeDef *GPIOx,uint16_t GPIO_PIN,unsigned long color0, unsigned long color1,unsigned int speed) ;//��ɫ����

//extern void LED_Init(GPIO_TypeDef *GPIOx,uint16_t GPIO_PIN,unsigned long color);                                      //��ʼ���Դ�����	
//extern void RUN_LED(GPIO_TypeDef *GPIOx,uint16_t GPIO_PIN,unsigned long color,unsigned int speed,unsigned char temp); //�����






///////////////////////////////////ws2812b : one light/////////////////////////////////


extern void ws2812b_init(void);

extern void ws2812b_rgb(unsigned char red , unsigned char green , unsigned char blue);

extern void ws2812b_red(unsigned char red );

extern void ws2812b_green(unsigned char green);

extern void ws2812b_blue(unsigned char blue);





extern void ws2812b_init_2(void);

extern void ws2812b_rgb_2(unsigned char red , unsigned char green , unsigned char blue);

extern void ws2812b_red_2(unsigned char red );

extern void ws2812b_green_2(unsigned char green);

extern void ws2812b_blue_2(unsigned char blue);




extern void ws2812b_init_3(void);

extern void ws2812b_rgb_3(unsigned char red , unsigned char green , unsigned char blue);

extern void ws2812b_red_3(unsigned char red );

extern void ws2812b_green_3(unsigned char green);

extern void ws2812b_blue_3(unsigned char blue);



extern void ws2812b_init_4(void);

extern void ws2812b_rgb_4(unsigned char red , unsigned char green , unsigned char blue);

extern void ws2812b_red_4(unsigned char red );

extern void ws2812b_green_4(unsigned char green);

extern void ws2812b_blue_4(unsigned char blue);


	
#endif

