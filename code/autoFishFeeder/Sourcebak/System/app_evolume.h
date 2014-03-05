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
 * File Name    : app_evolume.h
 * Abstract     : application of e-volume
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AE1-LF demo board
 * Description  : This is application of e-volume.
 * Operation    : none
 * Limitation   : This file can be only used as sample code for AE1-LF.
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/
#ifndef __APP_EVOLUME_H__
#define __APP_EVOLUME_H__
/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "basictype.h"

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/* Message type of evolume */ 
#define		EV_MESSAGE					U16
#define		EV_MSG_NULL 				(EV_MESSAGE)0x0000
#define		EV_MSG_VOLUME				(EV_MESSAGE)0x0001			
#define		EV_MSG_VOLUME_LR			(EV_MESSAGE)0x0002	
#define		EV_MSG_VOLUME_RR			(EV_MESSAGE)0x0004	
#define		EV_MSG_VOLUME_LF			(EV_MESSAGE)0x0008	
#define		EV_MSG_VOLUME_RF			(EV_MESSAGE)0x0010		
#define		EV_MSG_MUTE					(EV_MESSAGE)0x0020	
#define		EV_MSG_AUDIOSWITCH			(EV_MESSAGE)0x0040	
#define		EV_MSG_BASS					(EV_MESSAGE)0x0080	
#define		EV_MSG_TREBLE				(EV_MESSAGE)0x0100	
#define 	EV_MSG_NUMBER				(U8)10

typedef struct{
	S8 S8Volume;				/* Volume, Range: 0-63, step is 1 */
	S8 S8VolumeLR;				/* Speaker ATT LR, Range: -15-+15, step is 1 */
	S8 S8VolumeRR;				/* Speaker ATT RR, Range: -15-+15, step is 1 */
	S8 S8VolumeLF;				/* Speaker ATT LF, Range: -15-+15, step is 1 */
	S8 S8VolumeRF;				/* Speaker ATT RF, Range: -15-+15, step is 1 */
	U8 U8Mute;					/* Mute, 0-not mute, 1-mute */
	U8 U8SwitchLoudGain;			/* Loudness of stereo n (n=1-4) */
	S8 S8Bass;					/* Bass, Unit: 2.0 dB, Range: -7-+7, step is 1 */
	S8 S8Treble;				/* Treble, Unit: 2.0 dB, Range: -7-+7, step is 1 */
}t_EVData;

typedef struct{
	S8 S8DataDelta;
	EV_MESSAGE EVMessage;
}t_MsgHostToEV;

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
/* Device state */
#define EV_STATE_INIT					(U8)0
#define EV_STATE_POWERDOWN				(U8)1	
#define EV_STATE_POWERUP				(U8)2
#define EV_STATE_POWERUP_DELAY			(U8)3
#define EV_STATE_INIT1_VOLUME			(U8)4
#define EV_STATE_INIT2_VOLUMELR			(U8)5
#define EV_STATE_INIT3_VOLUMERR			(U8)6
#define EV_STATE_INIT4_VOLUMELF			(U8)7
#define EV_STATE_INIT5_VOLUMERF			(U8)8
#define EV_STATE_INIT6_AUDIOSWITCH		(U8)9
#define EV_STATE_INIT7_BASS				(U8)10
#define EV_STATE_INIT8_TREBLE			(U8)11
#define EV_STATE_OPERATION				(U8)12
#define EV_STATE_POWERDOWN_PREPARE		(U8)13	  

/* Default volume(Note: when gain = 7.5dB) */
#define DEFAULT_VOLUME		            (S8)2
#define DEFAULT_VOLUME_LF				(S8)9
#define DEFAULT_VOLUME_LR				(S8)9
#define DEFAULT_VOLUME_RF				(S8)9
#define DEFAULT_VOLUME_RR				(S8)9
#define DEFAULT_VOLUME_BASS				(S8)3
#define DEFAULT_VOLUME_TREBLE			(S8)3
#define DEFAULT_SWITCH_LOUD_GAIN	(EV_SWITCH_LOUDNESS_GAIN_ADDR |	EV_AUDIO_SWITCH_STEREO1 |EV_LOUDNESS_OFF |EV_GAIN_7P5_DB)
/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/
extern U8 U8EVState;
extern t_MsgHostToEV	TMsgHostToEV;
extern t_EVData			TEVData;
extern U16 U16TimerCountEVPowerUpDelay;
extern void App_EV_InitEVolumeData(void);
#endif
/* End of File */
