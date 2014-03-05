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
* File Name 	: driver_power.c
* Abstract 		: driver of power control
* Version 		: Ver 0.10
* Device 		: R8C/2A group, or R8C/2B group
* Tool-Chain 	: High-performance Embedded Workshop (Version 4.08.00.011)
* 				: C Compiler Package for M16C Series M3T-NC30WA(V.5.45 Release 00)
* OS 			: None
* H/W Platform 	: AE1-LF demo board
* Description 	: This is driver of power control.
* Operation 	: 
* Limitation 	: This program can be operated by 20MHz only.
* 				:
*******************************************************************************
* History 		: Dec.16,2010 Ver. 0.10 First Release
* 				:
*******************************************************************************/
#include "BasicType.h"
#include "sfr_r82b.h"
#include "driver_power.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define PORT_POWER_12V_CTRL				p6_1
#define PORT_DIRECTION_POWER_12V_CTRL	pd6_1
#define PORT_POWER_5V_CTRL				p3_3
#define PORT_DIRECTION_POWER_5V_CTRL	pd3_3
#define PORT_POWER_3P3V_CTRL			p6_2
#define PORT_DIRECTION_POWER_3P3V_CTRL	pd6_2

/*****************************************************************************
 * ID                :
 * Outline           : Initialize the port of power control
 * Include           : none
 * Declaration       : void Drv_Power_InitPowerControl(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Drv_Power_InitPowerControl(void)
{
	PORT_POWER_12V_CTRL = LOW;
	PORT_DIRECTION_POWER_12V_CTRL = 1;		/* Direction output */
	PORT_POWER_12V_CTRL = LOW;

	PORT_POWER_5V_CTRL = LOW;
	PORT_DIRECTION_POWER_5V_CTRL = 1;		/* Direction output */
	PORT_POWER_5V_CTRL = LOW;

	PORT_POWER_3P3V_CTRL = HIGH;
	PORT_DIRECTION_POWER_3P3V_CTRL = 1 ;		/* Direction output */
	PORT_POWER_3P3V_CTRL = HIGH;
}

/*****************************************************************************
 * ID                :
 * Outline           : Turn off the 12V power supply of peripheral device 
 * Include           : none
 * Declaration       : void Drv_Power_12V_TurnOff(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Drv_Power_12V_TurnOff(void)
{
	PORT_POWER_12V_CTRL = LOW ;
}

/*****************************************************************************
 * ID                :
 * Outline           : Turn off the 5V power supply of peripheral device 
 * Include           : none
 * Declaration       : void Drv_Power_5V_TurnOff(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Drv_Power_5V_TurnOff(void)
{
	PORT_POWER_5V_CTRL = LOW ;
}

/*****************************************************************************
 * ID                :
 * Outline           : Turn off the 3.3V power supply of peripheral device 
                     : except MCU
 * Include           : none
 * Declaration       : void Drv_Power_3P3V_TurnOff(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Drv_Power_3P3V_TurnOff(void)
{
	PORT_POWER_3P3V_CTRL = HIGH ;
}

/*****************************************************************************
 * ID                :
 * Outline           : Turn on the 12V power supply of peripheral device 
 * Include           : none
 * Declaration       : void Drv_Power_12V_TurnOn(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Drv_Power_12V_TurnOn(void)
{
	PORT_POWER_12V_CTRL = HIGH;
}

/*****************************************************************************
 * ID                :
 * Outline           : Turn on the 5V power supply of peripheral device 
 * Include           : none
 * Declaration       : void Drv_Power_5V_TurnOn(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Drv_Power_5V_TurnOn(void)
{
	PORT_POWER_5V_CTRL = HIGH ;
}	

/*****************************************************************************
 * ID                :
 * Outline           : Turn on the 3.3V power supply of peripheral device
 * Include           : none
 * Declaration       : void Drv_Power_3P3V_TurnOn(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Drv_Power_3P3V_TurnOn(void)
{
	PORT_POWER_3P3V_CTRL = LOW ;
}

/*****************************************************************************
 * ID                :
 * Outline           : Set the port state for low power
 * Include           : none
 * Declaration       : void Drv_Power_SetPortForLowPower(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Drv_Power_SetPortForLowPower(void)
{
	/* P0 - key input, not change */
	/* Note:
       1. Do not remove the internal pull-up from key1-key6 and key of rotary1/2
          because key scan will used these state!!!
    */

	/* P1 */
    /* Note: 1. p1_0 is reset-.
			 2. p1_4 is TXD0, p1_5 is RXD0, and p1_6 is CLK0
    */
	smd0_u0mr = 0;	/* p1_4, p1_5, P1_6 as GPIO */
	smd1_u0mr = 0;
	smd2_u0mr = 0;
	p1 = 0x00;
	pd1  = 0xFF;
	p1 = 0x00;

	/* P2 */
	p2 = 0x00;
	pd2  = 0xFF;
	p2 = 0x00;

	/* P3 */
	/* Note:
       1. p3_0, p3_1, p3_2 and p3_6 are encoder phase port
       2. p3_3 is 5V power control, 5V is power off when p3_3 is low
       3. p3_4 and p3_5 are iic port 
       4. p3_7 is reset+ port 
    */
	pu06 = 0;		/* p3_0 to p3_3 are not internally pulled-up */
	pu07 = 0;		/* p3_4 to p3_7 are not internally pulled-up */
	int2en = 0;		/* p3_2 disable the external INT2 */
	ice_iccr1 = 0;  /* p3_4, p3_5 - iic is halted */
	int1en = 0;		/* p3_6 disable the external INT1 */
	p3 = 0x00;
	pd3  = 0xFF;
	p3 = 0x00;

	/* P4 */	
	/* Note:
       1. p4_0 to p4_2 are unavailable, only can set 0b.
       2. pd4_0 to pd4_2, pd4_6 to pd4_7 are unavailable, only can set 0b(input mode).
    */
	p4 = 0x00;
	pd4  = 0x38;
	p4 = 0x00;

	/* P5 */
	/* Note:
       1. p5_5 to p5_7 are reserved, only can set 0b.
       2. pd5_5 to pd5_7 are reserved, only can set 0b(input mode).
    */
	p5 = 0x00;
	pd5  = 0x1f;
	p5 = 0x00;

	/* P6 */
	/* Note:
       1. p6_1 is 12V power control, 12V is power off when low 
       2. p6_2 is 3.3V power control, 3.3V is power off when high!!! 
	   3. p6_3 is TXD2, p6_4 is RXD2, and p6_5 is CLK2
    */
	smd0_u2mr = 0;	/* p6_3, p6_4, p6_5 as GPIO */
	smd1_u2mr = 0;
	smd2_u2mr = 0;
	p6 = 0x04;
	pd6  = 0xff;
	p6 = 0x04;

	/* P8 */
	/* Note:
       1. p8_7 is reserved, only can set 0b.
       2. pd8_7 is reserved, only can set 0b.
    */
	p8 = 0x00;
	pd8  = 0x7f;
	p8 = 0x00;
}

/* End of File */