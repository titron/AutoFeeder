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
 * File Name    : main.c
 * Abstract     : main routine
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AE1-LF demo board
 * Description  : This is the main routine.
 * Operation    : none
 * Limitation   : This file can be only used as sample code for AE1-LF.
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "basictype.h"
#include "driver_oled.h"
#include "draw_task.h"
#include "if_power.h"
#include "if_reset.h"
#include "if_led.h"
#include "if_lcd_text.h"
#include "if_iic.h"
#include "if_key.h"
#include "app_ae1.h"
#include "app_host.h"
#include "app_evolume.h"
#include "service_general.h"

#include "config.h"
#include "disp_widget.h"m
#include "sfr_r82b.h"
/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
#define SYS_INIT 			(0)
#define SYS_NORMAL 			(SYS_INIT + 1)
#define SYS_FEEDING 		(SYS_NORMAL + 1)
#define SYS_SLEEP 			(SYS_FEEDING + 1)

#define SYS_FEED_TIME_IN_MS     5
#define SYS_DEFAULT_TIME_HOUR   	0x14
#define SYS_DEFAULT_TIME_MINUTE 	0x00
#define SYS_DEFAULT_TIME_SECOND 	0x00
#define SYS_FEED_TIME_HOUR   	0x08
#define SYS_FEED_TIME_MINUTE 	0x00
#define SYS_FEED_TIME_SECOND 	0x00
#define SYS_FEED_TIME_MILCOND	(1000-SYS_FEED_TIME_IN_MS)

/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/

/*****************************************************************************
 Private variables and functions
 *****************************************************************************/
u8 stSys = SYS_INIT;
u32 vsysHour = SYS_DEFAULT_TIME_HOUR;
u32 vsysMinute = SYS_DEFAULT_TIME_MINUTE;
u32 vsysSecond = SYS_DEFAULT_TIME_SECOND;
u32 vsysMilSecond = 0;
u32 vsysFeedTime = 0;
u32 vsysFeedHour = SYS_FEED_TIME_HOUR;
u32 vsysFeedMinute = SYS_FEED_TIME_MINUTE;
u32 vsysFeedSecond = SYS_FEED_TIME_SECOND;
static void InitializationMCU(void);

/*****************************************************************************
 * ID                : 1.0
 * Outline           : InitializationMCU function
 * Include           : none
 * Declaration       : void main(void)
 * Description       : Initialize
 *                   : --- clock
 *                   : --- GPIO
 *                   : --- I2C
 *                   : --- timer
 *                   : --- UART0
 *                   : --- UART2
 * Argument          : void
 * Return Value      : void
 * Calling Functions : none
 *****************************************************************************/
void InitializationMCU(void)
{
	Service_INT_DisableInterrupt();
	Service_Clock_SelectHighSpeedOCO();	/* Initialize Clock module */
	If_Power_InitPowerControl();		/* Initialize power control */
	Service_INT_EnableInterrupt();
}

void sys_Init(void)
{
	/* MCU restore the high-speed mode */
	Service_INT_DisableInterrupt();
	Service_Clock_SelectHighSpeedOCO();	/* Initialize Clock module */
	Service_WDT_InitWDTInHighSpeedOCO();
	If_Power_InitPowerControl();		/* Initialize power control */
	If_Led_InitLed();					/* Initialize Led */
	If_Timer_InitSysTimerInHighSpeed();	/* Initialize timer */
	Service_INT_EnableInterrupt();
	If_Power_TurnOn();
	If_Led_SetState(LED_POWER, LED_ON);
}

