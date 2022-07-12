/*
;********************************************************************************************************
;
; Name:          Firmware_API_JumpTable.inc
; Description:   Include file for the TP40 firmware functions contained in TP62_API_JumpTable.lib
;                Please include the correct TXX_API_JumpTable.lib and this Include file in your application. 
;                Emosyn recommends that you call these functions to access the Theseus API's
; Copyright:     Emosyn Inc. 2005
;				 
;********************************************************************************************************
; The Example Code hereinbelow is provided "AS IS" and at your sole risk.  
; As to this Code, EMOSYN expressly disclaims all Warranties, including, but not limited to the implied 
; warranties of merchantability and fitness for a particular purpose. EMOSYN does not warrant that the 
; functions contained in this code will meet your requirements, or that the operation of the code will 
; be accurate, error-free, or non-infringing.  No oral or written information or advice given by EMOSYN 
; or an authorized representative shall create or affect any Warranty.
;********************************************************************************************************
; $Revision: 1.1 $
; $Author: chin $ 
; $Date: 2005/08/09 11:53:42 $
;********************************************************************************************************
*/
$include (../Common_Platinum/Theseus_Platinum_Family.h)

APDU_JUMPTABLE_SIZE		equ	0x03
XDATA_START_ADDRESS		equ	0x000000
SD_BOOTLOADER_START_ADDRESS	equ	0x5D00

extrn code (Firmware_WriteByteEE)
extrn code (Firmware_WriteByteUCM)
extrn code (Firmware_WriteUCM)
extrn code (Firmware_MassEraseUCM)
extrn code (Firmware_EraseEE8Bytes)
extrn code (Firmware_EraseEE64Bytes)
extrn code (Firmware_WriteEE)
extrn code (Firmware_MassEraseEE)
extrn code (Firmware_GetChipID)
extrn code (Firmware_GetClockSourceSelectSFR)
extrn code (Firmware_SetClock)
extrn code (Firmware_GetInterruptEnable)
extrn code (Firmware_SetInterruptEnable)
extrn code (Firmware_GetFirmwareVersion)
extrn code (Firmware_SetSecurityAction)
extrn code (Firmware_SetSecurityMask)
extrn code (Firmware_GetClockControlSFR)
extrn code (Firmware_SetProtectStatus)
extrn code (Firmware_ErasePageUCM)
extrn code (Firmware_Erase24K_OTP)
extrn code (Firmware_EraseOTPBlock)
extrn code (Firmware_SetExecuteOnlyStatus)
extrn code (Firmware_EraseConfigBlock)
extrn code (Firmware_GetRandomNumber)

