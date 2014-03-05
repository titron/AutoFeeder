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
 * System Name  : AutoFeeder
 * File Name    : main.c
 * Abstract     : main routine
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AutoFeeder module
 * Description  : This is the main routine.
 * Operation    : none
 * Limitation   : none
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/
/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "basictype.h"
#include "drv_int.h"
#include "drv_clk.h"
#include "drv_wdt.h"
#include "drv_led.h"
#include "drv_tmr0.h"
#include "drv_key.h"
#include "if_key.h"

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
#define SYS_INIT 					(0)
#define SYS_NORMAL 					(SYS_INIT + 1)
#define SYS_FEEDING 				(SYS_NORMAL + 1)
#define SYS_SLEEP 					(SYS_FEEDING + 1)

#define SYS_FEED_TIME_IN_MS     	5
#define SYS_DEFAULT_TIME_HOUR   	0x14
#define SYS_DEFAULT_TIME_MINUTE 	0x00
#define SYS_DEFAULT_TIME_SECOND 	0x00
#define SYS_FEED_TIME_HOUR   		0x08
#define SYS_FEED_TIME_MINUTE 		0x00
#define SYS_FEED_TIME_SECOND 		0x00
#define SYS_FEED_TIME_MILCOND		(1000-SYS_FEED_TIME_IN_MS)

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
	drv_Led_SetState(LED_HEART, LED_ON);
	drv_Pwr_5V_TurnOn();
}

void sys_stopFeed(void)
{
	vsysFeedTime = 0;
	drv_Led_SetState(LED_HEART, LED_OFF);
	drv_Pwr_5V_TurnOff();
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
void initMCU(void){
	drv_INT_Disable();
	drv_Clk_SelectHighSpeedOCO();	/* Initialize Clock module */
	drv_Pwr_InitPwrCtrl();		/* Initialize power control */
	drv_INT_Enable();
}

void sys_Init(void)
{
	/* MCU restore the high-speed mode */
	drv_INT_Disable();
	drv_Clk_SelectHighSpeedOCO();
	drv_WDT_InitWDTInHighSpeedOCO();
	drv_Pwr_InitPwrCtrl();
	drv_Led_InitLed();
	drv_Tmr0_InitTmr0InHighSpeed();	/* Initialize timer */
	drv_INT_Enable();
	drv_Power_TurnOn();
	drv_Led_SetState(LED_POWER, LED_ON);
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

	if_Key_Scan();
	/* Get the key event, then clear */
	syskeyEvent = if_Key_GetEvent();
	if_Key_ClearEvent();

	sysAdjustTime(syskeyEvent);
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : main
 * Include           : none
 * Declaration       : void main(void)
 * Description       : main
 * Argument          : void
 * Return Value      : void
 * Calling Functions : none
 *****************************************************************************/
void main(void){
	/* InitializationMCU */
	initMCU();

	/* main loop */
	while(1){
		/* Feed the watchdog */
		//drv_Watchdog_FeedDog();

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
