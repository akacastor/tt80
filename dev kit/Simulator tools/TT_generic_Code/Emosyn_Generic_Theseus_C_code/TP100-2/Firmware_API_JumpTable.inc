/*
;********************************************************************************************************
;
;    Name:          Firmware_API_JumpTable.inc
;    Description:   TP100-2_JumpTable.lib header file for Assembly code for the TP100-2
;		    Please include the correct TXX_API_JumpTable.lib and this Include file in your application. 
;		    Emosyn recommends that you call these functions to access the Theseus API's
;    Copyright:	    Emosyn Inc. 2005
;				 
;********************************************************************************************************
; The Example Code hereinbelow is provided "AS IS" and at your sole risk.  
; As to this Code, EMOSYN expressly disclaims all Warranties, including, but not limited to the implied 
; warranties of merchantability and fitness for a particular purpose. EMOSYN does not warrant that the 
; functions contained in this code will meet your requirements, or that the operation of the code will 
; be accurate, error-free, or non-infringing.  No oral or written information or advice given by EMOSYN 
; or an authorized representative shall create or affect any Warranty.
;********************************************************************************************************
*/

$include (../Common_Platinum/Theseus_Platinum_Family.h)

APDU_JUMPTABLE_SIZE	equ	0x03

extrn code (Firmware_SetMMU)
extrn code (Firmware_GetMMUsetting)
extrn code (Firmware_SetMemoryFaultMask)
extrn code (Firmware_SetInterruptVector)
extrn code (Firmware_EraseUCMBlock)
extrn code (Firmware_GetRandomNumber)


extrn code (Firmware_MassEraseUCM)
extrn code (Firmware_EraseEE64Bytes)
extrn code (Firmware_EraseEE8Bytes)
extrn code (Firmware_WriteEE)
extrn code (Firmware_MassEraseEE)
extrn code (Firmware_GetChipID)
extrn code (Firmware_GetClockSourceSelectSFR)
extrn code (Firmware_GetClockControlSFR)
extrn code (Firmware_SetProtectStatus)
extrn code (Firmware_SetSecurityAction)
extrn code (Firmware_SetSecurityMask)
extrn code (Firmware_ErasePageUCM)
extrn code (Firmware_GetInterruptEnable)
extrn code (Firmware_SetInterruptEnable)
extrn code (Firmware_GetFirmwareVersion)
extrn code (Firmware_SetClock)
;extrn code (Firmware_EraseUCMBlock1K)
extrn code (Firmware_WriteUCM)
extrn code (Firmware_WriteByteEE)
extrn code (Firmware_WriteByteUCM)

