// #include <string.h>
#include "hongwaiwendu.h"



void hongwaiwendu_trigger(void (*uart_send)(unsigned char *buff,unsigned int len))
{
	unsigned char send_cmd[3] = {0xA5,0x15,0xBA}; //单次请求
	// unsigned char send_cmd[3] = {0xA5,0x45,0xEA}; //连续发送 周期10ms
   	uart_send(send_cmd,3);
}



void hongwaiwendu_parse(unsigned char * input_buff ,unsigned int input_len ,void (*callback)(int wendu))
{
	static unsigned char hognwai_show_buff[30];
	static int index = 0;
	static unsigned char last_value = 0;
	static unsigned char flag_state = 0;
	static int wendu_value = 0;

	
	int len_to_Read = input_len;
	unsigned char temp_value;
	unsigned char * temp_pointer = input_buff ;

	if (len_to_Read > 0)
	{

		while ((len_to_Read--) && (index < sizeof(hognwai_show_buff)))
		{
			temp_value = *temp_pointer++;

			if (temp_value == 0x5A && last_value == 0x5A)
			{
				hognwai_show_buff[0] = 0x5A;
				hognwai_show_buff[1] = 0x5A;
				flag_state = 1;
				index=2;
			}
			else if(flag_state==1)
			{

				hognwai_show_buff[index++] = temp_value;
				last_value = temp_value;
				
				if(index>=9)
				{
					wendu_value = ((hognwai_show_buff[4]<<8)|hognwai_show_buff[5])/100; 

					callback(wendu_value);

					flag_state=0;
					index=0;
				}
				
			}
			last_value = temp_value;
		}
	}
}

