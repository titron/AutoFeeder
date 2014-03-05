/******************************************************************************
* DISCLAIMER
*
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized.
* This software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
*
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY,
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY
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
*******************************************************************************/
/* Copyright (C) 2010 Renesas Electronics Corporation. All rights reserved. */
/******************************************************************************
* System Name	: AE1-LF Car Audio Demo
* File Name 	: driver_evolume.c
* Abstract 		: driver of e-volume
* Version 		: Ver 0.10
* Device 		: R8C/2A group, or R8C/2B group
* Tool-Chain 	: High-performance Embedded Workshop (Version 4.08.00.011)
* 				: C Compiler Package for M16C Series M3T-NC30WA(V.5.45 Release 00)
* OS 			: None
* H/W Platform 	: AE1-LF demo board
* Description 	: This is driver of E-volume.
* Operation 	: 1. lower layer driver
* Limitation 	: This program can be operated by 20MHz only.
* 				:
*******************************************************************************
* History 		: Dec.16,2010 Ver. 0.10 First Release
* 				:
*******************************************************************************/
#include "basictype.h"
#include "driver_iic.h"
#include "driver_evolume.h"

/*****************************************************************************
 Private variables and functions
 *****************************************************************************/
static U8 	U8EVDataBuffer;	 /* EV data buffer (except slave device address) */

/*****************************************************************************
 * ID                : 
 * Outline           : Set the volume
 * Include           : none
 * Declaration       : StdRetType Drv_EV_SetVolume((S8)Volume)
 * Description       : Volume adjustment
 * Argument          : Volume
 * Return Value      : Standard Error code, ERROR1 means I2C bus busy
 * Calling Functions :
 *****************************************************************************/
StdRetType Drv_EV_SetVolume(S8 Volume)
{
	S8 VolumeStep;

	if( Volume > RANGE_VOLUME_MAX ){
		Volume = RANGE_VOLUME_MAX;
	}else if ( Volume < RANGE_VOLUME_MIN ){
		Volume = RANGE_VOLUME_MIN;
	}else{
	}

	VolumeStep = (S8)0x3F - Volume;

	U8EVDataBuffer = (U8)VolumeStep;

	return Drv_I2C_MasterSend(EV_DEV_ADDR, &U8EVDataBuffer, (U16)1);
}

/*****************************************************************************
 * ID                : 
 * Outline           : Set the LF speaker volume
 * Include           : none
 * Declaration       : StdRetType Drv_EV_SetVolumeOfLF((S8)Volume)
 * Description       : LF speaker volume adjustment
 * Argument          : Volume
 * Return Value      : Standard Error code, ERROR1 means I2C bus busy
 * Calling Functions :
 *****************************************************************************/
StdRetType Drv_EV_SetVolumeOfLF(S8 Volume)
{
	S8 VolumeStep;

	if( Volume > RANGE_VOLUMELF_MAX ){
		Volume = RANGE_VOLUMELF_MAX;
	}else if( Volume < RANGE_VOLUMELF_MIN ){
		Volume = RANGE_VOLUMELF_MIN;
	}else{
	}

	VolumeStep = (S8)0x0F - Volume;

	U8EVDataBuffer = (U8)0x80 | (U8)VolumeStep;

	return Drv_I2C_MasterSend(EV_DEV_ADDR, (U8*)&U8EVDataBuffer, (U16)1);
}
/*****************************************************************************
 * ID                : 
 * Outline           : Set the RF speaker volume
 * Include           : none
 * Declaration       : StdRetType Drv_EV_SetVolumeOfRF((S8)Volume)
 * Description       : RF speaker volume adjustment
 * Argument          : Volume
 * Return Value      : Standard Error code, ERROR1 means I2C bus busy
 * Calling Functions :
 *****************************************************************************/
StdRetType Drv_EV_SetVolumeOfRF(S8 Volume)
{
	S8 VolumeStep;

	if( Volume > RANGE_VOLUMERF_MAX ){
		Volume = RANGE_VOLUMERF_MAX;
	}else if( Volume < RANGE_VOLUMERF_MIN ){
		Volume = RANGE_VOLUMERF_MIN;
	}else{
	}


	VolumeStep = (S8)0x0F - Volume;

	U8EVDataBuffer = (U8)0xA0 | (U8)VolumeStep;

	return Drv_I2C_MasterSend(EV_DEV_ADDR, (U8*)&U8EVDataBuffer, (U16)1);
}
/*****************************************************************************
 * ID                : 
 * Outline           : Set the LR speaker volume
 * Include           : none
 * Declaration       : StdRetType Drv_EV_SetVolumeOfLR((S8)Volume)
 * Description       : LR speaker volume adjustment
 * Argument          : Volume
 * Return Value      : Standard Error code, ERROR1 means I2C bus busy
 * Calling Functions :
 *****************************************************************************/
