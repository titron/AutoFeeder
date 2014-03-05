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
 * System Name  : Program of AE1-L Demo.
 * File Name    : app_ae1_protocol.h
 * Abstract     : application layer header file for AE1-L.
 * Version      : 0.01
 * Device       : R8C/2A group, or R8C/2B group, or 78K0 group
 * Tool-Chain   : High-performance Embedded Workshop (Version 4.08.00.011)
 *              : Renesas M16C Standard Toolchain (V5.45.01)
 * OS           : none
 * H/W Platform : AE1-L demo board
 * Description  : This is the header file of application layer (AE1-L).
 *              : AE1 protocol parameters definition.
 * Operation    : none
 * Limitation   : This file can be only used as sample code for AE1-L.
 *****************************************************************************
 * History      : Dec.15,2010 Ver. 0.01 First Release
 *****************************************************************************/
#ifndef __APP_AE1_PROTOCOL_H__
#define __APP_AE1_PROTOCOL_H__
/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
/* define firmware version
 * when v.0.80 coming, use this definition */
#define FIRM_VER_080_USED
/* **** Command & Status ID definition **** */
#define STS_NO_RESPONSE       		  (U8)0xEF/* status: Command response */

#define CMD_USB_SD_CONNECTION         (U8)0x00/* command: USB/SD Connection */
#define STS_USB_SD_CONNECTION         (U8)0x80/* status: USB/SD Connection */

#define CMD_COMMAND_CANCEL            (U8)0x02/* command: Command Cancel */
#define STS_COMMAND_CANCEL            (U8)0x82/* status: Command Cancel */

#define CMD_CONNECTION_STATUS         (U8)0x03/* command: Connection Status */
#define STS_CONNECTION_STATUS         (U8)0x83/* status: Connection Status */

#define CMD_PLAYBACK_PAUSE            (U8)0x10/* command: Playback/Pause */
#define STS_PLAYBACK_PAUSE            (U8)0x90/* status: Playback/Pause */

#define CMD_STOP                      (U8)0x11/* command:Stop */
#define STS_STOP                      (U8)0x91/* status:Stop */

#define CMD_FF_FR                     (U8)0x12/* command: Fast Forward/Fast Rewind */
#define STS_FF_FR                     (U8)0x92/* status: Fast Forward/Fast Rewind */

#define CMD_RESUME_SETUP              (U8)0x13/* command: Resume setup */
#define STS_RESUME_SETUP              (U8)0x93/* status: Resume setup */

#define STS_ISOCHRONOUS_ERROR         (U8)0x9A/* status: Isochronous error report */

#define CMD_IAP_COMMUNICATION         (U8)0x1F/* command: iAP communication */
#define STS_IAP_COMMUNICATION         (U8)0x9F/* status: iAP communication */

#define CMD_SPECIAL_PLAYBACK          (U8)0x20/* command: Special playback */
#define STS_SPECIAL_PLAYBACK          (U8)0xA0/* status: Special playback */

#define CMD_FOLDER_UP_DOWN            (U8)0x21/* command: Folder Up/Down */
#define STS_FOLDER_UP_DOWN            (U8)0xA1/* status: Folder Up/Down */

#define CMD_FILE_UP_DOWN              (U8)0x22/* command: File Up/Down */
#define STS_FILE_UP_DOWN              (U8)0xA2/* status: File Up/Down */

#define CMD_FOLDER_STRUCT             (U8)0x24/* command: Folder structure */
#define STS_FOLDER_STRUCT             (U8)0xA4/* status: Folder structure */

#define CMD_SUBFOLDER_LIST            (U8)0x25/* command: Subfolder list */
#define STS_SUBFOLDER_LIST            (U8)0xA5/* status: Subfolder list */

#define CMD_NAME_INFO                 (U8)0x30/* command: Name information */
#define STS_NAME_INFO                 (U8)0xB0/* status: Name information */

#define CMD_TAG_INFO                  (U8)0x31/* command: Tag information */
#define STS_TAG_INFO                  (U8)0xB1/* status: Tag information */

#define CMD_HEADER_INFO               (U8)0x32/* command: Header information */
#define STS_HEADER_INFO               (U8)0xB2/* status: Header information */

