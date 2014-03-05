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
 * File Name    : app_menu.h
 * Abstract     : application of user menu and user interface
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AE1-LF demo board
 * Description  : This is application of menu and interface.
 * Operation    : none
 * Limitation   : This file can be only used as sample code for AE1-LF.
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/
#ifndef __APP_MENU_H__
#define __APP_MENU_H__
/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "basictype.h"

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/
typedef struct  
{
	U8 U8Language;
	U8 U8LEDLight;
}t_SettingParameter;

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
/* Menu of Setting */
#define MSET_0_LANGUAGE					(U8)0
#define MSET_0_0_LANGUAGE_SCHINESE		(U8)1
#define MSET_0_1_LANGUAGE_ENGLISH		(U8)2
#define MSET_0_2_LANGUAGE_JAPANESE		(U8)3
#define MSET_0_3_LANGUAGE_KOREA			(U8)4
#define MSET_0_4_LANGUAGE_EXIT			(U8)5
#define MSET_1_SOUND					(U8)6
#define MSET_1_0_SOUND_LF				(U8)7
#define MSET_1_0_0_SOUND_LF_SET			(U8)8
#define MSET_1_1_SOUND_LR				(U8)9
#define MSET_1_1_0_SOUND_LR_SET			(U8)10
#define MSET_1_2_SOUND_RF				(U8)11
#define MSET_1_2_0_SOUND_RF_SET			(U8)12
#define MSET_1_3_SOUND_RR				(U8)13
#define MSET_1_3_0_SOUND_RR_SET			(U8)14
#define MSET_1_4_SOUND_BASS				(U8)15
#define MSET_1_4_0_SOUND_BASS_SET		(U8)16
#define MSET_1_5_SOUND_TREBLE			(U8)17
#define MSET_1_5_0_SOUND_TREBLE_SET		(U8)18
#define MSET_1_6_SOUND_EXIT				(U8)19
#define MSET_2_OLED						(U8)20
#define MSET_2_0_OLED_SETLIGHT			(U8)21
#define MSET_3_FILEINFO					(U8)22
#define MSET_3_0_FILEINFO_DETAIL		(U8)23
#define MSET_4_SYSINFO					(U8)24
#define MSET_4_0_SYSINFO_DETAIL			(U8)25
#define MSET_5_EXIT						(U8)27
/* 1 virtaul menu is used to transit from host_setting to host_play state */
#define MPLAY_EXIT_FROM_SETTING			(U8)28
#define MSET_NUM						(U8)28

#define MSTART_IMAGE_0					(U8)100
#define MPLAY_HOME						(U8)101
#define MPLAY_SET_VOLUME				(U8)102
#define MPLAY_SET_FOLDER				(U8)103
#define MEND_IMAGE_0					(U8)104

/* Menu handle of Setting */
#define MSET_HANDLE_PREVIOUS_ITEM		(U8)0
#define MSET_HANDLE_NEXT_ITEM			(U8)1
#define MSET_HANDLE_IN 					(U8)2
#define MSET_HANDLE_OUT					(U8)3

/* Language */
#define SET_LANGUAGE_0_SIM_CHINESE		(U8)0
#define SET_LANGUAGE_1_ENGLISH			(U8)1
#define SET_LANGUAGE_2_JAPANESE			(U8)2
#define SET_LANGUAGE_3_KOREA			(U8)3

/* Sound */
#define SET_SOUND_LEFT_FRONT			(U8)0
#define SET_SOUND_LEFT_REAR				(U8)1
#define SET_SOUND_RIGHT_FRONT			(U8)2
#define SET_SOUND_RIGHT_REAR			(U8)3

/* Disp menu translated */
#define DISP_MSET_0_HOME				(U8)0
#define DISP_MSET_1_LANGUAGE			(U8)1
#define DISP_MSET_2_SOUND				(U8)2
#define DISP_MSET_3_LEDLIGHT			(U8)3
#define DISP_MSET_4_FILEINFO			(U8)4
#define DISP_MSET_5_SYSINFO				(U8)5
#define DISP_CURSOR_0					(U8)0
#define DISP_CURSOR_1					(U8)1
#define DISP_CURSOR_2					(U8)2
#define DISP_CURSOR_3					(U8)3
#define DISP_CURSOR_4					(U8)4
#define DISP_CURSOR_5					(U8)5
#define DISP_CURSOR_6					(U8)6
#define DISP_CURSOR_7					(U8)7
#define DISP_CURSOR_8					(U8)8
#define DISP_CURSOR_9					(U8)9

/* Setting value range - LED lightness */
#define RANGE_LED_LIGHT_MIN			(S8)0
#define RANGE_LED_LIGHT_MAX			(S8)10

/* Timer count */
#define TIME_QUIT_SET_VOLUME			TIME_1S
#define TIME_QUIT_SET_FOLDER			TIME_5S
/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/
extern U16 U16TimerCountQuitSetVolumeInterface;
extern U16 U16TimerCountQuitSetFolderInterface;
extern t_SettingParameter	TSettingPara;
extern U8 U8InterfaceID;
extern void App_Menu_UpdateUserInterface(U8 U8KeyEvent, S8 S8Rotary1Event, S8 S8Rotary2Event);
extern void TranslateSetMenu(U8 U8LocalMenuID);

#endif
/* End of File */
