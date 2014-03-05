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
* System Name  : Program of AE1-L Demo.
* File Name    : driver_lcd.h
* Abstract     : driver (lcd) header file.
* Version      : 0.01
* Device       : R8C/2A group, or R8C/2B group
* Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
*              : Renesas M16C Standard Toolchain (V5.45.01)
* OS           : none
* H/W Platform : AE1-L demo board
* Description  : This is the header file of lcd module.
* Operation    : none
* Limitation   : This file can be only used as sample code for AE1-L.
*****************************************************************************
* History      : Dec.15,2010 Ver. 0.01 First Release
*****************************************************************************/
#ifndef __DRAW_PLAY_H__
#define __DRAW_PLAY_H__
/*****************************************************************************
Includes   <System Includes> , "Project Includes"
*****************************************************************************/


/*****************************************************************************
Typedef definitions
*****************************************************************************/
/* Draw play state */
typedef enum{
	DISP_PLAY_INIT = 0,
	DISP_PLAY_UPDATA,
	DISP_PLAY_ROLLTITLE,
}DSIP_PLAY_STATE;

/*****************************************************************************
Macro definitions
*****************************************************************************/

/*****************************************************************************
Imported global variables and functions (from other files)
*****************************************************************************/

/*****************************************************************************
Exported global variables and functions (to be accessed by other files)
*****************************************************************************/
extern void Draw_play(void);
/*****************************************************************************
Private variables and functions
*****************************************************************************/



#endif