#define CMD_TIME_INFO                 (U8)0x33/* command: Time information */
#define STS_TIME_INFO                 (U8)0xB3/* status: Time information */

#define CMD_MEDIA_INFO_ACQ            (U8)0x34/* command: Media information acquisition */
#define STS_MEDIA_INFO_ACQ            (U8)0xB4/* status: Media information acquisition */

#define COM_PLAY_INFO				  (U8)0x37/* command: Play information */
#define STS_PLAY_INFO				  (U8)0xB7/* status: Play information */

#define CMD_OUTPUT_ADJUST             (U8)0x40/* command: Output adjustment */
#define STS_OUTPUT_ADJUST             (U8)0xC0/* status: Output adjustment */

#define CMD_DECODER_SELECT            (U8)0x41/* command: Decoder selection */
#define STS_DECODER_SELECT            (U8)0xC1/* status: Decoder selection */

#define CMD_DEFAULT_SETTING           (U8)0x50/* command: Default setting */
#define STS_DEFAULT_SETTING           (U8)0xD0/* status: Default setting */

#define CMD_LUN_SPEC                  (U8)0x51/* command: LUN specification */
#define STS_LUN_SPEC                  (U8)0xD1/* status: LUN specification */

#define CMD_CHANNEL_SELECT            (U8)0x52/* command: Channel selection */
#define STS_CHANNEL_SELECT            (U8)0xD2/* status: Channel selection */

#define CMD_OPTION_SETTING            (U8)0x53/* command: Option setting */
#define STS_OPTION_SETTING            (U8)0xD3/* status: Option setting */

#define CMD_PORT_SETUP                (U8)0x54/* command: Port setup */
#define STS_PORT_SETUP                (U8)0xD4/* status: Port setup */

#define CMD_COM_SETUP                 (U8)0x5E/* command: Communication setup */
#define STS_COM_SETUP                 (U8)0xDE/* status: Communication setup */

#define CMD_SETTING_CHECK             (U8)0x61/* command: Setting details check */
#define STS_SETTING_CHECK             (U8)0xE1/* status: Setting details check */

#define CMD_ROM_VERSION               (U8)0x62/* command: ROM version */
#define STS_ROM_VERSION               (U8)0xE2/* status: ROM version */

#define CMD_FLASH_UPDATE              (U8)0x71/* command: Flash update */
#define STS_FLASH_UPDATE              (U8)0xF1/* status: Flash update */

