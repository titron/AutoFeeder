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
/******************************************************************************
* System Name	: AE1-LF Car Audio Demo
* File Name 	: if_disp.c
* Abstract 		: interface of disp
* Version 		: Ver 0.10
* Device 		: R8C/2A group, or R8C/2B group, or 78K0 group
* Tool-Chain 	: High-performance Embedded Workshop (Version 4.08.00.011)
* 				: C Compiler Package for M16C Series M3T-NC30WA(V.5.45 Release 00)
* OS 			: None
* H/W Platform 	: AE1-LF demo board
* Description 	: This is interface of disp.
* Operation 	: 
* Limitation 	: This program can be operated by 20MHz only.
*******************************************************************************
* History 		: Dec.16,2010 Ver. 0.10 First Release
* 				:
*******************************************************************************/

/*****************************************************************************
Includes   <System Includes> , "Project Includes"
*****************************************************************************/
#include "driver_oled.h"
#include "driver_power.h"
#include "if_timer.h"
#include "if_disp.h"

/*****************************************************************************
Macro definitions
*****************************************************************************/

/*****************************************************************************
Private variables and functions
*****************************************************************************/

/*****************************************************************************
* ID                : 
* Outline           : init led
* Include           : none
* Declaration       : StdRetType If_EV_SetVolume((U8)U8Volume)
* Description       : Disp
* Argument          : 
* Return Value      : Standard Error code, ERROR1 means I2C bus busy
* Calling Functions :
*****************************************************************************/
void If_Disp_Init( void )
{
	/*Enable 12V for oled*/
	drv_Power_12V_TurnOn();

	Drv_OLED_Init();

}
#if 0
void If_Disp_PowerDown( void )
{
	//Disable 12V 
	Drv_Power_TurnOff();
}
#endif

U8 DispUpLine,DispDownLine,DispCurLine,DispRollupdown,DispRollStep,DispRollEnd;
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
	}else
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

void If_Disp_SetStartLine(U8 line)
{
	DispCurLine = line;
	Drv_OLED_SetStartLine(DispCurLine);

}

void If_Disp_SetRoll(U8 upline,U8 downline,U8 downup,U16 interva_ms)
{
	U32 Rolltimer;
	if((DispRollEnd == DISP_ROLL_ING))
	{
		If_Disp_RollEnd();
	}
	DispUpLine = 0U;
	DispDownLine += downline;
	DispRollupdown = downup;

	Rolltimer = (U32)(interva_ms)*1000U;
	Rolltimer = Rolltimer/DispDownLine;

	If_Timer1Init(Rolltimer,ScreenRollTimer);
	DispRollEnd = DISP_ROLL_ING;
}

void If_Disp_RollEnd(void)
{
	If_Timer1_Stop();
	if(DispRollupdown == 1U)
	{
		DispCurLine+=DispDownLine;
		DispCurLine&=0x7fU;
	}else
	{
		DispCurLine-=DispDownLine;
		DispCurLine&=0x7fU;
	}
	DispDownLine = 0U;
	Drv_OLED_SetStartLine(DispCurLine);
	DispRollEnd = DISP_ROLL_END;
}


