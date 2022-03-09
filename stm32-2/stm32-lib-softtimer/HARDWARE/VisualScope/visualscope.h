
#ifndef __VISUALSCOPE_H__
#define __VISUALSCOPE_H__

extern int OutData[4]; //定义虚拟示波器发送数组

void OutPut_Data(void (*send_data)(unsigned char buffer[], int len ));
#endif
