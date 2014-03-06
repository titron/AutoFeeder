/*
 * .c
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */
#ifndef __IF_SERIAL_FLASH_H__
#define __IF_SERIAL_FLASH_H__
/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/

/*
 * Includes
 */

/*
 * Typedef
 */

/*
 * Macro
 */
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

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */

extern void if_Flash_InitFlashComm(void);
extern BOOLEAN if_Flash_ReadData(U32 U32FlsAddress, U16 U16DataLength,
		U8* pU8Data);
extern BOOLEAN if_Flash_Read32BytesData(U32 U32FlsAddress, U8* pU8Data);
#if 0
extern BOOLEAN if_Flash_Read16BytesData(U32 U32FlsAddress, U8* pU8Data);
extern BOOLEAN if_Flash_Read48BytesData(U32 U32FlsAddress, U8* pU8Data);
extern BOOLEAN if_Flash_Read64BytesData(U32 U32FlsAddress, U8* pU8Data);
#endif
extern BOOLEAN if_Flash_WriteData(U32 U32FlsAddress, U16 U16DataLength,
		U8* pU8Data);
extern BOOLEAN if_Flash_ReadStatusRegister(U8* pU8StatusByte);
extern BOOLEAN if_Flash_ProtectSector(U32 U32FlsAddress);
extern BOOLEAN if_Flash_UnProtectSector(U32 U32FlsAddress);
extern BOOLEAN if_Flash_Erase4KBytesBlock(U32 U32FlsAddress);
#endif

/*
 * Private variables and functions
 */
/* End of File */
