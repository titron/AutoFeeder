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
 * File Name    : service_general.c
 * Abstract     : general service
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AE1-LF demo board
 * Description  : This is the service routine involved clock/timer/interrput and 
                : error management.
 * Operation    : none
 * Limitation   : This file can be only used as sample code for AE1-LF.
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "service_general.h"
#include "driver_int.h"
#include "driver_clock.h"
#include "driver_watchdog.h"
#include "if_lcd_draw.h"
#include "if_lcd_text.h"
#include "app_ae1.h"

/*****************************************************************************
 Private variables and functions
 *****************************************************************************/
volatile U16 U16TimerCountService = (U16)0;		/* volatile is for optimium */
static U8 ErrorLogBuffer[ERROR_LOG_BUFFER_SIZE];
static U8 U8ErrorLogIndex = (U8)0;

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/

/*****************************************************************************
 * ID                :
 * Outline           : Service_Gene_LimitS8
 * Include           : 
 * Declaration       : void Service_Gene_LimitS8(S8* pS8Value, S8 S8Min, S8 S8Max)
 * Description       : Limit the range of S8 type data
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Service_Gene_LimitS8(S8* pS8Value, S8 S8Min, S8 S8Max)
{
	if(*pS8Value > S8Max){
		*pS8Value = S8Max;
	}else if(*pS8Value < S8Min) {
		*pS8Value = S8Min;
	}else{
		/* do nothing */
	}
}

#if 0
/*****************************************************************************
 * ID                :
 * Outline           : Service_Gene_LimitU8
 * Include           : 
 * Declaration       : void Service_Gene_LimitU8(U8* pU8Value, U8 U8Min, U8 U8Max)
 * Description       : Limit the range of U8 type data
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Service_Gene_LimitU8(U8* pU8Value, U8 U8Min, U8 U8Max)
{
	if(*pU8Value > U8Max){
		*pU8Value = U8Max;
	}else if(*pU8Value < U8Min) {
		*pU8Value = U8Min;
	}else{
		/* do nothing */
	}
}
#endif

/*****************************************************************************
 * ID                :
 * Outline           : MCU clock 
 * Include           : none
 * Declaration       : void Service_Clock_SelectHighSpeedOCO(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Service_Clock_SelectHighSpeedOCO(void)
{
	Drv_Clock_SelectHighSpeedOCO();
}

/*****************************************************************************
 * ID                :
 * Outline           : MCU clock 
 * Include           : none
 * Declaration       : void Service_Clock_SelectLowSpeedOCO(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Service_Clock_SelectLowSpeedOCO(void)
{
	Drv_Clock_SelectLowSpeedOCO();
}

/*****************************************************************************
 * ID                :
 * Outline           : Disable the interrupt of MCU
 * Include           : 
 * Declaration       : void Service_INT_DisableInterrupt(void)
 * Description       : Disable the interrupt of MCU
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Service_INT_DisableInterrupt(void)
{
	Drv_INT_DisableInterrupt();
}

/*****************************************************************************
 * ID                :
 * Outline           : Enable the interrupt of MCU
 * Include           : 
 * Declaration       : void Service_INT_EnableInterrupt(void)
 * Description       : Enable the interrupt of MCU
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Service_INT_EnableInterrupt(void)
{
	Drv_INT_EnableInterrupt();
}

/*****************************************************************************
 * ID                :
 * Outline           : Initialize the watchdog when CPU use high-speed OCO
 * Include           : 
 * Declaration       : void Service_WDT_InitWDTInHighSpeedOCO(void)
 * Description       : Initialize the watchdog
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Service_WDT_InitWDTInHighSpeedOCO(void)
{
	Drv_WDT_InitWDTInHighSpeedOCO();
}

/*****************************************************************************
 * ID                :
 * Outline           : Initialize the watchdog when CPU use low-speed OCO
 * Include           : 
 * Declaration       : void Service_WDT_InitWDTInLowSpeedOCO(void)
 * Description       : Initialize the watchdog
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Service_WDT_InitWDTInLowSpeedOCO(void)
{
	Drv_WDT_InitWDTInLowSpeedOCO();
}

/*****************************************************************************
 * ID                :
 * Outline           : Feed the watchdog
 * Include           : 
 * Declaration       : void Service_WDT_FeedDog(void)
 * Description       : Feed the watchdog
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Service_WDT_FeedDog(void)
{
	Drv_Watchdog_FeedDog();
}

/*****************************************************************************
 * ID                :
 * Outline           : Error log
 * Include           : 
 * Declaration       : void Serive_Error_Log(void)
 * Description       : log the error
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Service_Error_Log(U8 ErrorNo)
{
	ErrorLogBuffer[U8ErrorLogIndex] = ErrorNo;

	U8ErrorLogIndex++;
	if(U8ErrorLogIndex >= ERROR_LOG_BUFFER_SIZE){
		U8ErrorLogIndex = (U8)0;
	}
}

#if 0
/*****************************************************************************
 * ID                :
 * Outline           : Read error log
 * Include           : 
 * Declaration       : U8 Service_Error_ReadLog(U8 U8Index)
 * Description       : Read error log
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
U8 Service_Error_ReadLog(U8 U8Index)
{
	U8 ret;
	if(U8Index < ERROR_LOG_BUFFER_SIZE){
		ret = ErrorLogBuffer[U8Index];
	}else{
		ret = ERROR_NULL;
	}
	return ret;
}
#endif

#ifdef DEBUG_ON
/*****************************************************************************
 * ID                :
 * Outline           : Error log
 * Include           : 
 * Declaration       : void Serive_Error_Log(void)
 * Description       : log the error
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Service_Error_PrintInfo(U8 * ErrorStr)
{
	If_disp_clear();
	LCD_TextA((U8*)"**ERROR LOG**",(U16)16,(U16)0,FONT16);
	LCD_TextA(ErrorStr,(U16)32,(U16)16,FONT16);
}
#endif

#if 0
/*****************************************************************************
 * ID                :
 * Outline           : Service_Timer_WaitTime
 * Include           : 
 * Declaration       : void Service_Timer_WaitTime(U16 U16TimeMS)
 * Description       : Wait for some time, unit ms
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void Service_Timer_WaitTime(U16 U16TimeMS)
{
	U16TimerCountService = (U16)0;
	while(U16TimerCountService < U16TimeMS){}	/* Wait for U16TimeMS ms */
}
#endif

/* End of file */
