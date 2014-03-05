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
 * File Name    : if_timer.c
 * Abstract     : interface of timer
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AE1-LF demo board
 * Description  : This is interface of timer.
 * Operation    : none
 * Limitation   : This file can be only used as sample code for AE1-LF.
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "sfr_r82b.h"
#include "driver_timer0.h"
#include "driver_timer1.h"
#include "if_timer.h"
/*****************************************************************************
 Private variables and functions
 *****************************************************************************/

/*****************************************************************************
 * ID                : 1.0
 * Outline           : Initialize system timer(timer0) in high-speed cpu
 * Include           : none
 * Declaration       : void If_Timer_InitSysTimerInHighSpeed(void)
 * Description       : Initialize timer0
 * Argument          : none
 * Return Value      : none
 * Calling Functions : none
 *****************************************************************************/
void If_Timer_InitSysTimerInHighSpeed(void)
{
	Drv_Timer0_InitTimer0InHighSpeed();
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : Initialize system timer(timer0) in low-speed cpu
 * Include           : none
 * Declaration       : void If_Timer_InitSysTimerInLowSpeed(void)
 * Description       : Initialize timer
 * Argument          : none
 * Return Value      : none
 * Calling Functions : none
 *****************************************************************************/
void If_Timer_InitSysTimerInLowSpeed(void)
{
	Drv_Timer0_InitTimer0InLowSpeed();
}

#if 0
/*****************************************************************************
 * ID                : 1.0
 * Outline           : Initialize rotary speed timer
 * Include           : none
 * Declaration       : void If_Timer_InitRotarySpeedTimer(void)
 * Description       : Initialize timer
 * Argument          : none
 * Return Value      : none
 * Calling Functions : none
 *****************************************************************************/
void If_Timer_InitRotarySpeedTimer(void)
{
	Drv_Timer1_InitTimer1();
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : Start rotary timer
 * Include           : none
 * Declaration       : void If_Timer_StartRotarySpeedTimer(void)
 * Description       : Start rotary timer
 * Argument          : none
 * Return Value      : none
 * Calling Functions : none
 *****************************************************************************/
void If_Timer_StartRotarySpeedTimer(void)
{
	Drv_Timer1_StartTimer1();
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : Stop rotary timer
 * Include           : none
 * Declaration       : void If_Timer_StopRotarySpeedTimer(void)
 * Description       : Stop rotary timer
 * Argument          : none
 * Return Value      : none
 * Calling Functions : none
 *****************************************************************************/
void If_Timer_StopRotarySpeedTimer(void)
{
	Drv_Timer1_StopTimer1();
}
#endif

/*****************************************************************************
* ID                : 1.0
* Outline           : Initialize the vertical-scroll-screen timer(timer1)
* Include           : none
* Declaration       : void If_Timer1Init(U16 time_us,TRF_TimeoutFuncType Timer)
* Description       : Initialize timer1
* Argument          : none
* Return Value      : none
* Calling Functions : none
*****************************************************************************/
void If_Timer1Init(U32 time_us,TRF_TimeoutFuncType Timer)
{
	U32 TRFCMP1count;
	
	Drv_TimerRF_Stop();
	Drv_TimerRF_Init();

	TRFCMP1count = (time_us*(U32)10)/((U32)F32_TIMER_PERCLOLK/(U32)100);
	Drv_TimerRF_SetCmp1((U16)TRFCMP1count);

	TimerRFFun = Timer;

	Drv_TimerRF_Start();
}

/*****************************************************************************
* ID                : 1.0
* Outline           : Stop the vertical-scroll-screen timer(timer1)
* Include           : none
* Declaration       : void If_Timer1_Stop(void)
* Description       : Stop timer1
* Argument          : none
* Return Value      : none
* Calling Functions : none
*****************************************************************************/
void If_Timer1_Stop(void)
{
	Drv_TimerRF_Stop();
}
