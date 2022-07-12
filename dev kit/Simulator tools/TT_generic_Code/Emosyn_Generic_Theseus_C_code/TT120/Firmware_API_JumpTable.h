/******************************************************************************
*
* Name:         Firmware_API_JumpTable.h
* Description:  Header file containing TT120 firmware functions contained in
*               TT120_API_JumpTable.a51
* Copyright:    Emosyn Inc. 2006
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
* $Author: chin $ 
* $Date: 2006/03/08 18:50:14 $
******************************************************************************/


/******************************************************************************
* Header file inclusions (#include)
******************************************************************************/
#include "../Common_Titanium/Theseus_Titanium_Family.h"


/******************************************************************************
* Definitions (#define)
******************************************************************************/
#define XDATA_START_ADDRESS             0x01E800
#define SD_BOOTLOADER_START_ADDRESS     0x01DE00

/* These define the UCM pages used for backing up */
/* data if buffer writing requires a page update */
#define PAGE1_BACKUP_START_ADDRESS 0xF000
#define PAGE2_BACKUP_START_ADDRESS 0xF100

/******************************************************************************
* Public Function Prototypes
******************************************************************************/
extern char Firmware_WriteByteUCM (unsigned char far *pDest, unsigned char ucByte_To_Write);
extern char Firmware_MassEraseUCM (void);

extern char Firmware_ErasePageUCM (unsigned char far *pDest);
extern char Firmware_EraseUCM256Bytes (unsigned char far *pDest);
extern char Firmware_EraseUCM512Bytes (unsigned char far *pDest);

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
extern char Firmware_Set_IO_Pullup (unsigned char Value, unsigned char Permanent_flag);

/* Software simulated API's */
extern char Firmware_WriteUCM (unsigned char idata pSource, unsigned char bLength, unsigned char far *pDest);

extern char Firmware_EraseUCMBlock (unsigned int wAddress);
