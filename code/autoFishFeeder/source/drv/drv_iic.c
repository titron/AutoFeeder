/*
 * drv_iic.c
 *
 *  Created on: 3/6/2014
 *      Author: titron
 *       email: hawkdtw@gmail.com
 */

/*
 * Includes
 */
#include "BasicType.h"
#include "sfr_r82b.h"
#include "config.h"
#include "drv_iic.h"

/*
 * Typedef
 */

/*
 * Macro
 */

/*
 * Imported global variables and functions (from other files)
 */

/*
 * Exported global variables and functions (to be accessed by other files)
 */

/*
 * Private variables and functions
 */
static U8* pI2CDataBuf;
static U16 I2CDataLength;
static U8 I2CStatus;
#if 0
static U8 I2CSlaveAddr;
#endif

/*
 * drv_I2C_Init
 */
void drv_I2C_Init(void)
{
	/* I2C mode init */
	mstiic = (U8) ON; /* Turn off standby bit */
	iicsel = (U8) ON; /* Set module as I2C */
	ssums_ssmr2 = (U8) 0;
	iccr1 &= 0xF0;
	iccr1 |= 0x5; /* fBLCK/100 */
	ice_iccr1 = ON; /* Enable this module */

	stop_icsr = OFF; /* Clear stop flag */

	nakie_icier = OFF;
	rie_icier = OFF; /* Receive interrupt */
	teie_icier = OFF;
	tie_icier = OFF; /* Transmit interrupt */
	stie_icier = OFF;
	iicic = (U8) 1; /* interrupt level */
	I2CStatus = I2CBUS_FREE;
}

/*
 * drv_I2C_MasterSend
 */
StdRetType drv_I2C_MasterSend(U8 SlaveAddr, U8* pData, U16 Length)
{
	if (bbsy_iccr2 != 0) /* Check bus busy */
	{
		return ERROR1 ; /* Bus is busy */
	}
	mst_iccr1 = ON; /* Master mode */
	trs_iccr1 = ON; /* Transmit */
	iccr2 = START_COND;
	pI2CDataBuf = pData;
	I2CDataLength = Length; /* Include the address */
	I2CStatus = TRANSMIT_HEAD;
#if 0
	I2CSlaveAddr = SlaveAddr; /* Backup slave address */
#endif
	nackf_icsr = FALSE;
	nakie_icier = OFF;
	rie_icier = OFF; /* Receive interrupt */
	stie_icier = OFF;
	acke_icier = TRUE;
	if (tdre_icsr == 1)
	{
		icdrt = (SlaveAddr << 1) & (U8) 0xFE;
		teie_icier = ON;
	}
	else
	{
		return ERROR2 ;
	}
	return DONE ;
}

#if 0
/*
 * drv_I2C_MasterReceive
 */
StdRetType drv_I2C_MasterReceive(U8 SlaveAddr, U8* pData, U16 Length)
{
	if(bbsy_iccr2 != FALSE) /* Check bus busy */
	{
		return ERROR1; /* Bus is busy */
	}
	mst_iccr1 = ON; /* Master mode */
	trs_iccr1 = ON; /* Transmit */
	iccr2 = START_COND; /* Start condition generate */
	pI2CDataBuf = pData;
	I2CStatus = RECEIVE_HEAD;
	I2CSlaveAddr = SlaveAddr; /* Backup slave address */
	I2CDataLength = Length;
	ackbt_icier = LOW; /* Ack bit is low */
	nakie_icier = OFF;
	rie_icier = OFF; /* Receive interrupt */
	tie_icier = OFF; /* Transmit interrupt */
	stie_icier = OFF;
	if(tdre_icsr == TRUE)
	{
		icdrt = (SlaveAddr << 1) | 0x01;
		teie_icier = ON;
	}
	else
	{
		return ERROR2;
	}
	return DONE;
}
#endif

/*
 * drv_I2C_Int
 */
