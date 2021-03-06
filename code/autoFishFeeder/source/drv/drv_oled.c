/*
 * drv_oled.c
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */

/*
 * Includes
 */
#include "config.h"
#include "sfr_r82b.h"
#include "basictype.h"
#include "drv_oled.h"
#include "drv_oled_port.h"

/*
 * Typedef
 */

/*
 * Macro
 */
#define Max_Column				0x3FU			/* 256/4-1*/
#define Max_Row					0x3FU			/* 64-1*/
#define	Brightness				0x0FU

/*******OLED GRAM write ************/
#define OLED_DATAWRITE(data)	OLED_WR = LOW;\
							 	OLED_DATA = data; \
							 	OLED_WR= HIGH;\

#define OLED_DATAREAD(pdata)	{OLED_RD = LOW; \
								pdata = OLED_DATA;\
								OLED_RD = HIGH; }

#define DISABLE_INT				(cmp1ic = (U8)0x00)
#define ENABLE_INT				(cmp1ic = (U8)0x01)

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */

/*
 * Private variables and functions
 */
static const U32 Gramtodraw32[256] =
{ 0x00000000, /*0x00*/
0x0000000F, /*0x01*/
0x000000F0, /*0x0F*/
0x000000FF, /*0x03*/
0x00000F00, /*0x04*/
0x00000F0F, /*0x05*/
0x00000FF0, /*0x06*/
0x00000FFF, /*0x07*/
0x0000F000, /*0x0F*/
0x0000F00F, /*0x09*/
0x0000F0F0, /*0x0a*/
0x0000F0FF, /*0x0b*/
0x0000FF00, /*0x0F*/
0x0000FF0F, /*0x0d*/
0x0000FFF0, /*0x0e*/
0x0000FFFF, /*0x0f*/
0x000F0000, /*0x00*/
0x000F000F, /*0x01*/
0x000F00F0, /*0x0F*/
0x000F00FF, /*0x03*/
0x000F0F00, /*0x04*/
0x000F0F0F, /*0x05*/
0x000F0FF0, /*0x06*/
0x000F0FFF, /*0x07*/
0x000FF000, /*0x0F*/
0x000FF00F, /*0x09*/
0x000FF0F0, /*0x0a*/
0x000FF0FF, /*0x0b*/
0x000FFF00, /*0x0F*/
0x000FFF0F, /*0x0d*/
0x000FFFF0, /*0x0e*/
0x000FFFFF, /*0x0f*/
0x00F00000, /*0x00*/
0x00F0000F, /*0x01*/
0x00F000F0, /*0x0F*/
0x00F000FF, /*0x03*/
0x00F00F00, /*0x04*/
0x00F00F0F, /*0x05*/
0x00F00FF0, /*0x06*/
0x00F00FFF, /*0x07*/
0x00F0F000, /*0x0F*/
0x00F0F00F, /*0x09*/
0x00F0F0F0, /*0x0a*/
0x00F0F0FF, /*0x0b*/
0x00F0FF00, /*0x0F*/
0x00F0FF0F, /*0x0d*/
0x00F0FFF0, /*0x0e*/
0x00F0FFFF, /*0x0f*/
0x00FF0000, /*0x00*/
0x00FF000F, /*0x01*/
0x00FF00F0, /*0x0F*/
0x00FF00FF, /*0x03*/
0x00FF0F00, /*0x04*/
0x00FF0F0F, /*0x05*/
0x00FF0FF0, /*0x06*/
0x00FF0FFF, /*0x07*/
0x00FFF000, /*0x0F*/
0x00FFF00F, /*0x09*/
0x00FFF0F0, /*0x0a*/
0x00FFF0FF, /*0x0b*/
0x00FFFF00, /*0x0F*/
0x00FFFF0F, /*0x0d*/
0x00FFFFF0, /*0x0e*/
0x00FFFFFF, /*0x0f*/
0x0F000000, /*0x00*/
0x0F00000F, /*0x01*/
0x0F0000F0, /*0x0F*/
0x0F0000FF, /*0x03*/
0x0F000F00, /*0x04*/
0x0F000F0F, /*0x05*/
0x0F000FF0, /*0x06*/
0x0F000FFF, /*0x07*/
0x0F00F000, /*0x0F*/
0x0F00F00F, /*0x09*/
0x0F00F0F0, /*0x0a*/
0x0F00F0FF, /*0x0b*/
0x0F00FF00, /*0x0F*/
0x0F00FF0F, /*0x0d*/
0x0F00FFF0, /*0x0e*/
0x0F00FFFF, /*0x0f*/
0x0F0F0000, /*0x00*/
0x0F0F000F, /*0x01*/
0x0F0F00F0, /*0x0F*/
0x0F0F00FF, /*0x03*/
0x0F0F0F00, /*0x04*/
0x0F0F0F0F, /*0x05*/
0x0F0F0FF0, /*0x06*/
0x0F0F0FFF, /*0x07*/
0x0F0FF000, /*0x0F*/
0x0F0FF00F, /*0x09*/
0x0F0FF0F0, /*0x0a*/
0x0F0FF0FF, /*0x0b*/
0x0F0FFF00, /*0x0F*/
0x0F0FFF0F, /*0x0d*/
0x0F0FFFF0, /*0x0e*/
0x0F0FFFFF, /*0x0f*/
0x0FF00000, /*0x00*/
0x0FF0000F, /*0x01*/
0x0FF000F0, /*0x0F*/
0x0FF000FF, /*0x03*/
0x0FF00F00, /*0x04*/
0x0FF00F0F, /*0x05*/
0x0FF00FF0, /*0x06*/
0x0FF00FFF, /*0x07*/
0x0FF0F000, /*0x0F*/
0x0FF0F00F, /*0x09*/
0x0FF0F0F0, /*0x0a*/
0x0FF0F0FF, /*0x0b*/
0x0FF0FF00, /*0x0F*/
0x0FF0FF0F, /*0x0d*/
0x0FF0FFF0, /*0x0e*/
0x0FF0FFFF, /*0x0f*/
0x0FFF0000, /*0x00*/
0x0FFF000F, /*0x01*/
0x0FFF00F0, /*0x0F*/
0x0FFF00FF, /*0x03*/
0x0FFF0F00, /*0x04*/
0x0FFF0F0F, /*0x05*/
0x0FFF0FF0, /*0x06*/
0x0FFF0FFF, /*0x07*/
0x0FFFF000, /*0x0F*/
0x0FFFF00F, /*0x09*/
0x0FFFF0F0, /*0x0a*/
0x0FFFF0FF, /*0x0b*/
0x0FFFFF00, /*0x0F*/
0x0FFFFF0F, /*0x0d*/
0x0FFFFFF0, /*0x0e*/
0x0FFFFFFF, /*0x0f*/
0xF0000000, /*0x00*/
0xF000000F, /*0x01*/
0xF00000F0, /*0x0F*/
0xF00000FF, /*0x03*/
0xF0000F00, /*0x04*/
0xF0000F0F, /*0x05*/
0xF0000FF0, /*0x06*/
0xF0000FFF, /*0x07*/
0xF000F000, /*0x0F*/
0xF000F00F, /*0x09*/
0xF000F0F0, /*0x0a*/
0xF000F0FF, /*0x0b*/
0xF000FF00, /*0x0F*/
0xF000FF0F, /*0x0d*/
0xF000FFF0, /*0x0e*/
0xF000FFFF, /*0x0f*/
0xF00F0000, /*0x00*/
0xF00F000F, /*0x01*/
0xF00F00F0, /*0x0F*/
0xF00F00FF, /*0x03*/
0xF00F0F00, /*0x04*/
0xF00F0F0F, /*0x05*/
0xF00F0FF0, /*0x06*/
0xF00F0FFF, /*0x07*/
0xF00FF000, /*0x0F*/
0xF00FF00F, /*0x09*/
0xF00FF0F0, /*0x0a*/
0xF00FF0FF, /*0x0b*/
0xF00FFF00, /*0x0F*/
0xF00FFF0F, /*0x0d*/
0xF00FFFF0, /*0x0e*/
0xF00FFFFF, /*0x0f*/
0xF0F00000, /*0x00*/
0xF0F0000F, /*0x01*/
0xF0F000F0, /*0x0F*/
0xF0F000FF, /*0x03*/
0xF0F00F00, /*0x04*/
0xF0F00F0F, /*0x05*/
0xF0F00FF0, /*0x06*/
0xF0F00FFF, /*0x07*/
0xF0F0F000, /*0x0F*/
0xF0F0F00F, /*0x09*/
0xF0F0F0F0, /*0x0a*/
0xF0F0F0FF, /*0x0b*/
0xF0F0FF00, /*0x0F*/
0xF0F0FF0F, /*0x0d*/
0xF0F0FFF0, /*0x0e*/
0xF0F0FFFF, /*0x0f*/
0xF0FF0000, /*0x00*/
0xF0FF000F, /*0x01*/
0xF0FF00F0, /*0x0F*/
0xF0FF00FF, /*0x03*/
0xF0FF0F00, /*0x04*/
0xF0FF0F0F, /*0x05*/
0xF0FF0FF0, /*0x06*/
0xF0FF0FFF, /*0x07*/
0xF0FFF000, /*0x0F*/
0xF0FFF00F, /*0x09*/
0xF0FFF0F0, /*0x0a*/
0xF0FFF0FF, /*0x0b*/
0xF0FFFF00, /*0x0F*/
0xF0FFFF0F, /*0x0d*/
0xF0FFFFF0, /*0x0e*/
0xF0FFFFFF, /*0x0f*/
0xFF000000, /*0x00*/
0xFF00000F, /*0x01*/
0xFF0000F0, /*0x0F*/
0xFF0000FF, /*0x03*/
0xFF000F00, /*0x04*/
0xFF000F0F, /*0x05*/
0xFF000FF0, /*0x06*/
0xFF000FFF, /*0x07*/
0xFF00F000, /*0x0F*/
0xFF00F00F, /*0x09*/
0xFF00F0F0, /*0x0a*/
0xFF00F0FF, /*0x0b*/
0xFF00FF00, /*0x0F*/
0xFF00FF0F, /*0x0d*/
0xFF00FFF0, /*0x0e*/
0xFF00FFFF, /*0x0f*/
0xFF0F0000, /*0x00*/
0xFF0F000F, /*0x01*/
0xFF0F00F0, /*0x0F*/
0xFF0F00FF, /*0x03*/
0xFF0F0F00, /*0x04*/
0xFF0F0F0F, /*0x05*/
0xFF0F0FF0, /*0x06*/
0xFF0F0FFF, /*0x07*/
0xFF0FF000, /*0x0F*/
0xFF0FF00F, /*0x09*/
0xFF0FF0F0, /*0x0a*/
0xFF0FF0FF, /*0x0b*/
0xFF0FFF00, /*0x0F*/
0xFF0FFF0F, /*0x0d*/
0xFF0FFFF0, /*0x0e*/
0xFF0FFFFF, /*0x0f*/
0xFFF00000, /*0x00*/
0xFFF0000F, /*0x01*/
0xFFF000F0, /*0x0F*/
0xFFF000FF, /*0x03*/
0xFFF00F00, /*0x04*/
0xFFF00F0F, /*0x05*/
0xFFF00FF0, /*0x06*/
0xFFF00FFF, /*0x07*/
0xFFF0F000, /*0x0F*/
0xFFF0F00F, /*0x09*/
0xFFF0F0F0, /*0x0a*/
0xFFF0F0FF, /*0x0b*/
0xFFF0FF00, /*0x0F*/
0xFFF0FF0F, /*0x0d*/
0xFFF0FFF0, /*0x0e*/
0xFFF0FFFF, /*0x0f*/
0xFFFF0000, /*0x00*/
0xFFFF000F, /*0x01*/
0xFFFF00F0, /*0x0F*/
0xFFFF00FF, /*0x03*/
0xFFFF0F00, /*0x04*/
0xFFFF0F0F, /*0x05*/
0xFFFF0FF0, /*0x06*/
0xFFFF0FFF, /*0x07*/
0xFFFFF000, /*0x0F*/
0xFFFFF00F, /*0x09*/
0xFFFFF0F0, /*0x0a*/
0xFFFFF0FF, /*0x0b*/
0xFFFFFF00, /*0x0F*/
0xFFFFFF0F, /*0x0d*/
0xFFFFFFF0, /*0x0e*/
0xFFFFFFFF, /*0x0f*/
};

