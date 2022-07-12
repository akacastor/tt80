;********************************************************************************************************
;
;    Name:          TT120_API_JumpTable.a51
;    Description:   Include file for the TT120 firmware and FSM interface
;    Copyright:	    Emosyn Inc. 2006
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
; $Date: 2006/03/08 18:50:14 $
;********************************************************************************************************

#include "../Common_Titanium/Theseus_Titanium_Family.h"


; Library Functions


; FSM interface
Public Firmware_MassEraseUCM, _Firmware_MassEraseUCM
Public Firmware_ErasePageUCM, _Firmware_ErasePageUCM
Public Firmware_EraseUCM256Bytes, _Firmware_EraseUCM256Bytes
Public Firmware_EraseUCM512Bytes, _Firmware_EraseUCM512Bytes
Public Firmware_WriteByteUCM, _Firmware_WriteByteUCM

;Public Firmware_API_Run_State_Machine

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
Public Firmware_GetRandomNumber, _Firmware_GetRandomNumber
Public Firmware_Set_IO_Pullup, _Firmware_Set_IO_Pullup


CSEG at 0x1CD

_Firmware_SetClockTrim:
Firmware_SetClockTrim:			ds 3

_Firmware_EraseUCMBlock:
Firmware_EraseUCMBlock:			ds 3

_Firmware_SetSecurityAction:
Firmware_SetSecurityAction:		ds 3

_Firmware_SetSecurityMask:
Firmware_SetSecurityMask:		ds 3

_Firmware_SetExecuteOnlyStatus:
Firmware_SetExecuteOnlyStatus:		ds 3

_Firmware_SetProtectStatus:
Firmware_SetProtectStatus:		ds 3

_Firmware_GetChipID:
Firmware_GetChipID:			ds 3

_Firmware_GetFirmwareVersion:
Firmware_GetFirmwareVersion:		ds 3

_Firmware_SetClock:
Firmware_SetClock:			ds 3

_Firmware_GetClockSourceSelectSFR:
Firmware_GetClockSourceSelectSFR:	ds 3

_Firmware_GetClockControlSFR:
Firmware_GetClockControlSFR:		ds 3

_Firmware_GetDiagnosticData:
Firmware_GetDiagnosticData:		ds 3

_Firmware_GetRandomNumber:
Firmware_GetRandomNumber:		ds 3

CSEG at 0x1F4

_Firmware_Set_IO_Pullup:
Firmware_Set_IO_Pullup:			ds 3



?PR?TT120_FSM_Interface_Segment?TT120_API_Jumptable SEGMENT CODE
	RSEG     ?PR?TT120_FSM_Interface_Segment?TT120_API_Jumptable

_Firmware_ErasePageUCM:
Firmware_ErasePageUCM:
_Firmware_EraseUCM256Bytes:
Firmware_EraseUCM256Bytes:
	acall	Load_DPTR					; Load DPTR with address the FSM will perform its operation on
								; This function also does an address boundary check

	jnz	Address_Error					; Return value from Load_DPTR is in the ACC
								; Non zero value means address boundary error

	mov	NvFsmMode,#10h					; 256 Byte UCM Erase
	movx	@dptr,a						; Select memory address
	ajmp	Firmware_API_Run_State_Machine			; Run the State Machine, Setup Retcode and RET

	ret



_Firmware_EraseUCM512Bytes:
Firmware_EraseUCM512Bytes:
	acall	Load_DPTR					; Load DPTR with address the FSM will perform its operation on
								; This function also does an address boundary check

	jnz	Address_Error					; Return value from Load_DPTR is in the ACC
								; Non zero value means address boundary error

	mov	NvFsmMode,#20h					; 512 Byte UCM Erase
	movx	@dptr,a						; Select memory address.
	ajmp	Firmware_API_Run_State_Machine			; Run the State Machine, Setup Retcode and RET

	ret



_Firmware_MassEraseUCM:
Firmware_MassEraseUCM:
; Do the Mass Erase via the FSM
; NOTE - this erases all UCM...including bootloader and OS. 
; So there is nothing to execute on return of this function
	mov	NvFsmMode,#070h					; Mass Erase UCM
	mov	NvFsmCon,#02h					; Set Start Bit
	jnb	NvFsmCon.0,$					; Wait for the Done flag

	ret



_Firmware_WriteByteUCM:
Firmware_WriteByteUCM:
	acall	Load_DPTR					; Load DPTR with address the FSM will perform its operation on
								; This function also does an address boundary check

	jnz	Address_Error					; Return value from Load_DPTR is in the ACC
								; Non zero value means address boundary error

	mov	a,r5						; Load the byte to write into ACC

	mov	NvFsmMode,#04h					; Byte Write selected in FSM
	movx	@dptr,a						; Setup the FSM with the desired address



; Set the NVM Finite Statem Machine running
Firmware_API_Run_State_Machine:
	orl	NvFsmCon,#02h					; Set Start Bit
	jnb	NvFsmCon.0,$					; Wait for the NvInt flag
								; This tells us the FSM has completed its task

	clr	NvFsmCon.0					; Clear the NvInt flag


	; Success will be 1 if FSM operation successful
	; Will be 0 if FSM operation failed.
	mov	r7,#0						; Assume Success until we check below
	jb	NvFsmCon.5,Firmware_API_Run_State_Machine__Return
	mov	r7,#0FFh					; If Success bit not set then return Fail

Firmware_API_Run_State_Machine__Return:

	ret



Load_DPTR:
	mov	DPX,r3						; Load DPX value
	mov	DPH,r2						; Load DPH value
	mov	DPL,r1						; Load DPL value

; Check that the page or byte is within the UCM boundary
; for the TT120 UCM
; e.g. above 800h and less than 1E800h
	clr	c
	mov	a,DPX
	jnz	Check_High_Address_Boundary		; if non zero it is above the 64K range

	mov	a,DPH
	subb	a,#08h					; check the high address byte is above 08h
	jc	Return_Error				; If carry flag set it means the address is not valid

	clr	a					; Address is less than not above 64K & above 800h 
							; Return 0 (success) in ACC
	ret

Check_High_Address_Boundary:
	cjne	a,#01h,Return_Error			; Jump to error if DPX is not 01 (value can only be 00 or 01)

	mov	a,DPH					; Load in DPH value to test
	add	a,#018h					; E8h + 18h will set carry flag (1E800h is start of XRAM)
	jc	Return_Error				; If carry flag set it means the address is not valid

	clr	a					; Address is less than 1E800h so return 0 (success) in ACC

	ret

Return_Error:	
	mov	a,#0FFh					; return FFh in Acc to state address violation

	ret



Address_Error:
	mov	r7,#0FFh				; code failed becuase of address boundary check
							; put FFh into r7 (NVM operation failed) & return to calling function
	ret



END
