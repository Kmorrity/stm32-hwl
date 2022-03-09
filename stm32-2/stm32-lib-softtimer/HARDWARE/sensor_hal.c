
#include "sensor_hal.h"
#include "protocol.h"

#include "include.h"

static struct protocol_send *sensor_protocol;

//-----------------------------
//传感器变量

unsigned int GlobalVar_sensor_distance = 0;
unsigned int GlobalVar_sensor_distance_2 = 0;
unsigned int GlobalVar_sensor_DO1 = 0;
unsigned int GlobalVar_sensor_huoyan = 0;
unsigned int GlobalVar_sensor_hongwai_duiguan = 0;
unsigned int GlobalVar_sensor_DO2 = 0;
unsigned int GlobalVar_sensor_DO3 = 0;
unsigned int GlobalVar_sensor_DO4 = 0;
unsigned int GlobalVar_sensor_DO5 = 0;
unsigned int GlobalVar_sensor_AO1 = 0;
unsigned int GlobalVar_sensor_AO2 = 0;

unsigned int GlobalVar_sensor_TDS_wendu = 0;
unsigned int GlobalVar_sensor_TDS = 0;
unsigned int GlobalVar_sensor_dht11_wendu = 0;
unsigned int GlobalVar_sensor_dht11_shidu = 0;
unsigned int GlobalVar_sensor_ds18b20_wendu = 0;
unsigned int GlobalVar_sensor_heart = 0;
unsigned int GlobalVar_sensor_RenTi = 0;
unsigned int GlobalVar_sensor_RenTi_2 = 0;
unsigned int GlobalVar_sensor_guangqiang = 0;
unsigned int GlobalVar_sensor_shuiwei = 0;
unsigned int GlobalVar_sensor_turang = 0;
unsigned int GlobalVar_sensor_jiguangceju = 0;
unsigned int GlobalVar_sensor_dianya = 0;
unsigned int GlobalVar_sensor_dianliu = 0;
unsigned int GlobalVar_sensor_xinlv = 0;
unsigned int GlobalVar_sensor_xueyang = 0;
unsigned int GlobalVar_sensor_PulseSpeed = 0;
unsigned int GlobalVar_sensor_yali = 0;
unsigned int GlobalVar_sensor_voice = 0;
unsigned int GlobalVar_sensor_yanwu = 0;
unsigned int GlobalVar_sensor_yanwu_2 = 0;
unsigned int GlobalVar_sensor_MQ1 = 0;
unsigned int GlobalVar_sensor_MQ2 = 0;
unsigned int GlobalVar_sensor_yudi = 0;
unsigned int GlobalVar_sensor_zhuodu = 0;
unsigned int GlobalVar_sensor_ph = 0;
float GlobalVar_sensor_ph_float = 0;
int GlobalVar_sensor_hongwai_wendu = 0;
int GlobalVar_sensor_pm25 = 0;
unsigned int GlobalVar_sensor_light = 40;
unsigned int GlobalVar_sensor_zhendong_DO = 0;
int GlobalVar_sensor_6050_x = 0;
int GlobalVar_sensor_6050_y = 0;
int GlobalVar_sensor_6050_z = 0;
int GlobalVar_sensor_max30102_xinlv = 0;
int GlobalVar_sensor_max30102_xueyang = 0;
unsigned int GlobalVar_sensor_ziwaixian = 0;
unsigned char GlobalVar_sensor_key_press_1 = 0;
unsigned char GlobalVar_sensor_key_vlaue_1 = 0;
unsigned char GlobalVar_sensor_key_press_2 = 0;
unsigned char GlobalVar_sensor_key_vlaue_2 = 0;
unsigned int GlobalVar_sensor_online_response = 0;


//-----------------------------
//自动调节变量

unsigned char GlobalVar_flag_auto_adjust_tds = 0;
unsigned char GlobalVar_flag_auto_adjust_wendu = 0;
unsigned char GlobalVar_flag_auto_adjust_shidu = 0;
unsigned char GlobalVar_flag_auto_adjust_yanwu = 0;
unsigned char GlobalVar_flag_auto_adjust_yanwu_2 = 0;
unsigned char GlobalVar_flag_auto_adjust_MQ1 = 0;
unsigned char GlobalVar_flag_auto_adjust_MQ2 = 0;
unsigned char GlobalVar_flag_auto_adjust_ziwaixian = 0;
unsigned char GlobalVar_flag_auto_adjust_renti = 0;
unsigned char GlobalVar_flag_auto_adjust_guangqiang = 0;
unsigned char GlobalVar_flag_auto_adjust_turang = 0;
unsigned char GlobalVar_flag_auto_adjust_shuiwei = 0;
unsigned char GlobalVar_flag_auto_adjust_dianliu = 0;
unsigned char GlobalVar_flag_auto_adjust_dianya = 0;
unsigned char GlobalVar_flag_auto_adjust_huoyan = 0;
unsigned char GlobalVar_flag_auto_adjust_zhendong = 0;
unsigned char GlobalVar_flag_auto_adjust_voice = 0;
unsigned char GlobalVar_flag_auto_adjust_yudi = 0;
unsigned char GlobalVar_flag_auto_adjust_yali = 0;
unsigned char GlobalVar_flag_auto_adjust_zhuodu = 0;
unsigned char GlobalVar_flag_auto_adjust_ph = 0;
unsigned int GlobalVar_flag_auto_adjust = 0;
unsigned int GlobalVar_flag_max30102_inited = 0;
unsigned char GlobalVar_flag_auto_adjust_distance = 0;
unsigned char GlobalVar_flag_auto_adjust_hongwai_duiguan = 0;
unsigned char GlobalVar_flag_scanner_inited = 0;
unsigned char GlobalVar_flag_uart6050_inited = 0;
unsigned char GlobalVar_flag_gps_inited = 0;
unsigned char GlobalVar_flag_gps_parse_success=0;
unsigned char GlobalVar_flag_hongwaiwendu_inited = 0;
unsigned char GlobalVar_flag_pm25_inited = 0;

