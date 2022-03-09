#ifndef __UltrasonicWave_H
#define	__UltrasonicWave_H

 

#define	TRIG_PORT_ch1      GPIOB		//TRIG       
#define	ECHO_PORT_ch1      GPIOB		//ECHO 
#define	TRIG_PIN_ch1       GPIO_Pin_8   //TRIG       
#define	ECHO_PIN_ch1       GPIO_Pin_7	//ECHO   

#define	TRIG_PORT_ch2      GPIOB		//TRIG       
#define	ECHO_PORT_ch2      GPIOB		//ECHO 
#define	TRIG_PIN_ch2      GPIO_Pin_6   //TRIG       
#define	ECHO_PIN_ch2       GPIO_Pin_5	//ECHO   

#define	TRIG_PORT_ch3      GPIOB		//TRIG       
#define	ECHO_PORT_ch3      GPIOB		//ECHO 
#define	TRIG_PIN_ch3      GPIO_Pin_4   //TRIG       
#define	ECHO_PIN_ch3       GPIO_Pin_3	//ECHO   

#define	TRIG_PORT_ch4      GPIOB		//TRIG       
#define	ECHO_PORT_ch4      GPIOB		//ECHO 
#define	TRIG_PIN_ch4       GPIO_Pin_2   //TRIG       
#define	ECHO_PIN_ch4       GPIO_Pin_1	//ECHO   






void UltrasonicWave_Configuration_channel(int channel);  //��������ʼ�� channel  1-4

float UltrasonicWave_GetDistance_ch1(void);  //��ȡ���� -- ��λ cm
float UltrasonicWave_GetDistance_ch2(void);  //��ȡ���� -- ��λ cm
float UltrasonicWave_GetDistance_ch3(void);  //��ȡ���� -- ��λ cm
float UltrasonicWave_GetDistance_ch4(void);  //��ȡ���� -- ��λ cm



#endif /* __UltrasonicWave_H */

