/*
 * drv_clk.h
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */
#ifndef __DRV_CLOCK_H__
#define __DRV_CLOCK_H__
/*
 * Includes
 */

/*
 * Typedef
 */

/*
 * Macro
 */
/* CPU clock source definition */
#define CPU_CLOCK_LOW_SPEED_OCO					0
#define CPU_CLOCK_HIGH_SPEED_OCO				1
#define CPU_CLOCK_XIN							2
#define CPU_CLOCK_XCIN							3
#define CPU_CLOCK_SELECT						CPU_CLOCK_HIGH_SPEED_OCO

/* System clock definition */
#define SYSTEM_CLOCK_IS_XIN_DIV_BY_1            0
#define SYSTEM_CLOCK_IS_XIN_DIV_BY_2            1
#define SYSTEM_CLOCK_IS_XIN_DIV_BY_4            2
#define SYSTEM_CLOCK_IS_XIN_DIV_BY_8            3
#define SYSTEM_CLOCK_IS_XIN_DIV_BY_16           4
#define SYSTEM_CLOCK_SELECT                     SYSTEM_CLOCK_IS_XIN_DIV_BY_1

/* register bit value definition */
/* ==== CM0 register ==== */
#define CM02_PERIPHER_CLOCK_NOT_STOP         0
#define CM02_PERIPHER_CLOCK_STOP             1
#define CM05_XIN_OSCILLATE                   0
#define CM05_XIN_STOP                        1
#define CM06_DIVISION_BY_CM16CM17            0
#define CM06_DIVISION_BY_8                   1

/* ==== CM1 register ==== */
#define CM10_ALL_CLOCK_OPERATE               0
#define CM10_ALL_CLOCK_STOP                  1
#define CM13_PORT_FUNCTION_INPUT_PORT        0
#define CM13_PORT_FUNCTION_XIN_XOUT          1
#define CM14_LOW_SPEED_OSCILLATOR_ON         0
#define CM14_LOW_SPEED_OSCILLATOR_OFF        1
#define CM15_XIN_XOUT_DRIVE_CAPACITY_LOW     0
#define CM15_XIN_XOUT_DRIVE_CAPACITY_HIGH    1
#define CM16_17_SYE_CLK_DIVISION_BY_NONE     (U8)0x00
#define CM16_17_SYE_CLK_DIVISION_BY_2        (U8)0x01
#define CM16_17_SYE_CLK_DIVISION_BY_4        (U8)0x02
#define CM16_17_SYE_CLK_DIVISION_BY_16       (U8)0x03

/* ==== OCD register ==== */
#define OCD0_OSC_STOP_DETECT_DISABLE         0
#define OCD0_OSC_STOP_DETECT_ENABLE          1
#define OCD1_OSC_STOP_DETECT_INT_DISABLE     0
#define OCD1_OSC_STOP_DETECT_INT_ENABLE      1
#define OCD2_SYS_CLOCK_SELECT_XIN            0
#define OCD2_SYS_CLOCK_SELECT_ON_CHIP        1

/* ==== FRA0 register ==== */
#define FRA00_HIGH_SPEED_OSC_OFF             0
#define FRA00_HIGH_SPEED_OSC_ON              1
#define FRA01_SELECT_LOW_SPEED_ONCHIP_OSC    0
#define FRA01_SELECT_HIGH_SPEED_ONCHIP_OSC   1

/* clock stable time definition */
#define	OSC_STABLE_TIME 					 (U8)255/* clock stable time:
                                                   instruction time * 255 */
/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */

/*
 * Private variables and functions
 */
extern void drv_Clk_SelectLowSpeedOCO(void);
extern void drv_Clk_SelectHighSpeedOCO(void);

#endif
/* End of File */
