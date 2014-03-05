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
 * File Name    : drv_led.h
 * Abstract     : led module header file
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AutoFeeder module
 * Description  : led module header file
 * Operation    : none
 * Limitation   : none
*******************************************************************************
* History 		: Dec.16,2010 Ver. 0.10 First Release
* 				:
*******************************************************************************/
#ifndef __DRV_LED_H__
#define __DRV_LED_H__

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
#define PORT_LED1			p8_0
#define PORT_LED2			p8_1
#define PORT_LED3			p8_2
#define PORT_LED4			p8_3
#define PORT_DIRECTION_LED1	pd8_0
#define PORT_DIRECTION_LED2	pd8_1
#define PORT_DIRECTION_LED3	pd8_2
#define PORT_DIRECTION_LED4	pd8_3

#define LED_ON		(U8)0
#define LED_OFF		(U8)1

#define LED1		(U8)0
#define LED2		(U8)1
#define LED3		(U8)2
#define LED4		(U8)3

/* led */
#define LED_POWER	LED1		/* On-Power on , Off-Power off */
#define LED_HEART   LED2		/* Heart beat every 1 second */
/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
extern void drv_Led_InitLed(void);
extern void drv_Led_SetState(U8 U8LedNo, U8 U8LedState);
#endif
/* End of File */
