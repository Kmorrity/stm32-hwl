#include "protocol.h"


void protocol_pipe_init(struct protocol_pipe *pipeline, unsigned char *buff, unsigned int max_len)
{
	unsigned int offset = max_len / 3;
	RINGBUF_Init(&(pipeline->ringbuf), buff + offset, max_len - offset);

	pipeline->frame_buff = buff;
	pipeline->frame_buff_max_len = offset;
	pipeline->frame_idx = 0;
	pipeline->frame_is_get_head = 0;


}


void protocol_pipe_parseFrame(struct protocol_pipe *pipeline)
{

	char *ptr = (char *)pipeline->frame_buff;

	char *id = (char *)pipeline->frame_buff + 1;

	char *value;

	for (; ptr < (char *)(pipeline->frame_buff + pipeline->frame_idx); ptr++)
	{
		if (*ptr == ',' || *ptr == '}')
		{
			value = id;
			while (value++ < ptr)
			{
				if (*value == ':')
				{
					value++;
					if (*id == '\"') id++;
					if (*value == '\"') value++;
					pipeline->callback(id, value);
					break;
				}
			}
			id = ptr + 1;
		}
	}
}



void protocol_pipe_Pack(struct protocol_pipe *pipeline, void(*callback)(const char *pack, const int len))
{
	unsigned char recv_byte;

	while (RINGBUF_Get(&(pipeline->ringbuf), &recv_byte) == 0)
	{

		if (recv_byte == '{')
		{
			pipeline->frame_is_get_head = 1;
			pipeline->frame_idx = 0;
			pipeline->frame_buff[pipeline->frame_idx++] = recv_byte;

			continue;
		}
		else if (recv_byte == '}')
		{
			if (pipeline->frame_is_get_head)
			{
				pipeline->frame_buff[pipeline->frame_idx++] = recv_byte;

				//callback : parse success and get one frame

				callback((char*)pipeline->frame_buff, pipeline->frame_idx);

				pipeline->frame_idx = 0;
				pipeline->frame_is_get_head = 0;
			}
			else
			{
				pipeline->frame_idx = 0;
			}
		}
		else
		{
			if (pipeline->frame_is_get_head && (pipeline->frame_idx < (pipeline->frame_buff_max_len) - 2) )
			{
				pipeline->frame_buff[pipeline->frame_idx++] = recv_byte;
			}
		}
	}
}




void protocol_pipe_get_IdValue_FromPack(struct protocol_pipe *pipeline, void(*callback)(const char *id, const char *value))
{

	char *ptr = (char *)pipeline->frame_buff;

	char *id = (char *)pipeline->frame_buff + 1;

	char *value;

	pipeline->callback = callback;


	for (; ptr < (char *)(pipeline->frame_buff + pipeline->frame_idx); ptr++)
	{
		if (*ptr == ',' || *ptr == '}')
		{
			value = id;
			while (value++ < ptr)
			{
				if (*value == ':')
				{
					value++;
					if (*id == '\"') id++;
					if (*value == '\"') value++;
					pipeline->callback(id, value);
					break;
				}
			}
			id = ptr + 1;
		}
	}
}



void protocol_pipe_get_IdValue(struct protocol_pipe *pipeline, void(*callback)(const char *id, const char *value))
{
	unsigned char recv_byte;

	pipeline->callback = callback;

	while (RINGBUF_Get(&(pipeline->ringbuf), &recv_byte) == 0)
	{

		if (recv_byte == '{')
		{
			pipeline->frame_is_get_head = 1;
			pipeline->frame_idx = 0;
			pipeline->frame_buff[pipeline->frame_idx++] = recv_byte;

			continue;
		}
		else if (recv_byte == '}')
		{
			if (pipeline->frame_is_get_head)
			{
				pipeline->frame_buff[pipeline->frame_idx++] = recv_byte;

				//callback : parse success and get one frame

				protocol_pipe_parseFrame(pipeline);

				pipeline->frame_idx = 0;
				pipeline->frame_is_get_head = 0;
			}
			else
			{
				pipeline->frame_idx = 0;
			}
		}
		else
		{
			if (pipeline->frame_is_get_head &&  (pipeline->frame_idx < (pipeline->frame_buff_max_len) - 2)  )
			{
				pipeline->frame_buff[pipeline->frame_idx++] = recv_byte;
			}
		}
	}
}










