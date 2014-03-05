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
* File Name 	: driver_rotary.c
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

#include "BasicType.h"
#include "sfr_r82b.h"
#include "driver_int.h"
#include "driver_timer0.h"
#include "driver_rotary.h"

/******************************************************************************
Macro definitions
******************************************************************************/
/* #define DEBUG_ROTARY_ON 1 */
/******************************************************************************
Private global variables and functions
******************************************************************************/
static U8 U8StateMachineRotary1 = ROTARY_STATE_IDLE;
static U8 U8StateMachineRotary2 = ROTARY_STATE_IDLE;
/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
S8 S8Rotary1Counter = (S8)0;
S8 S8Rotary2Counter = (S8)0;
/* S16 S16Rotary1Speed = (S16)0; */
S16 S16Rotary2SpeedTimerCount = (S16)0;
U16 U16TimerCountRotary2Speed = (U16)0;

#ifdef DEBUG_ROTARY_ON
U8 U8SpeedIndex = 0;
S16 S16SpeedTimerCountBuff[16] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
#endif

/*****************************************************************************
 * ID                :
 * Outline           : Initialize the Port of Rotary A/B phase
 * Include           : none
 * Declaration       : void Drv_Rotary_InitRotary(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Drv_Rotary_InitRotary(void)
{
	/* Initialise the external INTi used by 1A and 2A */ 
	Drv_INT_InitExternalINT();

	pu06 = 1;	/* p3_0 to p3_3 are internally pulled up */
	pd3_1 = 0;	/* 1B - input port */
	pd3_0 = 0;	/* 2B - input port */

	/* Initialise the variable */
	S8Rotary1Counter = (S8)0;
	S8Rotary2Counter = (S8)0;
	U8StateMachineRotary1 = ROTARY_STATE_IDLE;
	U8StateMachineRotary2 = ROTARY_STATE_IDLE;
}

/*****************************************************************************
 * ID                :
 * Outline           : rotary1A disposal is by INT0 interrupt
 * Include           : none
 * Declaration       : void Drv_rotary1_1AINTInt(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions : Timer interrupt
 *****************************************************************************/
void Drv_rotary1_1AINTInt(void)
{
#if ROTARY_1PULSE_DETENT_NO == ROTARY_1PULSE_2DETENT

#elif ROTARY_1PULSE_DETENT_NO == ROTARY_1PULSE_4DETENT
	U8 U8CurRotary1AValue;
	U8 U8CurRotary1BValue;

	U8CurRotary1AValue = GET_ROTARY1A_STATE();
	U8CurRotary1BValue = GET_ROTARY1B_STATE();

	switch(U8StateMachineRotary1){
	case ROTARY_STATE_IDLE:
		if((U8CurRotary1AValue == (U8)0) && (U8CurRotary1BValue == (U8)0)){
			U8StateMachineRotary1 = ROTARY_STATE_CLOCKWISE_AB_00;
		}else if((U8CurRotary1AValue == (U8)0) && (U8CurRotary1BValue == (U8)1)){
			U8StateMachineRotary1 = ROTARY_STATE_ANTICLOCKWISE_AB_01;
        }else{
			/* do nothing */
		}
		break;
	case ROTARY_STATE_CLOCKWISE_AB_00:
		if((U8CurRotary1AValue == (U8)1) && (U8CurRotary1BValue == (U8)1)){
			/* When AB transits according to 11b->00b->11b, clockwise 
               counter add 1. */
			if(S8Rotary1Counter < (S8)127){
				S8Rotary1Counter++;
			}
			else{
				S8Rotary1Counter = (S8)127;
			}
			/* state to idle */
			U8StateMachineRotary1 = ROTARY_STATE_IDLE;
		}else{
			U8StateMachineRotary1 = ROTARY_STATE_IDLE;
		}
		break;
	case ROTARY_STATE_ANTICLOCKWISE_AB_01:
		if((U8CurRotary1AValue == (U8)1) && (U8CurRotary1BValue == (U8)0)){
			/* When AB transits according to 11b->00b->11b, counterclockwise 
               counter subtract 1. */
			if(S8Rotary1Counter > (S8)(-128)){
				S8Rotary1Counter--;
			}else{
				S8Rotary1Counter = (S8)(-128);
			}
			/* state to idle */
			U8StateMachineRotary1 = ROTARY_STATE_IDLE;
		}else{
			U8StateMachineRotary1 = ROTARY_STATE_IDLE;
		}
		break;
	default:
		break;
	}
#else
	/* error */
#endif
}

#if 0
/*****************************************************************************
 * ID                :
 * Outline           : rotary1B disposal is by INT1 interrupt
 * Include           : none
 * Declaration       : void Drv_rotary1_1BINT1Int(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions : Timer interrupt
 *****************************************************************************/
void Drv_rotary1_1BINT1Int(void)
{
	/* To save 1 INT resource, 1B INT is not used. */
#if ROTARY_1PULSE_DETENT_NO == ROTARY_1PULSE_2DETENT
#elif ROTARY_1PULSE_DETENT_NO == ROTARY_1PULSE_4DETENT
#else
#endif
}
#endif

