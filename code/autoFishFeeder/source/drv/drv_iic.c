/******************************************************************************
* DISCLAIMER
*
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized.
* This software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
*
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY,
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY
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
*******************************************************************************/
/* Copyright (C) 2010 Renesas Electronics Corporation. All rights reserved. */
/******************************************************************************
* System Name	: AE1-LF Car Audio Demo
* File Name 	: driver_iic.c
* Abstract 		: driver of iic
* Version 		: Ver 0.10
* Device 		: R8C/2A group, or R8C/2B group
* Tool-Chain 	: High-performance Embedded Workshop (Version 4.08.00.011)
* 				: C Compiler Package for M16C Series M3T-NC30WA(V.5.45 Release 00)
* OS 			: None
* H/W Platform 	: AE1-LF demo board
* Description 	: This is driver of iic.
* Operation 	: 1. lower layer driver
* Limitation 	: This program can be operated by 20MHz only.
* 				:
*******************************************************************************
* History 		: Dec.16,2010 Ver. 0.10 First Release
* 				:
*******************************************************************************/
#include "BasicType.h"
#include "sfr_r82b.h"
#include "config.h"
#include "drv_iic.h"
//#include "service_general.h"

static U8*	pI2CDataBuf;
static U16	I2CDataLength;
static U8	I2CStatus;
#if 0
static U8	I2CSlaveAddr; 
#endif

/*****************************************************************************
 * ID                : 
 * Outline           : Initialise the I2C interface (SSU) of R8C/2X
 * Include           : none
 * Declaration       : void drv_I2C_Init(void)
 * Description       : 
 * Argument          : 
 * Return Value      : 
 * Calling Functions :
 *****************************************************************************/
void drv_I2C_Init(void)
{
	/* I2C mode init */
	mstiic = (U8)ON;			/* Turn off standby bit */
	iicsel = (U8)ON;			/* Set module as I2C */
	ssums_ssmr2 = (U8)0;
	iccr1 &= 0xF0;
	iccr1 |= 0x5;			/* fBLCK/100 */
	ice_iccr1 = ON;				/* Enable this module */

	stop_icsr = OFF;			/* Clear stop flag */

	nakie_icier = OFF;
	rie_icier = OFF;			/* Receive interrupt */
	teie_icier = OFF;
	tie_icier = OFF;			/* Transmit interrupt */
	stie_icier = OFF;
	iicic = (U8)1;				/* interrupt level */
	I2CStatus = I2CBUS_FREE;
}


/*****************************************************************************
 * ID                : 
 * Outline           : I2C Master send function
 * Include           : none
 * Declaration       : StdRetType drv_I2C_MasterSend(U8 SlaveAddr, U8* pData,
 *						U16 Length)
 * Description       : 
 * Argument          : 
 * Return Value      : Standard ERROR CODE, ERROR1 means bus busy
 * Calling Functions :
 *****************************************************************************/
StdRetType drv_I2C_MasterSend(U8 SlaveAddr, U8* pData, U16 Length)
{
	if(bbsy_iccr2 != 0)	/* Check bus busy */
	{
		return ERROR1;			/* Bus is busy */
	}
	mst_iccr1 = ON;				/* Master mode */
	trs_iccr1 = ON;				/* Transmit */
	iccr2 = START_COND;
	pI2CDataBuf = pData;
	I2CDataLength = Length;		/* Include the address */
	I2CStatus = TRANSMIT_HEAD;
#if 0
	I2CSlaveAddr = SlaveAddr;	/* Backup slave address */
#endif
	nackf_icsr = FALSE;
	nakie_icier = OFF;
	rie_icier = OFF;			/* Receive interrupt */
	stie_icier = OFF;
	acke_icier = TRUE;
	if(tdre_icsr == 1)
	{
		icdrt = (SlaveAddr << 1) & (U8)0xFE;
		teie_icier = ON;
	}
	else
	{
		return ERROR2;
	}
	return DONE;
}

#if 0
/*****************************************************************************
 * ID                : 
 * Outline           : I2C Master receive function
 * Include           : none
 * Declaration       : StdRetType drv_I2C_MasterReceive(U8 SlaveAddr, U8* pData,
 *						U16 Length)
 * Description       : 
 * Argument          : 
 * Return Value      : Standard ERROR CODE, ERROR1 means bus busy
 * Calling Functions :
 *****************************************************************************/
StdRetType drv_I2C_MasterReceive(U8 SlaveAddr, U8* pData, U16 Length)
{
	if(bbsy_iccr2 != FALSE)	/* Check bus busy */
	{
		return ERROR1;			/* Bus is busy */
	}
	mst_iccr1 = ON;				/* Master mode */
	trs_iccr1 = ON;				/* Transmit */
	iccr2 = START_COND;			/* Start condition generate */ 
	pI2CDataBuf = pData;
	I2CStatus = RECEIVE_HEAD;
	I2CSlaveAddr = SlaveAddr;	/* Backup slave address */
	I2CDataLength = Length;
	ackbt_icier = LOW;			/* Ack bit is low */
	nakie_icier = OFF;
	rie_icier = OFF;			/* Receive interrupt */
	tie_icier = OFF;			/* Transmit interrupt */
	stie_icier = OFF;
	if(tdre_icsr == TRUE)
	{
		icdrt = (SlaveAddr << 1) | 0x01;
		teie_icier = ON;
	}
	else
	{
		return ERROR2;
	}
	return DONE;
}
#endif

