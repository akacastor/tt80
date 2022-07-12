/*
;********************************************************************************************************
;
;    Name:          TT30_API_JumpTable.a51
;    Description:   Include file for the TT30 firmware and FSM interface
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
; $Revision: 1.4 $
; $Author: chin $ 
; $Date: 2005/10/26 16:37:59 $
;********************************************************************************************************
*/

#include "../Common_Titanium/Theseus_Titanium_Family.h"

; Library Functions



; FSM interface
Public Firmware_MassEraseUCM, _Firmware_MassEraseUCM
Public Firmware_ErasePageUCM, _Firmware_ErasePageUCM
Public Firmware_EraseUCM256Bytes, _Firmware_EraseUCM256Bytes
Public Firmware_EraseUCM512Bytes, _Firmware_EraseUCM512Bytes
Public Firmware_WriteByteUCM, _Firmware_WriteByteUCM


; Firmware jumptable
Public Firmware_EraseUCMBlock, _Firmware_EraseUCMBlock
Public Firmware_GetChipID, _Firmware_GetChipID
Public Firmware_SetProtectStatus, _Firmware_SetProtectStatus
Public Firmware_SetSecurityAction, _Firmware_SetSecurityAction
Public Firmware_SetSecurityMask, _Firmware_SetSecurityMask


Public Firmware_GetFirmwareVersion, _Firmware_GetFirmwareVersion
Public Firmware_SetClock, _Firmware_SetClock


Public Firmware_SetClockTrim, _Firmware_SetClockTrim
Public Firmware_GetClockSourceSelectSFR, _Firmware_GetClockSourceSelectSFR
Public Firmware_GetClockControlSFR, _Firmware_GetClockControlSFR
Public Firmware_SetExecuteOnlyStatus, _Firmware_SetExecuteOnlyStatus

Public Firmware_GetDiagnosticData, _Firmware_GetDiagnosticData


CSEG at 0x1CE

_Firmware_SetClockTrim:
Firmware_SetClockTrim:					ds 2	;1CE

_Firmware_EraseUCMBlock:
Firmware_EraseUCMBlock:					ds 2	;1D0

_Firmware_SetSecurityAction:
Firmware_SetSecurityAction:				ds 2	;1D2

_Firmware_SetSecurityMask:
Firmware_SetSecurityMask:				ds 2	;1D4

_Firmware_SetExecuteOnlyStatus:
Firmware_SetExecuteOnlyStatus:				ds 2	;1D6

_Firmware_SetProtectStatus:
Firmware_SetProtectStatus:				ds 2	;1D8

_Firmware_GetChipID:
Firmware_GetChipID:					ds 2	;1DA

_Firmware_GetFirmwareVersion:
Firmware_GetFirmwareVersion:				ds 2	;1DC

_Firmware_SetClock:
Firmware_SetClock:					ds 2	;1DE

_Firmware_GetClockSourceSelectSFR:
Firmware_GetClockSourceSelectSFR:			ds 2	;1E0

_Firmware_GetClockControlSFR:
Firmware_GetClockControlSFR:				ds 2	;1E2

_Firmware_GetDiagnosticData:
Firmware_GetDiagnosticData:				ds 2	;1E4



?PR?TT30_FSM_Interface_Segment?TT30_API_Jumptable SEGMENT CODE
	RSEG     ?PR?TT30_FSM_Interface_Segment?TT30_API_Jumptable



_Firmware_EraseUCM256Bytes:
Firmware_EraseUCM256Bytes:
_Firmware_ErasePageUCM:
Firmware_ErasePageUCM:

	acall	Address_Boundary_Check			; Check address passed in r6 & r7 is valid
	jnz	Address_Error				; Address_Boundary_Check returns 0 if OK & FFh on error

; Setup the DPTR with the destination address
	mov	dph,r6
	mov	dpl,r7

; Select the NVM operation you want to perform	
	mov	NvFsmMode,#10h				; 256 Byte Erase selected in FSM
	
