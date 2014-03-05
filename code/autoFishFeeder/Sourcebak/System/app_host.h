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
 * File Name    : app_host.h
 * Abstract     : application of host
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AE1-LF demo board
 * Description  : This is application of host.
 * Operation    : none
 * Limitation   : This file can be only used as sample code for AE1-LF.
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/
#ifndef __APP_HOST_H__
#define __APP_HOST_H__
/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "basictype.h"

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/
typedef struct{
	U8 U8Pause;
	U8 U8RepeatMode;
	U8 U8EnableRandom;
	U8 U8EnableScan;
	U8 U8Media;
}t_PlayState;

/* 2/3: Host to EVolume message. 
   (Note: Validity of parameters is guaranteed in EV module) */

/* 3/3: Host to Display message */
typedef struct{
	U8 U8MenuID;
	U8 U8CursorIndex;						/* Cursor index if any */
	S16 S16Rotary2SpeedTimerCount;
}t_MsgHostToDisplay;

/* Software version */
typedef struct{
	U8 U8MainNo;	/* When the whole software structure is changed, or add the multi-module */
	U8 U8SubNo;		/* When functions are added or modified */
	U8 U8ReviseNo;  /* When some little buggs are modified */
	U32 U32Date;	/* 0xAABBCCDD: AA-year, BB-month, CC-day DD-reserve */
}t_SoftwareVersion;
/*****************************************************************************
 Macro definitions
 *****************************************************************************/
/* Device state */
#define HOST_STATE_INIT						(U8)0
#define HOST_STATE_PREPARE_PERIPHERAL_POWERDOWN		(U8)1
#define HOST_STATE_PERIPHERAL_POWERDOWN		(U8)2
#define HOST_STATE_MCU_LOW_POWER			(U8)3
#define HOST_STATE_PERIPHERAL_POWERUP		(U8)4
#define HOST_STATE_RESETING					(U8)5
#define HOST_STATE_PLAY						(U8)6
#define HOST_STATE_SETTING					(U8)7
#define HOST_STATE_TEST						(U8)8

/* Repeat mode */
#define REPEAT_MODE1_SINGLE_1FOLDER			(U8)0
#define REPEAT_MODE2_CYCLE_1FOLDER			(U8)1
#define REPEAT_MODE3_SINGLE_FILE			(U8)2
#define REPEAT_MODE4_SINGLE_ALLFOLDER		(U8)3
#define REPEAT_MODE5_CYCLE_ALLFOLDER		(U8)4

/* Heartbeat display state */
#define STATE_HEART_INIT					(U8)0
#define STATE_HEART_SHRINK					(U8)1
#define STATE_HEART_EXTEND					(U8)2

/* Overtime of host */
#define TIME_RESET_PERIPHERAL_DEVICE		TIME_10MS
#define TIMEOUT_PREPARE_POWER_DOWN			TIME_5S

/* Parameter storage state(flash version) */
#define STORE_FLASH_0_IDLE					(U8)0
#define STORE_FLASH_1_UNPROTECTSECTOR		(U8)1
#define STORE_FLASH_2_ERASE_BLOCK			(U8)2
#define STORE_FLASH_3_ERASEING				(U8)3
#define STORE_FLASH_4_WRITE_DATA1			(U8)4
#define STORE_FLASH_5_PROGRAMMING_DATA1		(U8)5
#define STORE_FLASH_6_WRITE_DATA2			(U8)6
#define STORE_FLASH_7_PROGRAMMING_DATA2		(U8)7
#define STORE_FLASH_8_WRITE_DATA3			(U8)8
#define STORE_FLASH_9_PROGRAMMING_DATA3		(U8)9
#define STORE_FLASH_10_WRITE_DATA4			(U8)10
#define STORE_FLASH_11_PROGRAMMING_DATA4	(U8)11
#define STORE_FLASH_12_WRITE_DATA5			(U8)12
#define STORE_FLASH_13_PROGRAMMING_DATA5	(U8)13
#define STORE_FLASH_14_PROTECTSECTOR		(U8)14
#define STORE_FLASH_15_END					(U8)15

/* Parameter storage state(eeprom version) */
/*  Still not implmented */

/* Software version */
#define SOFT_VERSION_MAIN_NO				(U8)1
#define SOFT_VERSION_SUB_NO					(U8)1
#define SOFT_VERSION_REVISE_NO				(U8)0
#define SOFT_VERSION_DATE					(U32)0x0B0A1C00
/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/
extern U8 U8HostState;
extern U16 U16TimerCountHeart;
extern U16 U16TimerCountReset;
extern U16 U16TimerCountPreparePowerDown;
extern t_MsgHostToDisplay	TMsgHostToDisplay;
extern t_PlayState			TPlayState;
extern t_SoftwareVersion	TSoftVersion;
#endif
/* End of File */
