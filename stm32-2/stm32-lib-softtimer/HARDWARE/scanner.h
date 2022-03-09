#ifndef SCANNER_H
#define SCANNER_H
 
 
void scanner_parse(unsigned char * input_buff ,unsigned int input_len ,void (*callback)(char * string_code));



#endif