; Setup the FSM with the desired address.
; This line MUST be included as this sets up hardware in the FSM.
; You MUST have the destination address in the DPTR at this point.
; For Byte Writes you must have the desired byte in Acc.
; For Page Erases the value of Acc doesn't matter.
	movx	@dptr,a					; Select memory address
	ljmp	Firmware_API_Run_State_Machine		; Run the State Machine, Setup Retcode and RET







_Firmware_EraseUCM512Bytes:
Firmware_EraseUCM512Bytes:

	acall	Address_Boundary_Check			; Check address passed in r6 & r7 is valid
	jnz	Address_Error				; Address_Boundary_Check returns 0 if OK & FFh on error

; Setup the DPTR with the destination address
	mov	dph,r6
	mov	dpl,r7

; Select the NVM operation you want to perform	
	mov	NvFsmMode,#20h				; 512 Byte Erase selected in FSM
	
; Setup the FSM with the desired address.
; This line MUST be included as this sets up hardware in the FSM.
; You MUST have the destination address in the DPTR at this point.
; For Byte Writes you must have the desired byte in Acc.
; For Page Erases the value of Acc doesn't matter.
	movx	@dptr,a					; Select memory address
	ljmp	Firmware_API_Run_State_Machine		; Run the State Machine, Setup Retcode and RET






_Firmware_MassEraseUCM:
Firmware_MassEraseUCM:
; Do the Mass Erase via the FSM

; NOTE - this erases all UCM...including bootloader and OS. 
; So there is nothing to execute on return of this function
	mov	NvFsmMode,#070h				; Mass Erase UCM
	mov	NvFsmCon,#02h				; Set Start Bit
	jnb	NvFsmCon.0,$				; Wait for the Done flag

	ret






_Firmware_WriteByteUCM:
Firmware_WriteByteUCM:

	acall	Address_Boundary_Check			; Check address passed in r6 & r7 is valid
	jnz	Address_Error				; Address_Boundary_Check returns 0 if OK & FFh on error

; Setup the DPTR with the destination address
	mov	dph,r6
	mov	dpl,r7

; Select the NVM operation you want to perform	
	mov	NvFsmMode,#04h				; Byte Write selected in FSM
	
; Setup the FSM with the desired address.
; This line MUST be included as this sets up hardware in the FSM.
; You MUST have the destination address in the DPTR at this point.
; For Byte Writes you must have the desired byte in Acc.
; For Page Erases the value of Acc doesn't matter.
	mov	a,r5
	movx	@dptr,a					; Setup the FSM with the desired address


; Set the NVM Finite Statem Machine running
Firmware_API_Run_State_Machine:

	orl	NvFsmCon,#02h				; Set Start Bit
	jnb	NvFsmCon.0,$				; Wait for the NvInt flag
							; This tells us the FSM has completed its task

	clr	NvFsmCon.0				; Clear the NvInt flag

; Here we setup a return code for a C function
; Success will be 1 if FSM operation successful
; Will be 0 if FSM operation failed.
	mov	r7,#0					; Assume Success until we check below
	jb	NvFsmCon.5,Firmware_API_Run_State_Machine__Return
	mov	r7,#0FFh				; If Success bit not set then return Fail
Firmware_API_Run_State_Machine__Return:

	ret






_Address_Boundary_Check:
Address_Boundary_Check:

; R6 & R7 contain the address of page to erase
; Check that the page is within the UCM boundary
; for the TT30 UCM
; e.g. above 400h and less than 7C00h
	clr	c
	mov	a,r6
	subb	a,#04h					; check the high address byte is above 04h
	jc	Return_Error
	mov	a,r6
	add	a,#84h					; check the high address byte is less than 7Ch (84h + 7Ch = 100h)
	jc	Return_Error
	clr	a					; if the code gets here the address is within the 
							; TT30 UCM boundary so return 0 in Acc
	ret

Return_Error:	
	mov	a,#0FFh					; return FFh in Acc to state address violation

	ret



Address_Error:
	mov	r7,#0FFh				; code failed becuase of address boundary check
							; put FFh into r7 (NVM operation failed) & return to calling function
	ret

	
END