void drv_OLED_CommandWrite(U8 data);
void drv_OLED_DataWrite(U8 data);
void drv_OLED_DataRead(U8 *data);
static U8 drv_OLED_WaitBusy();
static void drv_OLED_PortInit();
void drv_OLED_Clear();

/*
 * drv_OLED_CommandWrite
 */
void drv_OLED_CommandWrite(U8 data)
{
	OLED_DC = LOW; /*Command Write*/
	OLED_WR = LOW; /*Write data*/

	OLED_DATA = data; /*Output data*/

	OLED_WR = HIGH;
	OLED_DC = HIGH; /*Data Write*/
}

/*
 * drv_OLED_DataWrite
 */
void drv_OLED_DataWrite(U8 data)
{
	OLED_WR = LOW; /*Write data*/
	OLED_DATA = data; /*Output data*/
	OLED_WR = HIGH;
}

void drv_OLED_SetColumnAddress(U8 StartAdr, U8 EndAdr)
{
	drv_OLED_CommandWrite((U8) 0x15); /* Set Column Address*/
	drv_OLED_DataWrite(StartAdr); /*   Default => 0x00*/
	drv_OLED_DataWrite(EndAdr); /*  Default => 0xFF*/
}

void drv_OLED_SetRowAddress(U8 StartAdr, U8 EndAdr)
{
	drv_OLED_CommandWrite((U8) 0x75); /* Set Column Address*/
	drv_OLED_DataWrite(StartAdr); /*   Default => 0x00*/
	drv_OLED_DataWrite(EndAdr); /*   Default => 0x7F*/
}

