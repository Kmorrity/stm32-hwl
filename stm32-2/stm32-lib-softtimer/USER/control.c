#include "include.h"
#include "control.h"



int data_save_average_ch0 = 0 , data_save_average_ch1 = 0 , data_save_average_ch2 = 0 , data_save_average_ch3 = 0 ;



//初始化获取多个
void Get_Average_Init()
{
	int i ;
	for(i=0 ;i<10;i++)
	{
	
		data_save_average_ch0+=Read_ldc_address(0x00);      // Read CH0 Val
		data_save_average_ch1+= Read_ldc_address(0x02);      // Read CH1 Val
		data_save_average_ch2+= Read_ldc_address(0x04);      // Read CH2 Val		
		data_save_average_ch3+= Read_ldc_address(0x06);      // Read CH3 Val		
		delay_ms(100);
	}
	
	data_save_average_ch0=data_save_average_ch0/10;
	data_save_average_ch1=data_save_average_ch1/10;
	data_save_average_ch2=data_save_average_ch2/10;		
	data_save_average_ch3=data_save_average_ch3/10;		
}





//获取各个通道的偏移量

int Get_Offset_right(void)
{
	return (Read_ldc_address(0x00)-data_save_average_ch0);
}

int Get_Offset_forward(void)
{
	return (Read_ldc_address(0x02)-data_save_average_ch1);
}

int Get_Offset_left(void)
{
	return (Read_ldc_address(0x04)-data_save_average_ch2);
}

int Get_Offset_behind(void)
{
	
	return (Read_ldc_address(0x06)-data_save_average_ch3);
}



//获取各个通道的偏移量绝对值
int Get_ABS_Offset_right(void)
{
	
		return (ABS(Read_ldc_address(0x00)-data_save_average_ch0));
}

int Get_ABS_Offset_forward(void)
{
	return (ABS(Read_ldc_address(0x02)-data_save_average_ch1));
	
}

int Get_ABS_Offset_left(void)
{
	return (ABS(Read_ldc_address(0x04)-data_save_average_ch2));
}

int Get_ABS_Offset_behind(void)
{
	return (ABS(Read_ldc_address(0x06)-data_save_average_ch3));
}



//控制小吃  参数范围 -100 -1000
void Turn_Car(int left , int right)
{
	
		if(right > 0 )
	{
		if(right>99)
		{
			TIM_SetCompare3(TIM2,1);
			TIM_SetCompare4(TIM2,99);
		} 
		else
		{
			TIM_SetCompare3(TIM2,1);
			TIM_SetCompare4(TIM2,right);
		}
	}
	else if(right == 0)
	{
		TIM_SetCompare3(TIM2,1);
		TIM_SetCompare4(TIM2,1);
	}
	else
	{
		if(right < -99)
		{
			TIM_SetCompare3(TIM2,99);
			TIM_SetCompare4(TIM2,1);
		}
		else
		{
			TIM_SetCompare3(TIM2,ABS(right));
			TIM_SetCompare4(TIM2,1);
		}
	}


	if(left > 0 )
	{
		if(left>99)
		{
			TIM_SetCompare1(TIM1,1);
			TIM_SetCompare4(TIM1,99);
		} 
		else
		{
			TIM_SetCompare1(TIM1,1);
			TIM_SetCompare4(TIM1,left);
		}
	}
	else if(left == 0)
	{
		TIM_SetCompare1(TIM1,1);
		TIM_SetCompare4(TIM1,1);
	}
	else
	{
		if(left < -99)
		{
			TIM_SetCompare1(TIM1,99);
			TIM_SetCompare4(TIM1,1);
		}
		else
		{
			TIM_SetCompare1(TIM1,ABS(left));
			TIM_SetCompare4(TIM1,1);
		}
	}
	
}