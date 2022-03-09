#ifndef __UART6050_H__
#define __UART6050_H__

 

void uart6050_trigger(void (*uart_send)(unsigned char *buff, unsigned int len));

void uart6050_parse(unsigned char *input_buff, unsigned int input_len, void (*callback)(int x, int y, int z));

#endif  
	 

