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
* File Name    : disp_task.c
* Abstract     : application of disp
* Version      : 1.00
* Device       : R8C/2A group, or R8C/2B group, or 78K0 group
* Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
*              : Renesas M16C Standard Toolchain (V5.45.01)
* OS           : none
* H/W Platform : AE1-LF demo board
* Description  : This is application of disp.
* Operation    : none
* Limitation   : This file can be only used as sample code for AE1-LF.
*****************************************************************************
* History      : May.15,2011 Ver. 1.00 First Release
*****************************************************************************/

/*****************************************************************************
Includes   <System Includes> , "Project Includes"
*****************************************************************************/
#include "config.h"
#include "driver_lcd.h"
#include "basictype.h"
#include "if_lcd_draw.h"
#include "if_lcd_text.h"
#include "draw_task.h"
#include "disp_widget.h"
#include "driver_timer0.h"
#include "app_host.h"
#include "if_disp.h"
#include "if_timer.h"
#include <math.h>
#include "driver_oled.h"
#include "disp_msg.h"
#include "app_ae1.h"
#include "app_menu.h"

/*****************************************************************************
Typedef definitions
*****************************************************************************/

/*****************************************************************************
Macro definitions
*****************************************************************************/

/*****************************************************************************
Imported global variables and functions (from other files)
*****************************************************************************/
extern const Disp_WidgetType WidgetPlayMode;
extern const Disp_WidgetType WidgetDisp;
extern const Disp_WidgetType WidgetVolume;
extern const Disp_WidgetType WidgetFolder;
extern const Disp_WidgetType WidgetTitle;
extern const Disp_WidgetType WidgetPlayState;
extern const Disp_WidgetType WidgetPlayTimer;
extern const Disp_WidgetType WidgetPlayRoll;
extern const Disp_WidgetType WidgetFolderscan;
extern const Disp_WidgetType WidgetfolderRoll;
extern const Disp_WidgetType WidgetSet;
extern void folderRollTimerPro( void );
extern void SetRollTimerPro( void );
extern void PlayRollTimerPro( void );
extern void VolumePullup( U8 mode );
extern void FolderScanSetRoll(U8 updown,U16 rolltime);
extern void FolderscanTimerPro( void );
extern void FolderScanSetTimer(U16 timer_us);
extern void ForderItemPoschg(U8 flag);
extern void FolderscanPaint(U8 mode);
extern void Draw_warn_nomedia(U8 warntype);
extern U8 FolderRollState;



/*****************************************************************************
Exported global variables and functions (to be accessed by other files)
*****************************************************************************/
U8 DispShutDown;
DISP_STATE DispState = DISP_INIT;

U32 DispWaitTM; 
U8 DispRollBackState;

/*****************************************************************************
Private variables and functions
*****************************************************************************/
static void DrawScreen(DISP_STATE screenno);
static Disp_Message GetMessage(void);

