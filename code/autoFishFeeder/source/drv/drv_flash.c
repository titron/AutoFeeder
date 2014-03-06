/*
 * drv_flash.c
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */

/*
 * Includes
 */
#include "basictype.h"
#include "config.h"
#include "drv_flash.h"
#include "drv_csi1.h"

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
static U8 U8Segment1CmdBuffer[6]; /* Segment1(command) buffer */
static void drv_Flash_MakeCommandData(U8 U8CommandType, U32 U32FlsAddress);

/*
 * drv_Flash_ReadData
 * Read data x bytes,which address starts from 'U32FlsAddress'.
 */
BOOLEAN drv_Flash_ReadData(U32 U32FlsAddress, U16 U16DataLength, U8* pU8Data)
{
	U16 U16Index = (U16) 0;
#if 0
	/* Note: Because this routine will be loaded frequently, to save the time,
	 remove the check. Upper layer ensure the validity. */
	if(U16DataLength == (U16)0)
	{
		return FALSE;
	}

	/* Note: Because this routine will be loaded frequently, to save the time,
	 remove the check. Upper layer ensure the validity. */
	if((U32FlsAddress + U16DataLength - (U32)1) > FLASH_ADD_END)
	{
		return FALSE;
	}
#endif

	/* Make the read command */
	drv_Flash_MakeCommandData(FLASH_CMD_READ_ARRAY_2, U32FlsAddress);

#ifdef PORT_CS_BY_SOFTWARE
	/* CS assert */
	SCI1_CS_ASSERT();
#endif

	/* Segment1: command */
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[0]);
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[1]);
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[2]);
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[3]);
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[4]);

	/* Segment2: data */
	/* The 5th byte transmission period */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	while (DRV_CSI1_IS_TX_COMPLETE() == CSI1_TX_SHIFT_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_GetReceivesData();

	for (U16Index = (U8) 0; U16Index < U16DataLength; U16Index++)
	{
#if 0
		/* Wait for transmit buffer empty */
		while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
		{
			; /* wait */
		}
#endif
		/* Send dummy */
		Drv_CSI1_SendData(FLASH_COMM_SEG2_DUMMY);
		/* Wait for receive buffer full */
		while (DRV_CSI1_IS_RX_BUFFER_FULL() == CSI1_RX_BUFFER_NOT_FULL)
		{
			; /* wait */
		}
		/* Receive data */
		pU8Data[U16Index] = Drv_CSI1_GetReceivesData();
	}

#ifdef PORT_CS_BY_SOFTWARE
	/* CS dessert */
	SCI1_CS_DEASSERT();
#endif

	return TRUE ;
}

/*
 * drv_Flash_Read32BytesData
 * Read data 32 bytes,which address starts from 'U32FlsAddress'.
 *
 */
