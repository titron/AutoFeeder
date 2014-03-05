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
* System Name	: AE1-LF Car Audio Demo
* File Name 	: driver_rotary.h
* Abstract 		: driver of rotary
* Version 		: Ver 0.10
* Device 		: R8C/2A group, or R8C/2B group
* Tool-Chain 	: High-performance Embedded Workshop (Version 4.08.00.011)
* 				: C Compiler Package for M16C Series M3T-NC30WA(V.5.45 Release 00)
* OS 			: None
* H/W Platform 	: AE1-LF demo board
* Description 	: This is driver of rotary.
* Operation 	: 
* Limitation 	: This program can be operated by 20MHz only.
* 				:
*******************************************************************************
* History 		: Dec.16,2010 Ver. 0.10 First Release
* 				:
*******************************************************************************/
#ifndef __DRIVER_ROTARY_H__
#define __DRIVER_ROTARY_H__

/******************************************************************************
Includes <System Includes> , "Project Includes"
******************************************************************************/
#include "basictype.h"

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/
#define GET_ROTARY1A_STATE()	p3_6
#define GET_ROTARY1B_STATE()	p3_1
#define GET_ROTARY2A_STATE()	p3_2
#define GET_ROTARY2B_STATE()	p3_0

/* State of rotary (Note: These state considers the following condition:
   1. use only 1 external INT to implement
   2. rotary is 1 pulse with 4 detents. ) */
#define ROTARY_STATE_IDLE						(U8)0
#define ROTARY_STATE_CLOCKWISE_AB_00			(U8)1
#define ROTARY_STATE_CLOCKWISE_AB_11			(U8)2
#define ROTARY_STATE_ANTICLOCKWISE_AB_01		(U8)11
#define ROTARY_STATE_ANTICLOCKWISE_AB_10		(U8)12

#define ROTARY_1PULSE_2DETENT	0
#define ROTARY_1PULSE_4DETENT	1
/* Note: ROTARY_1PULSE_2DETENT is not implemented */
#define ROTARY_1PULSE_DETENT_NO	ROTARY_1PULSE_4DETENT

#define ROTARY2_SPEED_COUNT_MAX	(S16)0x7FFF

#if 0
#define SINGLE_INT_USED			0
#define DOUBLE_INT_USED			1
#define INT_USED_MODE			SINGLE_INT_USED
#endif
/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/
/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
extern S8 S8Rotary1Counter;
extern S8 S8Rotary2Counter;
extern S16 S16Rotary2SpeedTimerCount;
extern U16 U16TimerCountRotary2Speed;
extern void Drv_Rotary_InitRotary(void);
extern void Drv_rotary1_1AINTInt(void);
extern void Drv_rotary1_1BINT1Int(void);
extern void Drv_rotary2_2AINTInt(void);
extern void Drv_rotary2_2BINT3Int(void);
#endif
/* End of File */
