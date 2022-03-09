#ifndef __HX711_H
#define __HX711_H

#include "sys.h"

#define HX711_SCK PBout(0)// PB0
#define HX711_DOUT PBin(1)// PB1


void yali_init(void);

void yali_Weight_calibration(void); //calibration the weight

int yali_Get_Weight(void);


#endif

