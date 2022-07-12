/*
;********************************************************************************************************
;
;    Name:          TT80_API_JumpTable.a51
;    Description:   Include file for the TT80 firmware and FSM interface
;    Author:        Mathew Key
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
;    $Revision: 1.5 $
;********************************************************************************************************
*/

#include "../Common_Titanium/Theseus_Titanium_Family.h"


; Define EMULATOR as 1 to create code compatible with the emulator.
; This will replace (some) NVFSM and IE usage with equivalent firmware calls.
; ALSO change Firmware_API_JumpTable.h to match.
; FW version 0x21 or higher is required.
;
$SET (EMULATOR = 0)


; Library Functions


; FSM interface
Public Firmware_MassEraseUCM, _Firmware_MassEraseUCM
Public Firmware_ErasePageUCM, _Firmware_ErasePageUCM
Public Firmware_EraseUCM256Bytes, _Firmware_EraseUCM256Bytes
Public Firmware_EraseUCM512Bytes, _Firmware_EraseUCM512Bytes
Public Firmware_WriteByteUCM, _Firmware_WriteByteUCM

Public Firmware_EraseUCM256Bytes_In_CODE_Space, _Firmware_EraseUCM256Bytes_In_CODE_Space
Public Firmware_EraseUCM512Bytes_In_CODE_Space, _Firmware_EraseUCM512Bytes_In_CODE_Space
Public Firmware_WriteByteUCM_In_CODE_Space, _Firmware_WriteByteUCM_In_CODE_Space


$IF (EMULATOR <> 1)
Public Firmware_API_Run_State_Machine
$ENDIF

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
$IF (EMULATOR = 1)
Public Firmware_SetInterruptEnable, _Firmware_SetInterruptEnable
Public Firmware_GetInterruptEnable, _Firmware_GetInterruptEnable
$ENDIF


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

_Firmware_GetRandomNumber:
Firmware_GetRandomNumber:				ds 2	;1E6

CSEG at 0x1F4

_Firmware_Set_IO_Pullup:
Firmware_Set_IO_Pullup:					ds 2	;1F4

$IF (EMULATOR = 1)
Firmware_API_WriteByteUCM:				ds 2	;1F6
Firmware_API_MassEraseUCM:				ds 2	;1F8
Firmware_API_ErasePageUCM:				ds 2	;1FA

_Firmware_SetInterruptEnable:
Firmware_SetInterruptEnable:				ds 2	;1FC

_Firmware_GetInterruptEnable:
Firmware_GetInterruptEnable:				ds 2	;1FE
$ENDIF



$IF (EMULATOR = 1)

?DT?TT80_FSM_Interface_Segment?TT80_API_Jumptable SEGMENT DATA OVERLAYABLE
	RSEG     ?DT?TT80_FSM_Interface_Segment?TT80_API_Jumptable

Temp_Addr_Hi:	ds 1					; Temporary address storage
Temp_Addr_Lo:	ds 1

$ENDIF


?PR?TT80_FSM_Interface_Segment?TT80_API_Jumptable SEGMENT CODE
	RSEG     ?PR?TT80_FSM_Interface_Segment?TT80_API_Jumptable




_Firmware_EraseUCM256Bytes:
Firmware_EraseUCM256Bytes:
_Firmware_ErasePageUCM:
Firmware_ErasePageUCM:

	lcall	Address_Boundary_Check			; Check address passed in r6 & r7 is valid
	jnz	Address_Error				; Address_Boundary_Check returns 0 if OK & FFh on error

$IF (EMULATOR <> 1)

; Setup the DPTR with the destination address
	mov	dph,r6
	mov	dpl,r7

; Select the NVM operation you want to perform	
	mov	NvFsmMode,#10h				; XDATA space 256 Byte Erase selected in FSM
	
	ljmp	Firmware_API_Run_State_Machine		; Run the State Machine, Setup Retcode and RET

$ELSE ; EMULATOR = 1

	ljmp	Firmware_API_ErasePageUCM

$ENDIF


_Firmware_EraseUCM256Bytes_In_CODE_Space:
Firmware_EraseUCM256Bytes_In_CODE_Space:

$IF (EMULATOR <> 1)

; Setup the DPTR with the destination address
	mov	dph,r6
	mov	dpl,r7

; Select the NVM operation you want to perform	
	mov	NvFsmMode,#11h				; CODE space 256 Byte Erase selected in FSM
	
	ljmp	Firmware_API_Run_State_Machine		; Run the State Machine, Setup Retcode and RET

$ELSE ; EMULATOR = 1

	sjmp	Address_Error				; Firmware cannot modify CODE space

$ENDIF






_Firmware_EraseUCM512Bytes:
Firmware_EraseUCM512Bytes:

$IF (EMULATOR <> 1)

	lcall	Address_Boundary_Check			; Check address passed in r6 & r7 is valid
	jnz	Address_Error				; Address_Boundary_Check returns 0 if OK & FFh on error

