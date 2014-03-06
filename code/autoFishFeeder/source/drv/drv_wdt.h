/*
 * drv_wdt.h
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */

#ifndef __DRV_WDT_H__
#define __DRV_WDT_H__
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

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */
extern void drv_WDT_InitWDTInHighSpeedOCO(void);
extern void drv_WDT_InitWDTInLowSpeedOCO(void);
extern void drv_Watchdog_FeedDog(void);

/*
 * Private variables and functions
 */

#endif
/* End of file */
