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
 * File Name    : driver_timer0.h
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
#ifndef __DRIVER_TIMER0_H__
#define __DRIVER_TIMER0_H__

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "basictype.h"

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
/* Timer counter when timer clock is 20MHz */
#define TIME_1MS	(U16)1
#define TIME_2MS	(U16)2
#define TIME_3MS	(U16)3
#define TIME_4MS	(U16)4
#define TIME_5MS	(U16)5
#define TIME_6MS	(U16)6
#define TIME_7MS	(U16)7
#define TIME_8MS	(U16)8
#define TIME_9MS	(U16)9
#define TIME_10MS	(U16)10
#define TIME_15MS	(U16)15
#define TIME_20MS	(U16)20
#define TIME_25MS	(U16)25
#define TIME_30MS	(U16)30
#define TIME_35MS	(U16)35
#define TIME_40MS	(U16)40
#define TIME_45MS	(U16)45
#define TIME_50MS	(U16)50
#define TIME_55MS	(U16)55
#define TIME_60MS	(U16)60
#define TIME_65MS	(U16)65
#define TIME_70MS	(U16)70
#define TIME_75MS	(U16)75
#define TIME_80MS	(U16)80
#define TIME_85MS	(U16)85
#define TIME_90MS	(U16)90
#define TIME_95MS	(U16)95
#define TIME_100MS	(U16)100
#define TIME_200MS	(U16)200
#define TIME_300MS	(U16)300
#define TIME_400MS	(U16)400
#define TIME_500MS	(U16)500
#define TIME_1S		(U16)1000
#define TIME_2S		(U16)2000
#define TIME_3S		(U16)3000
#define TIME_4S		(U16)4000
#define TIME_5S		(U16)5000

/* Key scan times number when clock is high-speed OCO */
#define TIME_25MS_LOWSPEED	(U16)1
/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/
extern U32 CurrentTimer;
extern void Drv_Timer0_InitTimer0InHighSpeed(void);
extern void Drv_Timer0_InitTimer0InLowSpeed(void);
extern void TmrRAInt(void);
#endif
/* End of file */
