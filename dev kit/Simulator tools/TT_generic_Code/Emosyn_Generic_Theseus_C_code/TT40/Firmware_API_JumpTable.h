/******************************************************************************
*
* Name:         Firmware_API_JumpTable.h
* Description:  Header file containing TT40 firmware functions contained in
*               TT40_API_JumpTable.a51
* Copyright:    SST 2006
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
* $Author: dhunter $ 
* $Date: 2006/10/10 22:40:18 $
******************************************************************************/


/******************************************************************************
* Header file inclusions (#include)
******************************************************************************/
#include "../Common_Titanium/Theseus_Titanium_Family.h"


/******************************************************************************
* Definitions (#define)
******************************************************************************/
#define XDATA_START_ADDRESS             0x00B000
#define SD_BOOTLOADER_START_ADDRESS     0x00A100

/* These define the UCM pages used for backing up */
/* data if buffer writing requires a page update */
/* Addresses chosen reside in the UCM block before bootloader. */
#define PAGE1_BACKUP_START_ADDRESS 0x9A00
#define PAGE2_BACKUP_START_ADDRESS 0x9B00

/* Define EMULATOR to create code compatible with the emulator.
 * This will replace (some) NVFSM and IE usage with equivalent firmware calls.
 * ALSO change TT*_API_JumpTable.a51 to match.
 */
/* #define EMULATOR */

/******************************************************************************
* Public Function Prototypes
******************************************************************************/
extern char Firmware_WriteByteUCM (unsigned int wAddress, unsigned char bByteToWrite);
extern char Firmware_MassEraseUCM (void);

extern char Firmware_ErasePageUCM (unsigned int wAddress);

extern char Firmware_EraseUCM256Bytes (unsigned int wAddress);

extern char Firmware_EraseUCM512Bytes (unsigned int wAddress);

extern char Firmware_GetFirmwareVersion (void);
extern void Firmware_GetChipID (unsigned char idata *dest_addr);
extern void Firmware_GetDiagnosticData (unsigned char idata *dest_addr);
extern char Firmware_GetClockSourceSelectSFR (void);
extern char Firmware_GetClockControlSFR (void);
extern char Firmware_SetClock (unsigned char Clock_Source, unsigned char Multiplier,unsigned char Divider);
extern char Firmware_SetSecurityAction (unsigned char Value, unsigned char Permanent_flag);
extern char Firmware_SetSecurityMask (unsigned char Mask, unsigned char Permanent_flag);
extern char Firmware_SetProtectStatus (unsigned char Value, unsigned char Permanent_flag);
extern char Firmware_SetExecuteOnlyStatus (unsigned char Value, unsigned char Permanent_flag);
extern char Firmware_Set_IO_Pullup (unsigned char Value, unsigned char Permanent_flag);
extern char Firmware_API_WriteByteUCM (unsigned int wAddress, unsigned char bByteToWrite);
extern char Firmware_API_MassEraseUCM (void);
extern char Firmware_API_ErasePageUCM (unsigned int wAddress);
extern void Firmware_SetInterruptEnable (unsigned char IE_Value);
extern char Firmware_GetInterruptEnable (void);

/* Software simulated API's */
extern char Firmware_WriteUCM (unsigned int wAddress, unsigned char idata pSource,unsigned char bLength);

extern char Firmware_EraseUCMBlock (unsigned int wAddress);
