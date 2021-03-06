/*
 * drv_wdt.c
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */

/*
 * Includes
 */
#include "sfr_r82b.h"
#include "config.h"
#include "drv_wdt.h"

/*
 * Typedef
 */

/*
 * Macro
 */
#define WDC7_DIVIDED_BY_16					0
#define WDC7_DIVIDED_BY_128					1
#define CSPRO_COUNT_SOURCE_CPU_CLOCK		0
#define CSPRO_COUNT_SOURCE_LOWSPEED_OCO		1
/* Note: OFS is defined in the file of "cstartdef.c" */

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
 * drv_WDT_InitWDTInHighSpeedOCO
 * 1. Watchdong timer is about 209ms, when clock source use
 *    high-speed OCO.
 * 2. After reset, watchdog-timer is stopped.
 * 3. Considered 'cspro' cannot be set 0 by program, select
 *    cspro is always 1(CPU clock as clock source).
 */
void drv_WDT_InitWDTInHighSpeedOCO(void)
{
	/* Drv_INT_DisableInterrupt(); *//* Disable interrupt */
	/* reset WDT */
	wdtr = 0x00;
	wdtr = 0xFF;
	/* Select reset when WDT timer underflow */
	prc1 = PRC0_PROTECT_OFF; /* protection OFF */
	pm12 = 1;
	prc1 = PRC0_PROTECT_ON; /* protection ON */
	/* division */
	prc0 = PRC0_PROTECT_OFF; /* protection OFF */
	cm07 = 0;
	prc0 = PRC0_PROTECT_ON; /* protection ON */
	wdc7 = WDC7_DIVIDED_BY_128;
	/* count source select low-speed OCO */
	/* cspro = 0; *//* default 0, 0 cannot be set by a program */
	/* start WDT (After reset, WDT is stopped. Once start, WDT cannot stop!)*/
//	wdts = 0xFF;
	/* reset WDT */
	wdtr = 0x00;
	wdtr = 0xFF;
	/* Drv_INT_EnableInterrupt(); *//* Enable interrupt */
}

/*
 * drv_WDT_InitWDTInLowSpeedOCO
 * 1. Watchdong timer is about 4.194s, when clock source use
 *    low-speed OCO 125KHz.
 * 2. After reset, watchdog-timer is stopped.
 * 3. Considered 'cspro' cannot be set 0 by program, select
 *    cspro is always 1(CPU clock as clock source).
 */
void drv_WDT_InitWDTInLowSpeedOCO(void)
{
	/* Drv_INT_DisableInterrupt(); *//* Disable interrupt */
	/* reset WDT */
	wdtr = 0x00;
	wdtr = 0xFF;
	/* Select reset when WDT timer underflow */
	prc1 = PRC0_PROTECT_OFF; /* protection OFF */
	pm12 = 1;
	prc1 = PRC0_PROTECT_ON; /* protection ON */
	/* division */
	prc0 = PRC0_PROTECT_OFF; /* protection OFF */
	cm07 = 0;
	prc0 = PRC0_PROTECT_ON; /* protection ON */
	wdc7 = WDC7_DIVIDED_BY_16;
	/* wdc7 = WDC7_DIVIDED_BY_128; */
	/* count source select low-speed OCO */
	/* cspro = 0; *//* default 0, 0 cannot be set by a program */
	/* start WDT (After reset, WDT is stopped. Once start, WDT cannot stop!)*/
	wdts = 0xFF;
	/* reset WDT */
	wdtr = 0x00;
	wdtr = 0xFF;
	/* Drv_INT_EnableInterrupt(); *//* Enable interrupt */
}

void drv_Watchdog_FeedDog(void)
{
	/* reset WDT counter */
	wdtr = 0x00;
	wdtr = 0xFF;
}

/* End of file */