BOOLEAN drv_Flash_Read32BytesData(U32 U32FlsAddress, U8* pU8Data)
{
#if 0
	/* Note: Because this routine will be loaded frequently, to save the time,
	 remove the check. Upper layer ensure the validity. */
	if(U16DataLength == (U16)0)
	{
		return FALSE;
	}

	/* Note: Because this routine will be loaded frequently, to save the time,
	 remove the check. Upper layer ensure the validity. */
	if((U32FlsAddress + U16DataLength - (U32)1) > FLASH_ADD_END)
	{
		return FALSE;
	}
#endif

	/* Make the read command, data length is fixed 16 bytes */
	drv_Flash_MakeCommandData(FLASH_CMD_READ_ARRAY_2, U32FlsAddress);

#ifdef PORT_CS_BY_SOFTWARE
	/* CS assert */
	SCI1_CS_ASSERT();
#endif

	/* Segment1: command */
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[0]);
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[1]);
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[2]);
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[3]);
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[4]);

	/* enable continous receive */
	CONTINOUS_REC_ENABLE();

	/* Segment2: data */
	/* The 5th byte transmission period */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	while (DRV_CSI1_IS_TX_COMPLETE() == CSI1_TX_SHIFT_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_GetReceivesData();

	asm("MOV.W:G   -2H[FB],A0");

	asm("LL0: BTST:G    3,0165H");
	asm("JEQ       LL0");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,[A0]");

	asm("LL1: BTST:G    3,0165H");
	asm("JEQ       LL1");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,1H[A0]");

	asm("LL2: BTST:G    3,0165H");
	asm("JEQ       LL2");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,2H[A0]");

	asm("LL3: BTST:G    3,0165H");
	asm("JEQ       LL3");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,3H[A0]");

	asm("LL4: BTST:G    3,0165H");
	asm("JEQ       LL4");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,4H[A0]");

	asm("LL5: BTST:G    3,0165H");
	asm("JEQ       LL5");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,5H[A0]");

	asm("LL6: BTST:G    3,0165H");
	asm("JEQ       LL6");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,6H[A0]");

	asm("LL7: BTST:G    3,0165H");
	asm("JEQ       LL7");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,7H[A0]");

	asm("LL8: BTST:G    3,0165H");
	asm("JEQ       LL8");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,8H[A0]");

	asm("LL9: BTST:G    3,0165H");
	asm("JEQ       LL9");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,9H[A0]");

	asm("LL10: BTST:G    3,0165H");
	asm("JEQ       LL10");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0AH[A0]");

	asm("LL11: BTST:G    3,0165H");
	asm("JEQ       LL11");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0BH[A0]");

	asm("LL12: BTST:G    3,0165H");
	asm("JEQ       LL12");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0CH[A0]");

	asm("LL13: BTST:G    3,0165H");
	asm("JEQ       LL13");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0DH[A0]");

	asm("LL14: BTST:G    3,0165H");
	asm("JEQ       LL14");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0EH[A0]");

	asm("LL15: BTST:G    3,0165H");
	asm("JEQ       LL15");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0FH[A0]");

	asm("LL16: BTST:G    3,0165H");
	asm("JEQ       LL16");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,10H[A0]");

	asm("LL17: BTST:G    3,0165H");
	asm("JEQ       LL17");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,11H[A0]");

	asm("LL18: BTST:G    3,0165H");
	asm("JEQ       LL18");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,12H[A0]");

	asm("LL19: BTST:G    3,0165H");
	asm("JEQ       LL19");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,13H[A0]");

	asm("LL20: BTST:G    3,0165H");
	asm("JEQ       LL20");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,14H[A0]");

	asm("LL21: BTST:G    3,0165H");
	asm("JEQ       LL21");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,15H[A0]");

	asm("LL22: BTST:G    3,0165H");
	asm("JEQ       LL22");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,16H[A0]");

	asm("LL23: BTST:G    3,0165H");
	asm("JEQ       LL23");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,17H[A0]");

	asm("LL24: BTST:G    3,0165H");
	asm("JEQ       LL24");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,18H[A0]");

	asm("LL25: BTST:G    3,0165H");
	asm("JEQ       LL25");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,19H[A0]");

	asm("LL26: BTST:G    3,0165H");
	asm("JEQ       LL26");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,1AH[A0]");

	asm("LL27: BTST:G    3,0165H");
	asm("JEQ       LL27");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,1BH[A0]");

	asm("LL28: BTST:G    3,0165H");
	asm("JEQ       LL28");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,1CH[A0]");

	asm("LL29: BTST:G    3,0165H");
	asm("JEQ       LL29");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,1DH[A0]");

	asm("LL30: BTST:G    3,0165H");
	asm("JEQ       LL30");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,1EH[A0]");

	asm("LL31: BTST:G    3,0165H");
	asm("JEQ       LL31");
	asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,1FH[A0]");

#ifdef PORT_CS_BY_SOFTWARE
	/* CS dessert */
	SCI1_CS_DEASSERT();
#endif

	CONTINOUS_REC_DISABLE();

	return TRUE ;
}

/*
 * drv_Flash_WriteData
 * Write data x bytes,which address starts from 'U32FlsAddress'.
 */
