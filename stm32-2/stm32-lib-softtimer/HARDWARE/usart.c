#include "stm32f10x_rcc.h"
#include "usart.h"

#ifdef __GNUC__
// With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf set to 'Yes') calls __io_putchar()
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;







void UART1_Init(unsigned int BaudRate)
{
    
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    USART1_GPIO_Cmd(USART1_GPIO_CLK, ENABLE);
    USART1_AFIO_Cmd(USART1_AFIO_CLK, ENABLE);
    USART1_CLK_Cmd(USART1_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Pin = USART1_TxPin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART1_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = USART1_RxPin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(USART1_GPIO_PORT, &GPIO_InitStructure);
 
 //============================================================//
    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

//	USART_Cmd(USART1, ENABLE);
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART1, ENABLE);
    /* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
    如下语句解决第1个字节无法正确发送出去的问题 */
    USART_ClearFlag(USART1, USART_FLAG_TC); /* 清发送完成标志，Transmission Complete flag */

    //使能串口中断，并设置优先级
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}



void UART2_Init(unsigned int BaudRate)
{
    
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    USART2_GPIO_Cmd(USART2_GPIO_CLK, ENABLE);
    USART2_CLK_Cmd(USART2_CLK, ENABLE);
    USART2_AFIO_Cmd(USART2_AFIO_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Pin = USART2_TxPin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART2_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = USART2_RxPin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(USART2_GPIO_PORT, &GPIO_InitStructure);
 
 //============================================================//
    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);

    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART2, ENABLE);
    /* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
    如下语句解决第1个字节无法正确发送出去的问题 */
    USART_ClearFlag(USART2, USART_FLAG_TC); /* 清发送完成标志，Transmission Complete flag */

    //使能串口中断，并设置优先级
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}



void UART3_Init(unsigned int BaudRate)
{
    
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    USART3_GPIO_Cmd(USART3_GPIO_CLK, ENABLE);
    USART3_CLK_Cmd(USART3_CLK, ENABLE);
    USART3_AFIO_Cmd(USART3_AFIO_CLK, ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);

    GPIO_InitStructure.GPIO_Pin = USART3_TxPin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART3_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = USART3_RxPin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(USART3_GPIO_PORT, &GPIO_InitStructure);
 
 //============================================================//
    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);

    USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART3, ENABLE);
		
    /* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
    如下语句解决第1个字节无法正确发送出去的问题 */
    USART_ClearFlag(USART3, USART_FLAG_TC); /* 清发送完成标志，Transmission Complete flag */


    //使能串口中断，并设置优先级
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}







/*********************************************************************
  * @brief  UART2 Send DATA.
	* @param  None
  * @retval None
	* @date   20141205
***********************************************************************/
void UART2_Send_DATA(unsigned char data)
{
    USART_SendData(USART2,data);
    //Loop until the end of transmission
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
}

/*********************************************************************
  * @brief  UART1 Send DATA.
	* @param  None
  * @retval None
	* @date   20141205
***********************************************************************/
void UART1_Send_DATA(unsigned char data)
{
    USART_SendData(USART1,data);
    //Loop until the end of transmission
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

/*********************************************************************
  * @brief  UART3 Send DATA.
	* @param  None
  * @retval None
	* @date   20141205
***********************************************************************/
void UART3_Send_DATA(unsigned char data)
{
    USART_SendData(USART3,data);
    //Loop until the end of transmission
    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
}


//串口1发送数组
void UART1_Send_BUFF(const unsigned char *Buf, unsigned int PackLen)
{
    unsigned int i;
    for(i=0; i<PackLen; i++)
    {
        UART1_Send_DATA(Buf[i]);
    }
}

//串口2发送数组
void UART2_Send_BUFF(const unsigned char *Buf, unsigned int PackLen)
{
    unsigned int i;
    for(i=0; i<PackLen; i++)
    {
        UART2_Send_DATA(Buf[i]);
    }
}

//串口3发送数组
void UART3_Send_BUFF(const unsigned char *Buf, unsigned int PackLen)
{
    unsigned int i;
    for(i=0; i<PackLen; i++)
    {
        UART3_Send_DATA(Buf[i]);
    }
}


//---- 支持printf() 打印输出
void PrintChar(char *s)
{
	char *p;
	p=s;
	while(*p != '\0')
	{
		UART2_Send_DATA(*p);
		p++;
	}
}



//不使用半主机模式, 如果没有这段，则需要在target选项中选择使用USE microLIB
// #if 1
// #pragma import(__use_no_semihosting)
// struct __FILE
// {
// 	int handle;
// };
// FILE __stdout;

// _sys_exit(int x)
// {
// 	x = x;
// }
// #endif

PUTCHAR_PROTOTYPE
{
    //Place your implementation of fputc here , e.g. write a character to the USART
    USART_SendData(USART2,(u8)ch);
    //Loop until the end of transmission
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
    return ch;
}

