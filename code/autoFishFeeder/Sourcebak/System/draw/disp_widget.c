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
* File Name    : disp_widget.c
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
#include <string.h>
#include <stdio.h>

#include "config.h"
#include "driver_oled.h"
#include "driver_evolume.h"
#include "basictype.h"
#include "if_lcd_draw.h"
#include "if_lcd_text.h"
#include "driver_oled.h"
#include "draw_task.h"
#include "app_ae1.h"
#include "disp_widget.h"
#include "driver_timer0.h"
#include "disp_msg.h"
#include "app_host.h"
#include "app_menu.h"
#include "app_evolume.h"
#include "if_timer.h"
#include "if_led.h"
#include "if_disp.h"

/*****************************************************************************
Typedef definitions
*****************************************************************************/

/*****************************************************************************
Macro definitions
*****************************************************************************/
#define DRAWFOLDERNUM;

/*Postion define*/
#define POS_OFFSET 					(U16)16
#define POS_DISK_SD_X				POS_OFFSET
#define POS_DISK_SD_Y				(U16)0
#define POS_DISK_USB_X				(POS_OFFSET+(U16)16)
#define POS_DISK_USB_Y				(U16)0
#define POS_PLAY_FILE_X				(POS_OFFSET+(U16)100)
#define POS_PLAY_FILE_Y				(U16)0
#define POS_PLAY_MODE_SPACE			(U16)4
#define POS_PLAY_MODE_WIDTH			(U16)16
#define POS_PLAY_MODE_X				((U16)36+POS_PLAY_MODE_SPACE+POS_OFFSET)
#define POS_PLAY_MODE_Y				(U16)0
#define POS_PLAY_MODE_LOOP_X		POS_PLAY_MODE_X
#define POS_PLAY_MODE_RANDOM_X		(POS_PLAY_MODE_LOOP_X+POS_PLAY_MODE_WIDTH+POS_PLAY_MODE_SPACE)
#define POS_PLAY_MODE_SCAN_X		(POS_PLAY_MODE_RANDOM_X+POS_PLAY_MODE_WIDTH+POS_PLAY_MODE_SPACE)
#define POS_PLAY_SPEEK_X			((U16)196+POS_OFFSET)
#define POS_PLAY_SPEEK_Y			(U16)0
#define POS_PLAY_SPEEK_LINE_X		(POS_PLAY_SPEEK_X+(U16)16-POS_OFFSET)
#define POS_PLAY_SPEEK_VOLUME_X		(POS_PLAY_SPEEK_X+(U16)16+(U16)24)
#define POS_PLAY_AUDIO_ALBUM_X		(U16)64
#define POS_PLAY_AUDIO_ALBUM_Y		(U16)16
#define POS_PLAY_AUDIO_TITLE_Y		(U16)32
#define POS_PLAY_PAUSE_X			POS_OFFSET
#define POS_PLAY_PAUSE_Y			(U16)48
#define POS_PLAY_TIME_X				((U16)20+POS_OFFSET)
#define POS_PLAY_TIME_Y				(U16)48
#define POS_PLAY_TIME_PLAYBACK_X	POS_PLAY_TIME_X
#define POS_PLAY_TIME_LINE_X		(POS_PLAY_TIME_X+(U16)40-POS_OFFSET)
#define POS_PLAY_TIME_LINE_WIDTH	(U16)100
#define POS_PLAY_TIME_FILE_X		(POS_PLAY_TIME_X+POS_PLAY_TIME_LINE_WIDTH+(U16)40+(U16)8)
/*widget postion*/
#define POS_WIDGET_TITLE_X						(U16)0		
#define POS_WIDGET_TILLE_Y						(U16)24
#define POS_WIDGET_TITLE_WIDTH					(U16)0
#define POS_WIDGET_TITLE_HIGHT					(U16)0
#define POS_WIDGET_DISK_X						(U16)POS_OFFSET		
#define POS_WIDGET_DISK_Y						(U16)0
#define POS_WIDGET_DISK_WIDTH					(U16)0
#define POS_WIDGET_DISK_HIGHT					(U16)0
#define POS_WIDGET_PLAYMODE_X						(U16)POS_PLAY_MODE_X		
#define POS_WIDGET_PLAYMODE_Y						(U16)POS_PLAY_MODE_Y
#define POS_WIDGET_PLAYMODE_WIDTH					(U16)0
#define POS_WIDGET_PLAYMODE_HIGHT					(U16)0
#define POS_WIDGET_VOLUME_X						(U16)POS_PLAY_SPEEK_X		
#define POS_WIDGET_VOLUME_Y						(U16)POS_PLAY_SPEEK_Y
#define POS_WIDGET_VOLUME_WIDTH					(U16)0
#define POS_WIDGET_VOLUME_HIGHT					(U16)0
#define POS_WIDGET_FOLDER_X						(U16)POS_PLAY_FILE_X		
#define POS_WIDGET_FOLDER_Y						(U16)POS_PLAY_FILE_Y
#define POS_WIDGET_FOLDER_WIDTH					(U16)0
#define POS_WIDGET_FOLDER_HIGHT					(U16)0
#define POS_WIDGET_PLAYSTATE_X						(U16)POS_PLAY_PAUSE_X		
#define POS_WIDGET_PLAYSTATE_Y						(U16)POS_PLAY_PAUSE_Y
#define POS_WIDGET_PLAYSTATER_WIDTH					(U16)0
#define POS_WIDGET_PLAYSTATE_HIGHT					(U16)0
#define POS_WIDGET_PLAYTIMER_X						(U16)POS_PLAY_TIME_X		
#define POS_WIDGET_PLAYTIMER_Y						(U16)POS_PLAY_TIME_Y
#define POS_WIDGET_PLAYTIMER_WIDTH					(U16)0
#define POS_WIDGET_PLAYTIMER_HIGHT					(U16)0
#define POS_WIDGET_MENU_X						(U16)0		
#define POS_WIDGET_MENU_Y						(U16)62
#define POS_WIDGET_MENU_WIDTH					(U16)0
#define POS_WIDGET_MENU_HIGHT					(U16)0


#define DISK_SD_UNLINK		(U8)0
#define DISK_SD_LINK		(U8)1
#define DISK_SD_ACTIV		(U8)2
#define DISK_USB_UNLINK		(U8)0
#define DISK_USB_LINK		(U8)1
#define DISK_USB_ACTIV		(U8)2

#define ALBUM_MAX_NUM		(U8)23
#define TITLE_MAX_NUM		(U8)32
#define TITLE_MAX_NUM_DISP	(U8)64

#define FORDERSCAN_FILE_ORDER_UP_PRE		(U8)0
#define FORDERSCAN_FILE_ORDER_UP_CURRENT	(U8)1
#define FORDERSCAN_FILE_ORDER_UP_NEXT1		(U8)2
#define FORDERSCAN_FILE_ORDER_UP_NEXT2		(U8)3
#define FORDERSCAN_FILE_ORDER_UP_NEXT3		(U8)4

#define FORDERSCAN_FILE_ORDER_DOWN_PRE3		(U8)0
#define FORDERSCAN_FILE_ORDER_DOWN_PRE2		(U8)1
#define FORDERSCAN_FILE_ORDER_DOWN_PRE1		(U8)2
#define FORDERSCAN_FILE_ORDER_DOWN_CURRENT	(U8)3
#define FORDERSCAN_FILE_ORDER_DOWN_NEXT		(U8)4

#define FOLDERSCAN_NAMEBUF_MAX				(U8)16

#define TITLE_LENGTH			48U

#define TIMER_HOUR_SECOND		(U32)3600
#define TIMER_MINUTE_SENCOND	(U32)60

#define ITEMPAINT_NULL      (Disp_MenuItemPaint)0
#define ITEMMSG_NULL		(Disp_MenuItemMsg)0
#define ITEMS_NULL		(Disp_WidgetMenuItem const **)0
/*****************************************************************************
Imported global variables and functions (from other files)
*****************************************************************************/
U8 Volume;
/*****************************************************************************
Exported global variables and functions (to be accessed by other files)
*****************************************************************************/
Disp_Message DispMessage;
Disp_Message DispMsgMask;

U8 DispPlayTitle[TITLE_LENGTH];

/*****************************************************************************
Private variables and functions
*****************************************************************************/
void DecToStr(U16 data, U8 *str,U8 bit);
void DecToStrSign(S16 data, U8 *str,U8 bit);
void Strformat2(U8 * destbuf, U16 data1,U16 data2, U8 *str,U8 bit);
void Strformat3(U8 * destbuf, U16 data1,U16 data2, U16 data3, U8 *str,U8 bit);

/******************************************************************/
/***********Widget setting Unite***********************************/

/***********Draw song title****************************************/
/*-Raw data-*/
/*NULL*/
/*-message process function-*/
/*NULL*/
/*-initialize function-*/
void WidgetTitleInit(void);
/*NULL*/
/*-paint function-*/
void TitlePaint(U8 mode);
/*-Timer-*/
 U32 RollTimer;		
 U8  TimerEnable;
 S16 RollPos;
 S16 Rolloffent;
 void TitleTimerPro(void);
 const Disp_WidgetTimer TitleTimer = {(U32)50,(U8)2,(U8)0,TitleTimerPro,&RollTimer,&TimerEnable,RAWDATA_NULL};

 /*Define widget*/
 const Disp_WidgetType WidgetTitle ={POS_WIDGET_TITLE_X,POS_WIDGET_TILLE_Y,POS_WIDGET_TITLE_WIDTH,POS_WIDGET_TITLE_HIGHT,RAWDATA_NULL,MSGPROC_NULL,WidgetTitleInit,TitlePaint,&TitleTimer};
 /********Title widget end**************************************************/

#if 0 
  void TitleMsgPro(Disp_Message Msg)
  {
	  switch(Msg)
	  {
	  case DISP_MSG_FILE_CHANGE:
		  if(Dispinfo.currentFile.InfoUpdate)
		  {
			  WidgetTitle.Init();
			  WidgetTitle.Paint(UPDATA);
		  }else
		  {
			  /*nothing*/
		  }
		  break;
	  default:
		  break;
	  }
  }
#endif

