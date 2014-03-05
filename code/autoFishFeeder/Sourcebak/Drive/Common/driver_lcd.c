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
 * System Name  : driver (lcd module).
 * File Name    : driver_lcd.c
 * Abstract     : driver (lcd module) AE1-LF Car Audio Demo
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AE1-LF demo board
 * Description  : driver of lcd module.
 * Operation    : none
 * Limitation   : This file can be only used as sample code for AE1-LF.
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/

#if 0
/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "config.h"
#include "driver_lcd.h"
#include "basictype.h"

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
	/*LCD IO PORT**/
#define LCD2_RS		p1_2
#define LCD2_RW		p1_1
#define LCD2_E		p1_0
#define APL_RESET	p3_7
#define LCD2_LIGHT	p1_7
#define LCD2_DB 	p2
#define PCTRL		p6_2
	
#define LCD2_RS_D		pd1_2
#define LCD2_RW_D		pd1_1
#define LCD2_E_D		pd1_0
#define APL_RESET_D	pd3_7
#define LCD2_LIGHT_D	pd1_7
#define LCD2_DB_D 	pd2
#define PCTRL_D		pd6_2

	
#define ST7920_RS_DATA			(U8)1
#define ST7920_RS_COMMANT	(U8)0
	
#define LCD_CHECK_TIMEOVER	(U8)1
#define LCD_CHECE_OK		(U8)0
	
#define LCD_CLS				(U8) 0x01
#define LCD_INSTRUCTION_BASIC (U8)0x30
#define LCD_INSTRUCTION_EXTEND (U8)0x34
#define LCD_GRAPHIC_ENABLE	(U8)0x36
#define LCD_ADDRESS_SET		(U8)0x80

#define WAIT_INIT			(U8)0
#define WAIT_ING			(U8)1
#define LCD_WAIT_BUSY_TIMEOUT	(U8)100

/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/
 U8 U8TimerCount_LCD; 

/*****************************************************************************
 Private variables and functions
 *****************************************************************************/
void Drv_LCD_CommandWrite( U8 data);
static void Drv_LCD_DataWrite( U8 data);
static void Drv_LCD_DataRead( U8 *data );
static U8 Drv_LCD_WaitBusy( );
static void Drv_LCD_PortInit( );
void Drv_LCD_Clear( );


/*****************************************************************************
* ID				 : 1.0
* Outline		 : LCD driver
* Include		 : none
* Declaration		 : U8 Drv_LCD_Wait_TimeOut( U8 timeout )
* Description		 : wait for lcd busy
* Argument 		 : timeout,the upper time of wait
* Return Value 	 : TRUE  ---it is within the time frame
*				 : FALSE ---if is out the time frame
* Calling Functions : none
*****************************************************************************/
static U8 Drv_LCD_WaitTimeOut( U8 timeout )
{
	static U8 wait_state = WAIT_INIT;

	switch(wait_state)
	{
		case WAIT_INIT:
			U8TimerCount_LCD = 0;
			wait_state = WAIT_ING;
			break;
		case WAIT_ING:
			//if (U8TimerCount_LCD > timeout )
			//{
				wait_state = WAIT_INIT;
				//return FALSE;
			//}
			break;
		default:
			break;
	}

	return TRUE;
	
}

/*****************************************************************************
* ID				 : 1.0
* Outline		 : LCD driver
* Include		 : none
* Declaration		 : void Drv_LCD_delay(U8 count)
* Description		 : delay
* Argument 		 : count,delay time
* Return Value 	 : void
* Calling Functions : none
*****************************************************************************/
static void Drv_LCD_Delay(U8 count)
{
	while(count--);
}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : LCD driver
 * Include           : none
 * Declaration       : void Drv_LCD_Init()
 * Description       : Init LCD module
 * Argument          : void
 * Return Value      : void
 * Calling Functions : none
 *****************************************************************************/
void Drv_LCD_Init()
{
	Drv_LCD_PortInit();

	PCTRL = LOW ;/*power*/

	LCD2_LIGHT = HIGH;

	LCD2_E = LOW;

	APL_RESET = LOW;

	Drv_LCD_Delay(100);

	APL_RESET = HIGH;

	Drv_LCD_Delay(100);

	Drv_LCD_CommandWrite(LCD_INSTRUCTION_BASIC); /* 8bit mode ,basic instruction set*/

	Drv_LCD_CommandWrite(LCD_CLS);	/* clear LCD */

	//Drv_LCD_CommandWrite(LCD_INSTRUCTION_EXTEND); /* */

	//Drv_LCD_CommandWrite(LCD_GRAPHIC_ENABLE);
	//Drv_LCD_CommandWrite(0x06);
	//Drv_LCD_CommandWrite(0x0d);
	Drv_LCD_Clear();
}
/*****************************************************************************
 * ID                : 1.0
 * Outline           : LCD driver
 * Include           : none
 * Declaration       : void Drv_LCD_Graphic_Write(U8 address_vertical,U8 address_horizontal,U16 data_gdram)
 * Description       : Graphic pixel to lcd
 * Argument          : address_vertical, Y axis from top
 *                   : address_horizontal,X axis from left
 *                   : data_gdram, the data of graphic
 * Return Value      : void
 * Calling Functions : none
 *****************************************************************************/
