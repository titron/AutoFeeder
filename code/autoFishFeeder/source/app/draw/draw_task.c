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
#include "basictype.h"
#include "if_oled_draw.h"
#include "if_oled_text.h"
#include "draw_task.h"
#include "drv_tmr0.h"
#include "if_disp.h"
#include <math.h>
#include "drv_oled.h"
#include "string.h"

/*****************************************************************************
Typedef definitions
*****************************************************************************/

/*****************************************************************************
Macro definitions
*****************************************************************************/
/*Postion define*/
#define POS_OFFSET 					(U16)16
#define POS_PLAY_TIME_X				(U16)100
#define POS_PLAY_TIME_Y				(U16)48
#define POS_PLAY_TIME_PLAYBACK_X	POS_PLAY_TIME_X
#define POS_PLAY_TIME_LINE_X		(POS_PLAY_TIME_X+(U16)40-POS_OFFSET)
#define POS_PLAY_TIME_LINE_WIDTH	(U16)100
#define POS_PLAY_TIME_FILE_X		(POS_PLAY_TIME_X+POS_PLAY_TIME_LINE_WIDTH+(U16)40+(U16)8)

#define FISH_BMP_POS_X 				0
#define FISH_BMP_POS_Y 				30

/*****************************************************************************
Imported global variables and functions (from other files)
*****************************************************************************/

/*****************************************************************************
Exported global variables and functions (to be accessed by other files)
*****************************************************************************/
DISP_STATE DispState = DISP_INIT;
U32 DispWaitTM; 
U8 DispTest[] = "AutoFeeder!";
/*****************************************************************************
Private variables and functions
*****************************************************************************/

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
extern u32 vsysHour;
extern u32 vsysMinute;
extern u32 vsysSecond;
extern u32 vsysFeedHour;
extern u32 vsysFeedMinute;
extern u32 vsysFeedSecond;
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

void updateTimerPaint(U8 mode)
{
	U16 LineLegth;
	U8 buf[10];
	U16 second,minute,hour;
	U16 offset;
	/*draw total time*/
	hour = (U16)vsysHour;
	minute = (U16)vsysMinute;
	second = (U16)vsysSecond;
	memset(buf,0,sizeof(buf));
	Strformat3(buf,hour,minute,second,":",(U8)2);
	OLED_TextA(buf,POS_PLAY_TIME_PLAYBACK_X,POS_PLAY_TIME_Y-16,FONT16);
	/*draw playback time*/
	hour = (U16)vsysFeedHour;
	minute = (U16)vsysFeedMinute;
	second = (U16)vsysFeedSecond;
	memset(buf,0,sizeof(buf));
	Strformat3(buf,hour,minute,second,":",(U8)2);
	OLED_TextA(buf,POS_PLAY_TIME_PLAYBACK_X,POS_PLAY_TIME_Y,FONT16);
}

void App_Task_Disp(void){
	switch(DispState)
	{
	case DISP_INIT:
		/*Wait for power up*/
		/*clear timer*/
		CurrentTimer = (U32)0;
		DispWaitTM = CurrentTimer;
		/*switch to wait vcc12 mode*/
		DispState = DISP_WAIT_VCC12;
		break;
	case DISP_WAIT_VCC12:
		/*after reset oled, wait for 100ms ,then set 12v*/
		if(CurrentTimer>(DispWaitTM+(U32)TIME_100MS))
		{
			if_Disp_Init();
			if_Disp_SetStartLine(DISP_SCREEN_START_LINE);
			/*switch to play mode*/
			DispState = DISP_PLAY;
		}
		break;
	case DISP_PLAY:
		OLED_TextA(DispTest,ORIGNAL_POS_X,ORIGNAL_POS_Y,FONT16);
		updateTimerPaint(REDRAW);
		OLED_DrawBmp(FISH_BMP_POS_X,FISH_BMP_POS_Y,BMP_FISH_NO);
		break;
	default:
		break;
	}
}