#if 0
/*****************************************************************************
* ID					 : 1.0
* Outline				 : disp widget
* Include				 : none
* Declaration			 : void MergeTitle(void)
* Description			 : disp widget
* Argument 			 : void
* Return Value 		 : void
* Calling Functions	 : none
*****************************************************************************/
void MergeTitle(U8 *DispBuf,U8 *ArtistBuf,U8 *TitleBuf,U8 DispBufLen)
{
	U8 copylen=0;

	while (*ArtistBuf)
	{
		*DispBuf = *ArtistBuf;
		copylen++;
		if (copylen == DispBufLen)
		{
			*DispBuf = '.';
			return;
		}
		DispBuf++;
		ArtistBuf++;
	}
	*DispBuf = '-';
	*DispBuf++;


}
#endif
/*****************************************************************************
* ID					 : 1.0
* Outline				 : disp widget
* Include				 : none
* Declaration			 : void WidgetTitleInit(void)
* Description			 : disp widget
* Argument 			 : void
* Return Value 		 : void
* Calling Functions	 : none
*****************************************************************************/
 void WidgetTitleInit(void)
 {
	 U8 TitleLen;
	 RollTimer = CurrentTimer;

	 /*If havn't taginfo ,then use file name*/
	 if (Dispinfo.currentFile.tagInfo.title.length<(U8)2)
	 {
		 /*length limit*/
		 if (Dispinfo.currentFile.fileNameInfo.nameLength>(sizeof(DispPlayTitle)-(U8)2))
		 {
			 TitleLen = sizeof(DispPlayTitle)-(U8)2;
		 }else
		 {
			 TitleLen = Dispinfo.currentFile.fileNameInfo.nameLength;
		 }
		 /*clear title str buf and copy str*/
		 memset(DispPlayTitle,0,sizeof(DispPlayTitle));
		 memcpy(DispPlayTitle,Dispinfo.currentFile.fileNameInfo.Name,TitleLen);

		 /*str characters convert*/
		 if (Dispinfo.currentFile.fileNameInfo.nameCharacterCode == UTF_16LE )
		 {
			 ConvertUnicodeToGBCode(DispPlayTitle,(U16)Dispinfo.currentFile.fileNameInfo.nameLength,LITTLE_ENDIAN);
		 }else
		 {
			 memset(DispPlayTitle,0,sizeof(DispPlayTitle));
		 }
		 
	 }else/*if have tag info ,then draw title and artist*/
	 {
		 /*Convert code*/
		 switch(Dispinfo.currentFile.tagInfo.title.characterCode)
		 {
		 case UNICODE_UTF16_BE:
			 ConvertUnicodeToGBCode(Dispinfo.currentFile.tagInfo.title.name,(U16)Dispinfo.currentFile.tagInfo.title.length,BIG_ENDIAN);
			 ConvertUnicodeToGBCode(Dispinfo.currentFile.tagInfo.artistName.name,(U16)Dispinfo.currentFile.tagInfo.artistName.length,BIG_ENDIAN);
			 Dispinfo.currentFile.tagInfo.title.characterCode = ISO8859;
		 	break;
		 case UNICODE_UTF16_LE:
			 ConvertUnicodeToGBCode(Dispinfo.currentFile.tagInfo.title.name,(U16)Dispinfo.currentFile.tagInfo.title.length,LITTLE_ENDIAN);
			 ConvertUnicodeToGBCode(Dispinfo.currentFile.tagInfo.artistName.name,(U16)Dispinfo.currentFile.tagInfo.artistName.length,LITTLE_ENDIAN);
			 Dispinfo.currentFile.tagInfo.title.characterCode = ISO8859;
		    break;
		 case UNICODE_UTF16_WITH_BOM:
			 if (Dispinfo.currentFile.tagInfo.title.name[0] == 0xff)
			 {
				 ConvertUnicodeToGBCode(Dispinfo.currentFile.tagInfo.title.name,(U16)Dispinfo.currentFile.tagInfo.title.length,LITTLE_ENDIAN);
				 ConvertUnicodeToGBCode(Dispinfo.currentFile.tagInfo.artistName.name,(U16)Dispinfo.currentFile.tagInfo.artistName.length,LITTLE_ENDIAN);
			 }else
			 {
				 ConvertUnicodeToGBCode(Dispinfo.currentFile.tagInfo.title.name,(U16)Dispinfo.currentFile.tagInfo.title.length,BIG_ENDIAN);
				 ConvertUnicodeToGBCode(Dispinfo.currentFile.tagInfo.artistName.name,(U16)Dispinfo.currentFile.tagInfo.artistName.length,BIG_ENDIAN);
			 }
			 Dispinfo.currentFile.tagInfo.title.characterCode = ISO8859;
		 	break;
		 case UNICODE_UTF8:
			 ConvertUTF8ToGBCode(Dispinfo.currentFile.tagInfo.title.name,(U16)Dispinfo.currentFile.tagInfo.title.length,Dispinfo.currentFile.tagInfo.title.name,(U16)Dispinfo.currentFile.tagInfo.title.length);
			 ConvertUTF8ToGBCode(Dispinfo.currentFile.tagInfo.artistName.name,(U16)Dispinfo.currentFile.tagInfo.artistName.length,Dispinfo.currentFile.tagInfo.artistName.name,(U16)Dispinfo.currentFile.tagInfo.artistName.length);
			 Dispinfo.currentFile.tagInfo.title.characterCode = ISO8859;
			 break;
		 case ISO8859:
		    break;
		 case UNKOWN:
			break;
		 default:
		    break;
		 }
		 /*clear str buf and copy info*/
		 memset(DispPlayTitle,0,sizeof(DispPlayTitle));
		 if(Dispinfo.currentFile.tagInfo.artistName.length<TITLE_LENGTH-1U)
		 {
			strcpy(DispPlayTitle,Dispinfo.currentFile.tagInfo.artistName.name);
			if ((Dispinfo.currentFile.tagInfo.title.length+Dispinfo.currentFile.tagInfo.artistName.length)<((U8)TITLE_LENGTH-(U8)2))
			{
				strcat(DispPlayTitle,"-");
				strcat(DispPlayTitle,Dispinfo.currentFile.tagInfo.title.name);
			}else
			{
				strcat(DispPlayTitle,"-");
				TitleLen = ((U8)TITLE_LENGTH-(Dispinfo.currentFile.tagInfo.artistName.length+(U8)2));
				strncat(DispPlayTitle,Dispinfo.currentFile.tagInfo.title.name,TitleLen);
				DispPlayTitle[(U8)TITLE_LENGTH-(U8)1] = (U8)0x00;
			}
		 }else
		 {
			strncpy(DispPlayTitle,Dispinfo.currentFile.tagInfo.artistName.name,TITLE_LENGTH-1U);
		 }
		 

		 
	 }

	 /*calc str disp length, check if need roll*/
	 Rolloffent = (S16)GetDrawTextWidthA(DispPlayTitle,FONT24);
	 if (Rolloffent>(S16)OLED_MAXLINE)
	 {
		 TimerEnable = TRUE;
		 /*left most on screen*/
		 Rolloffent = Rolloffent-(((S16)OLED_MAXLINE+(S16)FONT24)-(S16)32);
		 RollPos = (S16)FONT24;
	 }else
	 {
		 TimerEnable = FALSE;
		 /*center on screen*/
		 RollPos =(S16)16+(((S16)OLED_MAXLINE-Rolloffent)/2);

	 }


 }
 
 /*****************************************************************************
 * ID					 : 1.0
 * Outline				 : display widget
 * Include				 : none
 * Declaration			 : void TitlePaint(U8 mode)
 * Description			 : display widget
 * Argument 			 : U8 mode
 * Return Value 		 : void
 * Calling Functions	 : none
 *****************************************************************************/
 void TitlePaint(U8 mode)
 {
	 /*clear title zone*/	 	 
	 LCD_DrawBox(WidgetTitle.PosX,WidgetTitle.PoxY,OLED_MAXLINE,WidgetTitle.PoxY+FONT24,(U8)1,(U8)0x00,(U8)0x00);
	 
	 LCD_TextA(DispPlayTitle,WidgetTitle.PosX+(U16)RollPos,WidgetTitle.PoxY,FONT24);
	 
 }

 /*****************************************************************************
 * ID					 : 1.0
 * Outline				 : display widget
 * Include				 : none
 * Declaration			 : void TitleTimerPro(void)
 * Description			 : display widget
 * Argument 			 : U8 mode
 * Return Value 		 : void
 * Calling Functions	 : none
 *****************************************************************************/
 void TitleTimerPro(void)
 {

	 /*if taginfo is updateing,then do nothing*/
	 if(Dispinfo.currentFile.InfoUpdate)
	 {
		 LCD_Draw_TextRoll24(DispPlayTitle,(S16)WidgetTitle.PosX+RollPos,WidgetTitle.PoxY,(U16)Rolloffent);
		 RollPos--;
		 if (RollPos==((S16)0-Rolloffent))
		 {
			 RollPos = (S16)(OLED_MAXLINE+FONT24);
		 }
	 }else
	 {
		/*nothing*/
	 }
 }


#if 0
 /***********Draw song album***************************************/
 /*-Raw data-*/
 /*NULL*/
 /*-message process function-*/
 void AlbumMsgPro(Disp_Message Msg);
 /*-initialize function-*/
  void WidgetAlbumInit();
 /*NULL*/
 /*-paint function-*/
 void AlbumPaint(U8 mode);
 /*-Timer-*/
 U32 RollTimer_Album;		
 U8  TimerEnable_Album;
 S16 RollPos_Album;
 void AlbumTimerPro();
 const Disp_WidgetTimer AlbumTimer = {100,2,0,AlbumTimerPro,&RollTimer_Album,&TimerEnable_Album,RAWDATA_NULL};

 /*NULL*/
 /*-Define widget-*/
 const Disp_WidgetType WidgetAlbum ={0U,16U,0U,0U,RAWDATA_NULL,AlbumMsgPro,INITFUNC_NULL,AlbumPaint,TIMER_NULL};
 /********Album widget end**************************************************/
 void AlbumMsgPro(Disp_Message Msg)
 {
	 switch(Msg)
	 {
	 case DISP_MSG_FILE_CHANGE:
		 WidgetAlbum.Paint(UPDATA);
		 break;
	 default:
		 break;
	 }
 }
 void WidgetAlbumInit()
 {
	 RollTimer_Album = CurrentTimer;
	 TimerEnable_Album = 0;

 }

 void AlbumTimerPro()
 {
	 //LCD_Draw_TextRoll((U16*)Dispinfo.currentFile.tagInfo.AlbumName.name,WidgetAlbum.PosX+RollPos_Album,WidgetAlbum.PoxY,40);
	 RollPos_Album--;
	 if (RollPos_Album==-40)
	 {
		 RollPos_Album = 255+16;

	 }
 }
 void AlbumPaint(U8 mode)
 {
	 U16 StrDispWidth;
	 U16 AlbumBuf[64];
	 U16 PosOffset;

	 LCD_DrawBox(WidgetAlbum.PosX,WidgetAlbum.PoxY,OLED_MAXLINE,WidgetAlbum.PoxY+FONT16,1,0x00,0x00);

	 if (Dispinfo.currentFile.tagInfo.AlbumName.length == 0)
	 {
		 return;
	 }

	 StrDispWidth = GetDrawTextWidthA(Dispinfo.currentFile.tagInfo.AlbumName.name,FONT24);

	 if (StrDispWidth>ALBUM_MAX_NUM*8)
	 {
		 memset(AlbumBuf,0,sizeof(AlbumBuf));
		 memcpy(AlbumBuf,Dispinfo.currentFile.tagInfo.AlbumName.name,ALBUM_MAX_NUM*2);
		 AlbumBuf[ALBUM_MAX_NUM]=CODE_ELLIPSIS;
		 LCD_TextW(AlbumBuf,WidgetAlbum.PosX,WidgetAlbum.PoxY,FONT16);

	 } 
	 else
	 {
		 PosOffset = 16+(256-StrDispWidth)/2;
		 LCD_TextW((U16*)Dispinfo.currentFile.tagInfo.AlbumName.name,WidgetAlbum.PosX+PosOffset,WidgetAlbum.PoxY,FONT16);

	 }
 }
#endif
 /*************Draw Disk ***************************************************/
 /*-Raw data-*/
 /*NULL*/
 /*-message process function-*/
 /*void MsgDiskProc(Disp_Message Msg);*/
 /*-initialize function-*/
 void DiskWidgetInit( void);
 /*-paint function-*/
 void DiskPaint(U8 mode);
 /*-Timer-*/
 /*NULL*/
 /*-Define widget-*/
 const Disp_WidgetType WidgetDisp ={POS_WIDGET_DISK_X,POS_WIDGET_DISK_Y,POS_WIDGET_DISK_WIDTH,POS_WIDGET_DISK_HIGHT,RAWDATA_NULL,MSGPROC_NULL,DiskWidgetInit,DiskPaint,TIMER_NULL};

 /***********Disk widget end********************************************/

#if 0
void MsgDiskProc(Disp_Message Msg)
{
	switch(Msg)
	{
	case DISP_MSG_DISK_CHANGE:
		WidgetDisp.Paint(UPDATA);
		break;
	default:
	    break;
	}
}
#endif

void DiskWidgetInit(void)
{

}

/*****************************************************************************
* ID					 : 1.0
* Outline				 : display widget
* Include				 : none
* Declaration			 : void DiskPaint(U8 mode)
* Description			 : display widget
* Argument 			 : U8 mode
* Return Value 		 : void
* Calling Functions	 : none
*****************************************************************************/
void DiskPaint(U8 mode)
{
	const U8 * ModeBuf;
	U8 DiskSDMode;
	U8 DiskUSBMode;

	/*Get disk mode*/
	if (Dispinfo.sd.connectSts == CONNECTED)
	{
		if(Dispinfo.currentFile.device == SD)
		{
			DiskSDMode = DISK_SD_ACTIV;
		}else
		{
			DiskSDMode = DISK_SD_LINK;
		}

	}else
	{
		DiskSDMode = DISK_SD_UNLINK;
	}

	if (Dispinfo.usb.connectSts == CONNECTED)
	{
		
		if (Dispinfo.currentFile.device == USB)
		{
			DiskUSBMode = DISK_USB_ACTIV;
		}else
		{
			DiskUSBMode = DISK_USB_LINK;
		}
	} 
	else
	{
		DiskUSBMode = DISK_USB_UNLINK;
	}

	switch(DiskSDMode)
	{
	case DISK_SD_UNLINK:
		ModeBuf ="\x80\x00";
		break;
	case DISK_SD_LINK:
		ModeBuf =CODE_MODE_SD;
		break;
	case DISK_SD_ACTIV:
		ModeBuf =CODE_MODE_SDR;
		break;
	default:
		ModeBuf ="\x80\x00";
		break;
	}

	LCD_TextA(ModeBuf,POS_DISK_SD_X,POS_DISK_SD_Y,FONT16);

	switch(DiskUSBMode)
	{
	case DISK_USB_UNLINK:
		ModeBuf="\x80\x00";
		break;
	case DISK_USB_LINK:
		ModeBuf=CODE_MODE_USB;
		break;
	case DISK_USB_ACTIV:
		ModeBuf=CODE_MODE_USBR;
		break;
	default:
		ModeBuf="\x80\x00";
		break;
	}

	LCD_TextA(ModeBuf,POS_DISK_USB_X,POS_DISK_USB_Y,FONT16);

	if ((DiskSDMode == DISK_SD_UNLINK)&&(DiskUSBMode == DISK_USB_UNLINK))
	{
		DispMessage |= DISP_MSG_WARN_NOMEDIA;
	}

}


/**************Draw play mode ************************************************/
#define ORDER_RANDOM 0
#define ORDER_LOOP	 1
#define ORDER_SCAN   2
/*-Raw data-*/
/*NULL*/
/*-message process function-*/
/*void MsgPlayModeProc(Disp_Message Msg);*/
/*-initialize function-*/
/*void PlayModeWidgetInit();*/
/*-paint function-*/
void PlayModePaint(U8 mode);
/*-Timer-*/
/*NULL*/
/*-Define widget-*/
const Disp_WidgetType WidgetPlayMode ={POS_WIDGET_PLAYMODE_X,POS_WIDGET_PLAYMODE_Y,POS_WIDGET_PLAYMODE_WIDTH,POS_WIDGET_PLAYMODE_HIGHT,RAWDATA_NULL,MSGPROC_NULL,INITFUNC_NULL,PlayModePaint,TIMER_NULL};

/***********Widget Play mode end**********************************/
#if 0
void MsgPlayModeProc(Disp_Message Msg)
{
	switch(Msg)
	{
	case DISP_MSG_PLAYMODE_CHANGE:
		PlayModePaint(UPDATA);
		break;
	default:
	    break;
	}
}
#endif

