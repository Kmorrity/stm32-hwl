#ifndef __SENSOR_HAL_H__
#define __SENSOR_HAL_H__

#include "protocol.h"



//-----------------------------
//传感器变量

extern unsigned int GlobalVar_sensor_distance ;
extern unsigned int GlobalVar_sensor_distance_2;
extern unsigned int GlobalVar_sensor_DO1 ;
extern unsigned int GlobalVar_sensor_huoyan ;
extern unsigned int GlobalVar_sensor_DO2 ;
extern unsigned int GlobalVar_sensor_DO3 ;
extern unsigned int GlobalVar_sensor_DO4 ;
extern unsigned int GlobalVar_sensor_DO5 ;
extern unsigned int GlobalVar_sensor_AO1 ;
extern unsigned int GlobalVar_sensor_AO2 ;

extern unsigned int GlobalVar_sensor_TDS_wendu ;
extern unsigned int GlobalVar_sensor_TDS ;
extern unsigned int GlobalVar_sensor_dht11_wendu ;
extern unsigned int GlobalVar_sensor_dht11_shidu ;
extern unsigned int GlobalVar_sensor_ds18b20_wendu ;
extern unsigned int GlobalVar_sensor_heart ;
extern unsigned int GlobalVar_sensor_RenTi ;
extern unsigned int GlobalVar_sensor_RenTi_2 ;
extern unsigned int GlobalVar_sensor_guangqiang ;
extern unsigned int GlobalVar_sensor_shuiwei ;
extern unsigned int GlobalVar_sensor_turang ;
extern unsigned int GlobalVar_sensor_jiguangceju ;
extern unsigned int GlobalVar_sensor_dianya ;
extern unsigned int GlobalVar_sensor_dianliu ;
extern unsigned int GlobalVar_sensor_xinlv ;
extern unsigned int GlobalVar_sensor_xueyang ;
extern unsigned int GlobalVar_sensor_PulseSpeed ;
extern unsigned int GlobalVar_sensor_yali ;
extern unsigned int GlobalVar_sensor_voice ;
extern unsigned int GlobalVar_sensor_yanwu ;
extern unsigned int GlobalVar_sensor_yanwu_2 ;
extern unsigned int GlobalVar_sensor_MQ1 ;
extern unsigned int GlobalVar_sensor_MQ2 ;
extern unsigned int GlobalVar_sensor_ziwaixian ;
extern unsigned int GlobalVar_sensor_yudi ;
extern unsigned int GlobalVar_sensor_zhuodu ;
extern unsigned int GlobalVar_sensor_ph ;
extern float  GlobalVar_sensor_ph_float ;
extern int GlobalVar_sensor_hongwai_wendu ;
extern int GlobalVar_sensor_pm25;
extern unsigned int GlobalVar_sensor_light;
extern unsigned int GlobalVar_sensor_zhendong_DO ;
extern int GlobalVar_sensor_6050_x ;
extern int GlobalVar_sensor_6050_y ;
extern int GlobalVar_sensor_6050_z ;
extern int GlobalVar_sensor_max30102_xinlv ;
extern int GlobalVar_sensor_max30102_xueyang ;
extern unsigned int GlobalVar_sensor_hongwai_duiguan;
extern unsigned char GlobalVar_sensor_key_press_1;
extern unsigned char GlobalVar_sensor_key_vlaue_1;
extern unsigned char GlobalVar_sensor_key_press_2;
extern unsigned char GlobalVar_sensor_key_vlaue_2;
extern unsigned int GlobalVar_sensor_online_response;



//-----------------------------
//自动调节变量

