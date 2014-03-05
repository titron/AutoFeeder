/*****************************************************************************
* DISCLAIMER
*
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized.
* This software is owned by Renesas Electronics Corporation and is protected
* under all applicable laws, including copyright laws.
*
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY,
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY
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
*****************************************************************************/
/* Copyright (C) 2010 Renesas Electronics Corporation. All rights reserved.  */
/*****************************************************************************
 * System Name  : AutoFeeder
 * File Name    : drv_oled_port.c
 * Abstract     : OLED port header file
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AutoFeeder module
 * Description  : OLED port header file
 * Operation    : none
 * Limitation   : none
*****************************************************************************
* History      : May.15,2011 Ver. 1.00 First Release
*****************************************************************************/
#ifndef __DRIVER_OLED_PIN_H__
#define __DRIVER_OLED_PIN_H__
/*****************************************************************************
Includes   <System Includes> , "Project Includes"
*****************************************************************************/
#include "basictype.h"

/*****************************************************************************
Typedef definitions
*****************************************************************************/

/*****************************************************************************
Macro definitions
*****************************************************************************/
#define VERSION_2

#ifdef VERSION_2
#define OLED_CS				p5_0		/*Chip Select*/
#define OLED_DC				p5_1		/*Data/Command Control*/
#define OLED_ENABLE			p5_3		/*Read/Write Enable*/
#define OLED_RW   			p5_2		/*Read/Write Select*/
#define OLED_RD 			p5_3			/*Read Signal*/
#define OLED_WR				p5_2		/*Write Signal*/
#define OLED_POWER      	p6_1		/*12V OLED POWER*/
#define OLED_DATA			p2			/*Data bus*/

#define OLED_RESST_D		pd3_7		/*Reset*/
#define OLED_CS_D			pd5_0			/*Chip Select*/
#define OLED_DC_D			pd5_1			/*Data/Command Control*/
#define OLED_ENABLE_D		pd5_3			/*Read/Write Enable*/
#define OLED_RW_D   		pd5_2			/*Read/Write Select*/
#define OLED_RD_D 			pd5_3			/*Read Signal*/
#define OLED_WR_D			pd5_2			/*Write Signal*/
#define OLDE_POWER_D		p6_1		

#define OLED_DATA_D			pd2				/*Data bus*/
#endif

/*****************************************************************************
Imported global variables and functions (from other files)
*****************************************************************************/

/*****************************************************************************
Exported global variables and functions (to be accessed by other files)
*****************************************************************************/

/*****************************************************************************
Private variables and functions
*****************************************************************************/

#endif
/* End of File */