/*****************************************************************************
 * ID                :
 * Outline           : rotary2A disposal is by INT2 interrupt
 * Include           : none
 * Declaration       : void Drv_rotary2_2AINTInt(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions : Timer interrupt
 *****************************************************************************/
void Drv_rotary2_2AINTInt(void)
{
#if ROTARY_1PULSE_DETENT_NO == ROTARY_1PULSE_2DETENT

#elif ROTARY_1PULSE_DETENT_NO == ROTARY_1PULSE_4DETENT
	U8 U8CurRotary2AValue;
	U8 U8CurRotary2BValue;

	U8CurRotary2AValue = GET_ROTARY2A_STATE();
	U8CurRotary2BValue = GET_ROTARY2B_STATE();

	switch(U8StateMachineRotary2){
	case ROTARY_STATE_IDLE:
		if((U8CurRotary2AValue == (U8)0) && (U8CurRotary2BValue == (U8)0)){
			U8StateMachineRotary2 = ROTARY_STATE_CLOCKWISE_AB_00;
		}else if((U8CurRotary2AValue == (U8)0) && (U8CurRotary2BValue == (U8)1)){
			U8StateMachineRotary2 = ROTARY_STATE_ANTICLOCKWISE_AB_01;
        }else{
			/* do nothing */
		}
		break;
	case ROTARY_STATE_CLOCKWISE_AB_00:
		if((U8CurRotary2AValue == (U8)1) && (U8CurRotary2BValue == (U8)1)){
			/* When AB transits according to 11b->00b->11b, clockwise 
               counter add 1. */
			if(S8Rotary2Counter < (S8)127){
				S8Rotary2Counter++;
			}
			else{
				S8Rotary2Counter = (S8)127;
			}
			/* After 1 valid pulse, record the speed counter(between 2 valid 
               rotary pulse). */
			if(U16TimerCountRotary2Speed <= (U16)ROTARY2_SPEED_COUNT_MAX){
				S16Rotary2SpeedTimerCount = (S16)U16TimerCountRotary2Speed;
			}else{
				S16Rotary2SpeedTimerCount = ROTARY2_SPEED_COUNT_MAX;
			}
			U16TimerCountRotary2Speed = (U16)0;
#ifdef DEBUG_ROTARY_ON
S16SpeedTimerCountBuff[U8SpeedIndex] = S16Rotary2SpeedTimerCount;
U8SpeedIndex++;
if(U8SpeedIndex >= (U8)16){
	U8SpeedIndex = (U8)0;
}
#endif
			/* state to idle */
			U8StateMachineRotary2 = ROTARY_STATE_IDLE;
		}else{
			U8StateMachineRotary2 = ROTARY_STATE_IDLE;
		}
		break;
	case ROTARY_STATE_ANTICLOCKWISE_AB_01:
		if((U8CurRotary2AValue == (U8)1) && (U8CurRotary2BValue == (U8)0)){
			/* When AB transits according to 11b->00b->11b, counterclockwise 
               counter subtract 1. */
			if(S8Rotary2Counter > (S8)(-128)){
				S8Rotary2Counter--;
			}else{
				S8Rotary2Counter = (S8)(-128);
			}
			/* After 1 valid pulse, record the speed counter(between 2 valid 
               rotary pulse). */
			if(U16TimerCountRotary2Speed <= (U16)ROTARY2_SPEED_COUNT_MAX){
				S16Rotary2SpeedTimerCount = (S16)0 - (S16)U16TimerCountRotary2Speed;
			}else{
				S16Rotary2SpeedTimerCount = (S16)0 - ROTARY2_SPEED_COUNT_MAX;
			}
			U16TimerCountRotary2Speed = (U16)0;
#ifdef DEBUG_ROTARY_ON
S16SpeedTimerCountBuff[U8SpeedIndex] = S16Rotary2SpeedTimerCount;
U8SpeedIndex++;
if(U8SpeedIndex >= (U8)16){
	U8SpeedIndex = (U8)0;
}
#endif
			/* state to idle */
			U8StateMachineRotary2 = ROTARY_STATE_IDLE;
		}else{
			U8StateMachineRotary2 = ROTARY_STATE_IDLE;
		}
		break;
	default:
		break;
	}
#else
	/* error */
#endif
}

#if 0
/*****************************************************************************
 * ID                :
 * Outline           : rotary2B disposal is by INT3 interrupt
 * Include           : none
 * Declaration       : void Drv_rotary2_2BINT3Int(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions : Timer interrupt
 *****************************************************************************/
void Drv_rotary2_2BINT3Int(void)
{
	/* To save 1 INT resource, 2B INT is not used. */
#if ROTARY_1PULSE_DETENT_NO == ROTARY_1PULSE_2DETENT
#elif ROTARY_1PULSE_DETENT_NO == ROTARY_1PULSE_4DETENT
#else
#endif
}
#endif

/* End of File */
