#ifndef __LDC_H
#define __LDC_H

#include "sys.h"



void LDC_Init(void);
	
void Write_ldc_address(u8 address ,u16 Date);

u16 Read_ldc_address(u8 ldc_add);

void Config_LDC(void);









#endif
