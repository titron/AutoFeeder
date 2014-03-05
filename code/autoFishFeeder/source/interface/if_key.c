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
#include "BasicType.h"
#include "sfr_r82b.h"
#include "if_key.h"
//#include "if_led.h"
#include "drv_tmr0.h"
//#include "app_host.h"

/******************************************************************************
Private global variables and functions
******************************************************************************/
static U8 U8TempKeyValue = KEY_INIT_VALUE;
static U8 U8FilterKeyValue = KEY_INIT_VALUE;
static U8 U8StateMachineScanKey;
static U8 U8ScanTimes;
static U8 U8StatePressJitterSource;
static U8 U8KeyEvent = EVENT_KEY_NONE;
static void SetKeyEvent(U8 U8NewKeyValue, U8 U8OldKeyValue);

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
U16 U16TimerCountScanKey = (U16)0x00;
U16 U16TimerCountPressedKey = (U16)0x00; /* Timer count of 1 key is pressed */

/*****************************************************************************
 * ID                :
 * Outline           : Get the key event
 * Include           : none
 * Declaration       : U8 if_Key_GetEvent(void)
 * Description       :
 * Argument          :
 * Return Value      : key event
 * Calling Functions :
 *****************************************************************************/
U8 if_Key_GetEvent(void)
{
	return U8KeyEvent;
}

/*****************************************************************************
 * ID                :
 * Outline           : Get the key value after filter by software
 * Include           : none
 * Declaration       : U8 if_Key_GetState(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
U8 if_Key_GetState(U8 U8KeyID)
{
	U8 U8Ret = (U8)0x00;
	switch(U8KeyID){
		case KEY_ROTARY1:
			U8Ret = (U8FilterKeyValue>>KEY_ROTARY1) & (U8)0x01;
		break;
		case KEY_ROTARY2:
			U8Ret = (U8FilterKeyValue>>KEY_ROTARY2)& (U8)0x01;
		break;
		case KEY_1:
			U8Ret = (U8FilterKeyValue>>KEY_1)& (U8)0x01;
		break;
		case KEY_2:
			U8Ret = (U8FilterKeyValue>>KEY_2)& (U8)0x01;
		break;
		case KEY_3:
			U8Ret = (U8FilterKeyValue>>KEY_3)& (U8)0x01;
		break;
		case KEY_4:
			U8Ret = (U8FilterKeyValue>>KEY_4)& (U8)0x01;
		break;
		case KEY_5:
			U8Ret = (U8FilterKeyValue>>KEY_5)& (U8)0x01;
		break;
		case KEY_6:
			U8Ret = (U8FilterKeyValue>>KEY_6)& (U8)0x01;
		break;
		default:
		break;
	}
	return U8Ret;
}

/*****************************************************************************
 * ID                :
 * Outline           : Clear the key event
 * Include           : none
 * Declaration       : void if_Key_ClearEvent(void)
 * Description       :
 * Argument          :
 * Return Value      : 
 * Calling Functions :
 *****************************************************************************/
void if_Key_ClearEvent(void)
{
	U8KeyEvent = EVENT_KEY_NONE;
}

/*****************************************************************************
 * ID                :
 * Outline           : Set the key event
 * Include           : none
 * Declaration       : void SetKeyEvent(U8 U8NewKeyValue, U8 U8OldKeyValue)
 * Description       :
 * Argument          :
 * Return Value      : key event
 * Calling Functions :
 *****************************************************************************/
void SetKeyEvent(U8 U8NewKeyValue, U8 U8OldKeyValue)
{
	switch(U8NewKeyValue){
	case KEY_VALUE_ROTARY1:	/* Rotary1 Key */
		if(U8OldKeyValue == KEY_VALUE_NULL){
			U8KeyEvent = EVENT_KEY_ROTARY1_DOWN;
		}
		break;
	case KEY_VALUE_ROTARY2:	/* Rotary2 Key */
		if(U8OldKeyValue == KEY_VALUE_NULL){
			U8KeyEvent = EVENT_KEY_ROTARY2_DOWN;
		}
		break;
	case KEY_VALUE_1:	/* Key 1 */
		if(U8OldKeyValue == KEY_VALUE_NULL){
			U8KeyEvent = EVENT_KEY_1_DOWN;
		}
		break;
	case KEY_VALUE_2:	/* Key 2 */
		if(U8OldKeyValue == KEY_VALUE_NULL){
			U8KeyEvent = EVENT_KEY_2_DOWN;
		}
		break;
	case KEY_VALUE_3:	/* Key 3 */
		if(U8OldKeyValue == KEY_VALUE_NULL){
			U8KeyEvent = EVENT_KEY_3_DOWN;
		}
		break;
	case KEY_VALUE_4:	/* Key 4 */
		if(U8OldKeyValue == KEY_VALUE_NULL){
			U8KeyEvent = EVENT_KEY_4_DOWN;
		}
		break;
	case KEY_VALUE_5:	/* Key 5 */
		if(U8OldKeyValue == KEY_VALUE_NULL){
			U8KeyEvent = EVENT_KEY_5_DOWN;
		}
		break;
	case KEY_VALUE_6:	/* Key 6 */
		if(U8OldKeyValue == KEY_VALUE_NULL){
			U8KeyEvent = EVENT_KEY_6_DOWN;
		}
		break;
	case KEY_VALUE_RKEY1_RKEY2_KEY1:	/* Rotary1 Key + Rotary2 Key + Key1 */
		U8KeyEvent = EVENT_KEY_RKEY1_RKEY2_KEY1_DOWN;
		break;
	case KEY_VALUE_NULL:
		switch(U8OldKeyValue){
			case KEY_VALUE_ROTARY1:
				U8KeyEvent = EVENT_KEY_ROTARY1_UP;
				break;
			case KEY_VALUE_ROTARY2:
				U8KeyEvent = EVENT_KEY_ROTARY2_UP;
				break;
			case KEY_VALUE_1:
				U8KeyEvent = EVENT_KEY_1_UP;
				break;
			case KEY_VALUE_2:
				U8KeyEvent = EVENT_KEY_2_UP;
				break;
			case KEY_VALUE_3:
				U8KeyEvent = EVENT_KEY_3_UP;
				break;
			case KEY_VALUE_4:
				U8KeyEvent = EVENT_KEY_4_UP;
				break;
			case KEY_VALUE_5:
				U8KeyEvent = EVENT_KEY_5_UP;
				break;
			case KEY_VALUE_6:
				U8KeyEvent = EVENT_KEY_6_UP;
				break;
			default:
				U8KeyEvent = EVENT_KEY_UNDEFINED;
				break;
		}
		break;
	default:
		U8KeyEvent = EVENT_KEY_UNDEFINED;
		break;
	}
}

