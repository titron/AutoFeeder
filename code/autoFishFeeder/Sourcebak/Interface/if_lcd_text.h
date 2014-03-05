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
* File Name 	: if_disp_text.h
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
#ifndef __LCD_TEXT_H__
#define __LCD_TEXT_H__
/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/


/*****************************************************************************
 Typedef definitions
 *****************************************************************************/


/*****************************************************************************
 Macro definitions
 *****************************************************************************/
#define FONT24 (U8)24
#define FONT16 (U8)16
#define FONT12 (U8)12

/*ENDIAN*/
#define BIG_ENDIAN (U8)1
#define LITTLE_ENDIAN (U8)0

/*Ico unicode*/
//#define CODE_SPEEK_OFF			0x0081
#define CODE_SPEEK_OFF			"\x81\x00"
//#define CODE_SPEEK_ON			0x0082
#define CODE_SPEEK_ON			"\x82\x00"
//#define CODE_MODE_ORDER			0x0083
#define CODE_MODE_ORDER			"\x83\x00"
//#define CODE_MODE_ALLORDER		0x0084
#define CODE_MODE_ALLORDER		"\x84\x00"
//#define CODE_MODE_LOOP			0x0085
#define CODE_MODE_LOOP			"\x85\x00"
//#define CODE_MODE_SINGLE		0x0086
#define CODE_MODE_ALLLOOP		"\xb2\x00"
#define CODE_MODE_SINGLE		"\x86\x00"
//#define CODE_MODE_RANDOM		0x0087
#define CODE_MODE_RANDOM		"\x87\x00"
//#define CODE_MODE_SCN			0x0088
#define CODE_MODE_SCN			"\x88\x00"
//#define CODE_MODE_PAUSE			0x0089
#define CODE_MODE_PAUSE			"\x89\x00"
//#define CODE_MODE_START			0x008A
#define CODE_MODE_START			"\x8A\x00"
//#define CODE_MODE_SD			0x008B
#define CODE_MODE_SD			"\x8b\x00"
//#define CODE_MODE_SDR			0x008C
#define CODE_MODE_SDR			"\x8c\x00"
//#define CODE_MODE_USB			0x008D
#define CODE_MODE_USB			"\x8d\x00"
//#define CODE_MODE_USBR			0x008E
#define CODE_MODE_USBR			"\x8e\x00"
#define CODE_MODE_CUR			0x008F
//#define CODE_SPACE				0x0080
#define CODE_SPACE				"\x80\x00"
#define CODE_ELLIPSIS			0x0090
#define CODE_FOLDER				0x0091
#define CODE_FILE				0x0092


/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/
extern void LCD_TextW(U16 *code_buf,U16 pos_horizontal,U16 pos_vertical,U8 font);
extern void LCD_TextA(U8 *code_buf,U16 pos_horizontal,U16 pos_vertical,U8 font);
extern void LCD_TextA_Rev(U8 *code_buf,U16 PosX,U16 PosY,U8 font,U8 mode);
extern void LCD_draw_roll(U8 PosX,U8 PosY,U16 * codeBuf,U8 codeNum);
extern void LCD_Draw_TextRoll(U16 *CodeBuf,S16 PosX,U16 PosY,U16 StrWidth);
extern void LCD_Draw_TextRoll24(U8 *CodeBuf,S16 PosX,U16 PosY,U16 StrWidth);
extern U16 GetDrawTextWidthA(U8 *Code,U8 font);
extern void ConvertUnicodeToGBCode(U8 *code,U16 len,U8 flag);
extern void ConvertUTF8ToGBCode(U8 *utf8code,U16 utf8len,U8 *GBcode,U16 GBcodelen);
/*****************************************************************************
 Private variables and functions
 *****************************************************************************/



#endif