void protocol_pipe_put(struct protocol_pipe *pipeline, unsigned char * buff, unsigned int len)
{
	unsigned int i;
	for (i = 0; i < len; i++)
	{
		RINGBUF_Put(&pipeline->ringbuf, buff[i]);
	}
}




char protocol_compare(const char * src, const char * aa)
{
	const char * start = src;
	int i = 0;
	int len = 0;

	while ((*(aa + len)) != '\0')
	{
		len++;
	}


	//if (*src == '\"') start = src + 1;

	for (i = 0; i < len; i++)
	{
		if (start[i] != aa[i])  return 0;
	}

	return 1;

}




int protocol_atoi(const char *str)
{
	int value = 0;
	while (*str >= '0' && *str <= '9')
	{
		value *= 10;
		value += *str - '0';
		str++;
	}
	return value;
}





int protocol_valuelen(const char *str)
{
	int len = 0;
	while ((*(str + len)) != '}' && (*(str + len)) != ',' && (*(str + len)) != '\"' && (*(str + len)) != ':')
	{
		len++;
	}

	return len;
}









void protocol_send_init(struct protocol_send *send_protocol, unsigned char *buff, unsigned int max_len)
{
	send_protocol->buffer = buff;
	send_protocol->buffer_max_len = max_len;


}

void protocol_send_start(struct protocol_send * send_protocol)
{
	send_protocol->ptr = 0;
	send_protocol->buffer[0] = '{';
	send_protocol->ptr++;

}



// void my_itoa(long num, char *string)
// {
// 	int power = 0, j = 0;

// 	j = num;
// 	for (power = 1; j>10; j /= 10)
// 		power *= 10;

// 	for (; power>0; power /= 10)
// 	{
// 		*string++ = '0' + num / power;
// 		num %= power;
// 	}
// 	*string = '\0';

// }



void protocol_send_insert_value(struct protocol_send * send_protocol, unsigned char byte)
{
	if (send_protocol->ptr < send_protocol->buffer_max_len)
	{
		send_protocol->buffer[send_protocol->ptr++] = byte;
	}

}


void protocol_send_IdValue_int(struct protocol_send * send_protocol, const char * id, int value)
{
	int power = 0, j = 0;
	protocol_send_insert_value(send_protocol, '\"');
	while (*id != '\0')
	{
		protocol_send_insert_value(send_protocol, *id);
		id++;
	}
	protocol_send_insert_value(send_protocol, '\"');
	protocol_send_insert_value(send_protocol, ':');
	protocol_send_insert_value(send_protocol, '\"');


	if(value<0)
	{
		value = -value;
		protocol_send_insert_value(send_protocol, '-');
	}

	j = value;

	for (power = 1; j >= 10; j /= 10)
		power *= 10;

	for (; power > 0; power /= 10)
	{
		protocol_send_insert_value(send_protocol, '0' + value / power);
		value %= power;
	}

	protocol_send_insert_value(send_protocol, '\"');
	protocol_send_insert_value(send_protocol, ',');

}



void protocol_send_IdValue_str(struct protocol_send * send_protocol, const char * id, const  char * value)
{
	protocol_send_insert_value(send_protocol, '\"');
	while (*id != '\0')
	{
		protocol_send_insert_value(send_protocol, *id);
		id++;
	}
	protocol_send_insert_value(send_protocol, '\"');
	protocol_send_insert_value(send_protocol, ':');

	protocol_send_insert_value(send_protocol, '\"');
	while (*value != '\0')
	{
		protocol_send_insert_value(send_protocol, *value);
		value++;
	}
	protocol_send_insert_value(send_protocol, '\"');
	protocol_send_insert_value(send_protocol, ',');

}



void protocol_send_complete(struct protocol_send * send_protocol, void(*device_send)(const unsigned char * src, int len))
{
	if (send_protocol->buffer[send_protocol->ptr - 1] == ',')
	{
		send_protocol->buffer[send_protocol->ptr - 1] = '}';

		device_send(&send_protocol->buffer[0], send_protocol->ptr);

	}

}


