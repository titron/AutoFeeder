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
 * System Name  : draw 
 * File Name    : draw_play.c
 * Abstract     :  program of AE1-L Demo.
 * Version      : 0.01
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AE1-L demo board
 * Description  : driver of lcd module.
 * Operation    : none
 * Limitation   : This file can be only used as sample code for AE1-L.
 *****************************************************************************
 * History      : Dec.15,2010 Ver. 0.01 First Release
 *****************************************************************************/

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include <string.h>
#include <stdio.h>

#include "config.h"
#include "driver_lcd.h"
#include "basictype.h"
#include "if_lcd_draw.h"
#include "if_lcd_text.h"
#include "app_ae1.h"
#include "disp_widget.h"
#include "draw_play.h"



/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
/*Postion define*/
#define POS_OFFSET 0x10
#define POS_DISK_SD_X				POS_OFFSET
#define POS_DISK_SD_Y				0
#define POS_DISK_USB_X				POS_OFFSET+16
#define POS_DISK_USB_Y				0
#define POS_PLAY_FILE_X POS_OFFSET
#define POS_PLAY_FILE_Y 0x10
#define POS_PLAY_MODE_SPACE			4
#define POS_PLAY_MODE_WIDTH			16
#define POS_PLAY_MODE_X				32+POS_PLAY_MODE_SPACE+POS_OFFSET
#define POS_PLAY_MODE_Y				0
#define POS_PLAY_MODE_RANDOM_X		POS_PLAY_MODE_X
#define POS_PLAY_MODE_LOOP_X		POS_PLAY_MODE_RANDOM_X+POS_PLAY_MODE_WIDTH+POS_PLAY_MODE_SPACE
#define POS_PLAY_MODE_SCAN_X		POS_PLAY_MODE_LOOP_X+POS_PLAY_MODE_WIDTH+POS_PLAY_MODE_SPACE
#define POS_PLAY_SPEEK_X			196+POS_OFFSET
#define POS_PLAY_SPEEK_Y			0
#define POS_PLAY_SPEEK_LINE_X		POS_PLAY_SPEEK_X+16-POS_OFFSET
#define POS_PLAY_SPEEK_VOLUME_X		POS_PLAY_SPEEK_X+16+24
#define POS_PLAY_AUDIO_ALBUM_X		64
#define POS_PLAY_AUDIO_ALBUM_Y		16
#define POS_PLAY_AUDIO_TITLE_Y		32
#define POS_PLAY_PAUSE_X			POS_OFFSET
#define POS_PLAY_PAUSE_Y			48
#define POS_PLAY_TIME_X				20+POS_OFFSET
#define POS_PLAY_TIME_Y				48
#define POS_PLAY_TIME_PLAYBACK_X	POS_PLAY_TIME_X
#define POS_PLAY_TIME_LINE_X		POS_PLAY_TIME_X+56-POS_OFFSET
#define POS_PLAY_TIME_LINE_WIDTH	100
#define POS_PLAY_TIME_FILE_X		POS_PLAY_TIME_X+POS_PLAY_TIME_LINE_WIDTH+56+8

/*Display select*/
#define PLAY_MODE_RANDOM	1
#define PLAY_MODE_NORMAL	0

#define PLAY_MODE_ORDER		0
#define PLAY_MODE_ALLORDER  1
#define PLAY_MODE_LOOP		2
#define PLAY_MODE_ALLLOOP	3
#define PLAY_MODE_SINGLE	4

#define DISK_SD_UNLINK		0
#define DISK_SD_LINK		1
#define DISK_SD_ACTIV		2
#define DISK_USB_UNLINK		0
#define DISK_USB_LINK		1
#define DISK_USB_ACTIV		2

#define PLAY_MODE_SCAN		1

#define PLAY_ING			1
#define PLAY_PAUSE			0

#define PLAY_MODE_DISPLAYNUM 3



