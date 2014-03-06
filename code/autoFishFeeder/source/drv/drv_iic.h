/*
 * drv_iic.h
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */
#ifndef __DRIVER_IIC_H__
#define __DRIVER_IIC_H__
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
/* Status of I2C */
#define TRANSMIT_HEAD		(U8)1
#define TRANSMIT_DATA		(U8)2
#define TRANSMIT_END		(U8)3
#define RECEIVE_HEAD		(U8)4
#define RECEIVE_DATA		(U8)5
#define RECEIVE_END			(U8)6
#define I2CBUS_FREE			(U8)7

#define START_COND			(U8)0xB0
#define STOP_COND			(U8)0x30

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */
extern void drv_I2C_Init(void);
extern void drv_I2C_Int(void);
extern StdRetType drv_I2C_MasterSend(U8 SlaveAddr, U8 * pData, U16 Length);
#if 0
extern StdRetType Drv_I2C_MasterReceive(U8 SlaveAddr, U8 * pData, U16 Length);
#endif
extern BOOLEAN drv_I2C_GetI2CBusyState(void);

/*
 * Private variables and functions
 */

#endif
/* End of File */
