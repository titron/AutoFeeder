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
 * File Name    : drv_flash.c
 * Abstract     : driver of serial flash
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AE1-LF demo board
 * Description  : This is driver of flash.
 * Operation    : none
 * Limitation   : This file can be only used as sample code for AE1-LF.
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "basictype.h"
#include "config.h"
#include "driver_flash.h"
#include "driver_csi1.h"

/*****************************************************************************
 Private variables and functions
 *****************************************************************************/
static U8 	U8Segment1CmdBuffer[6];		/* Segment1(command) buffer */
static void Drv_Flash_MakeCommandData(U8 U8CommandType, U32 U32FlsAddress);

/*****************************************************************************
 * ID                :
 * Outline           : Read any length data(less than buffer length)
 * Include           : none
 * Declaration       : BOOLEAN Drv_Flash_ReadData(U32 U32FlsAddress, U16 U16DataLength,
 * 												 U8* pU8Data)
 * Description       : Read data x bytes,which address starts from 'U32FlsAddress'.
 * Argument          :
 * Return Value      : TRUE  - Operation have been accepted.
 * 					   FALSE - Operation is prohibited.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN Drv_Flash_ReadData(U32 U32FlsAddress, U16 U16DataLength, U8* pU8Data)
{
	U16 U16Index = (U16)0;
#if 0
	/* Note: Because this routine will be loaded frequently, to save the time,
             remove the check. Upper layer ensure the validity. */
	if(U16DataLength == (U16)0){
		return FALSE;
	}

	/* Note: Because this routine will be loaded frequently, to save the time,
             remove the check. Upper layer ensure the validity. */
	if((U32FlsAddress + U16DataLength - (U32)1) > FLASH_ADD_END){
		return FALSE;
	}
#endif

	/* Make the read command */
	Drv_Flash_MakeCommandData(FLASH_CMD_READ_ARRAY_2, U32FlsAddress);

#ifdef PORT_CS_BY_SOFTWARE
	/* CS assert */
	SCI1_CS_ASSERT();
#endif

	/* Segment1: command */
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[0]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[1]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[2]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[3]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[4]);

	/* Segment2: data */
	/* The 5th byte transmission period */
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	while(DRV_CSI1_IS_TX_COMPLETE() == CSI1_TX_SHIFT_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_GetReceivesData();

	for(U16Index = (U8)0; U16Index < U16DataLength; U16Index++){
#if 0
		/* Wait for transmit buffer empty */ 
		while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 			; /* wait */
		}
#endif
		/* Send dummy */ 
		Drv_CSI1_SendData(FLASH_COMM_SEG2_DUMMY);
		/* Wait for receive buffer full */ 
		while(DRV_CSI1_IS_RX_BUFFER_FULL() == CSI1_RX_BUFFER_NOT_FULL){
 			; /* wait */
		}
		/* Receive data */ 
		pU8Data[U16Index] = Drv_CSI1_GetReceivesData();
	}

#ifdef PORT_CS_BY_SOFTWARE
	/* CS dessert */
	SCI1_CS_DEASSERT();
#endif

	return TRUE;
}

/*****************************************************************************
 * ID                :
 * Outline           : Read the fixed length(32bytes) data
 * Include           : none
 * Declaration       : BOOLEAN Drv_Flash_Read32BytesData(U32 U32FlsAddress,
 * 												 U8* pU8Data)
 * Description       : Read data 32 bytes,which address starts from 'U32FlsAddress'.
 * Argument          :
 * Return Value      : TRUE  - Operation have been accepted.
 * 					   FALSE - Operation is prohibited.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN Drv_Flash_Read32BytesData(U32 U32FlsAddress, U8* pU8Data)
{
#if 0
	/* Note: Because this routine will be loaded frequently, to save the time,
             remove the check. Upper layer ensure the validity. */
	if(U16DataLength == (U16)0){
		return FALSE;
	}

	/* Note: Because this routine will be loaded frequently, to save the time,
             remove the check. Upper layer ensure the validity. */
	if((U32FlsAddress + U16DataLength - (U32)1) > FLASH_ADD_END){
		return FALSE;
	}
#endif

	/* Make the read command, data length is fixed 16 bytes */
	Drv_Flash_MakeCommandData(FLASH_CMD_READ_ARRAY_2, U32FlsAddress);

#ifdef PORT_CS_BY_SOFTWARE
	/* CS assert */
	SCI1_CS_ASSERT();
#endif

	/* Segment1: command */
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[0]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[1]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[2]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[3]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[4]);

	/* enable continous receive */
	CONTINOUS_REC_ENABLE();

	/* Segment2: data */
	/* The 5th byte transmission period */
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	while(DRV_CSI1_IS_TX_COMPLETE() == CSI1_TX_SHIFT_NOT_EMPTY){
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

	return TRUE;
}