/*about Tag*/
#define CODE_UNICODE_16		(U8)1
#define CODE_UNICODE_8		(U8)2
#define CODE_GB2312			(U8)3

#define ALBUM_MAX_NUM		10
#define TITLE_MAX_NUM		32
#define TITLE_MAX_NUM_DISP	64

/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/


/*****************************************************************************
 Private variables and functions
 *****************************************************************************/
#define  FILENUMBER			35
#define  FILEID				16
#define  PlayModeRandom		1
#define  PlayModeLoop		2
#define  PlayModeScan		1
U8	 PlayStatu=1;
U32  FileSecond=378;
//#define  PlayBackSecond		60
U32		PlayBackSecond;
U8 Volume=53;



/*****************************************************************************
* ID				 : 1.0
* Outline			 : LCD draw file number 
* Include			 : none
* Declaration		 : Draw_play_fileinfo(void)
* Description		 : LCD draw file number
* Argument 			 : void
* Return Value 		 : void
* Calling Functions	 : none
*****************************************************************************/
void Draw_play_fileinfo(void)
{
	U16 CurrentFileNum;
	U16 DiskFileNum;
	char buf[10];
	memset(buf,0,sizeof(buf));

	if (Dispinfo.currentFile.device == USB)
	{
		DiskFileNum = Dispinfo.usb.totalFileNum;
	} 
	else if(Dispinfo.currentFile.device == SD)
	{
		DiskFileNum = Dispinfo.sd.totalFileNum;
	}else
	{
		DiskFileNum = 0;
	}

	CurrentFileNum = Dispinfo.currentFile.fileNum;
		
	if(DiskFileNum<100)
	{
		sprintf(buf,"%02d/%d",CurrentFileNum,DiskFileNum);
	}
	else if (DiskFileNum>=100)
	{
		sprintf(buf,"%3d/%d",CurrentFileNum,DiskFileNum);
	}

	LCD_TextA(buf,POS_PLAY_FILE_X,POS_PLAY_FILE_Y,FONT16);
}

