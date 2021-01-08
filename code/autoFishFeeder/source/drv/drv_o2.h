#ifndef DRV_O2_H
#define DRV_O2_H

#include "sfr_r82b.h"
#include "BasicType.h"
#include "drv_led.h"

#define PORT_ADD_O2			p0_7
#define PORT_DIR_O2			pd0_7
#define PORT_MODE_OUTPUT  	1

#define O2_OUT_HIGH		(U8)1
#define O2_OUT_LOW		  (U8)0


void drv_O2_init(void);
void sys_AddingO2(void);
void sys_stopO2(void);



#endif