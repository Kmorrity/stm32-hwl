#ifndef __GPS_H
#define __GPS_H


void GPS_parse(unsigned char *input_buff, unsigned int input_len, void (*callback)(char *x, char *y));


#endif  
	 