/*****************************************************************************
* ID				 : 1.0
* Outline			 : LCD get font data
* Include			 : none
* Declaration		 : void main(void)
* Description		 : LCD module
* Argument 			 : void
* Return Value 		 : void
* Calling Functions	 : none
*****************************************************************************/
#define ORDER_RANDOM 0
#define ORDER_LOOP	 1
#define ORDER_SCAN   2
void Draw_play_mode(void)
{
	U16 PlayModeBuf[4];

	memset(PlayModeBuf,0,sizeof(PlayModeBuf));

	switch(Dispinfo.playbackMode)
	{
	case ALL_FILES_SCAN:
		PlayModeBuf[ORDER_RANDOM] = CODE_SPACE;
		PlayModeBuf[ORDER_LOOP] = CODE_MODE_ALLORDER;
		PlayModeBuf[ORDER_SCAN] = CODE_MODE_SCN;
		break;
	case ALL_FILES_RANDOM:
		PlayModeBuf[ORDER_RANDOM] = CODE_MODE_RANDOM;
		PlayModeBuf[ORDER_LOOP] = CODE_MODE_ALLORDER;
		PlayModeBuf[ORDER_SCAN] = CODE_SPACE;
		break;
	case ALL_FILES_SCAN_RANDOM:
		PlayModeBuf[ORDER_RANDOM] = CODE_MODE_RANDOM;
		PlayModeBuf[ORDER_LOOP] = CODE_MODE_ALLORDER;
		PlayModeBuf[ORDER_SCAN] = CODE_MODE_SCN;
	    break;
	case ALL_FILES_REPEAT:
		PlayModeBuf[ORDER_RANDOM] = CODE_SPACE;
		PlayModeBuf[ORDER_LOOP] = CODE_MODE_LOOP;
		PlayModeBuf[ORDER_SCAN] = CODE_SPACE;
	    break;
	case ALL_FILES_REPEAT_SCAN:
		PlayModeBuf[ORDER_RANDOM] = CODE_SPACE;
		PlayModeBuf[ORDER_LOOP] = CODE_MODE_LOOP;
		PlayModeBuf[ORDER_SCAN] = CODE_MODE_SCN;
		break;
	case ALL_FILES_REPEAT_RANDOM:
		PlayModeBuf[ORDER_RANDOM] = CODE_MODE_RANDOM;
		PlayModeBuf[ORDER_LOOP] = CODE_MODE_LOOP;
		PlayModeBuf[ORDER_SCAN] = CODE_SPACE;
		break;
	case ALL_FILES_REPEAT_SCAN_RANDOM:
		PlayModeBuf[ORDER_RANDOM] = CODE_MODE_RANDOM;
		PlayModeBuf[ORDER_LOOP] = CODE_MODE_LOOP;
		PlayModeBuf[ORDER_SCAN] = CODE_MODE_SCN;
	    break;
	case FOLDER_SCAN:
		PlayModeBuf[ORDER_RANDOM] = CODE_SPACE;
		PlayModeBuf[ORDER_LOOP] = CODE_MODE_ORDER;
		PlayModeBuf[ORDER_SCAN] = CODE_MODE_SCN;
	    break;
	case FOLDER_RANDOM:
		PlayModeBuf[ORDER_RANDOM] = CODE_MODE_RANDOM;
		PlayModeBuf[ORDER_LOOP] = CODE_MODE_ORDER;
		PlayModeBuf[ORDER_SCAN] = CODE_SPACE;
		break;
	case FOLDER_SCAN_RANDOM:
		PlayModeBuf[ORDER_RANDOM] = CODE_MODE_RANDOM;
		PlayModeBuf[ORDER_LOOP] = CODE_MODE_ORDER;
		PlayModeBuf[ORDER_SCAN] = CODE_MODE_SCN;
		break;
	case FOLDER_REPEAT:
		PlayModeBuf[ORDER_RANDOM] = CODE_SPACE;
		PlayModeBuf[ORDER_LOOP] = CODE_MODE_LOOP;
		PlayModeBuf[ORDER_SCAN] = CODE_SPACE;
		break;
	case FOLDER_REPEAT_SCAN:
		PlayModeBuf[ORDER_RANDOM] = CODE_SPACE;
		PlayModeBuf[ORDER_LOOP] = CODE_MODE_LOOP;
		PlayModeBuf[ORDER_SCAN] = CODE_MODE_SCN;
		break;
	case FOLDER_REPEAT_RANDOM:
		PlayModeBuf[ORDER_RANDOM] = CODE_MODE_RANDOM;
		PlayModeBuf[ORDER_LOOP] = CODE_MODE_LOOP;
		PlayModeBuf[ORDER_SCAN] = CODE_SPACE;
		break;
	case FOLDER_REPEAT_SCAN_RANDOM:
		PlayModeBuf[ORDER_RANDOM] = CODE_MODE_RANDOM;
		PlayModeBuf[ORDER_LOOP] = CODE_MODE_LOOP;
		PlayModeBuf[ORDER_SCAN] = CODE_MODE_SCN;
		break;
	case FILES_SCAN:
		PlayModeBuf[ORDER_RANDOM] = CODE_SPACE;
		PlayModeBuf[ORDER_LOOP] = CODE_MODE_SINGLE;
		PlayModeBuf[ORDER_SCAN] = CODE_MODE_SCN;
		break;
	case FILES_RANDOM:
		PlayModeBuf[ORDER_RANDOM] = CODE_MODE_RANDOM;
		PlayModeBuf[ORDER_LOOP] = CODE_MODE_SINGLE;
		PlayModeBuf[ORDER_SCAN] = CODE_SPACE;
		break;
	case FILES_SCAN_RANDOM:
		PlayModeBuf[ORDER_RANDOM] = CODE_MODE_RANDOM;
		PlayModeBuf[ORDER_LOOP] = CODE_MODE_SINGLE;
		PlayModeBuf[ORDER_SCAN] = CODE_MODE_SCN;
		break;
	case FILES_REPEAT:
		PlayModeBuf[ORDER_RANDOM] = CODE_SPACE;
		PlayModeBuf[ORDER_LOOP] = CODE_MODE_SINGLE;
		PlayModeBuf[ORDER_SCAN] = CODE_SPACE;
		break;
	case FILES_REPEAT_SCAN:
		PlayModeBuf[ORDER_RANDOM] = CODE_SPACE;
		PlayModeBuf[ORDER_LOOP] = CODE_MODE_SINGLE;
		PlayModeBuf[ORDER_SCAN] = CODE_MODE_SCN;
		break;
	case FILES_REPEAT_RANDOM:
		PlayModeBuf[ORDER_RANDOM] = CODE_MODE_RANDOM;
		PlayModeBuf[ORDER_LOOP] = CODE_MODE_SINGLE;
		PlayModeBuf[ORDER_SCAN] = CODE_SPACE;
		break;
	case FILES_REPEAT_SCAN_RANDOM:
		PlayModeBuf[ORDER_RANDOM] = CODE_MODE_RANDOM;
		PlayModeBuf[ORDER_LOOP] = CODE_MODE_SINGLE;
		PlayModeBuf[ORDER_SCAN] = CODE_MODE_SCN;
		break;
	default:
		PlayModeBuf[ORDER_RANDOM] = CODE_SPACE;
		PlayModeBuf[ORDER_LOOP] = CODE_SPACE;
		PlayModeBuf[ORDER_SCAN] = CODE_SPACE;
	    break;
	}


	LCD_TextW(PlayModeBuf,POS_PLAY_MODE_RANDOM_X,POS_PLAY_MODE_Y,FONT16);


}

