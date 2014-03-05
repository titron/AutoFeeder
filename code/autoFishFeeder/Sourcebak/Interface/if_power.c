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
* File Name 	: if_power.c
* Abstract 		: interface of power control
* Version 		: Ver 0.10
* Device 		: R8C/2A group, or R8C/2B group, or 78K0 group
* Tool-Chain 	: High-performance Embedded Workshop (Version 4.08.00.011)
* 				: C Compiler Package for M16C Series M3T-NC30WA(V.5.45 Release 00)
* OS 			: None
* H/W Platform 	: AE1-LF demo board
* Description 	: This is interface of power control.
* Operation 	:
* Limitation 	: This program can be operated by 20MHz only.
*******************************************************************************
* History 		: Dec.16,2010 Ver. 0.10 First Release
* 				:
*******************************************************************************/
#include "BasicType.h"
#include "sfr_r82b.h"
#include "driver_power.h"
#include "driver_clock.h"
#include "if_power.h"

/*****************************************************************************
 * ID                :
 * Outline           : Initialize the port of power control
 * Include           : none
 * Declaration       : void If_Power_InitPowerControl(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void If_Power_InitPowerControl(void)
{
	/* Initialize the power control */
	Drv_Power_InitPowerControl();

	/* Power is supplied for peripheral module */
	Drv_Power_12V_TurnOff();
	Drv_Power_5V_TurnOff();
	Drv_Power_3P3V_TurnOff();
}

/*****************************************************************************
 * ID                :
 * Outline           : Turn off the power supply of peripheral module except MCU
 * Include           : none
 * Declaration       : void If_Power_TurnOff(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void If_Power_TurnOff(void)
{
	Drv_Power_12V_TurnOff();
	Drv_Power_5V_TurnOff();
	Drv_Power_3P3V_TurnOff();
}

void If_Power_5V_TurnOff(void)
{
	Drv_Power_5V_TurnOff();
}
void If_Power_5V_TurnOn(void)
{
	Drv_Power_5V_TurnOn();
}

/*****************************************************************************
 * ID                :
 * Outline           : Turn on the power supply of screen device
 * Include           : none
 * Declaration       : void If_Power_Screen_TurnOn(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void If_Power_Screen_TurnOn(void)
{
	Drv_Power_12V_TurnOn();
}

/*****************************************************************************
 * ID                :
 * Outline           : Turn on the power supply of peripheral module except 
                     : display device
 * Include           : none
 * Declaration       : void If_Power_TurnOn(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void If_Power_TurnOn(void)
{
//	Drv_Power_5V_TurnOn();
	Drv_Power_5V_TurnOff();
	Drv_Power_3P3V_TurnOn();
}

/*****************************************************************************
 * ID                :
 * Outline           : Set port state for low power
 * Include           : none
 * Declaration       : void If_Power_SetPortForLowPower(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void If_Power_SetPortForLowPower(void)
{
	Drv_Power_SetPortForLowPower();
}

/* End of File */
