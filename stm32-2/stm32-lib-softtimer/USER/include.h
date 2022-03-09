#ifndef __INCLUDE_H__
#define __INCLUDE_H__


/**************系统核心服务  建议保持开启**************/
#include "delay.h"   //根据时钟晶振配置的延时函数
#include "sys.h"			//基础配置（包括 gpio输入输出简化 及变量名的简化
#include "common.h"  //常用宏定义 如：求绝对值 数组交换 等。。。
#include "stdio.h"



/**************自由配置文件 选择需要的，注释不需要的***********/

//#include "led.h"  //led小灯
//#include "lcd.h"  //lcd液晶显示屏
#include "key.h"  //按键检测
#include "rc522.h" //rfid读卡器
#include "uart6050.h"  //mpu6050陀螺仪配置（带滤波 GY-25 uart）
#include "oled.h"   //四线oled读取配置
//#include "ldc.h"  //ldc1314 配置



//#include "STM32_I2C.h"  //模拟I2C配置
#include "usart.h"  //串口配置
#include "adc.h"     //adc读取配置
#include "timer.h"  //定时器配置
#include "pwm.h"  //定时器配置
#include "gpio.h"   //gpio 配置模板
//#include "encoder.h"  //编码器
#include "ws2812b.h" //WS2812B
#include "dht11.h"  //DHT11
#include "soft_timer.h" //软件定时器
#include "hx711.h"  //压力模块
#include "ultrasonicwave.h"  //超声波测距
#include "ds18b20.h"  //ds18b20 
#include "hongwaiwendu.h" //红外温度
#include "scanner.h" //条形码 二维码
#include "tds.h"  //tds电导率测温模块
#include "gps.h"  //GPS 定位

#include "28byj_48.h"   //步进电机
#include "max30102.h"

#include "pm25.h"  //pm25

//#include "control.h"

// #include "math.h"    //常用数学转换
//#include "visualscope.h"  //虚拟示波器
//#include "pid.h"  //PID 计算模板
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
// A11 -- pwm   默认第二优先级 风扇
// A10 -- pwm   默认第一优先级 风扇
// A9  -- pwm
// A8  -- pwm
// A7 -- rc522  ---ADC (yudi)
// A6 -- rc522  ---ADC (yanwu)
// A5 -- rc522  ---ADC (guangqiang)  --- zhuodu
// A4  -- rc522  ---ADC (turang)
// A3  ---------------------USART2_RxPin(要接其它串口的 TX)
// A2  ---------------------USART2_TxPin(要接其它串口的 RX)
// A1 -- rc522
// A0  ------------ds18b20
