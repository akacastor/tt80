/*
;********************************************************************************************************
;
;    Name:          Software_APIs.a51
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
; $Revision: 1.4 $
; $Author: chin $ 
; $Date: 2005/08/30 14:52:26 $
;********************************************************************************************************
*/

$include (../Common_Titanium/Theseus_Titanium_Family.h)

extrn code (Firmware_WriteByteUCM)

; Library Functions
Public Firmware_WriteUCM, _Firmware_WriteUCM
Public Firmware_WriteEE, _Firmware_WriteEE


?PR?Software_APIs_Segment?Software_APIs SEGMENT CODE
	RSEG     ?PR?Software_APIs_Segment?Software_APIs

using 0

_Firmware_WriteEE:
Firmware_WriteEE:
_Firmware_WriteUCM:
Firmware_WriteUCM:					; Created as a software library for backwards
							; Theseus Platinum API compatibility

	mov	R0,AR5					; Backup the IDATA buffer address

Firmware_WriteNVM_Loop:
	mov	A,@R0					; Read the byte from IDATA pinted to by R0
	mov	R5,A					; Move the actual data byte into R5

	lcall	Firmware_WriteByteUCM			; Call the single byte write to UCM function
							; This function is expecting the target address
							; in R6 & R7 and the data byte to write in R5

	mov	A,R7					; Check the return value of the single write byte
	anl	A,#80h					; firmware call, if MSB is set it indicates error
	jnz	Firmware_WriteNVM_Return_Fail		; It will exit the function on error

	inc	R0					; Point to next IDATA buffer location containing data

	inc	DPTR					; Increment destination address
	mov	R6,DPH					; Load the address pointer into R6 & R7 as the
	mov	R7,DPL					; Firmware_WriteByteUCM function expects it there

	djnz	R3,Firmware_WriteNVM_Loop		; Keep writing until all the bytes (R3 - number of
							; of bytes) have been written

Firmware_WriteNVM_Return_Success:
	mov	R7,#0h
	ret

Firmware_WriteNVM_Return_Fail:
	mov	R7,#0FFh
	ret


END
