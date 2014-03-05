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
 * Abstract     : clock synchronous interface diver header file for AE1-LF.
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AE1-LF demo board
 * Description  : This is the header file of serial module (AE1-L).
 * Operation    : none
 * Limitation   : This file can be only used as sample code for AE1-LF.
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/
#ifndef __DRIVER_CSI0_H__
#define __DRIVER_CSI0_H__
/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "basictype.h"

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
/* **** Port definition**** */
#define RTS                           p8_5
#define CTS                           p8_6

/* **** Dummy data define **** */
#define DUMMY_DATA_FOR_RX             (U8)0xFF
/* ---- 3rd-level section comment ---- */

/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/
/* set reset AE1 pin high or low */
extern void Drv_ResetAE1(BOOLEAN resetPinState);

/* Initialize host interface */
extern StdRetType Drv_CSI0_Init(U16 baudRateIn100bps);

/* start CSI0 transmission */
extern BOOLEAN Drv_CSI0_Transmit(U8* pTXBuf, U16 TXLength);

/* CSI0 reception */
extern BOOLEAN Drv_CSI0_Receive(U8* pRXBuf, U16 RXLength);

/* get counter during communication */
extern U16 Drv_CSI0_GetComCounter(void);

/* Abort transmission */
extern void Drv_CSI0_AbortTransmit(void);

/* Abort reception */
extern void Drv_CSI0_AbortReceive(void);

/* CSI0 transmission interrupt service program */
extern void CSI0TransmitInt(void);

/* CSI0 reception interrupt service program */
extern void CSI0ReceiveInt(void);
/*****************************************************************************
 Private variables and functions
 *****************************************************************************/

#endif
/* End of File */