/*****************************************************************************
 * ID                : 
 * Outline           : I2C interrupt processing
 * Include           : none
 * Declaration       : void drv_I2C_Int(void)
 * Description       : Transmite or receive all the data in buffer
 * Argument          : None
 * Return Value      : None
 * Calling Functions :
 *****************************************************************************/
void drv_I2C_Int(void)
{
/*	asm("fset i"); */
	switch(I2CStatus)
	{
	case TRANSMIT_HEAD:
		if(tend_icsr == 1)		/* Used only for transmit */
		{
			if(ackbr_icier== 1)  /* Resend if receive 1 unexpected high ACK*/
			{
				nackf_icsr = 0;
				/* Note: 1. Remove the resend to avoid the iic interrupt 
                            generation is no-end.
                         2. Add the error log here. */
				/* drv_I2C_MasterSend(I2CSlaveAddr, pI2CDataBuf, I2CDataLength); */
//				Service_Error_Log(ERROR_IIC_NOACK);
			}
			else
			{
				if(I2CDataLength == (U16)0)
				{
					I2CStatus = TRANSMIT_END;
					iccr2 = STOP_COND;
					stie_icier = ON;
				}
				else
				{
					I2CStatus = TRANSMIT_DATA;
					icdrt = *pI2CDataBuf;
					pI2CDataBuf++;
					I2CDataLength --;
					teie_icier = OFF;
					tie_icier = ON;
				}
			}
		}

		break;
	case TRANSMIT_DATA:
		if(tdre_icsr == 1)		/* Used only for transmit */
		{
			if(I2CDataLength == (U16)0)
			{
				teie_icier = ON;
				tie_icier = OFF;
				I2CStatus = TRANSMIT_END;
			}
			else
			{
				icdrt = *pI2CDataBuf;
				pI2CDataBuf++;
				I2CDataLength --;
			}
		}
		break;
	case TRANSMIT_END:
		if(tend_icsr == 1)		/* Used only for transmit */
		{
			teie_icier = OFF;
			tend_icsr = FALSE;		/* Clear the status flag */
			stop_icsr = FALSE;
			iccr2 = STOP_COND;		
			stie_icier = ON;
		}
		if(stop_icsr == 1)
		{
			stop_icsr = FALSE;
			stie_icier = OFF;
			mst_iccr1 = (U8)0;
			trs_iccr1 = (U8)0;
			I2CStatus = I2CBUS_FREE;		/* Mark of communication ending */
		}
		break;
	case RECEIVE_HEAD:
		if(tend_icsr == 1)		/* Used only for receive */
		{
			tend_icsr = FALSE;		/* Clear the status flag */
			trs_iccr1 = OFF;		/* Switch to receive mode */
			tdre_icsr = FALSE;
			teie_icier = OFF;
			rie_icier = ON;
			if(I2CDataLength == (U16)1)
			{
				rcvd_iccr1 = ON;		/* Disable next receive */
				I2CStatus = RECEIVE_END;
			}
			else
			{
				rcvd_iccr1 = OFF;
				I2CStatus = RECEIVE_DATA;
			}
			*pI2CDataBuf = icdrr;	/* Dummy read for starting receive */ 
		}
		break;
	case RECEIVE_DATA:
		if(rdrf_icsr == 1)
		{
			/* rdrf_icsr = FALSE;	NO need */
			I2CDataLength--;
			if(I2CDataLength == (U16)1)
			{
				rcvd_iccr1 = ON;		/* Disable next receive */
				I2CStatus = RECEIVE_END;
			}
			*pI2CDataBuf = icdrr;
			pI2CDataBuf++;
		}
		break;
	case RECEIVE_END:
		if(rdrf_icsr == 1)
		{
			rdrf_icsr = FALSE;	
			stop_icsr = FALSE;			/*Clear stop flag before the command */

			iccr2 = STOP_COND;
			stie_icier = ON;
		}
		if(stop_icsr == 1)
		{
			*pI2CDataBuf = icdrr;
			stop_icsr = FALSE;
			stie_icier = OFF;
			mst_iccr1 = (U8)0;
			trs_iccr1 = (U8)0;
			I2CStatus = I2CBUS_FREE;		/* Mark of communication ending */
		}
		break;
	case I2CBUS_FREE:
		break;
	default:
		break;
	}
}

/*****************************************************************************
 * ID                : 
 * Outline           : Get I2C busy state
 * Include           : none
 * Declaration       : BOOLEAN drv_I2C_GetI2CBusyState(void)
 * Description       : Get I2C busy state
 * Argument          : None
 * Return Value      : TURE - busy, FALSE - idle
 * Calling Functions :
 *****************************************************************************/
BOOLEAN drv_I2C_GetI2CBusyState(void)
{
	BOOLEAN ret;

	if(bbsy_iccr2 == 1){
		ret = TRUE;
	}else{
		ret = FALSE;
	}

	return ret;
}
/* End of File */