void drv_OLED_SetWriteRAM(void)
{
	drv_OLED_CommandWrite((U8) 0x5c); /* Enable MCU to Write into RAM*/
}

void drv_OLED_SetReadRAM(void)
{
	drv_OLED_CommandWrite((U8) 0x5d); /* Enable MCU to Read from RAM*/
}

void drv_OLED_SetRemapFormat(U8 mode)
{
	drv_OLED_CommandWrite((U8) 0xA0); /* Set Re-Map / Dual COM Line Mode*/
	drv_OLED_DataWrite(mode); /*   Default => 0x40*/
	/*     Horizontal Address Increment*/
	/*     Column Address 0 Mapped to SEG0*/
	/*     Disable Nibble Remap*/
	/*     Scan from COM0 to COM[N-1]*/
	/*     Disable COM Split Odd Even*/
	drv_OLED_DataWrite((U8) 0x11); /*   Default => 0x01 (Disable Dual COM Mode)*/
}

void drv_OLED_SetStartLine(U8 Startline)
{
	drv_OLED_CommandWrite((U8) 0xA1); /* Set Vertical Scroll by RAM*/
	drv_OLED_DataWrite(Startline); /*   Default => 0x00*/
}

void drv_OLED_SetDisplayOffset(U8 offset)
{
	drv_OLED_CommandWrite((U8) 0xA2); /* Set Vertical Scroll by Row*/
	drv_OLED_DataWrite(offset); /*   Default => 0x00*/
}

