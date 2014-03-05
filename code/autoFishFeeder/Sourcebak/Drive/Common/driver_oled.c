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
* File Name    : drv_oled.c
* Abstract     : driver of oled
* Version      : 1.00
* Device       : R8C/2A group, or R8C/2B group
* Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
*              : Renesas M16C Standard Toolchain (V5.45.01)
* OS           : none
* H/W Platform : AE1-LF demo board
* Description  : This is driver of oled.
* Operation    : none
* Limitation   : This file can be only used as sample code for AE1-LF.
*****************************************************************************
* History      : May.15,2011 Ver. 1.00 First Release
*****************************************************************************/

/*****************************************************************************
Includes   <System Includes> , "Project Includes"
*****************************************************************************/
#include "config.h"
#include "sfr_r82b.h"
#include "driver_oled.h"
#include "basictype.h"
#include "driver_oled_port.h"


/*****************************************************************************
Typedef definitions
*****************************************************************************/

/*****************************************************************************
Macro definitions
*****************************************************************************/
/*LCD IO PORT**/
#ifdef DEBUG
#define OLED_RESST		p3_0	/*Reset*/
#define OLED_CS			p1_0		/*Chip Select*/
#define OLED_DC			p1_1		/*Data/Command Control*/
#define OLED_ENABLE		p1_2		/*Read/Write Enable*/
#define OLED_RW   		p1_3		/*Read/Write Select*/
#define OLED_RD 		p1_2			/*Read Signal*/
#define OLED_WR			p1_3		/*Write Signal*/
#define OLED_DATA		p2			/*Data bus*/

#define OLED_RESST_D		pd3_0		/*Reset*/
#define OLED_CS_D			pd1_0			/*Chip Select*/
#define OLED_DC_D			pd1_1			/*Data/Command Control*/
#define OLED_ENABLE_D		pd1_2			/*Read/Write Enable*/
#define OLED_RW_D   		pd1_3			/*Read/Write Select*/
#define OLED_RD_D 			pd1_2			/*Read Signal*/
#define OLED_WR_D			pd1_3			/*Write Signal*/
#define OLED_DATA_D			pd2				/*Data bus*/
#endif
/*Port init end*/


#define Max_Column	0x3FU			/* 256/4-1*/
#define Max_Row		0x3FU			/* 64-1*/
#define	Brightness	0x0FU

/*******OLED GRAM write ************/
#define OLED_DATAWRITE(data) OLED_WR = LOW;\
							 OLED_DATA = data; \
							 OLED_WR= HIGH;\

#define OLED_DATAREAD(pdata)	{OLED_RD = LOW; \
								pdata = OLED_DATA;\
								OLED_RD = HIGH; }

#define DISABLE_INT		(cmp1ic = (U8)0x00)
#define ENABLE_INT		(cmp1ic = (U8)0x01)
/*****************************************************************************
Imported global variables and functions (from other files)
*****************************************************************************/

/*****************************************************************************
Exported global variables and functions (to be accessed by other files)
*****************************************************************************/