/*****************************************************************************
* ID					 : 1.0
* Outline				 : display widget
* Include				 : none
* Declaration			 : void PlayModePaint(U8 mode)
* Description			 : display widget
* Argument 			 : U8 mode
* Return Value 		 : void
* Calling Functions	 : none
*****************************************************************************/
void PlayModePaint(U8 mode)
{
	const U8 * PlayMode;

	/*draw random ico*/
	if (TPlayState.U8EnableRandom)
	{
		PlayMode = CODE_MODE_RANDOM;
	}else
	{
		PlayMode = CODE_SPACE;
	}

	LCD_TextA(PlayMode,POS_PLAY_MODE_RANDOM_X,POS_PLAY_MODE_Y,FONT16);
	/*draw scan ico*/
	if (TPlayState.U8EnableScan)
	{
		PlayMode = CODE_MODE_SCN;
	} 
	else
	{
		PlayMode = CODE_SPACE;
	}
	LCD_TextA(PlayMode,POS_PLAY_MODE_SCAN_X,POS_PLAY_MODE_Y,FONT16);

	/*draw repeat ico*/
	switch(TPlayState.U8RepeatMode)
	{
	case REPEAT_MODE1_SINGLE_1FOLDER:
		PlayMode = CODE_MODE_ORDER;
		break;
	case REPEAT_MODE2_CYCLE_1FOLDER:
		PlayMode = CODE_MODE_LOOP;
		break;
	case REPEAT_MODE3_SINGLE_FILE:
		PlayMode = CODE_MODE_SINGLE;
	    break;
	case REPEAT_MODE4_SINGLE_ALLFOLDER:
		PlayMode = CODE_MODE_ALLORDER;
	    break;
	case REPEAT_MODE5_CYCLE_ALLFOLDER:
		PlayMode = CODE_MODE_ALLLOOP;
		break;
	default:
		PlayMode = CODE_SPACE;
	    break;
	}


	LCD_TextA(PlayMode,POS_PLAY_MODE_LOOP_X,POS_PLAY_MODE_Y,FONT16);

}






#define U8VOLUME TEVData.S8Volume
/**************Draw volume ****************************************/
/*-Raw data-*/
/*NULL*/
/*-message process function-*/
/*void MsgVolumeProc(Disp_Message Msg);*/
/*-initialize function-*/
void VolumeInit();
/*void PlayModeWidgetInit();*/
/*-paint function-*/
void VolumePaint(U8 mode);
/*-Timer-*/

U32 VolumeTimerCnt;		
U8  VolumeTimerEnable;
void VolumeTimerPro(void);
const Disp_WidgetTimer VolumeTimer = {1000U,0U,0U,VolumeTimerPro,&VolumeTimerCnt,&VolumeTimerEnable,RAWDATA_NULL};

/*NULL*/
/*-Define widget-*/
const Disp_WidgetType WidgetVolume ={POS_WIDGET_VOLUME_X,POS_WIDGET_VOLUME_Y,POS_WIDGET_VOLUME_WIDTH,POS_WIDGET_VOLUME_HIGHT,RAWDATA_NULL,MSGPROC_NULL,VolumeInit,VolumePaint,&VolumeTimer};

U8 VolumeTitleTimerCheck;
/***************Widget volume end****************************************/
#define POS_PLAY_SPEEK_PULLUP_X 60U
#define POS_PLAY_SPEEK_PULLUP_Y (8U+64U)
#define POS_PLAY_SPEEK_PULLUP_HIGHT 42U
#define POS_PLAY_SPEEK_PULLUP_WIDTH 148U

/*****************************************************************************
* ID					 : 1.0
* Outline				 : display widget
* Include				 : none
* Declaration			 : void VolumePullup(U8 mode)
* Description			 : display widget
* Argument 			 : U8 mode
* Return Value 		 : void
* Calling Functions	 : none
*****************************************************************************/
void VolumePullup(U8 mode)
{
	U8 buf[10];
	U8 u8_i;
	U8 VLevel;

	if(mode == REDRAW)
	{	
		/*Draw Box*/
		/*LCD_DrawBox(POS_PLAY_SPEEK_PULLUP_X-1,POS_PLAY_SPEEK_PULLUP_Y,POS_PLAY_SPEEK_PULLUP_X+POS_PLAY_SPEEK_PULLUP_WIDTH,POS_PLAY_SPEEK_PULLUP_Y+POS_PLAY_SPEEK_PULLUP_HIGHT,1,0x08,0x00);*/

		/*Draw speek ico*/
		LCD_TextA(CODE_SPEEK_OFF,POS_PLAY_SPEEK_PULLUP_X+16U+4U,POS_PLAY_SPEEK_PULLUP_Y+POS_PLAY_SPEEK_PULLUP_HIGHT-20U,FONT16);
		LCD_TextA(CODE_SPEEK_ON,POS_PLAY_SPEEK_PULLUP_X+POS_PLAY_SPEEK_PULLUP_WIDTH+16U-20U,POS_PLAY_SPEEK_PULLUP_Y+POS_PLAY_SPEEK_PULLUP_HIGHT-20U,FONT16);
	}
	/*Draw Volume num*/
	DecToStr(U8VOLUME,buf,(U8)2);
	LCD_TextA(buf,POS_PLAY_SPEEK_PULLUP_X+POS_PLAY_SPEEK_PULLUP_WIDTH/2U-2U,POS_PLAY_SPEEK_PULLUP_Y+2U,FONT24);
	/*Draw delight bar*/
	VLevel = (U8)U8VOLUME/(RANGE_VOLUME_MAX/(U8)20);
	for (u8_i=(U8)0;u8_i<(U8)20;u8_i++)
	{
		if (u8_i<=VLevel)
		{
			LCD_DrawLineT(POS_PLAY_SPEEK_PULLUP_X+30U+u8_i*4U,POS_PLAY_SPEEK_PULLUP_Y+POS_PLAY_SPEEK_PULLUP_HIGHT-5U-u8_i,POS_PLAY_SPEEK_PULLUP_X+30U+u8_i*4U,POS_PLAY_SPEEK_PULLUP_Y+POS_PLAY_SPEEK_PULLUP_HIGHT-5U,0x0cU);
			LCD_DrawLineT(POS_PLAY_SPEEK_PULLUP_X+30U+u8_i*4U+1U,POS_PLAY_SPEEK_PULLUP_Y+POS_PLAY_SPEEK_PULLUP_HIGHT-5U-u8_i,POS_PLAY_SPEEK_PULLUP_X+30U+u8_i*4U+1U,POS_PLAY_SPEEK_PULLUP_Y+POS_PLAY_SPEEK_PULLUP_HIGHT-5U,0x0cU);
		}else
		{
			LCD_DrawLineT(POS_PLAY_SPEEK_PULLUP_X+30U+u8_i*4U,POS_PLAY_SPEEK_PULLUP_Y+POS_PLAY_SPEEK_PULLUP_HIGHT-5U-u8_i,POS_PLAY_SPEEK_PULLUP_X+30U+u8_i*4U,POS_PLAY_SPEEK_PULLUP_Y+POS_PLAY_SPEEK_PULLUP_HIGHT-5U,0x03U);
			LCD_DrawLineT(POS_PLAY_SPEEK_PULLUP_X+30U+u8_i*4U+1U,POS_PLAY_SPEEK_PULLUP_Y+POS_PLAY_SPEEK_PULLUP_HIGHT-5U-u8_i,POS_PLAY_SPEEK_PULLUP_X+30U+u8_i*4U+1U,POS_PLAY_SPEEK_PULLUP_Y+POS_PLAY_SPEEK_PULLUP_HIGHT-5U,0x03U);
		}

	}
}

#if 0 
void MsgVolumeProc(Disp_Message Msg)
{
	switch(Msg)
	{
	case DISP_MSG_VOLUME_CHANGE:
		VolumePaint(UPDATA);
		VolumePullup(REDRAW);
		/* Set Timer*/
		VolumeTimerCnt = CurrentTimer;
		VolumeTimerEnable = TRUE;
		/*set mask,disenable other msg */
		DispMsgMask = DISP_MSG_VOLUME_CHANGE;

		break;
	default:
	    break;
	}
}
#endif

/*****************************************************************************
* ID					 : 1.0
* Outline				 : display widget
* Include				 : none
* Declaration			 : void VolumeInit( )
* Description			 : display widget
* Argument 			 : U8 mode
* Return Value 		 : void
* Calling Functions	 : none
*****************************************************************************/
void VolumeInit()
{
	VolumeTimerEnable = FALSE;
}
/*****************************************************************************
* ID					 : 1.0
* Outline				 : display widget
* Include				 : none
* Declaration			 : void VolumePaint(U8 mode)
* Description			 : display widget
* Argument 			 : U8 mode
* Return Value 		 : void
* Calling Functions	 : none
*****************************************************************************/
void VolumePaint(U8 mode)
{
	U8 u8_i;
	U8 buf[5];
	U8 VLevel;

	/*Draw speek ico*/
	LCD_TextA(CODE_SPEEK_ON,POS_PLAY_SPEEK_X,POS_PLAY_SPEEK_Y,FONT16);
	/*Draw speek number*/
	DecToStr((U8)U8VOLUME,buf,2U);
	LCD_TextA(buf,POS_PLAY_SPEEK_VOLUME_X,POS_PLAY_SPEEK_Y,FONT16);

	/*Draw speed bar*/
	VLevel = (U8)U8VOLUME/(RANGE_VOLUME_MAX/(U8)10);
	for (u8_i=0U;u8_i<(U8)10;u8_i++)
	{
		if (u8_i<=VLevel)
		{
			LCD_DrawLineT(POS_PLAY_SPEEK_LINE_X+u8_i*2,(POS_PLAY_SPEEK_Y+14)-u8_i,POS_PLAY_SPEEK_LINE_X+u8_i*2,POS_PLAY_SPEEK_Y+14,0x0c);
		}else
		{
			LCD_DrawLineT(POS_PLAY_SPEEK_LINE_X+u8_i*2,(POS_PLAY_SPEEK_Y+14)-u8_i,POS_PLAY_SPEEK_LINE_X+u8_i*2,POS_PLAY_SPEEK_Y+14,0x03);
		}

	}
}
/*****************************************************************************
* ID					 : 1.0
* Outline				 : display widget
* Include				 : none
* Declaration			 : void VolumeTimerPro()
* Description			 : display widget
* Argument 			 : void
* Return Value 		 : void
* Calling Functions	 : none
*****************************************************************************/
void VolumeTimerPro()
{
	LCD_DrawBox(POS_PLAY_SPEEK_PULLUP_X-1U,POS_PLAY_SPEEK_PULLUP_Y,POS_PLAY_SPEEK_PULLUP_X+POS_PLAY_SPEEK_PULLUP_WIDTH,POS_PLAY_SPEEK_PULLUP_Y+POS_PLAY_SPEEK_PULLUP_HIGHT,1U,0x00U,0x00U);
	DispMsgMask = DISP_MSG_NOMASK;
	DispMessage |= DISP_MSG_PLAYTIMER_REDRAW;
	/*Enable title timmer*/
	if (VolumeTitleTimerCheck)
	{
		TimerEnable = TRUE;
	}else
	{
		DispMessage |= DISP_MSG_FILE_CHANGE;
	}
	
}

/***************Draw Folder **********************************************/
/*-Raw data-*/
/*NULL*/
/*-message process function-*/
/*void MsgFolderProc(Disp_Message Msg);*/
/*-initialize function-*/
void FolderWidgetInit(void);
/*-paint function-*/
void FolderPaint(U8 mode);
/*-Timer-*/
/*NULL*/
/*-Define widget-*/
const Disp_WidgetType WidgetFolder ={POS_WIDGET_FOLDER_X,POS_WIDGET_FOLDER_Y,POS_WIDGET_FOLDER_WIDTH,POS_WIDGET_FOLDER_HIGHT,RAWDATA_NULL,MSGPROC_NULL,FolderWidgetInit,FolderPaint,TIMER_NULL};
/***************Widget Folder end*******************************************/
#define  POS_FILE_PULLUP_X 16
#define  POS_FILE_PULLUP_Y 64
#define  POS_FILE_PULLUP_WIDTH 216
#define  POS_FILE_PULLUP_HIGHT 56
#define  POS_FILE_PULLUP_END_X POS_FILE_PULLUP_X+POS_FILE_PULLUP_WIDTH
#define  POS_FILE_PULLUP_END_Y POS_FILE_PULLUP_Y+POS_FILE_PULLUP_HIGHT

U8 FolderPullEnable;
U8 FolderPullInit;
void FolderWidgetInit()
{
FolderPullEnable = FALSE;
FolderPullInit = FALSE;
}


