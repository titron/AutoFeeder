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
 * File Name    : service_general.h
 * Abstract     : general service
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AE1-LF demo board
 * Description  : This is the header file of general service.
 * Operation    : none
 * Limitation   : This file can be only used as sample code for AE1-LF.
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/
#ifndef __SERVICE_GENERAL_H__
#define __SERVICE_GENERAL_H__
/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "basictype.h"

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
/* Error definition */
#define ERROR_NULL							(U8)0
#define ERROR_IIC_NOACK						(U8)1
#define ERROR_FLASH_NO_USER_DATA			(U8)2
#define ERROR_TIMEOUT_AE1_POWER_DOWN		(U8)3
#define ERROR_TIMEOUT_EV_POWER_DOWN			(U8)4
#define ERROR_TIMEOUT_FLASH_POWER_DOWN		(U8)5
#define ERROR_AE1_COMM_00					(U8)6
#define ERROR_AE1_COMM_01					(U8)7
#define ERROR_AE1_COMM_02					(U8)8
#define ERROR_AE1_COMM_03					(U8)9
#define ERROR_AE1_COMM_04					(U8)10
#define ERROR_AE1_COMM_05					(U8)11
#define ERROR_AE1_COMM_06					(U8)12
#define ERROR_AE1_COMM_07					(U8)13
#define ERROR_AE1_COMM_08					(U8)14
#define ERROR_AE1_COMM_09					(U8)15
#define ERROR_AE1_COMM_10					(U8)16

#define ERROR_LOG_BUFFER_SIZE				(U16)16
/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/
extern volatile U16 U16TimerCountService;
#if 0
extern void Service_Timer_WaitTime(U16 U16TimeMS);
#endif
extern void Service_Gene_LimitS8(S8* pS8Value, S8 S8Min, S8 S8Max);
#if 0
extern void Service_Gene_LimitU8(U8* pU8Value, U8 U8Min, U8 U8Max);
#endif
extern void Service_Clock_SelectHighSpeedOCO(void);
extern void Service_Clock_SelectLowSpeedOCO(void);
extern void Service_INT_DisableInterrupt(void);
extern void Service_INT_EnableInterrupt(void);
extern void Service_WDT_InitWDTInHighSpeedOCO(void);
extern void Service_WDT_InitWDTInLowSpeedOCO(void);
extern void Service_WDT_FeedDog(void);
extern void Service_Error_Log(U8 ErrorNo);
#ifdef DEBUG_ON
extern void Service_Error_PrintInfo(U8 * ErrorStr);
#endif
/* extern U8 Service_Error_ReadLog(U8 U8Index); */
#endif
/* End of File */