void drv_OLED_SetDisplayMode(U8 mode)
{
	drv_OLED_CommandWrite((U8) 0xA4 | mode); /* Set Display Mode*/
	/*   Default => 0xA4*/
	/*     0xA4 (0x00) => Entire Display Off, All Pixels Turn Off*/
	/*     0xA5 (0x01) => Entire Display On, All Pixels Turn On at GS Level 15*/
	/*     0xA6 (0x02) => Normal Display*/
	/*     0xA7 (0x03) => Inverse Display*/
}

void drv_OLED_SetFunctionSelection(U8 d)
{
	drv_OLED_CommandWrite((U8) 0xAB); /* Function Selection*/
	drv_OLED_DataWrite(d); /*   Default => 0x01*/
	/*    Enable Internal VDD Regulator*/
}

void drv_OLED_SetDisplayOnOff(U8 d)
{
	drv_OLED_CommandWrite((U8) 0xAE | d); /* Set Display On/Off*/
	/*   Default => 0xAE*/
	/*     0xAE (0x00) => Display Off (Sleep Mode On)*/
	/*     0xAF (0x01) => Display On (Sleep Mode Off)*/
}

void drv_OLED_SetPhaseLength(U8 d)
{
	drv_OLED_CommandWrite((U8) 0xB1); /* Phase 1 (Reset) & Phase 2 (Pre-Charge) Period Adjustment*/
	drv_OLED_DataWrite(d); /*   Default => 0x74 (7 Display Clocks [Phase 2] / 9 Display Clocks [Phase 1])*/
	/*     D[3:0] => Phase 1 Period in 5~31 Display Clocks*/
	/*     D[7:4] => Phase 2 Period in 3~15 Display Clocks*/
}