/*****************************************************************************
* ID				 : 1.0
* Outline		 : LCD get font data
* Include		 : none
* Declaration		 : void main(void)
* Description		 : LCD module
* Argument 		 : void
* Return Value 	 : void
* Calling Functions : none
*****************************************************************************/
void Draw_play_disk(void)
{
	U16 ModeBuf[2];
	U8 DiskSDMode;
	U8 DiskUSBMode;

	ModeBuf[0] = 0x00;
	ModeBuf[1] = 0x00;

	if (Dispinfo.sd.connectSts == CONNECTED)
	{
		DiskSDMode = DISK_SD_LINK;
	}else
	{
		DiskSDMode = DISK_SD_UNLINK;
	}

	if (Dispinfo.usb.connectSts == CONNECTED)
	{
		DiskUSBMode = DISK_USB_LINK;
	} 
	else
	{
		DiskUSBMode = DISK_USB_UNLINK;
	}

	if (Dispinfo.currentFile.device == USB)
	{
		DiskUSBMode = DISK_USB_ACTIV;
	}else if (Dispinfo.currentFile.device == SD)
	{
		DiskSDMode = DISK_SD_ACTIV;
	}
	switch(DiskSDMode)
	{
	case DISK_SD_UNLINK:
		ModeBuf[0]=0x80;
		break;
	case DISK_SD_LINK:
		ModeBuf[0]=CODE_MODE_SD;
		break;
	case DISK_SD_ACTIV:
		ModeBuf[0]=CODE_MODE_SDR;
	    break;
	default:
		ModeBuf[0]=0x80;
	    break;
	}

	LCD_TextW(ModeBuf,POS_DISK_SD_X,POS_DISK_SD_Y,FONT16);

	switch(DiskUSBMode)
	{
	case DISK_USB_UNLINK:
		ModeBuf[0]=0x80;
			break;
	case DISK_USB_LINK:
		ModeBuf[0]=CODE_MODE_USB;
		break;
	case DISK_USB_ACTIV:
		ModeBuf[0]=CODE_MODE_USBR;
		break;
	default:
		ModeBuf[0]=0x80;
		break;
	}

	LCD_TextW(ModeBuf,POS_DISK_USB_X,POS_DISK_USB_Y,FONT16);

}

