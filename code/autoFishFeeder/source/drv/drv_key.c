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
 * File Name    : drv_key.h
 * Abstract     : key module header file
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AutoFeeder module
 * Description  : key module
 * Operation    : none
 * Limitation   : none
*******************************************************************************
* History 		: Dec.16,2010 Ver. 0.10 First Release
* 				:
*******************************************************************************/

#include "BasicType.h"
#include "sfr_r82b.h"
#include "drv_key.h"
#include "drv_tmr0.h"

/******************************************************************************
Private global variables and functions
******************************************************************************/

/*****************************************************************************
 * ID                :
 * Outline           : Initialize the Port of Rotary(only key) and Key
 * Include           : none
 * Declaration       : void drv_Key_InitKey(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void drv_Key_InitKey(void)
{
	/* Set the port direction key1-key6, key of rotary1, key of rotary2: input */
	/* Protect off */
	prc2 = (U8)1;
	pd0 = (U8)0x00;		/* P0_0 to P0_7 direction is input */
	pu00 = (U8)1;		/* P0_0 to P0_3 is pull-up */
	pu01 = (U8)1;		/* P0_4 to P0_7 is pull-up */
	/* Protect on */
	prc2 = (U8)0;
}
/* End of File */
