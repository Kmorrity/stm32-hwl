#include "include.h"
#include "sensor_hal.h"

/*ȫ�ֱ���*/

//----------------------------
//���ڽ���ͨѶЭ������
struct protocol_send send_protocol_uart;
unsigned char send_protocol_uart_buff[512];

struct protocol_pipe protocol_pipe_uart;
unsigned char protocol_pipe_uart_buff[1024];

struct protocol_pipe protocol_pipe_uart_2;
unsigned char protocol_pipe_uart_buff_2[256];

//���ڽ�������1�Ĵ���������
RINGBUF Uart_sensor_RB;
unsigned char uart_sensor_buff[512];

//----------------------------

//-----------------------------
//�����ʱ���趨
static Timer timer_detect_sensor;

static Timer timer_recv_data;

static Timer timer_MAX30102;

static Timer timer_1s;

// static Timer timer_key;
//-----------------------------

//-----------------------------

/*���غ���*/
void HardWare_Init(void); //Ӳ����ʼ��
void SoftWare_Init(void); //�����ʼ��
void UserBoot_Init(void); //�û���ʼ��

void uart_recv_IdValue(const char *id, const char *value);		  //�����ڽ��յ���ָ��
void uart_recv_IdValue_sensor(const char *id, const char *value); //�����ڽ��յ���ָ��
void detect_sensor(void);										  //���ڲɼ���������Ϣ

void key_button_process(unsigned char key_number); //����������

void user_recive_data(unsigned char *src, unsigned int len);
void user_send_data(const unsigned char *src, int len);

void wireless_config()
{
	const char *cfg_server_host = "{\"cfg_server_host\":\"www.xiaotongren.top/student/5313/update.php\"}";
	// const char *cfg_server_host = "{\"cfg_server_host\":\"www.xiaotongren.top/design/update/m1/pid/��Ʊ��/uid/�������\"}";

	const char *cfg_wifi_ssid = "{\"cfg_wifi_ssid\":\"xiaotongren\"}";
	const char *cfg_wifi_passwd = "{\"cfg_wifi_passwd\":\"12345678\"}";


	//config wifi and  gprs/4g
	user_send_data((unsigned char *)cfg_server_host, strlen(cfg_server_host));

	//wifi only
	user_send_data((unsigned char *)cfg_wifi_passwd, strlen(cfg_wifi_passwd));
	user_send_data((unsigned char *)cfg_wifi_ssid, strlen(cfg_wifi_ssid));





}

void wireless_config_refresh()
{
	static unsigned int tick_count = 0;
	tick_count++;
	if (tick_count % 20 == 3)
	{
		wireless_config(); //��ʼ����������
	}
}

/*****************************************/
//Ӳ�����ֳ�ʼ��
/*****************************************/
void HardWare_Init(void)
{

	NVIC_Configuration(); /* ����NVIC�ж�ģʽ */

	delay_init(); /* ��ʱ������ʼ�� */

	UART2_Init(38400); //����2��ʼ��

	// UART1_Init(9600); //����1��ʼ�� -- ������������

	TIM4_Int_Init(1000, 72); /* ��TIM4��ʱ�ж� ������Ϊ 1ms */

	//5������ȫΪ��ͨ���ţ�����������JTAG&SWD���������ԣ�ֻ����st-link����
	// GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);

	//�������PB3��PB4��PA15����ͨIO��PA13&14����SWD����
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
}

//����ɨ��ģ��
void process_card_callback(char *string_code)
{

	protocol_send_start(&send_protocol_uart);

	//################################################################
	protocol_send_IdValue_str(&send_protocol_uart, "card1", string_code);
	//################################################################

	protocol_send_complete(&send_protocol_uart, user_send_data);
}

//��������
void process_hongwai_callback(int value)
{
	GlobalVar_sensor_hongwai_wendu = value;
}

//mpu6050 (GY-25)
void process_6050_callback(int x, int y, int z)
{
	GlobalVar_sensor_6050_x = x;
	GlobalVar_sensor_6050_y = y;
	GlobalVar_sensor_6050_z = z;
}

//TDS
void process_tds_callback(int tds, int wendu)
{
	GlobalVar_sensor_TDS = tds;
	GlobalVar_sensor_TDS_wendu = wendu;
}


