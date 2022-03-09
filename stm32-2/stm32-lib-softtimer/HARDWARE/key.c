#include "key.h"
#include "sys.h"



 


static volatile unsigned char key_button_state_1 = 0;
static volatile unsigned char key_button_state_2 = 0;
static volatile unsigned char key_button_state_3 = 0;
static volatile unsigned char key_button_state_4 = 0;
static void (*key_button_callback)(unsigned char key_number);

static volatile unsigned char key_button_state_TEST = 0;


void key_button_init()
{
    GPIO_InitTypeDef GPIOInit;
	RCC_APB2PeriphClockCmd(KEY_GPIO_Clock_1, ENABLE);  
    
    GPIOInit.GPIO_Mode = GPIO_Mode_IPU;   //上拉输入
    GPIOInit.GPIO_Pin = KEY_GPIO_Pin_1 ;  
    GPIOInit.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(KEY_GPIO_Group_1, &GPIOInit);  



	RCC_APB2PeriphClockCmd(KEY_GPIO_Clock_2, ENABLE);  
    
    GPIOInit.GPIO_Mode = GPIO_Mode_IPU;   //上拉输入
    GPIOInit.GPIO_Pin = KEY_GPIO_Pin_2 ;  
    GPIOInit.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(KEY_GPIO_Group_2, &GPIOInit);  


}


void key_button_register(void (*callback)(unsigned char key_number))
{

	if (callback)
	{
		key_button_callback = callback;
	}
}

static void key_button_poll()
{
	if (key_button_state_1)
	{
		if (key_button_callback)
		{
			key_button_callback(1);
		}

		key_button_state_1 = 0;
	}
	else if (key_button_state_2)
	{
		if (key_button_callback)
		{
			key_button_callback(2);
		}

		key_button_state_2 = 0;
	}
}




void key_button_scan_10ms()
{
	static char key1_last = 0;
	static char key2_last = 0;
	// static char key3_last = 0;
	// static char key4_last = 0;
	static char key1_up = 0;
	static char key2_up = 0;
	// static char key3_up = 0;
	// static char key4_up = 0;
	static unsigned char poll_timeout = 0;


	if (KEY_GPIO_1 == KEY_active_1)
	{
		if (key1_last)
		{
			key1_up = 1;
		}
		key1_last = 1;
	}
	else
	{
		if(key1_up)
		{
			key_button_state_1 = 1; //key up done
		}
		key1_up = 0;
		key1_last = 0;
	}



	if (KEY_GPIO_2 == KEY_active_2)
	{
		if (key2_last)
		{
			key2_up = 1;
		}
		key2_last = 1;
	}
	else
	{
		if(key2_up)
		{
			key_button_state_2 = 1; //key up done
		}
		key2_up = 0;
		key2_last = 0;
	}





	if (poll_timeout++ > 20)
	{
		key_button_poll();
		poll_timeout = 0;
	}
}
 




void key_button_scan_1ms()
{
	static unsigned int num = 0;

	num++ ;

	if(num>=10)
	{
		key_button_scan_10ms();
		num = 0;
	}

}




 	    
// //按键初始化函数 
// //PA15和PC5 设置成输入
// void KEY_Init(void)
// {
	
// 	GPIO_InitTypeDef GPIO_InitStructure;

//  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//使能PORTE时钟

// //	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
	
// 	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;//PE6
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
//  	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOA15
	
// } 


// void Simple_Key_Scan( void )
// {
// 	for (;; )
// 	{
// 		if ( GPIO_ReadInputDataBit( GPIOE, GPIO_Pin_6 ) == 0 )
// 		{
// 			delay_ms( 20 ); /* 去抖动 */

// 			if ( GPIO_ReadInputDataBit( GPIOE, GPIO_Pin_6 ) == 0 )
// 			{
// 				break;
// 			}
// 		}
// 	}
// }
// //按键处理函数
// //返回按键值
// //mode:0,不支持连续按;1,支持连续按;
// //返回值：
// //0，没有任何按键按下
// //KEY0_PRES，KEY0按下
// //KEY1_PRES，KEY1按下
// //WKUP_PRES，WK_UP按下 
// //注意此函数有响应优先级,KEY0>KEY1>WK_UP!!
// u8 KEY_Scan(u8 mode)
// {	 
// 	static u8 key_up=1;//按键按松开标志
// 	if(mode)key_up=1;  //支持连按		  
// 	if(key_up&&(KEY0==0||KEY1==0||WK_UP==1))
// 	{
// 		delay_ms(10);//去抖动 
// 		key_up=0;
// 		if(KEY0==0)return KEY0_PRES;
// 		else if(KEY1==0)return KEY1_PRES;
// 		else if(WK_UP==1)return WKUP_PRES; 
// 	}else if(KEY0==1&&KEY1==1&&WK_UP==0)key_up=1; 	     
// 	return 0;// 无按键按下
// }
// //单独扫描KEY0是否被按下
// //返回值:0,没按下;1,按下了.
// u8 KEY0_Scan(void)
// {	 
// 	static u8 key_up=1;//按键按松开标志 	  
// 	if(key_up&&KEY0==0)
// 	{
// 		delay_ms(10);//去抖动 
// 		key_up=0;
// 		if(KEY0==0)return 1;
// 	}else if(KEY0==1)key_up=1; 	     
// 	return 0;// 无按键按下
// }


