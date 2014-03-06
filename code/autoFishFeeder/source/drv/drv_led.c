/*
 * drv_led.c
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */

/*
 * Includes
 */
#include "BasicType.h"
#include "sfr_r82b.h"
#include "drv_led.h"

/*
 * Typedef
 */

/*
 * Macro
 */

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */

/*
 * Private variables and functions
 */

/*
 * drv_Led_InitLed
 */
void drv_Led_InitLed(void)
{
	PORT_LED1 = (U8) 1;
	PORT_DIRECTION_LED1 = (U8) 1; /* direction is output */
	PORT_LED1 = (U8) 1;

	PORT_LED2 = (U8) 1;
	PORT_DIRECTION_LED2 = (U8) 1; /* direction is output */
	PORT_LED2 = (U8) 1;

	PORT_LED3 = (U8) 1;
	PORT_DIRECTION_LED3 = (U8) 1; /* direction is output */
	PORT_LED3 = (U8) 1;

	PORT_LED4 = (U8) 1;
	PORT_DIRECTION_LED4 = (U8) 1; /* direction is output */
	PORT_LED4 = (U8) 1;
}

/*
 * drv_Led_SetState
 */
void drv_Led_SetState(U8 U8LedNo, U8 U8LedState)
{
	switch (U8LedNo)
	{
	case LED1 :
		PORT_LED1 = U8LedState;
		break;
	case LED2 :
		PORT_LED2 = U8LedState;
		break;
	case LED3 :
		PORT_LED3 = U8LedState;
		break;
	case LED4 :
		PORT_LED4 = U8LedState;
		break;
	default:
		break;
	}
}

/* End of File */
