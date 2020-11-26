/*
 * main.c
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */

/*
 * Includes
 */
#include "main.h"

/*
 * Typedef
 */

/*
 * Macro
 */
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

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */
u32 vsysHour = SYS_DEFAULT_TIME_HOUR;
u32 vsysMinute = SYS_DEFAULT_TIME_MINUTE;
u32 vsysSecond = SYS_DEFAULT_TIME_SECOND;
u32 vsysMilSecond = 0;
u32 vsysFeedTime = 0;
u32 vsysFeedHour = SYS_FEED_TIME_HOUR;
u32 vsysFeedMinute = SYS_FEED_TIME_MINUTE;
u32 vsysFeedSecond = SYS_FEED_TIME_SECOND;

/*
 * Private variables and functions
 */
u8 stSys = SYS_INIT;

/*
 * sys_IsFeedingTime
 *
 */
u8 sys_IsFeedingTime(void)
{
	if ((vsysFeedHour == vsysHour) && (vsysFeedMinute == vsysMinute)
			&& (vsysFeedSecond == vsysSecond)
			&& (SYS_FEED_TIME_MILCOND < vsysMilSecond))
	{
		return TRUE ;
	}
	else
	{
		return FALSE ;
	}
}

/*
 * sys_Feeding
 * start feeding.
 */
void sys_Feeding(void)
{
	vsysFeedTime = 0;
	drv_Led_SetState(LED_HEART, LED_ON);
	drv_Pwr_5V_TurnOn();
}

/*
 * sys_stopFeed
 */
void sys_stopFeed(void)
{
	vsysFeedTime = 0;
	drv_Led_SetState(LED_HEART, LED_OFF);
	drv_Pwr_5V_TurnOff();
}

/*
 * sys_IsFeedComplete
 */
u8 sys_IsFeedComplete(void)
{
	if (SYS_FEED_TIME_IN_MS < vsysFeedTime)
	{
		return TRUE ;
	}
	else
	{
		return FALSE ;
	}

}

/*
 * initMCU
 */
void initMCU(void)
{
	drv_INT_Disable();
	drv_Clk_SelectHighSpeedOCO(); /* Initialize Clock module */
	drv_Pwr_InitPwrCtrl(); /* Initialize power control */
	drv_INT_Enable();
}

/*
 * sys_Init
 */
void sys_Init(void)
{
	/* MCU restore the high-speed mode */
	drv_INT_Disable();
	drv_Clk_SelectHighSpeedOCO();
	drv_WDT_InitWDTInHighSpeedOCO();
	drv_Pwr_InitPwrCtrl();
	drv_Led_InitLed();
	drv_Tmr0_InitTmr0InHighSpeed(); /* Initialize timer */
	drv_INT_Enable();
	drv_Power_TurnOn();
	drv_Led_SetState(LED_POWER, LED_ON);
	drv_stepper_init();
}

/*
 * sysAdjustTime
 */
void sysAdjustTime(U8 keyEvent)
{
	if (keyEvent == EVENT_KEY_1_DOWN)
	{
		vsysHour++;
		if (23 <= vsysHour)
		{
			vsysHour = 0;
		}
	}

	if (keyEvent == EVENT_KEY_2_DOWN)
	{
		vsysMinute++;
		if (60 <= vsysMinute)
		{
			vsysMinute = 0;
		}
	}

	if (keyEvent == EVENT_KEY_5_DOWN)
	{
		vsysFeedHour++;
		if (23 <= vsysFeedHour)
		{
			vsysFeedHour = 0;
		}
	}

	if (keyEvent == EVENT_KEY_6_DOWN)
	{
		vsysFeedMinute++;
		if (60 <= vsysFeedMinute)
		{
			vsysFeedMinute = 0;
		}
	}
}

/*
 * sysKeyPro
 */
void sysKeyPro(void)
{
	U8 syskeyEvent = EVENT_KEY_NONE;

	if_Key_Scan();
	/* Get the key event, then clear */
	syskeyEvent = if_Key_GetEvent();
	if_Key_ClearEvent();

	sysAdjustTime(syskeyEvent);
}

/*
 * main
 */
void main(void)
{
	/* InitializationMCU */
	initMCU();

	/* main loop */
	while (1)
	{
		/* Feed the watchdog */
		//drv_Watchdog_FeedDog();
		switch (stSys)
		{
		case SYS_INIT:
			sys_Init();
			//drv_stepper_moveDegreesCW(90);
			stSys = SYS_NORMAL;
			break;
		case SYS_NORMAL:
			if (TRUE == sys_IsFeedingTime())
			{
				//drv_stepper_moveDegreesCW(90);

				sys_Feeding();
				stSys = SYS_FEEDING;
			}
			break;
		case SYS_FEEDING:
			if (TRUE == sys_IsFeedComplete())
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

		App_Task_Disp(); /* Display task */
	}
}
/* End of file */
