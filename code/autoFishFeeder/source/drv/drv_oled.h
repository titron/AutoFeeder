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
* File Name    : driver_oled.h
* Abstract     : driver of oled
* Version      : 1.00
* Device       : R8C/2A group, or R8C/2B group
* Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
*              : Renesas M16C Standard Toolchain (V5.45.01)
* OS           : none
* H/W Platform : AE1-LF demo board
* Description  : This is driver of oled.
* Operation    : none
* Limitation   : This file can be only used as sample code for AE1-LF.
*****************************************************************************
* History      : May.15,2011 Ver. 1.00 First Release
*****************************************************************************/
#ifndef __DRIVER_OLED_H__
#define __DRIVER_OLED_H__
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
#define OLED_MAXLINE		(U16)256
#define OLED_MAXROW			(U16)64
#define OLED_CELL_LINE		(U16)4
#define OLED_POWER_ON		(U8)1
#define OLED_POWER_OFF		(U8)0

#define ORIGNAL_POS_X		15
#define ORIGNAL_POS_Y		0
/*****************************************************************************
Imported global variables and functions (from other files)
*****************************************************************************/

/*****************************************************************************
Exported global variables and functions (to be accessed by other files)
*****************************************************************************/

/*****************************************************************************
Private variables and functions
*****************************************************************************/
extern void drv_OLED_Init(void);
extern void drv_OLED_GraphicWrite(U16 AdrHorizontal,U16 AdrVertical,U16 width,U16 high,U8 *GDRAMData ,U16 wnum);
extern void drv_OLED_GraphicWrite_Offset(U16 AdrHorizontal,U16 AdrVertical,U16 width,U16 high,U8 *GDRAMData ,U16 wnum,U8 ColumnStart);
extern void drv_OLED_GraphicRead(U16 AdrHorizontal,U16 AdrVertical,U16 width,U16 high,U8 *GDRAMData ,U16 rnum);
extern void drv_OLED_GraphicWriteWord(U8 AdrVertical,U8 AdrHorizontal,U8 GDRAMDataH ,U8 GDRAMDataL);
extern void drv_OLED_Clear(U8 data);
extern void drv_OLED_DataWrite( U8 data);
extern void drv_OLED_CommandWrite( U8 data);
extern void drv_OLED_DataRead( U8 *data );
extern void drv_OLED_SetColumnAddress(U8 StartAdr, U8 EndAdr);
extern void drv_OLED_SetRowAddress(U8 StartAdr, U8 EndAdr);
extern void drv_OLED_SetWriteRAM( void );
extern void drv_OLED_SetStartLine(U8);
extern void drv_OLED_GraphicLineV(U16 StartX,U16 StartY,U16 Length,U8 Gray);
extern void drv_OLED_GraphicLineVT(U16 StartX,U16 StartY,U16 Length,U8 Gray);
extern void drv_OLED_GraphicLineH(U16 StartX,U16 StartY,U16 Length,U8 Gray);
extern void drv_OLED_GraphicWriteData(U16 AdrHorizontal,U16 AdrVertical,U16 width,U16 high,U8 *GDRAMData ,U16 wnum);
extern void drv_OLED_SetGrayScaleTable(U8 level);
#endif
/* End of File */