/*****************************************************************************
* ID				 : 1.0
* Outline			 : Display task
* Include			 : none
* Declaration		 : void App_Task_Disp(void)
* Description		 : Display task
* Argument 			 : void
* Return Value 		 : void
* Calling Functions  : none
*****************************************************************************/
void App_Task_Disp(void)
{
	static DISP_FOLDER_STATE DispFolderState = DISP_FOLDER_INIT;
	static DISP_FOLDER_STATE DispFolderStateFirst = DISP_FOLDER_INIT;
	static DISP_SHUTDOWN_STATE DispShupDownState = DISP_SHUTDOWN_INIT;
	U16 Rolltimer;

	Disp_Message DispMsg;

	/*set draw screen no*/
	switch(U8HostState)
	{
	case HOST_STATE_PLAY:

		break;
	case HOST_STATE_SETTING:
		
		break;
	case HOST_STATE_TEST:
		
	case HOST_STATE_PREPARE_PERIPHERAL_POWERDOWN:
		DispState = DISP_SHUTDOWN;
		break;
	default:
		
		break;
	}

	switch(DispState)
	{
	case DISP_INIT:

		/*Wait for power up*/
//		if(U8HostState == HOST_STATE_PLAY)
//		{
			/*clear timer*/
			CurrentTimer = (U32)0;
			DispWaitTM = CurrentTimer;
			/*switch to wait vcc12 mode*/
			DispState = DISP_WAIT_VCC12;
			DispShutDown = FALSE;
//		}
		break;
	case DISP_WAIT_VCC12:
		/*after reset oled, wait for 100ms ,then set 12v*/
		if(CurrentTimer>(DispWaitTM+(U32)TIME_100MS))
		{
			If_Disp_Init();
			If_Disp_SetStartLine(DISP_SCREEN_START_LINE);
			DispMsgMask = DISP_MSG_NOMASK;

			/*set msg language*/
			switch(TSettingPara.U8Language)
			{
			case SET_LANGUAGE_1_ENGLISH:
				Msgstr = MsgEn;
				break;
			case SET_LANGUAGE_0_SIM_CHINESE:
				Msgstr = MsgCh;
				break;
			default:
				Msgstr = MsgEn;
				break;
			}

			/*draw play mode screen*/
			DrawScreen(DISP_PLAY);

			/*switch to play mode*/
			DispState = DISP_PLAY;
			
		}
		break;
	case DISP_PLAY:

		/*get message for play mode*/
		DispMsg = GetMessage( );

		/*handle the message*/
		switch(DispMsg)
		{
		case DISP_MSG_DISK_CHANGE:
			WidgetDisp.Paint(REDRAW);
			break;
		case DISP_MSG_PLAYMODE_CHANGE:
			WidgetPlayMode.Paint(UPDATA);
			break;
		case DISP_MSG_VOLUME_SHOW_HIDE:
			/*draw volume change screen*/
			DrawScreen(DISP_VOLUME_PULLUP);
			
			/*set play mode back timer*/
			*WidgetVolume.Timer->TimerTick = CurrentTimer;
			
			/*set play screen switch to volumn screen*/
			If_Disp_SetRoll(DISP_SCREEN_START_LINE,DISP_SCREEN_HALFT_LINE,(U8)1,(U16)500);

			/*switch to volume mode*/
			DispState = DISP_ROLLING;
			DispRollBackState = DISP_VOLUME_PULLUP;
		    break;
		case DISP_MSG_FILE_CHANGE:
			/*draw file info*/
			WidgetFolder.Paint(REDRAW);
			/*if all infos of tag are updata,draw title info and timer info*/
			if(Dispinfo.currentFile.InfoUpdate)
			{
				WidgetTitle.Init();
				WidgetTitle.Paint(REDRAW);
				WidgetPlayTimer.Paint(REDRAW);
			}
		    break;
		case DISP_MSG_PLAYSTATE_CHANGE:
			WidgetPlayState.Paint(REDRAW);
			break;
		case DISP_MSG_PLAYTIMER_CHANGE:
			WidgetPlayTimer.Paint(UPDATA);
			break;
		case DISP_MSG_PLAYTIMER_REDRAW:
			WidgetPlayTimer.Paint(REDRAW);
		    break;
		case DISP_MSG_FOLDER_SHOW_HIDE:
			/*draw folder change screen*/
			DrawScreen(DISP_FOLDERSCAN);

			/*set play screen switch to folder change screen*/
			If_Disp_SetRoll(DISP_SCREEN_START_LINE,DISP_SCREEN_HALFT_LINE,(U8)1,(U16)500);
			
			/*set sub mode of folder change mode*/
			DispFolderState = DISP_FOLDER_INIT;

			/*switch to folder change screen*/
			DispState = DISP_ROLLING;
			DispRollBackState = DISP_FOLDERSCAN;

			if((Dispinfo.currentFile.folderInfoBuf.folderDirection ==CLOCKWISE))
			{
				DispFolderStateFirst = DISP_FOLDER_UP;
			}else
			{
				DispFolderStateFirst = DISP_FOLDER_DOWN;
			}
			
			break;
		case DISP_MSG_MENU_ITEM_REDRAW:
			/*draw setting screen*/
			DrawScreen(DISP_SETTING);

			/*set Play screen switch to setting screen*/
			If_Disp_SetRoll(DISP_SCREEN_START_LINE,DISP_SCREEN_HALFT_LINE-(U8)2,(U8)1,(U16)500);

			/*switch to setting screen*/
			DispState = DISP_ROLLING;
			DispRollBackState = DISP_SETTING;
			break;
		case DISP_MSG_WARN_NOMEDIA:
			Draw_warn_nomedia(TEXT_WARN_NOMADIA);
			break;
		case DISP_MSG_WARN_ANYING:
			Draw_warn_nomedia(TEXT_WARN_ANLING);
			break;
		default:
		    break;
		}
		

		/*Timer*/
		/*widgettitle timer,roll tag info*/
		if (*(WidgetTitle.Timer->TimeEnable)==TRUE)
		{
			if (CurrentTimer>(WidgetTitle.Timer->DalyTime+*WidgetTitle.Timer->TimerTick))
			{
				*WidgetTitle.Timer->TimerTick = CurrentTimer;
				WidgetTitle.Timer->CheckTimeout();
			}
		}
		
		break;
	case DISP_VOLUME_PULLUP:
		DispMsg = GetMessage( );

		switch(DispMsg)
		{
		case DISP_MSG_VOLUME_CHANGE:
			/*reset come back timer*/
			*WidgetVolume.Timer->TimerTick = CurrentTimer;
			/*updata volume info*/
			VolumePullup(UPDATA);
			break;
		case DISP_MSG_VOLUME_SHOW_HIDE:
			/*draw play screen*/
			DrawScreen(DISP_PLAY);
			/*set volumn screen switch to play screen*/
			If_Disp_SetRoll(DISP_SCREEN_START_LINE,DISP_SCREEN_HALFT_LINE,(U8)0,(U16)500);
			/*switch to play screen*/
			DispState = DISP_ROLLING;
			DispRollBackState = DISP_PLAY;
			break;
		default:
		    break;
		}
#if 0
		/*Timer*/
		/*widgetvolume timer,when timer out,come back to play screen*/
		if (CurrentTimer>WidgetVolume.Timer->DalyTime+*WidgetVolume.Timer->TimerTick)
		{
			/*draw play screen*/
			DrawScreen(DISP_PLAY);
			/*set volumn screen switch to play screen*/
			If_Disp_SetRoll(DISP_SCREEN_START_LINE,DISP_SCREEN_HALFT_LINE,0,5000);
			/*switch to play screen*/
			DispState = DISP_PLAY;
		}
#endif
		break;
	case DISP_FILESCAN:
		break;
	case DISP_FOLDERSCAN:
		DispMsg = GetMessage( );

		switch(DispFolderState)
		{
		case DISP_FOLDER_INIT:
			switch(DispMsg)
			{
			case DISP_MSG_FOLDER_CHANGE:
				If_Disp_RollEnd();
				DispMessage |=DISP_MSG_FOLDER_CHANGE;
				break;
			case DISP_MSG_FOLDER_SHOW_HIDE:
				DispFolderState = DISP_FOLDER_EXIT;
				break;
			default:
				break;
			}
			/*wait for play screen switch to folder change screen end*/
			if(DispRollEnd == DISP_ROLL_END)
			{
				/*clear screen buf*/
				LCD_DrawBox(0U,0U,256U,62U,1U,0U,0U);
				DispFolderState = DispFolderStateFirst;
	
			}
			break;
		case DISP_FOLDER_DOWN:

			switch(DispMsg)
			{
			case DISP_MSG_FOLDER_CHANGE:
				if(DispRollEnd == DISP_ROLL_ING)
				{
					/*If_Disp_RollEnd();*/
				}
				if(Dispinfo.currentFile.folderInfoBuf.folderDirection ==CLOCKWISE)
				{
					if(DispRollEnd == DISP_ROLL_ING)
					{
						If_Disp_RollEnd();
					}
					/*Draw forder name buf*/
					FolderscanPaint(FOLDER_SCAN_DRAW_BUF_DOWNSWITCH);
					/*Set Roll timer*/
					Rolltimer = (U16)TMsgHostToDisplay.S16Rotary2SpeedTimerCount;
					FolderScanSetRoll((U8)3,Rolltimer);
					ForderItemPoschg((U8)1);
					DispFolderState = DISP_FOLDER_UP;
				}else if(Dispinfo.currentFile.folderInfoBuf.folderDirection == ANTI_CLOCKWISE)
				{
					FolderscanPaint(FOLDER_SCAN_DRAW_BUF_DWWN_ALL);	
					Rolltimer = (U16)((S16)0-TMsgHostToDisplay.S16Rotary2SpeedTimerCount);
					FolderScanSetRoll((U8)0,Rolltimer);
					ForderItemPoschg((U8)0);
					FolderscanPaint(FOLDER_SCAN_DRAW_BUF_DOWN);
				}else
				{
					/*nothing*/
				}
				break;
			case DISP_MSG_FOLDER_SHOW_HIDE:
				DispFolderState = DISP_FOLDER_EXIT;
			    break;
			default:
			    break;
			}			
			break;
		case DISP_FOLDER_UP:
			switch(DispMsg)
			{
			case DISP_MSG_FOLDER_CHANGE:
				if(DispRollEnd == DISP_ROLL_ING)
				{
					/*If_Disp_RollEnd();*/
				}
				if(Dispinfo.currentFile.folderInfoBuf.folderDirection ==CLOCKWISE)
				{
					FolderscanPaint(FOLDER_SCAN_DRAW_BUF_UP_ALL);
					/*Set Roll timer int*/
					Rolltimer = (U16)TMsgHostToDisplay.S16Rotary2SpeedTimerCount;
					FolderScanSetRoll((U8)1,Rolltimer);
					ForderItemPoschg((U8)1);
					/*Draw forder name buf*/
					FolderscanPaint(FOLDER_SCAN_DRAW_BUF_UP);
				}else if(Dispinfo.currentFile.folderInfoBuf.folderDirection == ANTI_CLOCKWISE)
				{
					if(DispRollEnd == DISP_ROLL_ING)
					{
						If_Disp_RollEnd();
					}
					/*Draw forder name buf*/
					FolderscanPaint(FOLDER_SCAN_DRAW_BUF_UPSWITCH);
					/*Set Roll timer*/
					Rolltimer = (U16)((S16)0-TMsgHostToDisplay.S16Rotary2SpeedTimerCount);
					FolderScanSetRoll((U8)2,Rolltimer);
					ForderItemPoschg((U8)0);
					DispFolderState = DISP_FOLDER_DOWN;
				}else
				{
					/*nothing to do*/
				}
				break;
			case DISP_MSG_FOLDER_SHOW_HIDE:
				DispFolderState = DISP_FOLDER_EXIT;
				break;
			default:
				break;
			}
			break;
		case DISP_FOLDER_IDLE:


			break;
		case DISP_FOLDER_EXIT:
			If_Disp_RollEnd();
			If_disp_clear();
			If_Disp_SetStartLine((U8)0);
			DrawScreen(DISP_PLAY);
			DispState = DISP_PLAY;
			break;
		default:
		    break;
		}

		break;
	case DISP_SETTING:
		DispMsg = GetMessage();

		WidgetSet.MsgProc(DispMsg);

		if (U8HostState == HOST_STATE_PLAY)
		{
			DrawScreen(DISP_PLAY);
			If_Disp_SetRoll(DISP_SCREEN_START_LINE,DISP_SCREEN_HALFT_LINE-(U8)2,(U8)0,(U16)500);
			/*switch to play screen*/
			DispState = DISP_ROLLING;
			DispRollBackState = DISP_PLAY;
		}

		break;
	case DISP_MAINTAIN:
	    break;
	case DISP_ROLLING:
		if (DispRollEnd == DISP_ROLL_END)
		{
			DispState = DispRollBackState;
		} 
		else
		{
			/* Do nothing*/
		}
		break;
	case DISP_SHUTDOWN:
		
		switch(DispShupDownState)
		{
		case DISP_SHUTDOWN_INIT:
			If_Disp_RollEnd();
			If_disp_clear();
			If_Disp_SetStartLine(DISP_SCREEN_START_LINE);
			LCD_DrawBmp((U16)20,(U16)2,BMP_LOGO_NO);
			LCD_TextA(Aboutinfo[0],20U,32U,FONT16);
			LCD_TextA(Aboutinfo[2],20U,48U,FONT16);
			
			/*wait some time*/
			DispShupDownState = DISP_SHUTDOWN_3;
			DispWaitTM = CurrentTimer;
			break;
		case DISP_SHUTDOWN_1:
			/*if first screen roll end,then clear first screen and roll */
			if (DispRollEnd == DISP_ROLL_END)
			{
				LCD_DrawBox(0U,0U,256U,16U,1U,0U,0U);
				DispShupDownState = DISP_SHUTDOWN_2;
				If_Disp_SetRoll(DISP_SCREEN_START_LINE,16U,1U,250U);
			}
			break;
		case DISP_SHUTDOWN_2:
			/*if roll end, sent shutdown to host*/
			if (DispRollEnd == DISP_ROLL_END)
			{
				DispShupDownState = DISP_SHUTDOWN_4;
				DispShutDown = TRUE;
			}
		    break;
		case DISP_SHUTDOWN_3:
			/*wait for 1s , then start roll*/
			if (CurrentTimer>(DispWaitTM+(U32)TIME_1S))
			{
				If_Disp_SetRoll(DISP_SCREEN_START_LINE,(U8)64,(U8)1,(U16)1000);
				DispShupDownState = DISP_SHUTDOWN_1;
			}

		    break;
		case DISP_SHUTDOWN_4:
			/*if host state is powerdown ,then entry powerdown state*/

			DispShupDownState = DISP_SHUTDOWN_INIT;
			DispState = DISP_POWERDOWN;
			break;

		default:
		    break;
		}

		
		break;
	case DISP_POWERDOWN:
		if (U8HostState ==HOST_STATE_PERIPHERAL_POWERUP)
		{
			DispState = DISP_INIT;
		}
		break;
	default:
	    break;
	}


}