unsigned char GlobalVar_flag_tds_inited = 0;
unsigned char GlobalVar_flag_key_inited = 0;
unsigned char GlobalVar_flag_time_inited = 0;
unsigned char GlobalVar_flag_is_inited_zhendong_DO = 0;


//-----------------------------
//阈值变量
unsigned int GlobalVar_Threshold_alert_guangqiang_max = 65;
unsigned int GlobalVar_Threshold_alert_guangqiang_min = 30;
unsigned int GlobalVar_Threshold_alert_guangqiang = 28;
unsigned int GlobalVar_Threshold_alert_wendu = 28;
unsigned int GlobalVar_Threshold_alert_wendu_max = 28;
unsigned int GlobalVar_Threshold_alert_shidu = 60;
unsigned int GlobalVar_Threshold_alert_shidu_max = 60;
unsigned int GlobalVar_Threshold_alert_tds = 50;
unsigned int GlobalVar_Threshold_alert_yanwu = 30;
unsigned int GlobalVar_Threshold_alert_yanwu_2 = 30;
unsigned int GlobalVar_Threshold_alert_MQ1 = 30;
unsigned int GlobalVar_Threshold_alert_MQ2 = 30;
unsigned int GlobalVar_Threshold_alert_ziwaixian = 30;
unsigned int GlobalVar_Threshold_alert_turang = 30;
unsigned int GlobalVar_Threshold_alert_shuiwei = 30;
unsigned int GlobalVar_Threshold_alert_dianya = 80;
unsigned int GlobalVar_Threshold_alert_dianliu = 8;
unsigned int GlobalVar_Threshold_alert_zhendong = 100;
unsigned int GlobalVar_Threshold_alert_zhendong_x = 100;
unsigned int GlobalVar_Threshold_alert_zhendong_y = 100;
unsigned int GlobalVar_Threshold_alert_zhendong_z = 100;
unsigned int GlobalVar_Threshold_alert_yudi = 30;
unsigned int GlobalVar_Threshold_alert_yali = 1000;
unsigned int GlobalVar_Threshold_alert_zhuodu = 50;
unsigned int GlobalVar_Threshold_alert_ph = 5;
unsigned int GlobalVar_Threshold_light_min = 40;
unsigned int GlobalVar_Threshold_alert_distance = 15;

unsigned int GlobalVar_Threshold_RC522 = 0;

unsigned int GlobalVar_sensor_zhuangtai1= 0;
unsigned int GlobalVar_sensor_zhuangtai2= 0;

//---------------------------------
char GlobalVar_phone_number[13] = {"13007151200"};
char GlobalVar_gps_x[15] ;
char GlobalVar_gps_y[15] ;
char time_current_buffer[21] = {"2021-4-11 12:22:21"};
unsigned int zhendong_buffer[20];
//--------------------------------

// void process_zhendong_AO_100ms()
// {

//   static unsigned int index = 0;

//   zhendong_buffer[index++] = Sensor_port_Get_AO2();

//   if (index >= (sizeof(zhendong_buffer)/sizeof(zhendong_buffer[0])))
//     index = 0;
// }


void process_zhendong_DO_100ms(void)
{

    static unsigned int index = 0;

    zhendong_buffer[index++] = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);

    if (index >= (sizeof(zhendong_buffer) / sizeof(zhendong_buffer[0])))
        index = 0;
}

void GetSensor_Zhendong_DO_high(char *name)
{
    GPIO_InitTypeDef GPIO_InitStructure;
 
    unsigned char index = 0;
 

    static char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PB端口时钟

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;        // 端口配置
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     //设置成上拉输入
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO口速度为50MHz
        GPIO_Init(GPIOB, &GPIO_InitStructure);            //根据设定参数初始化GPIOB13
        GPIO_ResetBits(GPIOB, GPIO_Pin_13);               // 输出低

        GlobalVar_flag_is_inited_zhendong_DO = 1;
    }

    GlobalVar_sensor_zhendong_DO = 0;

    for (index = 0; index < (sizeof(zhendong_buffer) / sizeof(zhendong_buffer[0])); index++)
    {
        if (zhendong_buffer[index] > 0)
        {
            GlobalVar_sensor_zhendong_DO = 1;
            break;
        }
    }

    protocol_send_IdValue_int(sensor_protocol, name, GlobalVar_sensor_zhendong_DO);
}



