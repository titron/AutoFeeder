/*
 * drv_clk.c
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */

/*
 * Includes
 */
#include "basictype.h"
#include "config.h"
#include "sfr_r82b.h"
#include "drv_clk.h"

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

/*
 * drv_Clk_SelectLowSpeedOCO
 */
void drv_Clk_SelectLowSpeedOCO(void)
{
	/* Drv_INT_DisableInterrupt(); *//* Disable interrupt */

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

	/* Drv_INT_EnableInterrupt(); *//* Enable interrupt */
}

/*
 * drv_Clk_SelectHighSpeedOCO
 */
void drv_Clk_SelectHighSpeedOCO(void)
{
	U8 waitOscStable = 0U;
	/* Drv_INT_DisableInterrupt(); *//* Disable interrupt */

	/* protection OFF */
	prc0 = PRC0_PROTECT_OFF;
#if SYSTEM_CLOCK_SELECT == SYSTEM_CLOCK_IS_XIN_DIV_BY_1
	cm06 = CM06_DIVISION_BY_CM16CM17;/* System clock division select */
	cm1 |= (CM16_17_SYE_CLK_DIVISION_BY_NONE << ((U8) 6));
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
	while (waitOscStable < OSC_STABLE_TIME )
	{
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

	/* Drv_INT_EnableInterrupt(); *//* Enable interrupt */
}
/* End of file */
