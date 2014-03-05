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
 * File Name    : if_serial_flash.c
 * Abstract     : interface for serial flash
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AE1-LF demo board
 * Description  : This is interface of serial flash.
 * Operation    : none
 * Limitation   : This file can be only used as sample code for AE1-LF.
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "basictype.h"
#include "drv_csi1.h"
#include "drv_flash.h"
#include "if_serial_flash.h"

/*****************************************************************************
 Macro definitions
 *****************************************************************************/

/*****************************************************************************
 Private variables and functions
 *****************************************************************************/

/*****************************************************************************
 * ID                :
 * Outline           : Initialise the flash communication
 * Include           : 
 * Declaration       : void drv_Flash_InitFlashComm(void)
 * Description       : 
 * Argument          :
 * Return Value      : 
 * Calling Functions :
 *****************************************************************************/
void if_Flash_InitFlashComm(void)
{
	drv_CSI1_Init(FLASH_COMM_BITRATE);
}

/*****************************************************************************
 * ID                :
 * Outline           : Read any length data(less than buffer length)
 * Include           : none
 * Declaration       : BOOLEAN if_Flash_ReadData(U32 U32FlsAddress, U16 U16DataLength,
 * 												 U8* pU8Data)
 * Description       : Read data x bytes,which address starts from 'U32FlsAddress'.
 * Argument          :
 * Return Value      : TRUE  - Operation have been accepted.
 * 					   FALSE - Operation is prohibited.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN if_Flash_ReadData(U32 U32FlsAddress, U16 U16DataLength, U8* pU8Data)
{
	return drv_Flash_ReadData(U32FlsAddress, U16DataLength, pU8Data);
}

/*****************************************************************************
 * ID                :
 * Outline           : Read the fixed length(32bytes) data
 * Include           : none
 * Declaration       : BOOLEAN if_Flash_Read32BytesData(U32 U32FlsAddress,
 * 												 U8* pU8Data)
 * Description       : Read 32 bytes data,which address starts from 'U32FlsAddress'.
 * Argument          :
 * Return Value      : TRUE  - Operation have been accepted.
 * 					   FALSE - Operation is prohibited.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN if_Flash_Read32BytesData(U32 U32FlsAddress, U8* pU8Data)
{
	return drv_Flash_Read32BytesData(U32FlsAddress, pU8Data);
}

#if 0
/*****************************************************************************
 * ID                :
 * Outline           : Read data
 * Include           : none
 * Declaration       : BOOLEAN if_Flash_Read16BytesData(U32 U32FlsAddress,
 * 												 U8* pU8Data)
 * Description       : Read data x bytes,which address starts from 'U32FlsAddress'.
 * Argument          :
 * Return Value      : TRUE  - Operation have been accepted.
 * 					   FALSE - Operation is prohibited.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN if_Flash_Read16BytesData(U32 U32FlsAddress, U8* pU8Data)
{
	return drv_Flash_Read16BytesData(U32FlsAddress, pU8Data);
}

/*****************************************************************************
 * ID                :
 * Outline           : Read data
 * Include           : none
 * Declaration       : BOOLEAN if_Flash_Read48BytesData(U32 U32FlsAddress,
 * 												 U8* pU8Data)
 * Description       : Read 48 bytes data,which address starts from 'U32FlsAddress'.
 * Argument          :
 * Return Value      : TRUE  - Operation have been accepted.
 * 					   FALSE - Operation is prohibited.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN if_Flash_Read48BytesData(U32 U32FlsAddress, U8* pU8Data)
{
	return drv_Flash_Read48BytesData(U32FlsAddress, pU8Data);
}

/*****************************************************************************
 * ID                :
 * Outline           : Read data
 * Include           : none
 * Declaration       : BOOLEAN if_Flash_Read64BytesData(U32 U32FlsAddress,
 * 												 U8* pU8Data)
 * Description       : Read 64 bytes data,which address starts from 'U32FlsAddress'.
 * Argument          :
 * Return Value      : TRUE  - Operation have been accepted.
 * 					   FALSE - Operation is prohibited.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN if_Flash_Read64BytesData(U32 U32FlsAddress, U8* pU8Data)
{
	return drv_Flash_Read64BytesData(U32FlsAddress, pU8Data);
}
#endif

/*****************************************************************************
 * ID                :
 * Outline           : Read status
 * Include           : none
 * Declaration       : if_Flash_ReadStatusRegister(U8* pU8StatusByte)
 * Description       : 
 * Argument          :
 * Return Value      :  TRUE  - Operation have been accepted.
 * 						FALSE - Operation is prohibited.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN if_Flash_ReadStatusRegister(U8* pU8StatusByte)
{
	return drv_Flash_ReadStatusRegister(pU8StatusByte);
}

/*****************************************************************************
 * ID                :
 * Outline           : Erase the 4K bytes block
 * Include           : none
 * Declaration       : if_Flash_Erase4KBytesBlock(U32 U32FlsAddress)
 * Description       : 
 * Argument          :
 * Return Value      :  TRUE  - Operation have been accepted.
 * 						FALSE - Operation is prohibited.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN if_Flash_Erase4KBytesBlock(U32 U32FlsAddress)
{
	drv_Flash_WriteEnable();

	drv_Flash_BlockErase4KBytes(U32FlsAddress);

	/* Write will be disabled automatically after finish the erase block */
	/* drv_Flash_WriteDisable(); */

	return TRUE;
}

/*****************************************************************************
 * ID                :
 * Outline           : Write any length data(less than buffer length)
 * Include           : none
 * Declaration       : if_Flash_WriteData(U32 U32FlsAddress, U16 U16DataLength,
 *                                        U8* pU8Data)
 * Description       : Write data x bytes,which address starts from 'U32FlsAddress'.
 * Argument          :
 * Return Value      :  TRUE  - Operation have been accepted.
 * 						FALSE - Operation is prohibited.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN if_Flash_WriteData(U32 U32FlsAddress, U16 U16DataLength, U8* pU8Data)
{
	drv_Flash_WriteEnable();

	drv_Flash_WriteData(U32FlsAddress, U16DataLength, pU8Data);

	/* Write will be disabled automatically after finish the program */
	/* drv_Flash_WriteDisable(); */
	return TRUE;
}

/*****************************************************************************
 * ID                :
 * Outline           : Protect sector
 * Include           : none
 * Declaration       : if_Flash_ProtectSector(U32 U32FlsAddress, U16 U16DataLength,
 *                                        U8* pU8Data)
 * Description       : 
 * Argument          :
 * Return Value      :  TRUE  - Operation have been accepted.
 * 						FALSE - Operation is prohibited.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN if_Flash_ProtectSector(U32 U32FlsAddress)
{
	drv_Flash_WriteEnable();

	drv_Flash_ProtectSector(U32FlsAddress);

	/* Write will be disabled automatically after finish the protect sector */
	/* drv_Flash_WriteDisable(); */
	return TRUE;
}

/*****************************************************************************
 * ID                :
 * Outline           : UnProtect sector
 * Include           : none
 * Declaration       : if_Flash_UnProtectSector(U32 U32FlsAddress, U16 U16DataLength,
 *                                        U8* pU8Data)
 * Description       : 
 * Argument          :
 * Return Value      :  TRUE  - Operation have been accepted.
 * 						FALSE - Operation is prohibited.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN if_Flash_UnProtectSector(U32 U32FlsAddress)
{
	drv_Flash_WriteEnable();

	drv_Flash_UnProtectSector(U32FlsAddress);

	/* Write will be disabled automatically after finish the unprotect sector */
	/* drv_Flash_WriteDisable(); */
	return TRUE;
}
/* End of file */