void GetSensor_Zhendong_DO_low(char *name)
{
    GPIO_InitTypeDef GPIO_InitStructure;
 
    unsigned char index = 0;
 

    static char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PB端口时钟

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;        // 端口配置
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     //设置成上拉输入
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO口速度为50MHz
        GPIO_Init(GPIOB, &GPIO_InitStructure);            //根据设定参数初始化GPIOB13
        GPIO_ResetBits(GPIOB, GPIO_Pin_13);               // 输出低

        GlobalVar_flag_is_inited_zhendong_DO = 1;
    }

    GlobalVar_sensor_zhendong_DO = 0;

    for (index = 0; index < (sizeof(zhendong_buffer) / sizeof(zhendong_buffer[0])); index++)
    {
        if (zhendong_buffer[index] ==0 )
        {
            GlobalVar_sensor_zhendong_DO = 1;
            break;
        }
    }

    protocol_send_IdValue_int(sensor_protocol, name, GlobalVar_sensor_zhendong_DO);
}




 

void sensor_hal_protocol_init(struct protocol_send *protocol)
{
    sensor_protocol = protocol;
}

//guangqiang AO5
void GetSensor_Guangqiang(char *name)
{
    int value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        Adc_Init_channel(5);
    }

    value = Get_ADC_channel(5); //channel 5
    value = value / 32;

    if (value > 100)
        value = 100;

    value = 100 - value;
    value = value - 40;

    if (value < 0)
        value = 0;

    protocol_send_IdValue_int(sensor_protocol, name, value);

    GlobalVar_sensor_guangqiang = value;
}

//guangqiang AO6
void GetSensor_Yanwu(char *name)
{
    unsigned int value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        Adc_Init_channel(6);
    }

    value = Get_ADC_channel(6); //channel and repeat times
    value = value / 32;

    protocol_send_IdValue_int(sensor_protocol, name, value);

    GlobalVar_sensor_yanwu = value;
    // GlobalVar_sensor_MQ1 = value;
}

void GetSensor_MQ1(char *name)
{
    unsigned int value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        Adc_Init_channel(6);
    }

    value = Get_ADC_channel(6); //channel and repeat times
    value = value / 32;

    protocol_send_IdValue_int(sensor_protocol, name, value);

    // GlobalVar_sensor_yanwu = value;
    GlobalVar_sensor_MQ1 = value;
}

//yanwu2 AO7
void GetSensor_Yanwu_2(char *name)
{
    unsigned int value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        Adc_Init_channel(0);
    }

    value = Get_ADC_channel(0); //channel and repeat times
    value = value / 32;

    protocol_send_IdValue_int(sensor_protocol, name, value);

    GlobalVar_sensor_yanwu_2 = value;
    GlobalVar_sensor_MQ2 = value;
}

void GetSensor_MQ2(char *name)
{
    unsigned int value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        Adc_Init_channel(0);
    }

    value = Get_ADC_channel(0); //channel and repeat times
    value = value / 32;

    protocol_send_IdValue_int(sensor_protocol, name, value);

    // GlobalVar_sensor_yanwu_2 = value;
    GlobalVar_sensor_MQ2 = value;
}

//guangqiang AO6
void GetSensor_Ziwaixian(char *name)
{
    unsigned int value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        Adc_Init_channel(6);
    }

    value = Get_ADC_channel(6); //channel and repeat times
    value = value / 32;

    protocol_send_IdValue_int(sensor_protocol, name, value);

    GlobalVar_sensor_ziwaixian = value;
}

//yudi  AO1
void GetSensor_Yudi(char *name)
{
    unsigned int value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        Adc_Init_channel(1);
    }

    value = Get_ADC_channel(1); //channel and repeat times
    value = value / 32;

    value = value > 128 ? 128 : value;
    value = value < 40 ? 40 : value;

    value = 128 - value;

    protocol_send_IdValue_int(sensor_protocol, name, value);

    GlobalVar_sensor_yudi = value;
}

//yudi  AO1
void GetSensor_Shuiwei(char *name)
{
    unsigned int value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        Adc_Init_channel(1);
    }

    value = Get_ADC_channel(1); //channel and repeat times
    value = value / 32;

    value = value < 40 ? 40 : value;
    value = value > 65 ? 65 : value;
    value = value - 40;
    value = value * 4;

    protocol_send_IdValue_int(sensor_protocol, name, value);

    GlobalVar_sensor_shuiwei = value;
}