StdRetType Drv_EV_SetVolumeOfLR(S8 Volume)
{
	S8 VolumeStep;

	if( Volume > RANGE_VOLUMELR_MAX ){
		Volume = RANGE_VOLUMELR_MAX;
	}else if( Volume < RANGE_VOLUMELR_MIN ){
		Volume = RANGE_VOLUMELR_MIN;
	}else{
	}


	VolumeStep = (S8)0x0F - Volume;

	U8EVDataBuffer = (U8)0xC0 | (U8)VolumeStep;

	return Drv_I2C_MasterSend(EV_DEV_ADDR, (U8*)&U8EVDataBuffer, (U16)1);
}
/*****************************************************************************
 * ID                : 
 * Outline           : Set the RR speaker volume
 * Include           : none
 * Declaration       : StdRetType Drv_EV_SetVolumeOfRR((S8)Volume)
 * Description       : RR speaker volume adjustment
 * Argument          : Volume
 * Return Value      : Standard Error code, ERROR1 means I2C bus busy
 * Calling Functions :
 *****************************************************************************/
StdRetType Drv_EV_SetVolumeOfRR(S8 Volume)
{
	S8 VolumeStep;

	if( Volume > RANGE_VOLUMERR_MAX ){
		Volume = RANGE_VOLUMERR_MAX;
	}else if( Volume < RANGE_VOLUMERR_MIN ){
		Volume = RANGE_VOLUMERR_MIN;
	}else{
	}


	VolumeStep = (S8)0x0F - Volume;

	U8EVDataBuffer = (U8)0xE0 | (U8)VolumeStep;

	return Drv_I2C_MasterSend(EV_DEV_ADDR, (U8*)&U8EVDataBuffer, (U16)1);
}

/*****************************************************************************
 * ID                : 
 * Outline           : Set input channel
 * Include           : none
 * Declaration       : StdRetType Drv_EV_SetAudioInput((U8)InputSource)
 * Description       : 
 * Argument          : Channel number is from 0 to 3
 * Return Value      : Standard Error code, ERROR1 means I2C bus busy
 * Calling Functions :
 *****************************************************************************/
StdRetType Drv_EV_SetAudioInput(U8 InputSource)
{
	U8EVDataBuffer = InputSource;

	return Drv_I2C_MasterSend(EV_DEV_ADDR, (U8*)&U8EVDataBuffer, (U16)1);
}

/****************************************************************************
 * ID                : 
 * Outline           : Set Bass Value
 * Include           : none
 * Declaration       : StdRetType Drv_EV_SetAudioBass((S8)Bass)
 * Description       : 
 * Argument          : Bass
 * Return Value      : Standard Error code, ERROR1 means I2C bus busy
 * Calling Functions :
 *****************************************************************************/
StdRetType Drv_EV_SetAudioBass(S8 Bass)
{ 
	if(Bass > RANGE_BASS_MAX)
	{
		Bass = RANGE_BASS_MAX;
	}
	else if (Bass < RANGE_BASS_MIN)
	{
		Bass = RANGE_BASS_MIN;
	}
	else{}

	if(Bass >= (S8)0)
	{
		Bass = (S8)0x0F - Bass;
	}
	else
	{
		Bass = (S8)0x07 + Bass;
	}
	
	U8EVDataBuffer = (U8)Bass | (U8)0x60;

	return Drv_I2C_MasterSend(EV_DEV_ADDR, (U8*)&U8EVDataBuffer, (U16)1);
}

/****************************************************************************
 * ID                : 
 * Outline           : Set treble Value
 * Include           : none
 * Declaration       : StdRetType Drv_EV_SetAudioTreble((S8)Treble)
 * Description       : 
 * Argument          : Treble
 * Return Value      : Standard Error code, ERROR1 means I2C bus busy
 * Calling Functions :
 *****************************************************************************/
StdRetType Drv_EV_SetAudioTreble(S8 Treble)
{
	if(Treble > RANGE_TREBLE_MAX)
	{
		Treble = RANGE_TREBLE_MAX;
	}
	else if (Treble < RANGE_TREBLE_MIN)
	{
		Treble = RANGE_TREBLE_MIN;
	}
	else{}

	if(Treble >= (S8)0)
	{
		Treble = (S8)0x0F - Treble;
	}
	else
	{
		Treble = (S8)0x07 + Treble;
	}

	U8EVDataBuffer = (U8)Treble | (U8)0x70;

	return Drv_I2C_MasterSend(EV_DEV_ADDR, (U8*)&U8EVDataBuffer, (U16)1);
}

