#ifndef __LDCIIC_H
#define __LDCIIC_H
#include "sys.h"

               
//IO方向设置
#define LDC1314_SDA_IN()  {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=8<<12;}
#define LDC1314_SDA_OUT() {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=3<<12;}

//IO操作函数     
#define LDC1314_IIC_SCL    PCout(12) //SCL
#define LDC1314_IIC_SDA    PCout(11) //SDA   
#define READ_SDA   PCin(11)  //输入SDA 

//LDC1314_IIC所有操作函数
void LDC1314_IIC_Init(void);                //初始化LDC1314_IIC的IO口                
void LDC1314_IIC_Start(void);               //发送LDC1314_IIC开始信号
void LDC1314_IIC_Stop(void);                //发送LDC1314_IIC停止信号
void LDC1314_IIC_Send_Byte(u8 txd);         //LDC1314_IIC发送一个字节
u8 LDC1314_IIC_Read_Byte(unsigned char ack);//LDC1314_IIC读取一个字节
u8 LDC1314_IIC_Wait_Ack(void);              //LDC1314_IIC等待ACK信号
void LDC1314_IIC_Ack(void);                 //LDC1314_IIC发送ACK信号
void LDC1314_IIC_NAck(void);                //LDC1314_IIC不发送ACK信号

void LDC1314_IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 LDC1314_IIC_Read_One_Byte(u8 daddr,u8 addr);   
#endif
