void drv_I2C_Int(void)
{
	/*	asm("fset i"); */
	switch (I2CStatus)
	{
	case TRANSMIT_HEAD :
		if (tend_icsr == 1) /* Used only for transmit */
		{
			if (ackbr_icier == 1) /* Resend if receive 1 unexpected high ACK*/
			{
				nackf_icsr = 0;
				/* Note: 1. Remove the resend to avoid the iic interrupt 
				 generation is no-end.
				 2. Add the error log here. */
				/* drv_I2C_MasterSend(I2CSlaveAddr, pI2CDataBuf, I2CDataLength); */
//				Service_Error_Log(ERROR_IIC_NOACK);
			}
			else
			{
				if (I2CDataLength == (U16) 0)
				{
					I2CStatus = TRANSMIT_END;
					iccr2 = STOP_COND;
					stie_icier = ON;
				}
				else
				{
					I2CStatus = TRANSMIT_DATA;
					icdrt = *pI2CDataBuf;
					pI2CDataBuf++;
					I2CDataLength--;
					teie_icier = OFF;
					tie_icier = ON;
				}
			}
		}

		break;
	case TRANSMIT_DATA :
		if (tdre_icsr == 1) /* Used only for transmit */
		{
			if (I2CDataLength == (U16) 0)
			{
				teie_icier = ON;
				tie_icier = OFF;
				I2CStatus = TRANSMIT_END;
			}
			else
			{
				icdrt = *pI2CDataBuf;
				pI2CDataBuf++;
				I2CDataLength--;
			}
		}
		break;
	case TRANSMIT_END :
		if (tend_icsr == 1) /* Used only for transmit */
		{
			teie_icier = OFF;
			tend_icsr = FALSE; /* Clear the status flag */
			stop_icsr = FALSE;
			iccr2 = STOP_COND;
			stie_icier = ON;
		}
		if (stop_icsr == 1)
		{
			stop_icsr = FALSE;
			stie_icier = OFF;
			mst_iccr1 = (U8) 0;
			trs_iccr1 = (U8) 0;
			I2CStatus = I2CBUS_FREE; /* Mark of communication ending */
		}
		break;
	case RECEIVE_HEAD :
		if (tend_icsr == 1) /* Used only for receive */
		{
			tend_icsr = FALSE; /* Clear the status flag */
			trs_iccr1 = OFF; /* Switch to receive mode */
			tdre_icsr = FALSE;
			teie_icier = OFF;
			rie_icier = ON;
			if (I2CDataLength == (U16) 1)
			{
				rcvd_iccr1 = ON; /* Disable next receive */
				I2CStatus = RECEIVE_END;
			}
			else
			{
				rcvd_iccr1 = OFF;
				I2CStatus = RECEIVE_DATA;
			}
			*pI2CDataBuf = icdrr; /* Dummy read for starting receive */
		}
		break;
	case RECEIVE_DATA :
		if (rdrf_icsr == 1)
		{
			/* rdrf_icsr = FALSE;	NO need */
			I2CDataLength--;
			if (I2CDataLength == (U16) 1)
			{
				rcvd_iccr1 = ON; /* Disable next receive */
				I2CStatus = RECEIVE_END;
			}
			*pI2CDataBuf = icdrr;
			pI2CDataBuf++;
		}
		break;
	case RECEIVE_END :
		if (rdrf_icsr == 1)
		{
			rdrf_icsr = FALSE;
			stop_icsr = FALSE; /*Clear stop flag before the command */

			iccr2 = STOP_COND;
			stie_icier = ON;
		}
		if (stop_icsr == 1)
		{
			*pI2CDataBuf = icdrr;
			stop_icsr = FALSE;
			stie_icier = OFF;
			mst_iccr1 = (U8) 0;
			trs_iccr1 = (U8) 0;
			I2CStatus = I2CBUS_FREE; /* Mark of communication ending */
		}
		break;
	case I2CBUS_FREE :
		break;
	default:
		break;
	}
}

/*
 * drv_I2C_GetI2CBusyState
 */
BOOLEAN drv_I2C_GetI2CBusyState(void)
{
	BOOLEAN ret;

	if (bbsy_iccr2 == 1)
	{
		ret = TRUE;
	}
	else
	{
		ret = FALSE;
	}

	return ret;
}
/* End of File */
