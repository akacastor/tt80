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
; $Revision: 1.3 $
; $Author: dhunter $ 
; $Date: 2006/11/02 22:35:38 $
;********************************************************************************************************

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

CSEG at 0x206

_Firmware_Set_IO_Pullup:
Firmware_Set_IO_Pullup:			ds 3

; The following emulator API were added in FW version 0x21.

_Firmware_API_WriteByteUCM:
Firmware_API_WriteByteUCM:		ds 3	;209

_Firmware_API_MassEraseUCM:
Firmware_API_MassEraseUCM:		ds 3	;20C

_Firmware_API_ErasePageUCM:
Firmware_API_ErasePageUCM:		ds 3	;20F

_Firmware_API_SetInterruptEnable:
Firmware_API_SetInterruptEnable:	ds 3	;212

_Firmware_API_GetInterruptEnable:
Firmware_API_GetInterruptEnable:	ds 3	;215



?DT?TT120_FSM_Interface_Segment?TT120_API_Jumptable SEGMENT DATA OVERLAYABLE
	RSEG     ?DT?TT120_FSM_Interface_Segment?TT120_API_Jumptable

Temp_Addr_DPX:	ds 1					; Temporary address storage
Temp_Addr_Hi:	ds 1



?BI?TT120_FSM_Interface_Segment?TT120_API_Jumptable SEGMENT BIT OVERLAYABLE
	RSEG     ?BI?TT120_FSM_Interface_Segment?TT120_API_Jumptable

Use_Emulator_API:	dbit 1				; Use the emulator API?



?PR?TT120_FSM_Interface_Segment?TT120_API_Jumptable SEGMENT CODE
	RSEG     ?PR?TT120_FSM_Interface_Segment?TT120_API_Jumptable



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


_Firmware_ErasePageUCM:
Firmware_ErasePageUCM:
_Firmware_EraseUCM256Bytes:
Firmware_EraseUCM256Bytes:
	acall	Load_DPTR					; Load DPTR with address the FSM will perform its operation on
								; This function also does an address boundary check

	jnz	Address_Error					; Return value from Load_DPTR is in the ACC
								; Non zero value means address boundary error

	jb	Use_Emulator_API, ErasePageUCM_Emulator		; Use emulator API if so chosen.

	mov	NvFsmMode,#10h					; 256 Byte UCM Erase
	movx	@dptr,a						; Select memory address
	ajmp	Firmware_API_Run_State_Machine			; Run the State Machine, Setup Retcode and RET


ErasePageUCM_Emulator:
	ljmp	Firmware_API_ErasePageUCM



_Firmware_EraseUCM512Bytes:
Firmware_EraseUCM512Bytes:
	acall	Load_DPTR					; Load DPTR with address the FSM will perform its operation on
								; This function also does an address boundary check

	jnz	Address_Error					; Return value from Load_DPTR is in the ACC
								; Non zero value means address boundary error

	jb	Use_Emulator_API, EraseUCM512Bytes_Emulator	; Use emulator API if so chosen.

	mov	NvFsmMode,#20h					; 512 Byte UCM Erase
	movx	@dptr,a						; Select memory address.
	ajmp	Firmware_API_Run_State_Machine			; Run the State Machine, Setup Retcode and RET


; Simulate 512 byte erase with two 256 byte erases.
EraseUCM512Bytes_Emulator:
	mov	a,r2						; Address bits A[8:0] are ignored: clear them.
	anl	a,#NOT 01h
	mov	r2,a
	mov	Temp_Addr_DPX,r3				; Save page address
	mov	Temp_Addr_Hi,r2

	mov	r1,#0
	lcall	Firmware_API_ErasePageUCM			; Erase first 256-byte page

	mov	r3,Temp_Addr_DPX				; Restore page address and add 256
	mov	r2,Temp_Addr_Hi	
	inc	r2
	mov	r1,#0
	ljmp	Firmware_API_ErasePageUCM			; Erase second 256-byte page



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




_Firmware_MassEraseUCM:
Firmware_MassEraseUCM:
; Do the Mass Erase via the FSM
; NOTE - this erases all UCM...including bootloader and OS. 
; So there is nothing to execute on return of this function
	jb	Use_Emulator_API, MassEraseUCM_Emulator		; Use emulator API if so chosen.

	mov	NvFsmMode,#070h					; Mass Erase UCM
	mov	NvFsmCon,#02h					; Set Start Bit
	jnb	NvFsmCon.0,$					; Wait for the Done flag

	ret

MassEraseUCM_Emulator:
	ljmp	Firmware_API_MassEraseUCM



_Firmware_WriteByteUCM:
Firmware_WriteByteUCM:
	acall	Load_DPTR					; Load DPTR with address the FSM will perform its operation on
								; This function also does an address boundary check

	jnz	Address_Error					; Return value from Load_DPTR is in the ACC
								; Non zero value means address boundary error

	jb	Use_Emulator_API, WriteByteUCM_Emulator		; Use emulator API if so chosen.

	mov	a,r5						; Load the byte to write into ACC

	mov	NvFsmMode,#04h					; Byte Write selected in FSM
	movx	@dptr,a						; Setup the FSM with the desired address

WriteByteUCM_Emulator:
	ljmp	Firmware_API_WriteByteUCM




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
