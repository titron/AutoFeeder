/*
 * drv_int.c
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
 * drv_INT_Disable
 */
void drv_INT_Disable(void)
{
	asm("FCLR I");				/* Disable interrupt */
}

/*
 * drv_INT_Enable
 */
void drv_INT_Enable(void)
{
	asm("FSET I");				/* Enable interrupt */
}
/* End of file */
