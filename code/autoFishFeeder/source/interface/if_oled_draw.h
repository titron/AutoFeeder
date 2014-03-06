/*
 * if_oled_draw.h
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */
#ifndef __LCD_DRAW_H__
#define __LCD_DRAW_H__

/*
 * Includes
 */

/*
 * Typedef
 */
typedef struct
{
	U8 bmp_no;
	U16 bmp_width;
	U16 bmp_hight;
	U8 const * bmp_address;
} BMPINFO;

/*
 * Macro
 */
#define BMP_LOGO_NO 					0U
#define BMP_CLOCK_NO 					1U
#define BMP_FISH_NO 					2U

#define PLAY_TIME_PROGRESS_LEN 			100U
#define PLAY_TIME_PROGRESS_HIGHT 		6U
#define PLAY_TIME_PROGRESS_FILL_HIGHT 	4U

#define REDRAW							(U8)0
#define UPDATA							(U8)1

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */
extern void OLED_DrawLine(U16 PosStartX, U16 PosStartY, U16 PosEndX,
		U16 PosEndY, U8 col);
extern void OLED_DrawLineT(U16 PosStartX, U16 PosStartY, U16 PosEndX,
		U16 PosEndY, U8 col);
extern void OLED_DrawDot(U8 PosStartX, U8 PosStartY);
extern void OLED_DrawBox(U16 PosStartX, U16 PosStartY, U16 PosEndX, U16 PosEndY,
		U8 fill, U8 col1, U8 col2);
extern void OLED_DrawBmp(U16 PosStartX, U16 PosStartY, U8 BmpNo);
extern void Draw_PlayTimeProgressFrame(U16 PosStartX, U16 PosStartY,
		U16 Progress, U8 flag);
extern void if_disp_clear(void);

/*
 * Private variables and functions
 */
#endif