/*****************************************************************************
* ID				 : 1.0
* Outline		 : LCD get font data
* Include		 : none
* Declaration		 : void main(void)
* Description		 : LCD module
* Argument 		 : void
* Return Value 	 : void
* Calling Functions : none
*****************************************************************************/
void Draw_PlaySongAlbum(void)
{
	U16 StrDispWidth;
	U16 AlbumBuf[64];

	StrDispWidth = GetDrawTextWidthW((U16*)Dispinfo.currentFile.tagInfo.AlbumName.name);

	if (StrDispWidth>ALBUM_MAX_NUM*8)
	{
		memset(AlbumBuf,0,sizeof(AlbumBuf));
		memcpy(AlbumBuf,Dispinfo.currentFile.tagInfo.AlbumName.name,ALBUM_MAX_NUM*2);
		AlbumBuf[ALBUM_MAX_NUM]=CODE_ELLIPSIS;
		LCD_TextW(AlbumBuf,POS_PLAY_AUDIO_ALBUM_X,POS_PLAY_AUDIO_ALBUM_Y,FONT16);

	} 
	else
	{
		LCD_TextW((U16*)Dispinfo.currentFile.tagInfo.AlbumName.name,POS_PLAY_AUDIO_ALBUM_X,POS_PLAY_AUDIO_ALBUM_Y,FONT16);

	}

}
/*****************************************************************************
* ID				 : 1.0
* Outline		 : LCD get font data
* Include		 : none
* Declaration		 : void main(void)
* Description		 : LCD module
* Argument 		 : void
* Return Value 	 : void
* Calling Functions : none
*****************************************************************************/
void Draw_PlaySongTitle(void)
{


}

/*****************************************************************************
* ID				 : 1.0
* Outline		 : LCD get font data
* Include		 : none
* Declaration		 : void main(void)
* Description		 : LCD module
* Argument 		 : void
* Return Value 	 : void
* Calling Functions : none
*****************************************************************************/
void Draw_play_time(void)
{
	U16 LineLegth;
	U8 buf[10];
	U16 second,minute,hour;
	
	/*draw playback time*/
	if (Dispinfo.currentFile.PlaybackTimeInSecond>3600)
	{
		hour = Dispinfo.currentFile.PlaybackTimeInSecond/3600;
		minute = (Dispinfo.currentFile.PlaybackTimeInSecond%3600)/60;
		second = Dispinfo.currentFile.PlaybackTimeInSecond%60;

		sprintf(buf,"%01d:%02d:%02d",hour,minute,second);
		LCD_TextA(buf,POS_PLAY_TIME_PLAYBACK_X,POS_PLAY_TIME_Y,FONT16);
	}else
	{
		minute = Dispinfo.currentFile.PlaybackTimeInSecond/60;
		second = Dispinfo.currentFile.PlaybackTimeInSecond%60;
		sprintf(buf,"%02d:%02d",minute,second);
		LCD_TextA(buf,POS_PLAY_TIME_PLAYBACK_X+16,POS_PLAY_TIME_Y,FONT16);
	}

	/*Draw file time*/
	if(Dispinfo.currentFile.totalPlaybackTimeInSecond>3600)
	{
		hour = Dispinfo.currentFile.totalPlaybackTimeInSecond/3600;
		minute = (Dispinfo.currentFile.totalPlaybackTimeInSecond%3600)/60;
		second = Dispinfo.currentFile.totalPlaybackTimeInSecond%60;
		sprintf(buf,"%1d:%02d:%02d",hour,minute,second);
	}else
	{
		minute = Dispinfo.currentFile.totalPlaybackTimeInSecond/60;
		second = Dispinfo.currentFile.totalPlaybackTimeInSecond%60;
		sprintf(buf,"%02d:%02d",minute,second);
	}
	LCD_TextA(buf,POS_PLAY_TIME_FILE_X,POS_PLAY_TIME_Y,FONT16);

	/*Draw time line*/
	LineLegth = Dispinfo.currentFile.PlaybackTimeInSecond*POS_PLAY_TIME_LINE_WIDTH/Dispinfo.currentFile.totalPlaybackTimeInSecond;
	Draw_PlayTimeProgressFrame(POS_PLAY_TIME_LINE_X,POS_PLAY_TIME_Y+6,LineLegth,1);

}

