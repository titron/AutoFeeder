/*
 * if_disp.h
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */
#ifndef __IF_DISP_H__
#define __IF_DISP_H__

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
#define DISP_ROLL_END			(U8)0
#define DISP_ROLL_ING			(u8)1

#define DISP_SCREEN_START_LINE 	(U8)0
#define DISP_SCREEN_HALFT_LINE 	(U8)64

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */
extern void if_Disp_Init(void);
extern void if_Disp_SetStartLine(U8 line);
#if 0
extern void if_Disp_PowerDown( void );
extern void if_Disp_SetRoll(U8 upline,U8 downline,U8 downup ,U16 interva);
extern void if_Disp_RollEnd( void );
extern void if_Disp_SetStartLine(U8 line);
#endif
extern U8 DispRollEnd;

/*
 * Private variables and functions
 */

#endif
/* End of File */
