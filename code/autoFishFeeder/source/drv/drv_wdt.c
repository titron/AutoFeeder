/*****************************************************************************
 * DISCLAIMER
 *
 * This software is supplied by Renesas Electronics Corporation and is only
 * intended for use with Renesas products. No other uses are authorized.
 * This software is owned by Renesas Electronics Corporation and is protected
 * under all applicable laws, including copyright laws.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES
 * REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY,
 * INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY
 * DISCLAIMED.
 *
 * TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
 * ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
 * FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES
 * FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS
 * AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 *
 * Renesas reserves the right, without notice, to make changes to this
 * software and to discontinue the availability of this software.
 * By using this software, you agree to the additional terms and
 * conditions found by accessing the following link:
 * http://www.renesas.com/disclaimer
 *****************************************************************************/
/* Copyright (C) 2010 Renesas Electronics Corporation. All rights reserved.  */
/*****************************************************************************
 * System Name  : AutoFeeder
 * File Name    : drv_wdt.c
 * Abstract     : watchdog timer module
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AutoFeeder module
 * Description  : watchdog timer module
 * Operation    : none
 * Limitation   : none
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "sfr_r82b.h"
#include "config.h"
#include "drv_wdt.h"

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
#define WDC7_DIVIDED_BY_16					0
#define WDC7_DIVIDED_BY_128					1
#define CSPRO_COUNT_SOURCE_CPU_CLOCK		0
#define CSPRO_COUNT_SOURCE_LOWSPEED_OCO		1
/* Note: OFS is defined in the file of "cstartdef.c" */
 
/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/

/*****************************************************************************
 Private variables and functions
 *****************************************************************************/

/*****************************************************************************
 * ID                : 1.0
 * Outline           : Initialize watchdog timer
 * Include           : none
 * Declaration       : void Drv_WDT_InitWDTInHighSpeedOCO(void)
 * Description       : 1. Watchdong timer is about 209ms, when clock source use
                     :    high-speed OCO.
                     : 2. After reset, watchdog-timer is stopped.
                     : 3. Considered 'cspro' cannot be set 0 by program, select
                     :    cspro is always 1(CPU clock as clock source).
 * Argument          : none
 * Return Value      : none
 * Calling Functions : none
 *****************************************************************************/
void drv_WDT_InitWDTInHighSpeedOCO(void)
{
	/* Drv_INT_DisableInterrupt(); */		/* Disable interrupt */
	/* reset WDT */
	wdtr = 0x00;
	wdtr = 0xFF;
	/* Select reset when WDT timer underflow */
	prc1 = PRC0_PROTECT_OFF;			/* protection OFF */
    pm12 = 1;
	prc1 = PRC0_PROTECT_ON;				/* protection ON */
	/* division */
	prc0 = PRC0_PROTECT_OFF;			/* protection OFF */
	cm07 = 0;
	prc0 = PRC0_PROTECT_ON;				/* protection ON */
	wdc7 = WDC7_DIVIDED_BY_128;
	/* count source select low-speed OCO */
	/* cspro = 0; */					/* default 0, 0 cannot be set by a program */
	/* start WDT (After reset, WDT is stopped. Once start, WDT cannot stop!)*/
//	wdts = 0xFF;
	/* reset WDT */
	wdtr = 0x00;
	wdtr = 0xFF;
	/* Drv_INT_EnableInterrupt(); */	/* Enable interrupt */
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : Initialize watchdog timer
 * Include           : none
 * Declaration       : void Drv_WDT_InitWDTInHighSpeedOCO(void)
 * Description       : 1. Watchdong timer is about 4.194s, when clock source use
                     :    low-speed OCO 125KHz.
                     : 2. After reset, watchdog-timer is stopped.
                     : 3. Considered 'cspro' cannot be set 0 by program, select
                     :    cspro is always 1(CPU clock as clock source).
 * Argument          : none
 * Return Value      : none
 * Calling Functions : none
 *****************************************************************************/
void drv_WDT_InitWDTInLowSpeedOCO(void)
{
	/* Drv_INT_DisableInterrupt(); */		/* Disable interrupt */
	/* reset WDT */
	wdtr = 0x00;
	wdtr = 0xFF;
	/* Select reset when WDT timer underflow */
	prc1 = PRC0_PROTECT_OFF;			/* protection OFF */
    pm12 = 1;
	prc1 = PRC0_PROTECT_ON;				/* protection ON */
	/* division */
	prc0 = PRC0_PROTECT_OFF;			/* protection OFF */
	cm07 = 0;
	prc0 = PRC0_PROTECT_ON;				/* protection ON */
	wdc7 = WDC7_DIVIDED_BY_16;
	/* wdc7 = WDC7_DIVIDED_BY_128; */
	/* count source select low-speed OCO */
	/* cspro = 0; */					/* default 0, 0 cannot be set by a program */
	/* start WDT (After reset, WDT is stopped. Once start, WDT cannot stop!)*/
	wdts = 0xFF;
	/* reset WDT */
	wdtr = 0x00;
	wdtr = 0xFF;
	/* Drv_INT_EnableInterrupt(); */	/* Enable interrupt */
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : Feed dog by reset WDT counter
 * Include           : none
 * Declaration       : void Drv_Watchdog_FeedDog(void)
 * Description       : Feed dog by reset WDT counter
 * Argument          : none
 * Return Value      : none
 * Calling Functions : none
 *****************************************************************************/
void drv_Watchdog_FeedDog(void)
{
	/* reset WDT counter */
	wdtr = 0x00;
	wdtr = 0xFF;
}

/* End of file */
