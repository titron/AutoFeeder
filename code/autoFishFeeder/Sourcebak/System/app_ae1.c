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
 * File Name    : app_ae1.c
 * Abstract     : application for AE1-L.
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AE1-LF demo board
 * Description  : AE1-L communication code.
 *              :   send command;
 *              :   status process;
 *              :   initialize AE1-L;
 *              :   USB/SD plug & play
 *              :   play back
 * Operation    : none
 * Limitation   : This file can be only used as sample code for AE1-LF.
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "app_ae1.h"
#include "app_host.h"
#include "disp_widget.h"
#include "mcu_depend.h"
#include "app_evolume.h"/* Adjust volume */
#include "service_general.h"
/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
/* **** Initialize AE1 default settings definition **** */
/* ID = 00H */
#define ID00_CDB7_DETECT_USB          (U8)0x01/* CDB[7], Startup status */
#define ID00_CDB8_FILE_ORDER          (U8)0x00/* CDB[8], File system storage order */
#define ID00_CDB8_FOLDER_ORDER        (U8)0x40/* CDB[8], File system storage order */
#ifdef FIRM_VER_080_USED
#else
#define ID00_CDB8_FOLDER_ORDER_SORT   (U8)0x41/* CDB[8], File system storage order */
#endif
/* ID = 41H */
#define ID41_CDB7_USED_DECODER        (U8)0x00/* CDB[7], used decoder: MP3 */
/* ID = 50H */
#define ID50_CDB7_DAC_SELECT          (U8)0x01/* CDB[7], DAC selection */
#define ID50_CDB8_DAC_FORMAT          (U8)0x01/* CDB[8], DAC parameter */
#define ID50_CDB9_SD_IF               (U8)0x00/* CDB[9], SD I/F */
#define ID50_CDB10_SD_IF_CLK          (U8)0x09/* CDB[10], Serial flash I/F clock */
#define ID50_CDB17_MAX_FOLDER_LEVEL   (U8)0x07/* CDB[17], max folder layer number */
#define ID50_CDB18_MAX_FILE_NUM_H     (U8)0xFF/* CDB[18], max file number,MSB */
#define ID50_CDB19_MAX_FILE_NUM_L     (U8)0xFF/* CDB[19], max file number,LSB */
#ifdef  FIRM_VER_080_USED
#define ID50_CDB20_MAX_FOLDER_NUM_H   (U8)0x07/* CDB[20], max folder number,MSB */
#define ID50_CDB21_MAX_FOLDER_NUM_L   (U8)0xD0/* CDB[21], max folder number,LSB */
#else
#define ID50_CDB20_MAX_FOLDER_NUM_H   (U8)0x03/* CDB[20], max folder number,MSB */
#define ID50_CDB21_MAX_FOLDER_NUM_L   (U8)0xE7/* CDB[21], max folder number,LSB */
#endif
#define ID50_CDB22_MAX_TAG_LEN_H      (U8)0x00/* CDB[22], max tag length, MSB */
#define ID50_CDB23_MAX_TAG_LEN_L      (U8)0x40/* CDB[23], max tag length, LSB */
#define ID50_CDB24_CHAR_CODE_CONVERSE (U8)0x00/* CDB[24], character code conversion */
#ifdef  FIRM_VER_080_USED
#define ID50_CDB25_LOCAL_CODE         (U8)0x00/* CDB[25], local language code */
#define ID50_CDB26_PLAY_OPTION        (U8)0x00/* CDB[26], play option */
#define ID50_CDB27_SCANTIME           (U8)0x0A/* CDB[27], scan time */
#define ID50_CDB28_STS_FRM_LEN_H      (U8)0x80/* CDB[28], max status frame length, MSB */
#define ID50_CDB29_STS_FRM_LEN_L      (U8)0xC0/* CDB[29], max status frame length, LSB */
#define ID50_CDB30_TIMEOUT_VALUE      (U8)0x46/* CDB[30], command timeout value */
#else
#define ID50_CDB25_PLAY_OPTION        (U8)0x00/* CDB[25], play option */
#define ID50_CDB26_SCANTIME           (U8)0x0A/* CDB[26], scan time */
#define ID50_CDB27_STS_FRM_LEN_H      (U8)0x80/* CDB[27], max status frame length, MSB */
#define ID50_CDB28_STS_FRM_LEN_L      (U8)0xC0/* CDB[28], max status frame length, LSB */
#define ID50_CDB29_TIMEOUT_VALUE      (U8)0x46/* CDB[29], command timeout value */
#endif
/* ID = 53H */
#define ID53_CDB7_MAX_FILES_NUM       (U8)0x27/* CDB[7]&[8], Maximum number of files: 9999 files */
#define ID53_CDB8_MAX_FILES_NUM       (U8)0x07
#define ID53_CDB9_MAX_FILES_NUM       (U8)0x03/* CDB[9]&[10], Maximum number of folders: 999 folders */
#define ID53_CDB10_MAX_FILES_NUM      (U8)0xE7
#define ID53_CDB11_MAX_TAG_LEN        (U8)0x00/* CDB[11]&[12], Maximum tag length: 128 bytes */
#define ID53_CDB12_MAX_TAG_LEN        (U8)0x80
#define ID53_CDB13_MAX_STS_FRM_LEN    (U8)0x81/* CDB[13]&[14], Maximum status frame length: 268 bytes */
#define ID53_CDB14_MAX_STS_FRM_LEN    (U8)0x0C
#define ID53_CDB15_MAX_FOLDER_LVL     (U8)0x07/* CDB[15], Maximum number of folder levels: 8 levels */
#define ID53_CDB16_IPOD_PWR_SUSPEND   (U8)0x00/* CDB[16]&[17], iPod power (suspend): 0 */
#define ID53_CDB17_IPOD_PWR_SUSPEND   (U8)0x00
#define ID53_CDB18_IPOD_PWR_NORMAL    (U8)0x00/* CDB[18]&[19], iPod power (normal): 0 */
#define ID53_CDB19_IPOD_PWR_NORMAL    (U8)0x00
#define ID53_CDB20_IPOD_PWR_ENABLE    (U8)0x00/* CDB[20], iPod power enable: Do not enable extra power */