/* **** command & status parameters definition **** */
/* ====command parameters definition==== */
/* ID = 00H */
#ifdef FIRM_VER_080_USED
#define START_DETECT_CONNECTION       (U8)0x01/* CDB[7] */
#define POLL_USB                      (U8)0x02/* CDB[7] */
#define POLL_SD                       (U8)0x12/* CDB[7] */
#else
#define USB_CONNECTION_START          (U8)0x01/* CDB[7] */
#define SD_CONNECTION_START           (U8)0x11/* CDB[7] */
#endif
/* ID = 10H */
#define COMMON_PLAY                   (U8)0x00/* CDB[7] */
#define PAUSE_RELEASED                (U8)0x01/* CDB[7] */
#define PLAY_FROM_NEXT_START          (U8)0x02/* CDB[7] */
#define PLAY_FROM_PREVIOUS_START      (U8)0x03/* CDB[7] */
#define PLAY_FROM_CURRENT_START       (U8)0x04/* CDB[7] */
#define PAUSE_STOP                    (U8)0x05/* CDB[7] */
#define RESUME_OR_DIRECT_FILE_PLAY    (U8)0x06/* CDB[7] */
#define PLAY_FROM_NEXT_FOLDER_START   (U8)0x07/* CDB[7] */
#define PLAY_FROM_PREVIOUS_FOLDER_START   (U8)0x08/* CDB[7] */
#define PLAY_DIRECT_FOLDER            (U8)0x09/* CDB[7] */
/* ID = 12H */
#define FAST_FORWARD                  (U8)0x00/* CDB[7] */
#define FAST_REWIND                   (U8)0x01/* CDB[7] */
#define CANCEL_FF_FR                  (U8)0x02/* CDB[7] */
#define SPEED_X4                      (U8)0x00/* CDB[8] */
#define SPEED_X2                      (U8)0x01/* CDB[8] */
#define SPEED_X3                      (U8)0x02/* CDB[8] */
#define SPEED_X6                      (U8)0x03/* CDB[8] */
#define SPEED_X10                     (U8)0x04/* CDB[8] */
#define SPEED_X20                     (U8)0x05/* CDB[8] */
#define SPEED_X30                     (U8)0x06/* CDB[8] */
/* ID = 20H */
#define MODE_ALL_FILES_NORMAL              		(U8)0x00/* CDB[7] */
#define MODE_ALL_FILES_SCAN                		(U8)0x01/* CDB[7] */
#define MODE_ALL_FILES_RANDOM              		(U8)0x02/* CDB[7] */
#define MODE_ALL_FILES_RANDOM_SCAN         		(U8)0x03/* CDB[7] */
#define MODE_ALL_FILES_REPEAT              		(U8)0x04/* CDB[7] */
#define MODE_ALL_FILES_REPEAT_SCAN         		(U8)0x05/* CDB[7] */
#define MODE_ALL_FILES_RANDOM_REPEAT       		(U8)0x06/* CDB[7] */
#define MODE_ALL_FILES_RANDOM_REPEAT_SCAN  		(U8)0x07/* CDB[7] */
#define MODE_FOLDER_NORMAL                 		(U8)0x10/* CDB[7] */
#define MODE_FOLDER_SCAN                   		(U8)0x11/* CDB[7] */
#define MODE_FOLDER_RANDOM                 		(U8)0x12/* CDB[7] */
#define MODE_FOLDER_RANDOM_SCAN            		(U8)0x13/* CDB[7] */
#define MODE_FOLDER_REPEAT                 		(U8)0x14/* CDB[7] */
#define MODE_FOLDER_REPEAT_SCAN            		(U8)0x15/* CDB[7] */
#define MODE_FOLDER_RANDOM_REPEAT          		(U8)0x16/* CDB[7] */
#define MODE_FOLDER_RANDOM_REPEAT_SCAN     		(U8)0x17/* CDB[7] */
#define MODE_ONE_FILE_NORMAL               		(U8)0x20/* CDB[7] */
#define MODE_ONE_FILE_REPEAT               		(U8)0x24/* CDB[7] */
#define MODE_ALL_FOLDER_1ST_FILE_SCAN      		(U8)0x31/* CDB[7] */
#define MODE_ALL_FOLDER_1ST_FILE_REPEAT_SCAN    (U8)0x35/* CDB[7] */
/* ID = 24H */
#define CURRENT_FOLDER                          (U8)0x00/* CDB[7] */
#define SPECIFIED_FOLDER_NUM                    (U8)0x01/* CDB[7] */
/* ID = 30H */
#define TARGET_FILE                   			(U8)0x00/* CDB[7] */
#define TARGET_FOLDER                 			(U8)0x01/* CDB[7] */
#define TARGET_PLAYLIST               			(U8)0x02/* CDB[7] */
#define NAME_TYPE_CURRENT             			(U8)0x00/* CDB[8] */
#define NAME_TYPE_SPECIFIED           			(U8)0x01/* CDB[8] */
/* ID = 31H */
#define TARGET_TITLE                  			(U8)0x00/* CDB[7] */
#define TARGET_ARTIST_NAME            			(U8)0x01/* CDB[7] */
#define TARGET_ALBUM_NAME             			(U8)0x02/* CDB[7] */
#define TARGET_COMPOSER               			(U8)0x03/* CDB[7] */
#define TARGET_COMMENTS               			(U8)0x10/* CDB[7] */
#define TARGET_TRACK_NUM              			(U8)0x11/* CDB[7] */
#define TARGET_GENRE                  			(U8)0x12/* CDB[7] */
#define TARGET_YEAR                   			(U8)0x13/* CDB[7] */
#define TARGET_CURRENT                 			(U8)0x00/* CDB[8] */
#define TARGET_SPECIFIED_NUM           			(U8)0x01/* CDB[8] */
/* ID = 33H */
#define TARGET_PLAYBACK_TIME          			(U8)0x00/* CDB[7] */
#define TARGET_TOTAL_TIME             			(U8)0x01/* CDB[7] */
/* ID = 34H */
#ifdef FIRM_VER_080_USED
#define HUB_PORT_1                              (U8)0x10
#define HUB_PORT_2                              (U8)0x20
#define HUB_PORT_3                              (U8)0x30
#define HUB_PORT_4                              (U8)0x40
#define HUB_PORT_5                              (U8)0x50
#define HUB_PORT_6                              (U8)0x60
#define HUB_PORT_7                              (U8)0x70
#define TARGET_USB_VENDOR_INFO         			(U8)0x00/* CDB[7] */
#define TARGET_USB_PRODUCT_INFO       			(U8)0x01/* CDB[7] */
#define TARGET_USB_SERIAL_NUM         			(U8)0x02/* CDB[7] */
#define TARGET_USB_HUB_VENDOR_INFO(A)           (A+(U8)0x00)/* CDB[7] */
#define TARGET_USB_HUB_PRODUCT_INFO(A)          (A+(U8)0x11)/* CDB[7] */
#define TARGET_USB_HUB_SERIAL_NUM(A)            (A+(U8)0x12)/* CDB[7] */
#define TARGET_SD_VENDOR_INFO          			(U8)0x80/* CDB[7] */
#define TARGET_SD_PRODUCT_INFO        			(U8)0x81/* CDB[7] */
#define TARGET_SD_SERIAL_NUM          			(U8)0x82/* CDB[7] */
#else
#define TARGET_USB_VENDOR_INFO         			(U8)0x00/* CDB[7] */
#define TARGET_USB_PRODUCT_INFO       			(U8)0x01/* CDB[7] */
#define TARGET_USB_SERIAL_NUM         			(U8)0x02/* CDB[7] */
#define TARGET_SD_VENDOR_INFO          			(U8)0x10/* CDB[7] */
#define TARGET_SD_PRODUCT_INFO        			(U8)0x11/* CDB[7] */
#define TARGET_SD_SERIAL_NUM          			(U8)0x12/* CDB[7] */
#endif
/* ID = 40H */
#define MAX_ATTENUATION_VALUE         			(U16)0x8000/* CDB[8&9] */
/* ID = 50H */
#ifdef FIRM_VER_080_USED
#define ID50_CDB31_TIME_SPON_STS_DISABLE     	(U8)0x00/* CDB[31] */
#define ID50_CDB31_TIME_SPON_STS_ENABLE      	(U8)0x01/* CDB[31] */
#else
#define ID50_CDB30_TIME_SPON_STS_DISABLE     	(U8)0x00/* CDB[30] */
#define ID50_CDB30_TIME_SPON_STS_ENABLE      	(U8)0x01/* CDB[30] */
#endif
/* ID = 5EH */
#define MASS_STORAGE_USB              			(U8)0x00/* CDB[7] */
#define ISOCHRONOUS_IPOD              			(U8)0x01/* CDB[7] */
#define MASS_STORAGE_SD               			(U8)0x03/* CDB[7] */
#define IPOD_VERIFY                   			(U8)0x04/* CDB[7] */

