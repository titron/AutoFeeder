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
 * File Name    : drv_led.c
 * Abstract     : led module
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AutoFeeder module
 * Description  : led module
 * Operation    : none
 * Limitation   : none
*******************************************************************************
* History 		: Dec.16,2010 Ver. 0.10 First Release
* 				:
*******************************************************************************/

#include "BasicType.h"
#include "sfr_r82b.h"
#include "drv_led.h"

/*****************************************************************************
 * ID                :
 * Outline           : Initialize the port of led
 * Include           : none
 * Declaration       : void drv_Led_InitLed(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void drv_Led_InitLed(void)
{
	PORT_LED1 = (U8)1;
	PORT_DIRECTION_LED1 = (U8)1;		/* direction is output */
	PORT_LED1 = (U8)1;
	
	PORT_LED2 = (U8)1;
	PORT_DIRECTION_LED2 = (U8)1;		/* direction is output */
	PORT_LED2 = (U8)1;
	
	PORT_LED3 = (U8)1;
	PORT_DIRECTION_LED3 = (U8)1;		/* direction is output */
	PORT_LED3 = (U8)1;

	PORT_LED4 = (U8)1;
	PORT_DIRECTION_LED4 = (U8)1;		/* direction is output */
	PORT_LED4 = (U8)1;
}


/*****************************************************************************
 * ID                :
 * Outline           : Set the led on/off state
 * Include           : none
 * Declaration       : void If_Led_SetLed(U8 U8LedNo, U8 U8LedState)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void drv_Led_SetState(U8 U8LedNo, U8 U8LedState)
{
	switch(U8LedNo)
	{
	case LED1:
		PORT_LED1 = U8LedState;
		break;
	case LED2:
		PORT_LED2 = U8LedState;
		break;
	case LED3:
		PORT_LED3 = U8LedState;
		break;
	case LED4:
		PORT_LED4 = U8LedState;
		break;
	default:
		break;
	}
}

/* End of File */
