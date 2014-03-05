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
 * File Name    : driver_CSI00.c
 * Abstract     : uart0 driver.
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AE1-LF demo board
 * Description  : Communication driver for host and AE1-LF.
 * Operation    : none
 * Limitation   : This file can be only used as sample code for AE1-LF.
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "sfr_r82b.h"
#include "driver_CSI0.h"

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
#define SFR_SIOCTRL0		          u0c0
#define SFR_SIOCTRL1		          u0c1
#define SFR_SIOBRG 			          u0brg
#define SFR_SIOMODE			          u0mr
#define SFR_SIORXBUF  	              u0rb
#define SFR_SIORXBUF_ERROR	          u0rbh
#define SFR_SIORXBUF_DATA             u0rbl
#define SFR_SIOTXBUF		          u0tbl

/* **** SFR value definition**** */
#define TX_INT_ENABLE()		          (s0tic = (U8)0x01)
#define TX_INT_DISABLE()	          (s0tic = (U8)0x00)
#define RX_INT_ENABLE()		          (s0ric = (U8)0x02)
#define RX_INT_DISABLE()              (s0ric = (U8)0x00)
#define TX_ENABLE()		              (SFR_SIOCTRL1 |= 0x01)
#define TX_DISABLE()	              (SFR_SIOCTRL1 &= 0xFE)
#define RX_ENABLE()		              (SFR_SIOCTRL1 |= 0x04)
#define RX_DISABLE()                  (SFR_SIOCTRL1 &= 0xFB)
#define INTCAUSE_TX_BUF_EMPTY()       (SFR_SIOCTRL1 &=0xEF)
#define INTCAUSE_TX_COMPLETE()        (SFR_SIOCTRL1 |=0x10)

/* **** Bit value definition**** */
#define CLK01_BRG_SOURCE_SELECT_F1    (U8)0x00
#define CLK01_BRG_SOURCE_SELECT_F8    (U8)0x01
#define CLK01_BRG_SOURCE_SELECT_F32   (U8)0x02
#define NCH_TXD_CMOS_OUTPUT           (U8)0x00
#define NCH_TXD_N_CH_OPENDRAIN_OUTPUT (U8)0x01
#define LSB_FIRST                     (U8)0x00
#define MSB_FIRST                     (U8)0x01
#define SMD_CLK_SYN_MODE              (U8)0x01
#define CKDIR_INTERNAL_CLK            (U8)0x00
#define CKDIR_EXTERNAL_CLK            (U8)0x01
#define NO_DATA_IN_TX_BUF             (U8)0x02
#define NO_DATA_IN_TX_REGISTER        (U8)0x08

/* **** Port definition**** */
#define	RX_PORT_SET()                 pu03 = 1; \
	                                  pd1_5 = 0
#define CTS_PORT_SET()                (pd8_6 = 0)
#define RTS_PORT_SET()                RTS = 1; \
	                                  pd8_5 = 1

/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/
static U16 U16gCSI0BufCount;/* byte counter for CSI0 transmission / reception */
static U8* pU8CSI0Buf;/* pointer to CSI0 transmission / reception buffer */

/*****************************************************************************
 Private variables and functions
 *****************************************************************************/
/*****************************************************************************
 * ID                : 1.0
 * Outline           : Initialize host interface
 * Include           : none
 * Declaration       : static StdRetType InitCSI0(U16 baudRateIn100bps)
 * Description       : Clock synchronous serial interface initialization.
 * Argument          : baudRateIn100bps
 *                   :   baud rate value, unit: 100bps
 *                   :   theory value,
 *                   :     (range [from 3930 to 50000] -> [39.3Kbps ~ 5Mbps])
 *                   :   actual value can be set,
 *                   :     (range [from 3930 to 10000] -> [39.3Kbps ~ 1Mbps])
 * Return Value      : DONE --- settings is OK.
 *                   : Error1 --- parameter error
 * Calling Functions : none
 *****************************************************************************/
