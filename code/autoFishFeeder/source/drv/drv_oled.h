/*
 * drv_oled.h
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */

#ifndef __DRIVER_OLED_H__
#define __DRIVER_OLED_H__
/*
 * Includes
 */
#include "basictype.h"

/*
 * Typedef
 */

/*
 * Macro
 */
#define OLED_MAXLINE		(U16)256
#define OLED_MAXROW			(U16)64
#define OLED_CELL_LINE		(U16)4
#define OLED_POWER_ON		(U8)1
#define OLED_POWER_OFF		(U8)0

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */
extern void drv_OLED_Init(void);
extern void drv_OLED_GraphicWrite(U16 AdrHorizontal, U16 AdrVertical, U16 width,
		U16 high, U8 *GDRAMData, U16 wnum);
extern void drv_OLED_GraphicWrite_Offset(U16 AdrHorizontal, U16 AdrVertical,
		U16 width, U16 high, U8 *GDRAMData, U16 wnum, U8 ColumnStart);
extern void drv_OLED_GraphicRead(U16 AdrHorizontal, U16 AdrVertical, U16 width,
		U16 high, U8 *GDRAMData, U16 rnum);
extern void drv_OLED_GraphicWriteWord(U8 AdrVertical, U8 AdrHorizontal,
		U8 GDRAMDataH, U8 GDRAMDataL);
extern void drv_OLED_Clear(U8 data);
extern void drv_OLED_DataWrite(U8 data);
extern void drv_OLED_CommandWrite(U8 data);
extern void drv_OLED_DataRead(U8 *data);
extern void drv_OLED_SetColumnAddress(U8 StartAdr, U8 EndAdr);
extern void drv_OLED_SetRowAddress(U8 StartAdr, U8 EndAdr);
extern void drv_OLED_SetWriteRAM(void);
extern void drv_OLED_SetStartLine(U8);
extern void drv_OLED_GraphicLineV(U16 StartX, U16 StartY, U16 Length, U8 Gray);
extern void drv_OLED_GraphicLineVT(U16 StartX, U16 StartY, U16 Length, U8 Gray);
extern void drv_OLED_GraphicLineH(U16 StartX, U16 StartY, U16 Length, U8 Gray);
extern void drv_OLED_GraphicWriteData(U16 AdrHorizontal, U16 AdrVertical,
		U16 width, U16 high, U8 *GDRAMData, U16 wnum);
extern void drv_OLED_SetGrayScaleTable(U8 level);

/*
 * Private variables and functions
 */

#endif
/* End of File */
