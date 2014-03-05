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
* File Name 	: driver_iic.h
* Abstract 		: driver of iic
* Version 		: Ver 0.10
* Device 		: R8C/2A group, or R8C/2B group
* Tool-Chain 	: High-performance Embedded Workshop (Version 4.08.00.011)
* 				: C Compiler Package for M16C Series M3T-NC30WA(V.5.45 Release 00)
* OS 			: None
* H/W Platform 	: AE1-LF demo board
* Description 	: This is driver of iic.
* Operation 	: 1. lower layer driver
* Limitation 	: This program can be operated by 20MHz only.
* 				:
*******************************************************************************
* History 		: Dec.16,2010 Ver. 0.10 First Release
* 				:
*******************************************************************************/
#ifndef __DRIVER_IIC_H__
#define __DRIVER_IIC_H__

/******************************************************************************
Includes <System Includes> , "Project Includes"
******************************************************************************/
#include "basictype.h"
/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/
/* Status of I2C */
#define TRANSMIT_HEAD		(U8)1
#define TRANSMIT_DATA		(U8)2
#define TRANSMIT_END		(U8)3
#define RECEIVE_HEAD		(U8)4
#define RECEIVE_DATA		(U8)5
#define RECEIVE_END			(U8)6
#define I2CBUS_FREE			(U8)7

#define START_COND			(U8)0xB0
#define STOP_COND			(U8)0x30
/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/
/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
extern void drv_I2C_Init(void);
extern void drv_I2C_Int(void);
extern StdRetType drv_I2C_MasterSend(U8 SlaveAddr, U8 * pData, U16 Length);
#if 0
extern StdRetType Drv_I2C_MasterReceive(U8 SlaveAddr, U8 * pData, U16 Length);
#endif
extern BOOLEAN drv_I2C_GetI2CBusyState(void);
/******************************************************************************
Private global variables and functions
******************************************************************************/

#endif
/* End of File */
