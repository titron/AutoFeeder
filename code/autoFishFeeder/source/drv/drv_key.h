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
 * File Name    : drv_key.c
 * Abstract     : key routine
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
#ifndef __DRV_KEY_H__
#define __DRV_KEY_H__

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
#define GET_KEY_STATE()				p0
#define KEY_INIT_VALUE				(U8)0xFF

#define KEY_VALUE_NULL				(U8)0xFF
#define KEY_VALUE_ROTARY2			(U8)0x7F
#define KEY_VALUE_ROTARY1			(U8)0xBF
#define KEY_VALUE_6					(U8)0xDF
#define KEY_VALUE_5					(U8)0xEF
#define KEY_VALUE_4					(U8)0xF7
#define KEY_VALUE_3					(U8)0xFB
#define KEY_VALUE_2					(U8)0xFD
#define KEY_VALUE_1					(U8)0xFE
#define KEY_VALUE_RKEY1_RKEY2_KEY1	(U8)0x3E
/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/
/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
extern void drv_Key_InitKey(void);

#endif
/* End of File */
