;********************************************************************************************************
;
; Name:		TT30_Mass_Erase_UCM_Leaving_Bootloader.a51
; Description:	Erase all of the UCM except the bootloader
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
; $Revision: 1.2 $
; $Author: dhunter $ 
; $Date: 2006/10/11 23:05:16 $
;********************************************************************************************************
;
; Command Syntax
;
;		E5 8A 00 00 00
;
; Inputs
;		None
;
; Outputs
;		None
;
; Example usage : Erase all of the UCM except the bootloader
;
;		To Card			->	E5 8A 00 00 00
;		Acknowledge from Card	<-	8A
;		Response from Card	<-	90 00
;
;********************************************************************************************************

;**+ Extrn's and Public's
$include (Firmware_API_JumpTable.inc)			; External declarations for API Jumptable library

Public Mass_Erase_UCM_Leaving_Bootloader, _Mass_Erase_UCM_Leaving_Bootloader


?PR?Mass_Erase_UCM_Leaving_Bootloader?TT30_Mass_Erase_UCM_Leaving_Bootloader SEGMENT CODE
	RSEG     ?PR?Mass_Erase_UCM_Leaving_Bootloader?TT30_Mass_Erase_UCM_Leaving_Bootloader

using 0

_Mass_Erase_UCM_Leaving_Bootloader:
Mass_Erase_UCM_Leaving_Bootloader:

; We need to copy the code to erase the UCM but not the bootloader into XRAM and run it from here.
; This is because if we run from the UCM, at some point we will erase ourselves


XRAM_CODE_LOCATION	equ	7C00h
XRAM_LOOP_FOREVER_ADDR	equ	7D00h

	mov	r1,#30h						; Number of bytes to copy into XRAM
	mov	dps, #00H
	mov	DPTR,#MASS_ERASE_CODE_TO_GO_INTO_XRAM

Copy_Code_And_Jump_Forever_Loop_To_XRAM_And_Jump_To_It:
	mov	dps, #01H
	mov	DPTR,#XRAM_CODE_LOCATION            		; XRAM destination location

Copy_Xram_Code_Loop:          
	mov     dps, #00H
	clr     A
	movc    A,@A+DPTR					; Copy code to Acc
	inc     DPTR						; Inc DPTR0

	mov     dps, #01H					; Copy Acc to XRAM
	movx    @DPTR,A
	inc	DPTR						; Inc DPTR1
	djnz    R1,Copy_Xram_Code_Loop

	;Now copy over the loop forever code. 
	mov	dptr,#XRAM_LOOP_FOREVER_ADDR
	mov	a,#02h
	movx	@dptr,a						; Code = LJMP 	XRAM_LOOP_FOREVER_ADDR
	inc 	dptr
	mov	a,#HIGH(XRAM_LOOP_FOREVER_ADDR)
	movx	@dptr,a
	inc 	dptr
	mov	a,#LOW(XRAM_LOOP_FOREVER_ADDR)
	movx	@dptr,a

	; Disable interrupts, as we're about to erase the ISR's.
	mov	r7, #00h
	call	_Firmware_SetInterruptEnable

	; Now the erase code is in XRAM....so jump to it
	ljmp	XRAM_CODE_LOCATION			;This will Mass Erase the UCM and go into a Forever loop. Needs a reset to exit
	; We never return from this....we are in a forever loop.


MASS_ERASE_CODE_TO_GO_INTO_XRAM:

	mov	r6,#000h
	mov	r7,#0FFh
	lcall	Firmware_EraseUCMBlock				; This will erase the UCM from 0400->77FF
	
	; Now we just have to erase the 256 block 7800->78FF
	mov	dptr,#7800h					; Setup DPTR with start address of the block to erase

	mov	NvFsmMode,#10h					; 256 Byte UCM Erase
	movx	@dptr,a						; Select memory type.
	orl	NvFsmCon,#02h					; Set Start Bit
	jnb	NvFsmCon.0,$					; Wait for the NvInt flag
								; This tells us the FSM has completed its task
	clr	NvFsmCon.0					; Clear the NvInt flag

	mov	SBUF, #90h       				; 3
	jnb	SCON.1, $        				; 3
	clr	SCON.1           				; 2

	mov	SBUF, #00h       				; 3
	jnb	SCON.1, $        				; 3
	clr	SCON.1           				; 2

	ljmp    XRAM_LOOP_FOREVER_ADDR 				; 3 total 22 bytes
end