/* ====response result from AE1 definition==== */
/* ID = 80H */
#define FILE_SIZE_LENGTH              			(U8)8/* File size length in byte */
#define ID80CDB7_USB_CMD_POLLING_ANSWER        	(U8)0x00/* CDB[7] */
#define ID80CDB7_USB_SPON_STS         			(U8)0x01/* CDB[7] */
#define ID80CDB7_SD_CMD_POLLING_ANSWER         	(U8)0x10/* CDB[7] */
#define ID80CDB7_SD_SPON_STS          			(U8)0x11/* CDB[7] */
#define ID80CDB7_CASE_CMD_NOT_EXED    			(U8)0xFF/* CDB[7] */
#define CON_STS_NO_CONNECTED          			(U8)0x00/* CDB[8] */
#define CON_STS_CONNECTED             			(U8)0x01/* CDB[8] */
#define CON_STS_BEING_CONNECTED       			(U8)0x02/* CDB[8] */
#define CON_STS_WAITING_COM_SETUP     			(U8)0x03/* CDB[8] */
#define CON_STS_WAITING_HUB_SPECIFIED 			(U8)0x04/* CDB[8] */
#define FILE_STS_NOT_STARTED          			(U8)0x00/* CDB[9] */
#define FILE_STS_ANALYSIS_COMPLETED   			(U8)0x01/* CDB[9] */
#define FILE_STS_ANALYSIS_IN_PROGRESS 			(U8)0x02/* CDB[9] */
/* ID = 83H */
#define ID83_ANSWER_CMD               			(U8)0x00/* CDB[7] */
#define ID83_CASE_STS_ISSUED_SPON     			(U8)0x01/* CDB[7] */
#define ID83_CMD_NOT_EXED             			(U8)0xFF/* CDB[7] */
#define OVERCURRENT_STS_NOT_DETECTED  			(U8)0x00/* CDB[8] */
#define OVERCURRENT_STS_DETECTED      			(U8)0x01/* CDB[8] */
#define USB_DISCONNECTION_DETECTED    			(U8)0x00/* CDB[9] */
#define USB_CONNECTION_DETECTED       			(U8)0x01/* CDB[9] */
#define USB_DISCON_DETECTED_STS_CHANGED    		(U8)0x02/* CDB[9] */
#define USB_CON_DETECTED_STS_CHANGED       		(U8)0x03/* CDB[9] */
#define SD_DISCONNECTION_DETECTED    			(U8)0x00/* CDB[9] */
#define SD_CONNECTION_DETECTED       			(U8)0x01/* CDB[9] */
#define SD_DISCON_DETECTED_STS_CHANGED    		(U8)0x02/* CDB[9] */
#define SD_CON_DETECTED_STS_CHANGED       		(U8)0x03/* CDB[9] */
/* ID = 90H */
#define ID90_CASE_CMD_RECEIVED        			(U8)0x00/* CDB[7] */
#define ID90_CASE_STS_ISSUED_SPON     			(U8)0x01/* CDB[7] */
#define ID90_CASE_CMD_NOT_EXED        			(U8)0xFF/* CDB[7] */
#define PLAY_STS_PLAYBACK_STARTED     			(U8)0x01/* CDB[8] */
#define PLAY_STS_PLAYBACK_PAUSED      			(U8)0x02/* CDB[8] */
#define PLAY_STS_PLAYBACK_OVER        			(U8)0x20/* CDB[8] */
#define PLAY_STS_FILENUM_ZERO         			(U8)0x80/* CDB[8] */
/* ID = A4H */
#define IDA4_STS_INFO_ACQUIRED		  			(U8)0x01/* CDB[7] */
/* ID = B0H */
#define IDB0_STS_NAME_ACQUIRED        			(U8)0x01/* CDB[7] */
#define IDB0_UNKOWN_CODE              			(U8)0x00/* CDB[8]*/
#define IDB0_UTF16_LE                 			(U8)0x01/* CDB[8]*/
#define IDB0_UTF8                    			(U8)0x03/* CDB[8]*/
/* ID = B1H */
#define IDB1_STS_INFO_ACQUIRED        			(U8)0x01/* CDB[7] */
#define IDB1_NO_TAG_INFO              			(U8)0x80/* CDB[7] */
#define IDB1_DECODE_NOT_COMPLETE      			(U8)0xC0/* CDB[7] */
#define IDB1_TAG_ERROR                			(U8)0xC1/* CDB[7] */
#define IDB1_SET_FAILURE              			(U8)0xFF/* CDB[7] */
#define IDB1_VER_RESERVED             			(U8)0x00/* CDB[8] */
#define IDB1_VER_ID3V22               			(U8)0x02/* CDB[8] */
#define IDB1_VER_ID3V23               			(U8)0x03/* CDB[8] */
#define IDB1_VER_ID3V24              			(U8)0x04/* CDB[8] */
#define IDB1_VER_ID3V10               			(U8)0x10/* CDB[8] */
#define IDB1_VER_ID3V11               			(U8)0x11/* CDB[8] */
#define IDB1_VER_WMA                  			(U8)0x20/* CDB[8] */
#define IDB1_VER_MP4                  			(U8)0x30/* CDB[8] */
#define IDB1_VER_WAV                  			(U8)0x40/* CDB[8] */
#define IDB1_TARGET_TITLE             			(U8)0x00/* CDB[9] */
#define IDB1_TARGET_ARTIST            			(U8)0x01/* CDB[9] */
#define IDB1_TARGET_ALBUM             			(U8)0x02/* CDB[9] */
#define IDB1_TARGET_COMPOSER          			(U8)0x03/* CDB[9] */
#define IDB1_TARGET_COMMENTS          			(U8)0x10/* CDB[9] */
#define IDB1_TARGET_TRACKNUM          			(U8)0x11/* CDB[9] */
#define IDB1_TARGET_GENRE             			(U8)0x12/* CDB[9] */
#define IDB1_TARGET_YEAR              			(U8)0x13/* CDB[9] */
#define IDB1_CHAR_CODE_UNKOWN         			(U8)0x00/* CDB[10] */
#define IDB1_CHAR_CODE_UTF16_LE       			(U8)0x01/* CDB[10] */
#define IDB1_CHAR_CODE_UTF16_BE       			(U8)0x02/* CDB[10] */
#define IDB1_CHAR_CODE_UTF8              		(U8)0x03/* CDB[10] */
#define IDB1_CHAR_CODE_UTF16_WITH_BOM    		(U8)0x04/* CDB[10] */
#define IDB1_CHAR_CODE_ISO8859        			(U8)0x05/* CDB[10] */
#define IDB1_CHAR_CODE_EXCEPTION      			(U8)0x06/* CDB[10] */
/* ID = B3H */
#define IDB3CDB7_GOTTEN_DISABLED      			(U8)0xFF/* CDB[7] */
#define IDB3_TIME_GOTTEN              			(U8)0x00/* CDB[8] */
#define IDB3_TOTAL_TIME_GOTTEN        			(U8)0x01/* CDB[8] */
#define IDB3_TIME_BEING_PREPARED      			(U8)0x80/* CDB[8] */
/* ID = B4H */
#define IDB4_STS_INFO_ACQUIRED        			(U8)0x01/* CDB[7] */
/* ID = C1H */
#define IDC1_STS_SETUP_COMPLETED      			(U8)0x01/* CDB[7] */
/* ID = D0H */
#define IDD0_CDB7_SET_COMPLETED       			(U8)0x01/* CDB[7] */
/* ID = DEH */
#define IDDE_CDB7_SETUP_RESERVED      			(U8)0x00/* CDB[7] */
#define IDDE_CDB7_SETUP_COMPLETED     			(U8)0x01/* CDB[7] */
#define IDDE_CDB7_SETUP_FAILURE       			(U8)0x80/* CDB[7] */
#define IDDE_CDB7_CMD_NOT_EXED        			(U8)0xFF/* CDB[7] */

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/
/* *** command & status data type definition start *** */
/* USB/SD connection(ID:00H, 80H) */
typedef struct{
	U8 startUpSts;/* CDB[7] */
	U8 fileSysStorageOrder;/* CDB[8] */
}cmdUsbSdConnection_type;