//PM25
void process_pm25_callback(int pm25)
{

	
	GlobalVar_sensor_pm25 = pm25;

	
}


//GPS

void process_gps_callback(char * x , char * y )
{
	GlobalVar_flag_gps_parse_success=1;
	strcpy(GlobalVar_gps_x,x);
	strcpy(GlobalVar_gps_y,y);
}

void parse_uart_sensor()
{
	static unsigned char read_buff[512];
	unsigned char value;
	unsigned int index = 0;


	while (RINGBUF_Get(&Uart_sensor_RB, &value) == 0 && index < sizeof(read_buff))
	{
		read_buff[index++] = value;
	}

	if (index == 0)
	{
		return;
	}

	if (GlobalVar_flag_hongwaiwendu_inited)
	{
		hongwaiwendu_parse(read_buff, index, process_hongwai_callback);
	}

	

	if (GlobalVar_flag_pm25_inited)
	{
		pm25_parse(read_buff, index, process_pm25_callback);
	}

	if (GlobalVar_flag_uart6050_inited)
	{
		uart6050_parse(read_buff, index, process_6050_callback);
	}

	// scanner_parse(read_buff, index, process_card_callback);

	if (GlobalVar_flag_tds_inited)
	{
		tds_parse(read_buff, index, process_tds_callback);
	}

	if(GlobalVar_flag_gps_inited)
	{
		GPS_parse(read_buff, index, process_gps_callback);
	}

}

void func_timer_recv_data()
{
	protocol_pipe_get_IdValue(&protocol_pipe_uart, uart_recv_IdValue); //��������2�Ŀ���ָ��

	protocol_pipe_get_IdValue(&protocol_pipe_uart_2, uart_recv_IdValue_sensor); //�������� ����������

	parse_uart_sensor(); //��������1����������

	if (GlobalVar_flag_is_inited_zhendong_DO)
	{
		process_zhendong_DO_100ms();
	}
}

void func_timer_MAX30102()
{
	int xinlv, xueyang;
	if (GlobalVar_flag_max30102_inited)
	{
		max30102_detect(&xinlv, &xueyang);
		GlobalVar_sensor_max30102_xinlv = xinlv;
		GlobalVar_sensor_max30102_xueyang = xueyang;
	}
}

void func_timer_1s()
{
	if (GlobalVar_flag_time_inited)
	{
		SetSensor_time_OLED_show_1s();
	}
}

// void func_timer_key()
// {
// 	// if (GlobalVar_flag_key_inited)
// 	// {
// 	// 	key_button_scan_10ms();
// 	// }
// }

void SoftWare_Init(void)
{

	//ͨѶЭ���ʼ��
	protocol_pipe_init(&protocol_pipe_uart, protocol_pipe_uart_buff, sizeof(protocol_pipe_uart_buff));
	protocol_send_init(&send_protocol_uart, send_protocol_uart_buff, sizeof(send_protocol_uart_buff));

	protocol_pipe_init(&protocol_pipe_uart_2, protocol_pipe_uart_buff_2, sizeof(protocol_pipe_uart_buff_2));

	sensor_hal_protocol_init(&send_protocol_uart); //��ʼ��

	//��ʱ����ʼ��
	timer_init(&timer_detect_sensor, detect_sensor, 2000, 1);	//���ڲɼ���������Ϣ
	timer_init(&timer_recv_data, func_timer_recv_data, 100, 1); //���ڽ�����������ָ��
	timer_init(&timer_MAX30102, func_timer_MAX30102, 1000, 1);	//MAX30102
	timer_init(&timer_1s, func_timer_1s, 1000, 1);				//1�붨ʱ��

	// timer_init(&timer_key, func_timer_key, 10, 1);				//�������

	timer_start(&timer_detect_sensor);
	timer_start(&timer_recv_data);
	timer_start(&timer_MAX30102);
	timer_start(&timer_1s);
	// timer_start(&timer_key);

	key_button_register(key_button_process); //ע�ᰴ��������

	RINGBUF_Init(&Uart_sensor_RB, uart_sensor_buff, sizeof(uart_sensor_buff)); //��ʼ�����ڻ��λ�����
}

/**************************************************************************************/
/***********************************main �������**************************************/
/**************************************************************************************/

