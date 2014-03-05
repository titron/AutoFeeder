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
* File Name 	: if_rotary.c
* Abstract 		: interface of rotary
* Version 		: Ver 0.10
* Device 		: R8C/2A group, or R8C/2B group, or 78K0 group
* Tool-Chain 	: High-performance Embedded Workshop (Version 4.08.00.011)
* 				: C Compiler Package for M16C Series M3T-NC30WA(V.5.45 Release 00)
* OS 			: None
* H/W Platform 	: AE1-LF demo board
* Description 	: This is interface of rotary.
* Operation 	: 
* Limitation 	: This program can be operated by 20MHz only.
*******************************************************************************
* History 		: Dec.16,2010 Ver. 0.10 First Release
* 				:
*******************************************************************************/
#include "BasicType.h"
#include "sfr_r82b.h"
#include "driver_timer0.h"
#include "if_rotary.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/

/*****************************************************************************
 * ID                :
 * Outline           : Initialize the port of rotary
 * Include           : none
 * Declaration       : void If_Rotary_InitRotary(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void If_Rotary_InitRotary(void)
{
	Drv_Rotary_InitRotary();
}

/*****************************************************************************
 * ID                :
 * Outline           : Get the rotary1 event
 * Include           : none
 * Declaration       : S8 If_Rotary_GetRotary1Event(void)
 * Description       : Get the rotary1 event.
 * Argument          :
 * Return Value      : negative - anti_clockwise count,
 *                     0 - no rotation,
 *                     positive - clockwise count
 * Calling Functions :
 *****************************************************************************/
S8 If_Rotary_GetRotary1Event(void)
{
	return S8Rotary1Counter;
}

/*****************************************************************************
 * ID                :
 * Outline           : Get the rotary2 event
 * Include           : none
 * Declaration       : S8 If_Rotary_GetRotary2Event(void)
 * Description       : Get the rotary2 event.
 * Argument          :
 * Return Value      : rotary2 event
 * Calling Functions :
 *****************************************************************************/
S8 If_Rotary_GetRotary2Event(void)
{
	return S8Rotary2Counter;
}

/*****************************************************************************
 * ID                :
 * Outline           : Get the rotary2 speed
 * Include           : none
 * Declaration       : S16 If_Rotary_GetRotary2SpeedTimerCount(void)
 * Description       : Get the rotary2 speed. This speed is timer count between 
                     : 2 sequentail valid rotary-pulse in unit-100us.
 * Argument          :
 * Return Value      : Timer count of rotary2 speed. 0 is invalid.  
 * Calling Functions :
 *****************************************************************************/
S16 If_Rotary_GetRotary2SpeedTimerCount(void)
{
	return S16Rotary2SpeedTimerCount;
}

/*****************************************************************************
 * ID                :
 * Outline           : Clear the rotary1 event
 * Include           : none
 * Declaration       : void If_Rotary_ClearRotary1Event(void)
 * Description       : Clear the rotary1 event.
 * Argument          :
 * Return Value      : negative - anti_clockwise count,
 *                     0 - no rotation,
 *                     positive - clockwise count
 * Calling Functions :
 *****************************************************************************/
void If_Rotary_ClearRotary1Event(void)
{
	S8Rotary1Counter = (S8)0;
}

/*****************************************************************************
 * ID                :
 * Outline           : Clear the rotary2 event
 * Include           : none
 * Declaration       : void If_Rotary_ClearRotary2Event(void)
 * Description       : Clear the rotary2 event.
 * Argument          :
 * Return Value      : negative - anti_clockwise count,
 *                     0 - no rotation,
 *                     positive - clockwise count
 * Calling Functions :
 *****************************************************************************/
void If_Rotary_ClearRotary2Event(void)
{
	S8Rotary2Counter = (S8)0;
}
/* End of File */
