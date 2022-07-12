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
;    $Revision: 1.6 $
;********************************************************************************************************
*/

#include "../Common_Titanium/Theseus_Titanium_Family.h"


; Define EMULATOR as 1 to create code compatible with the emulator.
; This will always use the firmware emulator API for NVFSM and IE access.
; FW version 0x21 or higher is required.
;
$SET (EMULATOR = 0)


; Library Functions

Public Firmware_Init
Public _Firmware_Use_Emulator_API

Public _Firmware_SetInterruptEnable
Public Firmware_GetInterruptEnable

; FSM interface
Public Firmware_MassEraseUCM, _Firmware_MassEraseUCM
Public Firmware_ErasePageUCM, _Firmware_ErasePageUCM
Public Firmware_EraseUCM256Bytes, _Firmware_EraseUCM256Bytes
Public Firmware_EraseUCM512Bytes, _Firmware_EraseUCM512Bytes
Public Firmware_WriteByteUCM, _Firmware_WriteByteUCM

Public Firmware_EraseUCM256Bytes_In_CODE_Space, _Firmware_EraseUCM256Bytes_In_CODE_Space
Public Firmware_EraseUCM512Bytes_In_CODE_Space, _Firmware_EraseUCM512Bytes_In_CODE_Space
Public Firmware_WriteByteUCM_In_CODE_Space, _Firmware_WriteByteUCM_In_CODE_Space


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

; The following emulator API were added in FW version 0x21.

_Firmware_API_WriteByteUCM:
Firmware_API_WriteByteUCM:				ds 2	;1F6

_Firmware_API_MassEraseUCM:
Firmware_API_MassEraseUCM:				ds 2	;1F8

_Firmware_API_ErasePageUCM:
Firmware_API_ErasePageUCM:				ds 2	;1FA

_Firmware_API_SetInterruptEnable:
Firmware_API_SetInterruptEnable:			ds 2	;1FC

_Firmware_API_GetInterruptEnable:
Firmware_API_GetInterruptEnable:			ds 2	;1FE




?DT?TT80_FSM_Interface_Segment?TT80_API_Jumptable SEGMENT DATA OVERLAYABLE
	RSEG     ?DT?TT80_FSM_Interface_Segment?TT80_API_Jumptable

Temp_Addr_Hi:	ds 1					; Temporary address storage
Temp_Addr_Lo:	ds 1



?BI?TT80_FSM_Interface_Segment?TT80_API_Jumptable SEGMENT BIT OVERLAYABLE
	RSEG     ?BI?TT80_FSM_Interface_Segment?TT80_API_Jumptable

Use_Emulator_API:	dbit 1				; Use the emulator API?



?PR?TT80_FSM_Interface_Segment?TT80_API_Jumptable SEGMENT CODE
	RSEG     ?PR?TT80_FSM_Interface_Segment?TT80_API_Jumptable




;*******************************************************************************
;
; Description	Initialize the firmware interface library.
;
; API		void Firmware_Init (void)
;
; Inputs	None
;	
; Outputs	None
;
; Registers changed:
;		None
;
; Notes:	Must be called once prior to using any other firmware functions.
;
;*******************************************************************************
Firmware_Init:

; If built for emulator, always use the emulator API. Otherwise, use direct access.

$IF (EMULATOR = 1)
	setb	Use_Emulator_API
$ELSE
	clr	Use_Emulator_API
$ENDIF
	ret



;*******************************************************************************
;
; Description	Select whether to use the firmware emulator API or to use
;		direct access for NVFSM and IE usage.
;
; API		unsigned char Firmware_Use_Emulator_API (unsigned char value)
;
; Inputs	R7	value
;			00	Use direct access
;			01	Use emulator API
;
; Outputs	R7	result
;			00	Success
;			FF	Failure: bad selection
;
; Registers changed:
;		ACC
;
; Notes:	The primary purpose of this function is to allow one to test
;		the firmware emulator API.
;
;*******************************************************************************
_Firmware_Use_Emulator_API:

$IF (EMULATOR = 1)

; If built for emulator, only emulator API usage is allowed.
	mov	a, r7
	jz	_Firmware_Use_Emulator_API_Fail

$ELSE

; If built for device, test for emulator API presence using firmware version.
; FW version 0x21 or higher is required.
	mov	a, r7
	clr	Use_Emulator_API
	jz	_Firmware_Use_Emulator_API_Success	; Use direct access

	call	Firmware_GetFirmwareVersion		; R7 = version
	clr	c
	mov	a, r7
	subb	a, #021h				; Is version 0x21 or higher?
	jc	_Firmware_Use_Emulator_API_Fail		; Nope: failure

	setb	Use_Emulator_API			; Yep: success

$ENDIF

_Firmware_Use_Emulator_API_Success:
	mov	r7, #00h
	ret

_Firmware_Use_Emulator_API_Fail:
	mov	r7, #0FFh
	ret


;*******************************************************************************


_Firmware_EraseUCM256Bytes:
Firmware_EraseUCM256Bytes:
_Firmware_ErasePageUCM:
Firmware_ErasePageUCM:

	lcall	Address_Boundary_Check			; Check address passed in r6 & r7 is valid
	jnz	Address_Error				; Address_Boundary_Check returns 0 if OK & FFh on error

; Use emulator API if so chosen.
	jb	Use_Emulator_API, ErasePageUCM_Emulator

