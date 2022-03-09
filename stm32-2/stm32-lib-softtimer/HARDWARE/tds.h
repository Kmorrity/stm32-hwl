#ifndef __TDS_H__
#define __TDS_H__


void tds_trigger(void (*uart_send)(unsigned char *buff,unsigned int len));

void tds_parse(unsigned char *input_buff, unsigned int input_len, void (*callback)(int value_tds, int value_wendu));


#endif  
	 

