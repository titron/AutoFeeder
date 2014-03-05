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
 * File Name    : driver_csi0.h
 * Abstract     : driver of R8C2A/2B csi2 module
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
#ifndef __DRV_CSI1_H__
#define __DRV_CSI1_H__
/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "basictype.h"
#include "sfr_r82b.h"

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
/* Flash communication bit rate */
#define FLASH_COMM_BITRATE				(U16)50000

/* Port definition */
#define SCI1_CS_ASSERT()				(p6_0 = 0)
#define SCI1_CS_DEASSERT()				(p6_0 = 1)
#define Drv_CSI1_GetReceivesData()		(u2rb)
#define Drv_CSI1_SendData(U8Data)		(u2tb = U8Data)

#define CSI1_TX_INT_ENABLE()		  	(s2tic = 0x01)
#define CSI1_TX_INT_DISABLE()	      	(s2tic = 0x00)
#define CSI1_RX_INT_ENABLE()		  	(s2ric = 0x05)
#define CSI1_RX_INT_DISABLE()         	(s2ric = 0x00)

/* Transmit Buffer Empty */
#define CSI1_TX_SHIFT_NOT_EMPTY			0
#define CSI1_TX_SHIFT_EMPTY				1
#define CSI1_TX_BUFFER_NOT_EMPTY		0
#define CSI1_TX_BUFFER_EMPTY			1
#define CSI1_RX_BUFFER_NOT_FULL			0
#define CSI1_RX_BUFFER_FULL				1
#define DRV_CSI1_IS_TX_COMPLETE()		txept_u2c0
#define DRV_CSI1_IS_TX_BUFFER_EMPTY()	ti_u2c1
#define DRV_CSI1_IS_RX_BUFFER_FULL()	ri_u2c1
#define DRV_CSI1_RX_ENABLE()		    (u2c1 |= 0x04)
#define DRV_CSI1_RX_DISABLE()           (u2c1 &= 0xFB)
#define CONTINOUS_REC_ENABLE()        	(u2c1 |= 0x20)
#define CONTINOUS_REC_DISABLE()        	(u2c1 &= 0xDF)

/* If use Clock Synchronous Serial, one port is used as CS.
 * If use real SPI, please comment the next 1 line. */
#define PORT_CS_BY_SOFTWARE

/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/
extern U8 drv_CSI1_Init(U16 U16CSI1baudRateIn100bps);
extern BOOLEAN drv_CSI1_Transmit(U8* pTXBuf, U16 TXLength);
extern BOOLEAN drv_CSI1_Receive(U8* pRXBuf, U16 RXLength);
#endif
/* End of File */
