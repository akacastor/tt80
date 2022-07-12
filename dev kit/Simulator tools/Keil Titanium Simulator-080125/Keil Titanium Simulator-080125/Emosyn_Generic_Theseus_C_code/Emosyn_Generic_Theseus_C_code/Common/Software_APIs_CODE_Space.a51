/*
;********************************************************************************************************
;
;    Name:          Software_APIs_CODE_Space.a51
;    Description:   API's to simulate previous Theseus family firmware API's
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
; $Revision: 1.1 $
; $Author: chin $ 
; $Date: 2005/08/30 14:57:03 $
;********************************************************************************************************
*/

$include (../Common_Titanium/Theseus_Titanium_Family.h)

extrn code (Firmware_WriteByteUCM_In_CODE_Space)


; Library Functions
Public Firmware_WriteUCM_In_CODE_Space, _Firmware_WriteUCM_In_CODE_Space
Public Firmware_WriteEE_In_CODE_Space, _Firmware_WriteEE_In_CODE_Space


?PR?Software_APIs_CODE_Space_Segment?Software_APIs_CODE_Space SEGMENT CODE
	RSEG     ?PR?Software_APIs_CODE_Space_Segment?Software_APIs_CODE_Space

using 0

_Firmware_WriteUCM_In_CODE_Space:
Firmware_WriteUCM_In_CODE_Space:			; Created as a software library for backwards
_Firmware_WriteEE_In_CODE_Space:			; Theseus Platinum API compatibility
Firmware_WriteEE_In_CODE_Space:

	mov	R0,AR5					; Backup the IDATA buffer address

Firmware_WriteNVM_In_CODE_Space_Loop:
	mov	A,@R0					; Read the byte from IDATA pinted to by R0
	mov	R5,A					; Move the actual data byte into R5

	lcall	Firmware_WriteByteUCM_In_CODE_Space	; Call the single byte write to UCM function
							; This function is expecting the target address
							; in R6 & R7 and the data byte to write in R5

	mov	A,R7					; Check the return value of the single write byte
	anl	A,#80h					; firmware call, if MSB is set it indicates error
	jnz	Firmware_WriteNVM_Return_Fail		; It will exit the function on error

	inc	R0					; Point to next IDATA buffer location containing data

	inc	DPTR					; Increment destination address
	mov	R6,DPH					; Load the address pointer into R6 & R7 as the
	mov	R7,DPL					; Firmware_WriteByteUCM function expects it there

	djnz	R3,Firmware_WriteNVM_In_CODE_Space_Loop	; Keep writing until all the bytes (R3 - number of
							; of bytes) have been written

	sjmp	Firmware_WriteNVM_Return_Success	; If this point is reached all bytes were written successfully


Firmware_WriteNVM_Return_Success:
	mov	R7,#0h
	ret

Firmware_WriteNVM_Return_Fail:
	mov	R7,#0FFh
	ret


END
