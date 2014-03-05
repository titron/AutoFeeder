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
 * File Name    : app_menu.c
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

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "if_key.h"
#include "if_rotary.h"
#include "driver_timer0.h"
#include "app_menu.h"
#include "app_host.h"
#include "app_evolume.h"
#include "app_ae1.h"
#include "disp_widget.h"
#include "service_general.h"

/*****************************************************************************
 Private variables and functions
 *****************************************************************************/
/* Setting Menu shift table */
const U8 U8SetMenuTable[MSET_NUM][3] = {
/* Previous             		Next	  			        Enter	*/			   
{MSET_0_LANGUAGE, 				MSET_1_SOUND,  				MSET_0_0_LANGUAGE_SCHINESE},
{MSET_0_0_LANGUAGE_SCHINESE,  	MSET_0_1_LANGUAGE_ENGLISH,  MSET_0_0_LANGUAGE_SCHINESE},
{MSET_0_0_LANGUAGE_SCHINESE, 	MSET_0_4_LANGUAGE_EXIT,  	MSET_0_1_LANGUAGE_ENGLISH},
{MSET_0_1_LANGUAGE_ENGLISH ,	MSET_0_3_LANGUAGE_KOREA,    MSET_0_2_LANGUAGE_JAPANESE},/* reserve for japanese language item */
{MSET_0_2_LANGUAGE_JAPANESE,    MSET_0_4_LANGUAGE_EXIT,     MSET_0_3_LANGUAGE_KOREA},	/* reserve for korea language item */
{MSET_0_1_LANGUAGE_ENGLISH,     MSET_0_4_LANGUAGE_EXIT,     MSET_0_LANGUAGE},
{MSET_0_LANGUAGE, 				MSET_2_OLED,      			MSET_1_0_SOUND_LF},
{MSET_1_6_SOUND_EXIT,  			MSET_1_1_SOUND_LR,       	MSET_1_0_0_SOUND_LF_SET},
{MSET_1_0_0_SOUND_LF_SET, 		MSET_1_0_0_SOUND_LF_SET, 	MSET_1_0_SOUND_LF},
{MSET_1_0_SOUND_LF, 			MSET_1_2_SOUND_RF,  		MSET_1_1_0_SOUND_LR_SET},
{MSET_1_1_0_SOUND_LR_SET,    	MSET_1_1_0_SOUND_LR_SET,   	MSET_1_1_SOUND_LR},
{MSET_1_1_SOUND_LR,    			MSET_1_3_SOUND_RR,   		MSET_1_2_0_SOUND_RF_SET},
{MSET_1_2_0_SOUND_RF_SET,    	MSET_1_2_0_SOUND_RF_SET,   	MSET_1_2_SOUND_RF},
{MSET_1_2_SOUND_RF,    			MSET_1_6_SOUND_EXIT,   		MSET_1_3_0_SOUND_RR_SET},
{MSET_1_3_0_SOUND_RR_SET, 		MSET_1_3_0_SOUND_RR_SET,   	MSET_1_3_SOUND_RR},
{MSET_1_3_SOUND_RR, 			MSET_1_5_SOUND_TREBLE,   	MSET_1_4_0_SOUND_BASS_SET},	/* reserve for bass item */
{MSET_1_4_0_SOUND_BASS_SET, 	MSET_1_4_0_SOUND_BASS_SET,  MSET_1_4_SOUND_BASS},		/* reserve for bass set */
{MSET_1_4_SOUND_BASS, 			MSET_1_5_SOUND_TREBLE,   	MSET_1_5_0_SOUND_TREBLE_SET},/* reserve for treble item */
{MSET_1_5_0_SOUND_TREBLE_SET, 	MSET_1_5_0_SOUND_TREBLE_SET,MSET_1_5_SOUND_TREBLE},		/* reserve for treble set */
{MSET_1_3_SOUND_RR,   			MSET_1_0_SOUND_LF,      	MSET_1_SOUND},
{MSET_1_SOUND,    				MSET_3_FILEINFO,       		MSET_2_0_OLED_SETLIGHT},
{MSET_2_0_OLED_SETLIGHT,    	MSET_2_0_OLED_SETLIGHT,     MSET_2_OLED},
{MSET_2_OLED,    				MSET_4_SYSINFO,       		MSET_3_0_FILEINFO_DETAIL},
{MSET_3_0_FILEINFO_DETAIL,    	MSET_3_0_FILEINFO_DETAIL,   MSET_3_FILEINFO},
{MSET_3_FILEINFO,    			MSET_5_EXIT,       			MSET_4_0_SYSINFO_DETAIL},
{MSET_4_0_SYSINFO_DETAIL,    	MSET_4_0_SYSINFO_DETAIL,    MSET_4_SYSINFO},
{MSET_4_SYSINFO,    			MSET_5_EXIT,    			MPLAY_EXIT_FROM_SETTING},
/* Note: The following MPLAY_EXIT_FROM_SETTING will be used as host state management!!! */	
{MSET_4_SYSINFO,    			MSET_5_EXIT,    			MPLAY_EXIT_FROM_SETTING},			
};

