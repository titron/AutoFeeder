/*
 * drv_key.c
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
#include "drv_key.h"
#include "drv_tmr0.h"

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
 * drv_Key_InitKey
 */
void drv_Key_InitKey(void)
{
	/* Set the port direction key1-key6, key of rotary1, key of rotary2: input */
	/* Protect off */
	prc2 = (U8) 1;
	pd0 = (U8) 0x00; /* P0_0 to P0_7 direction is input */
	pu00 = (U8) 1; /* P0_0 to P0_3 is pull-up */
	pu01 = (U8) 1; /* P0_4 to P0_7 is pull-up */
	/* Protect on */
	prc2 = (U8) 0;
}
/* End of File */
