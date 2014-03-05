/*****************************************************************************
 * DISCLAIMER
 *
 * This software is supplied by Renesas Electronics Corporation and is only
 * intended for use with Renesas products. No other uses are authorized.
 * This software is owned by Renesas Electronics Corporation and is protected
 * under all applicable laws, including copyright laws.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES
 * REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY,
 * INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY
 * DISCLAIMED.
 *
 * TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
 * ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
 * FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES
 * FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS
 * AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 *
 * Renesas reserves the right, without notice, to make changes to this
 * software and to discontinue the availability of this software.
 * By using this software, you agree to the additional terms and
 * conditions found by accessing the following link:
 * http://www.renesas.com/disclaimer
 *****************************************************************************/
/* Copyright (C) 2010 Renesas Electronics Corporation. All rights reserved.  */
/*****************************************************************************
 * System Name  : AE1-LF Car Audio Demo
 * File Name    : if_evolume.c
 * Abstract     : interface of evolume
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AE1-LF demo board
 * Description  : This is interface of evolume.
 * Operation    : none
 * Limitation   : This file can be only used as sample code for AE1-LF.
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "driver_iic.h"
#include "driver_evolume.h"
#include "if_evolume.h"

/*****************************************************************************
 Macro definitions
 *****************************************************************************/

/*****************************************************************************
 Private variables and functions
 *****************************************************************************/

/*****************************************************************************
 * ID                : 
 * Outline           : Set the volume
 * Include           : none
 * Declaration       : StdRetType If_EV_SetVolume((S8)S8Volume)
 * Description       : Volume
 * Argument          : S8Volume is from 0 to 99 
 * Return Value      : Standard Error code, ERROR1 means I2C bus busy
 * Calling Functions :
 *****************************************************************************/
StdRetType If_EV_SetVolume(S8 S8Volume)
{
	return Drv_EV_SetVolume(S8Volume);
}

/*****************************************************************************
 * ID                : 
 * Outline           : Set the LF speaker volume
 * Include           : none
 * Declaration       : StdRetType If_EV_SetVolumeOfLF((S8)S8Volume)
 * Description       : Volume adjustment
 * Argument          : S8Volume is from 0 to 99
 * Return Value      : Standard Error code, ERROR1 means I2C bus busy
 * Calling Functions :
 *****************************************************************************/
StdRetType If_EV_SetVolumeOfLF(S8 S8Volume)
{
	return Drv_EV_SetVolumeOfLF(S8Volume);
}

/*****************************************************************************
 * ID                : 
 * Outline           : Set the RF speaker volume
 * Include           : none
 * Declaration       : StdRetType If_EV_SetVolumeOfRF((S8)S8Volume)
 * Description       : Volume adjustment
 * Argument          : S8Volume is from 0 to 99
 * Return Value      : Standard Error code, ERROR1 means I2C bus busy
 * Calling Functions :
 *****************************************************************************/
StdRetType If_EV_SetVolumeOfRF(S8 S8Volume)
{
	return Drv_EV_SetVolumeOfRF(S8Volume);
}

/*****************************************************************************
 * ID                : 
 * Outline           : Set the LR speaker volume
 * Include           : none
 * Declaration       : StdRetType If_EV_SetVolumeOfLR((U8)S8Volume)
 * Description       : S8Volume adjustment
 * Argument          : S8Volume is from 0 to 63
 * Return Value      : Standard Error code, ERROR1 means I2C bus busy
 * Calling Functions :
 *****************************************************************************/
StdRetType If_EV_SetVolumeOfLR(S8 S8Volume)
{
	return Drv_EV_SetVolumeOfLR(S8Volume);
}

/*****************************************************************************
 * ID                : 
 * Outline           : Set the RR speaker volume
 * Include           : none
 * Declaration       : StdRetType If_EV_SetVolumeOfRR((S8)S8Volume)
 * Description       : Volume adjustment
 * Argument          : S8Volume is from -15 to +15
 * Return Value      : Standard Error code, ERROR1 means I2C bus busy
 * Calling Functions :
 *****************************************************************************/
StdRetType If_EV_SetVolumeOfRR(S8 S8Volume)
{
	return Drv_EV_SetVolumeOfRR(S8Volume);
}

/*****************************************************************************
 * ID                : 
 * Outline           : Set input channel
 * Include           : none
 * Declaration       : StdRetType If_EV_SetAudioInput((S8)S8InputSource)
 * Description       : 
 * Argument          : Channel number is from 0 to 3
 * Return Value      : Standard Error code, ERROR1 means I2C bus busy
 * Calling Functions :
 *****************************************************************************/
StdRetType If_EV_SetAudioInput(U8 U8InputSource)
{
	return Drv_EV_SetAudioInput(U8InputSource);
}

/****************************************************************************
 * ID                : 
 * Outline           : Set Bass Value
 * Include           : none
 * Declaration       : StdRetType If_EV_SetAudioBass((S8)S8Bass)
 * Description       : 
 * Argument          : Bass Step is +/- 15 step
 * Return Value      : Standard Error code, ERROR1 means I2C bus busy
 * Calling Functions :
 *****************************************************************************/
StdRetType If_EV_SetAudioBass(S8 S8Bass)
{
	return Drv_EV_SetAudioBass(S8Bass);
}

/****************************************************************************
 * ID                : 
 * Outline           : Set treble Value
 * Include           : none
 * Declaration       : StdRetType If_EV_SetAudioTreble((S8)S8Treble)
 * Description       : 
 * Argument          : Treble Step is +/- 16 step
 * Return Value      : Standard Error code, ERROR1 means I2C bus busy
 * Calling Functions :
 *****************************************************************************/
StdRetType If_EV_SetAudioTreble(S8 S8Treble)
{
	return Drv_EV_SetAudioTreble(S8Treble);
}

/*****************************************************************************
 * ID                : 
 * Outline           : If_EV_GetCommBusyState
 * Include           : none
 * Declaration       : BOOLEAN If_EV_GetCommBusyState(void)
 * Description       : Get Communication busy state
 * Argument          : None
 * Return Value      : TURE - busy, FALSE - idle
 * Calling Functions :
 *****************************************************************************/
BOOLEAN If_EV_GetCommBusyState(void)
{
	return Drv_I2C_GetI2CBusyState();
}
/* End of file */
