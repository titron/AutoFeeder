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
 * System Name  : AE1-LF Car Audio Demo
 * File Name    : driver_timer0.c
 * Abstract     : driver of timer RA (used as system timer)
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AE1-LF demo board
 * Description  : This is driver of system timer implemented by timer RA.
 * Operation    : 
 * Limitation   : This file can be only used as sample code for AE1-LF.
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "sfr_r82b.h"
#include "driver_int.h"
#include "driver_timer0.h"
#include "driver_csi0.h"
#include "driver_led.h"
#include "driver_rotary.h"
#include "if_key.h"
#include "if_serial_ae1.h"
#include "app_ae1.h"
#include "app_host.h"
#include "app_menu.h"
#include "app_evolume.h"
#include "service_general.h"

#include "main.h"

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
/* timer clock definition when high-speed OCO */
#define F2_CLK_HIGHSPEED         (U32)10000000
#define TMRA_UNIT_HIGHSPEED       (U8)(100 - 1)	/* trapre's value */
#define TMRA_INTERVAL_HIGHSPEED   (U8)(((F2_CLK_HIGHSPEED/(U32)1000)/(TMRA_UNIT_HIGHSPEED+(U32)1)) - (U32)1)/* f2 is as count source */

/* timer clock definition when low-speed OCO */
#define F1_CLK_LOWSPEED 		(U32)125000
#define TMRA_UNIT_LOWSPEED       (U8)(25 - 1)	/* trapre's value */
#define TMRA_INTERVAL_LOWSPEED   (U8)(((F1_CLK_LOWSPEED/(U32)40)/(TMRA_UNIT_LOWSPEED+(U32)1)) - (U32)1)/* f1 is as count source */

/* SFR Bit value definition */
#define STOP    0
#define START   1
#define TIMER_MODE               (U8)0x00
#define TMRRA_COUNT_SOURCE_F1    (U8)0x00
#define TMRRA_COUNT_SOURCE_F8    (U8)0x01
#define TMRRA_COUNT_SOURCE_FOCO  (U8)0x02
#define TMRRA_COUNT_SOURCE_F2    (U8)0x03
#define TMRRA_COUNT_SOURCE_F32   (U8)0x04
#define TMRRA_INT_PRIORITY       (U8)0x01

/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/
/*****************************************************************************
 Private variables and functions
 *****************************************************************************/
U32 CurrentTimer = 0;
/*****************************************************************************
 * ID                : 1.0
 * Outline           : Initialize timer RA
 * Include           : none
 * Declaration       : void Drv_Timer0_InitTimer0InHighSpeed(void)
 * Description       : TimerRA is as system timer, in 1ms interval, f2=10MHz
 * Argument          : none
 * Return Value      : none
 * Calling Functions : none
 *****************************************************************************/
void Drv_Timer0_InitTimer0InHighSpeed(void)
{
	/* Drv_INT_DisableInterrupt(); */		/* Disable interrupt */
	/* Set 1ms interval */
	tstart_tracr = STOP;
	tramr = (U8)(TMRRA_COUNT_SOURCE_F2 << 4) + TIMER_MODE;
	trapre = (U8)TMRA_UNIT_HIGHSPEED;
	tra = TMRA_INTERVAL_HIGHSPEED;
	traic = TMRRA_INT_PRIORITY;
	tstart_tracr = START;
	/* Drv_INT_EnableInterrupt(); */		/* Enable interrupt */
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : Initialize timer RA
 * Include           : none
 * Declaration       : void Drv_Timer0_InitTimer0InLowSpeed(void)
 * Description       : TimerRA is as system timer, in 100ms interval, f1=125KHz
 * Argument          : none
 * Return Value      : none
 * Calling Functions : none
 *****************************************************************************/
void Drv_Timer0_InitTimer0InLowSpeed(void)
{
	/* Drv_INT_DisableInterrupt(); */		/* Disable interrupt */
	/* Set 10ms interval */
	tstart_tracr = STOP;
	tramr = (U8)(TMRRA_COUNT_SOURCE_F1 << 4) + TIMER_MODE;
	trapre = (U8)TMRA_UNIT_LOWSPEED;
	tra = TMRA_INTERVAL_LOWSPEED;
	traic = TMRRA_INT_PRIORITY;
	tstart_tracr = START;
	/* Drv_INT_EnableInterrupt(); */		/* Enable interrupt */
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : timer RA interrupt service routine
 * Include           : none
 * Declaration       : void TmrRAInt(void)
 * Description       : 1ms delay.
 * Argument          : none
 * Return Value      : none
 * Calling Functions : none
 *****************************************************************************/
void TmrRAInt(void)
{
	/*CurrentTimer*/
	CurrentTimer++;

	/* *** AE1 task used variable start *** */
	/* AE1-L connect guard timer */
	U32gAE1ConnectGuardTimer++;
	/* Guard timer, AE1 control state machine for every sub-state */
	U16gAE1CtrlGuardTimer++;
	/* Re-send command delay if previous STS parameters is invalid */
	U16gDelayResendCmd++;
	/* Check playback time in cycle loop */
	U16gDelayInCycle ++;
	/* Monitor playback time for switching next file if invalid file exists */
	U16gMonitorPlayTime ++;
	/* *** AE1 task used variable end *** */

	/* Timer counter of scan key */
	U16TimerCountScanKey++;

	/* Timer counter of some 1 key during pressed period */
	U16TimerCountPressedKey++;

	/* Service timer count */
	U16TimerCountService++;
	
	/* Timer counter of peripheral device reset */
	U16TimerCountReset++;

	/* Timer counter of program heartbeat */
	U16TimerCountHeart++;

	/* Timer counter of prepare power down timeout */
	U16TimerCountPreparePowerDown++;

	/* Timer counter of rotary2 speed */
	U16TimerCountRotary2Speed++;

	/* Timer counter of quit set volume interface */
	U16TimerCountQuitSetVolumeInterface++;

	/* Timer counter of quit set folder interface */
	U16TimerCountQuitSetFolderInterface++;

	/* Timer counter of EV power up delay */
	U16TimerCountEVPowerUpDelay++;

	/* system timer */
	vsysFeedTime++;
	vsysMilSecond++;
	if(1000 == vsysMilSecond)
	{
		p8_2 = ~p8_2;
		vsysSecond++;
		vsysMilSecond = 0;

		if(60 == vsysSecond)
		{
			vsysMinute++;
			vsysSecond = 0;

			if(60 == vsysMinute)
			{
				vsysHour++;
				vsysMinute = 0;

				if(24 == vsysHour)
				{
					vsysHour = 0;
				}
			}
		}
	}
}

/* End of file */