#if 0
/*****************************************************************************
 * ID                :
 * Outline           : Read data
 * Include           : none
 * Declaration       : BOOLEAN Drv_Flash_Read16BytesData(U32 U32FlsAddress,
 * 												 U8* pU8Data)
 * Description       : Read data 16 bytes,which address starts from 'U32FlsAddress'.
 * Argument          :
 * Return Value      : TRUE  - Operation have been accepted.
 * 					   FALSE - Operation is prohibited.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN Drv_Flash_Read16BytesData(U32 U32FlsAddress, U8* pU8Data)
{
	/* Note: Because this routine will be loaded frequently, to save the time,
             remove the check. Upper layer ensure the validity. */
	//if(U16DataLength == (U16)0){
	//	return FALSE;
	//}

	/* Note: Because this routine will be loaded frequently, to save the time,
             remove the check. Upper layer ensure the validity. */
	//if((U32FlsAddress + U16DataLength - (U32)1) > FLASH_ADD_END){
	//	return FALSE;
	//}

	/* Make the read command, data length is fixed 16 bytes */
	Drv_Flash_MakeCommandData(FLASH_CMD_READ_ARRAY_2, U32FlsAddress);

#ifdef PORT_CS_BY_SOFTWARE
	/* CS assert */
	SCI1_CS_ASSERT();
#endif

	/* Segment1: command */
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){};
	Drv_CSI1_SendData(U8Segment1CmdBuffer[0]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){};
	Drv_CSI1_SendData(U8Segment1CmdBuffer[1]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){};
	Drv_CSI1_SendData(U8Segment1CmdBuffer[2]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){};
	Drv_CSI1_SendData(U8Segment1CmdBuffer[3]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){};
	Drv_CSI1_SendData(U8Segment1CmdBuffer[4]);

	/* enable continous receive */
	CONTINOUS_REC_ENABLE();

	/* Segment2: data */
	/* The 5th byte transmission period */
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){};
	while(DRV_CSI1_IS_TX_COMPLETE() == CSI1_TX_SHIFT_NOT_EMPTY){};
	Drv_CSI1_GetReceivesData();

    asm("MOV.W:G   -2H[FB],A0");

    asm("LM0: BTST:G    3,0165H");
    asm("JEQ       LM0");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,[A0]");

    asm("LM1: BTST:G    3,0165H");
    asm("JEQ       LM1");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,1H[A0]");

    asm("LM2: BTST:G    3,0165H");
    asm("JEQ       LM2");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,2H[A0]");

    asm("LM3: BTST:G    3,0165H");
    asm("JEQ       LM3");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,3H[A0]");

    asm("LM4: BTST:G    3,0165H");
    asm("JEQ       LM4");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,4H[A0]");

    asm("LM5: BTST:G    3,0165H");
    asm("JEQ       LM5");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,5H[A0]");

    asm("LM6: BTST:G    3,0165H");
    asm("JEQ       LM6");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,6H[A0]");

    asm("LM7: BTST:G    3,0165H");
    asm("JEQ       LM7");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,7H[A0]");

    asm("LM8: BTST:G    3,0165H");
    asm("JEQ       LM8");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,8H[A0]");

    asm("LM9: BTST:G    3,0165H");
    asm("JEQ       LM9");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,9H[A0]");

    asm("LM10: BTST:G    3,0165H");
    asm("JEQ       LM10");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0AH[A0]");

    asm("LM11: BTST:G    3,0165H");
    asm("JEQ       LM11");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0BH[A0]");

    asm("LM12: BTST:G    3,0165H");
    asm("JEQ       LM12");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0CH[A0]");

    asm("LM13: BTST:G    3,0165H");
    asm("JEQ       LM13");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0DH[A0]");

    asm("LM14: BTST:G    3,0165H");
    asm("JEQ       LM14");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0EH[A0]");

    asm("LM15: BTST:G    3,0165H");
    asm("JEQ       LM15");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0FH[A0]");

#ifdef PORT_CS_BY_SOFTWARE
	/* CS dessert */
	SCI1_CS_DEASSERT();
#endif

	CONTINOUS_REC_DISABLE();

	return TRUE;
}

/*****************************************************************************
 * ID                :
 * Outline           : Read data
 * Include           : none
 * Declaration       : BOOLEAN Drv_Flash_Read48BytesData(U32 U32FlsAddress,
 * 												 U8* pU8Data)
 * Description       : Read 48 bytes data,which address starts from 'U32FlsAddress'.
 * Argument          :
 * Return Value      : TRUE  - Operation have been accepted.
 * 					   FALSE - Operation is prohibited.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN Drv_Flash_Read48BytesData(U32 U32FlsAddress, U8* pU8Data)
{
	/* Note: Because this routine will be loaded frequently, to save the time,
             remove the check. Upper layer ensure the validity. */
	//if(U16DataLength == (U16)0){
	//	return FALSE;
	//}

	/* Note: Because this routine will be loaded frequently, to save the time,
             remove the check. Upper layer ensure the validity. */
	//if((U32FlsAddress + U16DataLength - (U32)1) > FLASH_ADD_END){
	//	return FALSE;
	//}

	/* Make the read command, data length is fixed 16 bytes */
	Drv_Flash_MakeCommandData(FLASH_CMD_READ_ARRAY_2, U32FlsAddress);

#ifdef PORT_CS_BY_SOFTWARE
	/* CS assert */
	SCI1_CS_ASSERT();