u8 sys_IsFeedingTime(void)
{
	if((vsysFeedHour == vsysHour) &&
		(vsysFeedMinute== vsysMinute) &&
		(vsysFeedSecond== vsysSecond) &&
		(SYS_FEED_TIME_MILCOND < vsysMilSecond)
			)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
void sys_Feeding(void)
{
	vsysFeedTime = 0;
	If_Led_SetState(LED_HEART, LED_ON);
	If_Power_5V_TurnOn();
}

void sys_stopFeed(void)
{
	vsysFeedTime = 0;
	If_Led_SetState(LED_HEART, LED_OFF);
	If_Power_5V_TurnOff();
}

u8 sys_IsFeedComplete(void)
{
	if(SYS_FEED_TIME_IN_MS < vsysFeedTime)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

	U32 vbaktimeInSecond = (U32) 0;
static void UpdateAE1MsgForDisp_CurTime(void)
{
	U32 vCurtimeInSecond = (U32) 0;

	vCurtimeInSecond = vsysHour;/* Hour */
	vCurtimeInSecond = vCurtimeInSecond * (U32) 60;/* Minute */
	vCurtimeInSecond = vCurtimeInSecond + vsysMinute;/* Minute */

	vCurtimeInSecond = vCurtimeInSecond * (U32) 60;/* Second */

	vCurtimeInSecond = vCurtimeInSecond + vsysSecond;/* Second */

	if(vCurtimeInSecond != vbaktimeInSecond)
	{
		AE1MsgForDisplay.currentFile.PlaybackTimeInSecond = vCurtimeInSecond;
		vbaktimeInSecond = vCurtimeInSecond;
		DispMessage |= (U32) DISP_MSG_PLAYTIMER_CHANGE;
	}

}

U32 vbakFeedtimeInSecond = (U32) 0;
static void UpdateAE1MsgForDisp_FeedTime(void)
{
	U32 vCurtimeInSecond = (U32) 0;

	vCurtimeInSecond = vsysFeedHour;/* Hour */
	vCurtimeInSecond = vCurtimeInSecond * (U32) 60;/* Minute */
	vCurtimeInSecond = vCurtimeInSecond + vsysFeedMinute;/* Minute */

	vCurtimeInSecond = vCurtimeInSecond * (U32) 60;/* Second */

	vCurtimeInSecond = vCurtimeInSecond + vsysFeedSecond;/* Second */

	if(vCurtimeInSecond != vbakFeedtimeInSecond)
	{
		AE1MsgForDisplay.currentFile.totalPlaybackTimeInSecond = vCurtimeInSecond;
		vbakFeedtimeInSecond = vCurtimeInSecond;
		DispMessage |= (U32) DISP_MSG_PLAYTIMER_CHANGE;
	}
	

}

void sysAdjustTime(U8 keyEvent)
{
      if(keyEvent == EVENT_KEY_1_DOWN){
		vsysHour++;
		if(23 <= vsysHour)
		{
			vsysHour = 0;
		}
	}

	if(keyEvent == EVENT_KEY_2_DOWN){
		vsysMinute++;
		if(60 <= vsysMinute)
		{
			vsysMinute = 0;
		}
	}

	

	if(keyEvent == EVENT_KEY_5_DOWN){
		vsysFeedHour++;
		if(23 <=vsysFeedHour)
		{
			vsysFeedHour = 0;
		}
	}

	if(keyEvent == EVENT_KEY_6_DOWN){
		vsysFeedMinute++;
		if(60 <=vsysFeedMinute)
		{
			vsysFeedMinute = 0;
		}
	}
}

void sysKeyPro(void)
{
	U8 syskeyEvent = EVENT_KEY_NONE;

	App_Task_Key();
	/* Get the key event, then clear */
	syskeyEvent = If_Key_GetEvent();
	If_Key_ClearEvent();
	
	sysAdjustTime(syskeyEvent);
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : main function
 * Include           : none
 * Declaration       : void main(void)
 * Description       : main function
 * Argument          : void
 * Return Value      : void
 * Calling Functions :
 *                   : InitializationMCU()
 *****************************************************************************/
void main(void)
{
	unsigned short i,j;
	
	/* InitializationMCU */
	InitializationMCU();
	/* Task loop */
	for(;;)
	{
		/* Feed the watchdog */
		//Service_WDT_FeedDog();

		UpdateAE1MsgForDisp_CurTime();
		UpdateAE1MsgForDisp_FeedTime();

		switch(stSys)
		{
		case SYS_INIT:
			sys_Init();
			stSys = SYS_NORMAL;
			break;
		case SYS_NORMAL:
			if(TRUE == sys_IsFeedingTime())
			{
				sys_Feeding();
				stSys = SYS_FEEDING;
			}
			break;
		case SYS_FEEDING:
			if(TRUE == sys_IsFeedComplete())
			{
				sys_stopFeed();
				stSys = SYS_NORMAL;
			}
			break;
		case SYS_SLEEP:
			stSys = SYS_NORMAL;
			break;
		default:
			break;
		}
		
		sysKeyPro();

		App_Task_Disp();		/* Display task */
	}
}
/* End of file */