void drv_OLED_SetPartialDisplay(U8 a, U8 b, U8 c)
{
	drv_OLED_CommandWrite((U8) 0xA8 | a);
	/* Default => 0x8F*/
	/*   Select Internal Booster at Display On*/
	if (a == (U8) 0x00)
	{
		drv_OLED_DataWrite(b);
		drv_OLED_DataWrite(c);
	}
}

void drv_OLED_SetDisplayClock(U8 d)
{
	drv_OLED_CommandWrite((U8) 0xB3); /*Set Display Clock Divider / Oscillator Frequency*/
	drv_OLED_DataWrite(d); /*   Default => 0xD0*/
	/*     A[3:0] => Display Clock Divider*/
	/*     A[7:4] => Oscillator Frequency*/
}

void drv_OLED_SetDisplayEnhancement_A(U8 a, U8 b)
{
	drv_OLED_CommandWrite((U8) 0xB4); /* Display Enhancement*/
	drv_OLED_DataWrite((U8) 0xA0 | a); /*   Default => 0xA2*/
	/*     0xA0 (0x00) => Enable External VSL*/
	/*     0xA2 (0x02) => Enable Internal VSL (Kept VSL Pin N.C.)*/
	drv_OLED_DataWrite((U8) 0x05 | b); /*   Default => 0xB5*/
	/*     0xB5 (0xB0) => Normal*/
	/*     0xFD (0xF8) => Enhance Low Gray Scale Display Quality*/
}

void drv_OLED_SetGPIO(U8 d)
{
	drv_OLED_CommandWrite((U8) 0xB5); /* General Purpose IO*/
	drv_OLED_DataWrite(d); /*   Default => 0x0A (GPIO Pins output Low Level.)*/
}

void drv_OLED_SetPrechargePeriod(U8 d)
{
	drv_OLED_CommandWrite((U8) 0xB6); /* Set Second Pre-Charge Period*/
	drv_OLED_DataWrite(d); /*   Default => 0x08 (8 Display Clocks)*/
}

void drv_OLED_SetPrechargeVoltage(U8 d)
{
	drv_OLED_CommandWrite((U8) 0xBB); /* Set Pre-Charge Voltage Level*/
	drv_OLED_DataWrite(d); /*   Default => 0x17 (0.50*VCC)*/
}

void drv_OLED_SetVCOMH(U8 d)
{
	drv_OLED_CommandWrite((U8) 0xBE); /* Set COM Deselect Voltage Level*/
	drv_OLED_DataWrite(d); /*   Default => 0x04 (0.80*VCC)*/
}

void drv_OLED_SetContrastCurrent(U8 d)
{
	drv_OLED_CommandWrite((U8) 0xC1); /* Set Contrast Current*/
	drv_OLED_DataWrite(d); /*   Default => 0x7F*/
}

void drv_OLED_SetMasterCurrent(U8 d)
{
	drv_OLED_CommandWrite((U8) 0xC7); /* Master Contrast Current Control*/
	drv_OLED_DataWrite(d); /*   Default => 0x0f (Maximum)*/
}

void drv_OLED_SetMultiplexRatio(U8 d)
{
	drv_OLED_CommandWrite((U8) 0xCA); /* Set Multiplex Ratio*/
	drv_OLED_DataWrite(d); /*   Default => 0x7F (1/128 Duty)*/
}

void drv_OLED_SetDisplayEnhancement_B(U8 d)
{
	drv_OLED_CommandWrite((U8) 0xD1); /* Display Enhancement*/
	drv_OLED_DataWrite((U8) 0x82 | d); /*   Default => 0xA2*/
	/*     0x82 (0x00) => Reserved*/
	/*     0xA2 (0x20) => Normal*/
	drv_OLED_DataWrite((U8) 0x20);
}