#if 0
void MsgFolderProc(Disp_Message Msg)
{

	switch(Msg)
	{
	case DISP_MSG_FILE_CHANGE:
		FolderPaint(UPDATA);
		break;
	case DISP_MSG_FILE_BECHANGE:
	
		break;
	case DISP_MSG_FOLDER_CHANGE:
		if (FolderPullEnable)
		{
			FolderTimerEnable = TRUE;
			FolderTimerCnt = CurrentTimer;
			FolderTimernum = 64-32;
			FolderPullUp();

			//FolderTimerEnable = TRUE;
			//FolderTimerCnt = CurrentTimer;
			//DispMsgMask = DISP_MSG_FOLDER_CHANGE|DISP_MSG_FOLDER_PULLDOWN;
		}

		break;
	case DISP_MSG_FOLDER_PULLDOWN:
		//FolderTimerPro();
		break;
	default:
	    break;
	}

}
#endif
/*****************************************************************************
* ID					 : 1.0
* Outline				 : display widget
* Include				 : none
* Declaration			 : void FolderPaint(U8 mode)
* Description			 : display widget
* Argument 			 : U8 mode
* Return Value 		 : void
* Calling Functions	 : none
*****************************************************************************/
void FolderPaint(U8 mode)
{
	U16 CurrentFileNum;
	U16 DiskFileNum;
	U8 buf[10];
	U8 u8_i;
	memset(buf,0,sizeof(buf));

	/*Get folder file number and file number*/
	DiskFileNum = Dispinfo.currentFile.currentFolderInfo.containFileNum;
	CurrentFileNum = Dispinfo.currentFile.fileNumInCurrentFolder;

	if(DiskFileNum<(U16)100)
	{
		Strformat2(buf,CurrentFileNum,DiskFileNum,"/",(U8)2);
	}
	else if (DiskFileNum<(U16)1000)
	{
		Strformat2(buf,CurrentFileNum,DiskFileNum,"/",(U8)3);
	}
	else if (DiskFileNum>=(U16)1000)
	{
		if (CurrentFileNum<1000)
		{
			DecToStr(CurrentFileNum,buf,(U8)3);
			strcat(buf,"/***");
		}else
		{
			strcpy(buf,"***/***");
		}
	}

	/*insert space*/
	for (u8_i = strlen(buf);u8_i<(U8)7;u8_i++)
	{
		buf[u8_i] = 0x20;
	}
	

	LCD_TextA(buf,WidgetFolder.PosX,WidgetFolder.PoxY,FONT16);

#ifdef DRAWFOLDERNUM
	memset(buf,0,sizeof(buf));
	buf[0] = 'F';
	if(Dispinfo.currentFile.currentFolderInfo.folderNum<100U)
	{
		DecToStr(Dispinfo.currentFile.currentFolderInfo.folderNum,buf+1U,2U);
	}else if (Dispinfo.currentFile.currentFolderInfo.folderNum>99U)
	{
		DecToStr(Dispinfo.currentFile.currentFolderInfo.folderNum,buf+1U,3U);
	}else
	{
		strcpy(buf+1U,"***");
	}
	LCD_TextA(buf,WidgetFolder.PosX+60U,WidgetFolder.PoxY,FONT16);
#endif

}



/*************Draw play state ************************************************/
/*-Raw data-*/
/*NULL*/
/*-message process function-*/
/*void MsgPlayStateProc(Disp_Message Msg);*/
/*-initialize function-*/
/*void PlayModeWidgetInit();*/
/*-paint function-*/
void PlayStatePaint(U8 mode);
/*-Timer-*/
/*NULL*/
/*-Define widget-*/
const Disp_WidgetType WidgetPlayState ={POS_WIDGET_PLAYSTATE_X,POS_WIDGET_PLAYSTATE_Y,POS_WIDGET_PLAYSTATER_WIDTH,POS_WIDGET_PLAYSTATE_HIGHT,RAWDATA_NULL,MSGPROC_NULL,INITFUNC_NULL,PlayStatePaint,TIMER_NULL};
/***********Widget play state end*/
#if 0
void MsgPlayStateProc(Disp_Message Msg)
{
	switch(Msg)
	{
	case DISP_MSG_PLAYSTATE_CHANGE:
		PlayStatePaint(UPDATA);
		break;
	default:
	    break;
	}
}
#endif

/*****************************************************************************
* ID					 : 1.0
* Outline				 : display widget
* Include				 : none
* Declaration			 : void PlayStatePaint(U8 mode)
* Description			 : display widget
* Argument 			 : U8 mode
* Return Value 		 : void
* Calling Functions	 : none
*****************************************************************************/
void PlayStatePaint(U8 mode)
{
	const U8 * playstatebuf;

	if (Dispinfo.currentFile.PlayOrPause ==PLAY_STS_PLAYING)
	{
		playstatebuf = CODE_MODE_START;
	}else
	{
		playstatebuf = CODE_MODE_PAUSE;
	}

	LCD_TextA(playstatebuf,POS_PLAY_PAUSE_X,POS_PLAY_PAUSE_Y,FONT16);
}



/***************Draw play timer ***************************************/
/*-Raw data-*/
/*NULL*/
/*-message process function-*/
/*void MsgPlayTimerProc(Disp_Message Msg);*/
/*-initialize function-*/
/*void PlayModeWidgetInit();*/
/*-paint function-*/
void PlayTimerPaint(U8 mode);
/*-Timer-*/
/*NULL*/
/*-Define widget-*/
const Disp_WidgetType WidgetPlayTimer ={POS_WIDGET_PLAYTIMER_X,POS_WIDGET_PLAYTIMER_Y,POS_WIDGET_PLAYTIMER_WIDTH,POS_WIDGET_PLAYTIMER_HIGHT,RAWDATA_NULL,MSGPROC_NULL,INITFUNC_NULL,PlayTimerPaint,TIMER_NULL};
/***************Widget playtimer end***********/
#if 0
void MsgPlayTimerProc(Disp_Message Msg)
{
	switch(Msg)
	{
	case DISP_MSG_PLAYTIMER_CHANGE:
		if (Dispinfo.currentFile.InfoUpdate)
		{
			PlayTimerPaint(UPDATA);
		}else
		{
			/*nothing*/
		}
		break;
	case DISP_MSG_FILE_CHANGE:
	case DISP_MSG_PLAYTIMER_REDRAW:
		if (Dispinfo.currentFile.InfoUpdate)
		{
			PlayTimerPaint(REDRAW);
		}else
		{
			/*nothing*/
		}
	default:
	    break;
	}
}
#endif
/*****************************************************************************
* ID					 : 1.0
* Outline				 : display widget
* Include				 : none
* Declaration			 : void PlayTimerPaint(U8 mode)
* Description			 : display widget
* Argument 			 : U8 mode
* Return Value 		 : void
* Calling Functions	 : none
*****************************************************************************/
void PlayTimerPaint(U8 mode)
{
	U16 LineLegth;
	U8 buf[10];
	U16 second,minute,hour;
	U16 offset;

	/*Draw file time*/
	if (mode==REDRAW)
	{
		LCD_DrawBox(POS_PLAY_TIME_X,POS_PLAY_TIME_Y,256U,POS_PLAY_TIME_Y+16U,1U,0U,0U);
		if(Dispinfo.currentFile.totalPlaybackTimeInSecond>TIMER_HOUR_SECOND)
		{
			offset = (U16)24;
			hour = (U16)(Dispinfo.currentFile.totalPlaybackTimeInSecond/TIMER_HOUR_SECOND);
			minute = (U16)((Dispinfo.currentFile.totalPlaybackTimeInSecond%TIMER_HOUR_SECOND)/TIMER_MINUTE_SENCOND);
			second = (U16)(Dispinfo.currentFile.totalPlaybackTimeInSecond%TIMER_MINUTE_SENCOND);
			memset(buf,0,sizeof(buf));
			Strformat3(buf,hour,minute,second,":",(U8)2);
		}else
		{
			offset = (U16)0;
			minute = (U16)(Dispinfo.currentFile.totalPlaybackTimeInSecond/TIMER_MINUTE_SENCOND);
			second = (U16)(Dispinfo.currentFile.totalPlaybackTimeInSecond%TIMER_MINUTE_SENCOND);
			Strformat2(buf,minute,second,":",(U8)2);
		}
		LCD_TextA(buf,POS_PLAY_TIME_FILE_X+offset,POS_PLAY_TIME_Y,FONT16);
		memset(buf,0,sizeof(buf));
	}
	/*draw total time*/
	if(Dispinfo.currentFile.totalPlaybackTimeInSecond>TIMER_HOUR_SECOND)
	{
		offset = (U16)24;
		hour = (U16)(Dispinfo.currentFile.totalPlaybackTimeInSecond/TIMER_HOUR_SECOND);
		minute = (U16)((Dispinfo.currentFile.totalPlaybackTimeInSecond%TIMER_HOUR_SECOND)/TIMER_MINUTE_SENCOND);
		second = (U16)(Dispinfo.currentFile.totalPlaybackTimeInSecond%TIMER_MINUTE_SENCOND);
		memset(buf,0,sizeof(buf));
		Strformat3(buf,hour,minute,second,":",(U8)2);
	}else
	{
		offset = (U16)0;
		minute = (U16)(Dispinfo.currentFile.totalPlaybackTimeInSecond/TIMER_MINUTE_SENCOND);
		second = (U16)(Dispinfo.currentFile.totalPlaybackTimeInSecond%TIMER_MINUTE_SENCOND);
		Strformat2(buf,minute,second,":",(U8)2);
	}
	LCD_TextA(buf,POS_PLAY_TIME_FILE_X+offset,POS_PLAY_TIME_Y,FONT16);
	/*draw playback time*/
	if (Dispinfo.currentFile.totalPlaybackTimeInSecond>TIMER_HOUR_SECOND)
	{
		offset = 24U;
		hour = (U16)(Dispinfo.currentFile.PlaybackTimeInSecond/TIMER_HOUR_SECOND);
		minute = (U16)((Dispinfo.currentFile.PlaybackTimeInSecond%TIMER_HOUR_SECOND)/TIMER_MINUTE_SENCOND);
		second = (U16)(Dispinfo.currentFile.PlaybackTimeInSecond%TIMER_MINUTE_SENCOND);
		memset(buf,0,sizeof(buf));
		Strformat3(buf,hour,minute,second,":",(U8)2);
		LCD_TextA(buf,POS_PLAY_TIME_PLAYBACK_X,POS_PLAY_TIME_Y,FONT16);
	}else
	{
		offset = (U16)0;
		minute = (U16)(Dispinfo.currentFile.PlaybackTimeInSecond/TIMER_MINUTE_SENCOND);
		second = (U16)(Dispinfo.currentFile.PlaybackTimeInSecond%TIMER_MINUTE_SENCOND);
		memset(buf,0,sizeof(buf));
		Strformat2(buf,minute,second,":",(U8)2);
		LCD_TextA(buf,POS_PLAY_TIME_PLAYBACK_X,POS_PLAY_TIME_Y,FONT16);
	}
	/*Draw time line*/
	if(Dispinfo.currentFile.PlaybackTimeInSecond<Dispinfo.currentFile.totalPlaybackTimeInSecond)
	{
		LineLegth = (U16)(Dispinfo.currentFile.PlaybackTimeInSecond*POS_PLAY_TIME_LINE_WIDTH/Dispinfo.currentFile.totalPlaybackTimeInSecond);
	}else
	{
		LineLegth = POS_PLAY_TIME_LINE_WIDTH;
	}
	Draw_PlayTimeProgressFrame(POS_PLAY_TIME_LINE_X+offset,POS_PLAY_TIME_Y+6U,LineLegth,mode);

}

#if 0
//
/*************Draw play roll  ************************************************/
/*-Raw data-*/
/*NULL*/
/*-message process function-*/

/*-initialize function-*/
void PlayRollWidgetInit();
/*-paint function-*/
void PlayRollPaintPro(U8 mode);
/*-Timer-*/
U32 PlayRollTimerCnt;		
U8  PlayRollTimerEnable;
U8  PlayRollTimernum;
void PlayRollTimerPro();
const Disp_WidgetTimer PlayRollTimer = {5,2,0,PlayRollTimerPro,&PlayRollTimerCnt,&PlayRollTimerEnable,&PlayRollTimernum};

/*-Define widget-*/
const Disp_WidgetType WidgetPlayRoll ={0,0,0U,0U,RAWDATA_NULL,MSGPROC_NULL,PlayRollWidgetInit,PlayRollPaintPro,&PlayRollTimer};
/***********Widget play state end*/
void PlayRollTimerPro()
{
	static vline = 62;

	Drv_OLED_SetStartLine(vline);
	vline--;
	if (vline== 0)
	{
		vline = 62;
		If_Timer3_Stop();
	}
}
void PlayRollWidgetInit()
{
	PlayRollTimerEnable = TRUE;
}

void PlayRollPaintPro()
{

}
#endif
/************************************************************************/
/* menu                                                                     */
/************************************************************************/
#define MENU_X				(U16)16
#define MENU_TITLE_Y		WidgetSet.PoxY
#define MENU_ITEM_X			MENU_X+32
#define MENU_ITEM_Y_1		MENU_TITLE_Y+FONT16
#define MENU_ITEM_Y_2		MENU_ITEM_Y_1+FONT16
#define MENU_ITEM_Y_3		MENU_ITEM_Y_2+FONT16

typedef enum{
	MENU_NULL =0,
	MENU_SETUP,
	MENU_LANGUAGE,
	MENU_SOUND,
	MENU_LEDLIGHT,
	MENU_FILEINFO,
	MENU_SYSTEMINFO,
};

U8 Soundadjcursor;
void SetSoundAdjLFPaint(U8 mode);
void SetSoundAdjLRPaint(U8 mode);
void SetSoundAdjRFPaint(U8 mode);
void SetSoundAdjRRPaint(U8 mode);
void SetSoundAdjExitPaint(U8 mode);

void SetSoundAdjPaint(U8 mode);

const Disp_WidgetMenuItem SetSoundAdjleftfront = {0U,SetSoundAdjLFPaint,ITEMMSG_NULL,MENU_NULL};
const Disp_WidgetMenuItem SetSoundAdjleftrear = {0U,SetSoundAdjLRPaint,ITEMMSG_NULL,MENU_NULL};
const Disp_WidgetMenuItem SetSoundAdjrightfront = {0U,SetSoundAdjRFPaint,ITEMMSG_NULL,MENU_NULL};
const Disp_WidgetMenuItem SetSoundAdjrightrear = {0U,SetSoundAdjRRPaint,ITEMMSG_NULL,MENU_NULL};
const Disp_WidgetMenuItem SetSoundAdjExit = {0U,SetSoundAdjExitPaint,ITEMMSG_NULL,MENU_NULL};
const Disp_WidgetMenuItem * SetSoundAdjItems[5] = {&SetSoundAdjleftfront,&SetSoundAdjleftrear,&SetSoundAdjrightfront,&SetSoundAdjrightrear,&SetSoundAdjExit};
const Disp_WidgetMenu SetSoundAdj = {2U,5U,5U,SetSoundAdjItems,&TMsgHostToDisplay.U8CursorIndex,MENU_SETUP,SetSoundAdjPaint};

