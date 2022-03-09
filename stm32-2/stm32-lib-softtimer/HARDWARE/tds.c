#include "tds.h"



void tds_trigger(void (*uart_send)(unsigned char *buff,unsigned int len))
{
	unsigned char send_cmd[] = {0xA0, 00, 0, 0, 0, 0xA0}; //单次请求
	
   	uart_send(send_cmd,sizeof(send_cmd));
}



void tds_parse(unsigned char *input_buff, unsigned int input_len, void (*callback)(int value_tds, int value_wendu))
{
	static unsigned char tds_show_buff[30];
	static int index = 0;

	int len_to_Read = input_len;
	unsigned char temp_value;
	unsigned char *temp_pointer = input_buff;

	int temp_value_tds =0;
	int temp_value_wendu =0 ;
 

	if (len_to_Read > 0)
	{

		while ((len_to_Read--) && (index < sizeof(tds_show_buff)))
		{
			temp_value = *temp_pointer++;

			tds_show_buff[index++] = temp_value; //读取接收到的数据

			if (!(tds_show_buff[0] == 0xaa)) //如果帧头错误，清缓存
			{
				index = 0;
				tds_show_buff[0] = 0;
			}
			if (index == 12) //数据接收完毕
			{
				if (tds_show_buff[6] == 0xAB) //判断帧尾，正确则解析姿态角
				{
					temp_value_wendu = (tds_show_buff[7] * 0xff + tds_show_buff[8]) / 100;

					temp_value_tds = (tds_show_buff[1] * 0xff + tds_show_buff[2]);

	 				callback(temp_value_tds,temp_value_wendu);  // output
				}
				index = 0; //清缓存
			}

		 
		}
	}
}
