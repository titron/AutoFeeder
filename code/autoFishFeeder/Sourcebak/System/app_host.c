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
 * File Name    : app_host.c
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

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "config.h"
#include "driver_timer0.h"
#include "driver_evolume.h"
#include "if_key.h"
#include "if_rotary.h"
#include "if_timer.h"
#include "if_led.h"
#include "if_serial_flash.h"
#include "if_reset.h"
#include "if_power.h"
#include "if_iic.h"
#include "app_key.h"
#include "app_menu.h"
#include "app_host.h"
#include "app_ae1.h"
#include "app_evolume.h"
#include "draw_task.h"
#include "disp_widget.h"
#include "service_general.h"

/*****************************************************************************
 Private variables and functions
 *****************************************************************************/
static U8 U8HeartState = STATE_HEART_INIT;
static U8 U8StoreParameterState = STORE_FLASH_0_IDLE;
static U32 U32StoreStartAddress;
static void App_Host_KeyRotaryEventHandler(U8 U8KeyEvent, S8 S8Rotary1Event, 
                         S8 S8Rotary2Event);
static void InitData(void);
static void App_Host_Heartbeat(void);
static void App_Host_StoreParameter(void);
static BOOLEAN StartStoreParameterTask(void);
static void ReadCarAudioParameter(void);
static U32 GetFinalStoreStartAddress(void);
static U32 GetNextStoreStartAddress(void);
/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/
U8 U8HostState = HOST_STATE_INIT;
U16 U16TimerCountReset = (U16)0;
U16 U16TimerCountHeart = (U16)0;
U16 U16TimerCountPreparePowerDown = (U16)0;
t_MsgHostToDisplay	TMsgHostToDisplay;
t_PlayState			TPlayState;
t_SoftwareVersion	TSoftVersion = {SOFT_VERSION_MAIN_NO, 
                                    SOFT_VERSION_SUB_NO, 
                                    SOFT_VERSION_REVISE_NO, 
                                    SOFT_VERSION_DATE};

