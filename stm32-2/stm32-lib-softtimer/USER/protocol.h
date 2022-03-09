#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "ringbuffer.h"

struct protocol_pipe
{
	RINGBUF ringbuf;

	void(*callback)(const char *id, const char *value);

	//get pack
	unsigned char *frame_buff;
	unsigned int frame_buff_max_len;
	unsigned int frame_idx;
	unsigned char frame_is_get_head;
};

void protocol_pipe_init(struct protocol_pipe *pipeline, unsigned char *buff, unsigned int max_len);

void protocol_pipe_get_IdValue_FromPack(struct protocol_pipe *pipeline, void(*callback)(const char *id, const char *value));

void protocol_pipe_get_IdValue(struct protocol_pipe *pipeline, void(*callback)(const char *id, const char *value));

void protocol_pipe_put(struct protocol_pipe *pipeline, unsigned char * buff, unsigned int len);

char protocol_compare(const char * src, const char * aa);

int protocol_atoi(const char *str);

int protocol_valuelen(const char *str);






struct protocol_send
{
	unsigned char * buffer;
	unsigned int buffer_max_len;
	unsigned int ptr;
};


void protocol_send_init(struct protocol_send *send_protocol, unsigned char *buff, unsigned int max_len);

void protocol_send_start(struct protocol_send * send_protocol);

void protocol_send_IdValue_int(struct protocol_send * send_protocol, const char * id, int value);

void protocol_send_IdValue_str(struct protocol_send * send_protocol, const char * id, const char * value);

void protocol_send_complete(struct protocol_send * send_protocol, void(*device_send)(const unsigned char * src, int len));



#endif
 
