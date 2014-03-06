/*
 * drv_oled_port.h
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */
#ifndef __DRIVER_OLED_PIN_H__
#define __DRIVER_OLED_PIN_H__
/*
 * Includes
 */
#include "basictype.h"

/*
 * Typedef
 */

/*
 * Macro
 */
#define VERSION_2

#ifdef VERSION_2
#define OLED_CS				p5_0		/*Chip Select*/
#define OLED_DC				p5_1		/*Data/Command Control*/
#define OLED_ENABLE			p5_3		/*Read/Write Enable*/
#define OLED_RW   			p5_2		/*Read/Write Select*/
#define OLED_RD 			p5_3			/*Read Signal*/
#define OLED_WR				p5_2		/*Write Signal*/
#define OLED_POWER      	p6_1		/*12V OLED POWER*/
#define OLED_DATA			p2			/*Data bus*/

#define OLED_RESST_D		pd3_7		/*Reset*/
#define OLED_CS_D			pd5_0			/*Chip Select*/
#define OLED_DC_D			pd5_1			/*Data/Command Control*/
#define OLED_ENABLE_D		pd5_3			/*Read/Write Enable*/
#define OLED_RW_D   		pd5_2			/*Read/Write Select*/
#define OLED_RD_D 			pd5_3			/*Read Signal*/
#define OLED_WR_D			pd5_2			/*Write Signal*/
#define OLDE_POWER_D		p6_1		

#define OLED_DATA_D			pd2				/*Data bus*/
#endif

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */

/*
 * Private variables and functions
 */
#endif
/* End of File */
