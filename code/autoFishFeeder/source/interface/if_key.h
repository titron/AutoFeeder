/*
 * if_key.h
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */
#ifndef __IF_KEY_H__
#define __IF_KEY_H__

/*
 * Includes
 */
#include "basictype.h"
#include "drv_key.h"

/*
 * Typedef
 */

/*
 * Macro
 */
#define KEY_STATE_INIT				(U8)0
#define KEY_STATE_IDLE				(U8)1
#define KEY_STATE_PRESS_JITTER		(U8)2
#define KEY_STATE_PRESS_STABLE		(U8)3
#define KEY_STATE_RESTORE_JITTER 	(U8)4

#define DOWN						(U8)0
#define UP							(U8)1

/* Judge time number of Verified key, when clock is high-speed OCO */
#define KEY_JUDGE_TIMES_HIGHSPEED	(U8)3
/* Judge time number of Verified key, when clock is low-speed OCO */
#define KEY_JUDGE_TIMES_LOWSPEED	(U8)2

/* Key ID */
#define KEY_ROTARY2					(U8)7
#define KEY_ROTARY1					(U8)6
#define KEY_1						(U8)5
#define KEY_2						(U8)4
#define KEY_3						(U8)3
#define KEY_4						(U8)2
#define KEY_5						(U8)1
#define KEY_6						(U8)0

/* Event ID of event type - key */
#define EVENT_KEY_NONE					(U8)0x00
#define EVENT_KEY_ROTARY1_DOWN			(U8)0x01
#define EVENT_KEY_ROTARY2_DOWN			(U8)0x02
#define EVENT_KEY_1_DOWN				(U8)0x03
#define EVENT_KEY_2_DOWN				(U8)0x04
#define EVENT_KEY_3_DOWN				(U8)0x05
#define EVENT_KEY_4_DOWN				(U8)0x06
#define EVENT_KEY_5_DOWN				(U8)0x07
#define EVENT_KEY_6_DOWN				(U8)0x08
#define EVENT_KEY_ROTARY1_UP			(U8)0x09
#define EVENT_KEY_ROTARY2_UP			(U8)0x0A
#define EVENT_KEY_1_UP					(U8)0x0B
#define EVENT_KEY_2_UP					(U8)0x0C
#define EVENT_KEY_3_UP					(U8)0x0D
#define EVENT_KEY_4_UP					(U8)0x0E
#define EVENT_KEY_5_UP					(U8)0x0F
#define EVENT_KEY_6_UP					(U8)0x10
#define EVENT_KEY_ROTARY2_PRESSED_xS	(U8)0x11
#define EVENT_KEY_RKEY1_RKEY2_KEY1_DOWN	(U8)0x12
#define EVENT_KEY_UNDEFINED				(U8)0xFF

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */
extern U16 U16TimerCountScanKey;
extern U16 U16TimerCountPressedKey;

/* extern void If_Key_InitKey(void); */
extern void if_Key_Scan(void);
extern U8 if_Key_GetState(U8 U8KeyID);
extern U8 if_Key_GetEvent(void);
extern void if_Key_ClearEvent(void);

/*
 * Private variables and functions
 */

#endif
/* End of File */
