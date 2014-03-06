/*
 * if_oled_text.h
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */
#ifndef __LCD_TEXT_H__
#define __LCD_TEXT_H__
/*
 * Includes
 */

/*
 * Typedef
 */

/*
 * Macro
 */
#define FONT24 (U8)24
#define FONT16 (U8)16
#define FONT12 (U8)12

/*ENDIAN*/
#define BIG_ENDIAN (U8)1
#define LITTLE_ENDIAN (U8)0

/*Ico unicode*/
//#define CODE_SPEEK_OFF			0x0081
#define CODE_SPEEK_OFF			"\x81\x00"
//#define CODE_SPEEK_ON			0x0082
#define CODE_SPEEK_ON			"\x82\x00"
//#define CODE_MODE_ORDER			0x0083
#define CODE_MODE_ORDER			"\x83\x00"
//#define CODE_MODE_ALLORDER		0x0084
#define CODE_MODE_ALLORDER		"\x84\x00"
//#define CODE_MODE_LOOP			0x0085
#define CODE_MODE_LOOP			"\x85\x00"
//#define CODE_MODE_SINGLE		0x0086
#define CODE_MODE_ALLLOOP		"\xb2\x00"
#define CODE_MODE_SINGLE		"\x86\x00"
//#define CODE_MODE_RANDOM		0x0087
#define CODE_MODE_RANDOM		"\x87\x00"
//#define CODE_MODE_SCN			0x0088
#define CODE_MODE_SCN			"\x88\x00"
//#define CODE_MODE_PAUSE			0x0089
#define CODE_MODE_PAUSE			"\x89\x00"
//#define CODE_MODE_START			0x008A
#define CODE_MODE_START			"\x8A\x00"
//#define CODE_MODE_SD			0x008B
#define CODE_MODE_SD			"\x8b\x00"
//#define CODE_MODE_SDR			0x008C
#define CODE_MODE_SDR			"\x8c\x00"
//#define CODE_MODE_USB			0x008D
#define CODE_MODE_USB			"\x8d\x00"
//#define CODE_MODE_USBR			0x008E
#define CODE_MODE_USBR			"\x8e\x00"
#define CODE_MODE_CUR			0x008F
//#define CODE_SPACE				0x0080
#define CODE_SPACE				"\x80\x00"
#define CODE_ELLIPSIS			0x0090
#define CODE_FOLDER				0x0091
#define CODE_FILE				0x0092

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */
extern void OLED_TextW(U16 *code_buf, U16 pos_horizontal, U16 pos_vertical,
		U8 font);
extern void OLED_TextA(U8 *code_buf, U16 pos_horizontal, U16 pos_vertical,
		U8 font);
extern void OLED_TextA_Rev(U8 *code_buf, U16 PosX, U16 PosY, U8 font, U8 mode);
extern void OLED_draw_roll(U8 PosX, U8 PosY, U16 * codeBuf, U8 codeNum);
extern void OLED_Draw_TextRoll(U16 *CodeBuf, S16 PosX, U16 PosY, U16 StrWidth);
extern void OLED_Draw_TextRoll24(U8 *CodeBuf, S16 PosX, U16 PosY, U16 StrWidth);
extern U16 GetDrawTextWidthA(U8 *Code, U8 font);
extern void ConvertUnicodeToGBCode(U8 *code, U16 len, U8 flag);
extern void ConvertUTF8ToGBCode(U8 *utf8code, U16 utf8len, U8 *GBcode,
		U16 GBcodelen);

/*
 * Private variables and functions
 */

#endif
