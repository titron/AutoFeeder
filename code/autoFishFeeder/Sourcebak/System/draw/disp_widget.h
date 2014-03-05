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
* File Name    : disp_widget.h
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
#ifndef __DISP_WIDGET_H__
#define __DISP_WIDGET_H__
/*****************************************************************************
Includes   <System Includes> , "Project Includes"
*****************************************************************************/
/*typedef enum{
	DISP_MSG_NULL = 0,
	DISP_MSG_DISK_CHANGE,
	DISP_MSG_PLAYMODE_CHANGE,
	DISP_MSG_VOLUME_CHANGE,
	DISP_MSG_FOLDER_CHANGE,
	DISP_MSG_FILE_CHANGE,
	DISP_MSG_FILE_BECHANGE,
	DISP_MSG_PLAYSTATE_CHANGE,
	DISP_MSG_PLAYTIMER_CHANGE,
	DISP_MSG_MENU_ITEM_CHANGE,
	DISP_MSG_MENU_ITEM_IN,
	DISP_MSG_MENU_ITEM_OUT,
	DISP_MSG_MENU_ITEM_REDRAW,
}Disp_Message;*/
#define		DISP_MSG_NULL					(U32)0x00000000
#define		DISP_MSG_DISK_CHANGE			(U32)0x00000001
#define		DISP_MSG_PLAYMODE_CHANGE		(U32)0x00000002
#define		DISP_MSG_VOLUME_CHANGE			(U32)0x00000004
#define		DISP_MSG_FOLDER_CHANGE			(U32)0x00000008
#define		DISP_MSG_FOLDER_PULLDOWN 		(U32)0x00000010
#define		DISP_MSG_FILE_CHANGE		 	(U32)0x00000020
#define		DISP_MSG_FILE_BECHANGE		 	(U32)0x00000040
#define		DISP_MSG_PLAYSTATE_CHANGE	 	(U32)0x00000080
#define		DISP_MSG_PLAYTIMER_CHANGE	 	(U32)0x00000100
#define		DISP_MSG_PLAYTIMER_REDRAW	 	(U32)0x00000200
#define		DISP_MSG_MENU_ITEM_CHANGE	 	(U32)0x00000400
#define		DISP_MSG_MENU_ITEM_IN		 	(U32)0x00000800
#define		DISP_MSG_MENU_ITEM_OUT		 	(U32)0x00001000
#define		DISP_MSG_MENU_ITEM_REDRAW	 	(U32)0x00002000
#define     DISP_MSG_FOLDER_SHOW_HIDE		(U32)0x00004000
#define		DISP_MSG_POWEROFF				(U32)0x00008000
#define		DISP_MSG_MENU_ITEM				(U32)0x00010000
#define		DISP_MSG_VOLUME_SHOW_HIDE		(U32)0x00020000
#define     DISP_MSG_WARN_NOMEDIA           (U32)0x00040000
#define     DISP_MSG_WARN_ANYING			(U32)0x00080000
/*note change total number*/			

#define		DISP_MSG_NOMASK				(U32)0xffffffff

#define		DISP_MSG_NUM				(U8)20

#define		Disp_Message	U32
/*****************************************************************************
Typedef definitions
*****************************************************************************/
/* ---- display widget related types ---- */
typedef void (* Disp_MsgProcFuncType)(Disp_Message Msg);//(Svc_MsgType* pMessage);
typedef void (* Disp_InitFuncType)(void);
typedef void (* Disp_PaintFuncType)(U8 Mode);
typedef void (* Disp_TimeoutFuncType)(void);
typedef void (* Disp_ScreenInit)(void);

#define TIMER_ONESTEP	0
#define TIMER_COUNT		1
#define TIMER_INFINITY	2

/*Updata widget on time*/
typedef struct  
{
	U32 DalyTime;  
	U8	Type;		/* Timer type, 0:one step,1:count, 2,infinity*/
	U8	Count;		/*If timer type is select 1,count mode, this is the number of count*/
	Disp_TimeoutFuncType CheckTimeout;  /*This is the func witch be called on time*/
	U32	*TimerTick; /* This is the point of variable which can save current time*/
	U8 *TimeEnable; /* TRUE:enable FLASE:disable*/
	U8 *TimerCnt;
}Disp_WidgetTimer;

/*Menu item*/
typedef void (* Disp_MenuItemPaint)(U8 mode);
typedef void (* Disp_MenuItemInit)(void);
typedef void (* Disp_MenuItemMsg)(U8 Msg);

typedef struct  
{
	U8 ItemNameNo;
	Disp_MenuItemPaint ItemPaint;
	Disp_MenuItemMsg    ItemMsg;
	U8		SubMenuNo;
}Disp_WidgetMenuItem;

typedef struct  
{
	U8 MenuNameNo;
	U8 ItemNum;
	U8 MaxItemPerscreen;
	Disp_WidgetMenuItem const ** Items;
	U8 *Cursor;
	U8 UpMenuNo;
	Disp_MenuItemPaint MenuPaint;
}Disp_WidgetMenu;

typedef struct {
	U16 PosX;
	U16 PoxY;
	U16 Width;
	U16 Heigth;
	U8* RawData;
	Disp_MsgProcFuncType MsgProc;
	Disp_InitFuncType Init;
	Disp_PaintFuncType Paint;
	Disp_WidgetTimer const * Timer;
} Disp_WidgetType;


typedef struct  
{
	U8 WidgetNum; /* numbers of widget in screen*/
	Disp_WidgetType const ** Widget;
	Disp_ScreenInit	Init;
}Disp_Screen;
/*****************************************************************************
Macro definitions
*****************************************************************************/
#define NULL		0
#define NULL_PTR (U32 *)0
#define NULL_PTRR (u32 **)0

#define RAWDATA_NULL		(U8*)0
#define MSGPROC_NULL		(Disp_MsgProcFuncType)0
#define INITFUNC_NULL		(Disp_InitFuncType)0
#define PAINT_NULL			(Disp_PaintFuncType)0
#define TIMER_NULL			(Disp_WidgetTimer*)0


#define FOLDER_SCAN_DRAW_UP			(U8)0
#define FOLDER_SCAN_DRAW_DOWN		(U8)1
#define FOLDER_SCAN_DRAW_BUF_UP		(U8)2
#define FOLDER_SCAN_DRAW_BUF_DOWN	(U8)3
#define FOLDER_SCAN_DRAW_BUF_UPSWITCH (U8)4
#define FOLDER_SCAN_DRAW_BUF_DOWNSWITCH (U8)5
#define FOLDER_SCAN_DRAW_BUF_UP_ALL		(U8)6
#define FOLDER_SCAN_DRAW_BUF_DWWN_ALL	(U8)7
	
#define  Dispinfo AE1MsgForDisplay

typedef enum{
	DISP_SCREEN_PLAY=0,
	DISP_SCREEN_FOLERSCAN,
	DISP_SCREEN_SETTING,
	DISP_SCREEN_TEST,
	DISP_SCREEN_NULL,
}DISP_SCREEN_NO;


/*****************************************************************************
Imported global variables and functions (from other files)
*****************************************************************************/
//extern Disp_WidgetType WidgetTitle;
extern Disp_Message DispMessage;
extern Disp_Message DispMsgMask;
extern DISP_SCREEN_NO DispScreenNo;
extern U8 FolderPullEnable;
extern const Disp_Screen * Screen[];
extern U8 CheckTimeOut(void);
/*****************************************************************************
Exported global variables and functions (to be accessed by other files)
*****************************************************************************/

/*****************************************************************************
Private variables and functions
*****************************************************************************/



#endif
