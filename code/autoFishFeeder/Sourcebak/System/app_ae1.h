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
 * File Name    : app_ae1.h
 * Abstract     : application layer header file for AE1-L.
 * Version      : 1.00
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AE1-LF demo board
 * Description  : This is the header file of application layer (AE1-L).
 * Operation    : none
 * Limitation   : This file can be only used as sample code for AE1-LF.
 *****************************************************************************
 * History      : May.15,2011 Ver. 1.00 First Release
 *****************************************************************************/
#ifndef __APP_AE1_H__
#define __APP_AE1_H__
/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "if_serial_ae1.h"
#include "app_ae1_protocol.h"

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
/* **** Device type definition(save) **** */
#define MEDIA_NUMBERS                   (U8)0x02/* Media type numbers supported */
#define MEDIA_TYPE_USB 					(U8)0x00
#define MEDIA_TYPE_SD 					(U8)0x01
#define MEDIA_TYPE_IPOD 				(U8)0x02
#define MEDIA_TYPE_INVALID              (U8)0xFF

/* **** Function select switch definition start **** */
/* debug switch definition */
//#define DEBUG_ON
/* Device being used definition */
#define SD_USED
//#define IPOD_USED
/* Media switch definition */
#define MEDIA_SWITCH_ENABLE
/* Default media selection */
#define DEFAULT_MEDIA				    MEDIA_TYPE_USB
/* if using resume function */
#define RESUME_FUNCTION_USED
/* Save more media information for resume judgment */
//#define SAVE_MORE_MEDIA_INFO
/* Folder information buffer depth
 * should >= 3 && = 2^x */
#define FOLDER_INFO_BUF_DEPTH           (U8)4
/* **** Function select switch definition end **** */

/* **** communication definition **** */
#define TIME_INFO_STS_ENABLED/* Time information STS Enable or not */
/* wait response period definition after a command is sent, in milli-second  */
#define WAIT_RESP_PERIOD_AFTER_COMMAND 	(U16)65000
#define DELAY_SEND_CMD_IN_CYCLE        	(U16)300
#define DELAY_RESEND_CMD               	(U16)200
/* Wait playback time count for find invalid file type, in milli-second  */
#define PLAYBACK_TIME_MONITOR	    	(U16)3000
/* Connect media over time value definition, in millisecond.
 * Japan side require 1min.
 * Note: this value is depended on music number. */
#define CONNECT_OVERTIME_IN_MILLISECOND (U32)60000

/* length information definition */
#define FILE_NAME_LENGTH              	(U8)64/* in bytes */
#define TAG_LENGTH                    	(U8)64/* in bytes */
#define FIRM_VER_LSI_NAME_LENGTH      	(U8)12/* in bytes */
#define FIRM_VER_LENGTH               	(U8)4/* in bytes */
#define VENDOR_ID_LENGTH              	(U8)64/* in bytes */
#define PRODUCT_ID_LENGTH             	(U8)64/* in bytes */
#define SERIAL_NUM_LENGTH             	(U8)64/* in bytes */
//#define RESUME_NAME_LENGTH             	(U8)5/* in bytes */

/* Max Volume range setting */
#define MAX_VOLUME_RANGE               	100

/* Host to AE1 message definition */
#define AE1_Message						U32
#define AE1_MSG_NULL					(AE1_Message)0x00000000
#define AE1_MSG_PLAY_PAUSE				(AE1_Message)0x00000001
#define AE1_MSG_SHIFT_REPEAT			(AE1_Message)0x00000002
#define AE1_MSG_RANDOM_SEQUENCE			(AE1_Message)0x00000004
#define AE1_MSG_SCAN_NORMAL				(AE1_Message)0x00000008
#define AE1_MSG_SHIFT_MEDIA				(AE1_Message)0x00000010
#define AE1_MSG_READ_FIRMWARE_VERSION	(AE1_Message)0x00000020
#define AE1_MSG_TEST_SDCARD				(AE1_Message)0x00000040
#define AE1_MSG_TEST_USB				(AE1_Message)0x00000080
#define AE1_MSG_UPDATE_FILE_INFO		(AE1_Message)0x00000100
#define AE1_MSG_PERIPHERAL_POWER_UP		(AE1_Message)0x00000200
#define AE1_MSG_PERIPHERAL_POWER_DOWN	(AE1_Message)0x00000400
#define AE1_MSG_PERIPHERAL_RESET		(AE1_Message)0x00000800
#define AE1_MSG_UPDATE_VOLUME			(AE1_Message)0x00001000
#define AE1_MSG_NUMBER					(U8)13

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/
/* ****State machine variable definition start **** */
/* AE1 task machine */
typedef enum
{
	AE1_POWER_DOWN = 0,
	INIT_AE1,
	DEV_DISCONNECTED,
	NO_VALID_FILE,
	PLAYBACK,
	AE1_TASK_EXECEPTION
} e_AE1Task;