BOOLEAN drv_Flash_WriteData(U32 U32FlsAddress, U16 U16DataLength,
		const U8* pU8Data)
{
	U16 U16Index;

	/* Byte number is from 1 to 256 every program command. */
	if ((U16DataLength < (U16) 1) || (U16DataLength > (U16) 256))
	{
		return FALSE ;
	}

	if (((U32FlsAddress + U16DataLength) - (U32) 1) > FLASH_ADD_END)
	{
		return FALSE ;
	}

	/* Make the program command */
	drv_Flash_MakeCommandData(FLASH_CMD_PROGRAM_BYTE_OR_PAGE, U32FlsAddress);

#ifdef PORT_CS_BY_SOFTWARE
	/* CS assert */
	SCI1_CS_ASSERT();
#endif

	/* Segment1: command */
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[0]);
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[1]);
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[2]);
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[3]);

	/* Segment2: data */
	for (U16Index = (U8) 0; U16Index < U16DataLength; U16Index++)
	{
		/* Wait for transmit buffer empty */
		while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
		{
			; /* wait */
		}
		/* Send data */
		Drv_CSI1_SendData(pU8Data[U16Index]);
	}

	/* The last byte transmission period */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	while (DRV_CSI1_IS_TX_COMPLETE() == CSI1_TX_SHIFT_NOT_EMPTY)
	{
		; /* wait */
	}

#ifdef PORT_CS_BY_SOFTWARE
	/* CS dessert */
	SCI1_CS_DEASSERT();
#endif

	return TRUE ;
}

/*
 * drv_Flash_WriteEnable
 */
BOOLEAN drv_Flash_WriteEnable(void)
{
	/* Make the program command */
	drv_Flash_MakeCommandData(FLASH_CMD_PROTECT_W_ENABLE, (U32) 0);

#ifdef PORT_CS_BY_SOFTWARE
	/* CS assert */
	SCI1_CS_ASSERT();
#endif

	/* Segment1: command */
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[0]);

	/* Wait for transmit end */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	while (DRV_CSI1_IS_TX_COMPLETE() == CSI1_TX_SHIFT_NOT_EMPTY)
	{
		; /* wait */
	}

#ifdef PORT_CS_BY_SOFTWARE
	/* CS dessert */
	SCI1_CS_DEASSERT();
#endif

	return TRUE ;
}

/*
 * drv_Flash_ProtectSector
 */
BOOLEAN drv_Flash_ProtectSector(U32 U32FlsAddress)
{
	/* Make the program command */
	drv_Flash_MakeCommandData(FLASH_CMD_PROTECT_SECTOR, U32FlsAddress);

#ifdef PORT_CS_BY_SOFTWARE
	/* CS assert */
	SCI1_CS_ASSERT();
#endif

	/* Segment1: command */
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[0]);
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[1]);
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[2]);
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[3]);

	/* The last byte transmission period */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	while (DRV_CSI1_IS_TX_COMPLETE() == CSI1_TX_SHIFT_NOT_EMPTY)
	{
		; /* wait */
	}

#ifdef PORT_CS_BY_SOFTWARE
	/* CS dessert */
	SCI1_CS_DEASSERT();
#endif

	return TRUE ;
}

/*
 * drv_Flash_UnProtectSector
 */
BOOLEAN drv_Flash_UnProtectSector(U32 U32FlsAddress)
{
	/* Make the program command */
	drv_Flash_MakeCommandData(FLASH_CMD_UNPROTECT_SECTOR, U32FlsAddress);

#ifdef PORT_CS_BY_SOFTWARE
	/* CS assert */
	SCI1_CS_ASSERT();
#endif

	/* Segment1: command */
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[0]);
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[1]);
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[2]);
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[3]);

	/* The last byte transmission period */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	while (DRV_CSI1_IS_TX_COMPLETE() == CSI1_TX_SHIFT_NOT_EMPTY)
	{
		; /* wait */
	}

#ifdef PORT_CS_BY_SOFTWARE
	/* CS dessert */
	SCI1_CS_DEASSERT();
#endif

	return TRUE ;
}

/*
 * drv_Flash_BlockErase4KBytes
 */
BOOLEAN drv_Flash_BlockErase4KBytes(U32 U32FlsAddress)
{
	/* Make the program command */
	drv_Flash_MakeCommandData(FLASH_CMD_ERASE_BLOCK_4K_BYTES, U32FlsAddress);

#ifdef PORT_CS_BY_SOFTWARE
	/* CS assert */
	SCI1_CS_ASSERT();
#endif

	/* Segment1: command */
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[0]);
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[1]);
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[2]);
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[3]);

	/* The last byte transmission period */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	while (DRV_CSI1_IS_TX_COMPLETE() == CSI1_TX_SHIFT_NOT_EMPTY)
	{
		; /* wait */
	}