//dianliu  A1  100mA
void GetSensor_Dianliu(char *name)
{
    static unsigned char flag_is_init = 0;
    unsigned int value;
    unsigned long count_num;

    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        Adc_Init_channel(1);
    }

    value = Get_ADC_channel(1); //channel and repeat times

    //2048  2080

    if (2048 > value)
    {
        count_num = 2048 - value;
    }
    else
    {
        count_num = value - 2048;
    }

    //  (count_num /4096 )* (3.3 *1000)  /100  *1000  /10   === 10ma
    //  (count_num /4096 )* (3300)
    //  (count_num *33 / 41)   ====== 10ma
    //  (count_num *33 / 41)   =====100ma

    value = count_num * 33 / 410; //get 100mA
    if (value < 3)
        value = 0;

    GlobalVar_sensor_dianliu = value;

    protocol_send_IdValue_int(sensor_protocol, name, value);
}

//dianya  A0  110mv
void GetSensor_Dianya(char *name)
{
    static unsigned char flag_is_init = 0;
    unsigned int value;
    // unsigned long count_num;

    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        Adc_Init_channel(0);
    }

    value = Get_ADC_channel(0); //channel and repeat times
    value = value / 32;

    value = value * 5 * 33 / 128; //100mv

    GlobalVar_sensor_dianya = value;
    protocol_send_IdValue_int(sensor_protocol, name, value);
}

//turang  AO4
void GetSensor_Turang(char *name)
{
    unsigned int value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        Adc_Init_channel(4);
    }

    value = Get_ADC_channel(4); //channel and repeat times
    value = value / 32;

    value = value > 127 ? 127 : value;
    value = 127 - value;

    protocol_send_IdValue_int(sensor_protocol, name, value);

    GlobalVar_sensor_turang = value;
}

void GetSensor_Time(char *name)
{
    static unsigned int time_count = 0;

    time_count++;

    protocol_send_IdValue_int(sensor_protocol, name, time_count);
}

void GetSensor_AO1(char *name)
{
    unsigned int value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        Adc_Init_channel(1);
    }

    value = Get_ADC_channel(1); //channel and repeat times
    value = value / 32;

    protocol_send_IdValue_int(sensor_protocol, name, value);

    GlobalVar_sensor_turang = value;
}

//B12
void GetSensor_DO1(char *name)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    unsigned char value;

    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PB端口时钟

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;        // 端口配置
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     //设置成上拉输入
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO口速度为50MHz
        GPIO_Init(GPIOB, &GPIO_InitStructure);            //根据设定参数初始化GPIOA.8
        GPIO_ResetBits(GPIOB, GPIO_Pin_12);               // 输出低
    }

    value = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12);

    GlobalVar_sensor_DO1 = value;

    protocol_send_IdValue_int(sensor_protocol, name, value);
}

//B13
void GetSensor_DO2(char *name)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    unsigned char value;

    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PB端口时钟

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;        // 端口配置
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     //设置成上拉输入
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO口速度为50MHz
        GPIO_Init(GPIOB, &GPIO_InitStructure);            //根据设定参数初始化GPIOA.8
        GPIO_ResetBits(GPIOB, GPIO_Pin_13);               // 输出低
    }

    value = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);

    GlobalVar_sensor_DO2 = value;

    protocol_send_IdValue_int(sensor_protocol, name, value);
}

//B13
void GetSensor_hongwai_duiguan(char *name)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    unsigned char value;

    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PB端口时钟

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;        // 端口配置
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     //设置成上拉输入
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO口速度为50MHz
        GPIO_Init(GPIOB, &GPIO_InitStructure);            //根据设定参数初始化GPIOA.8
        GPIO_ResetBits(GPIOB, GPIO_Pin_12);               // 输出低
    }

    value = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12);

    GlobalVar_sensor_hongwai_duiguan = !value;

    protocol_send_IdValue_int(sensor_protocol, name, GlobalVar_sensor_hongwai_duiguan);
}

//B14
void GetSensor_DO3(char *name)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    unsigned char value;

    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PB端口时钟

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;        // 端口配置
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     //设置成上拉输入
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO口速度为50MHz
        GPIO_Init(GPIOB, &GPIO_InitStructure);            //根据设定参数初始化GPIOA.8
        GPIO_ResetBits(GPIOB, GPIO_Pin_14);               // 输出低
    }

    value = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14);

    GlobalVar_sensor_DO3 = value;

    protocol_send_IdValue_int(sensor_protocol, name, value);
}

//A7
void GetSensor_Zhuodu(char *name)
{
    unsigned int value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        Adc_Init_channel(7);
    }

    value = Get_ADC_channel(7); //channel and repeat times
    value = value / 32;

    if (value > 128)
        value = 128;
    value = 128 - value;

    GlobalVar_sensor_zhuodu = value;
    protocol_send_IdValue_int(sensor_protocol, name, value);
}

//A6
void GetSensor_PH(char *name)
{
    unsigned int value;
    unsigned int temp_value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        Adc_Init_channel(6);
    }

    value = Get_ADC_channel(6); //channel and repeat times
    value = value / 32;
    // value -   PH
    // 82    -  9.18
    // 115   -  4.0
    // 98    -  6.86

    if (value >= 98)
    {
        temp_value = ((value - 98) * 10 / 55);
        if (temp_value > 7)
            temp_value = 7;
        value = 7 - temp_value;
    }
    else
    {
        temp_value = ((98 - value) * 10 / 62);
        if (temp_value > 7)
            temp_value = 7;
        value = 7 + temp_value;
    }

    GlobalVar_sensor_ph = value;

    protocol_send_IdValue_int(sensor_protocol, name, value);
}

