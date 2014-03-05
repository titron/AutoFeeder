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
* System Name  : AE1-LF Car Audio Demo
* File Name    : disp_msg.c
* Abstract     : application of host
* Version      : 1.00
* Device       : R8C/2A group, or R8C/2B group, or 78K0 group
* Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
*              : Renesas M16C Standard Toolchain (V5.45.01)
* OS           : none
* H/W Platform : AE1-LF demo board
* Description  : This is application of disp.
* Operation    : none
* Limitation   : This file can be only used as sample code for AE1-LF.
*****************************************************************************
* History      : May.15,2011 Ver. 1.00 First Release
*****************************************************************************/

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

/*****************************************************************************
Imported global variables and functions (from other files)
*****************************************************************************/

/*****************************************************************************
Exported global variables and functions (to be accessed by other files)
*****************************************************************************/
const U8 *MsgEn[] = {
	"",					/*0*/
	"Language Select",		/*1*/
	"Sound adjust",			/*2*/
	"Brightness",			/*3*/
	"SETTING",				/*4*/
	"\x9f\xa0",				/*5*/
	"English",				/*6*/
	"Left Front",			/*7*/
	"Left Rear",			/*8*/
	"Right Front",			/*9*/
	"Right Rear",			/*10*/
	"FILE Info",			/*11*/
	"System Info",			/*12*/
	"Folder number:",		/*13*/
	"File number:",			/*14*/
	"Exit",					/*15*/
	"Please insert a media", /*16*/
	"File analyzing...",		 /*17*/
};

const U8 *MsgCh[] = 
{
	"",					/*0*/
	"\x93\x94",				/*1 Language*/
	"\x95\x96\x97\x98",		/*2*/
	"\x99\x9a\x9b\x9c",		/*3*/
	"\x9d\x9e",				/*4*/
	"\x9f\xa0",				/*5*/
	"English",				/*6*/
	"\xa1\xa2",				/*7*/
	"\xa1\xa3",				/*8*/
	"\xa4\xa2",				/*9*/
	"\xa4\xa3",				/*10*/
	"\xa5\xa6\xa7\xa8",		/*11*/
	"\xa9\xaa\xa7\xa8",		/*12*/
	"\xa5\xa6\xaf\xae\x3a",		/*13*/
	"\xa5\xa6\xad\xae\x3a",		/*14*/
	"\xb0\xb1",					/*15*/
	"\xc7\xeb\xb2\xe5\xc8\xeb\xc3\xbd\xcc\xe5", /*16*/
	"\xb7\xd6\xce\xf6\xce\xc4\xbc\xfe\xd6\xd0...",/*17*/
};

const U8 * Aboutinfo[]=
{
	
	"AE1 Mechless Car Audio Demo",
	"Ver. 1.00.00.110515",
	//"RECH R&D Center",
	//"Engineering Support Group,",
	"AAE Team",
	//"Liu Huiming,Dong Tiegang,",
	//"Li Yo",
	//"2011.05",
};

U8 ** Msgstr;
/*****************************************************************************
Private variables and functions
*****************************************************************************/


/* End of file */