typedef struct{
	U8 statusType;/* CDB[7] */
	U8 connectStatus;/* CDB[8] */
	U8 fileSysStatus;/* CDB[9] */
	U16 folderTotalNum;/* CDB[10~11] */
	U16 fileTotalNum;/* CDB[12~13] */
	U32 volumeID;/* CDB[14~17] */
	U8 fileSize[FILE_SIZE_LENGTH];/* CDB[18~25]  */
	U8 port_lun_num;/* CDB[26] */
}stsUsbSdConnection_type;

/* Connection status(ID:03H, 83H) */
typedef struct{
	U8 overCurrent;/* CDB[8] */
	U8 usbConnectInfo;/* CDB[9] */
	U8 connectPortNum;/* CDB[10] */
	U8 usbConnectPort;/* CDB[11] */
	U8 sdConnectInfo;/* CDB[12] */
	U8 maxLunNum;/* CDB[13] */
	U16 connectLunNum;/* CDB[14~15] */
}stsConnectStatus_type;

/* Playback/Pause(ID:10H, 90H) */
typedef struct{
	U16 specifiedFileOrFolderNum;/* CDB[8~9] */
	U16 specifiedPlaybackPos_Hour;/* CDB[10~11] */
	U8 specifiedPlaybackPos_Minute;/* CDB[12] */
	U8 specifiedPlaybackPos_Second;/* CDB[13] */
	U8 resumInfo[5];/* CDB[14~18] */
}cmdPlayback_Pause_type;