#endif

	/* Segment1: command */
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){};
	Drv_CSI1_SendData(U8Segment1CmdBuffer[0]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){};
	Drv_CSI1_SendData(U8Segment1CmdBuffer[1]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){};
	Drv_CSI1_SendData(U8Segment1CmdBuffer[2]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){};
	Drv_CSI1_SendData(U8Segment1CmdBuffer[3]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){};
	Drv_CSI1_SendData(U8Segment1CmdBuffer[4]);

	/* enable continous receive */
	CONTINOUS_REC_ENABLE();

	/* Segment2: data */
	/* The 5th byte transmission period */
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){};
	while(DRV_CSI1_IS_TX_COMPLETE() == CSI1_TX_SHIFT_NOT_EMPTY){};
	Drv_CSI1_GetReceivesData();

    asm("MOV.W:G   -2H[FB],A0");

    asm("LN0: BTST:G    3,0165H");
    asm("JEQ       LN0");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,[A0]");

    asm("LN1: BTST:G    3,0165H");
    asm("JEQ       LN1");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,1H[A0]");

    asm("LN2: BTST:G    3,0165H");
    asm("JEQ       LN2");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,2H[A0]");

    asm("LN3: BTST:G    3,0165H");
    asm("JEQ       LN3");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,3H[A0]");

    asm("LN4: BTST:G    3,0165H");
    asm("JEQ       LN4");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,4H[A0]");

    asm("LN5: BTST:G    3,0165H");
    asm("JEQ       LN5");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,5H[A0]");

    asm("LN6: BTST:G    3,0165H");
    asm("JEQ       LN6");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,6H[A0]");

    asm("LN7: BTST:G    3,0165H");
    asm("JEQ       LN7");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,7H[A0]");

    asm("LN8: BTST:G    3,0165H");
    asm("JEQ       LN8");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,8H[A0]");

    asm("LN9: BTST:G    3,0165H");
    asm("JEQ       LN9");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,9H[A0]");

    asm("LN10: BTST:G    3,0165H");
    asm("JEQ       LN10");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0AH[A0]");

    asm("LN11: BTST:G    3,0165H");
    asm("JEQ       LN11");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0BH[A0]");

    asm("LN12: BTST:G    3,0165H");
    asm("JEQ       LN12");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0CH[A0]");

    asm("LN13: BTST:G    3,0165H");
    asm("JEQ       LN13");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0DH[A0]");

    asm("LN14: BTST:G    3,0165H");
    asm("JEQ       LN14");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0EH[A0]");

    asm("LN15: BTST:G    3,0165H");
    asm("JEQ       LN15");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0FH[A0]");

    asm("LN16: BTST:G    3,0165H");
    asm("JEQ       LN16");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,10H[A0]");

    asm("LN17: BTST:G    3,0165H");
    asm("JEQ       LN17");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,11H[A0]");

    asm("LN18: BTST:G    3,0165H");
    asm("JEQ       LN18");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,12H[A0]");

    asm("LN19: BTST:G    3,0165H");
    asm("JEQ       LN19");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,13H[A0]");

    asm("LN20: BTST:G    3,0165H");
    asm("JEQ       LN20");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,14H[A0]");

    asm("LN21: BTST:G    3,0165H");
    asm("JEQ       LN21");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,15H[A0]");

    asm("LN22: BTST:G    3,0165H");
    asm("JEQ       LN22");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,16H[A0]");

    asm("LN23: BTST:G    3,0165H");
    asm("JEQ       LN23");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,17H[A0]");

    asm("LN24: BTST:G    3,0165H");
    asm("JEQ       LN24");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,18H[A0]");

    asm("LN25: BTST:G    3,0165H");
    asm("JEQ       LN25");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,19H[A0]");

    asm("LN26: BTST:G    3,0165H");
    asm("JEQ       LN26");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,1AH[A0]");

    asm("LN27: BTST:G    3,0165H");
    asm("JEQ       LN27");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,1BH[A0]");

    asm("LN28: BTST:G    3,0165H");
    asm("JEQ       LN28");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,1CH[A0]");

    asm("LN29: BTST:G    3,0165H");
    asm("JEQ       LN29");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,1DH[A0]");

    asm("LN30: BTST:G    3,0165H");
    asm("JEQ       LN30");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,1EH[A0]");

    asm("LN31: BTST:G    3,0165H");
    asm("JEQ       LN31");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,1FH[A0]");

    asm("LN32: BTST:G    3,0165H");
    asm("JEQ       LN32");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,20H[A0]");

    asm("LN33: BTST:G    3,0165H");
    asm("JEQ       LN33");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,21H[A0]");

    asm("LN34: BTST:G    3,0165H");
    asm("JEQ       LN34");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,22H[A0]");

    asm("LN35: BTST:G    3,0165H");
    asm("JEQ       LN35");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,23H[A0]");

    asm("LN36: BTST:G    3,0165H");
    asm("JEQ       LN36");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,24H[A0]");

    asm("LN37: BTST:G    3,0165H");
    asm("JEQ       LN37");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,25H[A0]");

    asm("LN38: BTST:G    3,0165H");
    asm("JEQ       LN38");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,26H[A0]");

    asm("LN39: BTST:G    3,0165H");
    asm("JEQ       LN39");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,27H[A0]");

    asm("LN40: BTST:G    3,0165H");
    asm("JEQ       LN40");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,28H[A0]");

    asm("LN41: BTST:G    3,0165H");
    asm("JEQ       LN41");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,29H[A0]");

    asm("LN42: BTST:G    3,0165H");
    asm("JEQ       LN42");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,2AH[A0]");

    asm("LN43: BTST:G    3,0165H");
    asm("JEQ       LN43");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,2BH[A0]");

    asm("LN44: BTST:G    3,0165H");
    asm("JEQ       LN44");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,2CH[A0]");

    asm("LN45: BTST:G    3,0165H");
    asm("JEQ       LN45");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,2DH[A0]");

    asm("LN46: BTST:G    3,0165H");
    asm("JEQ       LN46");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,2EH[A0]");

    asm("LN47: BTST:G    3,0165H");
    asm("JEQ       LN47");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,2FH[A0]");