void GetSensor_PH_float(char *name)
{
    float value;
    float temp_value;
    char buff[30];
    static unsigned char flag_is_init = 0;

    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        Adc_Init_channel(6);
    }

    value = Get_ADC_channel(6); //channel and repeat times
    value = value / 32;
    // value -   PH
    // 82    -  9.18
    // 115   -  4.0
    // 98    -  6.86

    if (value >= 98)
    {
        temp_value = ((value - 98) * 10 / 55);
        if (temp_value > 7)
            temp_value = 7;
        value = 7 - temp_value;
    }
    else
    {
        temp_value = ((98 - value) * 10 / 62);
        if (temp_value > 7)
            temp_value = 7;
        value = 7 + temp_value;
    }

    GlobalVar_sensor_ph_float = value;

    sprintf(buff, "%f", GlobalVar_sensor_ph_float);

    protocol_send_IdValue_str(sensor_protocol, name, buff);
}

void GetSensor_hongwai_wendu(char *name)
{

    static unsigned char flag_is_init = 0;

    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        UART1_Init(115200); //v1
        // UART1_Init(9600);  //v2
        GlobalVar_flag_hongwaiwendu_inited = 1;
    }

    hongwaiwendu_trigger((void (*)(unsigned char *, unsigned int))UART1_Send_BUFF);

    protocol_send_IdValue_int(sensor_protocol, name, GlobalVar_sensor_hongwai_wendu);
}


void GetSensor_pm25(char *name)
{

    static unsigned char flag_is_init = 0;

    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        // UART1_Init(115200); //v1
        UART1_Init(9600);  //v2
        GlobalVar_flag_pm25_inited = 1;

    }

    protocol_send_IdValue_int(sensor_protocol, name, GlobalVar_sensor_pm25);
}

void GetSensor_uart6050(char *x, char *y, char *z)
{

    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        UART1_Init(115200);

        GlobalVar_flag_uart6050_inited = 1;
    }

    uart6050_trigger((void (*)(unsigned char *, unsigned int))UART1_Send_BUFF);

    protocol_send_IdValue_int(sensor_protocol, x, GlobalVar_sensor_6050_x);
    protocol_send_IdValue_int(sensor_protocol, y, GlobalVar_sensor_6050_y);
    protocol_send_IdValue_int(sensor_protocol, z, GlobalVar_sensor_6050_z);
}

void GetSensor_tds(char *tds, char *wendu)
{

    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        UART1_Init(9600);

        GlobalVar_flag_tds_inited = 1;
    }

    tds_trigger((void (*)(unsigned char *, unsigned int))UART1_Send_BUFF);

    protocol_send_IdValue_int(sensor_protocol, tds, GlobalVar_sensor_TDS);
    protocol_send_IdValue_int(sensor_protocol, wendu, GlobalVar_sensor_TDS_wendu);
}

void GetSensor_max30102(char *xinlv, char *xueyang)
{

    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        GlobalVar_flag_max30102_inited = 1;

        max30102_init_main();
    }

    protocol_send_IdValue_int(sensor_protocol, xinlv, GlobalVar_sensor_max30102_xinlv);
    protocol_send_IdValue_int(sensor_protocol, xueyang, GlobalVar_sensor_max30102_xueyang);
}

void GetSensor_Renti(char *name)
{
    unsigned int value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        InitSensor_Renti();
    }

    value = Get_Renti();

    protocol_send_IdValue_int(sensor_protocol, name, value);

    GlobalVar_sensor_RenTi = value;
}

void GetSensor_Renti_2(char *name)
{
    unsigned int value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        InitSensor_Renti_2();
    }

    value = Get_Renti_2();

    protocol_send_IdValue_int(sensor_protocol, name, value);

    GlobalVar_sensor_RenTi_2 = value;
}

void GetSensor_Voice(char *name)
{
    unsigned int value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        InitSensor_Voice();
    }

    value = Get_Voice();

    protocol_send_IdValue_int(sensor_protocol, name, value);

    GlobalVar_sensor_voice = value;
}

void GetSensor_Huoyan(char *name)
{
    unsigned int value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        InitSensor_Huoyan();
    }

    value = Get_Huoyan();

    protocol_send_IdValue_int(sensor_protocol, name, value);

    GlobalVar_sensor_huoyan = value;
}

void GetSensor_Key(char *name)
{
    // unsigned int value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        key_button_init();
        GlobalVar_flag_key_inited = 1;
    }

    if (GlobalVar_sensor_key_press_1)
    {
        GlobalVar_sensor_key_press_1 = 0;

        protocol_send_IdValue_int(sensor_protocol, name, GlobalVar_sensor_key_vlaue_1);
    }
}

