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
 * File Name    : drv_clk.c
 * Abstract     : clock module
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AutoFeeder module
 * Description  : clock module
 * Operation    : none
 * Limitation   : none
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "basictype.h"
#include "config.h"
#include "sfr_r82b.h"
#include "drv_clk.h"

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Macro definitions
 *****************************************************************************/

/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/

/*****************************************************************************
 Private variables and functions
 *****************************************************************************/

/*****************************************************************************
 * ID                :
 * Outline           : MCU clock select low-speed on-chip oscillator
 * Include           : none
 * Declaration       : void drv_Clk_SelectLowSpeedOCO(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void drv_Clk_SelectLowSpeedOCO(void)
{
	/* Drv_INT_DisableInterrupt(); */		/* Disable interrupt */

	/* protection OFF */
	prc0 = PRC0_PROTECT_OFF;

	/* System clock division select 8-divided in low-speed OCO mode */
	cm06 = CM06_DIVISION_BY_8;
	ocd0 = OCD0_OSC_STOP_DETECT_DISABLE;
    ocd1 = OCD1_OSC_STOP_DETECT_INT_DISABLE;

	/* Switch CPU clock to low-speed on-chip ocillator */
	fra01 = FRA01_SELECT_LOW_SPEED_ONCHIP_OSC;
	ocd2 = OCD2_SYS_CLOCK_SELECT_ON_CHIP;
	/* Stop XIN clock */
	cm05 = CM05_XIN_STOP;
	/* Stop high-speed on-chip oscillator */
	fra00 = FRA00_HIGH_SPEED_OSC_OFF;
	/* protection ON */
	prc0 = PRC0_PROTECT_ON;

	/* Drv_INT_EnableInterrupt(); */		/* Enable interrupt */
}

/*****************************************************************************
 * ID                :
 * Outline           : MCU clock select low-speed on-chip oscillator
 * Include           : none
 * Declaration       : void drv_Clk_SelectHighSpeedOCO(void)
 * Description       :
 * Argument          :
 * Return Value      :
 * Calling Functions :
 *****************************************************************************/
void drv_Clk_SelectHighSpeedOCO(void)
{
	U8 waitOscStable = 0U;
	/* Drv_INT_DisableInterrupt(); */		/* Disable interrupt */

	/* protection OFF */
	prc0 = PRC0_PROTECT_OFF;
#if SYSTEM_CLOCK_SELECT == SYSTEM_CLOCK_IS_XIN_DIV_BY_1
	cm06 = CM06_DIVISION_BY_CM16CM17;/* System clock division select */
	cm1 |= (CM16_17_SYE_CLK_DIVISION_BY_NONE << ((U8)6));
#elif SYSTEM_CLOCK_SELECT == SYSTEM_CLOCK_IS_XIN_DIV_BY_2
	cm06 = CM06_DIVISION_BY_CM16CM17;/* System clock division select */
	cm1 |= (CM16_17_SYE_CLK_DIVISION_BY_2 << (U8)6);
#elif SYSTEM_CLOCK_SELECT == SYSTEM_CLOCK_IS_XIN_DIV_BY_4
	cm06 = CM06_DIVISION_BY_CM16CM17;/* System clock division select */
	cm1 |= (CM16_17_SYE_CLK_DIVISION_BY_4 << (U8)6);
#elif SYSTEM_CLOCK_SELECT == SYSTEM_CLOCK_IS_XIN_DIV_BY_8
	cm06 = CM06_DIVISION_BY_8;/* System clock division select */
#elif SYSTEM_CLOCK_SELECT == SYSTEM_CLOCK_IS_XIN_DIV_BY_16
	cm06 = CM06_DIVISION_BY_CM16CM17;/* System clock division select */
	cm1 |= (CM16_17_SYE_CLK_DIVISION_BY_16 << (U8)6);
#endif
	ocd0 = OCD0_OSC_STOP_DETECT_DISABLE;
    ocd1 = OCD1_OSC_STOP_DETECT_INT_DISABLE;
	/* Start high-speed on-chip oscillator */
	fra00 = FRA00_HIGH_SPEED_OSC_ON;
	/* Wait oscillator stable */
	while (waitOscStable < OSC_STABLE_TIME) {
		waitOscStable++;
	}
	/* Switch CPU clock to high-speed on-chip ocillator */
	fra01 = FRA01_SELECT_HIGH_SPEED_ONCHIP_OSC;
	ocd2 = OCD2_SYS_CLOCK_SELECT_ON_CHIP;
	/* Stop XIN clock */
	cm05 = CM05_XIN_STOP;
	/* Note: When high-speed is on, low-speed on-chip cannot stop. */
	/* protection ON */
	prc0 = PRC0_PROTECT_ON;

	/* Drv_INT_EnableInterrupt(); */		/* Enable interrupt */
}
/* End of file */