#ifdef PORT_CS_BY_SOFTWARE
	/* CS dessert */
	SCI1_CS_DEASSERT();
#endif

	CONTINOUS_REC_DISABLE();

	return TRUE;
}

/*****************************************************************************
 * ID                :
 * Outline           : Read data
 * Include           : none
 * Declaration       : BOOLEAN Drv_Flash_Read64BytesData(U32 U32FlsAddress,
 * 												 U8* pU8Data)
 * Description       : Read 64 bytes data,which address starts from 'U32FlsAddress'.
 * Argument          :
 * Return Value      : TRUE  - Operation have been accepted.
 * 					   FALSE - Operation is prohibited.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN Drv_Flash_Read64BytesData(U32 U32FlsAddress, U8* pU8Data)
{
	/* Note: Because this routine will be loaded frequently, to save the time,
             remove the check. Upper layer ensure the validity. */
	//if(U16DataLength == (U16)0){
	//	return FALSE;
	//}

	/* Note: Because this routine will be loaded frequently, to save the time,
             remove the check. Upper layer ensure the validity. */
	//if((U32FlsAddress + U16DataLength - (U32)1) > FLASH_ADD_END){
	//	return FALSE;
	//}

	/* Make the read command, data length is fixed 16 bytes */
	Drv_Flash_MakeCommandData(FLASH_CMD_READ_ARRAY_2, U32FlsAddress);

#ifdef PORT_CS_BY_SOFTWARE
	/* CS assert */
	SCI1_CS_ASSERT();