void GetSensor_Key_2(char *name)
{
    // unsigned int value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        key_button_init();
        GlobalVar_flag_key_inited = 1;
    }

    if (GlobalVar_sensor_key_press_2)
    {
        GlobalVar_sensor_key_press_2 = 0;

        protocol_send_IdValue_int(sensor_protocol, name, GlobalVar_sensor_key_vlaue_2);
    }
}

void GetSensor_GPS(char *gps_x, char *gps_y)
{
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        UART1_Init(9600);

        GlobalVar_flag_gps_inited = 1;
    }
    if(GlobalVar_flag_gps_parse_success)
    {
        protocol_send_IdValue_str(sensor_protocol, gps_x, GlobalVar_gps_x);
        protocol_send_IdValue_str(sensor_protocol, gps_y, GlobalVar_gps_y);
    }
    
}

void GetSensor_Dht11(char *name_wendu, char *name_shidu)
{
    unsigned char wendu = 0;
    unsigned char shidu = 0;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        DHT11_Init();
    }

    DHT11_Read_Data(&wendu, &shidu);

    protocol_send_IdValue_int(sensor_protocol, name_wendu, wendu);
    protocol_send_IdValue_int(sensor_protocol, name_shidu, shidu);

    GlobalVar_sensor_dht11_wendu = wendu;
    GlobalVar_sensor_dht11_shidu = shidu;
}

void GetSensor_Yali(char *name)
{
    unsigned int value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        yali_init();

        yali_Weight_calibration(); //压力传感器校准
    }

    value = yali_Get_Weight();

    protocol_send_IdValue_int(sensor_protocol, name, value);

    GlobalVar_sensor_yali = value;
}

void GetSensor_Xueya(char *name)
{
    unsigned int value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        yali_init();

        yali_Weight_calibration(); //压力传感器校准
    }

    value = yali_Get_Weight();

    value = value / 500;

    if (value < 50)
        value = 0;

    protocol_send_IdValue_int(sensor_protocol, name, value);

    GlobalVar_sensor_yali = value;
}

void GetSensor_Chaoshengbo(char *name)
{
    unsigned int value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        UltrasonicWave_Configuration_channel(3);
    }

    value = UltrasonicWave_GetDistance_ch3();

    protocol_send_IdValue_int(sensor_protocol, name, value);

    GlobalVar_sensor_distance = value;
}

void GetSensor_Chaoshengbo_2(char *name)
{
    unsigned int value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        UltrasonicWave_Configuration_channel(2);
    }

    value = UltrasonicWave_GetDistance_ch2();

    protocol_send_IdValue_int(sensor_protocol, name, value);

    GlobalVar_sensor_distance_2 = value;
}

void GetSensor_Ds18b20(char *name)
{
    unsigned int value;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        ds18b20_start();
    }

    value = ds18b20_read();

    // value = value / 10;

    GlobalVar_sensor_ds18b20_wendu = value;

    protocol_send_IdValue_int(sensor_protocol, name, value);
}

void GetSensor_zhuangtai(char *name , int value)
{
    protocol_send_IdValue_int(sensor_protocol, name, value);
}

void GetSensor_IdValue_int(char *name, int value)
{
    protocol_send_IdValue_int(sensor_protocol, name, value);
}

void GetSensor_IdValue_str(char *name, char *value)
{
    protocol_send_IdValue_str(sensor_protocol, name, value);
}

unsigned char GetSensor_Rc522(char *name)
{
    char state;
    unsigned char value[10];
    char temp[20];
    unsigned int len;

    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;
        RC522_GPIO_init();         //引脚初始化rc522
        PcdReset();                //复位RC522
        PcdAntennaOff();           //关闭天线
        PcdAntennaOn();            //开启天线
        M500PcdConfigISOType('A'); //选择模式
    }

    state = PcdRequest(PICC_REQIDL, value);
    if (!state)
    {
        state = PcdAnticoll(value);

        if (state == MI_OK)
        {
            len = sprintf(temp, "%02X%02X%02X%02X", value[0], value[1], value[2], value[3]);
            temp[len] = 0;

            //OLED_P6x8Str(0,4,temp);

            protocol_send_IdValue_str(sensor_protocol, name, temp);

            GlobalVar_Threshold_RC522 = 1 ;

            return 1;
        }
    }

    return 0;
}



void SetSensor_Beep(unsigned char value)
{
    static unsigned char flag_is_init = 0;
    GPIO_InitTypeDef GPIO_InitStructure;

    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PG,PD端口时钟

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;        // 端口配置
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //设置成上拉输入
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO口速度为50MHz
        GPIO_Init(GPIOB, &GPIO_InitStructure);            //根据设定参数初始化GPIOA.8
        GPIO_SetBits(GPIOB, GPIO_Pin_10);                 // 输出高 -- 低电平触发
    }

    if (value)
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_10); // 输出低  -- 低电平触发
    }
    else
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_10); // 输出高 停止
    }
}

