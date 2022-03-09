#ifndef RINGBUFFER_H
#define RINGBUFFER_H


typedef struct 
{
	unsigned char *p_o;           
	unsigned char *volatile p_r;  
	unsigned char *volatile p_w;  
	volatile int fill_cnt;       
	int size;                   
} RINGBUF;


int RINGBUF_Init(RINGBUF *r, unsigned char *buf, int size);
int RINGBUF_Put(RINGBUF *r, unsigned char c);
int RINGBUF_Get(RINGBUF *r, unsigned char *c);



#endif