#define		POS_SETSOUNDADJ_LF_X 140U
#define		POS_SETSOUNDADJ_LF_Y 8U+MENU_TITLE_Y
#define		POS_SETSOUNDADJ_LR_X POS_SETSOUNDADJ_LF_X
#define		POS_SETSOUNDADJ_LR_Y POS_SETSOUNDADJ_LF_Y+35U
#define		POS_SETSOUNDADJ_RF_X POS_SETSOUNDADJ_LF_X+108U
#define		POS_SETSOUNDADJ_RF_Y POS_SETSOUNDADJ_LF_Y
#define		POS_SETSOUNDADJ_RR_X POS_SETSOUNDADJ_RF_X
#define		POS_SETSOUNDADJ_RR_Y POS_SETSOUNDADJ_LR_Y

void SetLanguageCHNPaint(U8 mode);
void SetLanguageENPaint(U8 mode);

const Disp_WidgetMenuItem SetLanguageCHN = {5U,SetLanguageCHNPaint,ITEMMSG_NULL,MENU_NULL};
const Disp_WidgetMenuItem SetLanguageEN = {6U,SetLanguageENPaint,ITEMMSG_NULL,MENU_NULL};
const Disp_WidgetMenuItem SetLanguageExit = {15U,ITEMPAINT_NULL,ITEMMSG_NULL,MENU_NULL};
const Disp_WidgetMenuItem * SetLanguageItems[3] = {&SetLanguageCHN,&SetLanguageEN,&SetLanguageExit};
const Disp_WidgetMenu	  SetLanguage = {1U,3U,3U,SetLanguageItems,&TMsgHostToDisplay.U8CursorIndex,MENU_SETUP,ITEMPAINT_NULL};

void SetDelightChgPaint(U8 mode);
void SetDelightPaint(U8 mode);
const Disp_WidgetMenuItem SetDelightChg = {0U,SetDelightChgPaint,ITEMMSG_NULL,MENU_NULL};
const Disp_WidgetMenuItem * SetDelightItems[1] = {&SetDelightChg};
const Disp_WidgetMenu	  SetDelight ={3U,1U,3U,SetDelightItems,&TMsgHostToDisplay.U8CursorIndex,MENU_SETUP,SetDelightPaint};

void SetFileInfoPaint(U8 mode);
void SetSystemInfoPaint(U8 mode);
const Disp_WidgetMenu SetFileInfo = {11U,0U,1U,ITEMS_NULL,&TMsgHostToDisplay.U8CursorIndex,MENU_SETUP,SetFileInfoPaint};
const Disp_WidgetMenu SetSystemInfo = {12U,0U,1U,ITEMS_NULL,&TMsgHostToDisplay.U8CursorIndex,MENU_SETUP,SetSystemInfoPaint};
U8 SettPage;
const Disp_WidgetMenuItem SetLanguageItem = {1U,ITEMPAINT_NULL,ITEMMSG_NULL,MENU_LANGUAGE} ;
const Disp_WidgetMenuItem SetSoundItem = {2U,ITEMPAINT_NULL,ITEMMSG_NULL,MENU_SOUND};
const Disp_WidgetMenuItem SetLedlightItem = {3U,ITEMPAINT_NULL,ITEMMSG_NULL,MENU_LEDLIGHT};
const Disp_WidgetMenuItem SetFileInfoItem = {11U,ITEMPAINT_NULL,ITEMMSG_NULL,MENU_FILEINFO};
const Disp_WidgetMenuItem SetSystemInfoItem = {12U,ITEMPAINT_NULL,ITEMMSG_NULL,MENU_SYSTEMINFO};
const Disp_WidgetMenuItem * SetItem[6] = {&SetLanguageItem,&SetSoundItem,&SetLedlightItem,&SetFileInfoItem,&SetSystemInfoItem,&SetLanguageExit};
const Disp_WidgetMenu	Setting= {4U,6U,3U,SetItem,&TMsgHostToDisplay.U8CursorIndex,MENU_NULL,ITEMPAINT_NULL};

const Disp_WidgetMenu *Menus[6] = {&Setting,&SetLanguage,&SetSoundAdj,&SetDelight,&SetFileInfo,&SetSystemInfo};


Disp_WidgetMenu const * CurrentSetup;



/*************Draw Menu ************************************************/
/*-Raw data-*/
/*NULL*/
/*-message process function-*/
void MsgSetProc(Disp_Message Msg);
/*-initialize function-*/
void SetWidgetInit(void);
/*-paint function-*/
void SetPaint(U8 mode);
/*-Timer-*/
/*NULL*/
/*-Define widget-*/
const Disp_WidgetType WidgetSet ={POS_WIDGET_MENU_X,POS_WIDGET_MENU_Y,POS_WIDGET_MENU_WIDTH,POS_WIDGET_MENU_HIGHT,RAWDATA_NULL,MsgSetProc,SetWidgetInit,SetPaint,TIMER_NULL};
/***********Widget play state end*/
#define MAXITEMPER CurrentSetup->MaxItemPerscreen
/*****************************************************************************
* ID					 : 1.0
* Outline				 : display widget
* Include				 : none
* Declaration			 : void SetPaint(U8 mode)
* Description			 : display widget
* Argument 			 : U8 mode
* Return Value 		 : void
* Calling Functions	 : none
*****************************************************************************/
void SetPaint(U8 mode)
{
	U8 u8_i;
	U8 currentpage;
	U8 currentcursor;
	U8 buf[5];


	/*Clear Disp*/
	LCD_DrawBox(0U,WidgetSet.PoxY,256U,WidgetSet.PoxY+64U,1U,0U,0U);

	/*Draw Menu title number*/

	/*Draw Menu title text*/
	LCD_TextA(Msgstr[CurrentSetup->MenuNameNo],MENU_X,MENU_TITLE_Y,FONT16);
	
	/*Draw Menu paint spec*/
	if (CurrentSetup->MenuPaint!=ITEMPAINT_NULL)
	{
		CurrentSetup->MenuPaint(REDRAW);
	}

	/*Draw Menu item*/
	currentpage = *CurrentSetup->Cursor/MAXITEMPER;
	currentcursor = *CurrentSetup->Cursor%MAXITEMPER;

	for (u8_i=0U;u8_i< MAXITEMPER;u8_i++)
	{
		if(currentpage*MAXITEMPER+u8_i<CurrentSetup->ItemNum)
		{
			/*draw item text*/
			LCD_TextA(Msgstr[CurrentSetup->Items[currentpage*MAXITEMPER+u8_i]->ItemNameNo],MENU_ITEM_X,MENU_ITEM_Y_1+FONT16*u8_i,FONT16);
			/*draw item spec*/
			if (CurrentSetup->Items[currentpage*MAXITEMPER+u8_i]->ItemPaint!=ITEMPAINT_NULL)
			{
				CurrentSetup->Items[currentpage*MAXITEMPER+u8_i]->ItemPaint(REDRAW);
			}

			/*Draw cur ico*/
			if(CurrentSetup->Items[currentpage*MAXITEMPER+u8_i]->ItemNameNo !=0)
			{
				if (currentcursor == u8_i)
				{
					LCD_TextA("\x8f\x00",MENU_X,MENU_ITEM_Y_1+FONT16*u8_i,FONT16);
				} 
				else
				{
					LCD_TextA("\x80\x00",MENU_X,MENU_ITEM_Y_1+FONT16*u8_i,FONT16);
				}
			}
		}
	}

	
}

/*****************************************************************************
* ID					 : 1.0
* Outline				 : display widget
* Include				 : none
* Declaration			 : void SetWidgetInit(void)
* Description			 : display widget
* Argument 			 : void
* Return Value 		 : void
* Calling Functions	 : none
*****************************************************************************/
void SetWidgetInit()
{
	SettPage = 0;
	CurrentSetup = &Setting;
}


/*****************************************************************************
* ID					 : 1.0
* Outline				 : display widget
* Include				 : none
* Declaration			 : void MsgSetProc(Disp_Message Msg)
* Description			 : display widget
* Argument 			 : void
* Return Value 		 : void
* Calling Functions	 : none
*****************************************************************************/
void MsgSetProc(Disp_Message Msg)
{
	U8 u8_i;
	U8 Currentcursor;
	U8 MenuNo;
	U8 currentPage;

	switch(Msg)
	{
	case DISP_MSG_MENU_ITEM_CHANGE:

		currentPage = *CurrentSetup->Cursor/MAXITEMPER;

		/*change page*/
		if(SettPage!=currentPage)
		{
			LCD_DrawBox(MENU_X-16,MENU_ITEM_Y_1,OLED_MAXLINE,MENU_ITEM_Y_1+FONT16*3,1,0x00,0x00);
			for (u8_i = 0;u8_i<MAXITEMPER;u8_i++)
			{
				/*Draw new item*/
				if(currentPage*MAXITEMPER+u8_i<CurrentSetup->ItemNum)
					LCD_TextA(Msgstr[CurrentSetup->Items[currentPage*MAXITEMPER+u8_i]->ItemNameNo],MENU_ITEM_X,MENU_ITEM_Y_1+FONT16*u8_i,FONT16);
		
			}
		}

		for (u8_i = 0;u8_i<MAXITEMPER;u8_i++)
		{
			if(currentPage*MAXITEMPER+u8_i<CurrentSetup->ItemNum)
			{
				Currentcursor = *CurrentSetup->Cursor%MAXITEMPER;
				if(CurrentSetup->Items[currentPage*MAXITEMPER+u8_i]->ItemNameNo!=0)
				{
					if (Currentcursor == u8_i)
					{
						LCD_TextA("\x8f\x00",MENU_X,MENU_ITEM_Y_1+FONT16*(u8_i),FONT16);
					} 
					else
					{
						LCD_TextA("\x80\x00",MENU_X,MENU_ITEM_Y_1+FONT16*(u8_i),FONT16);
					}
				}
				
				if (CurrentSetup->Items[currentPage*MAXITEMPER+u8_i]->ItemPaint!=ITEMPAINT_NULL)
				{
					CurrentSetup->Items[currentPage*MAXITEMPER+u8_i]->ItemPaint(REDRAW);
				}
			}
			
		}
		
		SettPage = currentPage;
		break;
	case DISP_MSG_MENU_ITEM:
		MenuNo = TMsgHostToDisplay.U8MenuID; //CurrentSetup->Items[*CurrentSetup->Cursor]->SubMenuNo;
		if (MenuNo<6)
		{
			CurrentSetup = Menus[MenuNo];
			SetPaint(UPDATA);
		}

	    break;

	case DISP_MSG_MENU_ITEM_IN:
		MenuNo = TMsgHostToDisplay.U8MenuID;
		CurrentSetup = Menus[MenuNo];
		SetPaint(UPDATA);
		
		break;

	case DISP_MSG_MENU_ITEM_REDRAW:
		if(CurrentSetup->Items[*CurrentSetup->Cursor]->ItemPaint!= ITEMPAINT_NULL)
			CurrentSetup->Items[*CurrentSetup->Cursor]->ItemPaint(UPDATA);
		break;
	default:
	    break;
	}
}


void SetLanguageENPaint(U8 mode)
{
		switch(TSettingPara.U8Language)
		{
		case SET_LANGUAGE_1_ENGLISH:
			Msgstr = MsgEn;
			LCD_TextA_Rev(Msgstr[6],MENU_ITEM_X,MENU_ITEM_Y_2,FONT16,0);
			LCD_TextA(Msgstr[5],MENU_ITEM_X,MENU_ITEM_Y_1,FONT16);
			break;
		case SET_LANGUAGE_0_SIM_CHINESE:
			Msgstr = MsgCh;
			LCD_TextA_Rev(Msgstr[5],MENU_ITEM_X,MENU_ITEM_Y_1,FONT16,0);
			LCD_TextA(Msgstr[6],MENU_ITEM_X,MENU_ITEM_Y_2,FONT16);
			break;
		default:
			Msgstr = MsgEn;
			break;
		}
	
	
}

void SetLanguageCHNPaint(U8 mode)
{
		switch(TSettingPara.U8Language)
		{
		case SET_LANGUAGE_1_ENGLISH:
			Msgstr = MsgEn;
			LCD_TextA_Rev(Msgstr[6],MENU_ITEM_X,MENU_ITEM_Y_2,FONT16,0);
			LCD_TextA(Msgstr[5],MENU_ITEM_X,MENU_ITEM_Y_1,FONT16);
			break;
		case SET_LANGUAGE_0_SIM_CHINESE:
			Msgstr = MsgCh;
			LCD_TextA_Rev(Msgstr[5],MENU_ITEM_X,MENU_ITEM_Y_1,FONT16,0);
			LCD_TextA(Msgstr[6],MENU_ITEM_X,MENU_ITEM_Y_2,FONT16);
			break;
		default:
			Msgstr = MsgEn;
			break;
		}

}