#endif

	/* Segment1: command */
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){};
	Drv_CSI1_SendData(U8Segment1CmdBuffer[0]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){};
	Drv_CSI1_SendData(U8Segment1CmdBuffer[1]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){};
	Drv_CSI1_SendData(U8Segment1CmdBuffer[2]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){};
	Drv_CSI1_SendData(U8Segment1CmdBuffer[3]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){};
	Drv_CSI1_SendData(U8Segment1CmdBuffer[4]);

	/* enable continous receive */
	CONTINOUS_REC_ENABLE();

	/* Segment2: data */
	/* The 5th byte transmission period */
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){};
	while(DRV_CSI1_IS_TX_COMPLETE() == CSI1_TX_SHIFT_NOT_EMPTY){};
	Drv_CSI1_GetReceivesData();

    asm("MOV.W:G   -2H[FB],A0");

    asm("LH0: BTST:G    3,0165H");
    asm("JEQ       LH0");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,[A0]");

    asm("LH1: BTST:G    3,0165H");
    asm("JEQ       LH1");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,1H[A0]");

    asm("LH2: BTST:G    3,0165H");
    asm("JEQ       LH2");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,2H[A0]");

    asm("LH3: BTST:G    3,0165H");
    asm("JEQ       LH3");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,3H[A0]");

    asm("LH4: BTST:G    3,0165H");
    asm("JEQ       LH4");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,4H[A0]");

    asm("LH5: BTST:G    3,0165H");
    asm("JEQ       LH5");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,5H[A0]");

    asm("LH6: BTST:G    3,0165H");
    asm("JEQ       LH6");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,6H[A0]");

    asm("LH7: BTST:G    3,0165H");
    asm("JEQ       LH7");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,7H[A0]");

    asm("LH8: BTST:G    3,0165H");
    asm("JEQ       LH8");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,8H[A0]");

    asm("LH9: BTST:G    3,0165H");
    asm("JEQ       LH9");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,9H[A0]");

    asm("LH10: BTST:G    3,0165H");
    asm("JEQ       LH10");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0AH[A0]");

    asm("LH11: BTST:G    3,0165H");
    asm("JEQ       LH11");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0BH[A0]");

    asm("LH12: BTST:G    3,0165H");
    asm("JEQ       LH12");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0CH[A0]");

    asm("LH13: BTST:G    3,0165H");
    asm("JEQ       LH13");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0DH[A0]");

    asm("LH14: BTST:G    3,0165H");
    asm("JEQ       LH14");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0EH[A0]");

    asm("LH15: BTST:G    3,0165H");
    asm("JEQ       LH15");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,0FH[A0]");

    asm("LH16: BTST:G    3,0165H");
    asm("JEQ       LH16");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,10H[A0]");

    asm("LH17: BTST:G    3,0165H");
    asm("JEQ       LH17");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,11H[A0]");

    asm("LH18: BTST:G    3,0165H");
    asm("JEQ       LH18");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,12H[A0]");

    asm("LH19: BTST:G    3,0165H");
    asm("JEQ       LH19");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,13H[A0]");

    asm("LH20: BTST:G    3,0165H");
    asm("JEQ       LH20");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,14H[A0]");

    asm("LH21: BTST:G    3,0165H");
    asm("JEQ       LH21");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,15H[A0]");

    asm("LH22: BTST:G    3,0165H");
    asm("JEQ       LH22");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,16H[A0]");

    asm("LH23: BTST:G    3,0165H");
    asm("JEQ       LH23");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,17H[A0]");

    asm("LH24: BTST:G    3,0165H");
    asm("JEQ       LH24");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,18H[A0]");

    asm("LH25: BTST:G    3,0165H");
    asm("JEQ       LH25");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,19H[A0]");

    asm("LH26: BTST:G    3,0165H");
    asm("JEQ       LH26");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,1AH[A0]");

    asm("LH27: BTST:G    3,0165H");
    asm("JEQ       LH27");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,1BH[A0]");

    asm("LH28: BTST:G    3,0165H");
    asm("JEQ       LH28");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,1CH[A0]");

    asm("LH29: BTST:G    3,0165H");
    asm("JEQ       LH29");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,1DH[A0]");

    asm("LH30: BTST:G    3,0165H");
    asm("JEQ       LH30");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,1EH[A0]");

    asm("LH31: BTST:G    3,0165H");
    asm("JEQ       LH31");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,1FH[A0]");

    asm("LH32: BTST:G    3,0165H");
    asm("JEQ       LH32");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,20H[A0]");

    asm("LH33: BTST:G    3,0165H");
    asm("JEQ       LH33");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,21H[A0]");

    asm("LH34: BTST:G    3,0165H");
    asm("JEQ       LH34");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,22H[A0]");

    asm("LH35: BTST:G    3,0165H");
    asm("JEQ       LH35");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,23H[A0]");

    asm("LH36: BTST:G    3,0165H");
    asm("JEQ       LH36");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,24H[A0]");

    asm("LH37: BTST:G    3,0165H");
    asm("JEQ       LH37");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,25H[A0]");

    asm("LH38: BTST:G    3,0165H");
    asm("JEQ       LH38");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,26H[A0]");

    asm("LH39: BTST:G    3,0165H");
    asm("JEQ       LH39");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,27H[A0]");

    asm("LH40: BTST:G    3,0165H");
    asm("JEQ       LH40");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,28H[A0]");

    asm("LH41: BTST:G    3,0165H");
    asm("JEQ       LH41");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,29H[A0]");

    asm("LH42: BTST:G    3,0165H");
    asm("JEQ       LH42");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,2AH[A0]");

    asm("LH43: BTST:G    3,0165H");
    asm("JEQ       LH43");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,2BH[A0]");

    asm("LH44: BTST:G    3,0165H");
    asm("JEQ       LH44");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,2CH[A0]");

    asm("LH45: BTST:G    3,0165H");
    asm("JEQ       LH45");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,2DH[A0]");

    asm("LH46: BTST:G    3,0165H");
    asm("JEQ       LH46");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,2EH[A0]");

    asm("LH47: BTST:G    3,0165H");
    asm("JEQ       LH47");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,2FH[A0]");

    asm("LH48: BTST:G    3,0165H");
    asm("JEQ       LH48");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,30H[A0]");

    asm("LH49: BTST:G    3,0165H");
    asm("JEQ       LH49");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,31H[A0]");

    asm("LH50: BTST:G    3,0165H");
    asm("JEQ       LH50");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,32H[A0]");

    asm("LH51: BTST:G    3,0165H");
    asm("JEQ       LH51");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,33H[A0]");

    asm("LH52: BTST:G    3,0165H");
    asm("JEQ       LH52");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,34H[A0]");

    asm("LH53: BTST:G    3,0165H");
    asm("JEQ       LH53");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,35H[A0]");

    asm("LH54: BTST:G    3,0165H");
    asm("JEQ       LH54");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,36H[A0]");

    asm("LH55: BTST:G    3,0165H");
    asm("JEQ       LH55");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,37H[A0]");

    asm("LH56: BTST:G    3,0165H");
    asm("JEQ       LH56");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,38H[A0]");

    asm("LH57: BTST:G    3,0165H");
    asm("JEQ       LH57");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,39H[A0]");

    asm("LH58: BTST:G    3,0165H");
    asm("JEQ       LH58");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,3AH[A0]");

    asm("LH59: BTST:G    3,0165H");
    asm("JEQ       LH59");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,3BH[A0]");

    asm("LH60: BTST:G    3,0165H");
    asm("JEQ       LH60");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,3CH[A0]");

    asm("LH61: BTST:G    3,0165H");
    asm("JEQ       LH61");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,3DH[A0]");

    asm("LH62: BTST:G    3,0165H");
    asm("JEQ       LH62");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,3EH[A0]");

    asm("LH63: BTST:G    3,0165H");
    asm("JEQ       LH63");
    asm("MOV.W:G   0166H,A1");
	asm("MOV.B:G   A1,3FH[A0]");

#ifdef PORT_CS_BY_SOFTWARE
	/* CS dessert */
	SCI1_CS_DEASSERT();
#endif

	CONTINOUS_REC_DISABLE();

	return TRUE;
}
#endif