/*****************************************************************************
Private variables and functions
*****************************************************************************/
static const U32 Gramtodraw32[256]={
	0x00000000,	/*0x00*/
	0x0000000F,	/*0x01*/
	0x000000F0,	/*0x0F*/
	0x000000FF,	/*0x03*/
	0x00000F00,	/*0x04*/
	0x00000F0F,	/*0x05*/
	0x00000FF0,	/*0x06*/
	0x00000FFF,	/*0x07*/
	0x0000F000,	/*0x0F*/
	0x0000F00F,	/*0x09*/
	0x0000F0F0,	/*0x0a*/
	0x0000F0FF,	/*0x0b*/
	0x0000FF00,	/*0x0F*/
	0x0000FF0F,	/*0x0d*/
	0x0000FFF0,	/*0x0e*/
	0x0000FFFF,	/*0x0f*/
	0x000F0000,	/*0x00*/
	0x000F000F,	/*0x01*/
	0x000F00F0,	/*0x0F*/
	0x000F00FF,	/*0x03*/
	0x000F0F00,	/*0x04*/
	0x000F0F0F,	/*0x05*/
	0x000F0FF0,	/*0x06*/
	0x000F0FFF,	/*0x07*/
	0x000FF000,	/*0x0F*/
	0x000FF00F,	/*0x09*/
	0x000FF0F0,	/*0x0a*/
	0x000FF0FF,	/*0x0b*/
	0x000FFF00,	/*0x0F*/
	0x000FFF0F,	/*0x0d*/
	0x000FFFF0,	/*0x0e*/
	0x000FFFFF,	/*0x0f*/
	0x00F00000,	/*0x00*/
	0x00F0000F,	/*0x01*/
	0x00F000F0,	/*0x0F*/
	0x00F000FF,	/*0x03*/
	0x00F00F00,	/*0x04*/
	0x00F00F0F,	/*0x05*/
	0x00F00FF0,	/*0x06*/
	0x00F00FFF,	/*0x07*/
	0x00F0F000,	/*0x0F*/
	0x00F0F00F,	/*0x09*/
	0x00F0F0F0,	/*0x0a*/
	0x00F0F0FF,	/*0x0b*/
	0x00F0FF00,	/*0x0F*/
	0x00F0FF0F,	/*0x0d*/
	0x00F0FFF0,	/*0x0e*/
	0x00F0FFFF,	/*0x0f*/
	0x00FF0000,	/*0x00*/
	0x00FF000F,	/*0x01*/
	0x00FF00F0,	/*0x0F*/
	0x00FF00FF,	/*0x03*/
	0x00FF0F00,	/*0x04*/
	0x00FF0F0F,	/*0x05*/
	0x00FF0FF0,	/*0x06*/
	0x00FF0FFF,	/*0x07*/
	0x00FFF000,	/*0x0F*/
	0x00FFF00F,	/*0x09*/
	0x00FFF0F0,	/*0x0a*/
	0x00FFF0FF,	/*0x0b*/
	0x00FFFF00,	/*0x0F*/
	0x00FFFF0F,	/*0x0d*/
	0x00FFFFF0,	/*0x0e*/
	0x00FFFFFF,	/*0x0f*/
	0x0F000000,	/*0x00*/
	0x0F00000F,	/*0x01*/
	0x0F0000F0,	/*0x0F*/
	0x0F0000FF,	/*0x03*/
	0x0F000F00,	/*0x04*/
	0x0F000F0F,	/*0x05*/
	0x0F000FF0,	/*0x06*/
	0x0F000FFF,	/*0x07*/
	0x0F00F000,	/*0x0F*/
	0x0F00F00F,	/*0x09*/
	0x0F00F0F0,	/*0x0a*/
	0x0F00F0FF,	/*0x0b*/
	0x0F00FF00,	/*0x0F*/
	0x0F00FF0F,	/*0x0d*/
	0x0F00FFF0,	/*0x0e*/
	0x0F00FFFF,	/*0x0f*/
	0x0F0F0000,	/*0x00*/
	0x0F0F000F,	/*0x01*/
	0x0F0F00F0,	/*0x0F*/
	0x0F0F00FF,	/*0x03*/
	0x0F0F0F00,	/*0x04*/
	0x0F0F0F0F,	/*0x05*/
	0x0F0F0FF0,	/*0x06*/
	0x0F0F0FFF,	/*0x07*/
	0x0F0FF000,	/*0x0F*/
	0x0F0FF00F,	/*0x09*/
	0x0F0FF0F0,	/*0x0a*/
	0x0F0FF0FF,	/*0x0b*/
	0x0F0FFF00,	/*0x0F*/
	0x0F0FFF0F,	/*0x0d*/
	0x0F0FFFF0,	/*0x0e*/
	0x0F0FFFFF,	/*0x0f*/
	0x0FF00000,	/*0x00*/
	0x0FF0000F,	/*0x01*/
	0x0FF000F0,	/*0x0F*/
	0x0FF000FF,	/*0x03*/
	0x0FF00F00,	/*0x04*/
	0x0FF00F0F,	/*0x05*/
	0x0FF00FF0,	/*0x06*/
	0x0FF00FFF,	/*0x07*/
	0x0FF0F000,	/*0x0F*/
	0x0FF0F00F,	/*0x09*/
	0x0FF0F0F0,	/*0x0a*/
	0x0FF0F0FF,	/*0x0b*/
	0x0FF0FF00,	/*0x0F*/
	0x0FF0FF0F,	/*0x0d*/
	0x0FF0FFF0,	/*0x0e*/
	0x0FF0FFFF,	/*0x0f*/
	0x0FFF0000,	/*0x00*/
	0x0FFF000F,	/*0x01*/
	0x0FFF00F0,	/*0x0F*/
	0x0FFF00FF,	/*0x03*/
	0x0FFF0F00,	/*0x04*/
	0x0FFF0F0F,	/*0x05*/
	0x0FFF0FF0,	/*0x06*/
	0x0FFF0FFF,	/*0x07*/
	0x0FFFF000,	/*0x0F*/
	0x0FFFF00F,	/*0x09*/
	0x0FFFF0F0,	/*0x0a*/
	0x0FFFF0FF,	/*0x0b*/
	0x0FFFFF00,	/*0x0F*/
	0x0FFFFF0F,	/*0x0d*/
	0x0FFFFFF0,	/*0x0e*/
	0x0FFFFFFF,	/*0x0f*/
	0xF0000000,	/*0x00*/
	0xF000000F,	/*0x01*/
	0xF00000F0,	/*0x0F*/
	0xF00000FF,	/*0x03*/
	0xF0000F00,	/*0x04*/
	0xF0000F0F,	/*0x05*/
	0xF0000FF0,	/*0x06*/
	0xF0000FFF,	/*0x07*/
	0xF000F000,	/*0x0F*/
	0xF000F00F,	/*0x09*/
	0xF000F0F0,	/*0x0a*/
	0xF000F0FF,	/*0x0b*/
	0xF000FF00,	/*0x0F*/
	0xF000FF0F,	/*0x0d*/
	0xF000FFF0,	/*0x0e*/
	0xF000FFFF,	/*0x0f*/
	0xF00F0000,	/*0x00*/
	0xF00F000F,	/*0x01*/
	0xF00F00F0,	/*0x0F*/
	0xF00F00FF,	/*0x03*/
	0xF00F0F00,	/*0x04*/
	0xF00F0F0F,	/*0x05*/
	0xF00F0FF0,	/*0x06*/
	0xF00F0FFF,	/*0x07*/
	0xF00FF000,	/*0x0F*/
	0xF00FF00F,	/*0x09*/
	0xF00FF0F0,	/*0x0a*/
	0xF00FF0FF,	/*0x0b*/
	0xF00FFF00,	/*0x0F*/
	0xF00FFF0F,	/*0x0d*/
	0xF00FFFF0,	/*0x0e*/
	0xF00FFFFF,	/*0x0f*/
	0xF0F00000,	/*0x00*/
	0xF0F0000F,	/*0x01*/
	0xF0F000F0,	/*0x0F*/
	0xF0F000FF,	/*0x03*/
	0xF0F00F00,	/*0x04*/
	0xF0F00F0F,	/*0x05*/
	0xF0F00FF0,	/*0x06*/
	0xF0F00FFF,	/*0x07*/
	0xF0F0F000,	/*0x0F*/
	0xF0F0F00F,	/*0x09*/
	0xF0F0F0F0,	/*0x0a*/
	0xF0F0F0FF,	/*0x0b*/
	0xF0F0FF00,	/*0x0F*/
	0xF0F0FF0F,	/*0x0d*/
	0xF0F0FFF0,	/*0x0e*/
	0xF0F0FFFF,	/*0x0f*/
	0xF0FF0000,	/*0x00*/
	0xF0FF000F,	/*0x01*/
	0xF0FF00F0,	/*0x0F*/
	0xF0FF00FF,	/*0x03*/
	0xF0FF0F00,	/*0x04*/
	0xF0FF0F0F,	/*0x05*/
	0xF0FF0FF0,	/*0x06*/
	0xF0FF0FFF,	/*0x07*/
	0xF0FFF000,	/*0x0F*/
	0xF0FFF00F,	/*0x09*/
	0xF0FFF0F0,	/*0x0a*/
	0xF0FFF0FF,	/*0x0b*/
	0xF0FFFF00,	/*0x0F*/
	0xF0FFFF0F,	/*0x0d*/
	0xF0FFFFF0,	/*0x0e*/
	0xF0FFFFFF,	/*0x0f*/
	0xFF000000,	/*0x00*/
	0xFF00000F,	/*0x01*/
	0xFF0000F0,	/*0x0F*/
	0xFF0000FF,	/*0x03*/
	0xFF000F00,	/*0x04*/
	0xFF000F0F,	/*0x05*/
	0xFF000FF0,	/*0x06*/
	0xFF000FFF,	/*0x07*/
	0xFF00F000,	/*0x0F*/
	0xFF00F00F,	/*0x09*/
	0xFF00F0F0,	/*0x0a*/
	0xFF00F0FF,	/*0x0b*/
	0xFF00FF00,	/*0x0F*/
	0xFF00FF0F,	/*0x0d*/
	0xFF00FFF0,	/*0x0e*/
	0xFF00FFFF,	/*0x0f*/
	0xFF0F0000,	/*0x00*/
	0xFF0F000F,	/*0x01*/
	0xFF0F00F0,	/*0x0F*/
	0xFF0F00FF,	/*0x03*/
	0xFF0F0F00,	/*0x04*/
	0xFF0F0F0F,	/*0x05*/
	0xFF0F0FF0,	/*0x06*/
	0xFF0F0FFF,	/*0x07*/
	0xFF0FF000,	/*0x0F*/
	0xFF0FF00F,	/*0x09*/
	0xFF0FF0F0,	/*0x0a*/
	0xFF0FF0FF,	/*0x0b*/
	0xFF0FFF00,	/*0x0F*/
	0xFF0FFF0F,	/*0x0d*/
	0xFF0FFFF0,	/*0x0e*/
	0xFF0FFFFF,	/*0x0f*/
	0xFFF00000,	/*0x00*/
	0xFFF0000F,	/*0x01*/
	0xFFF000F0,	/*0x0F*/
	0xFFF000FF,	/*0x03*/
	0xFFF00F00,	/*0x04*/
	0xFFF00F0F,	/*0x05*/
	0xFFF00FF0,	/*0x06*/
	0xFFF00FFF,	/*0x07*/
	0xFFF0F000,	/*0x0F*/
	0xFFF0F00F,	/*0x09*/
	0xFFF0F0F0,	/*0x0a*/
	0xFFF0F0FF,	/*0x0b*/
	0xFFF0FF00,	/*0x0F*/
	0xFFF0FF0F,	/*0x0d*/
	0xFFF0FFF0,	/*0x0e*/
	0xFFF0FFFF,	/*0x0f*/
	0xFFFF0000,	/*0x00*/
	0xFFFF000F,	/*0x01*/
	0xFFFF00F0,	/*0x0F*/
	0xFFFF00FF,	/*0x03*/
	0xFFFF0F00,	/*0x04*/
	0xFFFF0F0F,	/*0x05*/
	0xFFFF0FF0,	/*0x06*/
	0xFFFF0FFF,	/*0x07*/
	0xFFFFF000,	/*0x0F*/
	0xFFFFF00F,	/*0x09*/
	0xFFFFF0F0,	/*0x0a*/
	0xFFFFF0FF,	/*0x0b*/
	0xFFFFFF00,	/*0x0F*/
	0xFFFFFF0F,	/*0x0d*/
	0xFFFFFFF0,	/*0x0e*/
	0xFFFFFFFF,	/*0x0f*/
};
void Drv_OLED_CommandWrite( U8 data);
void Drv_OLED_DataWrite( U8 data);
void Drv_OLED_DataRead( U8 *data );
static U8 Drv_OLED_WaitBusy( );
static void Drv_OLED_PortInit( );
void Drv_OLED_Clear( );


