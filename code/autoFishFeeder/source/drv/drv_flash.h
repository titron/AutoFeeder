/*
 * drv_flash.h
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */
#ifndef __IF_SERIAL_FLASH_H__
#define __IF_SERIAL_FLASH_H__
/*
 * Includes
 */

/*
 * Typedef
 */
typedef struct
{
	U8 U8OperationCode;
	U8 U8AddHigh;
	U8 U8AddMid;
	U8 U8AddLow;
	U8 U8Dummy1;
} StrFlsCmdReadArray2; /* Read Commands - Read Array: 0BH */

/* Note: The erasing of the device is internally self-timed and should take place in a
 *       time of tCHPE. tCHPE = 16 seconds(Typical value)*/
typedef struct
{
	U8 U8OperationCode;
} StrFlsCmdEraseChip; /* Erase Commands - Chip Erase: 60H or C7H*/

typedef struct
{
	U8 U8OperationCode;
	U8 U8AddHigh;
	U8 U8AddMid;
	U8 U8AddLow;
} StrFlsCmdProgramBytePage; /* Program Commands - Byte/Page Program: 02H*/

typedef struct
{
	U8 U8OperationCode;
} StrFlsCmdWriteEnable; /* Protection Commands - Write enable: 06H*/

typedef struct
{
	U8 U8OperationCode;
} StrFlsCmdWriteDisable; /* Protection Commands - Write disable: 04H*/

typedef struct
{
	U8 U8OperationCode;
	U8 U8AddHigh;
	U8 U8AddMid;
	U8 U8AddLow;
} StrFlsCmdProtectSector; /* Protection Commands - Protect sector: 36H*/

typedef struct
{
	U8 U8OperationCode;
	U8 U8AddHigh;
	U8 U8AddMid;
	U8 U8AddLow;
} StrFlsCmdUnProtectSector; /* UnProtection Commands - UnProtect sector: 39H*/

typedef struct
{
	U8 U8OperationCode;
	U8 U8AddHigh;
	U8 U8AddMid;
	U8 U8AddLow;
} StrFlsCmdBlockErase4KBytes; /* Block erase Commands - Block erase: 20H*/

typedef struct
{
	U8 U8OperationCode;
} StrFlsCmdReadStatusRegister; /* Read status Commands - Read status: 05H*/

/*
 * Macro
 */
/* All flash commands (flash module - AT25DF161 ) */
#define FLASH_CMD_READ_ARRAY_1						(U8)0x1B
#define FLASH_CMD_READ_ARRAY_2						(U8)0x0B
#define FLASH_CMD_READ_ARRAY_3						(U8)0x03
#define FLASH_CMD_READ_DUALREAD_ARRAY				(U8)0x3B
#define FLASH_CMD_ERASE_BLOCK_4K_BYTES				(U8)0x20
#define FLASH_CMD_ERASE_BLOCK_32K_BYTES				(U8)0x52
#define FLASH_CMD_ERASE_BLOCK_64K_BYTES				(U8)0xD8
#define FLASH_CMD_ERASE_CHIP1						(U8)0x60
#define FLASH_CMD_ERASE_CHIP2						(U8)0xC7																			()
#define FLASH_CMD_PROGRAM_BYTE_OR_PAGE				(U8)0x02	/* 1-256 bytes */
#define FLASH_CMD_PROGRAM_DUAL_INPUT				(U8)0xA2	/* 1-256 bytes */
#define FLASH_CMD_PROGRAM_ERASE_SUSPEND				(U8)0xB0
#define FLASH_CMD_PROGRAM_ERASE_RESUME				(U8)0xD0
#define FLASH_CMD_PROTECT_W_ENABLE					(U8)0x06
#define FLASH_CMD_PROTECT_W_DISABLE					(U8)0x04
#define FLASH_CMD_PROTECT_SECTOR					(U8)0x36
#define FLASH_CMD_UNPROTECT_SECTOR					(U8)0x39
#define FLASH_CMD_PROTECT_READ_SECTOR_PRT_REG		(U8)0x3C
#define FLASH_CMD_SECURITY_SECTOR_LOCKDOWN			(U8)0x33
#define FLASH_CMD_SECURITY_FREEZE_SECTOR_LOCKDOWN	(U8)0x34
#define FLASH_CMD_SECURITY_READ_SECTOR_LOCKDOWN_REG	(U8)0x35
#define FLASH_CMD_SECURITY_PROGRAM_OTP_SECURITY_REG	(U8)0x9B
#define FLASH_CMD_SECURITY_READ_OTP_SECURITY_REG	(U8)0x77
#define FLASH_CMD_STATUS_READ_STATUS_REG			(U8)0x05
#define FLASH_CMD_STATUS_WRITE_BYTE1_STATUS_REG		(U8)0x01
#define FLASH_CMD_STATUS_WRITE_BYTE2_STATUS_REG		(U8)0x31
#define FLASH_CMD_MISC_RESET						(U8)0xF0
#define FLASH_CMD_MISC_READ_MANUFACTURER_ID			(U8)0x9F
#define FLASH_CMD_MISC_DEEP_POWER_DOWN				(U8)0xB9
#define FLASH_CMD_MISC_WAKEUP						(U8)0xAB
#define FLASH_CMD_PROTECT_OR_UNPROTECT_GLOBAL	FLASH_CMD_STATUS_WRITE_BYTE1_STATUS_REG