/*****************************************************************************
* ID				 : 1.0
* Outline		 : LCD get font data
* Include		 : none
* Declaration		 : void main(void)
* Description		 : LCD module
* Argument 		 : void
* Return Value 	 : void
* Calling Functions : none
*****************************************************************************/
void Draw_play_startstop(void)
{
	U16 bufW[2];
	bufW[1] = 0x0000;

	if (Dispinfo.currentFile.PlayOrPause ==PLAY_STS_PLAYING)
	{
		bufW[0] = CODE_MODE_PAUSE;
	}else
	{
		bufW[0] = CODE_MODE_START;
	}

	LCD_TextW(bufW,POS_PLAY_PAUSE_X,POS_PLAY_PAUSE_Y,FONT16);

}

/*****************************************************************************
* ID				 : 1.0
* Outline		 : LCD get font data
* Include		 : none
* Declaration		 : void main(void)
* Description		 : LCD module
* Argument 		 : void
* Return Value 	 : void
* Calling Functions : none
*****************************************************************************/
void Draw_play_volume(void)
{
	U8 u8_i;
	U16 bufW[2];
	U8 buf[10];
	U8 VLevel;

	bufW[0] = CODE_SPEED_ON;
	bufW[1] = 0x00;

	LCD_TextW(bufW,POS_PLAY_SPEEK_X,POS_PLAY_SPEEK_Y,FONT16);

	sprintf(buf,"%02d",Volume);
	LCD_TextA(buf,POS_PLAY_SPEEK_VOLUME_X,POS_PLAY_SPEEK_Y,FONT16);

	VLevel = Volume/10;

	for (u8_i=0;u8_i<10;u8_i++)
	{
		if (u8_i<=VLevel)
		{
			LCD_DrawLineT(POS_PLAY_SPEEK_LINE_X+u8_i*2,POS_PLAY_SPEEK_Y+14-u8_i,POS_PLAY_SPEEK_LINE_X+u8_i*2,POS_PLAY_SPEEK_Y+14,0x0c);
		}else
		{
			LCD_DrawLineT(POS_PLAY_SPEEK_LINE_X+u8_i*2,POS_PLAY_SPEEK_Y+14-u8_i,POS_PLAY_SPEEK_LINE_X+u8_i*2,POS_PLAY_SPEEK_Y+14,0x03);
		}

	}
}

/*Draw song title*/