/*****************************************************************************
* ID				 : 1.0
* Outline		 : LCD driver
* Include		 : none
* Declaration		 : void Drv_OLED_PowerOnOff(U8 flag)
* Description		 : delay
* Argument 		 : count,delay time
* Return Value 	 : void
* Calling Functions : none
*****************************************************************************/
#if 0
void Drv_OLED_PowerOnOff(U8 flag)
{
	OLDE_POWER_D = PULL_UP;
	if (flag == OLED_POWER_ON)
	{
		OLED_POWER = HIGH;
	} 
	else
	{
		OLED_POWER = LOW;
	}
}
#endif
/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_Command_Write( U8 data)
* Description       : sent command to oled
* Argument          : command
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_CommandWrite( U8 data)
{
	OLED_DC = LOW;		/*Command Write*/
	OLED_WR = LOW;		/*Write data*/

	OLED_DATA = data;   /*Output data*/

	OLED_WR = HIGH;
	OLED_DC = HIGH;		/*Data Write*/

}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_Data_Write( U8 data)
* Description       : sent data to Oled
* Argument          : data
* Return Value      : void
* Calling Functions : none
*****************************************************************************/


void Drv_OLED_DataWrite( U8 data)
{
	OLED_WR = LOW;		/*Write data*/

	OLED_DATA = data;   /*Output data*/

	OLED_WR = HIGH;

}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_Data_Read( U8 *data )
* Description       : read data from Olcd
* Argument          : data
* Return Value      : void
* Calling Functions : none
*****************************************************************************/

#if 0
void Drv_OLED_DataRead( U8 *data )
{

	//OLED_DATA = 0xff;
	OLED_DC = HIGH;		/*Data Write*/
	//OLED_CS = LOW;		/*Select chip*/
	OLED_WR = HIGH;
	OLED_RD = LOW;		/*Write data*/

	//Drv_OLED_Delay(10);
	*data = OLED_DATA;   /*Input data*/

	//Drv_OLED_Delay(10);
	OLED_RD = HIGH;

}
#endif