/* Select root folder number */
#define ROOT_FOLDER_NUM               0x02/* NOTE: MODIFY BASED ON CMD(00H) CDB8 IN
                                               FUNCTION: sendCmd_USBSDConnection()
                                             root number based on file system turns
                                             0x01: when CMD(00H) CDB8 = 00H
                                             0x02: when CMD(00H) CDB8 except 00H */

/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/

/*****************************************************************************
 Private variables and functions
 *****************************************************************************/
/* *** State related definition start *** */
/* AE1 task and sub-task state definition */
e_AE1Task EgAE1Task = AE1_POWER_DOWN;/* AE1 task state */

/*** Connect start ***/
/* AE1-L connect guard timer */
U32 U32gAE1ConnectGuardTimer = (U32) 0;
/*** Connect end ***/

/*** Switch file & folder start ***/
/* Switch folder number */
enum_getFolderInfoCtl_type getFolderInfoCtl;
/*** Switch file & folder end ***/

/*** To check whether can get music information or not start ***/
BOOLEAN vCanGetMusicInfo = FALSE;
/*** To check whether can get music information or not end ***/


/* Record spontaneous STS when do AE1 task */
/* *** State related definition end *** */

/* *** Command transmission related variable definition start *** */

/* Check playback time in cycle loop */
U16 U16gDelayInCycle = (U16) 0;
/* Re-send command delay if previous STS parameters is invalid */
U16 U16gDelayResendCmd = (U16) 0;
/* Monitor playback time for switching next file if invalid file exists */
U16 U16gMonitorPlayTime = (U16) 0;


/* *** Command transmission related variable definition end *** */

/* *** Messages definition between host-AE1, display-AE1 task start *** */
/* === Messages: host -> AE1 === */
t_MsgHostToAE1 TMsgHostToAE1;
/* === Messages: display -> AE1 === */
/* === MessageA: AE1 -> display === */
t_AE1MsgForDisplay AE1MsgForDisplay;
/* *** Messages definition between host-AE1, display-AE1 task end *** */

/* *** Save Resume/Current playback information start *** */
/* Media resume information */
resumeMediaInfo_type resumeMediaInfo;

/* End of file */
