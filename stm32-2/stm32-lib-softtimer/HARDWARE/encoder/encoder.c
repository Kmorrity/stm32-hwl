#include "encoder.h"


long signed int			TIM3_Encoder_distance	= 0;  //
signed  int	TIM3_Encoder_rate	= 0;	 // 50ms 

long signed int			TIM5_Encoder_distance	= 0;  //
signed  int	TIM5_Encoder_rate	= 0;	 // 50ms 


void TIM3_Encoder_Init( void )
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef	TIM_ICInitStructure;
	/* TIM_OCInitTypeDef  TIM_OCInitStructure; */

/*----------------------------------------------------------------*/

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );


	GPIO_StructInit( &GPIO_InitStructure );
	/* Configure PA.06,07 as encoder input */
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN_FLOATING;
	GPIO_Init( GPIOA, &GPIO_InitStructure );

/*----------------------------------------------------------------*/


	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE ); /* ??TIM3 */
	TIM_DeInit( TIM3 );
	TIM_TimeBaseInit( TIM3, &TIM_TimeBaseStructure );

	TIM_TimeBaseStructure.TIM_Period	= 0xffff;
	TIM_TimeBaseStructure.TIM_Prescaler	= 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;
	/* TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; */

	TIM_TimeBaseInit( TIM3, &TIM_TimeBaseStructure );


	TIM_EncoderInterfaceConfig( TIM3, TIM_EncoderMode_TI12,
	TIM_ICPolarity_Rising, TIM_ICPolarity_Rising ); /* TIM_ICPolarity_Rising */
	TIM_ICStructInit( &TIM_ICInitStructure );
	TIM_ICInitStructure.TIM_ICFilter = 6;
	TIM_ICInit( TIM3, &TIM_ICInitStructure );  

	/* TIM_ARRPreloadConfig(TIM3, ENABLE); */
/* Clear all pending interrupts */
	TIM_ClearFlag( TIM3, TIM_FLAG_Update );
	TIM_ITConfig( TIM3, TIM_IT_Update, ENABLE ); /*  */
	/* Reset counter */
	TIM3->CNT = 0;

	TIM_Cmd( TIM3, ENABLE );
}




void TIM5_Encoder_Init( void )
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef	TIM_ICInitStructure;
	/* TIM_OCInitTypeDef  TIM_OCInitStructure; */

/*----------------------------------------------------------------*/

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );


	GPIO_StructInit( &GPIO_InitStructure );
	/* Configure PA.06,07 as encoder input */
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN_FLOATING;
	GPIO_Init( GPIOA, &GPIO_InitStructure );

/*----------------------------------------------------------------*/


	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM5, ENABLE ); /* ??TIM5 */
	TIM_DeInit( TIM5 );
	TIM_TimeBaseInit( TIM5, &TIM_TimeBaseStructure );

	TIM_TimeBaseStructure.TIM_Period	= 0xffff;
	TIM_TimeBaseStructure.TIM_Prescaler	= 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;
	/* TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; */

	TIM_TimeBaseInit( TIM5, &TIM_TimeBaseStructure );


	TIM_EncoderInterfaceConfig( TIM5, TIM_EncoderMode_TI12,
				    TIM_ICPolarity_Rising, TIM_ICPolarity_Rising ); /* TIM_ICPolarity_Rising */
	TIM_ICStructInit( &TIM_ICInitStructure );
	TIM_ICInitStructure.TIM_ICFilter = 6;
	TIM_ICInit( TIM5, &TIM_ICInitStructure );

	/* TIM_ARRPreloadConfig(TIM5, ENABLE); */
/* Clear all pending interrupts */
	TIM_ClearFlag( TIM5, TIM_FLAG_Update );
	TIM_ITConfig( TIM5, TIM_IT_Update, ENABLE ); /*  */
	/* Reset counter */
	TIM5->CNT = 0;

	TIM_Cmd( TIM5, ENABLE );
}




//��ȡ�������Ĵ�������
unsigned short int TIM3_Encoder_Read_Prototype( void )
{
	unsigned short int tim_count;
	tim_count = TIM_GetCounter( TIM3 ); /* ��ȡ TIM3��ֵ */
	return(tim_count);
}

//��ȡ�������Ĵ�������
unsigned short int TIM5_Encoder_Read_Prototype( void )
{
	unsigned short int tim_count;
	tim_count = TIM_GetCounter( TIM5 ); /* ��ȡ TIM5��ֵ */
	return(tim_count);
}



/****************************************************************
//��ģʽ�Ż���STM32����������ֵΪ�޷���16λ���εı׶�
//ʹ�÷�����  ���齫�˺������� ��ʱ����ִ�У�����������ٶ� �� ����
***************************************************************/
signed int  TIM3_Encoder_Read( void )
{
	static unsigned short int	lastCount	= 0;
	unsigned int			curCount	= TIM3->CNT;
	signed int			dAngle		= curCount - lastCount;
	if ( dAngle >= MAX_COUNT )
	{
		dAngle = (curCount - 65536) - lastCount;
	}else if ( dAngle < -MAX_COUNT )
	{
		dAngle = (65536 - lastCount) + curCount;
	}
	lastCount = curCount;
	return dAngle;
}



/****************************************************************
//��ģʽ�Ż���STM32����������ֵΪ�޷���16λ���εı׶�
//ʹ�÷�����  ���齫�˺������� ��ʱ����ִ�У�����������ٶ� �� ����
***************************************************************/
signed int  TIM5_Encoder_Read( void )
{
	static unsigned short int	lastCount	= 0;
	unsigned int			curCount	= TIM5->CNT;
	signed int			dAngle		= curCount - lastCount;
	if ( dAngle >= MAX_COUNT )
	{
		dAngle = (curCount - 65536) - lastCount;
	}else if ( dAngle < -MAX_COUNT )
	{
		dAngle = (65536 - lastCount) + curCount;
	}
	lastCount = curCount;
	return dAngle;
}


//ֱ�Ӷ�ȡ��������λ����
signed int TIM5_Encoder_Distance( void )
{
	TIM5_Encoder_rate = TIM5_Encoder_Read();

	return(TIM5_Encoder_distance += TIM5_Encoder_rate);
}



//ֱ�Ӷ�ȡ��������λ����
signed int TIM3_Encoder_Distance( void )
{
	TIM3_Encoder_rate = TIM3_Encoder_Read();

	return(TIM3_Encoder_distance += TIM3_Encoder_rate);
}