/* Reset command confirmation code */
#define FLASH_CMD_MISC_RESET_CONFIRM_CODE			(U8)0xD0

/* Flash address space */
#define FLASH_ADD_TOP								(U32)0x000000
#define FLASH_ADD_END								(U32)0x3FFFFF

/* State machine of flash communication */
#define FLASH_COMM_STATE_INIT_CSI1		 			(U8)0
#define FLASH_COMM_STATE_IDLE         	 			(U8)1
#define FLASH_COMM_STATE_TX_SEGMENT1         		(U8)2
#define FLASH_COMM_STATE_TX_SEGMENT2         		(U8)3
#define FLASH_COMM_STATE_WRITE_TX_END         		(U8)4

/* Dummy data */
#define FLASH_COMM_SEG1_DUMMY						(U8)0xFF
#define FLASH_COMM_SEG2_DUMMY						(U8)0xFF

/* Segment2(data) access type */
#define FLASH_SEG2_ACCESS_TYPE_NONE					(U8)0x00	/* 0 byte data  */
#define FLASH_SEG2_ACCESS_TYPE_WRITE				(U8)0x01	/* W type data segment */
#define FLASH_SEG2_ACCESS_TYPE_READ					(U8)0x02	/* R type data segment */

#define SEND_DUMMY_RECEIVE_DATA(U16Index)								\
	Drv_CSI1_SendData(FLASH_COMM_SEG2_DUMMY);							\
	while(DRV_CSI1_IS_RX_BUFFER_FULL() == CSI1_RX_BUFFER_NOT_FULL){};   \
	pU8Data[U16Index] = Drv_CSI1_GetReceivesData()

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */
extern BOOLEAN drv_Flash_ReadData(U32 U32FlsAddress, U16 U16DataLength,
		U8* pU8Data);
extern BOOLEAN drv_Flash_Read32BytesData(U32 U32FlsAddress, U8* pU8Data);
#if 0
extern BOOLEAN drv_Flash_Read16BytesData(U32 U32FlsAddress, U8* pU8Data);
extern BOOLEAN drv_Flash_Read48BytesData(U32 U32FlsAddress, U8* pU8Data);
extern BOOLEAN drv_Flash_Read64BytesData(U32 U32FlsAddress, U8* pU8Data);
#endif
extern BOOLEAN drv_Flash_WriteData(U32 U32FlsAddress, U16 U16DataLength,
		const U8* pU8Data);
extern BOOLEAN drv_Flash_WriteEnable(void);
/* extern BOOLEAN drv_Flash_WriteDisable(void); */
extern BOOLEAN drv_Flash_ProtectSector(U32 U32FlsAddress);
extern BOOLEAN drv_Flash_UnProtectSector(U32 U32FlsAddress);
extern BOOLEAN drv_Flash_BlockErase4KBytes(U32 U32FlsAddress);
extern BOOLEAN drv_Flash_ReadStatusRegister(U8* pU8StatusByte);

/*
 * Private variables and functions
 */

#endif
/* End of File */
