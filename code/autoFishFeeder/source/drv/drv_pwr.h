/*
 * drv_pwr.h
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */

#ifndef __DRV_PWR_H__
#define __DRV_PWR_H__
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
extern void drv_Pwr_12V_TurnOff(void);
extern void drv_Pwr_5V_TurnOff(void);
extern void drv_Pwr_3P3V_TurnOff(void);
extern void drv_Pwr_12V_TurnOn(void);
extern void drv_Pwr_5V_TurnOn(void);
extern void drv_Pwr_3P3V_TurnOn(void);
extern void drv_Pwr_SetPortForLowPower(void);
extern void drv_Pwr_InitPwrCtrl(void);
extern void drv_Power_TurnOn(void);

/*
 * Private variables and functions
 */
#endif
/* End of File */
