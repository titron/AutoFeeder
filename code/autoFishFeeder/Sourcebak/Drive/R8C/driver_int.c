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
* File Name 	: driver_int.c
* Abstract 		: driver of external interrupt
* Version 		: Ver 0.10
* Device 		: R8C/2A group, or R8C/2B group
* Tool-Chain 	: High-performance Embedded Workshop (Version 4.08.00.011)
* 				: C Compiler Package for M16C Series M3T-NC30WA(V.5.45 Release 00)
* OS 			: None
* H/W Platform 	: AE1-LF demo board
* Description 	: This is driver of external interrupt.
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
#include "driver_rotary.h"

#define EXTERNAL_INT_POLARITY_SINGLE_EDGE	(U8)0
#define EXTERNAL_INT_POLARITY_BOTH_EDGES	(U8)1
#define EXTERNAL_INT_FALLING_EDGE			(U8)0	/* Only valid for one edge*/
#define EXTERNAL_INT_RISING_EDGE			(U8)1	/* Only valid for one edge*/

#define EXTERNAL_INT_LEVEL					(U8)0x01

/*****************************************************************************
 * ID                :
 * Outline           : Disable interrupt
 * Include           : none
 * Declaration       : void Drv_INT_DisableInterrupt(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Drv_INT_DisableInterrupt(void)
{
	asm("FCLR I");				/* Disable interrupt */
}

/*****************************************************************************
 * ID                :
 * Outline           : Enable interrupt
 * Include           : none
 * Declaration       : void Drv_INT_EnableInterrupt(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Drv_INT_EnableInterrupt(void)
{
	asm("FSET I");				/* Enable interrupt */
}

/*****************************************************************************
 * ID                :
 * Outline           : Initialise the external interrupt
 * Include           : none
 * Declaration       : void Drv_INT_InitExternalINT(void)
 * Description       : INT1 is used by rotary1A
 *					   INT2 is used by rotary2A
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Drv_INT_InitExternalINT(void)
{
	/* Drv_INT_DisableInterrupt(); */

#if ROTARY_1PULSE_DETENT_NO == ROTARY_1PULSE_2DETENT
	/* Not implemented */
#elif ROTARY_1PULSE_DETENT_NO == ROTARY_1PULSE_4DETENT
	/* INT1  */
	int1sel = 1;        /* INT1 select P3_6 */
	int1en = (U8)1;		/* INT0 enable */
	pu07 = 1;			/* p3_4 to p3_7 are internally pulled up */ 
	pd3_6 = 0;			/* input port */
	int1pl = EXTERNAL_INT_POLARITY_BOTH_EDGES;
	int1f0 = 1;			/* INT input filter select f32 */
	int1f1 = 1;			/* INT input filter select f32 */
	int1ic = EXTERNAL_INT_LEVEL;
	pol_int1ic = EXTERNAL_INT_FALLING_EDGE;

	/* INT2  */
	int2sel = 1;		/* INT2 select p3_2 */
	int2en = (U8)1;		/* INT2 enable */
	pu06 = 1;			/* p3_0 to p3_3 are internally pulled up */ 
	pd3_2 = 0;			/* input port */
	int2pl = EXTERNAL_INT_POLARITY_BOTH_EDGES;
	int2f0 = 1;			/* INT input filter select f32 */
	int2f1 = 1;			/* INT input filter select f32 */
	int2ic = EXTERNAL_INT_LEVEL;
	pol_int2ic = EXTERNAL_INT_FALLING_EDGE;
#else
#endif
	/* Drv_INT_EnableInterrupt(); */
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : INT0 interrupt service routine
 * Include           : none
 * Declaration       : void INT0Int(void)
 * Description       : 
 * Argument          : none
 * Return Value      : none
 * Calling Functions : none
 *****************************************************************************/
void INT0Int(void)
{

}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : INT1 interrupt service routine
 * Include           : none
 * Declaration       : void INT1Int(void)
 * Description       : 
 * Argument          : none
 * Return Value      : none
 * Calling Functions : none
 *****************************************************************************/
void INT1Int(void)
{
	Drv_rotary1_1AINTInt();
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : INT2 interrupt service routine
 * Include           : none
 * Declaration       : void INT2Int(void)
 * Description       : 
 * Argument          : none
 * Return Value      : none
 * Calling Functions : none
 *****************************************************************************/
void INT2Int(void)
{
	Drv_rotary2_2AINTInt();
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : INT3 interrupt service routine
 * Include           : none
 * Declaration       : void INT3Int(void)
 * Description       : 
 * Argument          : none
 * Return Value      : none
 * Calling Functions : none
 *****************************************************************************/
void INT3Int(void)
{

}
/* End of File */
