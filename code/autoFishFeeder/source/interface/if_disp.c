/*
 * if_disp.c
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */

/*
 * Includes
 */
#include "drv_oled.h"
#include "drv_pwr.h"
#include "if_disp.h"

/*
 * Typedef
 */

/*
 * Macro
 */

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */

/*
 * Private variables and functions
 */
U8 DispCurLine;

void if_Disp_Init(void)
{
	/*Enable 12V for oled*/
	drv_Pwr_12V_TurnOn();
	drv_OLED_Init();
}

#if 0
void ScreenRollTimer(void)
{

	if(DispRollupdown == 1U)
	{
		DispCurLine+=1U;
		DispCurLine&=0x7fU;
		DispDownLine--;
		if (DispDownLine==0U)
		{
			If_Timer1_Stop();
			DispRollEnd = DISP_ROLL_END;
		}
	}
	else
	{
		DispCurLine-=1U;
		DispCurLine&=0x7fU;
		DispDownLine--;
		if (DispDownLine==0U)
		{
			If_Timer1_Stop();
			DispRollEnd = DISP_ROLL_END;
		}
	}
	Drv_OLED_SetStartLine(DispCurLine);

}
#endif

void if_Disp_SetStartLine(U8 line)
{
	DispCurLine = line;
	drv_OLED_SetStartLine(DispCurLine);

}

#if 0
void if_Disp_SetRoll(U8 upline,U8 downline,U8 downup,U16 interva_ms)
{
	U32 Rolltimer;
	if((DispRollEnd == DISP_ROLL_ING))
	{
		if_Disp_RollEnd();
	}
	DispUpLine = 0U;
	DispDownLine += downline;
	DispRollupdown = downup;

	Rolltimer = (U32)(interva_ms)*1000U;
	Rolltimer = Rolltimer/DispDownLine;

	if_Timer1Init(Rolltimer,ScreenRollTimer);
	DispRollEnd = DISP_ROLL_ING;
}

void if_Disp_RollEnd(void)
{
	if_Timer1_Stop();
	if(DispRollupdown == 1U)
	{
		DispCurLine+=DispDownLine;
		DispCurLine&=0x7fU;
	}
	else
	{
		DispCurLine-=DispDownLine;
		DispCurLine&=0x7fU;
	}
	DispDownLine = 0U;
	Drv_OLED_SetStartLine(DispCurLine);
	DispRollEnd = DISP_ROLL_END;
}
#endif
/* End of file */