/*****************************************************************************
 * ID                :
 * Outline           : App_Task_Host
 * Include           : none
 * Declaration       : void App_Task_Host(void)
 * Description       : Task of host
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
/*****************************************************************************
 * ID                :
 * Outline           : App_Host_KeyRotaryEventHandler
 * Include           : none
 * Declaration       : void App_Host_KeyRotaryEventHandler(void)
 * Description       : Event handler of key and rotary
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void App_Host_KeyRotaryEventHandler(U8 U8KeyEvent, S8 S8Rotary1Event, 
                         S8 S8Rotary2Event)
{
	switch(U8HostState){
	case HOST_STATE_PERIPHERAL_POWERDOWN:
		break;
	case HOST_STATE_PERIPHERAL_POWERUP:
		break;
	case HOST_STATE_RESETING:
		/* do nothing */
		break;
	case HOST_STATE_PLAY:
		switch(U8InterfaceID){
		case MPLAY_HOME:
			switch(U8KeyEvent){
			case EVENT_KEY_NONE:
				break;
			case EVENT_KEY_ROTARY1_DOWN:
			/* Power down disposal in routine 'App_Task_Host' */
				break;
			case EVENT_KEY_ROTARY2_UP:
				break;
			case EVENT_KEY_1_DOWN:
				/* AE1 maintain the play/pause state. */
				TMsgHostToAE1.AE1Message |= AE1_MSG_PLAY_PAUSE;
				break;
			case EVENT_KEY_2_DOWN:
				/* Repeat mode */
				switch(TPlayState.U8RepeatMode){
				case REPEAT_MODE2_CYCLE_1FOLDER:
					TPlayState.U8RepeatMode = REPEAT_MODE3_SINGLE_FILE;
					break;
				case REPEAT_MODE3_SINGLE_FILE:
					TPlayState.U8RepeatMode = REPEAT_MODE5_CYCLE_ALLFOLDER;
					break;
				case REPEAT_MODE5_CYCLE_ALLFOLDER:
					TPlayState.U8RepeatMode = REPEAT_MODE2_CYCLE_1FOLDER;
					break;
				default:
					TPlayState.U8RepeatMode = REPEAT_MODE2_CYCLE_1FOLDER;
					break;
				}
				TMsgHostToAE1.AE1Message |= AE1_MSG_SHIFT_REPEAT;
				break;
			case EVENT_KEY_3_DOWN:
				/* Random or Sequence */
				if(TPlayState.U8EnableRandom == OFF){
					TPlayState.U8EnableRandom = ON;		/* Random */
				}else{
					TPlayState.U8EnableRandom = OFF;	/* Sequence */
				}
				TMsgHostToAE1.AE1Message |= AE1_MSG_RANDOM_SEQUENCE;
				break;
			case EVENT_KEY_4_DOWN:
				/* Scan or normal */
				if(TPlayState.U8EnableScan == OFF){
					TPlayState.U8EnableScan = ON;		/* Scan */
				}else{
					TPlayState.U8EnableScan = OFF;		/* Normal */
				}
				TMsgHostToAE1.AE1Message |= AE1_MSG_SCAN_NORMAL;
				break;
			case EVENT_KEY_5_DOWN:
				TMsgHostToAE1.AE1Message |= AE1_MSG_SHIFT_MEDIA;
				break;
			case EVENT_KEY_RKEY1_RKEY2_KEY1_DOWN:
				/* Device state to 'HOST_STATE_TEST', implement in 
	               'App_Task_Host' */
				break;
			case EVENT_KEY_UNDEFINED:
				break;
			default:
				break;
			}
            break;
        case MPLAY_SET_VOLUME:
			break;
		case MPLAY_SET_FOLDER:
			switch(U8KeyEvent){
			case EVENT_KEY_ROTARY2_UP:
			/* user interface transits in 'App_Menu_UpdateUserInterface' */
				break;
			default:
				break;
			}
			break;
        default:
			break;
		}
			
		/* Handle the rotary1 event */
		if(S8Rotary1Event != EVENT_ROTARY_NONE){
			switch(U8InterfaceID){
			case MPLAY_HOME:
				TMsgHostToEV.S8DataDelta += S8Rotary1Event;
				TMsgHostToEV.EVMessage |= EV_MSG_VOLUME;
				break;
			case MPLAY_SET_VOLUME:	
				TMsgHostToEV.S8DataDelta += S8Rotary1Event;
				TMsgHostToEV.EVMessage |= EV_MSG_VOLUME;
				break;
			case MPLAY_SET_FOLDER:
				/* do nothing */
				break;
			default:
				break;
			}
		}

		/* Handle the rotary2 event */
		if(S8Rotary2Event != EVENT_ROTARY_NONE){
			switch(U8InterfaceID){
			case MPLAY_HOME:
				if(TPlayState.U8Pause == OFF){
					TMsgHostToAE1.S8HostToAE1FileCount += S8Rotary2Event;
				}
				break;
			case MPLAY_SET_VOLUME:	
				/* do nothing */
				break;
			case MPLAY_SET_FOLDER:
				TMsgHostToAE1.S8HostToAE1FolderCount += S8Rotary2Event;
				break;
			default:
				break;
			}
		}
			
		break;
	case HOST_STATE_SETTING:
		/* Event handle of Setting mode is in 'App_Menu_UpdateUserInterface' */
		break;
	case HOST_STATE_TEST:

		break;
	default:
		break;
	}
}

/*****************************************************************************
 * ID                :
 * Outline           : App_Host_Heartbeat
 * Include           : none
 * Declaration       : void App_Host_Heartbeat(void)
 * Description       : Display the program still run(not dead-loop) by LED.
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void App_Host_Heartbeat(void)
{
	VU16 VU16TimerCount;
	
	if(U8HostState != HOST_STATE_MCU_LOW_POWER){
		VU16TimerCount = TIME_1S;
	}else{
		return;
	}

	switch(U8HeartState){
	case STATE_HEART_INIT:
		U16TimerCountHeart = (U16)0;
		U8HeartState = STATE_HEART_SHRINK;
		break;
	case STATE_HEART_SHRINK:
		if(U16TimerCountHeart >= VU16TimerCount){
			U8HeartState = STATE_HEART_EXTEND;
			If_Led_SetState(LED_HEART, LED_ON);		/* LED on */
			U16TimerCountHeart = (U16)0;
		}
		break;
	case STATE_HEART_EXTEND:	
		if(U16TimerCountHeart >= VU16TimerCount){
			U8HeartState = STATE_HEART_SHRINK;
			If_Led_SetState(LED_HEART, LED_OFF);	/* LED off */
			U16TimerCountHeart = (U16)0;
		}
		break;
	default:
		break;
	}
}