/* AE1 playback state sub-state definition */
typedef enum
{
	GET_FOLDER_INFO = 0,
	GET_FOLDER_NAME,
	GET_OTHER_FOLDER_INFO,
	GET_OTHER_FOLDER_NAME,
	GET_TOTAL_TIME,
	WAIT_REGET_TOTAL_TIME,
	GET_FILE_NAME,
	GET_TAG_TITLE,
	WAIT_REGET_TAG_TITLE,
	GET_TAG_ARTIST,
	WAIT_REGET_TAG_ARTIST,
	GET_TAG_ALBUM,
	WAIT_REGET_TAG_ALBUM,
	IDLE
} e_playSubstate;

/* AE1 switch media sub-state definition */
typedef enum
{
	SWITCH_MEDIA_IDLE = 0,
	SWITCH_MEDIA_START,
	SWITCH_MEDIA_WAITING,
	SWITCH_MEDIA_DONE,
	SWITCH_MEDIA_OVERTIME
} e_switchMediaSubstate;
/* ****State machine variable definition end **** */

/* *** Message structure definition between task start *** */
/* AE1 <-> Display task &
 * AE1 <-> Host task
 * */
/* ====enum definition==== */
/* playback mode */
typedef enum
{
	ALL_FILES_NORMAL_PLAY = 0,
	ALL_FILES_SCAN,
	ALL_FILES_RANDOM,
	ALL_FILES_RANDOM_SCAN,
	ALL_FILES_REPEAT,
	ALL_FILES_REPEAT_SCAN,
	ALL_FILES_RANDOM_REPEAT,
	ALL_FILES_RANDOM_REPEAT_SCAN,
	FOLDER_NORMAL_PLAY,
	FOLDER_SCAN,
	FOLDER_RANDOM,
	FOLDER_RANDOM_SCAN,
	FOLDER_REPEAT,
	FOLDER_REPEAT_SCAN,
	FOLDER_RANDOM_REPEAT,
	FOLDER_RANDOM_REPEAT_SCAN,
	ONE_FILE_NORMAL_PLAY,
	ONE_FILE_REPEAT,
	ALL_FOLDER_1ST_FILE_SCAN,
	ALL_FOLDER_1ST_FILE_REPEAT_SCAN
} enum_playbackMode;

/* which device current file belongs to */
typedef enum
{
	USB = 0, SD, IPOD, INVALID
} enum_device;

/* file name character code */
typedef enum
{
	UNKOWN_CODE = 0, UTF_16LE, UTF_8
} enum_nameCharacterCode;

/* device connected status */
typedef enum
{
	CONNECTED = 0, DISCONNECTED
} enum_connectSts;

/* playback status */
typedef enum
{
	PLAY_STS_PLAYING = 0, PLAY_STS_PAUSE, PLAY_STS_STOP
} enum_playPause;

/* Tag information --- version */
typedef enum
{
	ID3V22 = 0,
	ID3V23,
	ID3V24,
	ID3V10,
	ID3V11,
	WMACONTENTS,
	MP4CONTENTS,
	WAVCONTENTS
} enum_tagVersion;

/* Tag information --- character code */
typedef enum
{
	UNKOWN = 0,
	UNICODE_UTF16_LE,
	UNICODE_UTF16_BE,
	UNICODE_UTF8,
	UNICODE_UTF16_WITH_BOM,
	ISO8859,
	EXCEPTION
} enum_tag_characterCode;

/* ====structure definition==== */
typedef struct
{
	enum_tagVersion version;
	enum_tag_characterCode characterCode;
	U8 length;
	U8 name[TAG_LENGTH + (U8)1];
} t_tagStruct;

/* tag information related */
typedef struct
{
	t_tagStruct title;
	t_tagStruct artistName;
	t_tagStruct AlbumName;
//t_tagStruct composer;
//t_tagStruct comments;
//trackNum;
//genre;
//year;
} struct_tagInfo;

/* File or folder name information definition */
typedef struct
{
	enum_nameCharacterCode nameCharacterCode;
	U8 nameLength;
	U8 Name[FILE_NAME_LENGTH + (U8)1];
} struc_fileFolderNameInfo_type;

/* Folder or file switch direction */
typedef enum
{
	UPSIDE = 0,/* used to get information for the 1st time */
	DOWNSIDE, CLOCKWISE, ANTI_CLOCKWISE, KEEP_SILENT
} enum_getFolderInfoCtl_type;

/* folder information */
typedef struct
{
	struc_fileFolderNameInfo_type folderName;
	U16 folderNum;
	U16 containFileNum;
	U16 firstFileNumInFolder;
} struct_folderInfo_type;

/* folder buffer structure definition */
typedef struct
{
	enum_getFolderInfoCtl_type folderDirection;/* folder direction: clockwise/anti-clockwise */
	U8 currentBufIndex;/* current buffer index */
	struct_folderInfo_type folderBuf[FOLDER_INFO_BUF_DEPTH];/* loop buffer */
} struct_folderInfoBuf_type;

