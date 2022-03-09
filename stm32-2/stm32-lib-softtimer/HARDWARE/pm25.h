#ifndef __PM25_H__
#define __PM25_H__

 
void pm25_parse(unsigned char *input_buff, unsigned int input_len, void (*callback)(int value));

#endif  
	 