#ifdef PORT_CS_BY_SOFTWARE
	/* CS dessert */
	SCI1_CS_DEASSERT();
#endif

	return TRUE ;
}

/*
 * drv_Flash_ReadStatusRegister
 */
BOOLEAN drv_Flash_ReadStatusRegister(U8* pU8StatusByte)
{
	/* Make the program command */
	drv_Flash_MakeCommandData(FLASH_CMD_STATUS_READ_STATUS_REG, (U32) 0);

#ifdef PORT_CS_BY_SOFTWARE
	/* CS assert */
	SCI1_CS_ASSERT();
#endif

	/* Segment1: command */
	/* Wait for transmit buffer empty and send */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[0]);

	/* The 1th byte transmission period */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	while (DRV_CSI1_IS_TX_COMPLETE() == CSI1_TX_SHIFT_NOT_EMPTY)
	{
		; /* wait */
	}
	Drv_CSI1_GetReceivesData();

	/* Segment2: Data */

	/* Wait for transmit buffer empty */
	while (DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{
		; /* wait */
	}
	/* Send dummy */
	Drv_CSI1_SendData(FLASH_COMM_SEG2_DUMMY);
	/* Wait for receive buffer full */
	while (DRV_CSI1_IS_RX_BUFFER_FULL() == CSI1_RX_BUFFER_NOT_FULL)
	{
		; /* wait */
	}
	/* Receive data */
	*pU8StatusByte = Drv_CSI1_GetReceivesData();

#if 0
	/* Wait for transmit buffer empty */
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY)
	{};
	/* Send dummy */
	Drv_CSI1_SendData(FLASH_COMM_SEG2_DUMMY);
	/* Wait for receive buffer full */
	while(DRV_CSI1_IS_RX_BUFFER_FULL() == CSI1_RX_BUFFER_NOT_FULL)
	{};
	/* Receive data */
	*pU8StatusByte2 = Drv_CSI1_GetReceivesData();
#endif

#ifdef PORT_CS_BY_SOFTWARE
	/* CS dessert */
	SCI1_CS_DEASSERT();
#endif

	return TRUE ;
}

/*
 * drv_Flash_MakeCommandData
 * Make command and data, format includes:
 *   segment1: Opcode(1 byte) + Address(0 or 3 bytes) + Dummy(0-2 bytes)
 *   segment2: Data(byte number related with on command)
 */
