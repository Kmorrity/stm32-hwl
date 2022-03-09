#ifndef __KEY_H
#define __KEY_H	 

 


#define  KEY_GPIO_Pin_1   GPIO_Pin_8
#define  KEY_GPIO_Group_1   GPIOA
#define  KEY_GPIO_Clock_1   RCC_APB2Periph_GPIOA
#define  KEY_GPIO_1  GPIO_ReadInputDataBit( KEY_GPIO_Group_1, KEY_GPIO_Pin_1 )


#define  KEY_GPIO_Pin_2   GPIO_Pin_15
#define  KEY_GPIO_Group_2   GPIOA
#define  KEY_GPIO_Clock_2   RCC_APB2Periph_GPIOA
#define  KEY_GPIO_2  GPIO_ReadInputDataBit( KEY_GPIO_Group_2, KEY_GPIO_Pin_2 )
 

#define KEY_active_1  (0)
#define KEY_active_2  (0)
#define KEY_active_3  (0)
#define KEY_active_4  (0)


void key_button_init(void);

void key_button_register( void (*callback)(unsigned char key_number) );

void key_button_scan_10ms(void);

void key_button_scan_1ms(void);

 
	

#endif
