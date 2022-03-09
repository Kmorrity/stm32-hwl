// #include <string.h>
#include "uart6050.h"

void uart6050_trigger(void (*uart_send)(unsigned char *buff, unsigned int len))
{
	unsigned char send_cmd[2] = {0xA5, 0x51}; //单次请求
	uart_send(send_cmd, 2);
}

void uart6050_parse(unsigned char *input_buff, unsigned int input_len, void (*callback)(int x, int y, int z))
{
	static unsigned char uart6050_show_buff[30];
	static int index = 0;

	int len_to_Read = input_len;
	unsigned char temp_value;
	unsigned char *temp_pointer = input_buff;

	short int  PITCH ,YAW ,ROLL; // x y z  

 

	if (len_to_Read > 0)
	{

		while ((len_to_Read--) && (index < sizeof(uart6050_show_buff)))
		{
			temp_value = *temp_pointer++;

			uart6050_show_buff[index++] = temp_value; //读取接收到的数据

			if (!(uart6050_show_buff[0] == 0xaa)) //如果帧头错误，清缓存
			{
				index = 0;
				uart6050_show_buff[0] = 0;
			}
			if (index == 8) //数据接收完毕
			{
				if (uart6050_show_buff[7] == 0x55) //判断帧尾，正确则解析姿态角
				{
					YAW = (uart6050_show_buff[1] << 8 | uart6050_show_buff[2]); //YAW，PITCH,ROLL为真实值的100倍
					PITCH = (uart6050_show_buff[3] << 8 | uart6050_show_buff[4]);
					ROLL = (uart6050_show_buff[5] << 8 | uart6050_show_buff[6]);

	 				callback(PITCH/100,YAW/100,ROLL/100);  // output
					//  callback(PITCH,YAW,ROLL);  // output
				}
				index = 0; //清缓存
			}

		 
		}
	}
}
