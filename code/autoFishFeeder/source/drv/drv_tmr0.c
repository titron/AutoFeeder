/*
 * .c
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */

/*
 * Includes
 */
#include "sfr_r82b.h"
#include "basictype.h"
#include "main.h"
#include "if_key.h"

/*
 * Typedef
 */

/*
 * Macro
 */
/* timer clock definition when high-speed OCO */
#define F2_CLK_HIGHSPEED         (U32)10000000
#define TMRA_UNIT_HIGHSPEED       (U8)(100 - 1)	/* trapre's value */
#define TMRA_INTERVAL_HIGHSPEED   (U8)(((F2_CLK_HIGHSPEED/(U32)1000)/(TMRA_UNIT_HIGHSPEED+(U32)1)) - (U32)1)/* f2 is as count source */

/* timer clock definition when low-speed OCO */
#define F1_CLK_LOWSPEED 		(U32)125000
#define TMRA_UNIT_LOWSPEED       (U8)(25 - 1)	/* trapre's value */
#define TMRA_INTERVAL_LOWSPEED   (U8)(((F1_CLK_LOWSPEED/(U32)40)/(TMRA_UNIT_LOWSPEED+(U32)1)) - (U32)1)/* f1 is as count source */

/* SFR Bit value definition */
#define STOP    0
#define START   1
#define TIMER_MODE               (U8)0x00
#define TMRRA_COUNT_SOURCE_F1    (U8)0x00
#define TMRRA_COUNT_SOURCE_F8    (U8)0x01
#define TMRRA_COUNT_SOURCE_FOCO  (U8)0x02
#define TMRRA_COUNT_SOURCE_F2    (U8)0x03
#define TMRRA_COUNT_SOURCE_F32   (U8)0x04
#define TMRRA_INT_PRIORITY       (U8)0x01

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */
U32 CurrentTimer = 0;

/*
 * Private variables and functions
 */

/*
 * drv_Tmr0_InitTmr0InHighSpeed
 * TimerRA is as system timer, in 1ms interval, f2=10MHz
 */
void drv_Tmr0_InitTmr0InHighSpeed(void)
{
	/* Drv_INT_DisableInterrupt(); *//* Disable interrupt */
	/* Set 1ms interval */
	tstart_tracr = STOP;
	tramr = (U8) (TMRRA_COUNT_SOURCE_F2 << 4) + TIMER_MODE;
	trapre = (U8) TMRA_UNIT_HIGHSPEED;
	tra = TMRA_INTERVAL_HIGHSPEED;
	traic = TMRRA_INT_PRIORITY;
	tstart_tracr = START;
	/* Drv_INT_EnableInterrupt(); *//* Enable interrupt */
}

/*
 * drv_Tmr0_InitTmr0InLowSpeed
 * TimerRA is as system timer, in 100ms interval, f1=125KHz
 */
void drv_Tmr0_InitTmr0InLowSpeed(void)
{
	/* Drv_INT_DisableInterrupt(); *//* Disable interrupt */
	/* Set 10ms interval */
	tstart_tracr = STOP;
	tramr = (U8) (TMRRA_COUNT_SOURCE_F1 << 4) + TIMER_MODE;
	trapre = (U8) TMRA_UNIT_LOWSPEED;
	tra = TMRA_INTERVAL_LOWSPEED;
	traic = TMRRA_INT_PRIORITY;
	tstart_tracr = START;
	/* Drv_INT_EnableInterrupt(); *//* Enable interrupt */
}

/*
 * TmrRAInt
 * 1ms delay.
 */
void TmrRAInt(void)
{
	/*CurrentTimer*/
	CurrentTimer++;

	/* Timer counter of scan key */
	U16TimerCountScanKey++;

	/* Timer counter of some 1 key during pressed period */
	U16TimerCountPressedKey++;
	/* system timer */
	vsysFeedTime++;
	vsysMilSecond++;
	if (1000 == vsysMilSecond)
	{
		p8_2 = ~p8_2;
		vsysSecond++;
		vsysMilSecond = 0;

		if (60 == vsysSecond)
		{
			vsysMinute++;
			vsysSecond = 0;

			if (60 == vsysMinute)
			{
				vsysHour++;
				vsysMinute = 0;

				if (24 == vsysHour)
				{
					vsysHour = 0;
				}
			}
		}
	}
}

/* End of file */