void SetSoundAdjLFPaint(U8 mode)
{
	U8 sbuf[10];
	DecToStrSign(TEVData.S8VolumeLF,sbuf,2);

	if (U8InterfaceID==MSET_1_0_0_SOUND_LF_SET)
	{
		LCD_TextA_Rev(sbuf,POS_SETSOUNDADJ_LF_X,POS_SETSOUNDADJ_LF_Y,FONT16,0);
	}else
	{
		LCD_TextA(sbuf,POS_SETSOUNDADJ_LF_X,POS_SETSOUNDADJ_LF_Y,FONT16);
		if (*SetSoundAdj.Cursor==0)
		{
			LCD_DrawLine(POS_SETSOUNDADJ_LF_X-16,POS_SETSOUNDADJ_LF_Y+FONT16,POS_SETSOUNDADJ_LF_X+7,POS_SETSOUNDADJ_LF_Y+FONT16,0x0c);
		} 
		else
		{
			LCD_DrawLine(POS_SETSOUNDADJ_LF_X-16,POS_SETSOUNDADJ_LF_Y+FONT16,POS_SETSOUNDADJ_LF_X+7,POS_SETSOUNDADJ_LF_Y+FONT16,0x00);
		}
	}

}

void SetSoundAdjLRPaint(U8 mode)
{
	U8 sbuf[10];
	DecToStrSign(TEVData.S8VolumeLR,sbuf,2);
	if (U8InterfaceID==MSET_1_1_0_SOUND_LR_SET)
	{
		LCD_TextA_Rev(sbuf,POS_SETSOUNDADJ_LR_X,POS_SETSOUNDADJ_LR_Y,FONT16,0);
	}else
	{
		LCD_TextA(sbuf,POS_SETSOUNDADJ_LR_X,POS_SETSOUNDADJ_LR_Y,FONT16);
		if (*SetSoundAdj.Cursor==1)
		{
			LCD_DrawLine(POS_SETSOUNDADJ_LR_X-16,POS_SETSOUNDADJ_LR_Y+FONT16,POS_SETSOUNDADJ_LR_X+7,POS_SETSOUNDADJ_LR_Y+FONT16,0x0c);
		} 
		else
		{
			LCD_DrawLine(POS_SETSOUNDADJ_LR_X-16,POS_SETSOUNDADJ_LR_Y+FONT16,POS_SETSOUNDADJ_LR_X+7,POS_SETSOUNDADJ_LR_Y+FONT16,0x00);
		}
	}
}

void SetSoundAdjRFPaint(U8 mode)
{
	U8 sbuf[10];
	DecToStrSign(TEVData.S8VolumeRF,sbuf,2);
	if (U8InterfaceID==MSET_1_2_0_SOUND_RF_SET)
	{
		LCD_TextA_Rev(sbuf,POS_SETSOUNDADJ_RF_X,POS_SETSOUNDADJ_RF_Y,FONT16,0);
	}else
	{
		LCD_TextA(sbuf,POS_SETSOUNDADJ_RF_X,POS_SETSOUNDADJ_RF_Y,FONT16);
		if (*SetSoundAdj.Cursor==2)
		{
			LCD_DrawLine(POS_SETSOUNDADJ_RF_X-16,POS_SETSOUNDADJ_RF_Y+FONT16,POS_SETSOUNDADJ_RF_X+7,POS_SETSOUNDADJ_RF_Y+FONT16,0x0c);
		} 
		else
		{
			LCD_DrawLine(POS_SETSOUNDADJ_RF_X-16,POS_SETSOUNDADJ_RF_Y+FONT16,POS_SETSOUNDADJ_RF_X+7,POS_SETSOUNDADJ_RF_Y+FONT16,0x00);
		}
	}
}

void SetSoundAdjRRPaint(U8 mode)
{
	U8 sbuf[10];
	DecToStrSign(TEVData.S8VolumeRR,sbuf,2);
	if (U8InterfaceID==MSET_1_3_0_SOUND_RR_SET)
	{
		LCD_TextA_Rev(sbuf,POS_SETSOUNDADJ_RR_X,POS_SETSOUNDADJ_RR_Y,FONT16,0);
	}else
	{
		LCD_TextA(sbuf,POS_SETSOUNDADJ_RR_X,POS_SETSOUNDADJ_RR_Y,FONT16);
		if (*SetSoundAdj.Cursor==3)
		{
			LCD_DrawLine(POS_SETSOUNDADJ_RR_X-16,POS_SETSOUNDADJ_RR_Y+FONT16,POS_SETSOUNDADJ_RR_X+7,POS_SETSOUNDADJ_RR_Y+FONT16,0x0c);
		} 
		else
		{
			LCD_DrawLine(POS_SETSOUNDADJ_RR_X-16,POS_SETSOUNDADJ_RR_Y+FONT16,POS_SETSOUNDADJ_RR_X+7,POS_SETSOUNDADJ_RR_Y+FONT16,0x00);
		}
	}
}

void SetSoundAdjExitPaint(U8 mode)
{
	LCD_TextA(Msgstr[15],MENU_X+32,MENU_ITEM_Y_1+FONT16,FONT16);
	if (*SetSoundAdj.Cursor==4)
	{
		LCD_TextA("\x8f\x00",MENU_X,MENU_ITEM_Y_1+FONT16,FONT16);
	} 
	else
	{
		LCD_TextA("\x80\x00",MENU_X,MENU_ITEM_Y_1+FONT16,FONT16);
	}
}


void SetSoundAdjPaint(U8 mode)
{
	LCD_DrawBmp(152,10+MENU_TITLE_Y,BMP_SETSOUNDADJ_NO);
}


void SetDelightChgPaint(U8 mode)
{

	/*Change delight table*/
	Drv_OLED_SetGrayScaleTable(TSettingPara.U8LEDLight);

	/*Draw delight bar*/
	if(TSettingPara.U8LEDLight<=10)		
		Draw_PlayTimeProgressFrame(POS_PLAY_TIME_LINE_X,POS_PLAY_TIME_Y+6+MENU_TITLE_Y,TSettingPara.U8LEDLight*10,1);

}

void SetDelightPaint(U8 mode)
{

	/*Draw delight demo*/
	LCD_DrawBmp(64,20+MENU_TITLE_Y,BMP_LOGO_NO);

	/*Draw delight ico*/
	LCD_TextA("\xab\x00",POS_PLAY_TIME_LINE_X-18+16,POS_PLAY_TIME_Y+MENU_TITLE_Y,FONT16);

	LCD_TextA("\xac\x00",POS_PLAY_TIME_LINE_X+POS_PLAY_TIME_LINE_WIDTH+8+16,POS_PLAY_TIME_Y+MENU_TITLE_Y,FONT16);

	/*Draw delight bar*/
	Draw_PlayTimeProgressFrame(POS_PLAY_TIME_LINE_X,POS_PLAY_TIME_Y+6+MENU_TITLE_Y,TSettingPara.U8LEDLight,0);

}


void SetFileInfoPaint(U8 mode)
{
	//LCD_TextA("File info",32,16+MENU_TITLE_Y,FONT16);
	U8 buf[20];
	U8 buff[10];
	U16 foldernum,filenum;

	switch(Dispinfo.currentFile.device)
	{
	case USB:
		foldernum = Dispinfo.usb.totalFolderNum;
		filenum = Dispinfo.usb.totalFileNum;
		break;
	case SD:
		foldernum = Dispinfo.sd.totalFolderNum;
		filenum = Dispinfo.sd.totalFileNum;
	    break;
	default:
		foldernum = 0;
		filenum = 0;
	    break;
	}

	strcpy(buf,Msgstr[13]);
	DecToStr(foldernum,buff,5);
	strcat(buf,buff);
	LCD_TextA(buf,32,16+MENU_TITLE_Y,FONT16);

	memset(buf,0,sizeof(buf));
	memset(buff,0,sizeof(buff));
	strcpy(buf,Msgstr[14]);
	DecToStr(filenum,buff,5);
	strcat(buf,buff);
	LCD_TextA(buf,32,35+MENU_TITLE_Y,FONT16);


}

void SetSystemInfoPaint(U8 mode)
{
	//LCD_TextA("System info",32,16,FONT16);
	U8 buf[12];
	U8 buff[6];
	U8 year;
	U8 month;
	U8 day;
	/*Draw software ver*/
	Strformat2(buf,TSoftVersion.U8MainNo,TSoftVersion.U8SubNo,".",2);
	LCD_TextA(buf,32,16+MENU_TITLE_Y,FONT16);

#if 0
	year = (U8)(TSoftVersion.U32Date>>24);
	month = (U8)(TSoftVersion.U32Date>>16);
	day = (U8)(TSoftVersion.U32Date>>8);

	memset(buf,0,sizeof(buf));
	buf[0] = '.';
	DecToStr(year,buff,(U8)2);
	strcat(buf,buff);
	DecToStr(month,buff,(U8)2);
	strcat(buf,buff);
	DecToStr(day,buff,(U8)2);
	strcat(buf,buff);
	LCD_TextA(buf,32+8*FONT16/2,16+MENU_TITLE_Y,FONT16);
#endif
	memset(buf,0,sizeof(buf));
	/*Draw AEL ver*/
	memcpy(buf,Dispinfo.ae1Version.LSIName,12);
	buf[7] = 'V';
	buf[8] = Dispinfo.ae1Version.ver[1]+'0';
	buf[9] = Dispinfo.ae1Version.ver[2]+'0';
	buf[10] = Dispinfo.ae1Version.ver[3]+'0';
	buf[11] = (U8)0;
	
	LCD_TextA(buf,32,32+MENU_TITLE_Y,FONT16);
}

//
/*************Draw folder scan  ************************************************/
/*-Raw data-*/
/*NULL*/
/*-message process function-*/
//void MsgFolderscanProc(Disp_Message Msg);
/*-initialize function-*/
//void FolderscanWidgetInit();
/*-paint function-*/
void FolderscanPaint(U8 mode);
/*-Timer-*/
/*NULL*/
/*-Define widget-*/
//const Disp_WidgetType WidgetFolderscan ={0,0,0U,0U,RAWDATA_NULL,MsgFolderscanProc,FolderscanWidgetInit,FolderscanPaint,TIMER_NULL};
/***********Widget play state end*/
#define FOLDERITEMPOS_1 0
#define FOLDERITEMPOS_2 32
#define FOLDERITEMPOS_3 62
#define FOLDERITEMPOS_4 94
#define FOLDERITEMPOSEND 126
U16 FolderItemPosArray[5]={
	FOLDERITEMPOS_1,
	FOLDERITEMPOS_2,
	FOLDERITEMPOS_3,
	FOLDERITEMPOS_4,
	FOLDERITEMPOSEND,

};

U8 FolderItemPos;
U8 FolderRollState;
S8 FolderRollnum;
S8 FolderRollnumbuf;
U8 Folderoldernum;
U8 FolderDispbufferFlag;
U8 FolderAE1changeFlag;

/*****************************************************************************
* ID				 : 1.0
* Outline			 : Convert folder name to buf
* Include			 : none
* Declaration		 : void Getfolderstr(char *Strbuf,U8 folderorder)
* Description		 : Convert folder name to buf
* Argument 			 : 
* Return Value 		 : void
* Calling Functions  : none
*****************************************************************************/
void Getfolderstr(char *Strbuf,U8 folderorder,U8 strwidth)
{
	char cbuf[5];
	U8 u8_i;

	/*Unicode to GB code*/
	if (Dispinfo.currentFile.folderInfoBuf.folderBuf[folderorder].folderName.nameCharacterCode == UTF_16LE)
	{
		ConvertUnicodeToGBCode(Dispinfo.currentFile.folderInfoBuf.folderBuf[folderorder].folderName.Name,Dispinfo.currentFile.folderInfoBuf.folderBuf[folderorder].folderName.nameLength,LITTLE_ENDIAN);
		Dispinfo.currentFile.folderInfoBuf.folderBuf[folderorder].folderName.nameCharacterCode = 	UNKOWN_CODE;

		//strlen = GetDrawTextWidthW(Dispinfo.currentFile.currentFolderInfo.folderName.Name);		
	}

	/*convert the oder of folder*/
	if(Dispinfo.currentFile.folderInfoBuf.folderBuf[folderorder].folderNum!=0)
		DecToStr(Dispinfo.currentFile.folderInfoBuf.folderBuf[folderorder].folderNum,cbuf,2);
	strcpy(Strbuf,cbuf);
	/*insert space*/
	strcat(Strbuf,"\x20");

	/*copy folder name to buf,but note name length*/
	if (strlen(Dispinfo.currentFile.folderInfoBuf.folderBuf[folderorder].folderName.Name)>FOLDERSCAN_NAMEBUF_MAX)
	{
		strncat(Strbuf,Dispinfo.currentFile.folderInfoBuf.folderBuf[folderorder].folderName.Name,FOLDERSCAN_NAMEBUF_MAX);
	}else
	{
		strcat(Strbuf,Dispinfo.currentFile.folderInfoBuf.folderBuf[folderorder].folderName.Name);
	}

	/*insert space to buf*/
	for (u8_i = strlen(Strbuf);u8_i<strwidth;u8_i++)
	{
		Strbuf[u8_i]=0x20;
	}
}

