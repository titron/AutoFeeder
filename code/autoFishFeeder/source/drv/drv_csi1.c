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
 * System Name  : AE1-LF Car Audio Demo
 * File Name    : driver_csi1.c
 * Abstract     : driver of R8C2A/2B csi2 module(used by flash communication)
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AE1-LF demo board
 * Description  : This is driver of clock synchronous interface 2 which is used
                : in flash communication. A point need be mentioned, CSI replace
                : the SPI communication of flash, and CS pin use one GPIO by 
                : software.
 * Operation    : none
 * Limitation   : This file can be only used as sample code for AE1-LF.
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "sfr_r82b.h"
#include "drv_csi1.h"
#include "drv_flash.h"

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
/* **** baud rate related definition**** */
#define BAUDRATE_UNIT                 (U8)100
#define SIO_CLK                       (U32)20000000

/* **** SFR definition**** */
#define SFR_SIOCTRL0		          u2c0
#define SFR_SIOCTRL1		          u2c1
#define SFR_SIOBRG 			          u2brg
#define SFR_SIOMODE			          u2mr
#define SFR_SIORXBUF		          u2rb
#define SFR_SIOTXBUF		          u2tbl

/* **** SFR value definition**** */
#define TX_ENABLE()		              (SFR_SIOCTRL1 |= 0x01)
#define TX_DISABLE()	              (SFR_SIOCTRL1 &= 0xFE)
/* #define RX_ENABLE()		          SFR_SIOCTRL1 |= 0x04 */
/* #define RX_DISABLE()               SFR_SIOCTRL1 &= 0xFB */
#define INTCAUSE_TX_BUF_EMPTY()       (SFR_SIOCTRL1 &= 0xEF)
#define INTCAUSE_TX_COMPLETE()        (SFR_SIOCTRL1 |= 0x10)

/* **** Bit value definition**** */
#define CLK01_BRG_SOURCE_SELECT_F1    (U8)0x00
#define CLK01_BRG_SOURCE_SELECT_F8    (U8)0x01
#define CLK01_BRG_SOURCE_SELECT_F32   (U8)0x02
#define NCH_TXD_CMOS_OUTPUT           (U8)0x00
#define NCH_TXD_N_CH_OPENDRAIN_OUTPUT (U8)0x20
#define CLK_POLARITY_TX_FALLING_RX_RISING	(U8)0x00
#define CLK_POLARITY_TX_RISING_RX_FALLING	(U8)0x40
#define TX_SEQUENCE_LSB_FIRST		  (U8)0x00
#define TX_SEQUENCE_MSB_FIRST		  (U8)0x80

#define SMD_CLK_SYN_MODE              (U8)0x01
#define CKDIR_INTERNAL_CLK            (U8)0x00
#define CKDIR_EXTERNAL_CLK            (U8)0x08
#define NO_DATA_IN_UiTB               (U8)0x02
#define NO_DATA_IN_TX_SHIFT_SFR       (U8)0x08

/* **** Port definition**** */
#define	RX_PORT_SET()             	  (pd6_4 = 0)
#define	CLK_PORT_SET()    			  (u1sr = 0x00)
#define CS_PORT_SET()				  (pd6_0 = 1)

/*****************************************************************************
 Private variables and functions
 *****************************************************************************/
U16 U16CSI1BufCount;
U8* pU8CSI1Buf;

/*****************************************************************************
 * ID                : 1.0
 * Outline           : Initialize the clock synchronous interface
 * Include           : none
 * Declaration       : U8 Drv_CSI1_Init(U16 U16CSI1baudRateIn100bps)
 * Description       : Initialize the clock synchronous interface
 * Argument          : baudRateIn100bps
 *                   : baud rate value, unit: 100bps
 *                   : (range [from 3930 to 50000] -> [39.3Kbps ~ 5Mbps])
 * Return Value      : DONE --- settings is OK.
 *                   : Error1 --- parameter error
 * Calling Functions : none
 *****************************************************************************/
U8 drv_CSI1_Init(U16 U16CSI1baudRateIn100bps)
{
	U32 brpSet;

	/* Define port */
	RX_PORT_SET();
	CLK_PORT_SET();
	CS_PORT_SET();
	SCI1_CS_DEASSERT();

	/* Disable TX/RX and interrupt */
	CSI1_TX_INT_DISABLE();
	CSI1_RX_INT_DISABLE();
	TX_DISABLE();
	DRV_CSI1_RX_DISABLE();

	if (U16CSI1baudRateIn100bps == (U16) 0) {
		return ERROR1;
	}
	else {
		/* if parameter is correct then continue */
	}

	brpSet = ((((U32) SIO_CLK / (U32)2) / BAUDRATE_UNIT) / U16CSI1baudRateIn100bps) - (U32)1;
	if (brpSet >= (U32) 256) {
		/* BRG over range */
		return ERROR1;
	}
	else {
		/* Define the speed */
		SFR_SIOCTRL0 = CLK01_BRG_SOURCE_SELECT_F1|NCH_TXD_CMOS_OUTPUT|  \
			CLK_POLARITY_TX_FALLING_RX_RISING| TX_SEQUENCE_MSB_FIRST;
		SFR_SIOBRG = (U8) brpSet;
	}

	/* Define data format */
	SFR_SIOMODE = SMD_CLK_SYN_MODE|CKDIR_INTERNAL_CLK;

	/* transmit interrupt cause select */
	INTCAUSE_TX_BUF_EMPTY();

	/* enable continous receive */
	/* CONTINOUS_REC_ENABLE(); */

	/* Enable transmit and reception */
	TX_ENABLE();
	DRV_CSI1_RX_ENABLE();
	return DONE;
}
/* End of file */
