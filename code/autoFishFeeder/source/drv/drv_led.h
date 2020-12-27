/*
 * drv_led.h
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */
#ifndef __DRV_LED_H__
#define __DRV_LED_H__
/*
 * Includes
 */
#include "basictype.h"

/*
 * Typedef
 */

/*
 * Macro
 */
#define PORT_LED1			p8_0
#define PORT_LED2			p8_1
#define PORT_LED3			p8_2
#define PORT_LED4			p8_3
#define PORT_DIRECTION_LED1	pd8_0
#define PORT_DIRECTION_LED2	pd8_1
#define PORT_DIRECTION_LED3	pd8_2
#define PORT_DIRECTION_LED4	pd8_3

#define LED_ON		(U8)0
#define LED_OFF		(U8)1

#define LED1		(U8)0
#define LED2		(U8)1
#define LED3		(U8)2
#define LED4		(U8)3

/* led */
#define LED_POWER	LED1		/* On-Power on , Off-Power off */
#define LED_HEART    LED2		/* Heart beat every 1 second */
#define LED_O2          LED3		/* Adding O2 led */

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */
extern void drv_Led_InitLed(void);
extern void drv_Led_SetState(U8 U8LedNo, U8 U8LedState);

/*
 * Private variables and functions
 */

#endif
/* End of File */
