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
* File Name    : driver_timer1.c
* Abstract     : driver of timer RF (used as folder vertical scroll timer)
* Version      : 1.00
* Device       : R8C/2A group, or R8C/2B group
* Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
*              : Renesas M16C Standard Toolchain (V5.45.01)
* OS           : none
* H/W Platform : AE1-LF demo board
* Description  : This is driver of folder vertical scrolltimer implemented by 
               : timer RF.
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
#include "driver_timer1.h"
#include "driver_CSI0.h"
#include "driver_led.h"
#include "if_key.h"
#include "if_serial_ae1.h"
#include "app_ae1.h"
#include "app_host.h"
#include "if_led.h"

/*****************************************************************************
Typedef definitions
*****************************************************************************/

/*****************************************************************************
Macro definitions
*****************************************************************************/
/* **** clock source definition**** */
/* **** Bit value definition**** */
#define STOP    0
#define START   1
#define RF_OUTPUT_MODE 1
#define RF_INPUT_MODE  0
#define ENABLE_CLEAR_CMP1 1
#define DISABLE_CLEAR_CMP1 0


/*****************************************************************************
Imported global variables and functions (from other files)
*****************************************************************************/

/*****************************************************************************
Exported global variables and functions (to be accessed by other files)
*****************************************************************************/
TRF_TimeoutFuncType TimerRFFun;
/*****************************************************************************
Private variables and functions
*****************************************************************************/

/*****************************************************************************
* ID                : 1.0
* Outline           : Initialize timer RC
* Include           : none
* Declaration       : void Drv_Timer_InitTimerInHighSpeed(void)
* Description       : TimerRA is as system timer, in 1ms interval, f1=20MHz
* Argument          : none
* Return Value      : none
* Calling Functions : none
*****************************************************************************/
void Drv_TimerRF_Init(void)
{
	/* Drv_INT_DisableInterrupt(); */		/* Disable interrupt */
	/* Set timer RF */
	tstart_trfcr0 = STOP;
	/*f8 */
	tck0_trfcr0 = 0;
	tck1_trfcr0 = 1;

	/*Output compare mode,clear trf when compare 1*/
	tmod_trfcr1 = RF_OUTPUT_MODE;
	cclr_trfcr1 = ENABLE_CLEAR_CMP1;
 
	/*set int level cmpare 1*/
	cmp1ic = 1;

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
void TmrRFInt(void)
{
	if(TimerRFFun){
		TimerRFFun();
	}
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
void Drv_TimerRF_Start(void)
{
	tstart_trfcr0 = START;
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
void Drv_TimerRF_Stop(void)
{
	tstart_trfcr0 = STOP;
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
void Drv_TimerRF_SetCmp1(U16 cmp1)
{
	trfm1 = cmp1;
}

/*****************************************************************************
* ID                : 1.0
* Outline           : timer 
* Include           : none
* Declaration       : void Drv_TimerRF_Set(U16 Timerus)
* Description       : 1ms delay.
* Argument          : none
* Return Value      : none
* Calling Functions : none
*****************************************************************************/
void Drv_TimerRF_Set(U16 cmp1)
{
	trfm1 = cmp1;
}
/* End of file */
