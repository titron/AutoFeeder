/*
 * draw_task.c
 * Draw OLED is implemented in this file.
 *
 *  Created on: 3/6/2014
 *      Author: hawkdtw
 *       email: hawkdtw@gmail.com
 */

/*
 * Includes
 */
#include "draw_task.h"

#include <string.h>

#include "../../drv/basictype.h"
#include "../../drv/drv_tmr0.h"
#include "../../interface/if_disp.h"
#include "../../interface/if_oled_draw.h"
#include "../../interface/if_oled_text.h"

/*
 * Typedef
 */

/*
 * Macro
 */
/*Postion define*/
#define ORIGNAL_POS_X					15
#define ORIGNAL_POS_Y					0

#define BOTTOM_LINE_START_X    	     	0U
#define BOTTOM_LINE_START_Y         	17U
#define BOTTOM_LINE_END_X           	78U
#define BOTTOM_LINE_END_Y           	19U
#define BOTTOM_LINE_FILL            	1U
#define BOTTOM_LINE_FILL_GRAY       	2U
#define BOTTOM_LINE_BOX_FILL_GRAY   	8U

#define CURRENT_TIME_POS_X              (U16)208
#define CURRENT_TIME_POS_Y              (U16)0
#define FEED_TIME_POS_X		            (U16)80
#define FEED_TIME_POS_Y		            (U16)32
#define O2_TIME_POS_X		            (U16)208
#define O2_TIME_POS_Y		            (U16)32

#define FISH_BMP_POS_X 					0
#define FISH_BMP_POS_Y 					30

/*
 * Imported global variables and functions (from other files)
 */
extern u32 vsysHour;
extern u32 vsysMinute;
extern u32 vsysSecond;
extern u32 vsysFeedHour;
extern u32 vsysFeedMinute;
extern u32 vsysFeedSecond;
extern u32 vsysO2Hour;
extern u32 vsysO2Minute;
extern u32 vsysO2Second;

/*
 * Exported global variables and functions (to be accessed by other files)
 */

/*
 * Private variables and functions
 */
DISP_STATE DispState = DISP_INIT;
U32 DispWaitTM;
U8 DispName[] = "AutoFeeder";

/*
 * DecToStr
 * decimal -> string
 */
void DecToStr(U16 data, U8 *str, U8 bitwidth)
{
	switch (bitwidth)
	{
	case 5:
		str[0] = data / 10000 + '0';
		str[1] = (data % 10000) / 1000 + '0';
		str[2] = (data % 1000) / 100 + '0';
		str[3] = (data % 100) / 10 + '0';
		str[4] = data % 10 + '0';
		str[5] = 0;
		break;
	case 4:
		str[0] = data / 1000 + '0';
		str[1] = (data % 1000) / 100 + '0';
		str[2] = (data % 100) / 10 + '0';
		str[3] = data % 10 + '0';
		str[4] = 0;
		break;
	case 3:
		str[0] = data / 100 + '0';
		str[1] = (data % 100) / 10 + '0';
		str[2] = data % 10 + '0';
		str[3] = 0;
		break;
	case 2:
		str[0] = data / 10 + '0';
		str[1] = data % 10 + '0';
		str[2] = 0;
		break;
	case 1:
		str[0] = data % 10 + '0';
		str[1] = 0;
		break;
	default:
		str[0] = 0;
		break;
	}
}

/*
 * DecToStrSign
 * decimal -> signed string
 */
void DecToStrSign(S16 data, U8 *str, U8 bit)
{
	U16 U16temp;
	if (data < 0)
	{
		U16temp = 0 - data;
		str[0] = '-';
	}
	else
	{
		U16temp = data;
		str[0] = '+';
	}
	switch (bit)
	{
	case 4:
		str[1] = U16temp / 1000 + '0';
		str[2] = (U16temp % 1000) / 100 + '0';
		str[3] = (U16temp % 100) / 10 + '0';
		str[4] = U16temp % 10 + '0';
		str[5] = 0;
		break;
	case 3:
		str[1] = U16temp / 100 + '0';
		str[2] = (U16temp % 100) / 10 + '0';
		str[3] = U16temp % 10 + '0';
		str[4] = 0;
		break;
	case 2:
		str[1] = U16temp / 10 + '0';
		str[2] = U16temp % 10 + '0';
		str[3] = 0;
		break;
	case 1:
		str[1] = U16temp % 10 + '0';
		str[2] = 0;
		break;
	default:
		str[1] = 0;
		break;
	}
}

