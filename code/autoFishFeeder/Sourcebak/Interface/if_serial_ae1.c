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
 * File Name    : if_serial_ae1.c
 * Abstract     : serial interface for AE1-L progam.
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AE1-LF demo board
 * Description  : Interface between application layer (service) and driver.
 * Operation    : none
 * Limitation   : This file can be only used as sample code for AE1-LF.
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "sfr_r82b.h"
#include "basictype.h"
#include "if_serial_ae1.h"
#include "mcu_depend.h"
#include "app_host.h"
#include "app_ae1.h"
#include "driver_int.h"
#include "service_general.h"
/*****************************************************************************
 Typedef definitions
 *****************************************************************************/
typedef enum{
	CONTENTION_IN_TX_RESPONSE = 0,
	CONTENTION_IN_TX_CMD,
	CONTENTION_INVALID,
}e_contentionSource_type;

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
/* common buffer for AE1 communication: receive & transmit */
U8 U8AE1ComRxBuf[RX_FRM_SIZE];
U8 U8AE1ComTxBuf[TX_FRM_SIZE];

/* There are 2 types process for contention
 * 1. Host Re-transmit after contention
 * 2. Host receive STS from AE1 */
#define HOST_RX_AFTER_CONTENTION      0
#define HOST_RE_TX_AFTER_CONTENTION   1
#ifdef FIRM_VER_080_USED
#define HANDLE_CONTENTION 			  HOST_RE_TX_AFTER_CONTENTION
#else
#define HANDLE_CONTENTION 			  HOST_RX_AFTER_CONTENTION
#endif

/* Wrong frame size process definition */
#define WRONG_FRM_SIZE_PROCESS

/* **** Error code definition**** */
#define BAUDRATE_SET_ERROR            (U8)0
#define COM_OVERTIME_ERROR            (U8)1
#define COM_CHECKSUM_ERROR            (U8)2
#define CMD_SIZE_ERROR                (U8)3

/* **** Frame size position from frame start **** */
#define FRM_SIZE_POSITION_IN_BYTES    (U16)7

/* **** ACK & NACK code definition**** */
#define DO_NOTHING                    (U8)0/* when received response is other than
                                              82H and 84H, then do nothing */
#define RE_TRANSMIT                   (U8)1/* when received response is
                                              82H and 84H, then re-transmit */

/* **** guard timer timeout value definition **** */
#define RESPONSE_SIZE_IN_BYTE         (U16)1/* response size, in byte */

/* **** guard timer timeout value definition **** */
/* It takes more than 5ms after set RESET to low, and change RESET pin to high */
#define GUARDTIME_RST_AE1_PERIOD      (U16)10

/* 20MS + serial flash read time passed */
#define GUARDTIME_AE1_BOOTUP          (U16)1000

/* tTO, unit: millisecond,
 communication timeout */
#define GUARDTIME_TTO                 (U16)500

/* tRLE, unit: millisecond,
 clock complete to RTS high */
#define GUARDTIME_TRLE                 (U16)1

/* tCSE, unit: millisecond,
 delay time from status/response reception to CTS is high */
#define GUARDTIME_TCSE                (U16)5

/* tRCS, unit: millisecond,
 delay time from RTS low to CTS low */
#define GUARDTIME_TRCS                (U16)5

/* tCCE, unit: millisecond,
 delay time from RTS high to CTS high */
#define GUARDTIME_TCCE                (U16)5

/* tNXC, unit: millisecond, min value
 from command/status reception to the next command reception */
#define GUARDTIME_TNXC                (U16)3

/* tCH(max), unit: millisecond,max value,
 CTS high period during command reception */
#define GUARDTIME_TCH                 (U16)6

/* tCRT(max), unit: millisecond,
 Retransmit after RTS = H during contention happened */
#if (HANDLE_CONTENTION == HOST_RX_AFTER_CONTENTION)
#define GUARDTIME_TCRT_MAX            (U16)41
#else
#define GUARDTIME_TCRT_MAX            (U16)3
#endif

/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/
/* AE1-L communication control state machine state flag */
e_ae1ComState EgCSI0ComState = AE1_IF_IDLE;

/* AE1-L communication control guard timer for every sub-state */
U16 U16gAE1CtrlGuardTimer = (U16) 0;

/* decide to send command when value is TRUE */
BOOLEAN Bgcsi0BeginTX = FALSE;