/*****************************************************************************
 * ID                :
 * Outline           : Write any length data(less than buffer length)
 * Include           : none
 * Declaration       : Drv_Flash_WriteData(U32 U32FlsAddress, U16 U16DataLength,
 *                                        U8* pU8Data)
 * Description       : Write data x bytes,which address starts from 'U32FlsAddress'.
 * Argument          :
 * Return Value      :  TRUE  - Operation have been accepted.
 * 						FALSE - Operation is prohibited.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN Drv_Flash_WriteData(U32 U32FlsAddress, U16 U16DataLength, const U8* pU8Data)
{
	U16 U16Index;

	/* Byte number is from 1 to 256 every program command. */
	if((U16DataLength < (U16)1) || (U16DataLength > (U16)256)){
		return FALSE;
	}

	if(((U32FlsAddress + U16DataLength) - (U32)1) > FLASH_ADD_END){
		return FALSE;
	}

	/* Make the program command */
	Drv_Flash_MakeCommandData(FLASH_CMD_PROGRAM_BYTE_OR_PAGE, U32FlsAddress);

#ifdef PORT_CS_BY_SOFTWARE
	/* CS assert */
	SCI1_CS_ASSERT();
#endif

	/* Segment1: command */
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[0]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[1]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[2]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[3]);

	/* Segment2: data */
	for(U16Index = (U8)0; U16Index < U16DataLength; U16Index++){
		/* Wait for transmit buffer empty */ 
		while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 			; /* wait */
		}
		/* Send data */ 
		Drv_CSI1_SendData(pU8Data[U16Index]);
	}

	/* The last byte transmission period */
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	while(DRV_CSI1_IS_TX_COMPLETE() == CSI1_TX_SHIFT_NOT_EMPTY){
 		; /* wait */
	}

#ifdef PORT_CS_BY_SOFTWARE
	/* CS dessert */
	SCI1_CS_DEASSERT();
#endif

	return TRUE;
}

/*****************************************************************************
 * ID                :
 * Outline           : Write enable
 * Include           : none
 * Declaration       : Drv_Flash_WriteEnable(void)
 * Description       : Write enable
 * Argument          :
 * Return Value      :  TRUE  - Operation have been accepted.
 * 						FALSE - Operation is prohibited.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN Drv_Flash_WriteEnable(void)
{
	/* Make the program command */
	Drv_Flash_MakeCommandData(FLASH_CMD_PROTECT_W_ENABLE, (U32)0);

#ifdef PORT_CS_BY_SOFTWARE
	/* CS assert */
	SCI1_CS_ASSERT();
#endif

	/* Segment1: command */
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[0]);

	/* Wait for transmit end */
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	while(DRV_CSI1_IS_TX_COMPLETE() == CSI1_TX_SHIFT_NOT_EMPTY){
 		; /* wait */
	}

#ifdef PORT_CS_BY_SOFTWARE
	/* CS dessert */
	SCI1_CS_DEASSERT();
#endif

	return TRUE;
}

#if 0
/*****************************************************************************
 * ID                :
 * Outline           : Write disable
 * Include           : none
 * Declaration       : Drv_Flash_WriteDisable(void)
 * Description       : Write disable
 * Argument          :
 * Return Value      :  TRUE  - Operation have been accepted.
 * 						FALSE - Operation is prohibited.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN Drv_Flash_WriteDisable(void)
{
	/* Make the program command */
	Drv_Flash_MakeCommandData(FLASH_CMD_PROTECT_W_DISABLE, (U32)0);

#ifdef PORT_CS_BY_SOFTWARE
	/* CS assert */
	SCI1_CS_ASSERT();
#endif

	/* Segment1: command */
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){};
	Drv_CSI1_SendData(U8Segment1CmdBuffer[0]);

	/* Wait for transmit end */
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){};
	while(DRV_CSI1_IS_TX_COMPLETE() == CSI1_TX_SHIFT_NOT_EMPTY){};

#ifdef PORT_CS_BY_SOFTWARE
	/* CS dessert */
	SCI1_CS_DEASSERT();
#endif

	return TRUE;
}
#endif

/*****************************************************************************
 * ID                :
 * Outline           : Protect sector
 * Include           : none
 * Declaration       : BOOLEAN Drv_Flash_ProtectSector(U32 U32FlsAddress)
 * Description       : 
 * Argument          :
 * Return Value      :  TRUE  - Operation have been accepted.
 * 						FALSE - Operation is prohibited.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN Drv_Flash_ProtectSector(U32 U32FlsAddress)
{
	/* Make the program command */
	Drv_Flash_MakeCommandData(FLASH_CMD_PROTECT_SECTOR, U32FlsAddress);

#ifdef PORT_CS_BY_SOFTWARE
	/* CS assert */
	SCI1_CS_ASSERT();
#endif

	/* Segment1: command */
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[0]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[1]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[2]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[3]);

	/* The last byte transmission period */
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	while(DRV_CSI1_IS_TX_COMPLETE() == CSI1_TX_SHIFT_NOT_EMPTY){
 		; /* wait */
	}

#ifdef PORT_CS_BY_SOFTWARE
	/* CS dessert */
	SCI1_CS_DEASSERT();
#endif

	return TRUE;
}

/*****************************************************************************
 * ID                :
 * Outline           : UnProtect sector
 * Include           : none
 * Declaration       : BOOLEAN Drv_Flash_UnProtectSector(U32 U32FlsAddress)
 * Description       : 
 * Argument          :
 * Return Value      :  TRUE  - Operation have been accepted.
 * 						FALSE - Operation is prohibited.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN Drv_Flash_UnProtectSector(U32 U32FlsAddress)
{
	/* Make the program command */
	Drv_Flash_MakeCommandData(FLASH_CMD_UNPROTECT_SECTOR, U32FlsAddress);