extern unsigned char GlobalVar_flag_auto_adjust_tds ;
extern unsigned char GlobalVar_flag_auto_adjust_wendu ;
extern unsigned char GlobalVar_flag_auto_adjust_shidu ;
extern unsigned char GlobalVar_flag_auto_adjust_yanwu ;
extern unsigned char GlobalVar_flag_auto_adjust_yanwu_2 ;
extern unsigned char GlobalVar_flag_auto_adjust_MQ1 ;
extern unsigned char GlobalVar_flag_auto_adjust_MQ2 ;
extern unsigned char GlobalVar_flag_auto_adjust_ziwaixian ;
extern unsigned char GlobalVar_flag_auto_adjust_renti ;
extern unsigned char GlobalVar_flag_auto_adjust_renti_2 ;
extern unsigned char GlobalVar_flag_auto_adjust_guangqiang ;
extern unsigned char GlobalVar_flag_auto_adjust_turang ;
extern unsigned char GlobalVar_flag_auto_adjust_shuiwei ;
extern unsigned char GlobalVar_flag_auto_adjust_dianliu ;
extern unsigned char GlobalVar_flag_auto_adjust_dianya ;
extern unsigned char GlobalVar_flag_auto_adjust_huoyan ;
extern unsigned char GlobalVar_flag_auto_adjust_zhendong ;
extern unsigned char GlobalVar_flag_auto_adjust_voice ;
extern unsigned char GlobalVar_flag_auto_adjust_yudi ;
extern unsigned char GlobalVar_flag_auto_adjust_yali ;
extern unsigned char GlobalVar_flag_auto_adjust_zhuodu ;
extern unsigned int GlobalVar_flag_auto_adjust ;
extern unsigned int GlobalVar_flag_key_pressed ;
extern unsigned int GlobalVar_flag_max30102_inited ;
extern unsigned char GlobalVar_flag_auto_adjust_distance;
extern unsigned char GlobalVar_flag_auto_adjust_hongwai_duiguan ;
extern unsigned char GlobalVar_flag_scanner_inited ;
extern unsigned char GlobalVar_flag_uart6050_inited ;
extern unsigned char GlobalVar_flag_gps_inited ;
extern unsigned char GlobalVar_flag_gps_parse_success ;
extern unsigned char GlobalVar_flag_hongwaiwendu_inited ;
extern unsigned char GlobalVar_flag_pm25_inited ;
extern unsigned char GlobalVar_flag_tds_inited ;
extern unsigned char GlobalVar_flag_key_inited ;
extern unsigned char GlobalVar_flag_time_inited ;
extern unsigned char GlobalVar_flag_is_inited_zhendong_DO ;

//-----------------------------
//阈值变量
extern unsigned int GlobalVar_Threshold_alert_guangqiang_max ;
extern unsigned int GlobalVar_Threshold_alert_guangqiang_min ;
extern unsigned int GlobalVar_Threshold_alert_guangqiang ;
extern unsigned int GlobalVar_Threshold_alert_wendu ;
extern unsigned int GlobalVar_Threshold_alert_wendu_max ;
extern unsigned int GlobalVar_Threshold_alert_shidu ;
extern unsigned int GlobalVar_Threshold_alert_shidu_max ;
extern unsigned int GlobalVar_Threshold_alert_tds ;
extern unsigned int GlobalVar_Threshold_alert_yanwu ;
extern unsigned int GlobalVar_Threshold_alert_yanwu_2 ;
extern unsigned int GlobalVar_Threshold_alert_MQ1 ;
extern unsigned int GlobalVar_Threshold_alert_MQ2 ;
extern unsigned int GlobalVar_Threshold_alert_ziwaixian ;
extern unsigned int GlobalVar_Threshold_alert_turang ;
extern unsigned int GlobalVar_Threshold_alert_shuiwei ;
extern unsigned int GlobalVar_Threshold_alert_dianya ;
extern unsigned int GlobalVar_Threshold_alert_dianliu;
extern unsigned int GlobalVar_Threshold_alert_zhendong ;
extern unsigned int GlobalVar_Threshold_alert_zhendong_x;
extern unsigned int GlobalVar_Threshold_alert_zhendong_y;
extern unsigned int GlobalVar_Threshold_alert_zhendong_z;
extern unsigned int GlobalVar_Threshold_alert_yudi ;
extern unsigned int GlobalVar_Threshold_alert_yali ;
extern unsigned int GlobalVar_Threshold_alert_zhuodu;
extern unsigned int GlobalVar_Threshold_light_min;
extern unsigned int GlobalVar_Threshold_alert_distance;
extern unsigned int GlobalVar_Threshold_alert_ph ;

extern unsigned int GlobalVar_Threshold_RC522;

extern unsigned int GlobalVar_sensor_zhuangtai1;
extern unsigned int GlobalVar_sensor_zhuangtai2;


extern char GlobalVar_phone_number[] ;
extern char GlobalVar_gps_x[] ;
extern char GlobalVar_gps_y[] ;



void sensor_hal_protocol_init(struct protocol_send *protocol);

void GetSensor_Time(char *name); //.....
void GetSensor_Guangqiang(char *name);//guangqiang AO5
void GetSensor_Yanwu(char *name);//yanwu AO6
void GetSensor_Yanwu_2(char *name);//yanwu AO0
void GetSensor_MQ1(char *name); //A06
void GetSensor_MQ2(char *name); // A00
void GetSensor_Ziwaixian(char *name); //ziwaixian  AO6
void GetSensor_Yudi(char *name);//yudi  AO1
void GetSensor_Shuiwei(char *name); //shuwei AO1
void GetSensor_Turang(char *name);//turang  AO4
void GetSensor_Dianliu(char *name); //dianliu  A1   100mA
void GetSensor_Dianya(char *name); //dianya  A0     100mV
void GetSensor_AO1(char *name);//AO1 --- A1
void GetSensor_DO1(char *name);//B12
void GetSensor_DO2(char *name);//B13
void GetSensor_DO3(char *name);//B14
void GetSensor_hongwai_duiguan(char *name);//B13
void GetSensor_Zhuodu(char *name);//A7
void GetSensor_PH(char *name);//A6
void GetSensor_PH_float(char *name);//A6
void GetSensor_Renti(char *name); //B9
void GetSensor_Renti_2(char *name); //B12
void GetSensor_Voice(char *name); //B8
void GetSensor_Huoyan(char *name); //B4
void GetSensor_Key(char *name);//A8
void GetSensor_Key_2(char *name);//c13
void GetSensor_Dht11(char *name_wendu, char *name_shidu);//B11
void GetSensor_Chaoshengbo(char *name);//B4--TRIG   B3---ECHO  
void GetSensor_Chaoshengbo_2(char *name);//B4--TRIG   B3---ECHO  
void GetSensor_Ds18b20(char *name); //A0
void GetSensor_zhuangtai(char *name,int value);

