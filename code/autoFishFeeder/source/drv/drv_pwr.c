/*
 * drv_pwr.c
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */

/*
 * Includes
 */
#include "BasicType.h"
#include "sfr_r82b.h"
#include "drv_pwr.h"

/*
 * Typedef
 */

/*
 * Macro
 */
#define PORT_POWER_12V_CTRL				p6_1
#define PORT_DIRECTION_POWER_12V_CTRL	pd6_1
#define PORT_POWER_5V_CTRL				p3_3
#define PORT_DIRECTION_POWER_5V_CTRL	pd3_3
#define PORT_POWER_3P3V_CTRL			p6_2
#define PORT_DIRECTION_POWER_3P3V_CTRL	pd6_2

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */

/*
 * Private variables and functions
 */

void drv_Pwr_InitPwrCtrlPort(void)
{
	PORT_POWER_12V_CTRL = LOW;
	PORT_DIRECTION_POWER_12V_CTRL = 1; /* Direction output */
	PORT_POWER_12V_CTRL = LOW;

	PORT_POWER_5V_CTRL = LOW;
	PORT_DIRECTION_POWER_5V_CTRL = 1; /* Direction output */
	PORT_POWER_5V_CTRL = LOW;

	PORT_POWER_3P3V_CTRL = HIGH;
	PORT_DIRECTION_POWER_3P3V_CTRL = 1; /* Direction output */
	PORT_POWER_3P3V_CTRL = HIGH;
}

void drv_Pwr_12V_TurnOff(void)
{
	PORT_POWER_12V_CTRL = LOW;
}

void drv_Pwr_5V_TurnOff(void)
{
	PORT_POWER_5V_CTRL = LOW;
}

void drv_Pwr_3P3V_TurnOff(void)
{
	PORT_POWER_3P3V_CTRL = HIGH;
}

void drv_Pwr_12V_TurnOn(void)
{
	PORT_POWER_12V_CTRL = HIGH;
}

void drv_Pwr_5V_TurnOn(void)
{
	PORT_POWER_5V_CTRL = HIGH;
}

void drv_Pwr_3P3V_TurnOn(void)
{
	PORT_POWER_3P3V_CTRL = LOW;
}

void drv_Pwr_SetPortForLowPower(void)
{
	/* P0 - key input, not change */
	/* Note:
	 1. Do not remove the internal pull-up from key1-key6 and key of rotary1/2
	 because key scan will used these state!!!
	 */

	/* P1 */
	/* Note: 1. p1_0 is reset-.
	 2. p1_4 is TXD0, p1_5 is RXD0, and p1_6 is CLK0
	 */
	smd0_u0mr = 0; /* p1_4, p1_5, P1_6 as GPIO */
	smd1_u0mr = 0;
	smd2_u0mr = 0;
	p1 = 0x00;
	pd1 = 0xFF;
	p1 = 0x00;

	/* P2 */
	p2 = 0x00;
	pd2 = 0xFF;
	p2 = 0x00;

	/* P3 */
	/* Note:
	 1. p3_0, p3_1, p3_2 and p3_6 are encoder phase port
	 2. p3_3 is 5V power control, 5V is power off when p3_3 is low
	 3. p3_4 and p3_5 are iic port
	 4. p3_7 is reset+ port
	 */
	pu06 = 0; /* p3_0 to p3_3 are not internally pulled-up */
	pu07 = 0; /* p3_4 to p3_7 are not internally pulled-up */
	int2en = 0; /* p3_2 disable the external INT2 */
	ice_iccr1 = 0; /* p3_4, p3_5 - iic is halted */
	int1en = 0; /* p3_6 disable the external INT1 */
	p3 = 0x00;
	pd3 = 0xFF;
	p3 = 0x00;

	/* P4 */
	/* Note:
	 1. p4_0 to p4_2 are unavailable, only can set 0b.
	 2. pd4_0 to pd4_2, pd4_6 to pd4_7 are unavailable, only can set 0b(input mode).
	 */
	p4 = 0x00;
	pd4 = 0x38;
	p4 = 0x00;

	/* P5 */
	/* Note:
	 1. p5_5 to p5_7 are reserved, only can set 0b.
	 2. pd5_5 to pd5_7 are reserved, only can set 0b(input mode).
	 */
	p5 = 0x00;
	pd5 = 0x1f;
	p5 = 0x00;

	/* P6 */
	/* Note:
	 1. p6_1 is 12V power control, 12V is power off when low
	 2. p6_2 is 3.3V power control, 3.3V is power off when high!!!
	 3. p6_3 is TXD2, p6_4 is RXD2, and p6_5 is CLK2
	 */
	smd0_u2mr = 0; /* p6_3, p6_4, p6_5 as GPIO */
	smd1_u2mr = 0;
	smd2_u2mr = 0;
	p6 = 0x04;
	pd6 = 0xff;
	p6 = 0x04;

	/* P8 */
	/* Note:
	 1. p8_7 is reserved, only can set 0b.
	 2. pd8_7 is reserved, only can set 0b.
	 */
	p8 = 0x00;
	pd8 = 0x7f;
	p8 = 0x00;
}

void drv_Pwr_InitPwrCtrl(void)
{
	/* Initialize the power control */
	drv_Pwr_InitPwrCtrlPort();

	/* Power is supplied for peripheral module */
	drv_Pwr_12V_TurnOff();
	drv_Pwr_5V_TurnOff();
	drv_Pwr_3P3V_TurnOff();
}

void drv_Power_TurnOn(void)
{
//	Drv_Power_5V_TurnOn();
	drv_Pwr_5V_TurnOff();
	drv_Pwr_3P3V_TurnOn();
}
/* End of File */
