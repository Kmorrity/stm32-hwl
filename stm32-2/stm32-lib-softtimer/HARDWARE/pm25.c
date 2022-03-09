// #include <string.h>
#include "pm25.h"

void pm25_parse(unsigned char *input_buff, unsigned int input_len, void (*callback)(int value))

{
	static unsigned char hognwai_show_buff[30];
	static int index = 0;
	static unsigned char last_value = 0;
	static unsigned char flag_state = 0;
	static int wendu_value = 0;

	int len_to_Read = input_len;
	unsigned char temp_value;
	unsigned char *temp_pointer = input_buff;

	if (len_to_Read > 0)
	{

		while ((len_to_Read--) && (index < sizeof(hognwai_show_buff)))
		{
			temp_value = *temp_pointer++;

			if (temp_value == 0x18 && last_value == 0xFF)
			{
				hognwai_show_buff[0] = 0xFF;
				hognwai_show_buff[1] = 0x18;
				flag_state = 1;
				index = 2;
			}
			else if (flag_state == 1)
			{

				hognwai_show_buff[index++] = temp_value;
				last_value = temp_value;

				if (index >= 9)
				{
					wendu_value = ((hognwai_show_buff[3] * 10) + (hognwai_show_buff[4] / 10));

					callback(wendu_value);

					flag_state = 0;
					index = 0;
				}
			}
			last_value = temp_value;
		}
	}
}