#if 0
void Drv_OLED_CommandRead( U8 *data )
{

	OLED_DATA = 0xff;
	OLED_DC = LOW;		/*Data Write*/
	//OLED_CS = LOW;		/*Select chip*/
	OLED_WR = HIGH;
	OLED_RD = LOW;		/*Write data*/

	Drv_OLED_Delay(10);
	*data = OLED_DATA;   /*Input data*/

	Drv_OLED_Delay(10);
	OLED_RD = HIGH;

}
#endif
/************************************************************************/
/* Instruction Setting                                                                     */
/************************************************************************/

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_SetColumnAddress(U8 StartAdr, U8 EndAdr)
* Description       : set column address
* Argument          : none
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetColumnAddress(U8 StartAdr, U8 EndAdr)
{
	Drv_OLED_CommandWrite((U8)0x15);			/* Set Column Address*/
	Drv_OLED_DataWrite(StartAdr);				/*   Default => 0x00*/
	Drv_OLED_DataWrite(EndAdr);				/*  Default => 0xFF*/
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : Drv_OLED_SetRowAddress(U8 StartAdr, U8 EndAdr)
* Description       : set row address
* Argument          : none
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetRowAddress(U8 StartAdr, U8 EndAdr)
{
	Drv_OLED_CommandWrite((U8)0x75);			/* Set Column Address*/
	Drv_OLED_DataWrite(StartAdr);				/*   Default => 0x00*/
	Drv_OLED_DataWrite(EndAdr);				/*   Default => 0x7F*/
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : Drv_OLED_SetWriteRAM( void )
* Description       : set enable write ram
* Argument          : none
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetWriteRAM( void )
{
	Drv_OLED_CommandWrite((U8)0x5c);			/* Enable MCU to Write into RAM*/
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_SetReadRAM( void )
* Description       : set enable read ram
* Argument          : none
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetReadRAM( void )
{
	Drv_OLED_CommandWrite((U8)0x5d);			/* Enable MCU to Read from RAM*/
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_SetRemapFormat(U8 mode)
* Description       : set Remap formate
* Argument          : mode
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetRemapFormat(U8 mode)
{
	Drv_OLED_CommandWrite((U8)0xA0);			/* Set Re-Map / Dual COM Line Mode*/
	Drv_OLED_DataWrite(mode);				/*   Default => 0x40*/
								/*     Horizontal Address Increment*/
								/*     Column Address 0 Mapped to SEG0*/
								/*     Disable Nibble Remap*/
								/*     Scan from COM0 to COM[N-1]*/
								/*     Disable COM Split Odd Even*/
	Drv_OLED_DataWrite((U8)0x11);			/*   Default => 0x01 (Disable Dual COM Mode)*/
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_SetStartLine( U8 Startline )
* Description       : Set Start line
* Argument          : none
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetStartLine(U8 Startline)
{
	Drv_OLED_CommandWrite((U8)0xA1);			/* Set Vertical Scroll by RAM*/
	Drv_OLED_DataWrite(Startline);				/*   Default => 0x00*/
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_SetDisplayOffset(U8 offset)
* Description       : Set Vertical offset
* Argument          : none
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetDisplayOffset(U8 offset)
{
	Drv_OLED_CommandWrite((U8)0xA2);			/* Set Vertical Scroll by Row*/
	Drv_OLED_DataWrite(offset);				/*   Default => 0x00*/
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : Drv_OLED_SetDisplayMode(U8 mode)
* Description       : Set Display mode
* Argument          : mode
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetDisplayMode(U8 mode)
{
	Drv_OLED_CommandWrite((U8)0xA4|mode);			/* Set Display Mode*/
									/*   Default => 0xA4*/
									/*     0xA4 (0x00) => Entire Display Off, All Pixels Turn Off*/
									/*     0xA5 (0x01) => Entire Display On, All Pixels Turn On at GS Level 15*/
									/*     0xA6 (0x02) => Normal Display*/
									/*     0xA7 (0x03) => Inverse Display*/
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_SetFunctionSelection(U8 d)
* Description       : enable or disable the VDD regulator
* Argument          : mode
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetFunctionSelection(U8 d)
{
	Drv_OLED_CommandWrite((U8)0xAB);			/* Function Selection*/
	Drv_OLED_DataWrite(d);				/*   Default => 0x01*/
	/*    Enable Internal VDD Regulator*/
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_SetDisplayOnOff(U8 d)
* Description       : turn the OLED panel display ON or OFF
* Argument          : d
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetDisplayOnOff(U8 d)
{
	Drv_OLED_CommandWrite((U8)0xAE|d);			/* Set Display On/Off*/
	/*   Default => 0xAE*/
	/*     0xAE (0x00) => Display Off (Sleep Mode On)*/
	/*     0xAF (0x01) => Display On (Sleep Mode Off)*/
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_SetPhaseLength(U8 d)
* Description       : sets the length of phase 1 and 2 of segment waveform of the driver
* Argument          : d
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetPhaseLength(U8 d)
{
	Drv_OLED_CommandWrite((U8)0xB1);			/* Phase 1 (Reset) & Phase 2 (Pre-Charge) Period Adjustment*/
	Drv_OLED_DataWrite(d);				/*   Default => 0x74 (7 Display Clocks [Phase 2] / 9 Display Clocks [Phase 1])*/
										/*     D[3:0] => Phase 1 Period in 5~31 Display Clocks*/
										/*     D[7:4] => Phase 2 Period in 3~15 Display Clocks*/
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : Drv_OLED_SetPartialDisplay(U8 a, U8 b, U8 c)
* Description       : Defined the partial mode display area
* Argument          : a,b,c
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetPartialDisplay(U8 a, U8 b, U8 c)
{
	Drv_OLED_CommandWrite((U8)0xA8|a);
	/* Default => 0x8F*/
	/*   Select Internal Booster at Display On*/
	if(a == (U8)0x00)
	{
		Drv_OLED_DataWrite(b);
		Drv_OLED_DataWrite(c);
	}
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : Drv_OLED_SetDisplayClock(U8 d)
* Description       : Front Clock Divide Ratio ,Oscillator Frequency 
* Argument          : d
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetDisplayClock(U8 d)
{
	Drv_OLED_CommandWrite((U8)0xB3);			/*Set Display Clock Divider / Oscillator Frequency*/
	Drv_OLED_DataWrite(d);				/*   Default => 0xD0*/
										/*     A[3:0] => Display Clock Divider*/
										/*     A[7:4] => Oscillator Frequency*/
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : Drv_OLED_SetDisplayEnhancement_A(U8 a, U8 b)
* Description       : Sent to enhance the display performance
* Argument          : a,b
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetDisplayEnhancement_A(U8 a, U8 b)
{
	Drv_OLED_CommandWrite((U8)0xB4);			/* Display Enhancement*/
	Drv_OLED_DataWrite((U8)0xA0|a);			/*   Default => 0xA2*/
										/*     0xA0 (0x00) => Enable External VSL*/
										/*     0xA2 (0x02) => Enable Internal VSL (Kept VSL Pin N.C.)*/
	Drv_OLED_DataWrite((U8)0x05|b);			/*   Default => 0xB5*/
										/*     0xB5 (0xB0) => Normal*/
										/*     0xFD (0xF8) => Enhance Low Gray Scale Display Quality*/
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : Drv_OLED_SetGPIO(U8 d)
* Description       : set the states of GPIO0 and GPIO1 pins
* Argument          : d
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetGPIO(U8 d)
{
	Drv_OLED_CommandWrite((U8)0xB5);			/* General Purpose IO*/
	Drv_OLED_DataWrite(d);				/*   Default => 0x0A (GPIO Pins output Low Level.)*/
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_SetPrechargePeriod(U8 d)
* Description       : set each individual gray scale  level for the display
* Argument          : d
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetPrechargePeriod(U8 d)
{
	Drv_OLED_CommandWrite((U8)0xB6);			/* Set Second Pre-Charge Period*/
	Drv_OLED_DataWrite(d);				/*   Default => 0x08 (8 Display Clocks)*/
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_SetPrechargeVoltage(U8 d)
* Description       : sets the first pre-charge voltage (phase 2) level of segment pins
* Argument          : d
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetPrechargeVoltage(U8 d)
{
	Drv_OLED_CommandWrite((U8)0xBB);			/* Set Pre-Charge Voltage Level*/
	Drv_OLED_DataWrite(d);				/*   Default => 0x17 (0.50*VCC)*/
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_SetVCOMH(U8 d)
* Description       : sets the high voltage level of common pins
* Argument          : d
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetVCOMH(U8 d)
{
	Drv_OLED_CommandWrite((U8)0xBE);			/* Set COM Deselect Voltage Level*/
	Drv_OLED_DataWrite(d);				/*   Default => 0x04 (0.80*VCC)*/
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_SetContrastCurrent(U8 d)
* Description       : set Contrast Setting of the display
* Argument          : d
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetContrastCurrent(U8 d)
{
	Drv_OLED_CommandWrite((U8)0xC1);			/* Set Contrast Current*/
	Drv_OLED_DataWrite(d);				/*   Default => 0x7F*/
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_SetMasterCurrent(U8 d)
* Description       : control the segment output current by a scaling factor
* Argument          : d
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetMasterCurrent(U8 d)
{
	Drv_OLED_CommandWrite((U8)0xC7);			/* Master Contrast Current Control*/
	Drv_OLED_DataWrite(d);				/*   Default => 0x0f (Maximum)*/
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_SetMultiplexRatio(U8 d)
* Description       :  switches default 1:128 multiplex mode to any multiplex mode from 16 to 128
* Argument          : d
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetMultiplexRatio(U8 d)
{
	Drv_OLED_CommandWrite((U8)0xCA);			/* Set Multiplex Ratio*/
	Drv_OLED_DataWrite(d);				/*   Default => 0x7F (1/128 Duty)*/
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_SetDisplayEnhancement_B(U8 d)
* Description       : sent to enhance the display performance
* Argument          : d
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetDisplayEnhancement_B(U8 d)
{
	Drv_OLED_CommandWrite((U8)0xD1);			/* Display Enhancement*/
	Drv_OLED_DataWrite((U8)0x82|d);			/*   Default => 0xA2*/
	/*     0x82 (0x00) => Reserved*/
	/*     0xA2 (0x20) => Normal*/
	Drv_OLED_DataWrite((U8)0x20);
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_SetCommandLock(U8 d)
* Description       : lock the OLED driver IC from accepting any command except itself
* Argument          : d
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetCommandLock(U8 d)
{
	Drv_OLED_CommandWrite((U8)0xFD);			/* Set Command Lock*/
	Drv_OLED_DataWrite((U8)0x12|d);			/*   Default => 0x12*/
	/*     0x12 => Driver IC interface is unlocked from entering command.*/
	/*     0x16 => All Commands are locked except 0xFD.*/
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_SetGrayScaleTable(U8 level)
* Description       : set each individual gray scale  level for the display
* Argument          : d
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_SetGrayScaleTable(U8 level)
{
	U8 MaxBright,u8_i;

	if (level >10U)
	{
		level =10U;
	}

	MaxBright = (180U-(15U*(10U-level)))/15U;

	Drv_OLED_CommandWrite((U8)0xB8);			/* Set Gray Scale Table*/

	for (u8_i = 0U;u8_i<15U;u8_i++)
	{
		Drv_OLED_DataWrite(MaxBright*u8_i);			/*   Gray Scale Level 1*/
	}
	


#if 0
	switch(level)
	{
	case 1:
		Drv_OLED_DataWrite(0x20);			//   Gray Scale Level 1
		Drv_OLED_DataWrite(0x28);			//   Gray Scale Level 2
		Drv_OLED_DataWrite(0x37);			//   Gray Scale Level 3
		Drv_OLED_DataWrite(0x43);			//   Gray Scale Level 4
		Drv_OLED_DataWrite(0x4D);			//   Gray Scale Level 5
		Drv_OLED_DataWrite(0x56);			//   Gray Scale Level 6
		Drv_OLED_DataWrite(0x60);			//   Gray Scale Level 7
		Drv_OLED_DataWrite(0x68);			//   Gray Scale Level 8
		Drv_OLED_DataWrite(0x72);			//   Gray Scale Level 9
		Drv_OLED_DataWrite(0x7C);			//   Gray Scale Level 10
		Drv_OLED_DataWrite(0x86);			//   Gray Scale Level 11
		Drv_OLED_DataWrite(0x91);			//   Gray Scale Level 12
		Drv_OLED_DataWrite(0x9B);			//   Gray Scale Level 13
		Drv_OLED_DataWrite(0xA6);			//   Gray Scale Level 14
		Drv_OLED_DataWrite(0xB4);			//   Gray Scale Level 15
		break;
	case 2:
		Drv_OLED_DataWrite(0x08);			//   Gray Scale Level 1
		Drv_OLED_DataWrite(0x10);			//   Gray Scale Level 2
		Drv_OLED_DataWrite(0x18);			//   Gray Scale Level 3
		Drv_OLED_DataWrite(0x20);			//   Gray Scale Level 4
		Drv_OLED_DataWrite(0x28);			//   Gray Scale Level 5
		Drv_OLED_DataWrite(0x37);			//   Gray Scale Level 6
		Drv_OLED_DataWrite(0x43);			//   Gray Scale Level 7
		Drv_OLED_DataWrite(0x4D);			//   Gray Scale Level 8
		Drv_OLED_DataWrite(0x56);			//   Gray Scale Level 9
		Drv_OLED_DataWrite(0x60);			//   Gray Scale Level 10
		Drv_OLED_DataWrite(0x68);			//   Gray Scale Level 11
		Drv_OLED_DataWrite(0x72);			//   Gray Scale Level 12
		Drv_OLED_DataWrite(0x7C);			//   Gray Scale Level 13
		Drv_OLED_DataWrite(0x86);			//   Gray Scale Level 14
		Drv_OLED_DataWrite(0x91);			//   Gray Scale Level 15
		break;
	case 3:
		Drv_OLED_DataWrite(0x08);			//   Gray Scale Level 1
		Drv_OLED_DataWrite(0x08);			//   Gray Scale Level 2
		Drv_OLED_DataWrite(0x08);			//   Gray Scale Level 3
		Drv_OLED_DataWrite(0x08);			//   Gray Scale Level 4
		Drv_OLED_DataWrite(0x10);			//   Gray Scale Level 5
		Drv_OLED_DataWrite(0x18);			//   Gray Scale Level 6
		Drv_OLED_DataWrite(0x20);			//   Gray Scale Level 7
		Drv_OLED_DataWrite(0x28);			//   Gray Scale Level 8
		Drv_OLED_DataWrite(0x37);			//   Gray Scale Level 9
		Drv_OLED_DataWrite(0x43);			//   Gray Scale Level 10
		Drv_OLED_DataWrite(0x4D);			//   Gray Scale Level 11
		Drv_OLED_DataWrite(0x56);			//   Gray Scale Level 12
		Drv_OLED_DataWrite(0x60);			//   Gray Scale Level 13
		Drv_OLED_DataWrite(0x68);			//   Gray Scale Level 14
		Drv_OLED_DataWrite(0x72);			//   Gray Scale Level 15
	    break;													  
	case 4:
		Drv_OLED_DataWrite(0x08);			//   Gray Scale Level 1
		Drv_OLED_DataWrite(0x08);			//   Gray Scale Level 2
		Drv_OLED_DataWrite(0x08);			//   Gray Scale Level 3
		Drv_OLED_DataWrite(0x08);			//   Gray Scale Level 4
		Drv_OLED_DataWrite(0x08);			//   Gray Scale Level 5
		Drv_OLED_DataWrite(0x08);			//   Gray Scale Level 6
		Drv_OLED_DataWrite(0x08);			//   Gray Scale Level 7
		Drv_OLED_DataWrite(0x10);			//   Gray Scale Level 8
		Drv_OLED_DataWrite(0x18);			//   Gray Scale Level 9
		Drv_OLED_DataWrite(0x20);			//   Gray Scale Level 10
		Drv_OLED_DataWrite(0x28);			//   Gray Scale Level 11
		Drv_OLED_DataWrite(0x37);			//   Gray Scale Level 12
		Drv_OLED_DataWrite(0x43);			//   Gray Scale Level 13
		Drv_OLED_DataWrite(0x4D);			//   Gray Scale Level 14
		Drv_OLED_DataWrite(0x56);			//   Gray Scale Level 15
	    break;
	default:
		Drv_OLED_DataWrite(0x20);			//   Gray Scale Level 1
		Drv_OLED_DataWrite(0x28);			//   Gray Scale Level 2
		Drv_OLED_DataWrite(0x37);			//   Gray Scale Level 3
		Drv_OLED_DataWrite(0x43);			//   Gray Scale Level 4
		Drv_OLED_DataWrite(0x4D);			//   Gray Scale Level 5
		Drv_OLED_DataWrite(0x56);			//   Gray Scale Level 6
		Drv_OLED_DataWrite(0x60);			//   Gray Scale Level 7
		Drv_OLED_DataWrite(0x68);			//   Gray Scale Level 8
		Drv_OLED_DataWrite(0x72);			//   Gray Scale Level 9
		Drv_OLED_DataWrite(0x7C);			//   Gray Scale Level 10
		Drv_OLED_DataWrite(0x86);			//   Gray Scale Level 11
		Drv_OLED_DataWrite(0x91);			//   Gray Scale Level 12
		Drv_OLED_DataWrite(0x9B);			//   Gray Scale Level 13
		Drv_OLED_DataWrite(0xA6);			//   Gray Scale Level 14
		Drv_OLED_DataWrite(0xB4);			//   Gray Scale Level 15
	    break;
	}
#endif

	Drv_OLED_CommandWrite((U8)0x00);			/* Enable Gray Scale Table*/
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_GraphicWrite(U16 AdrHorizontal,U16 AdrVertical,U16 width,U16 high,U8 *GDRAMData ,U16 wnum)
* Description       : Graphic pixel to OLED
* Argument          : address_vertical, Y axis from top
*                   : address_horizontal,X axis from left
*                   : data_gdram, the data of graphic
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
#if 0
void Drv_OLED_ResetGrayScaleTable()
{
	Drv_OLED_CommandWrite(0xB8);			// Set Gray Scale Table
	Drv_OLED_DataWrite(0x20);			//   Gray Scale Level 1
	Drv_OLED_DataWrite(0x28);			//   Gray Scale Level 2
	Drv_OLED_DataWrite(0x37);			//   Gray Scale Level 3
	Drv_OLED_DataWrite(0x43);			//   Gray Scale Level 4
	Drv_OLED_DataWrite(0x4D);			//   Gray Scale Level 5
	Drv_OLED_DataWrite(0x56);			//   Gray Scale Level 6
	Drv_OLED_DataWrite(0x60);			//   Gray Scale Level 7
	Drv_OLED_DataWrite(0x68);			//   Gray Scale Level 8
	Drv_OLED_DataWrite(0x72);			//   Gray Scale Level 9
	Drv_OLED_DataWrite(0x7C);			//   Gray Scale Level 10
	Drv_OLED_DataWrite(0x86);			//   Gray Scale Level 11
	Drv_OLED_DataWrite(0x91);			//   Gray Scale Level 12
	Drv_OLED_DataWrite(0x9B);			//   Gray Scale Level 13
	Drv_OLED_DataWrite(0xA6);			//   Gray Scale Level 14
	Drv_OLED_DataWrite(0xB4);			//   Gray Scale Level 15

	Drv_OLED_CommandWrite(0x00);			// Enable Gray Scale Table
}
#endif

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_GraphicWrite(U16 AdrHorizontal,U16 AdrVertical,U16 width,U16 high,U8 *GDRAMData ,U16 wnum)
* Description       : Graphic pixel to OLED
* Argument          : address_vertical, Y axis from top
*                   : address_horizontal,X axis from left
*                   : data_gdram, the data of graphic
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_GraphicWrite(U16 AdrHorizontal,U16 AdrVertical,U16 width,U16 high,U8 *GDRAMData ,U16 wnum)
{
	U8 i;
	U8 column;
	FAR_ADR U8 * DataH,*DataL;

	U8 data;

	column = (U8)(AdrHorizontal/4U);
	width = width/4U;

	/*disable int cmp1*/
	DISABLE_INT;
	/*Drv_OLED_SetRemapFormat(0x00);*/
	Drv_OLED_SetColumnAddress(column+0x18U,column+0x18U+width-1U);
	Drv_OLED_SetRowAddress(AdrVertical,AdrVertical+high-1U);
	Drv_OLED_SetWriteRAM();

	for(i=0U;i<wnum;i++,GDRAMData++)
	{
		DataH = (U8*)(Gramtodraw32+(*GDRAMData))+3U;

		data = *DataH;
		OLED_DATAWRITE(*DataH);
		DataH--;
		OLED_DATAWRITE(*DataH);
		DataH--;
		OLED_DATAWRITE(*DataH);
		DataH--;
		OLED_DATAWRITE(*DataH);
	}
	/*ensable int cmp1*/
	ENABLE_INT;
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_GraphicWrite_Offset(U16 AdrHorizontal,U16 AdrVertical,U16 width,U16 high,U8 *GDRAMData ,U16 wnum,U8 ColumnStart)
* Description       : Graphic pixel to OLED
* Argument          : address_vertical, Y axis from top
*                   : address_horizontal,X axis from left
*                   : data_gdram, the data of graphic
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_GraphicWrite_Offset(U16 AdrHorizontal,U16 AdrVertical,U16 width,U16 high,U8 *GDRAMData ,U16 wnum,U8 ColumnStart)
{
	U8 i;
	U8 column;
	FAR_ADR U8 * DataH,*DataL;

	U8 data;

	column = AdrHorizontal/4U;
	width = width/4U;
	/*disable int cmp1*/
	DISABLE_INT;
	/*Drv_OLED_SetRemapFormat(0x00);*/
	Drv_OLED_SetColumnAddress(column+ColumnStart,column+ColumnStart+width-1U);
	Drv_OLED_SetRowAddress(AdrVertical,AdrVertical+high-1U);
	Drv_OLED_SetWriteRAM();

	for(i=0U;i<wnum;i++,GDRAMData++)
	{
		DataH = (FAR_ADR U8*)(Gramtodraw32+(*GDRAMData))+3;

		data = *DataH;
		OLED_DATAWRITE(*DataH);
		DataH--;
		OLED_DATAWRITE(*DataH);
		DataH--;
		OLED_DATAWRITE(*DataH);
		DataH--;
		OLED_DATAWRITE(*DataH);
	}
	/*ensable int cmp1*/
	ENABLE_INT;
}
#if 0
void Drv_OLED_GraphicWriteWord(U8 AdrHorizontal,U8 AdrVertical,U8 GDRAMDataH ,U8 GDRAMDataL)
{
	unsigned char i,j;
	U8 column;
	U8 offset;
	U8 * DataH,*DataL;

	column = AdrHorizontal/4;

	Drv_OLED_SetColumnAddress(column+0x1C,column+0x1C+1);
	Drv_OLED_SetRowAddress(AdrVertical,AdrVertical+1);
	Drv_OLED_SetWriteRAM();

	OLED_DATAWRITE(Gramtodraw[GDRAMDataH&0x0f][0]);
	OLED_DATAWRITE(Gramtodraw[GDRAMDataH&0x0f][1]);


}
#endif

void Drv_OLED_GraphicLineV(U16 StartX,U16 StartY,U16 Length,U8 Gray)
{
	U8 u8_i,u8_j;
	U8 column;
	U8 offset;
	U8 DataH,DataL;
	U16 Data;

	DISABLE_INT;
	column = StartX/4U;

	offset = StartX%4U;

	switch(offset)
	{
	case 0:
		DataH = Gray<<4U;
		DataL = 0x00U;
		break;
	case 1:
		DataH = Gray;
		DataL = 0x00U;
		break;
	case 2:
		DataH = 0x00U;
		DataL = Gray<<4U;
	    break;
	case 3:
		DataH = 0x00U;
		DataL = Gray;
	    break;
	default:
		DataH = Gray<<4U;
		DataL = 0x00U;
	    break;
	}



	Drv_OLED_SetColumnAddress(column+0x1CU,column+0x1CU);
	Drv_OLED_SetRowAddress((U8)StartY,(U8)(StartY+Length));
	Drv_OLED_SetWriteRAM();

	for (u8_i = 0U;u8_i<Length;u8_i++)
	{
		OLED_DATAWRITE(DataH);
		OLED_DATAWRITE(DataL);
	}

	ENABLE_INT;

}

void Drv_OLED_GraphicLineVT(U16 StartX,U16 StartY,U16 Length,U8 Gray)
{
	U8 u8_i,u8_j;
	U8 column;
	U8 offset;
	U8 DataH,DataL;
	U16 Data;

	DISABLE_INT;
	DataH = 0U;
	DataL = 0U;

	column = StartX/4U;

	offset = StartX%4U;

	for (u8_i=0U;u8_i<Length;u8_i++)
	{

		Drv_OLED_SetColumnAddress(column+0x1CU,column+0x1CU);
		Drv_OLED_SetRowAddress(StartY+u8_i,StartY+u8_i);
		Drv_OLED_SetReadRAM();

		/*direct is mcu relate*/
		OLED_DATA_D = 0x00U;
		OLED_DATAREAD(DataH);
		OLED_DATAREAD(DataH);
		OLED_DATAREAD(DataL);
		OLED_DATA_D = 0xffU;
		switch(offset)
		{
		case 0:
			DataH &= 0x0fU;
			DataH |= Gray<<4U;
			break;
		case 1:
			DataH &= 0xf0U;
			DataH |= Gray;
			break;
		case 2:
			DataL &= 0x0fU;
			DataL |= Gray<<4U;
			break;
		case 3:
			DataL &= 0xf0U;
			DataL |= Gray;
			break;
		default:
			break;
		}

		Drv_OLED_SetColumnAddress(column+0x1CU,column+0x1CU);
		Drv_OLED_SetRowAddress((U8)(StartY+u8_i),(U8)(StartY+u8_i));
		Drv_OLED_SetWriteRAM();

		OLED_DATAWRITE(DataH);
		OLED_DATAWRITE(DataL);

	}

	ENABLE_INT;

}

void Drv_OLED_GraphicLineH(U16 StartX,U16 StartY,U16 Length,U8 Gray)
{
	U8 u8_i,u8_j;
	U8 column,width;
	U8 StartOffset,EndOffset;
	U8 DataH,DataL;
	U16 Data,Data1;

	DataH = 0x00U;
	DataL = 0x00U;

	if(Length<1U)
		return;

	DISABLE_INT;

	column = StartX/4U;
	width = (StartX+Length-1U)/4U-column;

	StartOffset = StartX%4U;
	EndOffset = (StartX+Length-1U)%4U;

	Data1 = Gray;
	Data1<<12U;

	Drv_OLED_SetColumnAddress(column+0x1CU,column+width+0x1CU);
	Drv_OLED_SetRowAddress(StartY,StartY);
	Drv_OLED_SetWriteRAM();

	/* draw first column*/
	if (width==0U)
	{
		for (u8_i=StartOffset;u8_i<EndOffset;u8_i++)
		{
			switch(u8_i)
			{
			case 0:
				DataH|=Gray<<4U;
				break;
			case 1:
				DataH|=Gray;
				break;
			case 2:
				DataL|=Gray<<4U;
			    break;
			case 3:
				DataL|=Gray;
			    break;
			default:
				DataH = 0U;
				DataL = 0U;
			    break;
			}
		}
		OLED_DATAWRITE(DataH);
		OLED_DATAWRITE(DataL);
	}
	else
	{

		switch(StartOffset)
		{
		case 0:
			DataH = Gray|Gray<<4U;
			DataL = DataH;
			break;
		case 1:
			DataH = Gray;
			DataL = Gray|(Gray<<4U);
			break;
		case 2:
			DataH = 0x00U;
			DataL = Gray|Gray<<4U;
			break;
		case 3:
			DataH =0x00U;
			DataL = Gray;
		    break;
		default:
			DataH = 0x00U;
			DataL = 0x00U;
		    break;
		}
		OLED_DATAWRITE(DataH);
		OLED_DATAWRITE(DataL);

		/*draw middle*/
		DataH =Gray|(Gray<<4U);
		DataL = DataH;
		for (u8_i = 0U;u8_i<width-1U;u8_i++)
		{
			OLED_DATAWRITE(DataH);
			OLED_DATAWRITE(DataL);
		}
		/*draw end*/
		switch(EndOffset)
		{
		case 0:
			DataH = Gray<<4U;
			DataL = 0x00U;
			break;
		case 1:
			DataH =Gray|(Gray<<4U);
			DataL = 0x00U;
			break;
		case 2:
			DataH = Gray|(Gray<<4U);
			DataL = Gray<<4U;
		    break;
		case 3:
			DataH = Gray|(Gray<<4U);
			DataL = DataH;
		    break;
		default:
			DataH =0x00U;
			DataL = 0x00U;
		    break;
		}
		OLED_DATAWRITE(DataH);
		OLED_DATAWRITE(DataL);

	}

	ENABLE_INT;

}
/*****************************************************************************
* ID                : 1.0
* Outline           : LCD driver
* Include           : none
* Declaration       : Drv_LCD_GraphicRead(U8 AdrVertical,U8 AdrHorizontal,U8 *GDRAMDataH ,U8 *GDRAMDataL)
* Description       : Read Graphic pixel
* Argument          : address_vertical, Y axis from top
*                   : address_horizontal,X axis from left
*                   : data_gdram, the data of graphic
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
#if 0
void Drv_OLED_GraphicRead(U16 AdrHorizontal,U16 AdrVertical,U16 width,U16 high,U8 *GDRAMData ,U16 rnum)
{
	unsigned char i,j;
	U8 column;

	column = AdrHorizontal/4;

	width = width/4;

	//Drv_OLED_SetRemapFormat(0x00);
	Drv_OLED_SetColumnAddress(0x18+column,0x18+column+width);
	Drv_OLED_SetRowAddress(AdrVertical,AdrVertical+high);	
	Drv_OLED_SetReadRAM();

	OLED_DATA_D = 0x00;		/*input mode*/
	OLED_DATAREAD(*GDRAMData); /*Read dump*/
	/*Repeat read GRAM 144times*/
	asm(".MREPEAT 144");
	asm("BCLR 2,00E1H");
	asm("MOV.B 00E4H,[A0]");
	asm("BSET 2,00E1H");
	asm("INC.W A0");
	asm(".ENDR");

	OLED_DATA_D = 0xff;		/*output mode*/
	//pu04 = 0;
	//pu05 = 0;

}
#endif
#if 0
void Drv_OLED_GraphicWriteData(U16 AdrHorizontal,U16 AdrVertical,U16 width,U16 high,U8 *GDRAMData ,U16 wnum)
{
	unsigned char i,j;
	U8 column;
	U8 * DataH,*DataL;

	column = AdrHorizontal/4;

	width = width/4;

	//Drv_OLED_SetRemapFormat(0x00);
	Drv_OLED_SetColumnAddress(column+0x18,column+0x18+width-1);
	Drv_OLED_SetRowAddress(AdrVertical,AdrVertical+high-1);
	Drv_OLED_SetWriteRAM();

	for(i=0;i<wnum;i++,GDRAMData++)
	{
		OLED_DATAWRITE(*GDRAMData);
	}
}
#endif



/*****************************************************************************
* ID				 : 1.0
* Outline			 : OLED driver
* Include			 : none
* Declaration		 : static void Drv_OLED_PortInit( )
* Description		 : Olcd port init
* Argument 			 : none
* Return Value 		 : void
* Calling Functions  : none
*****************************************************************************/
static void Drv_OLED_PortInit( )
{
	prcr = 0xff;
	/* out pin*/
	OLED_CS_D = PULL_UP;					/*Chip Select*/
	OLED_DC_D		= PULL_UP;				/*Data/Command Control*/
	OLED_ENABLE_D	= PULL_UP;				/*Read/Write Enable*/
	OLED_RW_D		= PULL_UP;  			/*Read/Write Select*/
	OLED_RD_D		= PULL_UP;				/*Read Signal*/
	OLED_WR_D		= PULL_UP;				/*Write Signal*/
	OLED_DATA_D		= 0xff;					/*Data bus*/

	prcr = 0x00;

	OLED_CS = HIGH;
	OLED_DC			= HIGH;
	OLED_ENABLE		= HIGH;
	OLED_RD			= HIGH;
    OLED_WR			= HIGH;

	OLED_DATA		= 0xff;

}


/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_LCD_Clear( )
* Description       : clear Olcd GDRAM
* Argument          : none
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_Clear( U8 data)
{
	U8 i,j;
	Drv_OLED_SetColumnAddress(0x00U,0x77U);
	Drv_OLED_SetRowAddress(0x00U,0x7fU);
	Drv_OLED_SetWriteRAM();

	for(i=0U;i<128U;i++)
	{
		for(j=0U;j<120U;j++)
		{
			Drv_OLED_DataWrite(data);
			Drv_OLED_DataWrite(data);
		}
	}
}

/*****************************************************************************
* ID                : 1.0
* Outline           : OLED driver
* Include           : none
* Declaration       : void Drv_OLED_Init()
* Description       : Init OLED module
* Argument          : void
* Return Value      : void
* Calling Functions : none
*****************************************************************************/
void Drv_OLED_Init(void)
{
	Drv_OLED_PortInit();

	OLED_CS = LOW;		/*Select chip*/
	Drv_OLED_SetCommandLock(0x12U);			/* Unlock Basic Commands (0x12/0x16)*/
	Drv_OLED_SetDisplayOnOff(0x00U);		/* Display Off (0x00/0x01)*/
	Drv_OLED_SetDisplayClock(0x90U);		/* Set Clock as 80 Frames/Sec*/
	Drv_OLED_SetMultiplexRatio(0x3FU);		/* 1/64 Duty (0x0F~0x3F)*/
	Drv_OLED_SetDisplayOffset(0x00U);		/* Shift Mapping RAM Counter (0x00~0x3F)*/
	Drv_OLED_SetStartLine(0x00U);			/* Set Mapping RAM Display Start Line (0x00~0x7F)*/
	Drv_OLED_SetRemapFormat(0x14U);			/* Set Horizontal Address Increment*/
	/*     Column Address 0 Mapped to SEG0*/
	/*     Disable Nibble Remap*/
	/*     Scan from COM[N-1] to COM0*/
	/*     Disable COM Split Odd Even*/
	/*     Enable Dual COM Line Mode*/
	Drv_OLED_SetGPIO(0x00U);				/* Disable GPIO Pins Input*/
	Drv_OLED_SetFunctionSelection(0x01U);		/* Enable Internal VDD Regulator*/
	Drv_OLED_SetDisplayEnhancement_A(0xA0U,0xFDU);	/* Enable External VSL*/
	/* Set Low Gray Scale Enhancement*/
	Drv_OLED_SetContrastCurrent(0xDFU);		/* Set Segment Output Current*/
	Drv_OLED_SetMasterCurrent(Brightness);		/* Set Scale Factor of Segment Output Current Control*/
	Drv_OLED_SetGrayScaleTable(4U);			/* Set Pulse Width for Gray Scale Table*/
	Drv_OLED_SetPhaseLength(0xE8U);			/* Set Phase 1 as 17 Clocks & Phase 2 as 14 Clocks*/
	Drv_OLED_SetDisplayEnhancement_B(0x20U);	/* Enhance Driving Scheme Capability (0x00/0x20)*/
	Drv_OLED_SetPrechargeVoltage(0x1FU);		/* Set Pre-Charge Voltage Level as 0.30*VCC*/
	Drv_OLED_SetPrechargePeriod(0x08U);		/* Set Second Pre-Charge Period as 15 Clocks*/
	Drv_OLED_SetVCOMH(0x07U);			/* Set Common Pins Deselect Voltage Level as 0.86*VCC*/
	Drv_OLED_SetDisplayMode(0x02U);			/* Normal Display Mode (0x00/0x01/0x02/0x03)*/
	/*Set_Partial_Display(0x01,0x00,0x00);*/	/* Disable Partial Display*/
	Drv_OLED_SetPartialDisplay(0x00U,0x00U,0x40U);

	Drv_OLED_Clear(0x00U);				/* Clear Screen*/

	Drv_OLED_SetDisplayOnOff(0x01U);		/* Display On (0x00/0x01)*/

	/*Drv_LCD_Clear();*/
}



/* End of File */