void drv_Flash_MakeCommandData(U8 U8CommandType, U32 U32FlsAddress)
{
	StrFlsCmdReadArray2* pStrFlsCmdReadArray2;
	StrFlsCmdProgramBytePage* pStrFlsCmdProgramBytePage;
	StrFlsCmdWriteEnable* pStrFlsCmdWriteEnable;
	StrFlsCmdWriteDisable* pStrFlsCmdWriteDisable;
	StrFlsCmdProtectSector* pStrFlsCmdProtectSector;
	StrFlsCmdUnProtectSector* pStrFlsCmdUnProtectSector;
	StrFlsCmdBlockErase4KBytes* pStrFlsCmdBlockErase4KBytes;
	StrFlsCmdReadStatusRegister* pStrFlsCmdReadStatusRegister;

	switch (U8CommandType)
	{
	case FLASH_CMD_READ_ARRAY_2 :
		pStrFlsCmdReadArray2 = (StrFlsCmdReadArray2*) U8Segment1CmdBuffer;
		/* Segment1(command) */
		pStrFlsCmdReadArray2->U8OperationCode = FLASH_CMD_READ_ARRAY_2;
		pStrFlsCmdReadArray2->U8AddHigh = (U8) (U32FlsAddress >> 16);
		pStrFlsCmdReadArray2->U8AddMid = (U8) (U32FlsAddress >> 8);
		pStrFlsCmdReadArray2->U8AddLow = (U8) U32FlsAddress;
		pStrFlsCmdReadArray2->U8Dummy1 = FLASH_COMM_SEG1_DUMMY;

		/* Segment2(data) */
		break;
	case FLASH_CMD_PROGRAM_BYTE_OR_PAGE :
		pStrFlsCmdProgramBytePage =
				(StrFlsCmdProgramBytePage*) U8Segment1CmdBuffer;
		/* Segment1(command) */
		pStrFlsCmdProgramBytePage->U8OperationCode =
		FLASH_CMD_PROGRAM_BYTE_OR_PAGE;
		pStrFlsCmdProgramBytePage->U8AddHigh = (U8) (U32FlsAddress >> 16);
		pStrFlsCmdProgramBytePage->U8AddMid = (U8) (U32FlsAddress >> 8);
		pStrFlsCmdProgramBytePage->U8AddLow = (U8) U32FlsAddress;

		/* Segment2(data) */
		break;

	case FLASH_CMD_PROTECT_W_ENABLE :
		pStrFlsCmdWriteEnable = (StrFlsCmdWriteEnable*) U8Segment1CmdBuffer;
		/* Segment1(command) */
		pStrFlsCmdWriteEnable->U8OperationCode = FLASH_CMD_PROTECT_W_ENABLE;

		/* Segment2(data) */
		break;
	case FLASH_CMD_PROTECT_W_DISABLE :
		pStrFlsCmdWriteDisable = (StrFlsCmdWriteDisable*) U8Segment1CmdBuffer;
		/* Segment1(command) */
		pStrFlsCmdWriteDisable->U8OperationCode = FLASH_CMD_PROTECT_W_DISABLE;

		/* Segment2(data) */
		break;
	case FLASH_CMD_PROTECT_SECTOR :
		pStrFlsCmdProtectSector = (StrFlsCmdProtectSector*) U8Segment1CmdBuffer;
		/* Segment1(command) */
		pStrFlsCmdProtectSector->U8OperationCode = FLASH_CMD_PROTECT_SECTOR;
		pStrFlsCmdProtectSector->U8AddHigh = (U8) (U32FlsAddress >> 16);
		pStrFlsCmdProtectSector->U8AddMid = (U8) (U32FlsAddress >> 8);
		pStrFlsCmdProtectSector->U8AddLow = (U8) U32FlsAddress;
		break;
	case FLASH_CMD_UNPROTECT_SECTOR :
		pStrFlsCmdUnProtectSector =
				(StrFlsCmdUnProtectSector*) U8Segment1CmdBuffer;
		/* Segment1(command) */
		pStrFlsCmdUnProtectSector->U8OperationCode = FLASH_CMD_UNPROTECT_SECTOR;
		pStrFlsCmdUnProtectSector->U8AddHigh = (U8) (U32FlsAddress >> 16);
		pStrFlsCmdUnProtectSector->U8AddMid = (U8) (U32FlsAddress >> 8);
		pStrFlsCmdUnProtectSector->U8AddLow = (U8) U32FlsAddress;
		break;
	case FLASH_CMD_ERASE_BLOCK_4K_BYTES :
		pStrFlsCmdBlockErase4KBytes =
				(StrFlsCmdBlockErase4KBytes*) U8Segment1CmdBuffer;
		/* Segment1(command) */
		pStrFlsCmdBlockErase4KBytes->U8OperationCode =
		FLASH_CMD_ERASE_BLOCK_4K_BYTES;
		pStrFlsCmdBlockErase4KBytes->U8AddHigh = (U8) (U32FlsAddress >> 16);
		pStrFlsCmdBlockErase4KBytes->U8AddMid = (U8) (U32FlsAddress >> 8);
		pStrFlsCmdBlockErase4KBytes->U8AddLow = (U8) U32FlsAddress;
		break;
	case FLASH_CMD_STATUS_READ_STATUS_REG :
		pStrFlsCmdReadStatusRegister =
				(StrFlsCmdReadStatusRegister*) U8Segment1CmdBuffer;
		/* Segment1(command) */
		pStrFlsCmdReadStatusRegister->U8OperationCode =
		FLASH_CMD_STATUS_READ_STATUS_REG;
		break;
	default:
		break;
	}
}
/* End of file */
