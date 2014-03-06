/*
 * basictype.h
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */
#ifndef _BASIC_TYPE_H
#define _BASIC_TYPE_H

/*
 * Includes
 */

/*
 * Typedef
 */
typedef unsigned char U8;
typedef signed char S8;
typedef unsigned short U16;
typedef signed short S16;
typedef unsigned long U32;
typedef signed long S32;
typedef unsigned long long U64;
typedef signed long long S64;

typedef volatile unsigned char VU8;
typedef volatile signed char VS8;
typedef volatile unsigned short VU16;
typedef volatile signed short VS16;
typedef volatile unsigned long VU32;
typedef volatile signed long VS32;
typedef volatile unsigned long long VU64;
typedef volatile signed long long VS64;

/* Some program may use these basic type define */
typedef unsigned char BOOLEAN;
typedef unsigned char INT8U;
typedef signed char INT8S;
typedef unsigned short INT16U;
typedef signed short INT16S;
typedef unsigned long INT32U;
typedef signed long INT32S;
typedef float FP32;
typedef double FP64;

/* It is used in SH header file */
typedef signed char _SBYTE;
typedef unsigned char _UBYTE;
typedef signed short _SWORD;
typedef unsigned short _UWORD;
typedef signed int _SINT;
typedef unsigned int _UINT;
typedef signed long _SDWORD;
typedef unsigned long _UDWORD;
typedef signed long long _SQWORD;
typedef unsigned long long _UQWORD;

typedef volatile struct
{
	VU8 b0 :1;
	VU8 b1 :1;
	VU8 b2 :1;
	VU8 b3 :1;
	VU8 b4 :1;
	VU8 b5 :1;
	VU8 b6 :1;
	VU8 b7 :1;
} bit8_type;

typedef volatile struct
{
	VU16 b0 :1;
	VU16 b1 :1;
	VU16 b2 :1;
	VU16 b3 :1;
	VU16 b4 :1;
	VU16 b5 :1;
	VU16 b6 :1;
	VU16 b7 :1;
	VU16 b8 :1;
	VU16 b9 :1;
	VU16 b10 :1;
	VU16 b11 :1;
	VU16 b12 :1;
	VU16 b13 :1;
	VU16 b14 :1;
	VU16 b15 :1;
} bit16_type;

typedef volatile struct
{
	VU32 b0 :1;
	VU32 b1 :1;
	VU32 b2 :1;
	VU32 b3 :1;
	VU32 b4 :1;
	VU32 b5 :1;
	VU32 b6 :1;
	VU32 b7 :1;
	VU32 b8 :1;
	VU32 b9 :1;
	VU32 b10 :1;
	VU32 b11 :1;
	VU32 b12 :1;
	VU32 b13 :1;
	VU32 b14 :1;
	VU32 b15 :1;
	VU32 b16 :1;
	VU32 b17 :1;
	VU32 b18 :1;
	VU32 b19 :1;
	VU32 b20 :1;
	VU32 b21 :1;
	VU32 b22 :1;
	VU32 b23 :1;
	VU32 b24 :1;
	VU32 b25 :1;
	VU32 b26 :1;
	VU32 b27 :1;
	VU32 b28 :1;
	VU32 b29 :1;
	VU32 b30 :1;
	VU32 b31 :1;
} bit32_type;

typedef volatile struct
{
	VU8 low;
	VU8 high;
} byte2_type;

typedef volatile struct
{
	VU8 lowlow;
	VU8 lowhigh;
	VU8 highlow;
	VU8 highhigh;
} byte4_type;

typedef volatile struct
{
	VU16 low;
	VU16 high;
} word2_type;

/* Standard Return value define */
typedef U8 Std_ReturnType;
typedef U8 StdRetType;

/************************* Additional TYPEDEF **********************************/
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;
typedef signed char s8;
typedef signed short s16;
typedef signed long s32;
typedef signed long long s64;

/*
 * Macro
 */
#define YES                         (U8)1
#define NO                          (U8)0
#define TRUE                        (U8)1
#define FALSE                       (U8)0
#define OK                          (U8)1
#define NG                          (U8)0
#define HIGH                        (U8)1
#define LOW                         (U8)0
#define	ON							(U8)1
#define	OFF							(U8)0
#define NULL_POINT					(void*)0
#define NONE						(U8)0xFF
#define PULL_UP						(U8)1
#define PULL_DOWN					(U8)0

#define	DONE						(U8)0
#define	ERROR1						(U8)1
#define	ERROR2						(U8)2
#define	ERROR3						(U8)3
#define	ERROR4						(U8)4
#define	ERROR5						(U8)5
#define	ERROR6						(U8)6
#define	ERROR7						(U8)7
#define	ERROR8						(U8)8
#define	ERROR9						(U8)9
#define	ERROR10						(U8)10
#define	ERROR11						(U8)11
#define	ERROR12						(U8)12
#define	ERROR13						(U8)13
#define	ERROR14						(U8)14
#define	ERROR15						(U8)15

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */

/*
 * Private variables and functions
 */

#endif /* _BASIC_TYPE_H */
/* End of file */