void Drv_LCD_GraphicWrite(U8 AdrVertical,U8 AdrHorizontal,U8 *GDRAMData ,U8 wnum)
{
	U16 u8_i,u8_j;

	if(wnum >16-AdrHorizontal*2)
		wnum = 16-AdrHorizontal*2;
	
	
	Drv_LCD_CommandWrite(LCD_GRAPHIC_ENABLE);
	Drv_LCD_CommandWrite(LCD_ADDRESS_SET|AdrVertical);

	Drv_LCD_CommandWrite(LCD_ADDRESS_SET|AdrHorizontal);

	Drv_LCD_CommandWrite(LCD_INSTRUCTION_BASIC);
	

	for(u8_i=0;u8_i<wnum;u8_i++)
	{
		Drv_LCD_DataWrite(*GDRAMData);
		GDRAMData++;
	}

	
	
}

void Drv_LCD_GraphicWriteWord(U8 AdrVertical,U8 AdrHorizontal,U8 GDRAMDataH ,U8 GDRAMDataL)
{
	U16 u8_i,u8_j;
	
	
	Drv_LCD_CommandWrite(LCD_GRAPHIC_ENABLE);
	Drv_LCD_CommandWrite(LCD_ADDRESS_SET|AdrVertical);

	Drv_LCD_CommandWrite(LCD_ADDRESS_SET|AdrHorizontal);

	Drv_LCD_CommandWrite(LCD_INSTRUCTION_BASIC);
	

	Drv_LCD_DataWrite(GDRAMDataH);
	Drv_LCD_DataWrite(GDRAMDataL);

	
	
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
void Drv_LCD_GraphicRead(U8 AdrVertical,U8 AdrHorizontal,U8 *GDRAMData ,U8 rnum)
{
	U16 u8_i,u8_j;

	Drv_LCD_CommandWrite(LCD_GRAPHIC_ENABLE);
	Drv_LCD_CommandWrite(LCD_ADDRESS_SET|AdrVertical);

	Drv_LCD_CommandWrite(LCD_ADDRESS_SET|AdrHorizontal);

	Drv_LCD_CommandWrite(LCD_INSTRUCTION_BASIC);

	Drv_LCD_DataRead(GDRAMData);

	for(u8_i=0;u8_i<rnum;u8_i++)
	{
		Drv_LCD_DataRead(GDRAMData);
		GDRAMData++;
	}
	
}


/*****************************************************************************
 * ID                : 1.0
 * Outline           : LCD driver
 * Include           : none
 * Declaration       : void Drv_LCD_ST7920_Write( U8 data,BOOLEAN RS)
 * Description       : send data or command to lcd
 * Argument          : data, the data is sent to lcd
 *                   : RS, the type of data
 *                         1: data
 *                   :     0: comment
 * Return Value      : void
 * Calling Functions : none
 *****************************************************************************/

static void Drv_LCD_ST7920Write( U8 data,BOOLEAN RS)
{

	if(Drv_LCD_WaitBusy ())
	{
		/* error code*/
	}
	
	if(RS == ST7920_RS_DATA)
	{
		LCD2_RS = 1;	/* Sent data */
	}else
	{
		LCD2_RS = 0; 	/* Sent commant */
	}

	LCD2_RW = 0;		/* Write mode */

	LCD2_E = 1;			/* Enable */

	LCD2_DB = data;		

	//Drv_LCD_Delay(1);

	LCD2_E = 0;

	//Drv_LCD_Delay(1);

	LCD2_RW = 1;

}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : LCD driver
 * Include           : none
 * Declaration       : void Drv_LCD_Command_Write( U8 data)
 * Description       : sent commant to lcd
 * Argument          : data, the commant
 * Return Value      : void
 * Calling Functions : none
 *****************************************************************************/
void Drv_LCD_CommandWrite( U8 data)
{


	//Drv_LCD_ST7920Write(data,ST7920_RS_COMMANT);
	if(Drv_LCD_WaitBusy ())
	{
		/* error code*/
	}

	LCD2_RS = LOW; 	/* Sent commant */

	LCD2_RW = LOW;		/* Write mode */

	LCD2_E = HIGH;			/* Enable */

	LCD2_DB = data;		

	//Drv_LCD_Delay(10);

	LCD2_E = LOW;

	//Drv_LCD_Delay(10);

	LCD2_RW = HIGH;
	LCD2_DB = 0xff;


}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : LCD driver
 * Include           : none
 * Declaration       : void Drv_LCD_Data_Write( U8 data)
 * Description       : sent data to lcd
 * Argument          : data
 * Return Value      : void
 * Calling Functions : none
 *****************************************************************************/

static void Drv_LCD_DataWrite( U8 data)
{
	//Drv_LCD_ST7920Write(data,ST7920_RS_DATA);
	if(Drv_LCD_WaitBusy ())
	{
		/* error code*/
	}
	
	LCD2_RS = HIGH;	/* Sent data */

	LCD2_RW = LOW;		/* Write mode */

	LCD2_E = HIGH;			/* Enable */

	LCD2_DB = data;		

	//Drv_LCD_Delay(10);

	LCD2_E = LOW;

	//Drv_LCD_Delay(10);

	LCD2_RW = HIGH;
	LCD2_DB = 0x00;

}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : LCD driver
 * Include           : none
 * Declaration       : void Drv_LCD_Data_Read( U8 *data )
 * Description       : read data from lcd
 * Argument          : data
 * Return Value      : void
 * Calling Functions : none
 *****************************************************************************/
static void Drv_LCD_DataRead( U8 *data )
{
	if(Drv_LCD_WaitBusy ())
	{
		/* error code*/
	}


	LCD2_DB_D = 0x00;  /*input*/

	LCD2_RS = 1;	/* read data */

	LCD2_RW = 1;		/* Write mode */

	LCD2_E = 1;			/* Enable */
		
	//Drv_LCD_Delay(2);

	*data = LCD2_DB;

	LCD2_E = 0;
	
	LCD2_RW = 1;

	LCD2_DB_D= 0xff;	/*output*/

}

/*****************************************************************************
 * ID                : 1.0
 * Outline           : LCD driver
 * Include           : none
 * Declaration       : U8 Drv_LCD_Wait_Busy( )
 * Description       : wait lcd busy
 * Argument          : void
 * Return Value      : void
 * Calling Functions : none
 *****************************************************************************/

static U8 Drv_LCD_WaitBusy( )
{
	U8 lcd_state;
	U8 busyFlag;

	lcd_state = LCD_CHECE_OK;

	pd2 = 0x00; /*input*/
	
	LCD2_RS = 0;	/* read command */

	LCD2_RW = 1;		/* read mode */

	LCD2_E = 1;			/* Enable */
			
	busyFlag = LCD2_DB&(U8)0x80;
	
	while(busyFlag==(U8)0x80)
	{
		if(!Drv_LCD_WaitTimeOut(LCD_WAIT_BUSY_TIMEOUT))
		{
			lcd_state = LCD_CHECK_TIMEOVER;
			break;
		}
		busyFlag = LCD2_DB&(U8)0x80;
	};

	LCD2_E = 0;
	
	LCD2_RW = 1;

	pd2 = 0xff;	/*output*/

	return lcd_state;

}

/*****************************************************************************
* ID				 : 1.0
* Outline		 : LCD driver
* Include		 : none
* Declaration		 : static void Drv_LCD_PortInit( )
* Description		 : lcd port init
* Argument 		 : none
* Return Value 	 : void
* Calling Functions : none
*****************************************************************************/
static void Drv_LCD_PortInit( )
{
/* out pin*/
	pd1_2 = PULL_UP; /*LCD_RS*/
	pd1_1 = PULL_UP; /*LCD_RW*/
	pd1_0 = PULL_UP; /*LCD_E*/
	pd3_7 = PULL_UP; /*APL_RESET*/
	pd1_7 = PULL_UP; /*LCD_LIGHT*/
	pd6_2 = PULL_UP; /*PCTRL*/
	pd2	  = 0xff;
}


/*****************************************************************************
 * ID                : 1.0
 * Outline           : LCD driver
 * Include           : none
 * Declaration       : void Drv_LCD_Clear( )
 * Description       : clear lcd gdram
 * Argument          : none
 * Return Value      : void
 * Calling Functions : none
 *****************************************************************************/
void Drv_LCD_Clear( )
{
	U16 u8_i,u8_j;

	for(u8_j=0;u8_j<32;u8_j++)
	{
		Drv_LCD_CommandWrite(LCD_INSTRUCTION_EXTEND);
		Drv_LCD_CommandWrite(LCD_ADDRESS_SET|u8_j);

		Drv_LCD_CommandWrite(LCD_ADDRESS_SET|0x00);

		Drv_LCD_CommandWrite(LCD_INSTRUCTION_BASIC);

	for(u8_i = 0;u8_i<16;u8_i++)
	{

		Drv_LCD_DataWrite(0x00);

		Drv_LCD_DataWrite(0x00);
	}
	}	
	Drv_LCD_CommandWrite(LCD_INSTRUCTION_EXTEND);
	Drv_LCD_CommandWrite(LCD_GRAPHIC_ENABLE);
}

#endif


/* End of File */
