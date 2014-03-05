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
* File Name 	: driver_evolume.h
* Abstract 		: driver of e-volume
* Version 		: Ver 0.10
* Device 		: R8C/2A group, or R8C/2B group
* Tool-Chain 	: High-performance Embedded Workshop (Version 4.08.00.011)
* 				: C Compiler Package for M16C Series M3T-NC30WA(V.5.45 Release 00)
* OS 			: None
* H/W Platform 	: AE1-LF demo board
* Description 	: This is driver of E-volume
* Operation 	: 1. lower layer driver
* Limitation 	: This program can be operated by 20MHz only.
* 				:
*******************************************************************************
* History 		: Dec.16,2010 Ver. 0.10 First Release
* 				:
*******************************************************************************/

/******************************************************************************
Includes <System Includes> , "Project Includes"
******************************************************************************/
#include "basictype.h"
/******************************************************************************
Typedef definitions
******************************************************************************/
/******************************************************************************
Macro definitions
******************************************************************************/
#define EV_DEV_ADDR 		(U8)0x44
/* #define EV_VOL_STEP			(U16)64 */
/* #define EV_SP_ATT_STEP		(U16)32 */

/* range of e-volume */
#define RANGE_VOLUME_MIN 	(S8)0
#define RANGE_VOLUME_MAX 	(S8)63
#define RANGE_VOLUMELF_MIN 	((S8)-15)
#define RANGE_VOLUMELF_MAX 	(S8)15
#define RANGE_VOLUMERF_MIN 	((S8)-15)
#define RANGE_VOLUMERF_MAX 	(S8)15
#define RANGE_VOLUMELR_MIN 	((S8)-15)
#define RANGE_VOLUMELR_MAX 	(S8)15
#define RANGE_VOLUMERR_MIN 	((S8)-15)
#define RANGE_VOLUMERR_MAX 	(S8)15
#define RANGE_BASS_MIN 		((S8)-7)
#define RANGE_BASS_MAX 		(S8)7
#define RANGE_TREBLE_MIN 	((S8)-7)
#define RANGE_TREBLE_MAX 	(S8)7

/* Audio switch, LOUDNESS, and gain */
#define EV_SWITCH_LOUDNESS_GAIN_ADDR	(U8)0x40
#define EV_AUDIO_SWITCH_STEREO1	(U8)0x00
#define EV_AUDIO_SWITCH_STEREO2	(U8)0x01
#define EV_AUDIO_SWITCH_STEREO3	(U8)0x02
#define EV_AUDIO_SWITCH_STEREO4	(U8)0x03
#define EV_LOUDNESS_ON			(U8)0x00
#define EV_LOUDNESS_OFF			(U8)0x04
#define EV_GAIN_11P25_DB		(U8)0x00
#define EV_GAIN_7P5_DB			(U8)0x08
#define EV_GAIN_3P75_DB			(U8)0x10
#define EV_GAIN_0_DB			(U8)0x18

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/
/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
extern StdRetType Drv_EV_SetVolume(S8 Volume);
extern StdRetType Drv_EV_SetVolumeOfLF(S8 Volume);
extern StdRetType Drv_EV_SetVolumeOfRF(S8 Volume);
extern StdRetType Drv_EV_SetVolumeOfLR(S8 Volume);
extern StdRetType Drv_EV_SetVolumeOfRR(S8 Volume);
extern StdRetType Drv_EV_SetAudioInput(U8 InputSource);
extern StdRetType Drv_EV_SetAudioBass(S8 Bass);
extern StdRetType Drv_EV_SetAudioTreble(S8 Treble);

/******************************************************************************
Private global variables and functions
******************************************************************************/