/*  Disp translate table*/
const U8 U8SetMenuTranslate[MSET_NUM][2] = {
{DISP_MSET_0_HOME, 			DISP_CURSOR_0},
{DISP_MSET_1_LANGUAGE, 		DISP_CURSOR_0},
{DISP_MSET_1_LANGUAGE, 		DISP_CURSOR_1},
{DISP_MSET_1_LANGUAGE, 		DISP_CURSOR_2},		/* reserve for japanese */
{DISP_MSET_1_LANGUAGE, 		DISP_CURSOR_3},		/* reserve for korea */
{DISP_MSET_1_LANGUAGE, 		DISP_CURSOR_2},
{DISP_MSET_0_HOME, 			DISP_CURSOR_1},
{DISP_MSET_2_SOUND, 		DISP_CURSOR_0},
{DISP_MSET_2_SOUND, 		DISP_CURSOR_0},
{DISP_MSET_2_SOUND, 		DISP_CURSOR_1},
{DISP_MSET_2_SOUND, 		DISP_CURSOR_1},
{DISP_MSET_2_SOUND,	 		DISP_CURSOR_2},
{DISP_MSET_2_SOUND, 		DISP_CURSOR_2},
{DISP_MSET_2_SOUND, 		DISP_CURSOR_3},
{DISP_MSET_2_SOUND, 		DISP_CURSOR_3},
{DISP_MSET_2_SOUND, 		DISP_CURSOR_4},		/* reserve for bass */
{DISP_MSET_2_SOUND, 		DISP_CURSOR_4},		/* reserve for bass */
{DISP_MSET_2_SOUND, 		DISP_CURSOR_5},		/* reserve for treble */
{DISP_MSET_2_SOUND, 		DISP_CURSOR_5},		/* reserve for treble */
{DISP_MSET_2_SOUND, 		DISP_CURSOR_4},
{DISP_MSET_0_HOME, 			DISP_CURSOR_2},
{DISP_MSET_3_LEDLIGHT, 		DISP_CURSOR_0},
{DISP_MSET_0_HOME, 			DISP_CURSOR_3},
{DISP_MSET_4_FILEINFO, 		DISP_CURSOR_0},
{DISP_MSET_0_HOME, 			DISP_CURSOR_4},
{DISP_MSET_5_SYSINFO, 		DISP_CURSOR_0},
{DISP_MSET_0_HOME, 			DISP_CURSOR_5},
{DISP_MSET_0_HOME, 			DISP_CURSOR_5},
};

/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/
U16 U16TimerCountQuitSetVolumeInterface = (U16)0;
U16 U16TimerCountQuitSetFolderInterface = (U16)0;
t_SettingParameter	TSettingPara;
U8	U8InterfaceID;

