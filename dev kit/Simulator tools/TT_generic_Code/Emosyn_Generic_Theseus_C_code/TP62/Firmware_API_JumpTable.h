/******************************************************************************
*
* Name:         Firmware_API_JumpTable.h
* Description:  Header file containing TP62 firmware functions contained in
*               TP62_API_JumpTable.lib
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
* $Revision: 1.4 $
* $Author: chin $ 
* $Date: 2005/10/17 17:48:41 $
******************************************************************************/


/******************************************************************************
* Header file inclusions (#include)
******************************************************************************/
#include "..\Common_Platinum\Theseus_Platinum_Family.h"


/******************************************************************************
* Definitions (#define)
******************************************************************************/
#define XDATA_START_ADDRESS             0x000000
#define EEPROM_START_ADDRESS            0x0800
#define BOOTLOADER_START_ADDRESS        0x6700
#define UCM_START_ADDRESS               0x6800
#define UCM_END_ADDRESS                 0xFC00


/******************************************************************************
* Public Function Prototypes
******************************************************************************/
extern char Firmware_Erase24K_OTP (void);
extern char Firmware_WriteUCM (unsigned int wAddress, unsigned char idata pSource, unsigned char bLength);
extern char Firmware_WriteEE (unsigned int wAddress, unsigned char idata pSource, unsigned char bLength);
extern char Firmware_WriteByteEE (unsigned int wAddress, unsigned char bByteToWrite);
extern char Firmware_WriteByteUCM (unsigned int wAddress, unsigned char bByteToWrite);
extern char Firmware_EraseEE8Bytes (unsigned int wAddress);
extern char Firmware_EraseEE64Bytes(unsigned int wAddress);
extern char Firmware_MassEraseUCM (void);
extern char Firmware_ErasePageUCM (unsigned int wAddress);
extern char Firmware_Erase1KUCM (unsigned int wAddress);
extern char Firmware_MassEraseEE (void);
extern char Firmware_GetFirmwareVersion (void);
extern void Firmware_GetChipID (unsigned char idata *dest_addr);
extern char Firmware_GetClockSourceSelectSFR (void);
extern char Firmware_GetClockControlSFR (void);
extern char Firmware_SetClock (unsigned char Clock_Source, unsigned char Multiplier, unsigned char Divider);
extern char Firmware_GetInterruptEnable (void);
extern void Firmware_SetInterruptEnable (unsigned char IE_Value);
extern char Firmware_SetSecurityAction (unsigned char Value, unsigned char Permanent_flag);
extern char Firmware_SetSecurityMask (unsigned char Mask, unsigned char Permanent_flag);
extern char Firmware_SetProtectStatus (unsigned char Value, unsigned char Permanent_flag);

extern char Firmware_SetExecuteOnlyStatus (unsigned char Value, unsigned char Permanent_flag);
extern char Firmware_SetProtectStatus (unsigned char Value, unsigned char Permanent_flag);
extern char Firmware_EraseConfigBlock (unsigned int wAddress);
extern char Firmware_GetRandomNumber (void);


/******************************************************************************
* Public Variables
******************************************************************************/