typedef struct{
	U8 playStatus;/* CDB[8] */
	U8 musicType;/* CDB[9] */
	U16 subjectFolderNum;/* CDB[10~11] */
	U16 fileNum;/* CDB[12~13] */
}stsPlayback_Pause_type;

/* Folder information(ID:24H, A4H) */
typedef struct{
	U8 standard;/* CDB[7] */
	U16 specifiedFolderNum;/* CDB[8~9] */
}cmdGetFolderInfo_type;

typedef struct{
	U16 currentFolderNum;/* CDB[8~9] */
	U16 fatherFolderNum;/* CDB[10~11] */
	U16 childFolderNum;/* CDB[12~13] */
	U16 oldBrotherFolderNum;/* CDB[14~15] */
	U16 youngBrotherFolderNum;/* CDB[16~17] */
	U16 includeFolderNum;/* CDB[18~19] */
	U16 includeFileNum;/* CDB[20~21] */
	U16 firstFileNum;/* CDB[22~23] */
	U16 relativeFolderNum;/* CDB[24~25] */
}stsGetFolderInfo_type;

/* Name information(ID:30H, B0H) */
typedef struct{
	U8 target;/* CDB[7] */
	U8 standard;/* CDB[8] */
	U16 specifiedNum;/* CDB[9~10] */
}cmdGetNameInfo_type;

