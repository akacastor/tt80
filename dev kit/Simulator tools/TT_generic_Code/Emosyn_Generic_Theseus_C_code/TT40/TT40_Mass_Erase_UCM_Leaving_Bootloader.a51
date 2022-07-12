;********************************************************************************************************
;
; Name:		TT40_Mass_Erase_UCM_Leaving_Bootloader.a51
; Description:	Erase all of the UCM except the bootloader
; Copyright:	SST 2006
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
; $Author: dhunter $ 
; $Date: 2006/10/10 22:40:18 $
;********************************************************************************************************
;
; Command Syntax
;
;		E5 30 00 00 00
;
; Inputs
;		None
;
; Outputs
;		None
;
; Example usage : Erase all of the UCM except the bootloader
;
;		To Card			->	E5 30 00 00 00
;		Acknowledge from Card	<-	30
;		Response from Card	<-	90 00
;
;********************************************************************************************************

;**+ Extrn's and Public's
$include (Firmware_API_JumpTable.inc)			; External declarations for API Jumptable library


Public Mass_Erase_UCM_Leaving_Bootloader, _Mass_Erase_UCM_Leaving_Bootloader


?PR?Mass_Erase_UCM_Leaving_Bootloader?TT40_Mass_Erase_UCM_Leaving_Bootloader SEGMENT CODE
	RSEG     ?PR?Mass_Erase_UCM_Leaving_Bootloader?TT40_Mass_Erase_UCM_Leaving_Bootloader

using 0

_Mass_Erase_UCM_Leaving_Bootloader:
Mass_Erase_UCM_Leaving_Bootloader:

; We need to copy the code to erase the UCM but not the bootloader into XRAM and run it from here.
; This is because if we run from the UCM, at some point we will erase ourselves

XRAM_CODE_LOCATION	equ	0B100h
XRAM_LOOP_FOREVER_ADDR	equ	0B1F0h

	mov	r1,#32h						; Number of bytes to copy into XRAM
	mov	dps, #00H
	mov	DPTR,#MASS_ERASE_CODE_TO_GO_INTO_XRAM

Copy_Code_And_Jump_Forever_Loop_To_XRAM_And_Jump_To_It:
	mov	dps, #01H
	mov	DPTR,#XRAM_CODE_LOCATION            		;XRAM destination location

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
	clr	IE.7						; IE.7 is EA

	; Now the erase code is in XRAM....so jump to it
	ljmp	XRAM_CODE_LOCATION			;This will Mass Erase the UCM and go into a Forever loop. Needs a reset to exit
	; We never return from this....we are in a forever loop.





MASS_ERASE_CODE_TO_GO_INTO_XRAM:
	mov	r6,#000h					; R6/R7 = 00FFh: Erase blocks 0-7
	mov	r7,#0FFh			
	lcall	Firmware_EraseUCMBlock				; This will erase the all of the UCM except
								; between 9C00h->A3FFh.

								; Erase UCM pages between 9C00h->A0FFh.
	mov     dps, #00H
	mov	dptr,#9C00h					; Setup DPTR with start address of the page to erase
	mov	r0,#5						; Erase 5 x 256 byte pages

	
Mass_Erase_UCM__Bootloader_Safe__Loop:	
	mov	NvFsmMode,#10h					; 256 Byte UCM Erase
	movx	@dptr,a						; Select memory type.
	orl	NvFsmCon,#02h					; Set Start Bit
	jnb	NvFsmCon.0,$					; Wait for the NvInt flag
								; This tells us the FSM has completed its task
	clr	NvFsmCon.0					; Clear the NvInt flag

	inc	dph						; Advance DPTR to next 256 byte page

	djnz	r0,Mass_Erase_UCM__Bootloader_Safe__Loop

	mov	SBUF, #90h
	jnb	TI, $
	clr	TI

	mov	SBUF, #00h
	jnb	TI, $
	clr	TI

	ljmp    XRAM_LOOP_FOREVER_ADDR 


end