/* response value that host need return, after received status frame */
U8 U8ae1lResponse;/* response to AE1-L */

/* contention source */
e_contentionSource_type contentionSource = CONTENTION_INVALID;
/*****************************************************************************
 Private variables and functions
 *****************************************************************************/
/* save response data when receiving response */
static U8 receiveResponse;

#ifdef DEBUG_ON
/* Debug used */
U8 errorCode = DONE;
#endif
#if 0
/*****************************************************************************
 * ID                : 1.0
 * Outline           : Communication error process
 * Include           : none
 * Declaration       : static void ComErrPro(U8 errorCode)
 * Description       : Error handle in communication (setting)
 * Argument          : none
 * Return Value      : none
 * Calling Functions : none
 *****************************************************************************/
static void ComErrPro(U8 errorCode)
{
	/* To do: error handle */
}
#endif
/*****************************************************************************
 * ID                : 1.0
 * Outline           : Calculate the check sum
 * Include           : none
 * Declaration       : U8 CheckSum8(const U8 * pData, U16 Length)
 * Description       : Calculate the check sum
 * Argument          : *pData, pointer to data buffer that need be calculated
 *                   : Length, buffer length in data byte number
 * Return Value      : calculated checksum
 * Calling Functions : none
 *****************************************************************************/
U8 CheckSum8(const U8 * pData, U16 Length)
{
	U8 sum = (U8)0;

	while (Length > (U16) 0)
	{
		sum += *pData;
		Length--;
		pData++;
	}
	return sum;
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : clear guard timer
 * Include           : none
 * Declaration       : void StartGuardTimer(U16* guardTimer)
 * Description       : clear guard timer
 * Argument          : *guardTimer, pointer to variable which need to be cleared
 * Return Value      : Specified variable = 0
 * Calling Functions : IF_AE1Ctrl_ComPro()
 *****************************************************************************/
void StartGuardTimer(U16* guardTimer)
{
	*guardTimer = (U16) 0;
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : check guard timer time out
 * Include           : none
 * Declaration       : BOOLEAN IsGuardTmrTimeout(U16 guardTimer, U16 timeOutValue)
 * Description       : check whether guard timer is timeout or not
 * Argument          : guardTimer, guard timer count.
 *                   : timeOutValue, timeout value settings.
 * Return Value      : TRUE, guard timer timeout.
 *                   : FALSE, guard timer does not timeout.
 * Calling Functions : IF_AE1Ctrl_ComPro()
 *****************************************************************************/
BOOLEAN IsGuardTmrTimeout(U16 guardTimer, U16 timeOutValue)
{
	if (guardTimer >= timeOutValue)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : return response to AE1-L
 * Include           : none
 * Declaration       : static U8 ReturnResponseToAE1L(const U8* pAE1LStatusBuf)
 * Description       : check received status then give response code
 * Argument          : *pAE1LStatusBuf, pointer to received status buffer
 * Return Value      : ACK, OK, normal reception
 *                   : NACK_UNDEF_CMD, Undefined command
 *                   : (NACK_INVALID_PARAMETER, Invalid parameter)
 *                   : NACK_CHECKSUM_ERR, check sum error
 * Calling Functions : none
 *****************************************************************************/
static U8 ReturnResponseToAE1L(const U8* pAE1LStatusBuf)
{
	U8 returnValue = (U8)0;
	U16 checkSumByteIndex = (U16)0;
	U16 frmSize = (U16)0;

	/* continue for correct ID */
	/* (1) checksum error check */
	/* big-endian conversion */
	frmSize = ReadU16FromBuf(&pAE1LStatusBuf[5]);
	checkSumByteIndex = frmSize - (U16)1;
	if (pAE1LStatusBuf[checkSumByteIndex] == CheckSum8(&pAE1LStatusBuf[0],
			frmSize - (U16)1))
	{
		/* NOTE:
		 *     HERE, NO CHECK FOR "UNDEFINED COMMAND" AND "INVALID PARAMETER". */
		returnValue = ACK;
	}
	else
	{
		/* CheckSum error then re-receive */
		returnValue = NACK_CHECKSUM_ERR;
	}

	return returnValue;
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : decide next action based on response from AE1-L
 * Include           : none
 * Declaration       : static U8 RxResponseProcess(const U8* pAE1LStatusBuf)
 * Description       : decide next action based on response from AE1-LF.
 * Argument          : *pAE1LStatusBuf, pointer to received status buffer
 * Return Value      : DO_NOTHING, for following commands:
 *                   :   ACK, OK, normal reception
 *                   :   NACK_UNDEF_CMD, Undefined command
 *                   :   NACK_INVALID_PARAMETER, Invalid parameter
 *                   :   NACK_RXED_BYTE_COUNT_ERR, received byte count error
 *                   : RE_TRANSMIT, for following commands:
 *                   :   NACK_CHECKSUM_ERR, check sum error
 *                   :   NACK_NON_EXE_STATE_ERR, non-executable state error
 * Calling Functions : none
 *****************************************************************************/
static U8 RxResponseProcess(const U8* pAE1LStatusBuf)
{
	U8 returnValue = DO_NOTHING;

	switch(*pAE1LStatusBuf)
	{
	case ACK:
	case NACK_UNDEF_CMD:
	case NACK_INVALID_PARAMETER:
	case NACK_RXED_BYTE_COUNT_ERR:
		returnValue = DO_NOTHING;
		break;
	case NACK_CHECKSUM_ERR:
	case NACK_NON_EXE_STATE_ERR:
		returnValue = RE_TRANSMIT;
		break;
	default:
		/* Ignore other  */
		break;
	}

	return returnValue;
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : AE1 Communication task
 * Include           : none
 * Declaration       : void IF_AE1Ctrl_ComPro(void)
 * Description       : should be called by application layer
 *                   : Communication between Host and AE1-LF.
 *                   : ...transmit/receive
 * Argument          : none
 * Return Value      : none
 * Calling Functions : none
 *****************************************************************************/
void IF_AE1Ctrl_ComPro(void)
{
	/* AE1-L communication control state check */
	switch (EgCSI0ComState)
	{
	case AE1_IF_IDLE:
		/* Wait AE1 task "Initialize" state */
		if (EgAE1Task == INIT_AE1) /* AE1 need initialization */
		{
			EgCSI0ComState = INIT_CSI_IF;
		}
		break;
	case INIT_CSI_IF:
		/* Initialize CSI interface */
		Drv_CSI0_Init((U16) 10000);

		EgCSI0ComState = WAIT_AE1_BOOTUP;
		break;
	case WAIT_AE1_BOOTUP:
		if (CTS == HIGH)
		{
			/* reset AE1 over */
			EgCSI0ComState = WAIT_COM;
		}
		else
		{
			/* wait until CTS is high */
		}

		break;
	case WAIT_COM:
		/* When AE1 task detected transferred to "Power down" state
		 * then wait to re-initialize CSI interface */
		if (EgAE1Task == AE1_POWER_DOWN)
		{
			/* RTS should be low when power down */
			RTS = LOW;
			EgCSI0ComState = AE1_IF_IDLE;
		}
		else
		{
			/* Wait Tx or Rx */
			if (CTS == LOW)
			{
				/* clear guard timer,
				 * and start new guard timer, "tTO"  */
				StartGuardTimer(&U16gAE1CtrlGuardTimer);
				/* start to receive by transmit dummy data */
				if (Drv_CSI0_Receive(&U8AE1ComRxBuf[0],
						FRM_SIZE_POSITION_IN_BYTES) == TRUE)
				{
					EgCSI0ComState = RX_HEADER;
				}
				else
				{
					/* wait sending dummy data */
				}
			}
			else if (Bgcsi0BeginTX == TRUE)
			{
				RTS = LOW;
				/* clear guard timer,
				 * and start new guard timer, "tRCS"  */
				StartGuardTimer(&U16gAE1CtrlGuardTimer);
				EgCSI0ComState = BEGIN_CMD_TX;
			}
			else
			{
				/* Wait communication */
			}
		}

		break;
	case RX_HEADER:
		/* Receive data byte */
		if (Drv_CSI0_GetComCounter() == (U16) 0)
		{
#ifdef WRONG_FRM_SIZE_PROCESS
			/* If wrong frame size is received
			 * then receive maximum size response until CTS = HIGH */
			if(ReadU16FromBuf(&U8AE1ComRxBuf[5]) > RX_FRM_SIZE)
			{
				/* Wrong frame size parameter received.
				 * Receive until CTS = HIGH although there error during reception */
				if (Drv_CSI0_Receive(&U8AE1ComRxBuf[7],
						(RX_FRM_SIZE - FRM_SIZE_POSITION_IN_BYTES)) == TRUE)
				{
					EgCSI0ComState = RX_BODY;
				}
				else
				{
					/* wait sending dummy data */
#ifdef DEBUG_ON
					Service_Error_PrintInfo("* Other wants send in receive"); /*Setting error process */
#endif
				}
			}
			else
			{
#endif
				/* receive complete */
				if (Drv_CSI0_Receive(&U8AE1ComRxBuf[7], (ReadU16FromBuf(
						&U8AE1ComRxBuf[5]) - FRM_SIZE_POSITION_IN_BYTES)) == TRUE)
				{
					EgCSI0ComState = RX_BODY;
				}
				else
				{
					/* wait sending dummy data */
#ifdef DEBUG_ON
					Service_Error_PrintInfo("* Other wants send in receive"); /*Setting error process */
#endif
				}
#ifdef WRONG_FRM_SIZE_PROCESS
			}
#endif
		}
		else
		{
			/* header reception is not complete */
			/* if CTS == HIGH during reception then host TX error response */
			if (CTS == HIGH)
			{
				/* if CTS is high before frame reception is complete,
				 * return "Received byte count error" */
				Drv_CSI0_AbortReceive();
				U8ae1lResponse = NACK_RXED_BYTE_COUNT_ERR;
				/* prepare for next reception */
				EgCSI0ComState = WAIT_HOST_TX_RESPONSE;
#ifdef DEBUG_ON
				Service_Error_PrintInfo("* CTS=H when header receive"); /*Setting error process */
#endif
			}
			else
			{
				/* receive continuously */
			}
		}

		if (IsGuardTmrTimeout(U16gAE1CtrlGuardTimer, GUARDTIME_TTO) == TRUE)
		{
			Drv_CSI0_AbortReceive();
			EgCSI0ComState = COM_ERROR;
#ifdef DEBUG_ON
			errorCode = ERROR1;
			Service_Error_PrintInfo("* Receive header overtime"); /*Setting error process */
#endif
		}
		else
		{
			/* continue to receive */
		}
		break;
	case RX_BODY:
		/* Judge from 'FRM_SIZE_POSITION_IN_BYTES' byte received */
		if (Drv_CSI0_GetComCounter() == (U16) 0)
		{
			/* Frame receive complete then judge frame integrity */
			U8ae1lResponse = ReturnResponseToAE1L(&U8AE1ComRxBuf[0]);

			/* clear guard timer, "tTO" is over.
			 * and start new guard timer, "tCSE"  */
			StartGuardTimer(&U16gAE1CtrlGuardTimer);
			EgCSI0ComState = WAIT_HOST_TX_RESPONSE;
		}
		else
		{
			/* receive until all frame bytes are received */
#if 0
			/* if CTS == HIGH during reception then host TX error response */
			if (CTS == HIGH)
			{
				/* if CTS is high before frame reception is complete,
				 * return "Received byte count error" */
				Drv_CSI0_AbortReceive();
				U8ae1lResponse = NACK_RXED_BYTE_COUNT_ERR;
				/* prepare for next reception */
				EgCSI0ComState = WAIT_HOST_TX_RESPONSE;
#ifdef DEBUG_ON
				Service_Error_PrintInfo("* CTS=H when Body receive"); /*Setting error process */
#endif
			}
			else
			{
				/* receive continuously */
			}
#endif
		}

		if (IsGuardTmrTimeout(U16gAE1CtrlGuardTimer, GUARDTIME_TTO) == TRUE)
		{
			Drv_CSI0_AbortReceive();
			EgCSI0ComState = COM_ERROR;
#ifdef DEBUG_ON
			errorCode = ERROR2;
			Service_Error_PrintInfo("* Receive body OT"); /*Setting error process */
#endif
		}
		else
		{
			/* continue to receive */
		}
		break;
	case WAIT_HOST_TX_RESPONSE:
		if (CTS == HIGH)
		{
			/* start host response transmission */
			RTS = LOW;
			/* clear guard timer, "tCSE" is over.
			 * and start new guard timer, "tRCS"  */
			StartGuardTimer(&U16gAE1CtrlGuardTimer);
			EgCSI0ComState = START_HOST_TX_RESPONSE;
		}
		else
		{
			/* wait until CTS = HIGH */
			if (IsGuardTmrTimeout(U16gAE1CtrlGuardTimer, GUARDTIME_TCSE)
					== TRUE)
			{
				/* AE1 error, re-initialize */
				Drv_CSI0_AbortReceive();
				EgCSI0ComState = COM_ERROR;
#ifdef DEBUG_ON
				errorCode = ERROR3;
				Service_Error_PrintInfo("* Wait CTS=H after Rec overtime"); /*Setting error process */
#endif
			}
			else
			{
			} /* wait until CTS = HIGH */
		}

		break;
	case START_HOST_TX_RESPONSE:
		if (CTS == LOW)
		{
			/* start host response transmission */
			if (Drv_CSI0_Transmit(&U8ae1lResponse, RESPONSE_SIZE_IN_BYTE)
					== TRUE)
			{
				/* clear guard timer, "tRCS" is over.
				 * and start new guard timer, "tTO"  */
				StartGuardTimer(&U16gAE1CtrlGuardTimer);
				EgCSI0ComState = HOST_TXING_RESPONSE;
			}
			else
			{
				/* wait until response can be transmitted successfully */
#ifdef DEBUG_ON
				Service_Error_PrintInfo("* Other wants send in ACK stage"); /*Setting error process */
#endif
			}
		}
		else
		{
			/* wait until CTS is low */
			if (IsGuardTmrTimeout(U16gAE1CtrlGuardTimer, GUARDTIME_TRCS)
					== TRUE)
			{
				/* AE1 error, re-initialize */
				RTS = HIGH;
				EgCSI0ComState = COM_ERROR;
#ifdef DEBUG_ON
				errorCode = ERROR4;
				Service_Error_PrintInfo("* AE1 set CTS=L before ACK OT"); /*Setting error process */
#endif
			}
			else
			{
			} /* wait until CTS is low */
		}

		break;
	case HOST_TXING_RESPONSE:
		/* wait until response transmit complete */
		if (Drv_CSI0_GetComCounter() == (U16) 0)
		{
			/* clock complete then transfer to idle mode */
			/* clear guard timer, "tTO" is over.
			 * and start new guard timer, "tRLE"  */
			StartGuardTimer(&U16gAE1CtrlGuardTimer);
			EgCSI0ComState = HOST_WAIT_RTS_HIGH_ACK;
		}
		else
		{
			/* wait until transmit complete */
			if (IsGuardTmrTimeout(U16gAE1CtrlGuardTimer, GUARDTIME_TTO) == TRUE)
			{
				/* AE1 error, re-initialize */
				RTS = HIGH;
				Drv_CSI0_AbortTransmit();
				EgCSI0ComState = COM_ERROR;
#ifdef DEBUG_ON
				errorCode = ERROR6;
				Service_Error_PrintInfo("* Tx stopped in ACK OT"); /*Setting error process */
#endif
			}
			else
			{
				/* Continue to wait */
			}

			if (CTS == HIGH)
			{
				/* contention process, during host transmitting response */
				Drv_CSI0_AbortTransmit();
				RTS = HIGH;
#ifdef DEBUG_ON
				errorCode = ERROR5;
				Service_Error_PrintInfo("* CTS=H when host Tx response"); /*Setting error process */
#endif
#if (HANDLE_CONTENTION == HOST_RX_AFTER_CONTENTION)/* Host receive after contention */
				EgCSI0ComState = COM_ERROR;
#else/* Host re-transmit after contention */
				/* clear guard timer,
				 * and start new guard timer, "tCRT(max)" */
				StartGuardTimer(&U16gAE1CtrlGuardTimer);
				contentionSource = CONTENTION_IN_TX_RESPONSE;
				EgCSI0ComState = WAIT_TX_FOR_CONTENTION;
#endif
			}
			else
			{
				/* Continue to wait */
			}
		}

		break;
	case HOST_WAIT_RTS_HIGH_ACK:
		/* wait until transmit complete */
		if (IsGuardTmrTimeout(U16gAE1CtrlGuardTimer, GUARDTIME_TRLE) == TRUE)
		{
			/* response complete then transfer to idle mode */
			RTS = HIGH;
			/* clear guard timer, "tRLE" is over.
			 * and start new guard timer, "tCCE"  */
			StartGuardTimer(&U16gAE1CtrlGuardTimer);
			EgCSI0ComState = WAIT_HOST_TX_RESPONSE_COMPLETE;
		}
		else
		{
			/* Continue to wait */
		}
		break;
	case WAIT_HOST_TX_RESPONSE_COMPLETE:
		if (CTS == HIGH)
		{
			/* status response reception is complete */
			/* clear guard timer, "tCCE" is over.
			 * and start new guard timer, "tNXC" or "tNXS"  */
			StartGuardTimer(&U16gAE1CtrlGuardTimer);
			EgCSI0ComState = STS_WAIT_FRM_INTERVAL;/* wait next communication */
		}
		else
		{
			/* wait until CTS is high */
			if (IsGuardTmrTimeout(U16gAE1CtrlGuardTimer, GUARDTIME_TCCE)
					== TRUE)
			{
				/* AE1 error, re-initialize */
				Drv_CSI0_AbortTransmit();
				/* clear guard timer, "tCCE" is over.
				 * and start new guard timer, "tNXC" or "tNXS"  */
				StartGuardTimer(&U16gAE1CtrlGuardTimer);
				EgCSI0ComState = STS_WAIT_FRM_INTERVAL;
			}
			else
			{
				/* wait until CTS is high */
			}
		}

		break;
	case STS_WAIT_FRM_INTERVAL:
		if (IsGuardTmrTimeout(U16gAE1CtrlGuardTimer, GUARDTIME_TNXC) == TRUE)
		{
			EgCSI0ComState = STS_RECEPTION_OVER;
		}
		else
		{
			/* wait until response reception is over */
		}
		break;
	case STS_RECEPTION_OVER:
		/* wait next communication */
		EgCSI0ComState = WAIT_COM;
		break;
	case BEGIN_CMD_TX:
		if (CTS == LOW)
		{
			/* start host response transmission */
			if (Drv_CSI0_Transmit(&U8AE1ComTxBuf[0], ReadU16FromBuf(
					&U8AE1ComTxBuf[5])) == TRUE)
			{
				/* host transmit command successfully */
				/* clear guard timer, "tRCS" is over.
				 * and start new guard timer, "tTO"  */
				StartGuardTimer(&U16gAE1CtrlGuardTimer);
				EgCSI0ComState = HOST_TXING_COMMAND;
			}
			else
			{
				/* wait when can transmit */
#ifdef DEBUG_ON
				Service_Error_PrintInfo("* Other wants send when Tx start"); /*Setting error process */
#endif
			}
		}
		else
		{
			/* wait until CTS is low */
			if (IsGuardTmrTimeout(U16gAE1CtrlGuardTimer, GUARDTIME_TRCS)
					== TRUE)
			{
				/* AE1 error, re-initialize */
				RTS = HIGH;
				Drv_CSI0_AbortTransmit();
				EgCSI0ComState = COM_ERROR;
#ifdef DEBUG_ON
				errorCode = ERROR8;
				Service_Error_PrintInfo("* CTS keeps H when when Tx start"); /*Setting error process */
#endif
			}
			else
			{
				/* wait until CTS is low */
			}
		}

		break;
	case HOST_TXING_COMMAND:
		if (CTS == HIGH)
		{
			/* contention process */
			Drv_CSI0_AbortTransmit();
			RTS = HIGH;
			/* clear guard timer,
			 * and start new guard timer, "tCRT(max)" */
			StartGuardTimer(&U16gAE1CtrlGuardTimer);
#if (HANDLE_CONTENTION == HOST_RX_AFTER_CONTENTION)/* Host receive after contention */
			EgCSI0ComState = RX_STS_FOR_CONTENTION;
#else/* Host re-transmit after contention */
			contentionSource = CONTENTION_IN_TX_CMD;
			EgCSI0ComState = WAIT_TX_FOR_CONTENTION;
#endif
		}
		else
		{
			if (Drv_CSI0_GetComCounter() == (U16) 0)
			{
				/* clock complete then transfer to idle mode */
				/* clear guard timer, "tTO" is over.
				 * and start new guard timer, "tRLE"  */
				StartGuardTimer(&U16gAE1CtrlGuardTimer);
				EgCSI0ComState = HOST_WAIT_RTS_HIGH_CMD;
			}
			else
			{
				/* wait until all commands transmission are over */
			}
		}

		if (IsGuardTmrTimeout(U16gAE1CtrlGuardTimer, GUARDTIME_TTO) == TRUE)
		{
			/* AE1 error, re-initialize */
			RTS = HIGH;
			Drv_CSI0_AbortTransmit();
			EgCSI0ComState = COM_ERROR;
#ifdef DEBUG_ON
			errorCode = ERROR9;
			Service_Error_PrintInfo("* Tx OT!"); /*Setting error process */
#endif
		}
		else
		{
			/* wait until all commands transmission are over */
		}

		break;
	case HOST_WAIT_RTS_HIGH_CMD:
		/* wait until transmit complete */
		if (IsGuardTmrTimeout(U16gAE1CtrlGuardTimer, GUARDTIME_TRLE) == TRUE)
		{
			/* transmit command over then wait receive response */
			RTS = HIGH;
			/* clear guard timer, "tRLE" is over.
			 * and start new guard timer, "tCCE" */
			StartGuardTimer(&U16gAE1CtrlGuardTimer);
			EgCSI0ComState = WAIT_HOST_TX_COMMAND_COMPLETE;
		}
		else
		{
			/* Continue to wait */
		}
		break;
	case WAIT_HOST_TX_COMMAND_COMPLETE:
		if (CTS == HIGH)
		{
			/* wait until CTS is high */
			/* clear guard timer, "tCCE" is over.
			 * and start new guard timer, "tCH" */
			StartGuardTimer(&U16gAE1CtrlGuardTimer);
			EgCSI0ComState = WAIT_RX_RESPONSE;
		}
		else
		{
			/* wait until CTS = HIGH */
			if (IsGuardTmrTimeout(U16gAE1CtrlGuardTimer, GUARDTIME_TCCE)
					== TRUE)
			{
				/* AE1 error, re-initialize */
				Drv_CSI0_AbortTransmit();
				EgCSI0ComState = WAIT_RX_RESPONSE;
			}
			else
			{
				/* wait until all commands transmission are over */
			}
		}

		break;
	case WAIT_RX_RESPONSE:
		if (CTS == LOW)
		{
			/* wait until CTS is high */
			/* clear guard timer, "tCH" is over.
			 * and start new guard timer, "tTO" */
			StartGuardTimer(&U16gAE1CtrlGuardTimer);
			if (Drv_CSI0_Receive(&receiveResponse, RESPONSE_SIZE_IN_BYTE)
					== TRUE)
			{
				/* wait receive response complete */
				EgCSI0ComState = RXING_RESPONSE;
			}
			else
			{
				/* wait until can receive response */
#ifdef DEBUG_ON
				Service_Error_PrintInfo("* Other wants send when Rx ACK"); /*Setting error process */
#endif
			}
		}
		else
		{
			/* wait until start receive response */
			if (IsGuardTmrTimeout(U16gAE1CtrlGuardTimer, GUARDTIME_TCH) == TRUE)
			{
				/* AE1 error, re-initialize */
				EgCSI0ComState = COM_ERROR;
#ifdef DEBUG_ON
				errorCode = ERROR11;
				Service_Error_PrintInfo("* CTS keeps H before Rx ACK OT"); /*Setting error process */
#endif
			}
			else
			{
				/* wait until start receive response */
			}
		}

		break;
	case RXING_RESPONSE:
		if (Drv_CSI0_GetComCounter() == (U16) 0)
		{
			/* clear guard timer, "tTO" is over.
			 * and start new guard timer, "tCSE" */
			StartGuardTimer(&U16gAE1CtrlGuardTimer);
			/* receive response complete then process */
			if (RxResponseProcess(&receiveResponse) == DO_NOTHING)
			{
				/* do nothing */
				EgCSI0ComState = WAIT_RX_RESPONSE_COMPLETE;
			}
			else
			{
#ifdef DEBUG_ON
				Service_Error_PrintInfo("* Report error in response"); /*Setting error process */
#endif
				EgCSI0ComState = CMD_WAIT_FRM_INTERVAL;
			}
		}

		if (IsGuardTmrTimeout(U16gAE1CtrlGuardTimer, GUARDTIME_TTO) == TRUE)
		{
			/* AE1 error, re-initialize */
			Drv_CSI0_AbortReceive();
			EgCSI0ComState = COM_ERROR;
#ifdef DEBUG_ON
			errorCode = ERROR12;
			Service_Error_PrintInfo("* Rx ACK OT"); /*Setting error process */
#endif
		}
		else
		{
			/* wait until response reception is over */
		}
		break;
	case WAIT_RX_RESPONSE_COMPLETE:
		if (CTS == HIGH)
		{
			/* transmit command is over then wait with frame interval time */
			/* clear guard timer, "tCSE" is over.
			 * and start new guard timer, "tNXC" or "tNXS" */
			StartGuardTimer(&U16gAE1CtrlGuardTimer);
			EgCSI0ComState = CMD_WAIT_FRM_INTERVAL;
		}
		else
		{
			/* wait until CTS is high */
			if (IsGuardTmrTimeout(U16gAE1CtrlGuardTimer, GUARDTIME_TCSE)
					== TRUE)
			{
				/* AE1 error, re-initialize */
				Drv_CSI0_AbortReceive();
				/* clear guard timer, "tCSE" is over.
				 * and start new guard timer, "tNXC" or "tNXS" */
				StartGuardTimer(&U16gAE1CtrlGuardTimer);
				EgCSI0ComState = CMD_WAIT_FRM_INTERVAL;
			}
			else
			{
				/* wait until response reception is over */
			}
		}

		break;
	case CMD_WAIT_FRM_INTERVAL:
		if (IsGuardTmrTimeout(U16gAE1CtrlGuardTimer, GUARDTIME_TNXC) == TRUE)
		{
			EgCSI0ComState = TX_CMD_OVER;
		}
		else
		{
			/* wait until response reception is over */
		}
		break;
	case TX_CMD_OVER:
		Bgcsi0BeginTX = FALSE;
		EgCSI0ComState = WAIT_COM;/* wait next communication */
		break;
#if (HANDLE_CONTENTION == HOST_RX_AFTER_CONTENTION)/* Host receive after contention */
	case RX_STS_FOR_CONTENTION:
		/* Receive STS because of contention */
		if (CTS == LOW)
		{
			/* clear guard timer,
			 * and start new guard timer, "tTO"  */
			StartGuardTimer(&U16gAE1CtrlGuardTimer);
			/* start to receive by transmit dummy data */
			if (Drv_CSI0_Receive(&U8AE1ComRxBuf[0], FRM_SIZE_POSITION_IN_BYTES)
					== TRUE)
			{
				EgCSI0ComState = RX_HEADER;
			}
			else
			{
				/* wait sending dummy data */
			}
		}
		else
		{
			/* Wait CTS is low */
			if (IsGuardTmrTimeout(U16gAE1CtrlGuardTimer, GUARDTIME_TCRT_MAX)
					== TRUE)
			{
				/* re-transmit */
				EgCSI0ComState = WAIT_COM;
			}
			else
			{
				/* Wait CTS is low */
			}
		}

		break;
#else/* Host re-transmit after contention */
	case WAIT_TX_FOR_CONTENTION:
		/* Wait for elapse of "tCRT" */
		if (IsGuardTmrTimeout(U16gAE1CtrlGuardTimer, GUARDTIME_TCRT_MAX)
				== TRUE)
		{
			RTS = LOW;
			if(contentionSource == CONTENTION_IN_TX_RESPONSE)
			{
				/* (1)re-transmit Response */
				/* clear guard timer, "tCSE" is over.
				 * and start new guard timer, "tRCS"  */
				StartGuardTimer(&U16gAE1CtrlGuardTimer);
				EgCSI0ComState = START_HOST_TX_RESPONSE;
			}
			else if(contentionSource == CONTENTION_IN_TX_CMD)
			{
				/* (2) re-transmit Command  */
				/* clear guard timer,
				 * and start new guard timer, "tRCS"  */
				StartGuardTimer(&U16gAE1CtrlGuardTimer);
				EgCSI0ComState = BEGIN_CMD_TX;
			}
			else
			{
				/* Unknown contention */
				EgCSI0ComState = COM_ERROR;
			}
		}
		else
		{
			/* Wait for elapse of "tCRT" */
		}
		break;
#endif
	case COM_ERROR:
		/* Error happened during communication */
		/* AE1 error, need re-initialize.
		 * after re-initialization, set EgCSI0ComState = WAIT_COM,
		 * start new communication. */
		RTS = LOW;
		EgCSI0ComState = WAIT_COM;/* Go to next communication */
		break;
	}
}

/* End of file */
