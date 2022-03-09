
#include "scanner.h"


 

void scanner_parse(unsigned char * input_buff ,unsigned int input_len ,void (*callback)(char * string_code))
{
	static unsigned char card_show_buff[100];
	static int index = 0;
	static unsigned char last_value = 0;
	
	unsigned char temp_value;
	int len_to_Read = input_len;
	unsigned char * temp_pointer = input_buff ;

	if((index+input_len) >= sizeof(card_show_buff))
	{
		//drop directly
		// memset(card_show_buff, 0, sizeof(card_show_buff));
		index = 0;
		return ;
	}

	while ((len_to_Read--) && (index < sizeof(card_show_buff)))
		{
			temp_value = *temp_pointer++;
			 
			if (temp_value == 0x0a && last_value == 0x0d)
			{
				card_show_buff[index-1]= 0x00;  // clean 0x0d
				card_show_buff[index]= 0x00;  // clean 0x0a
				callback((char *)card_show_buff);
				// memset(card_show_buff, 0, sizeof(card_show_buff));
				index = 0;
			}
			else
			{
				card_show_buff[index++] = temp_value;
				last_value = temp_value;
			}
		}
}