; Setup the DPTR with the destination address
	mov	dph,r6
	mov	dpl,r7

; Select the NVM operation you want to perform	
	mov	NvFsmMode,#10h				; XDATA space 256 Byte Erase selected in FSM
	
	ljmp	Firmware_API_Run_State_Machine		; Run the State Machine, Setup Retcode and RET


ErasePageUCM_Emulator:
	ljmp	Firmware_API_ErasePageUCM




_Firmware_EraseUCM256Bytes_In_CODE_Space:
Firmware_EraseUCM256Bytes_In_CODE_Space:

; If using emulator API, return fail. Firmware cannot modify CODE space
	jb	Use_Emulator_API, Address_Error

; Setup the DPTR with the destination address
	mov	dph,r6
	mov	dpl,r7

; Select the NVM operation you want to perform	
	mov	NvFsmMode,#11h				; CODE space 256 Byte Erase selected in FSM
	
	ljmp	Firmware_API_Run_State_Machine		; Run the State Machine, Setup Retcode and RET






_Firmware_EraseUCM512Bytes:
Firmware_EraseUCM512Bytes:

	lcall	Address_Boundary_Check			; Check address passed in r6 & r7 is valid
	jnz	Address_Error				; Address_Boundary_Check returns 0 if OK & FFh on error

; Use emulator API if so chosen.
	jb	Use_Emulator_API, EraseUCM512Bytes_Emulator

; Setup the DPTR with the destination address
	mov	dph,r6
	mov	dpl,r7

; Select the NVM operation you want to perform	
	mov	NvFsmMode,#20h				; XDATA space 512 Byte Erase selected in FSM
	
	ljmp	Firmware_API_Run_State_Machine		; Run the State Machine, Setup Retcode and RET


; Simulate 512 byte erase with two 256 byte erases.
EraseUCM512Bytes_Emulator:
	mov	Temp_Addr_Hi,r6				; Save page address
	mov	Temp_Addr_Lo,r7
	lcall	Firmware_API_ErasePageUCM		; Erase first 256-byte page

	mov	r6,Temp_Addr_Hi				; Restore page address and add 256
	inc	r6
	mov	r7,Temp_Addr_Lo
	ljmp	Firmware_API_ErasePageUCM		; Erase second 256-byte page




_Firmware_EraseUCM512Bytes_In_CODE_Space:
Firmware_EraseUCM512Bytes_In_CODE_Space:

; If using emulator API, return fail. Firmware cannot modify CODE space
	jb	Use_Emulator_API, Address_Error

; Setup the DPTR with the destination address
	lcall	Address_Boundary_Check			; Check address passed in r6 & r7 is valid
	jnz	Address_Error				; Address_Boundary_Check returns 0 if OK & FFh on error

; Setup the DPTR with the destination address
	mov	dph,r6
	mov	dpl,r7

; Select the NVM operation you want to perform	
	mov	NvFsmMode,#21h				; CODE space 512 Byte Erase selected in FSM
	
	ljmp	Firmware_API_Run_State_Machine		; Run the State Machine, Setup Retcode and RET






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




_Firmware_MassEraseUCM:
Firmware_MassEraseUCM:

; Use emulator API if so chosen.
	jb	Use_Emulator_API, MassEraseUCM_Emulator

; Do the Mass Erase via the FSM

; NOTE - this erases all UCM...including bootloader and OS. 
; So there is nothing to execute on return of this function
	mov	NvFsmMode,#070h				; Mass Erase UCM
	mov	NvFsmCon,#02h				; Set Start Bit
	jnb	NvFsmCon.0,$				; Wait for the Done flag
	ret

MassEraseUCM_Emulator:
	ljmp	Firmware_API_MassEraseUCM




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




_Firmware_WriteByteUCM_In_CODE_Space:
Firmware_WriteByteUCM_In_CODE_Space:

; If using emulator API, return fail. Firmware cannot modify CODE space
	jb	Use_Emulator_API, Address_Error

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




_Firmware_WriteByteUCM:
Firmware_WriteByteUCM:

	lcall	Address_Boundary_Check			; Check address passed in r6 & r7 is valid
	jnz	Address_Error				; Address_Boundary_Check returns 0 if OK & FFh on error

; Use emulator API if so chosen.
	jb	Use_Emulator_API, WriteByteUCM_Emulator

; Setup the DPTR with the destination address
	mov	dph,r6
	mov	dpl,r7

; Select the NVM operation you want to perform	
	mov	NvFsmMode,#04h				; XDATA space Byte Write selected in FSM
	
; For Byte Writes you must have the desired byte in Acc.
	mov	a,r5

WriteByteUCM_Emulator:
	ljmp	Firmware_API_WriteByteUCM





_Firmware_SetInterruptEnable:

; Use emulator API if so chosen.
	jb	Use_Emulator_API, SetInterruptEnable_Emulator

; Set IE.
	mov	IE, r7
	ret

SetInterruptEnable_Emulator:
	ljmp	Firmware_API_SetInterruptEnable





Firmware_GetInterruptEnable:

; Use emulator API if so chosen.
	jb	Use_Emulator_API, GetInterruptEnable_Emulator

; Get IE.
	mov	r7, IE
	ret

GetInterruptEnable_Emulator:
	ljmp	Firmware_API_GetInterruptEnable

END
