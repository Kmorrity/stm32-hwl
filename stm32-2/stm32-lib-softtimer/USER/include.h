#ifndef __INCLUDE_H__
#define __INCLUDE_H__


/**************ϵͳ���ķ���  ���鱣�ֿ���**************/
#include "delay.h"   //����ʱ�Ӿ������õ���ʱ����
#include "sys.h"			//�������ã����� gpio��������� ���������ļ�
#include "common.h"  //���ú궨�� �磺�����ֵ ���齻�� �ȡ�����
#include "stdio.h"



/**************���������ļ� ѡ����Ҫ�ģ�ע�Ͳ���Ҫ��***********/

//#include "led.h"  //ledС��
//#include "lcd.h"  //lcdҺ����ʾ��
#include "key.h"  //�������
#include "rc522.h" //rfid������
#include "uart6050.h"  //mpu6050���������ã����˲� GY-25 uart��
#include "oled.h"   //����oled��ȡ����
//#include "ldc.h"  //ldc1314 ����



//#include "STM32_I2C.h"  //ģ��I2C����
#include "usart.h"  //��������
#include "adc.h"     //adc��ȡ����
#include "timer.h"  //��ʱ������
#include "pwm.h"  //��ʱ������
#include "gpio.h"   //gpio ����ģ��
//#include "encoder.h"  //������
#include "ws2812b.h" //WS2812B
#include "dht11.h"  //DHT11
#include "soft_timer.h" //�����ʱ��
#include "hx711.h"  //ѹ��ģ��
#include "ultrasonicwave.h"  //���������
#include "ds18b20.h"  //ds18b20 
#include "hongwaiwendu.h" //�����¶�
#include "scanner.h" //������ ��ά��
#include "tds.h"  //tds�絼�ʲ���ģ��
#include "gps.h"  //GPS ��λ

#include "28byj_48.h"   //�������
#include "max30102.h"

#include "pm25.h"  //pm25

//#include "control.h"

// #include "math.h"    //������ѧת��
//#include "visualscope.h"  //����ʾ����
//#include "pid.h"  //PID ����ģ��
#include "ringbuffer.h"
#include "protocol.h"

#include "string.h"
#include "stdlib.h"


#endif  //__INCLUDE_H__



// c15  -- ws2812  -- oled  SCLK
// c14             -- oled  SDA
// c13  

// B15  -- IN OUT
// B14  -- IN OUT  ---- ws2812b_4
// B13  -- IN OUT  ---- ws2812b_3
// B12  -- IN OUT  ---- ws2812b_2
// B11 -- DHT11
// B10 --BEEP
// B9  --renti
// B8  --voice
// B7  --jidianqi1
// B6 -- jiedianqi2
// B5  --jiedianqi3
// B4  -- huoyan 
// B3
// B2
// B1  -- yali SDA
// B0  -- yali SCLK

// A12  
// A11 -- pwm   Ĭ�ϵڶ����ȼ� ����
// A10 -- pwm   Ĭ�ϵ�һ���ȼ� ����
// A9  -- pwm
// A8  -- pwm
// A7 -- rc522  ---ADC (yudi)
// A6 -- rc522  ---ADC (yanwu)
// A5 -- rc522  ---ADC (guangqiang)  --- zhuodu
// A4  -- rc522  ---ADC (turang)
// A3  ---------------------USART2_RxPin(Ҫ���������ڵ� TX)
// A2  ---------------------USART2_TxPin(Ҫ���������ڵ� RX)
// A1 -- rc522
// A0  ------------ds18b20
