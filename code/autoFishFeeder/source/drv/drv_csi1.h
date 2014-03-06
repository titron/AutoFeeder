/*
 * drv_csi1.h
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */

#ifndef __DRV_CSI1_H__
#define __DRV_CSI1_H__
/*
 * Includes
 */
#include "basictype.h"
#include "sfr_r82b.h"

/*
 * Typedef
 */

/*
 * Macro
 */
/* Flash communication bit rate */
#define FLASH_COMM_BITRATE				(U16)50000

/* Port definition */
#define SCI1_CS_ASSERT()				(p6_0 = 0)
#define SCI1_CS_DEASSERT()				(p6_0 = 1)
#define Drv_CSI1_GetReceivesData()		(u2rb)
#define Drv_CSI1_SendData(U8Data)		(u2tb = U8Data)

#define CSI1_TX_INT_ENABLE()		  	(s2tic = 0x01)
#define CSI1_TX_INT_DISABLE()	      	(s2tic = 0x00)
#define CSI1_RX_INT_ENABLE()		  	(s2ric = 0x05)
#define CSI1_RX_INT_DISABLE()         	(s2ric = 0x00)

/* Transmit Buffer Empty */
#define CSI1_TX_SHIFT_NOT_EMPTY			0
#define CSI1_TX_SHIFT_EMPTY				1
#define CSI1_TX_BUFFER_NOT_EMPTY		0
#define CSI1_TX_BUFFER_EMPTY			1
#define CSI1_RX_BUFFER_NOT_FULL			0
#define CSI1_RX_BUFFER_FULL				1
#define DRV_CSI1_IS_TX_COMPLETE()		txept_u2c0
#define DRV_CSI1_IS_TX_BUFFER_EMPTY()	ti_u2c1
#define DRV_CSI1_IS_RX_BUFFER_FULL()	ri_u2c1
#define DRV_CSI1_RX_ENABLE()		    (u2c1 |= 0x04)
#define DRV_CSI1_RX_DISABLE()           (u2c1 &= 0xFB)
#define CONTINOUS_REC_ENABLE()        	(u2c1 |= 0x20)
#define CONTINOUS_REC_DISABLE()        	(u2c1 &= 0xDF)

/* If use Clock Synchronous Serial, one port is used as CS.
 * If use real SPI, please comment the next 1 line. */
#define PORT_CS_BY_SOFTWARE

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */
extern U8 drv_CSI1_Init(U16 U16CSI1baudRateIn100bps);
extern BOOLEAN drv_CSI1_Transmit(U8* pTXBuf, U16 TXLength);
extern BOOLEAN drv_CSI1_Receive(U8* pRXBuf, U16 RXLength);

/*
 * Private variables and functions
 */
#endif
/* End of File */