StdRetType Drv_CSI0_Init(U16 baudRateIn100bps)
{
	U32 brpSet;

	/* Define port */
	RX_PORT_SET();
	CTS_PORT_SET();
	RTS_PORT_SET();

	/* Disable TX/RX and interrupt */
	TX_INT_DISABLE();
	RX_INT_DISABLE();
	TX_DISABLE();
	RX_DISABLE();

	if (baudRateIn100bps == (U16) 0)
	{
		return ERROR1;
	}
	else if (baudRateIn100bps > (U16) 10000)
	{
		/* For AE1-L, maximum baud rate is 1Mbps */
		return ERROR1;
	}
	else
	{
		/* if parameter is correct then continue */
	}

	brpSet = SIO_CLK / (U32) 2;
	brpSet = brpSet / BAUDRATE_UNIT;
	brpSet = brpSet / baudRateIn100bps;
	if (brpSet == (U32)0)
	{
		/* parameter error */
		return ERROR1;
	}
	else if (brpSet > (U32) 256)
	{
		/* BRG over range */
		return ERROR1;
	}
	else
	{
		/* Define the speed */
		SFR_SIOCTRL0 = CLK01_BRG_SOURCE_SELECT_F1 + (NCH_TXD_CMOS_OUTPUT << 5)
				+ (MSB_FIRST << 7);
		SFR_SIOBRG = (U8) (brpSet - (U32)1);
	}

	/* Define data format */
	SFR_SIOMODE = SMD_CLK_SYN_MODE + (CKDIR_INTERNAL_CLK << 3);

	/* transmit interrupt cause select */
	INTCAUSE_TX_COMPLETE();

	/* Enable TX/RX and interrupt */
	RX_INT_ENABLE();
	TX_ENABLE();
	RX_ENABLE();
	return DONE;
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : check if there is data in TX buffer
 * Include           : none
 * Declaration       : static BOOLEAN CanTX(void)
 * Description       : check TI flag
 * Argument          : none
 * Return Value      : TRUE, no data is in TX buffer
 *                   : FALSE, data is in TX buffer
 * Calling Functions : none
 *****************************************************************************/
static BOOLEAN CanTX(void)
{
	if (((SFR_SIOCTRL0 & NO_DATA_IN_TX_REGISTER) == NO_DATA_IN_TX_REGISTER)
			&& U16gCSI0BufCount == (U16) 0)
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
 * Outline           : get counter during communication
 * Include           : none
 * Declaration       : U16 Drv_CSI0_GetComCounter(void)
 * Description       : get counter during communication
 * Argument          : none
 * Return Value      : counter value
 * Calling Functions : none
 *****************************************************************************/
U16 Drv_CSI0_GetComCounter(void)
{
	return U16gCSI0BufCount;
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : Abort transmission
 * Include           : none
 * Declaration       : void Drv_CSI0_AbortTransmit(void)
 * Description       : Abort transmission
 * Argument          : none
 * Return Value      : none
 * Calling Functions : none
 *****************************************************************************/
void Drv_CSI0_AbortTransmit(void)
{
	U16gCSI0BufCount = (U16) 0;
	TX_INT_DISABLE();
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : Abort reception
 * Include           : none
 * Declaration       : void Drv_CSI0_AbortReceive(void)
 * Description       : Abort reception
 * Argument          : none
 * Return Value      : none
 * Calling Functions : none
 *****************************************************************************/
void Drv_CSI0_AbortReceive(void)
{
	U16gCSI0BufCount = (U16) 0;
	RX_INT_DISABLE();
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : CSI0 transmission
 * Include           : none
 * Declaration       : BOOLEAN Drv_CSI0_Transmit(U8* pTXBuf, U16 TXLength)
 * Description       : Send byte queue
 * Argument          : *pTXBuf, pointer to transmit buffer
 *                   : TXLength, length in byte of transmit buffer
 * Return Value      : TRUE, data is moved to TX buffer
 *                   : FALSE, data is not moved to TX buffer,
 *                   :        or input parameter "TXBufLength" is zero.
 * Calling Functions : none
 *****************************************************************************/
BOOLEAN Drv_CSI0_Transmit(U8* pTXBuf, U16 TXLength)
{
	if (CanTX() == TRUE)
	{
		if (TXLength == (U16) 0)
		{
			/* transmit byte length is zero */
			return FALSE;
		}

		/* transmit the 1st byte */
		pU8CSI0Buf = pTXBuf;
		U16gCSI0BufCount = TXLength;
		RX_INT_DISABLE();
		TX_INT_DISABLE();
		TX_INT_ENABLE();
		TX_ENABLE();
		RX_DISABLE();
		SFR_SIOTXBUF = *pU8CSI0Buf;
		return TRUE;
	}
	else
	{
		/* can not transmit */
		return FALSE;
	}
}
/*****************************************************************************
 * ID                : 1.0
 * Outline           : CSI0 reception
 * Include           : none
 * Declaration       : BOOLEAN Drv_CSI0_Receive(U8* pRXBuf, U16 RXLength)
 * Description       : Send byte queue
 * Argument          : *pRXBuf, pointer to receive buffer
 *                   : RXLength, length in byte of receive buffer
 * Return Value      : TRUE, data is moved to RX buffer
 *                   : FALSE, data is not moved to RX buffer,
 *                   :        or input parameter "RXLength" is zero.
 * Calling Functions : none
 *****************************************************************************/
BOOLEAN Drv_CSI0_Receive(U8* pRXBuf, U16 RXLength)
{
	if (CanTX() == TRUE)
	{
		if (RXLength == (U16) 0)
		{
			/* transmit byte length is zero */
			return FALSE;
		}

		/* receive the 1st byte */
		pU8CSI0Buf = pRXBuf;
		U16gCSI0BufCount = RXLength;
		TX_INT_DISABLE();/* clear interrupt flag */
		RX_INT_DISABLE();

		RX_INT_ENABLE();

		RX_DISABLE();/* Clear error part in UxRB */

		RX_ENABLE();
		TX_ENABLE();
		SFR_SIOTXBUF = DUMMY_DATA_FOR_RX;
		return TRUE;
	}
	else
	{
		/* can not transmit */
		return FALSE;
	}
}
/*****************************************************************************
 * ID                : 1.0
 * Outline           : CSI0 transmission interrupt service program
 * Include           : none
 * Declaration       : void CSI0TransmitInt(void)
 * Description       : Send byte in interrupt routine
 * Argument          : none
 * Return Value      : none.
 * Calling Functions : none
 *****************************************************************************/
void CSI0TransmitInt(void)
{
	U16gCSI0BufCount--;
	if (U16gCSI0BufCount > (U16) 0)
	{
		if (CTS == LOW)
		{
			pU8CSI0Buf++;
			SFR_SIOTXBUF = *pU8CSI0Buf;
		}
		else
		{
			/* contention happened */
			RTS = HIGH;
		}
	}
	else
	{
		TX_INT_DISABLE();
	}
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : CSI0 reception interrupt service program
 * Include           : none
 * Declaration       : void CSI0ReceiveInt(void)
 * Description       : receive byte in interrupt routine.
 * Argument          : none
 * Return Value      : none.
 * Calling Functions : none
 *****************************************************************************/
void CSI0ReceiveInt(void)
{
	*pU8CSI0Buf = (U8) (SFR_SIORXBUF & 0x00ff);
	U16gCSI0BufCount--;
	if (U16gCSI0BufCount > (U16) 0)
	{
		pU8CSI0Buf++;
		SFR_SIOTXBUF = DUMMY_DATA_FOR_RX;
	}
	else
	{
		RX_INT_DISABLE();
	}
}
/* End of file */