/*****************************************************************************
 * ID                :
 * Outline           : InitData
 * Include           : none
 * Declaration       : void InitData(void)
 * Description       : Initial data.
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void InitData(void)
{
	/* play state */
	TPlayState.U8Pause = OFF;
	TPlayState.U8RepeatMode = REPEAT_MODE2_CYCLE_1FOLDER;
	TPlayState.U8EnableScan = OFF;
	TPlayState.U8EnableRandom = OFF;
	TPlayState.U8Media = DEFAULT_MEDIA;

	/* AE1 message */
	/* ToDo: Move to AE1 */
	/* TMsgHostToAE1.AE1Message = AE1_MSG_NULL; */
	/* TMsgHostToAE1.S8HostToAE1FileCount = (S8)0; */
	/* TMsgHostToAE1.S8HostToAE1FolderCount = (S8)0; */
}

/*****************************************************************************
 * ID                :
 * Outline           : Start the store process
 * Include           : none
 * Declaration       : BOOLEAN StartStoreParameterTask(void)
 * Description       : Start the store process once
 * Argument          :
 * Return Value      :  TRUE  - Store have been accepted.
 * 						FALSE - Store is prohibited because still busy.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN StartStoreParameterTask(void)
{
	BOOLEAN U8Ret = TRUE;
	if(U8StoreParameterState == STORE_FLASH_0_IDLE){
		U8StoreParameterState = STORE_FLASH_1_UNPROTECTSECTOR;
	}else{
		U8Ret = FALSE;
	}
	return U8Ret;
}

/*****************************************************************************
 * ID                :
 * Outline           : Read the car audio parameter of ROM
 * Include           : none
 * Declaration       : void ReadCarAudioParameter(void)
 * Description       : Read the car audio parameter of ROM
 * Argument          :
 * Return Value      : none
 * Calling Functions :
 *****************************************************************************/
void ReadCarAudioParameter(void)
{
	U32 U32FinalStoreStartAddress;

	U32FinalStoreStartAddress = GetFinalStoreStartAddress();

	if(U32FinalStoreStartAddress != (U32)0xFFFFFFFF){	/* Valid address */
		/* Read the sound setting data */
		If_Flash_ReadData(U32FinalStoreStartAddress, (U16)sizeof(t_EVData), 
                          (U8*)&TEVData);

		/* Read the user setting data */
		If_Flash_ReadData( (U32FinalStoreStartAddress + sizeof(t_EVData)), 
	                        (U16)sizeof(t_SettingParameter), 
	                        (U8*)&TSettingPara);

		/* Read the play state data */
		If_Flash_ReadData( (U32FinalStoreStartAddress + sizeof(t_EVData) + 
	                                 sizeof(t_SettingParameter)), 
	                        (U16)sizeof(t_PlayState), 
	                        (U8*)&TPlayState);

		/* Read the AE1 play info */
		If_Flash_ReadData( (U32FinalStoreStartAddress + sizeof(t_EVData) + 
	                        sizeof(t_SettingParameter) + sizeof(t_PlayState)), 
	                        (U16)sizeof(resumeMediaInfo_type), 
	                        (U8*)&resumeMediaInfo);
	}else{
		/* Flash no user data (Because new flash chip or no flash chip) */ 
		Service_Error_Log(ERROR_FLASH_NO_USER_DATA);
	}
	
	/* Ensure the volume limit */
	Service_Gene_LimitS8((S8*)&(TEVData.S8Volume), RANGE_VOLUME_MIN, RANGE_VOLUME_MAX);
	Service_Gene_LimitS8((S8*)&(TEVData.S8VolumeLR), RANGE_VOLUMELR_MIN, RANGE_VOLUMELR_MAX);
	Service_Gene_LimitS8((S8*)&(TEVData.S8VolumeRR), RANGE_VOLUMERR_MIN, RANGE_VOLUMERR_MAX);
	Service_Gene_LimitS8((S8*)&(TEVData.S8VolumeLF), RANGE_VOLUMELF_MIN, RANGE_VOLUMELF_MAX);
	Service_Gene_LimitS8((S8*)&(TEVData.S8VolumeRF), RANGE_VOLUMERF_MIN, RANGE_VOLUMERF_MAX);
	Service_Gene_LimitS8(&(TEVData.S8Bass), RANGE_BASS_MIN, RANGE_BASS_MAX);
	Service_Gene_LimitS8(&(TEVData.S8Treble), RANGE_TREBLE_MIN, RANGE_TREBLE_MAX);
}