#ifdef PORT_CS_BY_SOFTWARE
	/* CS assert */
	SCI1_CS_ASSERT();
#endif

	/* Segment1: command */
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[0]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[1]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[2]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[3]);

	/* The last byte transmission period */
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	while(DRV_CSI1_IS_TX_COMPLETE() == CSI1_TX_SHIFT_NOT_EMPTY){
 		; /* wait */
	}

#ifdef PORT_CS_BY_SOFTWARE
	/* CS dessert */
	SCI1_CS_DEASSERT();
#endif

	return TRUE;
}

/*****************************************************************************
 * ID                :
 * Outline           : Block erase(4K Bytes)
 * Include           : none
 * Declaration       : BOOLEAN Drv_Flash_BlockErase4KBytes(U32 U32FlsAddress)
 * Description       : 
 * Argument          :
 * Return Value      :  TRUE  - Operation have been accepted.
 * 						FALSE - Operation is prohibited.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN Drv_Flash_BlockErase4KBytes(U32 U32FlsAddress)
{
	/* Make the program command */
	Drv_Flash_MakeCommandData(FLASH_CMD_ERASE_BLOCK_4K_BYTES, U32FlsAddress);

#ifdef PORT_CS_BY_SOFTWARE
	/* CS assert */
	SCI1_CS_ASSERT();
#endif

	/* Segment1: command */
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[0]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[1]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[2]);
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[3]);

	/* The last byte transmission period */
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	while(DRV_CSI1_IS_TX_COMPLETE() == CSI1_TX_SHIFT_NOT_EMPTY){
 		; /* wait */
	}

#ifdef PORT_CS_BY_SOFTWARE
	/* CS dessert */
	SCI1_CS_DEASSERT();
#endif

	return TRUE;
}

/*****************************************************************************
 * ID                :
 * Outline           : Read status register
 * Include           : none
 * Declaration       : BOOLEAN Drv_Flash_ReadStatusRegister(U8* pU8StatusByte)
 * Description       : 
 * Argument          :
 * Return Value      :  TRUE  - Operation have been accepted.
 * 						FALSE - Operation is prohibited.
 * Calling Functions :
 *****************************************************************************/
BOOLEAN Drv_Flash_ReadStatusRegister(U8* pU8StatusByte)
{
	/* Make the program command */
	Drv_Flash_MakeCommandData(FLASH_CMD_STATUS_READ_STATUS_REG, (U32)0);

#ifdef PORT_CS_BY_SOFTWARE
	/* CS assert */
	SCI1_CS_ASSERT();
#endif

	/* Segment1: command */
	/* Wait for transmit buffer empty and send */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_SendData(U8Segment1CmdBuffer[0]);

	/* The 1th byte transmission period */
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	while(DRV_CSI1_IS_TX_COMPLETE() == CSI1_TX_SHIFT_NOT_EMPTY){
 		; /* wait */
	}
	Drv_CSI1_GetReceivesData();

	/* Segment2: Data */

	/* Wait for transmit buffer empty */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){
 		; /* wait */
	}
	/* Send dummy */ 
	Drv_CSI1_SendData(FLASH_COMM_SEG2_DUMMY);
	/* Wait for receive buffer full */ 
	while(DRV_CSI1_IS_RX_BUFFER_FULL() == CSI1_RX_BUFFER_NOT_FULL){
 		; /* wait */
	}
	/* Receive data */ 
	*pU8StatusByte = Drv_CSI1_GetReceivesData();

#if 0
	/* Wait for transmit buffer empty */ 
	while(DRV_CSI1_IS_TX_BUFFER_EMPTY() == CSI1_TX_BUFFER_NOT_EMPTY){};
	/* Send dummy */ 
	Drv_CSI1_SendData(FLASH_COMM_SEG2_DUMMY);
	/* Wait for receive buffer full */ 
	while(DRV_CSI1_IS_RX_BUFFER_FULL() == CSI1_RX_BUFFER_NOT_FULL){};
	/* Receive data */ 
	*pU8StatusByte2 = Drv_CSI1_GetReceivesData();
#endif

#ifdef PORT_CS_BY_SOFTWARE
	/* CS dessert */
	SCI1_CS_DEASSERT();
#endif

	return TRUE;
}

/*****************************************************************************
 * ID                :
 * Outline           : Make command and data(if any)
 * Include           : none
 * Declaration       : void Drv_Flash_MakeCommandData(U8 U8CommandType, U32 U32FlsAddress)
 * Description       : Make command and data, format includes:
 * 					   segment1: Opcode(1 byte) + Address(0 or 3 bytes) + Dummy(0-2 bytes)
 *                     segment2: Data(byte number related with on command)
 * Argument          :
 * Return Value      : void
 * Calling Functions :
 *****************************************************************************/
