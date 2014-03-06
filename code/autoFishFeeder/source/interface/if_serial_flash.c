/*
 * if_serial_flash.c
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */

/*
 * Includes
 */
#include "basictype.h"
#include "drv_csi1.h"
#include "drv_flash.h"
#include "if_serial_flash.h"

/*
 * Typedef
 */

/*
 * Macro
 */

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */

/*
 * Private variables and functions
 */

void if_Flash_InitFlashComm(void)
{
	drv_CSI1_Init(FLASH_COMM_BITRATE);
}

/*
 * if_Flash_ReadData
 * Read data x bytes,which address starts from 'U32FlsAddress'.
 */
BOOLEAN if_Flash_ReadData(U32 U32FlsAddress, U16 U16DataLength, U8* pU8Data)
{
	return drv_Flash_ReadData(U32FlsAddress, U16DataLength, pU8Data);
}

/*
 * if_Flash_Read32BytesData
 * Read 32 bytes data,which address starts from 'U32FlsAddress'.
 */
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

/*
 * if_Flash_ReadStatusRegister
 */
BOOLEAN if_Flash_ReadStatusRegister(U8* pU8StatusByte)
{
	return drv_Flash_ReadStatusRegister(pU8StatusByte);
}

/*
 * if_Flash_Erase4KBytesBlock
 * Erase the 4K bytes block
 */
BOOLEAN if_Flash_Erase4KBytesBlock(U32 U32FlsAddress)
{
	drv_Flash_WriteEnable();

	drv_Flash_BlockErase4KBytes(U32FlsAddress);

	/* Write will be disabled automatically after finish the erase block */
	/* drv_Flash_WriteDisable(); */

	return TRUE ;
}

/*
 * if_Flash_WriteData
 * Write data x bytes,which address starts from 'U32FlsAddress'.
 */
BOOLEAN if_Flash_WriteData(U32 U32FlsAddress, U16 U16DataLength, U8* pU8Data)
{
	drv_Flash_WriteEnable();

	drv_Flash_WriteData(U32FlsAddress, U16DataLength, pU8Data);

	/* Write will be disabled automatically after finish the program */
	/* drv_Flash_WriteDisable(); */
	return TRUE ;
}

/*
 * if_Flash_ProtectSector
 */
BOOLEAN if_Flash_ProtectSector(U32 U32FlsAddress)
{
	drv_Flash_WriteEnable();

	drv_Flash_ProtectSector(U32FlsAddress);

	/* Write will be disabled automatically after finish the protect sector */
	/* drv_Flash_WriteDisable(); */
	return TRUE ;
}

BOOLEAN if_Flash_UnProtectSector(U32 U32FlsAddress)
{
	drv_Flash_WriteEnable();

	drv_Flash_UnProtectSector(U32FlsAddress);

	/* Write will be disabled automatically after finish the unprotect sector */
	/* drv_Flash_WriteDisable(); */
	return TRUE ;
}
/* End of file */
