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
* File Name 	: driver_eeprom.c
* Abstract 		: driver of e2prom
* Version 		: Ver 0.10
* Device 		: R8C/2A group, or R8C/2B group
* Tool-Chain 	: High-performance Embedded Workshop (Version 4.08.00.011)
* 				: C Compiler Package for M16C Series M3T-NC30WA(V.5.45 Release 00)
* OS 			: None
* H/W Platform 	: AE1-LF demo board
* Description 	: This is driver of E2PROM. It is not implemented(2011.05.03)
* Operation 	: 1. lower layer driver
* Limitation 	: This program can be operated by 20MHz only.
* 				:
*******************************************************************************
* History 		: Dec.16,2010 Ver. 0.10 First Release
* 				:
*******************************************************************************/
#if 0
#include "basictype.h"
#include "driver_iic.h"
#include "driver_eeprom.h"

/******************************************************************************
Private global variables and functions
******************************************************************************/
static U8 U8CmdDataBuff[12];

/****************************************************************************
 * ID                : 
 * Outline           : Read EEPROM
 * Include           : none
 * Declaration       : StdRetType Drv_EEPROM_SequentialRead(U8 U8SlaveAddr, 
 *                                               U16 U16DataAddr, U16 U16Length)
 * Description       : From the addrress 0000H, read data sequentially.
 * Argument          : 
 * Return Value      : Standard Error code, ERROR1 means I2C bus busy
 * Calling Functions :
 *****************************************************************************/
StdRetType Drv_EEPROM_SequentialRead(U8* pU8DataBuff,  U16 U16DataLength)
{
	/* The following sequential read command includes: 
       Slave Address(1 byte, R/W=1) + Data1 + ... + Datan */
	return Drv_I2C_MasterReceive(EEPROM_DEV_ADDR, pU8DataBuff, U16DataLength);
}

/****************************************************************************
 * ID                : 
 * Outline           : Write EEPROM
 * Include           : none
 * Declaration       : StdRetType Drv_EEPROM_WriteByte(U8 U8SlaveAddr, 
 *                                               U16 U16DataAddr, U16 U16Length)
 * Description       : From the addrress 0000H, read data sequentially.
 * Argument          : 
 * Return Value      : Standard Error code, ERROR1 means I2C bus busy
 * Calling Functions :
 *****************************************************************************/
StdRetType Drv_EEPROM_WriteByte(U16 U16DataAddr,  U8 U8Data)
{
	/* The following sequential read command includes: 
       Slave Address(1 byte, R/W=0) + Data */
	return Drv_I2C_MasterSend(EEPROM_DEV_ADDR, &U8Data, (U16)3);
}

/****************************************************************************
 * ID                : 
 * Outline           : Write EEPROM
 * Include           : none
 * Declaration       : StdRetType Drv_EEPROM_WriteByte(U8 U8SlaveAddr, 
 *                                               U16 U16DataAddr, U16 U16Length)
 * Description       : Write 1 page(8 bytes) in specific address
 * Argument          : 
 * Return Value      : Standard Error code, ERROR1 means I2C bus busy
 * Calling Functions :
 *****************************************************************************/
StdRetType Drv_EEPROM_WritePage(U8* pU8DataBuff,  U16 U16DataLength)
{
	/* The following sequential read command includes: 
       Slave Address(1 byte, R/W=0) + Data1 + ... + Datan, (n=8) */
	return Drv_I2C_MasterSend(EEPROM_DEV_ADDR, pU8DataBuff, (U16)8);
}

void MakeEEPROMCmdData(U8 U8CmdType, U16 U16DataAddr, U8* pU8DataBuff,   
                       U16 U16DataLength)
{
	U8 U8_i;

	switch(U8CmdType){
	case EEPROM_CMD_BYTE_WRITE:
		/* Command */
		U8CmdDataBuff[0] = EEPROM_DEV_ADDR|EEPROM_RW_WRITE;
		U8CmdDataBuff[1] = (U8)(U16DataAddr>>8);
		U8CmdDataBuff[2] = (U8)U16DataAddr;
		/* Data */
		U8CmdDataBuff[3] = pU8DataBuff[0];
		break;
	case EEPROM_CMD_PAGE_WRITE:
		/* Command */
		U8CmdDataBuff[0] = EEPROM_DEV_ADDR|EEPROM_RW_WRITE;
		U8CmdDataBuff[1] = (U8)(U16DataAddr>>8);
		U8CmdDataBuff[2] = (U8)U16DataAddr;
		/* Data */
		for(U8_i=(U8)0; U8_i<(U8)8; U8_i++){
			U8CmdDataBuff[3+U8_i] = pU8DataBuff[U8_i];
		}
		break;
	case EEPROM_CMD_CURRENT_READ:
		/* Command */
		U8CmdDataBuff[0] = EEPROM_DEV_ADDR|EEPROM_RW_READ;

		/* Data(Considered sequential read) */
		//pU8DataBuff[0] = ;
		//pU8DataBuff[1] = ;
		// ...
		break;
	case EEPROM_CMD_RANDOM_READ:
		/* Command */
		U8CmdDataBuff[0] = EEPROM_DEV_ADDR|EEPROM_RW_WRITE;
		U8CmdDataBuff[1] = (U8)(U16DataAddr>>8);
		U8CmdDataBuff[2] = (U8)U16DataAddr;
		// START need be retransmitted.
		U8CmdDataBuff[3] = EEPROM_DEV_ADDR|EEPROM_RW_READ;

		/* Data(Considered sequential read) */
		//pU8DataBuff[0] = ;
		//pU8DataBuff[1] = ;
		// ...
		break;
	default:
		break;
	}
}
#endif