//B12
void SetSensor_DO1(unsigned char value)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PB端口时钟

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;        // 端口配置
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //设置成输出
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO口速度为50MHz
        GPIO_Init(GPIOB, &GPIO_InitStructure);            //根据设定参数初始化GPIOA.8
        GPIO_ResetBits(GPIOB, GPIO_Pin_12);               // 输出低
    }

    if (value)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_12); // 输出高
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_12); // 输出低电平
    }
}

//B13
void SetSensor_DO2(unsigned char value)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PB端口时钟

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;        // 端口配置
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //设置成输出
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO口速度为50MHz
        GPIO_Init(GPIOB, &GPIO_InitStructure);            //根据设定参数初始化GPIOA.8
        GPIO_ResetBits(GPIOB, GPIO_Pin_13);               // 输出低
    }

    if (value)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_13); // 输出高
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_13); // 输出低电平
    }
}

//B14
void SetSensor_DO3(unsigned char value)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PB端口时钟

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;        // 端口配置
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //设置成输出
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO口速度为50MHz
        GPIO_Init(GPIOB, &GPIO_InitStructure);            //根据设定参数初始化GPIOA.8
        GPIO_ResetBits(GPIOB, GPIO_Pin_14);               // 输出低
    }

    if (value)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_14); // 输出高
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_14); // 输出低电平
    }
}

void SetSensor_Jidianqi(unsigned char value)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PB端口时钟

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;         // 端口配置
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //设置成上拉输入
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO口速度为50MHz
        GPIO_Init(GPIOB, &GPIO_InitStructure);            //根据设定参数初始化GPIOA.8
        GPIO_ResetBits(GPIOB, GPIO_Pin_7);                // 输出低电平
    }

    if (value)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_7); // 输出高
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_7); // 输出低电平
    }
}

void SetSensor_Jidianqi_2(unsigned char value)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PB端口时钟

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;         // 端口配置
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //设置成上拉输入
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO口速度为50MHz
        GPIO_Init(GPIOB, &GPIO_InitStructure);            //根据设定参数初始化GPIOA.8
        GPIO_ResetBits(GPIOB, GPIO_Pin_9);                // 输出低电平
    }

    if (value)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_9); // 输出高
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_9); // 输出低电平
    }
}

void SetSensor_Jidianqi_3(unsigned char value)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PB端口时钟

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;         // 端口配置
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //设置成上拉输入
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO口速度为50MHz
        GPIO_Init(GPIOB, &GPIO_InitStructure);            //根据设定参数初始化GPIOA.8
        GPIO_ResetBits(GPIOB, GPIO_Pin_5);                // 输出低电平
    }

    if (value)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_5); // 输出高
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_5); // 输出低电平
    }
}

void SetSensor_Ws2812b_rgb(unsigned char red, unsigned char green, unsigned char blue)
{
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        ws2812b_init();
    }

    ws2812b_rgb(red, green, blue);
}

void SetSensor_Ws2812b_red(unsigned char red)
{
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        ws2812b_init();
    }

    ws2812b_red(red);
}

void SetSensor_Ws2812b_green(unsigned char green)
{
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        ws2812b_init();
    }

    ws2812b_green(green);
}

void SetSensor_Ws2812b_blue(unsigned char blue)
{
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        ws2812b_init();
    }

    ws2812b_blue(blue);
}

void SetSensor_Ws2812b_rgb_2(unsigned char red, unsigned char green, unsigned char blue)
{
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        ws2812b_init_2();
    }

    ws2812b_rgb_2(red, green, blue);
}

void SetSensor_Ws2812b_red_2(unsigned char red)
{
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        ws2812b_init_2();
    }

    ws2812b_red_2(red);
}

void SetSensor_Ws2812b_green_2(unsigned char green)
{
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        ws2812b_init_2();
    }

    ws2812b_green_2(green);
}

void SetSensor_Ws2812b_blue_2(unsigned char blue)
{
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        ws2812b_init_2();
    }

    ws2812b_blue_2(blue);
}

void SetSensor_Ws2812b_rgb_3(unsigned char red, unsigned char green, unsigned char blue)
{
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        ws2812b_init_3();
    }

    ws2812b_rgb_3(red, green, blue);
}

void SetSensor_Ws2812b_red_3(unsigned char red)
{
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        ws2812b_init_3();
    }

    ws2812b_red_3(red);
}

void SetSensor_Ws2812b_green_3(unsigned char green)
{
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        ws2812b_init_3();
    }

    ws2812b_green_3(green);
}

void SetSensor_Ws2812b_blue_3(unsigned char blue)
{
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        ws2812b_init_3();
    }

    ws2812b_blue_3(blue);
}

void SetSensor_Ws2812b_rgb_4(unsigned char red, unsigned char green, unsigned char blue)
{
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        ws2812b_init_4();
    }

    ws2812b_rgb_4(red, green, blue);
}

void SetSensor_Ws2812b_red_4(unsigned char red)
{
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        ws2812b_init_4();
    }

    ws2812b_red_4(red);
}

void SetSensor_Ws2812b_green_4(unsigned char green)
{
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        ws2812b_init_4();
    }

    ws2812b_green_4(green);
}

