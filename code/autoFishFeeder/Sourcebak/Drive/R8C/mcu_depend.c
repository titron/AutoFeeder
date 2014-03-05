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
 * File Name    : mcu_depend.c
 * Abstract     : functions used on MCU dependency
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AE1-LF demo board
 * Description  : functions used on MCU dependency.
 * Operation    : none
 * Limitation   : This file can be only used as sample code for AE1-LF.
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "mcu_depend.h"

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Macro definitions
 *****************************************************************************/

/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/
U16 far *TaskRecallAdress;
U16 far *TaskReturnAddress;
U8 TaskRecallValue;
U8 *TaskRecallEvent = (U8*) 0xFFFF;

/*****************************************************************************
 Private variables and functions
 *****************************************************************************/

/*****************************************************************************
 * ID                : 1.0
 * Outline           : Read U16 for little endian
 * Include           : none
 * Declaration       : U16 ReadU16FromBuf(const U8* ptrData)
 * Description       : Read U16 for little endian.
 * Argument          : *ptrData, pointer to buffer
 *                   : this data unit and the next will be read as U16.
 * Return Value      : U16 data value.
 * Calling Functions : none
 *****************************************************************************/
U16 ReadU16FromBuf(const U8* ptrData)
{
	return ((*(U16*) ptrData << 8) + *(ptrData + 1));
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : Read U32 for little endian
 * Include           : none
 * Declaration       : U32 ReadU32FromBuf(const U8* ptrData)
 * Description       : Read U32 for little endian.
 * Argument          : *ptrData, pointer to buffer
 *                   : this data unit and the next will be read as U32.
 * Return Value      : U32 data value.
 * Calling Functions : none
 *****************************************************************************/
U32 ReadU32FromBuf(const U8* ptrData)
{
	return (*(U32*)(ptrData) << 24) +
			((*(U32*)(ptrData) & (U32)0xff00) << 8) +
			((*(U32*)(ptrData) & (U32)0xff0000) >> 8) +
			((*(U32*)(ptrData) & (U32)0xff000000) >> 24);
}

/*****************************************************************************
 * ID                :
 * Outline           : Wait do task complete
 * Include           : none
 * Declaration       : void TaskWait(void)
 * Description       : Wait do task complete
 *                   : And return to next task line in main loop.
 * Argument          : none
 * Return Value      : none
 * Calling Functions : The Task function which use this function must not
 *                   : has auto variable.
 *****************************************************************************/
void TaskWait(void)
{
	asm("MOVA _TaskRecallAdress, A0");
	asm("POP.W [A0]	");
	asm("POP.B 2H[A0]");
	asm("MOV.W _TaskReturnAddress, A0");
	asm("MOV.W _TaskReturnAddress+2, A1");
	asm("JMPI.A A1A0");
} /* return here will jump out from task */


/*****************************************************************************
 * ID                :
 * Outline           : Save return address in main loop
 * Include           : none
 * Declaration       : void BackupTaskReturnAddr(void)
 * Description       : Save return address in main loop
 * Argument          : none
 * Return Value      : none
 * Calling Functions : The Task function which use this function must not
 *                   : has auto variable. This function must not be used in other
 *                   : functions
 *****************************************************************************/
void BackupTaskReturnAddr(void)
{
	asm("MOVA _TaskReturnAddress, A0");
	asm("MOV.W 3H[SP], [A0]");
	asm("MOV.B 5H[SP], 2H[A0]");
} /* return here will jump out from task */
/* End of file */
