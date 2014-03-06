/*
 * drv_key.h
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */
#ifndef __DRV_KEY_H__
#define __DRV_KEY_H__
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
#define GET_KEY_STATE()				p0
#define KEY_INIT_VALUE				(U8)0xFF

#define KEY_VALUE_NULL				(U8)0xFF
#define KEY_VALUE_ROTARY2			(U8)0x7F
#define KEY_VALUE_ROTARY1			(U8)0xBF
#define KEY_VALUE_6					(U8)0xDF
#define KEY_VALUE_5					(U8)0xEF
#define KEY_VALUE_4					(U8)0xF7
#define KEY_VALUE_3					(U8)0xFB
#define KEY_VALUE_2					(U8)0xFD
#define KEY_VALUE_1					(U8)0xFE
#define KEY_VALUE_RKEY1_RKEY2_KEY1	(U8)0x3E

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */
extern void drv_Key_InitKey(void);

/*
 * Private variables and functions
 */

#endif
/* End of File */