U8 Folderbuf1write;
/*****************************************************************************
* ID				 : 1.0
* Outline			 : draw folder name to disp
* Include			 : none
* Declaration		 : void FolderscanPaint(U8 mode)
* Description		 : draw folder name to disp
* Argument 			 : 
* Return Value 		 : void
* Calling Functions  : none
*****************************************************************************/
#if 0
void FolderscanPaint(U8 mode)
{

	U8 Strbuf[20];
	U8 strwidth;
	U8 def[5] = {(U8)2,(U8)3,(U8)0,(U8)1,(U8)2};
	U8 defadd[4] ={(U8)1,(U8)2,(U8)3,(U8)0};
	U8 defdec[4] = {(U8)3,(U8)0,(U8)1,(U8)2};
	U8 defadd2[4] = {(U8)2,(U8)3,(U8)0,(U8)1};
	//U8 defv[5] = {}

	strwidth = (U8)sizeof(Strbuf)-(U8)1;
	switch(mode)
	{
	case FOLDER_SCAN_DRAW_UP:
		/*the first time draw when up roll*/ 

		/*enable write buf area*/
		Folderbuf1write =FALSE;
		/*draw folder ico*/
		LCD_TextA("\x91\x00",POS_FILE_PULLUP_X+8,FolderItemPosArray[2]+8,FONT16);
	
		/*draw first line on view area*/
		memset(Strbuf,0,sizeof(Strbuf));
		Getfolderstr(Strbuf,Dispinfo.currentFile.folderInfoBuf.currentBufIndex,strwidth); 
		LCD_TextA(Strbuf,POS_FILE_PULLUP_X+4+16+8,FolderItemPosArray[2]+4,FONT24);

		/*draw second line on view area,but note last folder*/
		memset(Strbuf,0,sizeof(Strbuf));
		if(Dispinfo.currentFile.folderInfoBuf.folderBuf[defadd[Dispinfo.currentFile.folderInfoBuf.currentBufIndex]].folderNum==(U8)0)
		{
			/*copy space*/
			memset(Strbuf,0x20,sizeof(Strbuf)-1);
		}else
		{
			Getfolderstr(Strbuf,defadd[Dispinfo.currentFile.folderInfoBuf.currentBufIndex]);
		} 
		//Getfolderstr(Strbuf,FORDERSCAN_FILE_ORDER_UP_NEXT1);
		LCD_TextA(Strbuf,POS_FILE_PULLUP_X+4+16+8,FolderItemPosArray[3]+4,FONT24);

		/*set pos*/
		FolderItemPos = (U8)2;

		break;
	case FOLDER_SCAN_DRAW_DOWN:
		/*The fist time draw when down roll*/

		FolderItemPos = (U8)3;
		/*enable draw buf area*/
		Folderbuf1write =FALSE;
		/*Draw folder ico*/ 
		LCD_TextA("\x91\x00",POS_FILE_PULLUP_X+8,FolderItemPosArray[3]+8,FONT16);
		/*Draw second line on view area*/
		memset(Strbuf,0,sizeof(Strbuf));
		Getfolderstr(Strbuf,Dispinfo.currentFile.folderInfoBuf.currentBufIndex); 
		LCD_TextA(Strbuf,POS_FILE_PULLUP_X+4+16+8,FolderItemPosArray[3]+4,FONT24);

		/*Draw first line on view area ,but note top folder*/
		memset(Strbuf,0,sizeof(Strbuf));
		if(Dispinfo.currentFile.folderInfoBuf.folderBuf[defdec[Dispinfo.currentFile.folderInfoBuf.currentBufIndex]].folderNum==(U8)0)
		{
			/*copy space*/
			memset(Strbuf,0x20,sizeof(Strbuf)-1);
		}else
		{
			Getfolderstr(Strbuf,defdec[Dispinfo.currentFile.folderInfoBuf.currentBufIndex]);
		}
		//Getfolderstr(Strbuf,FORDERSCAN_FILE_ORDER_DOWN_PRE1);
		LCD_TextA(Strbuf,POS_FILE_PULLUP_X+4+16+8,FolderItemPosArray[2]+4,FONT24);

		break;
	case FOLDER_SCAN_DRAW_BUF_UP:
		/*draw second line on buf area, but note last folder*/
		memset(Strbuf,0,sizeof(Strbuf));
		if(Dispinfo.currentFile.folderInfoBuf.folderBuf[defadd2[Dispinfo.currentFile.folderInfoBuf.currentBufIndex]].folderNum==(U8)0)
		{
			/*copy space*/
			memset(Strbuf,0x20,sizeof(Strbuf)-1);
		}else
		{
			Getfolderstr(Strbuf,defadd2[Dispinfo.currentFile.folderInfoBuf.currentBufIndex]);
		}
		LCD_TextA(Strbuf,POS_FILE_PULLUP_X+4+16+8,FolderItemPosArray[def[FolderItemPos]]+4,FONT24);

		/*draw folder ico*/
		LCD_TextA("\x80\x00",POS_FILE_PULLUP_X+8,FolderItemPosArray[def[FolderItemPos+1]]+8,FONT16);
		LCD_TextA("\x91\x00",POS_FILE_PULLUP_X+8,FolderItemPosArray[FolderItemPos]+8,FONT16);

		break;
	case FOLDER_SCAN_DRAW_BUF_DOWN:
		/*draw first line on buf area , but note top folder*/
		memset(Strbuf,0,sizeof(Strbuf));
		if(Dispinfo.currentFile.folderInfoBuf.folderBuf[defadd2[Dispinfo.currentFile.folderInfoBuf.currentBufIndex]].folderNum==(U8)0)
		{
			/*copy space*/
			memset(Strbuf,0x20,sizeof(Strbuf)-1);
		}else
		{
			Getfolderstr(Strbuf,defadd2[Dispinfo.currentFile.folderInfoBuf.currentBufIndex]);
		}
		LCD_TextA(Strbuf,POS_FILE_PULLUP_X+4+16+8,FolderItemPosArray[def[FolderItemPos]]+4,FONT24);

		/*draw folder ico*/
		LCD_TextA("\x80\x00",POS_FILE_PULLUP_X+8,FolderItemPosArray[defadd[FolderItemPos]]+8,FONT16);
		LCD_TextA("\x91\x00",POS_FILE_PULLUP_X+8,FolderItemPosArray[FolderItemPos]+8,FONT16);

		break;
	case FOLDER_SCAN_DRAW_BUF_DOWNSWITCH:
		/*draw buf area when switch direction */
		Folderbuf1write =FALSE;
		//LCD_TextA("\x80\x00",POS_FILE_PULLUP_X+8,FolderItemPosArray[def[FolderItemPos+1]]+8,FONT16);
		/*Draw first line on buf area*/
		memset(Strbuf,0,sizeof(Strbuf));
		Getfolderstr(Strbuf,Dispinfo.currentFile.folderInfoBuf.currentBufIndex); 
		LCD_TextA(Strbuf,POS_FILE_PULLUP_X+4+16+8,FolderItemPosArray[defadd[FolderItemPos]]+4,FONT24);

		/*Draw second line on buf area , but note last folder*/
		memset(Strbuf,0,sizeof(Strbuf));
		if(Dispinfo.currentFile.folderInfoBuf.folderBuf[defadd[Dispinfo.currentFile.folderInfoBuf.currentBufIndex]].folderNum==(U8)0)
		{
			/*copy space*/
			memset(Strbuf,0x20,sizeof(Strbuf)-1);
		}else
		{
			Getfolderstr(Strbuf,defadd[Dispinfo.currentFile.folderInfoBuf.currentBufIndex]);
		} 
		//Getfolderstr(Strbuf,FORDERSCAN_FILE_ORDER_UP_NEXT1);
		LCD_TextA(Strbuf,POS_FILE_PULLUP_X+4+16+8,FolderItemPosArray[def[FolderItemPos]]+4,FONT24);

		/*draw folder ico*/
		LCD_TextA("\x80\x00",POS_FILE_PULLUP_X+8,FolderItemPosArray[FolderItemPos]+8,FONT16);
		LCD_TextA("\x91\x00",POS_FILE_PULLUP_X+8,FolderItemPosArray[defadd[FolderItemPos]]+8,FONT16);

		break;
	case FOLDER_SCAN_DRAW_BUF_UPSWITCH:
		Folderbuf1write =FALSE;
		//LCD_TextA("\x80\x00",POS_FILE_PULLUP_X+8,FolderItemPosArray[def[FolderItemPos+1]]+8,FONT16);
		memset(Strbuf,0,sizeof(Strbuf));
		if(Dispinfo.currentFile.folderInfoBuf.folderBuf[defdec[Dispinfo.currentFile.folderInfoBuf.currentBufIndex]].folderNum==(U8)0)
		{
			/*copy space*/
			memset(Strbuf,0x20,sizeof(Strbuf)-1);
		}else
		{
			Getfolderstr(Strbuf,defdec[Dispinfo.currentFile.folderInfoBuf.currentBufIndex]);
		} 
		//Getfolderstr(Strbuf,FORDERSCAN_FILE_ORDER_DOWN_PRE1); 
		LCD_TextA(Strbuf,POS_FILE_PULLUP_X+4+16+8,FolderItemPosArray[def[FolderItemPos]]+4,FONT24);

		memset(Strbuf,0,sizeof(Strbuf));
		Getfolderstr(Strbuf,Dispinfo.currentFile.folderInfoBuf.currentBufIndex);
		LCD_TextA(Strbuf,POS_FILE_PULLUP_X+4+16+8,FolderItemPosArray[def[FolderItemPos+1]]+4,FONT24);

		LCD_TextA("\x80\x00",POS_FILE_PULLUP_X+8,FolderItemPosArray[FolderItemPos]+8,FONT16);
		LCD_TextA("\x91\x00",POS_FILE_PULLUP_X+8,FolderItemPosArray[def[FolderItemPos+1]]+8,FONT16);
		break;
	case FOLDER_SCAN_DRAW_BUF_UP_ALL:
		if(!Folderbuf1write)
		{
		/**/ 
		//LCD_TextA("\x91\x00",POS_FILE_PULLUP_X+8,FolderItemPosArray[2]+8,FONT16);
		Folderbuf1write =TRUE;
		memset(Strbuf,0,sizeof(Strbuf));
		if(Dispinfo.currentFile.folderInfoBuf.folderBuf[defadd[Dispinfo.currentFile.folderInfoBuf.currentBufIndex]].folderNum==(U8)0)
		{
			/*copy space*/
			memset(Strbuf,0x20,sizeof(Strbuf)-1);
		}else
		{
			Getfolderstr(Strbuf,defadd[Dispinfo.currentFile.folderInfoBuf.currentBufIndex]);
		} 
		LCD_TextA(Strbuf,POS_FILE_PULLUP_X+4+16+8,FolderItemPosArray[def[FolderItemPos]]+4,FONT24);

		memset(Strbuf,0,sizeof(Strbuf));
		Getfolderstr(Strbuf,defadd2[Dispinfo.currentFile.folderInfoBuf.currentBufIndex]);
		LCD_TextA(Strbuf,POS_FILE_PULLUP_X+4+16+8,FolderItemPosArray[def[FolderItemPos+1]]+4,FONT24);
		}
		break;
	case FOLDER_SCAN_DRAW_BUF_DWWN_ALL:
		if(!Folderbuf1write)
		{
			/**/ 
			//LCD_TextA("\x91\x00",POS_FILE_PULLUP_X+8,FolderItemPosArray[2]+8,FONT16);
			Folderbuf1write =TRUE;
			memset(Strbuf,0,sizeof(Strbuf));
			if(Dispinfo.currentFile.folderInfoBuf.folderBuf[defdec[Dispinfo.currentFile.folderInfoBuf.currentBufIndex]].folderNum==(U8)0)
			{
				/*copy space*/
				memset(Strbuf,0x20,sizeof(Strbuf)-1);
			}else
			{
				Getfolderstr(Strbuf,defdec[Dispinfo.currentFile.folderInfoBuf.currentBufIndex]);
			} 
			LCD_TextA(Strbuf,POS_FILE_PULLUP_X+4+16+8,FolderItemPosArray[def[FolderItemPos]]+4,FONT24);
		}
		break;
	default:
		break;
	}
}
#endif