/*
 * Strformat2
 *
 */
void Strformat2(U8 *destbuf, U16 data1, U16 data2, U8 *str, U8 bit)
{
	U8 buf1[5];
	U8 buf2[5];
	memset(buf1, 0, sizeof(buf1));
	memset(buf2, 0, sizeof(buf2));

	DecToStr(data1, buf1, bit);
	strcpy(destbuf, buf1);
	strcat(destbuf, str);

	DecToStr(data2, buf2, bit);
	strcat(destbuf, buf2);
}

/*
 * Strformat3
 */
void Strformat3(U8 *destbuf, U16 data1, U16 data2, U16 data3, U8 *str, U8 bit)
{
	U8 buf1[5];
	U8 buf2[5];
	U8 buf3[5];
	memset(buf1, 0, sizeof(buf1));
	memset(buf2, 0, sizeof(buf2));

	DecToStr(data1, buf1, bit);
	strcpy(destbuf, buf1);
	strcat(destbuf, str);

	DecToStr(data2, buf2, bit);
	strcat(destbuf, buf2);
	strcat(destbuf, str);

	DecToStr(data3, buf3, bit);
	strcat(destbuf, buf3);
}

/*
 * updateTimerPaint
 */
void updateTimerPaint(U8 mode)
{
	U16 LineLegth;
	U8 buf[10];
	U16 second, minute, hour;
	U16 offset;

	/*draw current time*/
	hour = (U16) vsysHour;
	minute = (U16) vsysMinute;
	second = (U16) vsysSecond;
	memset(buf, 0, sizeof(buf));
	Strformat3(buf, hour, minute, second, ":", (U8) 2);
	OLED_TextA(buf, CURRENT_TIME_POS_X, CURRENT_TIME_POS_Y, FONT16);
	/*draw feeding time*/
	hour = (U16) vsysFeedHour;
	minute = (U16) vsysFeedMinute;
	second = (U16) vsysFeedSecond;
	memset(buf, 0, sizeof(buf));
	Strformat3(buf, hour, minute, second, ":", (U8) 2);
	OLED_TextA(buf, FEED_TIME_POS_X, FEED_TIME_POS_Y, FONT16);
	/*draw O2 time*/
	hour = (U16) vsysO2Hour;
	minute = (U16) vsysO2Minute;
	second = (U16) vsysO2Second;
	memset(buf, 0, sizeof(buf));
	Strformat3(buf, hour, minute, second, ":", (U8) 2);
	OLED_TextA(buf, O2_TIME_POS_X, O2_TIME_POS_Y, FONT16);
}

/*
 * App_Task_Disp
 */
void App_Task_Disp(void)
{
	switch (DispState)
	{
	case DISP_INIT:
		/*Wait for power up*/
		/*clear timer*/
		CurrentTimer = (U32) 0;
		DispWaitTM = CurrentTimer;
		/*switch to wait vcc12 mode*/
		DispState = DISP_WAIT_VCC12;
		break;
	case DISP_WAIT_VCC12:
		/*after reset oled, wait for 100ms ,then set 12v*/
		if (CurrentTimer > (DispWaitTM + (U32) TIME_100MS ))
		{
			if_Disp_Init();
			if_Disp_SetStartLine(DISP_SCREEN_START_LINE);

			OLED_TextA(DispName, ORIGNAL_POS_X, ORIGNAL_POS_Y, FONT16);
			updateTimerPaint(REDRAW);
			OLED_DrawBox(BOTTOM_LINE_START_X,
			BOTTOM_LINE_START_Y,
			BOTTOM_LINE_END_X,
			BOTTOM_LINE_END_Y,
			BOTTOM_LINE_FILL,
			BOTTOM_LINE_FILL_GRAY,
			BOTTOM_LINE_BOX_FILL_GRAY);
			OLED_DrawBmp(FISH_BMP_POS_X, FISH_BMP_POS_Y, BMP_FISH_NO);
			DispState = DISP_PLAY;
		}
		break;
	case DISP_PLAY:
		updateTimerPaint(REDRAW);
		break;
	default:
		break;
	}
}

/* End of file */