; Setup the DPTR with the destination address
	mov	dph,r6
	mov	dpl,r7

; Select the NVM operation you want to perform	
	mov	NvFsmMode,#20h				; XDATA space 512 Byte Erase selected in FSM
	
	ljmp	Firmware_API_Run_State_Machine		; Run the State Machine, Setup Retcode and RET

$ELSE ; EMULATOR = 1

	mov	Temp_Addr_Hi,r6				; Save page address
	mov	Temp_Addr_Lo,r7
	lcall	Firmware_API_ErasePageUCM		; Erase first 256-byte page

	mov	r6,Temp_Addr_Hi				; Restore page address and add 256
	inc	r6
	mov	r7,Temp_Addr_Lo
	ljmp	Firmware_API_ErasePageUCM		; Erase second 256-byte page

$ENDIF



_Firmware_EraseUCM512Bytes_In_CODE_Space:
Firmware_EraseUCM512Bytes_In_CODE_Space:

$IF (EMULATOR <> 1)

	lcall	Address_Boundary_Check			; Check address passed in r6 & r7 is valid
	jnz	Address_Error				; Address_Boundary_Check returns 0 if OK & FFh on error

; Setup the DPTR with the destination address
	mov	dph,r6
	mov	dpl,r7

; Select the NVM operation you want to perform	
	mov	NvFsmMode,#21h				; CODE space 512 Byte Erase selected in FSM
	
	ljmp	Firmware_API_Run_State_Machine		; Run the State Machine, Setup Retcode and RET

$ELSE ; EMULATOR = 1

	sjmp	Address_Error				; Firmware cannot modify CODE space

$ENDIF






_Firmware_WriteByteUCM_In_CODE_Space:
Firmware_WriteByteUCM_In_CODE_Space:

$IF (EMULATOR <> 1)

	lcall	Address_Boundary_Check			; Check address passed in r6 & r7 is valid
	jnz	Address_Error				; Address_Boundary_Check returns 0 if OK & FFh on error

; Setup the DPTR with the destination address
	mov	dph,r6
	mov	dpl,r7

; Select the NVM operation you want to perform	
	mov	NvFsmMode,#05h				; CODE space Byte Write selected in FSM
	
; For Byte Writes you must have the desired byte in Acc.
	mov	a,r5
	ljmp	Firmware_API_Run_State_Machine		; Run the State Machine, Setup Retcode and RET

$ELSE ; EMULATOR = 1

	sjmp	Address_Error				; Firmware cannot modify CODE space

$ENDIF




_Firmware_WriteByteUCM:
Firmware_WriteByteUCM:

	lcall	Address_Boundary_Check			; Check address passed in r6 & r7 is valid
	jnz	Address_Error				; Address_Boundary_Check returns 0 if OK & FFh on error

$IF (EMULATOR <> 1)

; Setup the DPTR with the destination address
	mov	dph,r6
	mov	dpl,r7

; Select the NVM operation you want to perform	
	mov	NvFsmMode,#04h				; XDATA space Byte Write selected in FSM
	
; For Byte Writes you must have the desired byte in Acc.
	mov	a,r5

$ELSE ; EMULATOR = 1

	ljmp	Firmware_API_WriteByteUCM

$ENDIF





$IF (EMULATOR <> 1)

; Set the NVM Finite Statem Machine running
Firmware_API_Run_State_Machine:

; Setup the FSM with the desired address.
; This line MUST be included as this sets up hardware in the FSM.
; You MUST have the destination address in the DPTR at this point.
; For Byte Writes you must have the desired byte in Acc.
; For Page Erases the value of Acc doesn't matter.
	movx	@dptr,a					; Select memory address

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

$ENDIF




_Firmware_MassEraseUCM:
Firmware_MassEraseUCM:

$IF (EMULATOR = 1)

	ljmp	Firmware_API_MassEraseUCM

$ELSE ; EMULATOR <> 1

; Do the Mass Erase via the FSM

; NOTE - this erases all UCM...including bootloader and OS. 
; So there is nothing to execute on return of this function
	mov	NvFsmMode,#070h				; Mass Erase UCM
	mov	NvFsmCon,#02h				; Set Start Bit
	jnb	NvFsmCon.0,$				; Wait for the Done flag
	ret

$ENDIF




_Address_Boundary_Check:
Address_Boundary_Check:

; R6 & R7 contain the address of page to erase
; Check that the page is within the UCM boundary
; for the TT80 UCM
; e.g. Only addresses above 800h are allowed
	clr	c
	mov	a,r6
	subb	a,#08h					; check the high address byte is above 08h
	jc	Return_Error
	clr	a					; if the code gets here the address is within the 
							; TT80 UCM boundary so return 0 in Acc
	ret

Return_Error:	
	mov	a,#0FFh					; return FFh in Acc to state address violation

	ret						; This should return to the calling NVM function



Address_Error:
	mov	r7,#0FFh				; code failed becuase of address boundary check
							; put FFh into r7 (NVM operation failed) & return to calling function
	ret

END