int main(void)
{

	SoftWare_Init(); //�����ʼ��

	HardWare_Init(); //Ӳ����ʼ��

	UserBoot_Init(); //�û���ʼ��

	while (1)
	{
		timer_loop(); //��ʱ��ִ��
	}
}

void user_send_data(const unsigned char *src, int len)
{
	UART2_Send_BUFF(src, len);
}

/**************************************************************************************/
//��ʱ��  Ӳ����ʱ����Դ
/**************************************************************************************/
void TIM4_IRQHandler(void) /* TIM4�ж� */
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) /* ���ָ����TIM�жϷ������:TIM �ж�Դ */
	{

		TIM_ClearITPendingBit(TIM4, TIM_IT_Update); /* ���TIMx���жϴ�����λ:TIM �ж�Դ */

		timer_ticks(); //1ms tick to uodate timer

		if (GlobalVar_flag_key_inited)
		{
			key_button_scan_1ms();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
//
//      �����߼�����
//
//
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//
//
//      �����߼�����
//
//
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//
//
//      �����߼�����
//
//
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//
//
//      �����߼�����
//
//
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//
//
//      �����߼�����
//
//
/////////////////////////////////////////////////////////////////////////////////

void uart_recv_IdValue_sensor(const char *id, const char *value)
{
	// int value_len = protocol_valuelen(value); //��ȡЭ�����ֵ����
	// int num_value;

	// if (protocol_compare(id, "yuyin")) //��������
	// {
	// 	if (protocol_compare(value, "hongloumeng"))
	// 	{
	// 		SetSensor_Beep(1);
	// 	}
	// 	else if (protocol_compare(value, "shuihuzhuan"))
	// 	{
	// 		SetSensor_Beep(1);
	// 	}
	// 	else if (protocol_compare(value, "sanguoyanyi"))
	// 	{
	// 		SetSensor_Beep(1);
	// 	}
	// 	else if (protocol_compare(value, "xiyouji"))
	// 	{
	// 		SetSensor_Beep(1);
	// 	}
	// }
}

//����������
void key_button_process(unsigned char key_number)
{

	if (key_number == 1)
	{
		GlobalVar_sensor_key_press_1 = 1;
		GlobalVar_sensor_key_vlaue_1 = !GlobalVar_sensor_key_vlaue_1;

		//-------------------------------------------------------------//

		// if(GlobalVar_sensor_key_vlaue_1)
		// {
		// 	SetSensor_Ws2812b_rgb(0xff,0xff,0xff);
		// }
		// else
		// {
		// 	SetSensor_Ws2812b_rgb(0,0,0);
		// }

		//-------------------------------------------------------------//
	}

	else if (key_number == 2)
	{
		GlobalVar_sensor_key_press_2 = 1;
		GlobalVar_sensor_key_vlaue_2 = !GlobalVar_sensor_key_vlaue_2;

		//-------------------------------------------------------------//

		// if (GlobalVar_sensor_key_vlaue_2)
		// {
		// 	SetSensor_Ws2812b_rgb(0xff, 0xff, 0xff);
		// }
		// else
		// {
		// 	SetSensor_Ws2812b_rgb(0, 0, 0);
		// }

		//-------------------------------------------------------------//
	}
}

//�ϵ��ʼ��
void UserBoot_Init(void)
{
	SetSensor_Beep(0);
	SetSensor_Jidianqi(0);
	SetSensor_Ws2812b_rgb(0, 0, 0);
	SetSensor_fan(0);
	SetSensor_28byj_48(0,0);
}

//�Զ����ں���
//��ʼ�Զ������жϣ�����¿����ȡ���ڿ��ƣ�
//1:�����ж��Ƿ������Զ����ڣ����Ƿ�������ڿ��ƵĹ��ܣ�
//2:����������Զ����ڵĹ��ܣ���ô�����Զ������жϣ��� ��ǿ�����趨����ֵ����ô���ƣ�����صƣ�
void Adjust_Sensor(void)
{
	if(GlobalVar_flag_auto_adjust_wendu)
	{
		if(GlobalVar_sensor_ds18b20_wendu > GlobalVar_Threshold_alert_wendu || GlobalVar_sensor_MQ1 > GlobalVar_Threshold_alert_MQ1)
		{
			SetSensor_Beep(1); //����������

		}
		else
		{
			SetSensor_Beep(0); //����������
		}
		

	}else
		{
			SetSensor_Beep(0); //����������
		}



}

void detect_sensor(void)
{
	//---------------------------------------/////
	wireless_config_refresh(); //����wifi������ģ��
	//---------------------------------------/////

	protocol_send_start(&send_protocol_uart); //

	//################################################################

	GetSensor_Time("online1"); //���߼�� ����ʱ��


	GetSensor_MQ1("mq11"); //MQ1 ���ýӿ�

	GetSensor_Ds18b20("wendu1"); //ds18b20

	GetSensor_Rc522("card1");

	// GetSensor_Key("key1");
	// if(GetSensor_Rc522("card1"))   //RC522ˢ��ģ��
	// {
	// 	SetSensor_Beep(1);
	// 	delay_ms(700);
	// 	SetSensor_Beep(0);
	// }

	GetSensor_zhuangtai("zhuangtai1", GlobalVar_sensor_zhuangtai1);
	GetSensor_zhuangtai("zhuangtai2", GlobalVar_sensor_zhuangtai2);

	// GetSensor_IdValue_int("zhuangtai1", GlobalVar_sensor_zhuangtai1);//ֱ���ϴ�IDvalue  valueΪint
	// GetSensor_IdValue_int("zhuangtai2", GlobalVar_sensor_zhuangtai2);//ֱ���ϴ�IDvalue  valueΪint


	// GetSensor_Key("key1"); //����1


	//################################################################

	protocol_send_complete(&send_protocol_uart, user_send_data);

	Adjust_Sensor(); //�����������ж�
}

void uart_recv_IdValue(const char *id, const char *value)
{
	static unsigned int last_value_1 = 0;
	static unsigned int last_value_2 = 0;
	int value_len = protocol_valuelen(value); //��ȡЭ�����ֵ����
	int num_value;

	GlobalVar_sensor_online_response++;

	if (protocol_compare(id, "beep1")) //�жϸ�ָ���Ƿ��ǿ��� ������
	{
		//�������������Ԥ�� �� ����Ԥ�� �� ����Ԥ��
		if ( GlobalVar_flag_auto_adjust_wendu)
			return; //�Զ�����ģʽ��ֱ�ӷ��أ���ֹ��ָ��������ɸ���

		//{"beep1":"on"}  {"beep1":"off"}
		//��������ִ�У����������Զ����ھ�δ�򿪣���ʱΪ�ֶ�ģʽ
		if (protocol_compare(value, "on")) //�ж��Ƿ��
		{
			SetSensor_Beep(1); //����������
		}
		else
		{
			SetSensor_Beep(0); //�رշ�����
		}
	}

	
	else if (protocol_compare(id, "jdq11"))
	{
	
		GlobalVar_sensor_zhuangtai1 =0;
		if (protocol_compare(value, "on"))
		{
			if(last_value_1==0 )
			{
				SetSensor_Jidianqi(1);
			
			}
			else
			{
				GlobalVar_sensor_zhuangtai1 = 1;
			}
			last_value_1 ++;
		}
		else
		{
			SetSensor_Jidianqi(0);
			
			last_value_1 = 0;
		}

	}

	else if (protocol_compare(id, "jdq21"))
	{

		GlobalVar_sensor_zhuangtai2 =0;
		if (protocol_compare(value, "on"))
		{
			if(last_value_2==0 )
			{
				SetSensor_Jidianqi_2(1);
			}
			else
			{
				GlobalVar_sensor_zhuangtai2 = 1;
				
			}
			last_value_2 ++;
		}
		else
		{
			SetSensor_Jidianqi_2(0);

			last_value_2 = 0;
			
		}

	}


	else if (protocol_compare(id, "a_wen1"))
	{
		if (protocol_compare(value, "on"))
		{
			GlobalVar_flag_auto_adjust_wendu = 1;
		}
		else
		{
			GlobalVar_flag_auto_adjust_wendu = 0;
		}
	}

	else if (protocol_compare(id, "l_mq11"))
	{
		num_value = protocol_atoi(value);

		GlobalVar_Threshold_alert_MQ1 = num_value;
	}


	else if (protocol_compare(id, "l_wen1"))
	{
		num_value = protocol_atoi(value);

		GlobalVar_Threshold_alert_wendu = num_value;
	}


}