/*****************************************************************************
 * ID                :
 * Outline           : Get the start address stored the latest parameters 
 * Include           : none
 * Declaration       : void GetFinalStoreStartAddress(void)
 * Description       : Get the start address stored the latest parameters of 
                     : flash rom
                     : 1. The final 4K bytes of flash are used to store the 
                     :    parameters of this audio system.
                     : 2. Paramters are not more than 256 bytes. Every time only 
                     :    256 bytes of ROM are program as 1 unit.
                     : 3. Every 16 times program, the 4K bytes are erased as 
                     :    0xFF for the next 16 times program. 
                     : 4. The used sequence of 4K bytes ROM, if flash is 4M byte
                     :    1st   	2nd      3rd      ... 16th
                     :    0x3FF000  0x3FF100 0x3FF200 ... 0x3FFF00
                     : 5. About the flash endurance, for AT25DF321, it is  
                     :    100,000 Program/Erase Cycle. Considered step1-step4,
                     :    Audio paramters can be stored 800,000 times. After 
                     :    100,000 Program/Erase Cycle, the flash program\erase 
                     :    funciton still can work, but time consume will be more. 
 * Argument          :
 * Return Value      : 0xFFFFFFFF - Not found the stored data area  
                     : Other      - Start address stored the latest parameters
 * Calling Functions :
 *****************************************************************************/
U32 GetFinalStoreStartAddress(void)
{
	U32 U32FinalStoreStartAddress = (U32)0xFFFFFFFF;
	U32 U32TempAddress;
	U8 	U8_i;
	U8 	U8FlagByteValue;

	for(U8_i=(U8)FLASH_STORAGE_AREA_NUM; U8_i>(U8)0; U8_i--){

		U32TempAddress = FLASH_ADDRESS_ORIGINAL_STORAGE + ((FLASH_STORAGE_SIZE*((U32)U8_i-(U32)1)));

		/* Read the parameter memory of ROM */
		If_Flash_ReadData( (U32TempAddress + FLASH_STORAGE_FLAG_BYTE_OFFSET), 
	                       (U16)1, (U8*)&U8FlagByteValue);

		if(U8FlagByteValue == FLASH_STORAGE_FLAG_BYTE_USED){
			U32FinalStoreStartAddress = U32TempAddress;
			break;
		}
	}
	
	return U32FinalStoreStartAddress;
}

/*****************************************************************************
 * ID                :
 * Outline           : Get the start address to store the parameters
 * Include           : none
 * Declaration       : void GetFinalStoreStartAddress(void)
 * Description       : Get the start address to store the parameters in flashrom
                     : 1. The final 4K bytes of flash are used to store the 
                     :    parameters of this audio system.
                     : 2. Paramters are not more than 256 bytes. Every time only 
                     :    256 bytes of ROM are program as 1 unit.
                     : 3. Every 16 times program, the 4K bytes are erased as 
                     :    0xFF for the next 16 times program. 
                     : 4. The used sequence of 4K bytes ROM, if flash is 4M byte
                     :    1st   	2nd      3rd      ... 16th
                     :    0x3FF000  0x3FF100 0x3FF200 ... 0x3FFF00
                     : 5. About the flash endurance, for AT25DF321, it is  
                     :    100,000 Program/Erase Cycle. Considered step1-step4,
                     :    Audio paramters can be stored 800,000 times. After 
                     :    100,000 Program/Erase Cycle, the flash program\erase 
                     :    funciton still can work, but time consume will be more
 * Argument          :
 * Return Value      : Start address stored the latest parameters
 * Calling Functions :
 *****************************************************************************/