/* current file related */
typedef struct
{
	BOOLEAN InfoUpdate;/* TRUE: all following info update
	 FALSE: no update or update not complete */
	enum_device device;
	struct_folderInfoBuf_type folderInfoBuf;
	struct_folderInfo_type currentFolderInfo;/* folder number which current file is contained to */
	struc_fileFolderNameInfo_type fileNameInfo;
	U16 fileNumInCurrentFolder;/* file position in current folder */
	U16 fileNum;
	U32 PlaybackTimeInSecond;
	U32 totalPlaybackTimeInSecond;
	struct_tagInfo tagInfo;
	enum_playPause PlayOrPause;/* TRUE: playback, FALSE: pause*/
} struct_currentFile;

/* device related */
typedef struct
{
	enum_connectSts connectSts;
	BOOLEAN isFileValid;/* TRUE: valid, FALSE: invalid */
	U16 totalFileNum;
	U16 totalFolderNum;
	U32 volumeID;
	U8 fileSize[FILE_SIZE_LENGTH];
} struct_device;

/* ROM version */
typedef struct
{
	U8 LSIName[FIRM_VER_LSI_NAME_LENGTH];
	U8 ver[FIRM_VER_LENGTH];
} struct_romVer;

/* Structure definition: AE1 -> Display */
typedef struct
{
	struct_device usb;
	struct_device sd;
	enum_playbackMode playbackMode;/* Scan/Random/Repeat/Combination */
	struct_currentFile currentFile;
	struct_romVer ae1Version;
} t_AE1MsgForDisplay;

/* Structure definition: Display -> AE1
 * (no need) */

/* Structure definition: AE1 -> Host */
typedef struct
{
	struct_device usb;
	struct_device sd;
} t_AE1MsgForHost;

/* Structure definition: Host -> AE1 */
typedef struct
{
	S8 S8HostToAE1FileCount;
	S8 S8HostToAE1FolderCount;
	AE1_Message AE1Message;
} t_MsgHostToAE1;
/* *** Message structure definition between task end *** */

/* **** save Resume/Current playback information start **** */
typedef struct
{
	U16 id;
#ifdef SAVE_MORE_MEDIA_INFO
U8 length;
U8 word[64];
#endif
} mediaInfoContent_type;

typedef struct
{
	mediaInfoContent_type vendor;
	mediaInfoContent_type product;
	mediaInfoContent_type serial;
} mediaInfo_type;

typedef struct
{
	U16 hour;
	U8 minute;
	U8 second;
} timeInfo_type;

/* Resume information structure definition */
typedef struct
{
	/* Used for switch folder/file */
	U16 totalFolderNum;/* total folder number */
	U16 totalFileNum;/* total file number */

	/* VoumeID & File size */
	U32 volumeID;
	U8 fileSize[FILE_SIZE_LENGTH];

	/* file related */
	U16 fileNum;/* current file number */
	timeInfo_type timeInfo;/* current playback/pause time information */

	/* resume info related[reserved] */
	U8 resumeInfo[5];/* resume information */

	/* Media related */
	U8 deviceType;/* device information */
	mediaInfo_type mediaInfo;/* media information */
} resumeInfo_type;

typedef struct
{
	resumeInfo_type usbResumeInfo;
#ifdef SD_USED
	resumeInfo_type sdResumeInfo;
#endif
} resumeMediaInfo_type;

typedef struct
{
	U16 currentFolderNum;/* folder number which current file is contained to */
	U16 totalFileNumInCurrentFolder;/* total file number in current folder */
	U16 firstFileNumInFolder;/* first file number in current folder */
	U16 filePositionInCurrentFolder;/* current file position in current folder */
	struc_fileFolderNameInfo_type fileName;/* file name */

	/* Resume information */
	resumeInfo_type resumeInfo;
} currentPlayInfo_type;

/* **** save Resume/Current playback information end **** */

/* **** save current media information start **** */
typedef struct
{
	struct_device usb;
#ifdef SD_USED
	struct_device sd;
#endif
#ifdef IPOD_USED
	struct_device ipod;
#endif
} mediaStatus_type;
/* **** save current media information end **** */
/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/
/* **** External variables Start **** */

/* AE1-L connect guard timer */
extern U32 U32gAE1ConnectGuardTimer;

/* AE1 task and sub-task state definition */
extern e_AE1Task EgAE1Task;

/* Check playback time in cycle loop */
extern U16 U16gDelayInCycle;
/* Re-send command delay if previous STS parameters is invalid */
extern U16 U16gDelayResendCmd;
/* Monitor playback time for switching next file if invalid file exists */
extern U16 U16gMonitorPlayTime;

/* *** messages: host task -> AE1 *** */
extern t_MsgHostToAE1 TMsgHostToAE1;
/* media resume information, need to be saved when resume/power-down */
extern resumeMediaInfo_type resumeMediaInfo;
/* *** messages: AE1 -> display task *** */
extern t_AE1MsgForDisplay AE1MsgForDisplay;
/* **** External variables End **** */

/* **** External function start **** */
/* AE1 task control */
/* Check if resetting */
extern BOOLEAN IsResetting(void);
/* **** External function end **** */
/*****************************************************************************
 Private variables and functions
 *****************************************************************************/

#endif
/* End of File */