void SetSensor_Ws2812b_blue_4(unsigned char blue)
{
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        ws2812b_init_4();
    }

    ws2812b_blue_4(blue);
}

void SetSensor_PWM(unsigned char value)
{
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        // TIM1_PWM_Init( 100, 72);
        TIM1_PWM_Init(100, 1);
    }

    SetSensor_Pwm10(value);
}

void SetSensor_fan(unsigned char value)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PB端口时钟

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;        // 端口配置
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //设置成输出
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO口速度为50MHz
        GPIO_Init(GPIOB, &GPIO_InitStructure);            //根据设定参数初始化GPIOA.8
        GPIO_ResetBits(GPIOB, GPIO_Pin_14);               // 输出低
    }

    if (value)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_14); // 输出高
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_14); // 输出低电平
    }
}

void SetSensor_PWM_2(unsigned char value)
{
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        // TIM1_PWM_Init( 100, 72);
        TIM1_PWM_Init(100, 1);
    }

    SetSensor_Pwm11(value);
}

void SetSensor_OLED_Sring(unsigned char x, unsigned char y, unsigned char *buff, unsigned char Char_Size)
{
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        OLED_Init();       //oled初始化
        OLED_Display_On(); //oled开启显示
    }

    OLED_ShowString(x, y, buff, Char_Size);
}



void SetSensor_OLED_Chinese(unsigned char x, unsigned char y, int index)
{
    static unsigned char flag_is_init = 0;
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        OLED_Init();       //oled初始化
        OLED_Display_On(); //oled开启显示
    }

    OLED_ShowCHinese(x, y, index);
}



void SetSensor_Sms(char *sms)
{
    protocol_send_start(sensor_protocol); //
    protocol_send_IdValue_str(sensor_protocol, "cfg_phone_number", GlobalVar_phone_number);
    protocol_send_IdValue_str(sensor_protocol, "sms", sms);
    protocol_send_complete(sensor_protocol, (void (*)(const unsigned char *src, int len))UART2_Send_BUFF);
}

void SetSensor_phone_number(const char *number)
{
    int index = 0;
    const char *pointer = number;

    for (; index < 11; index++)
    {
        GlobalVar_phone_number[index] = *pointer++;
    }

    GlobalVar_phone_number[11] = 0;
}

void SetSensor_duoji(unsigned int value)
{
    unsigned int temp_value = 0;
    static unsigned char flag_is_init = 0;

    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        TIM1_PWM_Init(2000, 720);
    }

    if (value > 180)
        value = 180;

    temp_value = value;

    temp_value = 1750 + (temp_value * 20) / 18;

    TIM_SetCompare4(TIM1, temp_value);
}

void SetSensor_time_update(const char *value)
{
    char index = 0;
    const char *p_value = value;

    static unsigned char flag_is_init = 0;

    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        GlobalVar_flag_time_inited = 1;
    }

    if (*p_value == '2')
    {
        while (index < 19)
        {
            time_current_buffer[index++] = *p_value++;
        }
        time_current_buffer[index] = 0;
    }
}

void SetSensor_time_OLED_show_1s(void)
{
    static unsigned int record_time = 0;

    unsigned int compare_timestamp = 0;

    unsigned int diff_time = 0;

    static char time_buffer_date[12];
    static char time_buffer_time[10];

    char *p_value = time_current_buffer;

    unsigned char index = 0;

    record_time++;

    compare_timestamp = ((time_current_buffer[14] - '0') * 10 + (time_current_buffer[15] - '0')) * 60 +
                        ((time_current_buffer[17] - '0') * 10 + (time_current_buffer[18] - '0'));

    diff_time = compare_timestamp > record_time ? (compare_timestamp - record_time) : (record_time - compare_timestamp);

    if (diff_time > 3)
    {
        record_time = compare_timestamp;
    }

    while (index < 11)
    {
        time_buffer_date[index++] = *p_value++;
    }

    time_buffer_date[4] = '-';
    time_buffer_date[7] = '-';
    time_buffer_date[10] = 0;

    index = 0;
    while (index < 8)
    {
        time_buffer_time[index++] = *p_value++;
    }

    time_buffer_time[2] = ':';
    time_buffer_time[5] = ':';
    time_buffer_time[8] = 0;

    time_buffer_time[7] = (record_time % 60 % 10) + '0';
    time_buffer_time[6] = (record_time % 60 / 10) + '0';

    time_buffer_time[4] = (record_time / 60 % 10) + '0';
    time_buffer_time[3] = (record_time / 60 / 10) + '0';

    SetSensor_OLED_Sring(16, 0, (unsigned char *)time_buffer_date, 8);
    SetSensor_OLED_Sring(22, 1, (unsigned char *)time_buffer_time, 8);
}

void SetSensor_28byj_48(unsigned int value, unsigned int position)
{

    static unsigned char flag_is_init = 0;
    
    if (flag_is_init == 0)
    {
        flag_is_init = 1;

        Step_Motor_GPIO_Init();
    }

    motorNcircle(value, position); //n为步进电机转动的度数，position为正转或者反转
    
}