/*****************************************************************************
 * ID                :
 * Outline           : Task of menu&interface management
 * Include           : none
 * Declaration       : void App_Menu_UpdateUserInterface(U8 U8KeyEvent, 
                                S8 S8Rotary1Event, S8 S8Rotary2Event)
 * Description       : Task of menu management
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void App_Menu_UpdateUserInterface(U8 U8KeyEvent, S8 S8Rotary1Event, 
                         S8 S8Rotary2Event)
{
	U8 	U8TempInterfaceID;
	S8  S8Value;
	S8	S8_i;

	switch(U8HostState){
	case HOST_STATE_PERIPHERAL_POWERDOWN:
		/* do nothing */
		break;
	case HOST_STATE_PERIPHERAL_POWERUP:
		U8InterfaceID = MSTART_IMAGE_0;		/* reserve for start image */
		break;
	case HOST_STATE_RESETING:
		break;
	case HOST_STATE_PLAY:
		switch(U8InterfaceID){
		case MPLAY_EXIT_FROM_SETTING:
			if(U8KeyEvent == EVENT_KEY_ROTARY2_UP){
				U8InterfaceID = MPLAY_HOME;
			}
			break;
		case MPLAY_HOME:
			if(S8Rotary1Event != EVENT_ROTARY_NONE){
				U8InterfaceID = MPLAY_SET_VOLUME;
				U16TimerCountQuitSetVolumeInterface = (U16)0;
				DispMessage |= DISP_MSG_VOLUME_SHOW_HIDE;
			    /* Note: Set message after real entity is changed in EV module*/
				/* DispMessage |= DISP_MSG_VOLUME_CHANGE; */
			}
			/* Only in play(not pause) mode, folder interface can display  */
			if(U8KeyEvent == EVENT_KEY_ROTARY2_UP){
				if(TPlayState.U8Pause == OFF){
					U8InterfaceID = MPLAY_SET_FOLDER;
					U16TimerCountQuitSetFolderInterface = (U16)0;
					DispMessage |= DISP_MSG_FOLDER_SHOW_HIDE; 
				}
			}
			break;
		case MPLAY_SET_VOLUME:
			/* When rotation continues, clear the time-out count */
			if(S8Rotary1Event != EVENT_ROTARY_NONE){
				U16TimerCountQuitSetVolumeInterface = (U16)0;
			}
			/* When time-out, user interface transits MPLAY_HOME */	
			if(U16TimerCountQuitSetVolumeInterface >= TIME_QUIT_SET_VOLUME){
				U8InterfaceID = MPLAY_HOME;
				DispMessage |= DISP_MSG_VOLUME_SHOW_HIDE;
			}			
			break;
		case MPLAY_SET_FOLDER:
			/* When rotation continues, clear the time-out count */
			if(S8Rotary2Event != EVENT_ROTARY_NONE){
				U16TimerCountQuitSetFolderInterface = (U16)0;
			}
			/* When time-out, user interface transits MPLAY_HOME */			
			if( (U16TimerCountQuitSetFolderInterface >= TIME_QUIT_SET_FOLDER) ||
                (U8KeyEvent == EVENT_KEY_ROTARY2_UP) ){
				U8InterfaceID = MPLAY_HOME;
				DispMessage |= DISP_MSG_FOLDER_SHOW_HIDE; 
			}
			break;
		default:
			break;
		}
		break;
	case HOST_STATE_SETTING:
		switch(U8KeyEvent){
		case EVENT_KEY_NONE:
			break;
		case EVENT_KEY_ROTARY2_DOWN:		/* Enter */
			U8TempInterfaceID = U8InterfaceID;
			U8InterfaceID = U8SetMenuTable[U8InterfaceID][MSET_HANDLE_IN];
			
			/*  Send message to update the display */ 
			if(U8InterfaceID !=  U8TempInterfaceID){
				TranslateSetMenu(U8InterfaceID);
				DispMessage |= DISP_MSG_MENU_ITEM;				
			}

			/* The following interface id need some specific handle */
			switch(U8InterfaceID){
			case MSET_0_0_LANGUAGE_SCHINESE:
				/* For chinese language(1st item), change only when chinese 
                   language  */
				if(U8TempInterfaceID == MSET_0_0_LANGUAGE_SCHINESE){ 
					if(TSettingPara.U8Language != SET_LANGUAGE_0_SIM_CHINESE){
						TSettingPara.U8Language = SET_LANGUAGE_0_SIM_CHINESE;
						DispMessage |= DISP_MSG_MENU_ITEM_CHANGE;
					}
				}
				break;
			case MSET_0_1_LANGUAGE_ENGLISH:
				if(TSettingPara.U8Language != SET_LANGUAGE_1_ENGLISH){
					TSettingPara.U8Language = SET_LANGUAGE_1_ENGLISH;
					DispMessage |= DISP_MSG_MENU_ITEM_CHANGE;
				}
				break;
			case MSET_0_2_LANGUAGE_JAPANESE:
				if(TSettingPara.U8Language != SET_LANGUAGE_2_JAPANESE){
					TSettingPara.U8Language = SET_LANGUAGE_2_JAPANESE;
					DispMessage |= DISP_MSG_MENU_ITEM_CHANGE;
				}
				break;
			case MSET_0_3_LANGUAGE_KOREA:
				if(TSettingPara.U8Language != SET_LANGUAGE_3_KOREA){
					TSettingPara.U8Language = SET_LANGUAGE_3_KOREA;
					DispMessage |= DISP_MSG_MENU_ITEM_CHANGE;
				}
				break;
			case MSET_4_0_SYSINFO_DETAIL:
				/* Send message to get the AE1 firmware info */
				TMsgHostToAE1.AE1Message |= AE1_MSG_READ_FIRMWARE_VERSION;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

		if(S8Rotary2Event != EVENT_ROTARY_NONE){
			if(If_Key_GetState(KEY_ROTARY2) == UP){
				/* Shift the menu */
				U8TempInterfaceID = U8InterfaceID;
				if(S8Rotary2Event > (S8)0){		/* Next item */
					for(S8_i=(S8)0; S8_i<S8Rotary2Event; S8_i++){	/* LHM comment: Only 1 are fetched? */
						U8InterfaceID = U8SetMenuTable[U8InterfaceID][MSET_HANDLE_NEXT_ITEM];
					}
				}else{							/* Previous item */
					for(S8_i=(S8)0; S8_i>S8Rotary2Event; S8_i--){	/* LHM comment: Only 1 are fetched? */
						U8InterfaceID = U8SetMenuTable[U8InterfaceID][MSET_HANDLE_PREVIOUS_ITEM];
					}
				}

				/* When scroll to the new menu, set the message to display */
				if(U8InterfaceID !=  U8TempInterfaceID){
					TranslateSetMenu(U8InterfaceID);
					DispMessage |= DISP_MSG_MENU_ITEM_CHANGE;
				}

				/* If set value in menu, set the value. And rewrite the message 
                   type if need */
				switch(U8InterfaceID){
#if 0
				case MSET_0_0_LANGUAGE_SCHINESE:
					TSettingPara.U8Language = SET_LANGUAGE_0_SIM_CHINESE;
				break;
				case MSET_0_1_LANGUAGE_ENGLISH:
					TSettingPara.U8Language = SET_LANGUAGE_1_ENGLISH;
				break;
				case MSET_0_2_LANGUAGE_JAPANESE:
					TSettingPara.U8Language = SET_LANGUAGE_2_JAPANESE;
					break;
				case MSET_0_3_LANGUAGE_KOREA:
					TSettingPara.U8Language = SET_LANGUAGE_3_KOREA;
					break;
#endif
				case MSET_1_0_0_SOUND_LF_SET:	/* Set LeftFront message */
					TMsgHostToEV.S8DataDelta += S8Rotary2Event;
					TMsgHostToEV.EVMessage |= EV_MSG_VOLUME_LF;
					DispMessage |= DISP_MSG_MENU_ITEM_REDRAW;
					break;
				case MSET_1_1_0_SOUND_LR_SET:	/* Set LeftRear message */
					TMsgHostToEV.S8DataDelta += S8Rotary2Event;
					TMsgHostToEV.EVMessage |= EV_MSG_VOLUME_LR;
					DispMessage |= DISP_MSG_MENU_ITEM_REDRAW;
					break;
				case MSET_1_2_0_SOUND_RF_SET:	/* Set RightFront message */
					TMsgHostToEV.S8DataDelta += S8Rotary2Event;
					TMsgHostToEV.EVMessage |= EV_MSG_VOLUME_RF;
					DispMessage |= DISP_MSG_MENU_ITEM_REDRAW;
					break;
				case MSET_1_3_0_SOUND_RR_SET:	/* Set RightRear message */
					TMsgHostToEV.S8DataDelta += S8Rotary2Event;
					TMsgHostToEV.EVMessage |= EV_MSG_VOLUME_RR;
					DispMessage |= DISP_MSG_MENU_ITEM_REDRAW;
					break;
				case MSET_2_0_OLED_SETLIGHT:		/* Set Led light message */
					S8Value = (S8)TSettingPara.U8LEDLight;
					S8Value += S8Rotary2Event;
					Service_Gene_LimitS8(&S8Value, RANGE_LED_LIGHT_MIN, RANGE_LED_LIGHT_MAX);
					TSettingPara.U8LEDLight = (U8)S8Value;
					DispMessage |= DISP_MSG_MENU_ITEM_REDRAW;
					break;
				default:
					break;
				}
			}else{
				
			}
		}
		break;
	case HOST_STATE_TEST:

		break;
	default:
		break;
	}
}

/*****************************************************************************
 * ID                :
 * Outline           : TranslateSetMenu
 * Include           : none
 * Declaration       : TranslateSetMenu(U8 U8LocalMenuID)
 * Description       : Translate menu ID to the menu ID which can be identified 
 *                       by Display module
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void TranslateSetMenu(U8 U8LocalMenuID)
{
	TMsgHostToDisplay.U8MenuID = U8SetMenuTranslate[U8LocalMenuID][0];
	TMsgHostToDisplay.U8CursorIndex = U8SetMenuTranslate[U8LocalMenuID][1];
}