U32 GetNextStoreStartAddress(void)
{
	U32 U32TempAddress;

	U32TempAddress = GetFinalStoreStartAddress();

	if(U32TempAddress == (FLASH_ADDRESS_ORIGINAL_STORAGE + 
     (FLASH_STORAGE_SIZE*((U32)FLASH_STORAGE_AREA_NUM - (U32)1))) ){
		/* If 16 areas have all been stored once, return the origianl address */
		U32TempAddress = FLASH_ADDRESS_ORIGINAL_STORAGE;
	}else if(U32TempAddress == 0xFFFFFFFF){
		/* If 16 areas are all not stored, return the origianl address */
		U32TempAddress = FLASH_ADDRESS_ORIGINAL_STORAGE;
	}else{
		/* If one of 1st - 15th areas is the final stored area, return 
           the next area address */
		U32TempAddress += FLASH_STORAGE_SIZE;
	}

	return U32TempAddress;
}

/*****************************************************************************
 * ID                :
 * Outline           : Task of store the parameters into the flash
 * Include           : none
 * Declaration       : void App_Host_StoreParameter(void)
 * Description       : Task of store the parameters into the flash
 * Argument          :
 * Return Value      : None
 * Calling Functions :
 *****************************************************************************/
void App_Host_StoreParameter(void)
{
	U8 U8FlashStatusByte;
	U8 U8StoredFlagByte;

	/* Note: write 1 page(256bytes) need 1-3 ms for AT25DF321A. */
	/* Note: write 1 byte need 7 us for AT25DF321A. */
	switch(U8StoreParameterState){
	case STORE_FLASH_0_IDLE:
		break;
	case STORE_FLASH_1_UNPROTECTSECTOR:
		/* Get the store address */
		U32StoreStartAddress = GetNextStoreStartAddress();
		/* UnProtect the corresponding sector */
		If_Flash_UnProtectSector(U32StoreStartAddress);
		U8StoreParameterState = STORE_FLASH_2_ERASE_BLOCK;
		break;
	case STORE_FLASH_2_ERASE_BLOCK:
		/* When store address is original store address, erase the whole block */
		if(U32StoreStartAddress == FLASH_ADDRESS_ORIGINAL_STORAGE){
			/* Erase the corresponding 4K bytes block of 'U32FlsAddress' */
			If_Flash_Erase4KBytesBlock(U32StoreStartAddress);
			U8StoreParameterState = STORE_FLASH_3_ERASEING;
		}else{
			U8StoreParameterState = STORE_FLASH_3_ERASEING;
		}
		break;
	case STORE_FLASH_3_ERASEING:
		if(U32StoreStartAddress == FLASH_ADDRESS_ORIGINAL_STORAGE){
			/* Wait for erase end */
			If_Flash_ReadStatusRegister(&U8FlashStatusByte);
			if((U8FlashStatusByte&(U8)0x01) == (U8)0x00){
				U8StoreParameterState = STORE_FLASH_4_WRITE_DATA1;
			}
		}else{
			U8StoreParameterState = STORE_FLASH_4_WRITE_DATA1;
		}
		break;
	case STORE_FLASH_4_WRITE_DATA1:
		/* write the sound setting data */
		If_Flash_WriteData(U32StoreStartAddress, 
                          (U16)sizeof(t_EVData), 
                          (U8*)&TEVData);
		U8StoreParameterState = STORE_FLASH_5_PROGRAMMING_DATA1;
		break;
	case STORE_FLASH_5_PROGRAMMING_DATA1:
		/* Wait for program end */
		If_Flash_ReadStatusRegister(&U8FlashStatusByte);
		if((U8FlashStatusByte&(U8)0x01) == (U8)0x00){
			U8StoreParameterState = STORE_FLASH_6_WRITE_DATA2;
		}
		break;
	case STORE_FLASH_6_WRITE_DATA2:
		/* write the other setting data*/
		If_Flash_WriteData((U32StoreStartAddress + sizeof(t_EVData)), 
                           (U16)sizeof(t_SettingParameter), 
                           (U8*)&TSettingPara);
		U8StoreParameterState = STORE_FLASH_7_PROGRAMMING_DATA2;
		break;
	case STORE_FLASH_7_PROGRAMMING_DATA2:
		/* Wait for program end */
		If_Flash_ReadStatusRegister(&U8FlashStatusByte);
		if((U8FlashStatusByte&(U8)0x01) == (U8)0x00){
			U8StoreParameterState = STORE_FLASH_8_WRITE_DATA3;
		}
		break;
	case STORE_FLASH_8_WRITE_DATA3:
		/* write(backup) the AE1 play info */
		If_Flash_WriteData( (U32StoreStartAddress + sizeof(t_EVData) + 
                     		sizeof(t_SettingParameter)), 
                     		(U16)sizeof(t_PlayState), 
                     		(U8*)&TPlayState);
		U8StoreParameterState = STORE_FLASH_9_PROGRAMMING_DATA3;
		break;
	case STORE_FLASH_9_PROGRAMMING_DATA3:
		/* Wait for program end */
		If_Flash_ReadStatusRegister(&U8FlashStatusByte);
		if((U8FlashStatusByte&(U8)0x01) == (U8)0x00){
			U8StoreParameterState = STORE_FLASH_10_WRITE_DATA4;
		}
		break;
	case STORE_FLASH_10_WRITE_DATA4:
		/* write(backup) the AE1 play info */
		If_Flash_WriteData( (U32StoreStartAddress + sizeof(t_EVData) + 
                           sizeof(t_SettingParameter) + sizeof(t_PlayState)), 
                           (U16)sizeof(resumeMediaInfo_type), 
                           (U8*)&resumeMediaInfo);
		U8StoreParameterState = STORE_FLASH_11_PROGRAMMING_DATA4;
		break;
	case STORE_FLASH_11_PROGRAMMING_DATA4:
		/* Wait for program end */
		If_Flash_ReadStatusRegister(&U8FlashStatusByte);
		if((U8FlashStatusByte&(U8)0x01) == (U8)0x00){
			U8StoreParameterState = STORE_FLASH_12_WRITE_DATA5;
		}
		break;
	case STORE_FLASH_12_WRITE_DATA5:
		U8StoredFlagByte = FLASH_STORAGE_FLAG_BYTE_USED;
		/* write the flag byte to indicate the used state */
		If_Flash_WriteData( (U32StoreStartAddress + FLASH_STORAGE_FLAG_BYTE_OFFSET), 
                           (U16)1, 
                           (U8*)&U8StoredFlagByte);
		U8StoreParameterState = STORE_FLASH_13_PROGRAMMING_DATA5;
		break;
	case STORE_FLASH_13_PROGRAMMING_DATA5:
		/* Wait for program end */
		If_Flash_ReadStatusRegister(&U8FlashStatusByte);
		if((U8FlashStatusByte&(U8)0x01) == (U8)0x00){
			U8StoreParameterState = STORE_FLASH_14_PROTECTSECTOR;
		}
		break;
	case STORE_FLASH_14_PROTECTSECTOR:
		/* Protect the corresponding sector */
		If_Flash_ProtectSector(U32StoreStartAddress);
		U8StoreParameterState = STORE_FLASH_15_END;
		break;
	case STORE_FLASH_15_END:
		/* Wait for the last command end */
		If_Flash_ReadStatusRegister(&U8FlashStatusByte);
		if((U8FlashStatusByte&(U8)0x01) == (U8)0x00){
			U8StoreParameterState = STORE_FLASH_0_IDLE;
		}
		break;
	default:
		break;
	}
}

/* End of file */
