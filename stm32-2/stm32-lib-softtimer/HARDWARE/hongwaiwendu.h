#ifndef __HONGWAIWENDU_H__
#define __HONGWAIWENDU_H__

 

void hongwaiwendu_trigger(void (*uart_send)(unsigned char *buff,unsigned int len));

void hongwaiwendu_parse(unsigned char * input_buff ,unsigned int input_len ,void (*callback)(int wendu));


#endif  
	 

