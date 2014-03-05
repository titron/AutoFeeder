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
/******************************************************************************
* System Name	: AE1-LF Car Audio Demo
* File Name 	: if_disp.h
* Abstract 		: interface of disp
* Version 		: Ver 0.10
* Device 		: R8C/2A group, or R8C/2B group, or 78K0 group
* Tool-Chain 	: High-performance Embedded Workshop (Version 4.08.00.011)
* 				: C Compiler Package for M16C Series M3T-NC30WA(V.5.45 Release 00)
* OS 			: None
* H/W Platform 	: AE1-LF demo board
* Description 	: This is interface of disp.
* Operation 	: 
* Limitation 	: This program can be operated by 20MHz only.
*******************************************************************************
* History 		: Dec.16,2010 Ver. 0.10 First Release
* 				:
*******************************************************************************/
#ifndef __IF_DISP_H__
#define __IF_DISP_H__
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
#define DISP_ROLL_END	(U8)0
#define DISP_ROLL_ING	(u8)1

#define DISP_SCREEN_START_LINE (U8)0
#define DISP_SCREEN_HALFT_LINE (U8)64
/*****************************************************************************
Imported global variables and functions (from other files)
*****************************************************************************/

/*****************************************************************************
Exported global variables and functions (to be accessed by other files)
*****************************************************************************/
extern void If_Disp_Init( void );
extern void If_Disp_PowerDown( void );
extern void If_Disp_SetRoll(U8 upline,U8 downline,U8 downup ,U16 interva);
extern void If_Disp_RollEnd( void );
extern void If_Disp_SetStartLine(U8 line);
extern U8 DispRollEnd;

#endif
/* End of File */