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
 * File Name    : if_serial_ae1.h
 * Abstract     : serial interface for AE1-L header file.
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
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
#ifndef __IF_SERIAL_AE1_H__
#define __IF_SERIAL_AE1_H__
/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "driver_csi0.h"

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
/* **** Frame size definition**** */
//#define iPodIsUsed
#ifndef iPodIsUsed
#define TX_FRM_SIZE                   33/* ID = 50H */
#define RX_FRM_SIZE                   141/* ID = B1H£¬
                                           NOTE£º PLEASE DEFINE THIS PARAMETER CAREFULLY.
                                                 THIS PARAMETER MAYBE INFLUENCED BY PARAMETER
                                                 CMD(50H)-CDB[22~23]. */
#else
#define TX_FRM_SIZE                   520/* ID = 1FH */
#define RX_FRM_SIZE                   520/* ID = 9FH */
#endif

/* **** ACK & NACK code definition**** */
#define ACK                           (U8)0x00 /* OK, normal reception */
#define NACK_UNDEF_CMD                (U8)0x80 /* Undefined command */
#define NACK_INVALID_PARAMETER        (U8)0x81 /* Invalid parameter */
#define NACK_CHECKSUM_ERR             (U8)0x82 /* Checksum error */
#define NACK_RXED_BYTE_COUNT_ERR      (U8)0x83 /* Received byte count error */
#define NACK_NON_EXE_STATE_ERR        (U8)0x84 /* Non-executable state error */

/* **** AE1-L communication state definition **** */
typedef enum
{
	AE1_IF_IDLE = 0,
	INIT_CSI_IF,
	WAIT_AE1_BOOTUP,
	WAIT_COM,
	BEGIN_CMD_TX,
	RX_HEADER,
	RX_BODY,
	WAIT_HOST_TX_RESPONSE,
	WAIT_RTS_LOW,
	START_HOST_TX_RESPONSE,
	STS_WAIT_FRM_INTERVAL,
	STS_RECEPTION_OVER,
	HOST_TXING_RESPONSE,
	HOST_WAIT_RTS_HIGH_ACK,
	WAIT_HOST_TX_RESPONSE_COMPLETE,
	HOST_TXING_COMMAND,
	HOST_WAIT_RTS_HIGH_CMD,
	WAIT_HOST_TX_COMMAND_COMPLETE,
	WAIT_RX_RESPONSE,
	RXING_RESPONSE,
	WAIT_RX_RESPONSE_COMPLETE,
	CMD_WAIT_FRM_INTERVAL,
	TX_CMD_OVER,
	RX_STS_FOR_CONTENTION,/* Host receive STS after contention */
	WAIT_TX_FOR_CONTENTION,/* Host wait for re-transmit after contention */
	COM_ERROR
} e_ae1ComState;

typedef struct
{
	/* U8 Direction:1;
	 U8 Counter:7; */
	U8 Counter;
	U8 Identify;
	U8 LinkBit :1;
	U8 Reserved :7;
	U16 ParaSize;
	U16 FrameSize;
	U8 Status;
} typeCmdHeader;

/* ==== 2nd-level section definition ==== */
/* ---- 3rd-level section comment ---- */
/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/
/* *** exported variable *** */
/* AE1-L communication control guard timer for every sub-state */
extern U16 U16gAE1CtrlGuardTimer;

/* AE1-L communication control state machine state flag */
extern e_ae1ComState EgCSI0ComState;

/* common buffer for AE1 communication: receive & transmit */
extern U8 U8AE1ComRxBuf[];
extern U8 U8AE1ComTxBuf[];

/* decide to send command when value is TRUE
 * if command to AE1-L is saved to U8AE1ComBuf[] buffer then set this flag == TRUE */
extern BOOLEAN Bgcsi0BeginTX;

/* response value that host need return, after received status frame */
extern U8 U8ae1lResponse;/* response to AE1-L */

/* *** exported functions *** */
/* Calculate the check sum */
extern U8 CheckSum8(const U8 * pData, U16 Length);

/* clear guard timer */
extern void StartGuardTimer(U16* guardTimer);

/* check guard timer time out */
extern BOOLEAN IsGuardTmrTimeout(U16 guardTimer, U16 timeOutValue);

/* Communication task */
extern void IF_AE1Ctrl_ComPro(void);
/*****************************************************************************
 Private variables and functions
 *****************************************************************************/

#endif
/* End of File */
