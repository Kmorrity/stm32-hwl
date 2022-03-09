#include "ringbuffer.h"


 

int RINGBUF_Init(RINGBUF *r, unsigned char *buf, int size)
{
	if (r == 0 || buf == 0 || size < 2)
		return -1;

	r->p_o = r->p_r = r->p_w = buf;
	r->fill_cnt = 0;
	r->size = size;

	return 0;
}



 

int RINGBUF_Put(RINGBUF *r, unsigned char c)
{
    if(r->p_w==0) 
        return -1 ; //not been init
    
	if (r->fill_cnt >= r->size)
		return -1; // ring buffer is full, this should be atomic operation

	r->fill_cnt++; // increase filled slots count, this should be atomic operation

	*r->p_w++ = c; // put character into buffer

	if (r->p_w >= r->p_o + r->size) // rollback if write pointer go pass
		r->p_w = r->p_o;            // the physical boundary

	return 0;
}

 
int RINGBUF_Get(RINGBUF *r, unsigned char *c)
{
    if(r->p_w==0) 
        return -1 ; //not been init
        
	if (r->fill_cnt <= 0)
		return -1; // ring buffer is empty, this should be atomic operation

	r->fill_cnt--; // decrease filled slots count

	*c = *r->p_r++; // get the character out

	if (r->p_r >= r->p_o + r->size) // rollback if write pointer go pass
		r->p_r = r->p_o;            // the physical boundary

	return 0;
}