/*****************************************************************************
* ID				 : 1.0
* Outline			 : Display task
* Include			 : none
* Declaration		 : static Disp_Message GetMessage(void)
* Description		 : Display task
* Argument 			 : void
* Return Value 		 : Disp_Message
* Calling Functions  : none
*****************************************************************************/
static Disp_Message GetMessage()
{
	Disp_Message Msg,MsgC;
	U8 u8_i;

	Msg = DISP_MSG_NULL;
	MsgC = (U32)0x00000001;

	if(DispMessage != DISP_MSG_NULL)
	{
		/*Search the nearest msg and clear it */
		for (u8_i=0U;u8_i<DISP_MSG_NUM;u8_i++)
		{
			/*Search match message*/
			if ((MsgC&DispMessage)&&(MsgC&DispMsgMask))
			{
				Msg = MsgC;
				/*Clear message bit*/
				DispMessage=DispMessage&(~Msg);
				break;
			}
			MsgC = MsgC<<1;
		}
	}
	return Msg;
}

/*****************************************************************************
* ID				 : 1.0
* Outline			 : Display task
* Include			 : none
* Declaration		 : static void DrawScreen(DISP_STATE screenno)
* Description		 : Display task
* Argument 			 : screenno
* Return Value 		 : void
* Calling Functions  : none
*****************************************************************************/
static void DrawScreen(DISP_STATE screenno)
{
	switch(screenno)
	{
	case DISP_PLAY:
#if 0/* comment by titron */
		LCD_DrawBox(0U,0U,256U,64U,1U,0U,0U);
		WidgetTitle.Init();
		WidgetDisp.Paint(REDRAW);
		WidgetPlayMode.Paint(REDRAW);
		WidgetFolder.Paint(REDRAW);
		/*20110520 del */
		WidgetTitle.Paint(REDRAW);
		WidgetPlayState.Paint(REDRAW);
		WidgetPlayTimer.Paint(REDRAW);
		WidgetVolume.Paint(REDRAW);
#endif
		WidgetPlayTimer.Paint(REDRAW);
		break;
	case DISP_VOLUME_PULLUP:
		LCD_DrawBox(0U,62U,256U,126U,1U,0U,0U);
		VolumePullup(REDRAW);
		break;
	case DISP_FOLDERSCAN:
		LCD_DrawBox(0U,62U,256U,126U,1U,0U,0U);
		if((Dispinfo.currentFile.folderInfoBuf.folderDirection ==CLOCKWISE) )
		{
			FolderscanPaint(FOLDER_SCAN_DRAW_UP);
			
		}else
		{
			FolderscanPaint(FOLDER_SCAN_DRAW_DOWN);
			
		}
		
	    break;
	case DISP_SETTING:
		WidgetSet.Init();
		WidgetSet.Paint(REDRAW);
	    break;
	default:
	    break;
	}
}