void drv_OLED_SetCommandLock(U8 d)
{
	drv_OLED_CommandWrite((U8) 0xFD); /* Set Command Lock*/
	drv_OLED_DataWrite((U8) 0x12 | d); /*   Default => 0x12*/
	/*     0x12 => Driver IC interface is unlocked from entering command.*/
	/*     0x16 => All Commands are locked except 0xFD.*/
}

void drv_OLED_SetGrayScaleTable(U8 level)
{
	U8 MaxBright, u8_i;

	if (level > 10U)
	{
		level = 10U;
	}

	MaxBright = (180U - (15U * (10U - level))) / 15U;

	drv_OLED_CommandWrite((U8) 0xB8); /* Set Gray Scale Table*/

	for (u8_i = 0U; u8_i < 15U; u8_i++)
	{
		drv_OLED_DataWrite(MaxBright * u8_i); /*   Gray Scale Level 1*/
	}

	drv_OLED_CommandWrite((U8) 0x00); /* Enable Gray Scale Table*/
}

void drv_OLED_GraphicWrite(U16 AdrHorizontal, U16 AdrVertical, U16 width,
		U16 high, U8 *GDRAMData, U16 wnum)
{
	U8 i;
	U8 column;
	FAR_ADR U8
	*DataH, *DataL;

	U8 data;

	column = (U8)(AdrHorizontal / 4U);
	width = width / 4U;

	/*disable int cmp1*/
	DISABLE_INT;
	/*drv_OLED_SetRemapFormat(0x00);*/
	drv_OLED_SetColumnAddress(column + 0x18U, column + 0x18U + width - 1U);
	drv_OLED_SetRowAddress(AdrVertical, AdrVertical + high - 1U);
	drv_OLED_SetWriteRAM();

	for (i = 0U; i < wnum; i++, GDRAMData++)
	{
		DataH = (U8*) (Gramtodraw32 + (*GDRAMData)) + 3U;

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

void drv_OLED_GraphicWrite_Offset(U16 AdrHorizontal, U16 AdrVertical, U16 width,
		U16 high, U8 *GDRAMData, U16 wnum, U8 ColumnStart)
{
	U8 i;
	U8 column;
	FAR_ADR U8
	*DataH, *DataL;

	U8 data;

	column = AdrHorizontal / 4U;
	width = width / 4U;
	/*disable int cmp1*/
	DISABLE_INT;
	/*drv_OLED_SetRemapFormat(0x00);*/
	drv_OLED_SetColumnAddress(column + ColumnStart,
			column + ColumnStart + width - 1U);
	drv_OLED_SetRowAddress(AdrVertical, AdrVertical + high - 1U);
	drv_OLED_SetWriteRAM();

	for (i = 0U; i < wnum; i++, GDRAMData++)
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

void drv_OLED_GraphicLineV(U16 StartX, U16 StartY, U16 Length, U8 Gray)
{
	U8 u8_i, u8_j;
	U8 column;
	U8 offset;
	U8 DataH, DataL;
	U16 Data;

	DISABLE_INT;
	column = StartX / 4U;

	offset = StartX % 4U;

	switch (offset)
	{
	case 0:
		DataH = Gray << 4U;
		DataL = 0x00U;
		break;
	case 1:
		DataH = Gray;
		DataL = 0x00U;
		break;
	case 2:
		DataH = 0x00U;
		DataL = Gray << 4U;
		break;
	case 3:
		DataH = 0x00U;
		DataL = Gray;
		break;
	default:
		DataH = Gray << 4U;
		DataL = 0x00U;
		break;
	}

	drv_OLED_SetColumnAddress(column + 0x1CU, column + 0x1CU);
	drv_OLED_SetRowAddress((U8) StartY, (U8) (StartY + Length));
	drv_OLED_SetWriteRAM();

	for (u8_i = 0U; u8_i < Length; u8_i++)
	{
		OLED_DATAWRITE(DataH);
		OLED_DATAWRITE(DataL);
	}

	ENABLE_INT;
}

void drv_OLED_GraphicLineVT(U16 StartX, U16 StartY, U16 Length, U8 Gray)
{
	U8 u8_i, u8_j;
	U8 column;
	U8 offset;
	U8 DataH, DataL;
	U16 Data;

	DISABLE_INT;
	DataH = 0U;
	DataL = 0U;

	column = StartX / 4U;

	offset = StartX % 4U;

	for (u8_i = 0U; u8_i < Length; u8_i++)
	{

		drv_OLED_SetColumnAddress(column + 0x1CU, column + 0x1CU);
		drv_OLED_SetRowAddress(StartY + u8_i, StartY + u8_i);
		drv_OLED_SetReadRAM();

		/*direct is mcu relate*/
		OLED_DATA_D = 0x00U;
		OLED_DATAREAD(DataH);
		OLED_DATAREAD(DataH);
		OLED_DATAREAD(DataL);
		OLED_DATA_D = 0xffU;
		switch (offset)
		{
		case 0:
			DataH &= 0x0fU;
			DataH |= Gray << 4U;
			break;
		case 1:
			DataH &= 0xf0U;
			DataH |= Gray;
			break;
		case 2:
			DataL &= 0x0fU;
			DataL |= Gray << 4U;
			break;
		case 3:
			DataL &= 0xf0U;
			DataL |= Gray;
			break;
		default:
			break;
		}

		drv_OLED_SetColumnAddress(column + 0x1CU, column + 0x1CU);
		drv_OLED_SetRowAddress((U8) (StartY + u8_i), (U8) (StartY + u8_i));
		drv_OLED_SetWriteRAM();

		OLED_DATAWRITE(DataH);
		OLED_DATAWRITE(DataL);
	}

	ENABLE_INT;
}

void drv_OLED_GraphicLineH(U16 StartX, U16 StartY, U16 Length, U8 Gray)
{
	U8 u8_i, u8_j;
	U8 column, width;
	U8 StartOffset, EndOffset;
	U8 DataH, DataL;
	U16 Data, Data1;

	DataH = 0x00U;
	DataL = 0x00U;

	if (Length < 1U)
		return;

	DISABLE_INT;

	column = StartX / 4U;
	width = (StartX + Length - 1U) / 4U - column;

	StartOffset = StartX % 4U;
	EndOffset = (StartX + Length - 1U) % 4U;

	Data1 = Gray;
	Data1 << 12U;

	drv_OLED_SetColumnAddress(column + 0x1CU, column + width + 0x1CU);
	drv_OLED_SetRowAddress(StartY, StartY);
	drv_OLED_SetWriteRAM();

	/* draw first column*/
	if (width == 0U)
	{
		for (u8_i = StartOffset; u8_i < EndOffset; u8_i++)
		{
			switch (u8_i)
			{
			case 0:
				DataH |= Gray << 4U;
				break;
			case 1:
				DataH |= Gray;
				break;
			case 2:
				DataL |= Gray << 4U;
				break;
			case 3:
				DataL |= Gray;
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

		switch (StartOffset)
		{
		case 0:
			DataH = Gray | Gray << 4U;
			DataL = DataH;
			break;
		case 1:
			DataH = Gray;
			DataL = Gray | (Gray << 4U);
			break;
		case 2:
			DataH = 0x00U;
			DataL = Gray | Gray << 4U;
			break;
		case 3:
			DataH = 0x00U;
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
		DataH = Gray | (Gray << 4U);
		DataL = DataH;
		for (u8_i = 0U; u8_i < width - 1U; u8_i++)
		{
			OLED_DATAWRITE(DataH);
			OLED_DATAWRITE(DataL);
		}
		/*draw end*/
		switch (EndOffset)
		{
		case 0:
			DataH = Gray << 4U;
			DataL = 0x00U;
			break;
		case 1:
			DataH = Gray | (Gray << 4U);
			DataL = 0x00U;
			break;
		case 2:
			DataH = Gray | (Gray << 4U);
			DataL = Gray << 4U;
			break;
		case 3:
			DataH = Gray | (Gray << 4U);
			DataL = DataH;
			break;
		default:
			DataH = 0x00U;
			DataL = 0x00U;
			break;
		}
		OLED_DATAWRITE(DataH);
		OLED_DATAWRITE(DataL);

	}

	ENABLE_INT;
}

static void drv_OLED_PortInit()
{
	prcr = 0xff;
	/* out pin*/
	OLED_CS_D = PULL_UP; /*Chip Select*/
	OLED_DC_D = PULL_UP; /*Data/Command Control*/
	OLED_ENABLE_D = PULL_UP; /*Read/Write Enable*/
	OLED_RW_D = PULL_UP; /*Read/Write Select*/
	OLED_RD_D = PULL_UP; /*Read Signal*/
	OLED_WR_D = PULL_UP; /*Write Signal*/
	OLED_DATA_D = 0xff; /*Data bus*/

	prcr = 0x00;

	OLED_CS = HIGH;
	OLED_DC = HIGH;
	OLED_ENABLE = HIGH;
	OLED_RD = HIGH;
	OLED_WR = HIGH;

	OLED_DATA = 0xff;
}

void drv_OLED_Clear(U8 data)
{
	U8 i, j;

	drv_OLED_SetColumnAddress(0x00U, 0x77U);
	drv_OLED_SetRowAddress(0x00U, 0x7fU);
	drv_OLED_SetWriteRAM();

	for (i = 0U; i < 128U; i++)
	{
		for (j = 0U; j < 120U; j++)
		{
			drv_OLED_DataWrite(data);
			drv_OLED_DataWrite(data);
		}
	}
}

void drv_OLED_Init(void)
{
	drv_OLED_PortInit();

	OLED_CS = LOW; /*Select chip*/
	drv_OLED_SetCommandLock(0x12U); /* Unlock Basic Commands (0x12/0x16)*/
	drv_OLED_SetDisplayOnOff(0x00U); /* Display Off (0x00/0x01)*/
	drv_OLED_SetDisplayClock(0x90U); /* Set Clock as 80 Frames/Sec*/
	drv_OLED_SetMultiplexRatio(0x3FU); /* 1/64 Duty (0x0F~0x3F)*/
	drv_OLED_SetDisplayOffset(0x00U); /* Shift Mapping RAM Counter (0x00~0x3F)*/
	drv_OLED_SetStartLine(0x00U); /* Set Mapping RAM Display Start Line (0x00~0x7F)*/
	drv_OLED_SetRemapFormat(0x14U); /* Set Horizontal Address Increment*/
	/*     Column Address 0 Mapped to SEG0*/
	/*     Disable Nibble Remap*/
	/*     Scan from COM[N-1] to COM0*/
	/*     Disable COM Split Odd Even*/
	/*     Enable Dual COM Line Mode*/
	drv_OLED_SetGPIO(0x00U); /* Disable GPIO Pins Input*/
	drv_OLED_SetFunctionSelection(0x01U); /* Enable Internal VDD Regulator*/
	drv_OLED_SetDisplayEnhancement_A(0xA0U, 0xFDU); /* Enable External VSL*/
	/* Set Low Gray Scale Enhancement*/
	drv_OLED_SetContrastCurrent(0xDFU); /* Set Segment Output Current*/
	drv_OLED_SetMasterCurrent(Brightness); /* Set Scale Factor of Segment Output Current Control*/
	drv_OLED_SetGrayScaleTable(4U); /* Set Pulse Width for Gray Scale Table*/
	drv_OLED_SetPhaseLength(0xE8U); /* Set Phase 1 as 17 Clocks & Phase 2 as 14 Clocks*/
	drv_OLED_SetDisplayEnhancement_B(0x20U); /* Enhance Driving Scheme Capability (0x00/0x20)*/
	drv_OLED_SetPrechargeVoltage(0x1FU); /* Set Pre-Charge Voltage Level as 0.30*VCC*/
	drv_OLED_SetPrechargePeriod(0x08U); /* Set Second Pre-Charge Period as 15 Clocks*/
	drv_OLED_SetVCOMH(0x07U); /* Set Common Pins Deselect Voltage Level as 0.86*VCC*/
	drv_OLED_SetDisplayMode(0x02U); /* Normal Display Mode (0x00/0x01/0x02/0x03)*/
	/*Set_Partial_Display(0x01,0x00,0x00);*//* Disable Partial Display*/
	drv_OLED_SetPartialDisplay(0x00U, 0x00U, 0x40U);

	drv_OLED_Clear(0x00U); /* Clear Screen*/

	drv_OLED_SetDisplayOnOff(0x01U); /* Display On (0x00/0x01)*/

	/*drv_LCD_Clear();*/
}

/* End of File */