/*****************************************************************************
* ID				 : 1.0
* Outline		 : LCD get font data
* Include		 : none
* Declaration		 : void main(void)
* Description		 : LCD module
* Argument 		 : void
* Return Value 	 : void
* Calling Functions : none
*****************************************************************************/
void Draw_play(void)
{
	static DSIP_PLAY_STATE PlayState = DISP_PLAY_INIT;
	U32 u32_i;
	U8 Index;

	switch(PlayState)
	{
	case DISP_PLAY_INIT:

		Dispinfo.currentFile.device = SD;
		Dispinfo.currentFile.fileNum = 35;
		Dispinfo.currentFile.PlaybackTimeInSecond = 0;
		Dispinfo.currentFile.totalPlaybackTimeInSecond = 378;
		Dispinfo.currentFile.PlayOrPause = PLAY_STS_PLAYING;
		Dispinfo.currentFile.tagInfo.AlbumName.characterCode = ID3V2_UTF_16_BIG_ENDIAN;
		Dispinfo.currentFile.tagInfo.AlbumName.version = ID3V22;
		memset(Dispinfo.currentFile.tagInfo.AlbumName.name,0,128);
		memcpy(Dispinfo.currentFile.tagInfo.AlbumName.name,"\x41\x00\x4c\x00\x4c\x00\x20\x00\x45\x00\x76\x00\x65\x00\x72\x00\x20\x00\x57\x00\x61\x00\x6e\x00\x74\x00\x65\x00\x64\x00\x20\x00",32);
		Dispinfo.currentFile.tagInfo.artistName.characterCode = ID3V2_UTF_16_BIG_ENDIAN;
		Dispinfo.currentFile.tagInfo.artistName.version = ID3V22;
		memset(Dispinfo.currentFile.tagInfo.artistName.name,0,128);
		memcpy(Dispinfo.currentFile.tagInfo.artistName.name , "\x4b\x00\x65\x00\x6c\x00\x6c\x00\x79\x00\x20\x00\x43\x00\x6c\x00\x61\x00\x72\x00\x6b\x00\x73\x00\x6f\x00\x6e\x00",28);//Kelly Clarkson
		Dispinfo.currentFile.tagInfo.title.characterCode = ID3V2_UTF_16_BIG_ENDIAN;
		Dispinfo.currentFile.tagInfo.title.version = ID3V22;
		memset(Dispinfo.currentFile.tagInfo.title.name,0,128);
		//memcpy(Dispinfo.currentFile.tagInfo.title.name,"\x4d\x00\x79\x00\x20\x00\x4c\x00\x69\x00\x66\x00\x65\x00\x20\x00\x57\x00\x6f\x00\x75\x00\x6c\x00\x64\x00\x20\x00\x53\x00\x75\x00\x63\x00\x6b\x00\x20\x00\x57\x00\x69\x00\x74\x00\x68\x00\x6f\x00\x75\x00\x74\x00\x20\x00\x59\x00\x6f\x00\x75\x00\x20\x00",62);//My Life Would Suck Without You
		//memcpy(Dispinfo.currentFile.tagInfo.title.name,"\x11\x62\xec\x4e\xde\x8f\xc9\x89\x5f\x4e\xa1\x6c\x61\x77\xb3\x51\x9a\x5b\xde\x8f\x1c\x59\x76\x8d\xbb\x53\xdc\x62\xbf\x8b\x7e\x82\x9b\x52\x4b\x51\x4b\x51\xb1\x83\xaf\x65\x7f\x98\x20\x00",46);
		memcpy(Dispinfo.currentFile.tagInfo.title.name,"\x11\x62\xec\x4e\xde\x8f\xc9\x89\x5f\x4e\xa1\x6c\x61\x77\xb3\x51\x9a\x5b\xde\x8f\x1c\x59\x20\x00",24);
		
		Dispinfo.playbackMode = FOLDER_REPEAT_SCAN_RANDOM;

		Dispinfo.sd.totalFileNum =47;
		Dispinfo.sd.totalFolderNum = 6;
		Dispinfo.sd.connectSts = CONNECTED;
		Dispinfo.usb.totalFileNum = 56;
		Dispinfo.usb.totalFolderNum = 8;
		Dispinfo.usb.connectSts = CONNECTED;

		PlayState = DISP_PLAY_UPDATA; 
	break;
	case DISP_PLAY_UPDATA:

		Draw_play_disk();
		Draw_play_mode();
		Draw_play_volume();
		Draw_play_fileinfo();
		Draw_play_startstop();

		PlayState = DISP_PLAY_ROLLTITLE;

		break;
	case DISP_PLAY_ROLLTITLE:

		CheckTimeOut();

	    break;
	default:
	    break;
	}


	//PlayBackSecond=0;

	

}







