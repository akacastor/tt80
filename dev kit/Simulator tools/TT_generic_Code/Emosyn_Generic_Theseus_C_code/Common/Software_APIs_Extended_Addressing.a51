/*
;********************************************************************************************************
;
;    Name:          Software_APIs_Extended_Addressing.a51
;    Description:   API's to simulate previous Theseus family firmware API's for extended addressing chips
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
; $Date: 2006/03/08 16:21:59 $
;********************************************************************************************************
*/

$include (../Common_Titanium/Theseus_Titanium_Family.h)

extrn code (Firmware_WriteByteUCM)

; Library Functions
Public Firmware_WriteUCM, _Firmware_WriteUCM
Public Firmware_WriteEE, _Firmware_WriteEE


?PR?Software_APIs_Extended_Addressing?Software_APIs_Extended_Addressing SEGMENT CODE
	RSEG     ?PR?Software_APIs_Extended_Addressing?Software_APIs_Extended_Addressing

using 0

_Firmware_WriteEE:					; Created as a software library for backwards
Firmware_WriteEE:					; Theseus Platinum API compatibility
_Firmware_WriteUCM:
Firmware_WriteUCM:
	mov	R0,AR7					; Backup the IDATA buffer address
	mov	R4,AR5					; Backup counter

Firmware_WriteNVM_Loop:
	mov	A,@R0					; Read the byte from IDATA pinted to by R1
	mov	R5,A					; Place the byte to write into the correct register

	lcall	Firmware_WriteByteUCM			; Call the single byte write to UCM function
							; This function is expecting the target address
							; in R1, R2 & R7 and the data byte to write in R5
	
	mov	A,R7					; Check the return value of the single write byte
	anl	A,#80h					; firmware call, if MSB is set it indicates error
	jnz	Firmware_WriteNVM_Return_Fail		; It will exit the function on error

	inc	R0					; Point to next IDATA buffer location containing data
	inc	DPTR					; Point to next UCM byte to write to

	mov	R3,DPX					; Update the registers the Firmware_WriteByteUCM
	mov	R2,DPH					; function expects the address in
	mov	R1,DPL

	djnz	R4,Firmware_WriteNVM_Loop		; Only continue if there are bytes left to write

Firmware_WriteNVM_Return_Success:
	mov	R7,#0h
	ret



Firmware_WriteNVM_Return_Fail:
	mov	R7,#0FFh
	ret


END