/*****************************************************************************
 * ID                :
 * Outline           : Scan key
 * Include           : none
 * Declaration       : void if_Key_Scan(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void if_Key_Scan(void)
{
	U16 U16TimerCount;
	U8 U8CurKeyValue;	/* current key value */
	U8 U8JudgeTimes;

	U16TimerCount = TIME_10MS;
	U8JudgeTimes = KEY_JUDGE_TIMES_HIGHSPEED;

	if(U16TimerCountScanKey >= U16TimerCount){

		U8CurKeyValue = GET_KEY_STATE();

		switch(U8StateMachineScanKey){

		case KEY_STATE_INIT:
			drv_Key_InitKey();
			U8StateMachineScanKey = KEY_STATE_IDLE;
			break;

		case KEY_STATE_IDLE:
			/* One or many keys are pressed */
			if(U8CurKeyValue != KEY_VALUE_NULL){
				U8ScanTimes = (U8)1;
				U8TempKeyValue = U8CurKeyValue;
				U8StateMachineScanKey = KEY_STATE_PRESS_JITTER;
				U8StatePressJitterSource = KEY_STATE_IDLE;
			}
			break;

		case KEY_STATE_PRESS_JITTER:
			/* Press state does not change in judge period */
			if(U8TempKeyValue == U8CurKeyValue){
				U8ScanTimes++;
				if(U8ScanTimes >= U8JudgeTimes){
					/* Event point 1/3: Add the key event(key pressed) here if 
					 * key-pressed event mechanism is used. */
					SetKeyEvent(U8CurKeyValue, U8FilterKeyValue);
					/* Verified key state */
					U8FilterKeyValue = U8CurKeyValue;
					U8StateMachineScanKey = KEY_STATE_PRESS_STABLE;
					U16TimerCountPressedKey = (U16)0;
				}
			}
			 /* Press state does change in judge period, it is just a dither.*/
			else{
				/* Go back to previous state
				 * ( Note: KEY_STATE_PRESS_JITTER have 2 possible sources:
				 *   1. KEY_STATE_IDLE
				 *   2. KEY_STATE_PRESS_STABLE) */
				U8StateMachineScanKey = U8StatePressJitterSource;
			}
			break;

		case KEY_STATE_PRESS_STABLE:
			if(U8FilterKeyValue != U8CurKeyValue){	/* State is changed in pressed stable period */
				U8TempKeyValue = U8CurKeyValue;
				if(U8CurKeyValue == KEY_VALUE_NULL){/* Judge if restore normal state */
					U8StateMachineScanKey = KEY_STATE_RESTORE_JITTER;
				}
				else{						 		/* Judge if new press state */
					U8ScanTimes = (U8)1;
					U8StateMachineScanKey = KEY_STATE_PRESS_JITTER;
					U8StatePressJitterSource = KEY_STATE_PRESS_STABLE;
				}
			}else{
				/* Event point 2/3: Add the corresponding key event here, if stable 
				 * time event is used. */
				switch(U8FilterKeyValue){
				case KEY_VALUE_ROTARY2:	/* Rotary2 Key */
					if(U16TimerCountPressedKey >= TIME_2S){
						U8KeyEvent = EVENT_KEY_ROTARY2_PRESSED_xS;
					}
					break;	
				default:
					break;
				}			
			}
			break;
		case KEY_STATE_RESTORE_JITTER:
			/* State does not change in restore period */
			if(U8CurKeyValue == (U8)0xFF){
				U8ScanTimes++;
				if(U8ScanTimes >= U8JudgeTimes){
					/* Event point 3/3: Add the key event(key up) here if event
					 * key-up mechanism is used. */
					SetKeyEvent(U8CurKeyValue, U8FilterKeyValue);

					U8FilterKeyValue = U8CurKeyValue;
					U8StateMachineScanKey = KEY_STATE_IDLE;
				}
			}
			/* State does change in judge period, it is just a dither.*/
			else{
				U8StateMachineScanKey = KEY_STATE_PRESS_STABLE;
			}
			break;

		default:
			U8StateMachineScanKey = KEY_STATE_IDLE;
			/* U16ScanKeyTimes = 0; */
			break;
		}

		U16TimerCountScanKey = (U16)0;
	}
}
/* End of File */
