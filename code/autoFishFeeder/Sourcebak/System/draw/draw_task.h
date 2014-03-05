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
* File Name    : disp_task.h
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


/*****************************************************************************
Typedef definitions
*****************************************************************************/
/* Display task state */
typedef enum{
	DISP_INIT = 0,
	DISP_WAIT_VCC12,
	DISP_PLAY,
	DISP_SETTING,
	DISP_MAINTAIN,
	DISP_VOLUME_PULLUP,
	DISP_FOLDERSCAN,
	DISP_FILESCAN,
	DISP_SHUTDOWN,
	DISP_POWERDOWN,
	DISP_ROLLING,
}DISP_STATE;

typedef enum{
	DISP_FOLDER_INIT = 0,
	DISP_FOLDER_UP,
	DISP_FOLDER_DOWN,
	DISP_FOLDER_IDLE,
	DISP_FOLDER_EXIT,
}DISP_FOLDER_STATE;

typedef enum{
	DISP_SHUTDOWN_INIT = 0,
	DISP_SHUTDOWN_1,
	DISP_SHUTDOWN_2,
	DISP_SHUTDOWN_3,
	DISP_SHUTDOWN_4,
}DISP_SHUTDOWN_STATE;
/*****************************************************************************
Macro definitions
*****************************************************************************/


/*****************************************************************************
Imported global variables and functions (from other files)
*****************************************************************************/
extern void App_Task_Disp(void);

extern U8 DispShutDown;
extern DISP_STATE DispState;
/*****************************************************************************
Exported global variables and functions (to be accessed by other files)
*****************************************************************************/


/*****************************************************************************
Private variables and functions
*****************************************************************************/





