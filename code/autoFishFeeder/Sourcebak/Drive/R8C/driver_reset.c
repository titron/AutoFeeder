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
* File Name 	: driver_reset.c
* Abstract 		: driver of reset
* Version 		: Ver 0.10
* Device 		: R8C/2A group, or R8C/2B group
* Tool-Chain 	: High-performance Embedded Workshop (Version 4.08.00.011)
* 				: C Compiler Package for M16C Series M3T-NC30WA(V.5.45 Release 00)
* OS 			: None
* H/W Platform 	: AE1-LF demo board
* Description 	: This is driver of reset.
* Operation 	: 
* Limitation 	: This program can be operated by 20MHz only.
* 				:
*******************************************************************************
* History 		: Dec.16,2010 Ver. 0.10 First Release
* 				:
*******************************************************************************/
#include "BasicType.h"
#include "sfr_r82b.h"
#include "driver_reset.h"

/******************************************************************************
Macro definitions
******************************************************************************/
/* High reset control port */
#define PORT_RESET_H			p3_7
#define PORT_DIRECTION_RESET_H	pd3_7
/* Low reset control port */
#define PORT_RESET_L			p1_0
#define PORT_DIRECTION_RESET_L	pd1_0

/*****************************************************************************
 * ID                :
 * Outline           : Initialize the port of reset
 * Include           : none
 * Declaration       : void Drv_Reset_InitPowerControl(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Drv_Reset_InitResetPort(void)
{
	PORT_RESET_H = LOW;
	PORT_DIRECTION_RESET_H = 1 ;		/* Direction output */
	PORT_RESET_H = LOW;
	PORT_RESET_L = HIGH;
	PORT_DIRECTION_RESET_L = 1 ;		/* Direction output */
	PORT_RESET_L = HIGH;
}

#if 0
/*****************************************************************************
 * ID                :
 * Outline           : Output reset high signal
 * Include           : none
 * Declaration       : void Drv_Reset_OutputHighReset(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Drv_Reset_OutputHighReset(U8 U8State)
{
	PORT_RESET_H = U8State ;
}
#endif

/*****************************************************************************
 * ID                :
 * Outline           : Output reset low signal
 * Include           : none
 * Declaration       : void Drv_Reset_OutputLowReset(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Drv_Reset_OutputLowReset(U8 U8State)
{
	PORT_RESET_L = U8State ;
}

/* End of File */
