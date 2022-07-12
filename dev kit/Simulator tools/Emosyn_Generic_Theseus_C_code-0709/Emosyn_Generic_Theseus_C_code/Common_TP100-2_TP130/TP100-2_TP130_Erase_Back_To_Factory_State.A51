;********************************************************************************************************
;
; Name:		TP100-2_TP130_Erase_Back_To_Factory_State.A51
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
; $Revision: 1.2 $
; $Author: chin $ 
; $Date: 2005/08/31 15:57:04 $
;********************************************************************************************************
;
; Command Syntax
;
;       E5 30 00 00 00
;
; Inputs
;       None	
;
; Outputs
;       None
;
; Example usage : Mass Erase the EEPROM (leaving Bootloader) and Mass Erase the UCM. Needs a reset to exit
;
;       To Card                 -> E5 30 00 00 00
;       Acknowledge from Card   <- 30
;       Response from Card      <- 90 00
;
;********************************************************************************************************

;**+ Extrn's and Public's
$include (Firmware_API_JumpTable.inc)			; External declarations for jumptable library

Public Erase_Back_To_Factory_State, _Erase_Back_To_Factory_State
Public EraseNVM, _EraseNVM

Extrn code (Mass_Erase_EE_Leaving_Bootloader)


MMUSettings segment IDATA
	rseg MMUSettings
	PADDR:				ds 1		;Physical Address
	LADDR:				ds 1		;Logical Address
	PSZ:				ds 1		;Size of Partition
	PARCFG:				ds 1 		;Partition configuration
	

?PR?Erase_Back_To_Factory_State?TP100_TP130_Erase_Back_To_Factory_State	SEGMENT CODE
	RSEG     ?PR?Erase_Back_To_Factory_State?TP100_TP130_Erase_Back_To_Factory_State

using 0


EraseNVM:
_EraseNVM:
_Erase_Back_To_Factory_State:
Erase_Back_To_Factory_State:


; Calls Mass_Erase_EE_Leaving_Bootloader to erase the EEPROM, copies the MassEraseUCM code segment into 
; RAM, and runs it from here. This is so that when the device returns from the MassEraseUCM API, it can 
; go into a forever loop.	

	lcall	Mass_Erase_EE_Leaving_Bootloader	; Erase all of the EEPROM except the bootloader


; Create a RAM partition so we can copy the SW1SW2 code into it. We will Mass Erase the UCM...so there is not way to send 
; the 90 00 from CODE

; Setup Partition 0
; 1K RAM dual mapped
; Physical address 	= 0000h
; Logical address	= 4000h-43FFh
; Size			= 1K
; Partition Config	= Dual Mapped. No access restriction. RAM. Active in Kernal Mode

	mov	r0,#low (MMUSettings)
	mov	@r0,#00h				;Physical address = 0000h
	inc	r0
	mov 	@r0,#40h				;Logical Address = 4000h
	inc	r0
	mov	@r0,#03h				;Size = (1k/256)-1
	inc	r0
	mov	@r0,#6Dh				;Parcfg = 0110     10     01
							      ;Unified R/W RAM  Kernal Mode
	MOV  	R5,#LOW (MMUSettings)
	MOV  	R7,#0					;Partition 0
	LCALL	Firmware_SetMMU


;Copy code into SRAM

	MOV	R1,#16h			
	MOV	DPS, #00H
	MOV	DPTR,#Code_To_Go_Into_RAM

Copy_Code_And_Jump_Forever_Loop_To_XRAM_And_Jump_To_It:
	MOV	DPS, #01H
	MOV	DPTR,#04000h					; XRAM destination location

Copy_Xram_Code_Loop:          
	mov	DPS, #00H
	clr	a
	movc	a,@a+dptr					; Read byte that goes into XRAM
	inc	DPTR						; Inc DPTR0
	mov	DPS, #01H					; Copy it to XRAM
	movx	@DPTR,A
	inc	DPTR						; Inc DPTR1
	djnz    R1,Copy_Xram_Code_Loop


	;Now copy over the loop forever code. 
	mov	dptr,#04100h
	mov	a,#02h
	movx	@dptr,a						; LJMP
	inc	dptr
	mov	a,#041h
	movx	@dptr,a						; FDh
	inc	dptr
	clr	a
	movx	@dptr,a						; 00h

	; Now the erase code is in XRAM....so jump to it
	ljmp	04000h						; This will Mass Erase the UCM and go into a Forever loop. 
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

	ljmp	0x4100						; 3. total 22 bytes

end