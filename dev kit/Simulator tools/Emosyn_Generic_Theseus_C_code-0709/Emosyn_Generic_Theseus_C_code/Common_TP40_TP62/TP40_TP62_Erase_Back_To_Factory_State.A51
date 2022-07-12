;********************************************************************************************************
;
; Name:		Erase_Back_To_Factory_State.A51
; Description:	Clears all of the EEPROM and UCM back to factory state
; Copyright:	Emosyn Inc. 2005
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
; $Date: 2005/08/30 15:14:55 $
;********************************************************************************************************

$include (Firmware_API_JumpTable.inc)			; External declarations for jumptable library

Public Erase_Back_To_Factory_State, _Erase_Back_To_Factory_State
Public EraseNVM, _EraseNVM

Extrn Code (TheseusPlatinum_EE_MassErase_Bootloader_Safe)

EraseBackToFactoryState_Segment Segment Code
	Rseg EraseBackToFactoryState_Segment

using 0

;********************************************************************************************************
;**+ Erase Back To Factory State
;
; Clears out the EEPROM and the UCM back to factory delivered state.
;
; Calls TheseusPlatinum_EE_MassErase_Bootloader_Safe to erase the EEPROM, copies the MassEraseUCM code 
; segment into RAM, and runs it from here. This is so that when the device returns from the MassEraseUCM
; API, it can go into a forever loop.	
;********************************************************************************************************
;
; Command Syntax
;
; 	E5 30 00 00 00
;
; Inputs
;	None
;
; Outputs
;	None
;
; Example usage : Clears out the EEPROM and the UCM back to factory delivered state.
;
;	To Card			->	E5 30 00 00 00
;	Acknowledge from Card	<-	30
;	Response from Card	<-	90 00
;
;********************************************************************************************************
_EraseNVM:
EraseNVM:
_Erase_Back_To_Factory_State:
Erase_Back_To_Factory_State:
	lcall	TheseusPlatinum_EE_MassErase_Bootloader_Safe	; Erase all of the EEPROM except the bootloader

	MOV	R1,#16h			
	MOV	DPS, #00H
	MOV	DPTR,#Code_To_Go_Into_RAM

Copy_Code_And_Jump_Forever_Loop_To_XRAM_And_Jump_To_It:
	MOV	DPS, #01H
	MOV	DPTR,#0FC00h					; XRAM destination location

Copy_Xram_Code_Loop:          
	mov	DPS, #00H
	movx	A,@DPTR						; Transport_Key_Two_Code_To_Go_Into_XRAM
	inc	DPTR						; Inc DPTR0
	mov	DPS, #01H					; Copy it to XRAM
	movx	@DPTR,A
	inc	DPTR						; Inc DPTR1
	djnz    R1,Copy_Xram_Code_Loop


	;Now copy over the loop forever code. 
	mov	dptr,#0FD00h					; This allows the XRAM code to be upto 256 bytes.
	mov	a,#02h
	movx	@dptr,a						; LJMP
	inc	dptr
	mov	a,#0FDh
	movx	@dptr,a						; FDh
	inc	dptr
	clr	a
	movx	@dptr,a						; 00h

	; Now the erase code is in XRAM....so jump to it
	ljmp	0FC00h						; This will Mass Erase the UCM and go into a Forever loop. 
								; Needs a reset to exit
	; We never return from this....we are in a forever loop.

Code_To_Go_Into_RAM:
	lcall	Firmware_MassEraseUCM				; 3 bytes
	mov	SBUF, #90h					; 3
	jnb	SCON.1, $					; 3
	clr	SCON.1						; 2

	mov	SBUF, #00h					; 3
	jnb	SCON.1, $					; 3
	clr	SCON.1						; 2

	ljmp	0xFD00						; 3. total 22 bytes

end