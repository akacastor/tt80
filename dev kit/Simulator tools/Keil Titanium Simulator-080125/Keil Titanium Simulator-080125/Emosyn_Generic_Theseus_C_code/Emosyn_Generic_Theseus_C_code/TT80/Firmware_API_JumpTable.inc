/*
;********************************************************************************************************
;
;    Name:          Firmware_API_JumpTable.inc
;    Description:   TT80_API_JumpTable.lib header file for Assembly code
;		    Please include the correct TXX_API_JumpTable.lib and this Include file in your application. 
;		    Emosyn recommends that you call these functions to access the Theseus Firmware API's
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
; $Revision: 1.2 $
; $Author: dhunter $ 
; $Date: 2006/10/11 23:05:14 $
;********************************************************************************************************
*/
$include (../Common_Titanium/Theseus_Titanium_Family.h)

APDU_JUMPTABLE_SIZE	equ	0x03
XRAM_START_ADDRESS	equ	0x0400

; Firmware API's / FSM Interface
extrn code (Firmware_WriteByteUCM)
extrn code (Firmware_MassEraseUCM)
extrn code (Firmware_GetChipID)
extrn code (Firmware_GetClockSourceSelectSFR)
extrn code (Firmware_SetClock)
extrn code (Firmware_GetFirmwareVersion)
extrn code (Firmware_SetSecurityAction)
extrn code (Firmware_SetSecurityMask)
extrn code (Firmware_GetClockControlSFR)
extrn code (Firmware_SetProtectStatus)
extrn code (Firmware_EraseUCM256Bytes)
extrn code (Firmware_EraseUCM512Bytes)
extrn code (Firmware_SetExecuteOnlyStatus)
extrn code (Firmware_EraseUCMBlock)
extrn code (Firmware_ErasePageUCM)
extrn code (Firmware_GetDiagnosticData)
extrn code (_Firmware_SetInterruptEnable)
extrn code (Firmware_GetInterruptEnable)

; Software simulated API's
extrn code (Firmware_WriteUCM)
