/******************************************************************************
*
* Name:         Firmware_API_JumpTable.h
* Description:  Header file containing TT80 firmware functions contained in
*               TT80_API_JumpTable.lib
*               Please include the correct TXX_API_JumpTable.lib and this
*               Include file in your application. 
*               Emosyn recommends that you call these functions to access the
*               Theseus API's
* Copyright:    Emosyn Inc. 2005
*
* The Example Code herein below is provided "AS IS" and at your sole risk.  
* As to this Code, EMOSYN expressly disclaims all warranties, including, but
* not limited to the implied warranties of merchantability and fitness for a
* particular purpose. EMOSYN does not warrant that the functions contained in
* this code will meet your requirements, or that the operation of the code will
* be accurate, error-free, or non-infringing. No oral or written information or
* advice given by EMOSYN or an authorized representative shall create or affect
* any Warranty.
*******************************************************************************
* $Revision: 1.1 $
* $Author: xavier $ 
* $Date: 2006/07/12 02:40:31 $
******************************************************************************/


/******************************************************************************
* Header file inclusions (#include)
******************************************************************************/
#include "/Theseus_Titanium_Family.h"


/******************************************************************************
* Definitions (#define)
******************************************************************************/
#define XDATA_START_ADDRESS             0x000400
#define SD_BOOTLOADER_START_ADDRESS     0x00FC00


/******************************************************************************
* Public Function Prototypes
******************************************************************************/
extern char Firmware_WriteByteUCM_In_CODE_Space (unsigned char xdata * wAddress, unsigned char bByteToWrite);
extern char Firmware_WriteByteUCM (unsigned char xdata * wAddress, unsigned char bByteToWrite);
extern char Firmware_MassEraseUCM (void);

extern char Firmware_ErasePageUCM_In_CODE_Space (unsigned char xdata * wAddress);
extern char Firmware_ErasePageUCM (unsigned char xdata * wAddress);

extern char Firmware_Erase256Bytes (unsigned char xdata * wAddress);

extern char Firmware_EraseUCM512Bytes_In_CODE_Space (unsigned char xdata * wAddress);
extern char Firmware_EraseUCM512Bytes (unsigned char xdata * wAddress);

extern char Firmware_GetFirmwareVersion (void);
extern void Firmware_GetChipID (unsigned char idata *dest_addr);
extern void Firmware_GetDiagnosticData (unsigned char idata *dest_addr);
extern char Firmware_GetClockSourceSelectSFR (void);
extern char Firmware_GetClockControlSFR (void);
extern char Firmware_SetClock (unsigned char Clock_Source, unsigned char Multiplier,unsigned char Divider);
extern char Firmware_GetInterruptEnable (void);
extern void Firmware_SetInterruptEnable (unsigned char IE_Value);
extern char Firmware_SetSecurityAction (unsigned char Value, unsigned char Permanent_flag);
extern char Firmware_SetSecurityMask (unsigned char Mask, unsigned char Permanent_flag);
extern char Firmware_SetProtectStatus (unsigned char Value, unsigned char Permanent_flag);
extern char Firmware_SetExecuteOnlyStatus (unsigned char Value, unsigned char Permanent_flag);
extern char Firmware_GetRandomNumber (void);

/* Software simulated API's */
extern char Firmware_WriteUCM_In_CODE_Space (unsigned char xdata * wAddress, unsigned char idata pSource,unsigned char bLength);
extern char Firmware_WriteUCM (unsigned char xdata * wAddress, unsigned char idata pSource,unsigned char bLength);

extern char Firmware_EraseUCMBlock (unsigned char xdata * wAddress);
