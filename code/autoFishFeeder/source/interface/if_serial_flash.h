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
 * File Name    : if_serial_flash.h
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
#ifndef __IF_SERIAL_FLASH_H__
#define __IF_SERIAL_FLASH_H__
/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
/* #include "driver_csi1.h" */
/* #include "driver_flash.h" */

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
/* Font address in flash */
#define FLASH_ADDRESS_ACSII 	 (U32)0x000000
#define FLASH_ADDRESS_CJK 		 (U32)0x001000
#define FLASH_ADDRESS_HIRAGNAN   (U32)0x0A4800
#define FLASH_ADDRESS_KATAKNAN   (U32)0x0A5400
#define FLASH_ADDRESS_HANGULSYL  (U32)0x0A6000
#define FLASH_ADDRESS_HANGULJAMO (U32)0x0FD600
#define FLASH_ADDRESS_DEFINE     (U32)0x0FF600
#define FLASH_ADDRESS_BMPLOGO    (U32)0x0FF7C0
#define FLASH_ADDRESS_GB2312_24	 (U32)0x180000
#define FLASH_ADDRESS_UNICODETOGB2312_TABLE (U32)0x200000

/* Parameter storage address in flash (storage size = 256 bytes) */
#define FLASH_ADDRESS_ORIGINAL_STORAGE	 (U32)0x3FF000
#define FLASH_STORAGE_SIZE		 (U32)256
#define FLASH_STORAGE_AREA_NUM	 (U8)16
/* Offset of flag byte which indicates the used memory erea.
   The 256th byte is the flag byte. 
   0xFF - This erea is not used yet.
   0xAA - This erea has been stored the parameters.
 */
#define FLASH_STORAGE_FLAG_BYTE_OFFSET		(U8)255
#define FLASH_STORAGE_FLAG_BYTE_USED		(U8)0xAA
#define FLASH_STORAGE_FLAG_BYTE_NOT_USED	(U8)0xFF

/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/
extern void if_Flash_InitFlashComm(void);
extern BOOLEAN if_Flash_ReadData(U32 U32FlsAddress, U16 U16DataLength, U8* pU8Data);
extern BOOLEAN if_Flash_Read32BytesData(U32 U32FlsAddress, U8* pU8Data);
#if 0
extern BOOLEAN if_Flash_Read16BytesData(U32 U32FlsAddress, U8* pU8Data);
extern BOOLEAN if_Flash_Read48BytesData(U32 U32FlsAddress, U8* pU8Data);
extern BOOLEAN if_Flash_Read64BytesData(U32 U32FlsAddress, U8* pU8Data);
#endif
extern BOOLEAN if_Flash_WriteData(U32 U32FlsAddress, U16 U16DataLength, U8* pU8Data);
extern BOOLEAN if_Flash_ReadStatusRegister(U8* pU8StatusByte);
extern BOOLEAN if_Flash_ProtectSector(U32 U32FlsAddress);
extern BOOLEAN if_Flash_UnProtectSector(U32 U32FlsAddress);
extern BOOLEAN if_Flash_Erase4KBytesBlock(U32 U32FlsAddress);
#endif
/* End of File */