void Drv_Flash_MakeCommandData(U8 U8CommandType, U32 U32FlsAddress)
{
	StrFlsCmdReadArray2* pStrFlsCmdReadArray2;
	StrFlsCmdProgramBytePage* pStrFlsCmdProgramBytePage;
	StrFlsCmdWriteEnable* pStrFlsCmdWriteEnable;
	StrFlsCmdWriteDisable* pStrFlsCmdWriteDisable;
	StrFlsCmdProtectSector* pStrFlsCmdProtectSector;
	StrFlsCmdUnProtectSector* pStrFlsCmdUnProtectSector;
	StrFlsCmdBlockErase4KBytes* pStrFlsCmdBlockErase4KBytes;
	StrFlsCmdReadStatusRegister* pStrFlsCmdReadStatusRegister;

	switch(U8CommandType){
	case FLASH_CMD_READ_ARRAY_2:
		pStrFlsCmdReadArray2 = (StrFlsCmdReadArray2*)U8Segment1CmdBuffer;
		/* Segment1(command) */
		pStrFlsCmdReadArray2->U8OperationCode = FLASH_CMD_READ_ARRAY_2;
		pStrFlsCmdReadArray2->U8AddHigh = (U8)(U32FlsAddress>>16);
		pStrFlsCmdReadArray2->U8AddMid = (U8)(U32FlsAddress>>8);
		pStrFlsCmdReadArray2->U8AddLow = (U8)U32FlsAddress;
		pStrFlsCmdReadArray2->U8Dummy1 = FLASH_COMM_SEG1_DUMMY;

		/* Segment2(data) */
		break;
	case FLASH_CMD_PROGRAM_BYTE_OR_PAGE:
		pStrFlsCmdProgramBytePage = (StrFlsCmdProgramBytePage*)U8Segment1CmdBuffer;
		/* Segment1(command) */
		pStrFlsCmdProgramBytePage->U8OperationCode = FLASH_CMD_PROGRAM_BYTE_OR_PAGE;
		pStrFlsCmdProgramBytePage->U8AddHigh = (U8)(U32FlsAddress>>16);
		pStrFlsCmdProgramBytePage->U8AddMid = (U8)(U32FlsAddress>>8);
		pStrFlsCmdProgramBytePage->U8AddLow = (U8)U32FlsAddress;

		/* Segment2(data) */
		break;

	case FLASH_CMD_PROTECT_W_ENABLE:
		pStrFlsCmdWriteEnable = (StrFlsCmdWriteEnable*)U8Segment1CmdBuffer;
		/* Segment1(command) */
		pStrFlsCmdWriteEnable->U8OperationCode = FLASH_CMD_PROTECT_W_ENABLE;

		/* Segment2(data) */
		break;
	case FLASH_CMD_PROTECT_W_DISABLE:
		pStrFlsCmdWriteDisable = (StrFlsCmdWriteDisable*)U8Segment1CmdBuffer;
		/* Segment1(command) */
		pStrFlsCmdWriteDisable->U8OperationCode = FLASH_CMD_PROTECT_W_DISABLE;

		/* Segment2(data) */
		break;
	case FLASH_CMD_PROTECT_SECTOR:
		pStrFlsCmdProtectSector = (StrFlsCmdProtectSector*)U8Segment1CmdBuffer;
		/* Segment1(command) */
		pStrFlsCmdProtectSector->U8OperationCode = FLASH_CMD_PROTECT_SECTOR;
		pStrFlsCmdProtectSector->U8AddHigh = (U8)(U32FlsAddress>>16);
		pStrFlsCmdProtectSector->U8AddMid = (U8)(U32FlsAddress>>8);
		pStrFlsCmdProtectSector->U8AddLow = (U8)U32FlsAddress;
		break;
	case FLASH_CMD_UNPROTECT_SECTOR:
		pStrFlsCmdUnProtectSector = (StrFlsCmdUnProtectSector*)U8Segment1CmdBuffer;
		/* Segment1(command) */
		pStrFlsCmdUnProtectSector->U8OperationCode = FLASH_CMD_UNPROTECT_SECTOR;
		pStrFlsCmdUnProtectSector->U8AddHigh = (U8)(U32FlsAddress>>16);
		pStrFlsCmdUnProtectSector->U8AddMid = (U8)(U32FlsAddress>>8);
		pStrFlsCmdUnProtectSector->U8AddLow = (U8)U32FlsAddress;
		break;
	case FLASH_CMD_ERASE_BLOCK_4K_BYTES:
		pStrFlsCmdBlockErase4KBytes = (StrFlsCmdBlockErase4KBytes*)U8Segment1CmdBuffer;
		/* Segment1(command) */
		pStrFlsCmdBlockErase4KBytes->U8OperationCode = FLASH_CMD_ERASE_BLOCK_4K_BYTES;
		pStrFlsCmdBlockErase4KBytes->U8AddHigh = (U8)(U32FlsAddress>>16);
		pStrFlsCmdBlockErase4KBytes->U8AddMid = (U8)(U32FlsAddress>>8);
		pStrFlsCmdBlockErase4KBytes->U8AddLow = (U8)U32FlsAddress;
		break;
	case FLASH_CMD_STATUS_READ_STATUS_REG:
		pStrFlsCmdReadStatusRegister = (StrFlsCmdReadStatusRegister*)U8Segment1CmdBuffer;
		/* Segment1(command) */
		pStrFlsCmdReadStatusRegister->U8OperationCode = FLASH_CMD_STATUS_READ_STATUS_REG;
		break;
	default:
		break;
	}
}

/* End of file */