void FolderscanPaint(U8 mode)
{

	U8 Strbuf[20];
	U8 Strwidth;
	U8 def[5] = {(U8)2,(U8)3,(U8)0,(U8)1,(U8)2};
	U8 defadd[4] ={(U8)1,(U8)2,(U8)3,(U8)0};
	U8 defdec[4] = {(U8)3,(U8)0,(U8)1,(U8)2};
	U8 defadd2[4] = {(U8)2,(U8)3,(U8)0,(U8)1};
	//U8 defv[5] = {}
	U16 fcurpos0 =0,fcurpos1 = 0,ffpos = 0,fspos = 0;
	U8 fbuf0=0,fbuf1=0;

	Strwidth = (U8)sizeof(Strbuf)-(U8)1;
	switch(mode)
	{
	case FOLDER_SCAN_DRAW_UP:
		/*the first time draw when up roll*/ 

		/*enable write buf area*/
		Folderbuf1write =FALSE;
		/*draw folder ico*/
		fcurpos0 = FolderItemPosArray[2]+8;

		/*draw first line on view area*/
		fbuf0 = Dispinfo.currentFile.folderInfoBuf.currentBufIndex; 
		ffpos = FolderItemPosArray[2]+4;

		/*draw second line on view area,but note last folder*/
		fbuf1 = defadd[Dispinfo.currentFile.folderInfoBuf.currentBufIndex];
		fspos = FolderItemPosArray[3]+4;
		/*set pos*/
		FolderItemPos = (U8)2;

		break;
	case FOLDER_SCAN_DRAW_DOWN:
		/*The fist time draw when down roll*/
		FolderItemPos = (U8)3;
		/*enable draw buf area*/
		Folderbuf1write =FALSE;
		/*Draw folder ico*/ 
		fcurpos0 = FolderItemPosArray[3]+8;
		/*Draw second line on view area*/
		fbuf1 = Dispinfo.currentFile.folderInfoBuf.currentBufIndex; 
		fspos = FolderItemPosArray[3]+4;

		/*Draw first line on view area ,but note top folder*/
		fbuf0 = defdec[Dispinfo.currentFile.folderInfoBuf.currentBufIndex];
		//Getfolderstr(Strbuf,FORDERSCAN_FILE_ORDER_DOWN_PRE1);
		ffpos = FolderItemPosArray[2]+4;

		break;
	case FOLDER_SCAN_DRAW_BUF_UP:
		/*draw second line on buf area, but note last folder*/
		fbuf1 = defadd2[Dispinfo.currentFile.folderInfoBuf.currentBufIndex];
		fspos = FolderItemPosArray[def[FolderItemPos]]+4;

		/*draw folder ico*/
		fcurpos1 = FolderItemPosArray[def[FolderItemPos+1]]+8;
		fcurpos0 = FolderItemPosArray[FolderItemPos]+8;

		break;
	case FOLDER_SCAN_DRAW_BUF_DOWN:
		/*draw first line on buf area , but note top folder*/
		fbuf0 = defadd2[Dispinfo.currentFile.folderInfoBuf.currentBufIndex];
		ffpos = FolderItemPosArray[def[FolderItemPos]]+4;

		/*draw folder ico*/
		fcurpos1 = FolderItemPosArray[defadd[FolderItemPos]]+8;
		fcurpos0 = FolderItemPosArray[FolderItemPos]+8;

		break;
	case FOLDER_SCAN_DRAW_BUF_DOWNSWITCH:
		/*draw buf area when switch direction */
		Folderbuf1write =FALSE;
		//LCD_TextA("\x80\x00",POS_FILE_PULLUP_X+8,FolderItemPosArray[def[FolderItemPos+1]]+8,FONT16);
		/*Draw first line on buf area*/
		fbuf0 = Dispinfo.currentFile.folderInfoBuf.currentBufIndex; 
		ffpos = FolderItemPosArray[defadd[FolderItemPos]]+4;

		/*Draw second line on buf area , but note last folder*/
		fbuf1 = defadd[Dispinfo.currentFile.folderInfoBuf.currentBufIndex];
		fspos = FolderItemPosArray[def[FolderItemPos]]+4;

		/*draw folder ico*/
		fcurpos1 = FolderItemPosArray[FolderItemPos]+8;
		fcurpos0 = FolderItemPosArray[defadd[FolderItemPos]]+8;

		break;
	case FOLDER_SCAN_DRAW_BUF_UPSWITCH:
		Folderbuf1write =FALSE;
		//LCD_TextA("\x80\x00",POS_FILE_PULLUP_X+8,FolderItemPosArray[def[FolderItemPos+1]]+8,FONT16);
		fbuf0 = defdec[Dispinfo.currentFile.folderInfoBuf.currentBufIndex];
		ffpos = FolderItemPosArray[def[FolderItemPos]]+4;

		fbuf1 = Dispinfo.currentFile.folderInfoBuf.currentBufIndex;
		fspos = FolderItemPosArray[def[FolderItemPos+1]]+4;

		fcurpos1 = FolderItemPosArray[FolderItemPos]+8;
		fcurpos0 = FolderItemPosArray[def[FolderItemPos+1]]+8;
		break;
	case FOLDER_SCAN_DRAW_BUF_UP_ALL:
		if(!Folderbuf1write)
		{
			/**/ 
			//LCD_TextA("\x91\x00",POS_FILE_PULLUP_X+8,FolderItemPosArray[2]+8,FONT16);
			Folderbuf1write =TRUE;
			fbuf0 = defadd[Dispinfo.currentFile.folderInfoBuf.currentBufIndex]; 
			ffpos = FolderItemPosArray[def[FolderItemPos]]+4;

			fbuf1 = defadd2[Dispinfo.currentFile.folderInfoBuf.currentBufIndex];
			fspos = FolderItemPosArray[def[FolderItemPos+1]]+4;
		}
		break;
	case FOLDER_SCAN_DRAW_BUF_DWWN_ALL:
		if(!Folderbuf1write)
		{
			/**/ 
			//LCD_TextA("\x91\x00",POS_FILE_PULLUP_X+8,FolderItemPosArray[2]+8,FONT16);
			Folderbuf1write =TRUE;
			fbuf0 =	defdec[Dispinfo.currentFile.folderInfoBuf.currentBufIndex];
			ffpos = FolderItemPosArray[def[FolderItemPos]]+4;
		}
		break;
	default:
		break;
	}

	if(fcurpos0)
		LCD_TextA("\x91\x00",POS_FILE_PULLUP_X+8,fcurpos0,FONT16);
	
	if(fcurpos1)
		LCD_TextA("\x80\x00",POS_FILE_PULLUP_X+8,fcurpos1,FONT16);
	
	if(ffpos)
	{
		memset(Strbuf,0,sizeof(Strbuf));
		Getfolderstr(Strbuf,fbuf0,Strwidth);
		LCD_TextA(Strbuf,POS_FILE_PULLUP_X+4+16+8,ffpos,FONT24);
	}

	if(fspos)
	{
		memset(Strbuf,0,sizeof(Strbuf));
		Getfolderstr(Strbuf,fbuf1,Strwidth);
		LCD_TextA(Strbuf,POS_FILE_PULLUP_X+4+16+8,fspos,FONT24);
	}
}
/*****************************************************************************
* ID				 : 1.0
* Outline			 : Set display roll direction and time
* Include			 : none
* Declaration		 : void FolderScanSetRoll(U8 mode,U16 rolltime)
* Description		 : Set display roll direction and time
* Argument 			 : 
* Return Value 		 : void
* Calling Functions  : none
*****************************************************************************/
void FolderScanSetRoll(U8 mode,U16 rolltime)
{
	if (rolltime>300)
	{
		rolltime = 300;
	}else
	{
		/**/
	}

	switch(mode)
	{
	case 0:
		If_Disp_SetRoll(FolderItemPosArray[FolderItemPos],(U8)32,0,rolltime);
		break;
	case 1:
		If_Disp_SetRoll(FolderItemPosArray[FolderItemPos],(U8)32,1,rolltime);
		break;
	case 2:
		If_Disp_SetRoll(FolderItemPosArray[FolderItemPos],(U8)64,0,rolltime);
	    break;
	case 3:
		If_Disp_SetRoll(FolderItemPosArray[FolderItemPos],(U8)64,1,rolltime);
	    break;
	default:
	    break;
	}
}

/*****************************************************************************
* ID				 : 1.0
* Outline			 : Set current folder pos
* Include			 : none
* Declaration		 : void ForderItemPoschg(U8 flag)
* Description		 : Set current folder pos
* Argument 			 : 
* Return Value 		 : void
* Calling Functions  : none
*****************************************************************************/
void ForderItemPoschg(U8 flag)
{
	U8 defup[4]={1,2,3,0,};
	u8 defdown[4]={3,0,1,2};
	if (flag)
	{
		FolderItemPos = defup[FolderItemPos];
	} 
	else
	{
		FolderItemPos = defdown[FolderItemPos];
	}
}



#if 0
/*Screen define*/
/*play mode*/
void DispPlayscreenInit(void);
#define DISP_SCREEN_PLAYWIDGET_NUM 7
const Disp_WidgetType * Screen_PlayWidgets[DISP_SCREEN_PLAYWIDGET_NUM] = {
																	&WidgetPlayMode,
																	&WidgetDisp,
																	&WidgetVolume,
																	&WidgetFolder,
																	//&WidgetAlbum,
																	&WidgetTitle,
																	&WidgetPlayState,
																	&WidgetPlayTimer,
};

const Disp_Screen ScreenPlay = {DISP_SCREEN_PLAYWIDGET_NUM,Screen_PlayWidgets,DispPlayscreenInit};

void DispPlayscreenInit()
{
	/*Clear disp*/
	LCD_DrawBox(0,0,256,64,1,0,0);
}
/*Setting*/
void DispSettingscreenInit(void);
#define DISP_SCREEN_SET_NUM 1
const Disp_WidgetType *Screen_Setting[DISP_SCREEN_SET_NUM] = {&WidgetSet};

const Disp_Screen ScreenSet = {DISP_SCREEN_SET_NUM,Screen_Setting,DispSettingscreenInit};

void DispSettingscreenInit()
{
	/*Clear disp*/
	LCD_DrawBox(0,62,256,126,1,0,0);
}
//const Disp_Screen ScreenSet  = {NULL_PTR,NULL_PTRR};

/*Folder scan*/
void DispFolderscanInit(void);
#define DISP_SCREEN_FOLDERSCAN_NUM 1
const Disp_WidgetType *Screen_Folderscan[DISP_SCREEN_FOLDERSCAN_NUM]={&WidgetFolderscan};
const Disp_Screen ScreenFolderscan = {DISP_SCREEN_FOLDERSCAN_NUM,Screen_Folderscan,DispFolderscanInit};

#define DISP_SCREEN_NUM 3
const Disp_Screen * Screen[DISP_SCREEN_NUM] = {&ScreenPlay,&ScreenFolderscan,&ScreenSet}; 

void DispFolderscanInit()
{
	/*Clear disp*/
	LCD_DrawBox(0,62,256,126,1,0,0);
}
DISP_SCREEN_NO DispScreenNo;

#endif

/*****************************************************************************
* ID				 : 1.0
* Outline			 : Dec Conv str
* Include			 : none
* Declaration		 : void DecToStr(U16 data,U8 * str)
* Description		 : Dec Conv Str
* Argument 			 : 
* Return Value 		 : void
* Calling Functions  : none
*****************************************************************************/
/*20110607 modify santu :'bit' is a key word in 78k*/
/*void DecToStr(U16 data, U8 *str,U8 bit)*/
void DecToStr(U16 data, U8 *str,U8 bitwidth)
{
	switch(bitwidth)
	{
	case 5:
		str[0] = data/10000+'0';
		str[1] = (data%10000)/1000+'0';
		str[2] = (data%1000)/100+'0';
		str[3] = (data%100)/10+'0';
		str[4] = data%10+'0';
		str[5] = 0;
		break;
	case 4:
		str[0] = data/1000+'0';
		str[1] = (data%1000)/100+'0';
		str[2] = (data%100)/10+'0';
		str[3] = data%10+'0';
		str[4] = 0;
		break;
	case 3:
		str[0] = data/100+'0';
		str[1] = (data%100)/10+'0';
		str[2] = data%10+'0';
		str[3] = 0;
		break;
	case 2:
		str[0] = data/10+'0';
		str[1] = data%10+'0';
		str[2] = 0;
	    break;
	case 1:
		str[0] = data%10+'0';
		str[1] = 0;
	    break;
	default:
		str[0] = 0;
	    break;
	}
}

void DecToStrSign(S16 data, U8 *str,U8 bit)
{
	U16 U16temp;
	if(data<0)
	{
		U16temp = 0-data;
		str[0] = '-';
	}else
	{
		U16temp = data;
		str[0] = '+';
	}
	switch(bit)
	{
	case 4:
		str[1] = U16temp/1000+'0';
		str[2] = (U16temp%1000)/100+'0';
		str[3] = (U16temp%100)/10+'0';
		str[4] = U16temp%10+'0';
		str[5] = 0;
		break;
	case 3:
		str[1] = U16temp/100+'0';
		str[2] = (U16temp%100)/10+'0';
		str[3] = U16temp%10+'0';
		str[4] = 0;
		break;
	case 2:
		str[1] = U16temp/10+'0';
		str[2] = U16temp%10+'0';
		str[3] = 0;
		break;
	case 1:
		str[1] = U16temp%10+'0';
		str[2] = 0;
		break;
	default:
		str[1] = 0;
		break;
	}
}
/*****************************************************************************
* ID				 : 1.0
* Outline			 : str format
* Include			 : none
* Declaration		 : void Strformat(U16 data1,U16 data2,U8 *str,U8 bit);
* Description		 : str format
* Argument 			 : 
* Return Value 		 : void
* Calling Functions  : none
*****************************************************************************/
void Strformat2(U8 *destbuf, U16 data1,U16 data2, U8 *str,U8 bit)
{
	U8 buf1[5];
	U8 buf2[5];
	memset(buf1,0,sizeof(buf1));
	memset(buf2,0,sizeof(buf2));

	DecToStr(data1,buf1,bit);
	strcpy(destbuf,buf1);
	strcat(destbuf,str);
	
	DecToStr(data2,buf2,bit);
	strcat(destbuf,buf2);


}

void Strformat3(U8 *destbuf, U16 data1,U16 data2,U16 data3, U8 *str,U8 bit)
{
	U8 buf1[5];
	U8 buf2[5];
	U8 buf3[5];
	memset(buf1,0,sizeof(buf1));
	memset(buf2,0,sizeof(buf2));

	DecToStr(data1,buf1,bit);
	strcpy(destbuf,buf1);
	strcat(destbuf,str);

	DecToStr(data2,buf2,bit);
	strcat(destbuf,buf2);
	strcat(destbuf,str);

	DecToStr(data3,buf3,bit);
	strcat(destbuf,buf3);


}

/*****************************************************************************
* ID				 : 1.0
* Outline			 : draw warn no media
* Include			 : none
* Declaration		 : void Draw_warn_nomedia( );
* Description		 : draw warn no media
* Argument 			 : 
* Return Value 		 : void
* Calling Functions  : none
*****************************************************************************/
void Draw_warn_nomedia(U8 warntype)
{
	U16 offent;
	
	/*clear title zone*/	 	 
	LCD_DrawBox(WidgetTitle.PosX,WidgetTitle.PoxY,OLED_MAXLINE,WidgetTitle.PoxY+FONT24,(U8)1,(U8)0x00,(U8)0x00);
	offent = GetDrawTextWidthA(Msgstr[warntype],FONT24);
	offent =16+((OLED_MAXLINE-offent)/2);
	LCD_TextA(Msgstr[warntype],offent,POS_WIDGET_TILLE_Y,FONT24);
	*(WidgetTitle.Timer->TimeEnable)= FALSE;
	
}
/*end*/