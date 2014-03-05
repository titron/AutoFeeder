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
 * File Name    : mcu_depend.h
 * Abstract     : mcu dependency header file for AE1-LF.
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AE1-LF demo board
 * Description  : This is the header file of definition of MCU dependency.
 * Operation    : none
 * Limitation   : This file can be only used as sample code for AE1-LF.
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/
#ifndef __MCU_DEPEND_H__
#define __MCU_DEPEND_H__
/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "basictype.h"

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
/* **** task control event**** */
#define CANCEL_EVENT()                (TaskRecallEvent = (U8*)0xFFFF)/* NOTE: depends on MCU RAM area! */
#define EVENT_EXIST()                 (TaskRecallEvent != (U8*)0xFFFF) /* NOTE: depends on MCU RAM area! */
#define TASK_RECALL()                 {asm("ADD.W #3H,SP"); \
									   asm("MOVA _TaskRecallAdress, A0"); \
								       asm("MOV.W [A0], R0"); \
								       asm("MOV.W 2[A0], R2"); \
								       asm("JMPI.A R2R0"); \
								       }
/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/
extern U16 far *TaskRecallAdress;
extern U8 TaskRecallValue;
extern U8 *TaskRecallEvent;

/* Read U16 from buffer */
extern U16 ReadU16FromBuf(const U8* ptrData);
/* Read U32 from buffer */
extern U32 ReadU32FromBuf(const U8* ptrData);

/* Wait do task complete */
extern void TaskWait(void);
extern void BackupTaskReturnAddr(void);
/*****************************************************************************
 Private variables and functions
 *****************************************************************************/

#endif
/* End of File */
