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
 * File Name    : app_evolume.c
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

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "service_general.h"
#include "if_evolume.h"
#include "app_ae1.h"
#include "app_evolume.h"
#include "app_host.h"
#include "disp_widget.h"
#include "driver_timer0.h"

/*****************************************************************************
 Private variables and functions
 *****************************************************************************/
static EV_MESSAGE GetEVMessage(void);
static void ClearEVMessage(EV_MESSAGE Msg);

/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/
U8 U8EVState = EV_STATE_INIT;
U16 U16TimerCountEVPowerUpDelay = (U16)0;
t_MsgHostToEV	TMsgHostToEV;
t_EVData		TEVData;

/*****************************************************************************
 * ID                :
 * Outline           : App_Task_EV
 * Include           : none
 * Declaration       : void App_Task_EV(void)
 * Description       : Task of evolume
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/

/*****************************************************************************
 * ID                :
 * Outline           : Get the EVolume message
 * Include           : none
 * Declaration       : EV_MESSAGE GetEVMessage(void)
 * Description       : Get the EVolume message
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
EV_MESSAGE GetEVMessage(void)
{
	EV_MESSAGE Msg,MsgC;
	U8 U8_i;
	
	if(TMsgHostToEV.EVMessage == EV_MSG_NULL){
		Msg = EV_MSG_NULL;		
	}else{
		Msg = EV_MSG_NULL;
		MsgC = (EV_MESSAGE)0x01;

		/*Search the nearest msg and clear it */
		for (U8_i=(U8)0;U8_i<EV_MSG_NUMBER;U8_i++)
		{
			/*Search match message*/
			if (MsgC&(TMsgHostToEV.EVMessage))
			{
				Msg = MsgC;
				/*Clear message bit*/
				TMsgHostToEV.EVMessage = (TMsgHostToEV.EVMessage)&(~Msg);
				break;
			}
			MsgC = MsgC<<1;
		}
	}

	return Msg;
}

/*****************************************************************************
 * ID                :
 * Outline           : Clear the EVolume message
 * Include           : none
 * Declaration       : void ClearEVMessage(void)
 * Description       : Clear the evolume message
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void ClearEVMessage(EV_MESSAGE Msg)
{
	TMsgHostToEV.EVMessage = (TMsgHostToEV.EVMessage)&(~Msg);
}

/*****************************************************************************
 * ID                :
 * Outline           : App_EV_InitEVolumeData
 * Include           : none
 * Declaration       : void App_EV_InitEVolumeData(void)
 * Description       : Initialize the evolume data
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void App_EV_InitEVolumeData(void)
{
	TEVData.S8Volume = DEFAULT_VOLUME;
	TEVData.S8VolumeLF = DEFAULT_VOLUME_LF;
	TEVData.S8VolumeLR = DEFAULT_VOLUME_LR;
	TEVData.S8VolumeRF = DEFAULT_VOLUME_RF;
	TEVData.S8VolumeRR = DEFAULT_VOLUME_RR;
	TEVData.U8Mute = OFF;
	TEVData.U8SwitchLoudGain = DEFAULT_SWITCH_LOUD_GAIN;
	TEVData.S8Bass = DEFAULT_VOLUME_BASS;
	TEVData.S8Treble = DEFAULT_VOLUME_TREBLE;
}

/* End of file */
