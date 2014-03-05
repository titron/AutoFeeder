/******************************************************************************
* DISCLAIMER
*
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized.
* This software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
*
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY,
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY
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
*******************************************************************************/
/* Copyright (C) 2010 Renesas Electronics Corporation. All rights reserved. */
/******************************************************************************
 * System Name  : AutoFeeder
 * File Name    : drv_clk.c
 * Abstract     : interface of key module
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AutoFeeder module
 * Description  : interface of key module
 * Operation    : none
 * Limitation   : none
*******************************************************************************
* History 		: Dec.16,2010 Ver. 0.10 First Release
* 				:
*******************************************************************************/
#ifndef __IF_KEY_H__
#define __IF_KEY_H__

/******************************************************************************
Includes <System Includes> , "Project Includes"
******************************************************************************/
#include "basictype.h"
#include "drv_key.h"

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/
#define KEY_STATE_INIT				(U8)0
#define KEY_STATE_IDLE				(U8)1
#define KEY_STATE_PRESS_JITTER		(U8)2
#define KEY_STATE_PRESS_STABLE		(U8)3
#define KEY_STATE_RESTORE_JITTER 	(U8)4

#define DOWN						(U8)0
#define UP							(U8)1

/* Judge time number of Verified key, when clock is high-speed OCO */
#define KEY_JUDGE_TIMES_HIGHSPEED	(U8)3
/* Judge time number of Verified key, when clock is low-speed OCO */
#define KEY_JUDGE_TIMES_LOWSPEED	(U8)2

/* Key ID */
#define KEY_ROTARY2					(U8)7
#define KEY_ROTARY1					(U8)6
#define KEY_1						(U8)5
#define KEY_2						(U8)4
#define KEY_3						(U8)3
#define KEY_4						(U8)2
#define KEY_5						(U8)1
#define KEY_6						(U8)0

/* Event ID of event type - key */
#define EVENT_KEY_NONE					(U8)0x00
#define EVENT_KEY_ROTARY1_DOWN			(U8)0x01
#define EVENT_KEY_ROTARY2_DOWN			(U8)0x02
#define EVENT_KEY_1_DOWN				(U8)0x03
#define EVENT_KEY_2_DOWN				(U8)0x04
#define EVENT_KEY_3_DOWN				(U8)0x05
#define EVENT_KEY_4_DOWN				(U8)0x06
#define EVENT_KEY_5_DOWN				(U8)0x07
#define EVENT_KEY_6_DOWN				(U8)0x08
#define EVENT_KEY_ROTARY1_UP			(U8)0x09
#define EVENT_KEY_ROTARY2_UP			(U8)0x0A
#define EVENT_KEY_1_UP					(U8)0x0B
#define EVENT_KEY_2_UP					(U8)0x0C
#define EVENT_KEY_3_UP					(U8)0x0D
#define EVENT_KEY_4_UP					(U8)0x0E
#define EVENT_KEY_5_UP					(U8)0x0F
#define EVENT_KEY_6_UP					(U8)0x10
#define EVENT_KEY_ROTARY2_PRESSED_xS	(U8)0x11
#define EVENT_KEY_RKEY1_RKEY2_KEY1_DOWN	(U8)0x12
#define EVENT_KEY_UNDEFINED				(U8)0xFF
/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/
/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
extern U16 U16TimerCountScanKey;
extern U16 U16TimerCountPressedKey;

/* extern void If_Key_InitKey(void); */
extern void if_Key_Scan(void);
extern U8 if_Key_GetState(U8 U8KeyID);
extern U8 if_Key_GetEvent(void);
extern void if_Key_ClearEvent(void);

#endif
/* End of File */