unsigned char GetSensor_Rc522(char *name); //RST-A1  MISO-A4  MOSI-A5 SCK-A6 SDA-A7
void GetSensor_Yali(char *name); //SCLK-B0    SOUT-B1
void GetSensor_Xueya(char *name); //SCLK-B0    SOUT-B1
void GetSensor_GPS(char *gps_x, char *gps_y); //GPS
void GetSensor_hongwai_wendu(char *name); //串口A9-TX   A10-RX
void GetSensor_pm25(char *name); //串口A9-TX   A10-RX
void GetSensor_uart6050(char *x , char *y, char *z); //串口A9-TX   A10-RX
void GetSensor_tds(char *tds ,char * wendu);//串口A9-TX   A10-RX
void GetSensor_max30102(char *xinlv , char *xueyang); // SCL-B7  SDA-B8  INT-B9
void GetSensor_IdValue_int(char *name , int value);//直接上传IDvalue  value为int
void GetSensor_IdValue_str(char *name , char * value);//直接上传IDvalue  value为string
void GetSensor_Zhendong_DO_high(char *name); //震动DO接口数据  鼓型震动传感器    声音  ---默认用这个
void GetSensor_Zhendong_DO_low(char *name); //震动DO接口数据   棒型振动传感器   


void SetSensor_Beep(unsigned char value); //B10
void SetSensor_DO1(unsigned char value);//B12
void SetSensor_DO2(unsigned char value);//B13
void SetSensor_DO3(unsigned char value);//B14
void SetSensor_Jidianqi(unsigned char value); //B7
void SetSensor_Jidianqi_2(unsigned char value); //B6
void SetSensor_Jidianqi_3(unsigned char value); //B5
void SetSensor_Ws2812b_rgb(unsigned char red, unsigned char green, unsigned char blue); //C15
void SetSensor_Ws2812b_red(unsigned char red); //C15
void SetSensor_Ws2812b_green(unsigned char green); //C15
void SetSensor_Ws2812b_blue(unsigned char blue); //C15
void SetSensor_Ws2812b_rgb_2(unsigned char red, unsigned char green, unsigned char blue); //B12
void SetSensor_Ws2812b_red_2(unsigned char red);//B12
void SetSensor_Ws2812b_green_2(unsigned char green);//B12
void SetSensor_Ws2812b_blue_2(unsigned char blue);//B12
void SetSensor_Ws2812b_rgb_3(unsigned char red, unsigned char green, unsigned char blue); ////B13
void SetSensor_Ws2812b_red_3(unsigned char red);//B13
void SetSensor_Ws2812b_green_3(unsigned char green);//B13
void SetSensor_Ws2812b_blue_3(unsigned char blue);//B13
void SetSensor_Ws2812b_rgb_4(unsigned char red, unsigned char green, unsigned char blue); //B14
void SetSensor_Ws2812b_red_4(unsigned char red);//B14
void SetSensor_Ws2812b_green_4(unsigned char green);//B14
void SetSensor_Ws2812b_blue_4(unsigned char blue);//B14
void SetSensor_fan(unsigned char value);//B14
void SetSensor_PWM(unsigned char value);////A11    value[ 0 - 100 ]
// void SetSensor_PWM_2(unsigned char value);  //A8   value[ 0 - 100 ]
void SetSensor_OLED_Sring(unsigned char x, unsigned char y,unsigned char *buff ,unsigned char Char_Size);  //C15-SCLK   C14-SDA
void SetSensor_OLED_Chinese(unsigned char x, unsigned char y, int index);
void SetSensor_phone_number(const char * number);//设置号码，短信号码
void SetSensor_Sms(char * sms); //发短信  number:13000000000   sms:短信内容
void SetSensor_duoji(unsigned int value); //A8     value 0-180
void SetSensor_time_update(const char * value); //北京时间同步
void SetSensor_time_OLED_show_1s(void); //北京时间OLED显示

void SetSensor_28byj_48(unsigned int value, unsigned int position);


void process_zhendong_DO_100ms(void);



#endif  
	 

