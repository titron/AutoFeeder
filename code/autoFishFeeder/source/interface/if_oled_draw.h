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
* File Name 	: if_disp_draw.h
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
#ifndef __LCD_DRAW_H__
#define __LCD_DRAW_H__
/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/
typedef struct{
	U8 bmp_no;
	U16 bmp_width;
	U16 bmp_hight;
	U8 const * bmp_address;
}BMPINFO;

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
#define BMP_LOGO_NO 					0U
#define BMP_CLOCK_NO 					1U
#define BMP_FISH_NO 					2U

#define PLAY_TIME_PROGRESS_LEN 			100U
#define PLAY_TIME_PROGRESS_HIGHT 		6U
#define PLAY_TIME_PROGRESS_FILL_HIGHT 	4U

#define REDRAW							(U8)0
#define UPDATA							(U8)1
/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/
extern void OLED_DrawLine(U16 PosStartX,U16 PosStartY,U16 PosEndX,U16 PosEndY,U8 col);
extern void OLED_DrawLineT(U16 PosStartX,U16 PosStartY,U16 PosEndX,U16 PosEndY,U8 col);
extern void OLED_DrawDot(U8 PosStartX,U8 PosStartY);
extern void OLED_DrawBox(U16 PosStartX,U16 PosStartY,U16 PosEndX,U16 PosEndY,U8 fill,U8 col1,U8 col2);
extern void OLED_DrawBmp(U16 PosStartX,U16 PosStartY,U8 BmpNo);
extern void Draw_PlayTimeProgressFrame(U16 PosStartX,U16 PosStartY,U16 Progress ,U8 flag);
extern void if_disp_clear(void);

/*****************************************************************************
 Private variables and functions
 *****************************************************************************/
#endif


