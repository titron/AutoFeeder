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
* File Name    : driver_timer1.h
* Abstract     : driver of timer RF (used as folder vertical scroll timer)
* Version      : 1.00
* Device       : R8C/2A group, or R8C/2B group
* Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
*              : Renesas M16C Standard Toolchain (V5.45.01)
* OS           : none
* H/W Platform : AE1-LF demo board
* Description  : This is driver of folder vertical scrolltimer implemented by 
               : timer RF.
* Operation    : none
* Limitation   : This file can be only used as sample code for AE1-LF.
*****************************************************************************
* History      : May.15,2011 Ver. 1.00 First Release
*****************************************************************************/
#ifndef __DRIVER_TIMER1_H__
#define __DRIVER_TIMER1_H__

/*****************************************************************************
Includes   <System Includes> , "Project Includes"
*****************************************************************************/
#include "basictype.h"

/*****************************************************************************
Typedef definitions
*****************************************************************************/
typedef void (* TRF_TimeoutFuncType)(void);
/*****************************************************************************
Macro definitions
*****************************************************************************/
/* Timer counter when timer clock is 20MHz */
#define F1_CLK        (U32)20000000
#define F8_TIMER_PERCLOLK (U16)400
#define F1_TIMER_PERCLOLK (U16)50
#define F32_TIMER_PERCLOLK (U16)1600


/*****************************************************************************
Imported global variables and functions (from other files)
*****************************************************************************/

/*****************************************************************************
Exported global variables and functions (to be accessed by other files)
*****************************************************************************/
extern TRF_TimeoutFuncType TimerRFFun;
extern void Drv_TimerRF_Init(void);
extern void Drv_TimerRF_Start(void);
extern void Drv_TimerRF_Stop(void);
extern void Drv_TimerRF_SetCmp1(U16 cmp1);
extern void TmrRFInt(void);
#endif
/* End of file */