typedef struct{
	U8 wordCode;/* CDM[8] */
	U16 fatherFolderNum;/* CDB[9~10] */
	U16 fileOrFolderNum;/* CDB[11~12] */
	U8 length;/* CDB[13] */
	U8 name[64];/* CDB[14~77] */
}stsGetNameInfo_type;

/* Tag information(ID:31H, B1H) */
typedef struct{
	U8 tagType;/* CDB[7] */
	U8 target;/* CDB[8] */
	U16 fileNum;/* CDB[9~10] */
}cmdGetTagInfo_type;

typedef struct{
	U8 version;/* CDB[8] */
	U8 target;/* CDB[9] */
	U8 wordCode;/* CDB[10] */
	U8 length;/* CDB[11] */
	U8 name[128];/* CDB[12~139] */
}stsGetTagInfo_type;

/* Time information(ID:33H, B3H) */
typedef struct{
	U8 statusType;/* CDB[7] */
	U8 getResult;/* CDB[8] */
	U8 playStatus;/* CDB[9] */
	U16 hour;/* CDB[10~11] */
	U8 minute;/* CDB[12] */
	U8 second;/* CDB[13] */
	U8 resumeInfo[5];/* CDB[14~18] */
}stsTimeInfo_type;

/* Media information(ID:34H, B4H) */
typedef struct{
	U8 target;/* CDM[8] */
	U16 id;/* CDB[9~10] */
	U8 length;/* CDB[11] */
	U8 name[64];/* CDB[12~75] */
}stsMediaInfo_type;

/* Communication Setup information(ID:5EH, DEH) */
typedef struct{
	U8 setupStatus;/* CDM[7] */
}stsComSetupInfo_type;

/* ROM version information(ID:62H, E2H) */
typedef struct{
	U8 LSIName[12];/* CDB[7~18] */
	U8 version[4];/* CDB[19~22] */
	U8 year[2];/* CDB[23~24] */
	U8 month;/* CDB[25] */
	U8 date;/* CDB[26] */
}stsROMInfo_type;

/* *** command & status data type definition end *** */

/*****************************************************************************
 Imported global variables and functions (from other files)
 *****************************************************************************/

/*****************************************************************************
 Exported global variables and functions (to be accessed by other files)
 *****************************************************************************/

/*****************************************************************************
 Private variables and functions
 *****************************************************************************/

#endif
/* End of File */

