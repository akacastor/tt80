;********************************************************************************************************
; Name:		TT80_Core_Bootloader.a51
; Description:	S Algorithm loader for the TT80
; Copyright:	Emosyn Inc. 2004
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
; $Date: 2007/05/03 22:14:50 $
;********************************************************************************************************



/*

This code is setup to be the basic bootloader. It has links into the Normal loader to do the decryption....
but if its in core bootloader mode then the user doesnt have the option to select decrytion...so we are ok.

*/










$include (Bootloader.inc)

;*******************************************************************************
;       Public Definitions
;*******************************************************************************

Public Core_Bootloader_Entry
Public _Firmware_Set_Clock
Public Mass_Erase_UCM__Bootloader_Safe


Public Change_Divisor_Rate
Public Add_To_Serial_Checksum_Possibly_Decrypt
Public Decrypt_Acc_If_Encryption_Selected
Public Desired_Serial_Checksum_Hi
Public Desired_Serial_Checksum_Lo
Public Get_Byte__Possibly_Decrypt__Add_To_Receive_Checksum

Public Desired_Memory_Value

Public Serial_Checksum_Hi
Public Serial_Checksum_Lo



Public Data_Block_Size


Public Loop_Counter


Public Misc_Buffer

Public Send_SW1_SW2_9000
Public Send_SW1_SW2_Acc_00

Public APDU_CLA
Public APDU_INS
Public APDU_P1
Public APDU_P2
Public APDU_P3
Public SW2

Public Variable_For_Address_Checking
Public Variable_For_Length_Checking


Public SBOX_Offset_Hi
Public SBOX_Offset_Lo
Public Actual_Bulk_CKS_Low
Public Actual_Bulk_CKS_High
Public Encryted_Data




Public Write_Received_And_Possibly_Decrypted_Byte_To_NVM_And_Setup_For_Next_Loop
Public S_Algorithm_Write_Block
Public Core_Bootloader_Get_Command

Public GetChar
Public PutCharParityBit
Public _PutCharParityBit
Public Other_Loader_Present


Extrn code (ISO_Bootloader__Entry_Point)
#ifdef SIMULATION
Extrn code (Translate_Byte_In_Acc)
#endif
dseg at 0x08

Actual_Serial_Checksum_Hi:	ds 1
Actual_Serial_Checksum_Lo:	ds 1
Desired_Serial_Checksum_Hi:	ds 1
Desired_Serial_Checksum_Lo:	ds 1
Desired_Memory_Value:		ds 1



Actual_Memory_Checksum_Hi:	ds 1
Actual_Memory_Checksum_Lo:	ds 1


Serial_Checksum_Hi:		ds 1
Serial_Checksum_Lo:		ds 1

Data_Block_Size:		ds 1
Loop_Counter:			ds 1



APDU_CLA:			ds 1
APDU_INS:			ds 1
APDU_P1:			ds 1
APDU_P2: 			ds 1
APDU_P3:			ds 1


SW2:				ds 1




#ifndef SIMULATION
dseg at 0x30
; This is a memory alocation for the algorithm.
; These variables are used into the 
Already_Used_Upper:		ds 16			; Used in SBOX generation
Already_Used_Lower:		ds 16			; Used in SBOX generation
SBOX_IDATA:			ds 16
Seed_Byte_Upper:		ds 1
Seed_Byte_Lower:		ds 1
#endif
SBOX_Offset_Hi:			ds 1
SBOX_Offset_Lo:			ds 1
#ifndef SIMULATION
SBOX_Offset_Hi_New:		ds 1
SBOX_Offset_Lo_New:		ds 1
#endif
dseg at 0x70

Actual_Bulk_CKS_Low:		ds 1
Actual_Bulk_CKS_High:		ds 1

Variable_For_Address_Checking: 	ds 1
Variable_For_Length_Checking: 	ds 1


IDATA_Variables_Segment segment idata
	rseg IDATA_Variables_Segment

	
Misc_Buffer:			ds 8			; ChipID buffer

;Already_Used_Upper:		ds 16			; Used in SBOX generation
;Already_Used_Lower:		ds 16			; Used in SBOX generation
;SBOX_IDATA:			ds 16
;Seed_Byte_Upper:		ds 1
;Seed_Byte_Lower:		ds 1
;SBOX_Offset_Hi_New:		ds 1
;SBOX_Offset_Lo_New:		ds 1


BIT_Variables_Segment segment bit
	rseg BIT_Variables_Segment
Encryted_Data:			dbit 1


?STACK		SEGMENT   IDATA	

		RSEG	?STACK         
		DS	15




;*******************************************************************************
; Bootloader Start
;*******************************************************************************
?PR?Core_Bootloader_Segment?Core_Bootloader   SEGMENT CODE
	RSEG     ?PR?Core_Bootloader_Segment?Core_Bootloader

using 0


_Core_Bootloader_Entry:
Core_Bootloader_Entry:
	mov	Data_Block_Size,#DEFAULT_BLOCK_SIZE		; Set as 64 byte per block as default
	mov	SP,#?STACK-1
	mov	SW2, #0
							; Shows the part is in the bootloader

	mov	a,#03Bh
	acall	PutCharParityBit


	; Here we check to see if a more advanced bootloader is present.
	; If so jump to it to do the full ATR output.
	mov	dptr,#Other_Loader_Present			; Check to see if a full loader is present
	clr	a
	mov	SW2,a						; Setup SW2 while Acc is 0
	movc	a,@a+dptr
	cjne	a,#0FFh,Sub_Jump_To_Other_Loader_Present	; See if Full Loader is present. If so jump to
								; it to send the full PTS compliant ATR
	
	clr	a						
	acall	PutCharParityBit					; Acc contains 00. No bytes following



Core_Bootloader_Get_Command:
	acall	GetChar
	


Core_Bootloader__S_Algorithm__Write_UCM_Block:
	cjne	a,#CMD_WRITE_UCM,Core_Bootloader__Change_Divisor_Rate
	clr	Encryted_Data					; Not Encrypted by default
		
	acall	S_Algorithm_Write_Block

	sjmp	Core_Bootloader_Get_Command


Sub_Jump_To_Other_Loader_Present:
;	ljmp	Other_Loader_Present
	ljmp	ISO_Bootloader__Entry_Point


Core_Bootloader__Change_Divisor_Rate:                  		; Change Baud Rate
	cjne	a,#CMD_CHANGE_DIVIDOR_RATE,Core_Bootloader__Mass_Erase_UCM
	acall	Change_Divisor_Rate

	sjmp 	Core_Bootloader_Get_Command


Core_Bootloader__Mass_Erase_UCM:                     		; Mass Erase UCM
	cjne	a,#CMD_MASS_ERASE_UCM_BOOTLOADER_SAFE,ISO_Cmd

	acall	Mass_Erase_UCM__Bootloader_Safe

Send_SW1_SW2_9000:
	mov	a,#90h
Send_SW1_SW2_Acc_00:
	acall	PutCharParityBit
	mov	a, SW2
	acall	PutCharParityBit
	mov	SW2,#0
	sjmp	Core_Bootloader_Get_Command


ISO_Cmd:
	cjne	a,#0E5h, Core_Bootloader_Get_Command
	ljmp	ISO_Bootloader__Entry_Point


Mass_Erase_UCM__Bootloader_Safe:


	mov	r6,#00h			
	mov	r7,#0FFh			
	#ifndef SIMULATION
	lcall	Firmware_Erase_UCM_Blocks			; This will erase the all of the UCM
								; between 0400h->9BFFh
#endif
	ret




;Mass_Erase_UCM_Erase_512_Sub_Routine:

;	mov	NvFsmMode,#20h					; 512 Byte UCM Erase
;	movx	@dptr,a						; Select memory type.
;	orl	NvFsmCon,#02h					; Set Start Bit
;	jnb	NvFsmCon.0,$					; Wait for the NvInt flag
;								; This tells us the FSM has completed its task
;	clr	NvFsmCon.0					; Clear the NvInt flag

;	inc	dph
;	inc	dph
;
;	djnz	r0,Mass_Erase_UCM_Erase_512_Sub_Routine
;	ret
















Change_Divisor_Rate:
	acall	GetChar
	mov 	r0,a
	acall	GetChar
	mov	ISOTMR,r0
	mov	ISOTMR,a
	ret





S_Algorithm_Write_Block:
	clr 	A						; Init the checksum variables
	mov 	Serial_Checksum_Lo,a
	mov 	Serial_Checksum_Hi,a
	mov 	Actual_Memory_Checksum_Hi,a
	mov 	Actual_Memory_Checksum_Lo,a
	acall 	Get_Byte__Possibly_Decrypt__Add_To_Receive_Checksum
								; This byte doesnt do anything. But it has been 
								; purposefully left in the algorithm to future proof it.
								; ALL Titanium parts no matter what memory size, now share
								; a single protocol - a 3 byte address.
	mov	DPX, a 	; this byte will always be 0 for 8051 devices

	acall 	Get_Byte__Possibly_Decrypt__Add_To_Receive_Checksum
	mov 	DPH,a

	acall 	Get_Byte__Possibly_Decrypt__Add_To_Receive_Checksum
	mov 	DPL,a

S_Algorithm_Write_Block_Without_Receiving_Address:

	mov	Loop_Counter,Data_Block_Size
	mov	NvFsmMode,#04h					; Byte Write selected in FSM

S_Algorithm_Write_Block_Loop__UCM_Receiving_And_Writing_Loop:
	acall	Write_Received_And_Possibly_Decrypted_Byte_To_NVM_And_Setup_For_Next_Loop
	add 	A,Actual_Memory_Checksum_Lo
	mov 	Actual_Memory_Checksum_Lo,A
	jnc 	Dont_Inc_Actual_Memory_Checksum_Hi
	inc 	Actual_Memory_Checksum_Hi
Dont_Inc_Actual_Memory_Checksum_Hi:

	djnz	Loop_Counter,S_Algorithm_Write_Block_Loop__UCM_Receiving_And_Writing_Loop


Output_Checksums:					
	; ACC already contains Actual_Memory_Checksum_Lo
	mov 	A,Actual_Memory_Checksum_Lo			; Memory Checksum High
	acall	Decrypt_Acc_If_Encryption_Selected		; Uses the decryption SBOX to encrypt
	acall 	PutCharParityBit

	mov 	A,Actual_Memory_Checksum_Hi			; Memory Checksum High
	acall	Decrypt_Acc_If_Encryption_Selected		; Uses the decryption SBOX to encrypt
	acall 	PutCharParityBit

	mov 	A,Serial_Checksum_Lo				; Received Checksum Lo
	acall 	PutCharParityBit
	mov 	A,Serial_Checksum_Hi				; Received Checksum Hi
	acall 	PutCharParityBit
	
	ret







Write_Received_And_Possibly_Decrypted_Byte_To_NVM_And_Setup_For_Next_Loop:

	acall 	Get_Byte__Possibly_Decrypt__Add_To_Receive_Checksum  		
								; Get data byte. Returns byte in Acc
; Need to add in add to desired checksum here
; TESTING - need to make this optional as otherwise it slows down S-Algo


;XQ : this is not necessary. 
;	push	acc
; Make this two sepearte functions - one to get byte/decrypt/add to actual
; and one to just get byte/decrypt	
;	add 	A,Desired_Memory_Checksum_Lo
;	mov 	Desired_Memory_Checksum_Lo,A
;	jnc 	Dont_Inc_Desired_Memory_Checksum_Hi
;	inc 	Desired_Memory_Checksum_Hi
Dont_Inc_Desired_Memory_Checksum_Hi:

;	pop	acc

	movx	@dptr,a						; Select the Memory type / address
	orl	NvFsmCon,#02h					; Set Start Bit
	jnb	NvFsmCon.0,$					; Wait for the NvInt flag
	clr	NvFsmCon.0					; Clear the NvInt flag
	
	movx 	A,@dptr						; Read the byte we just programmed and add it to the memory checksum
	inc	dptr						; As we are using the FSM, we can just Inc DPTR
	ret





Get_Byte__Possibly_Decrypt__Add_To_Receive_Checksum:
	acall	GetChar
Add_To_Serial_Checksum_Possibly_Decrypt:
	mov	R5,A						; Return value in R5
	add 	A,Serial_Checksum_Lo				; Add byte to Rx Checksum
	mov 	Serial_Checksum_Lo,A
	jnc 	Add_To_Serial_Checksum_No_Overflow
	inc 	Serial_Checksum_Hi
Add_To_Serial_Checksum_No_Overflow:
	mov	a,r5
Decrypt_Acc_If_Encryption_Selected:				; We have to optionally do this as the ISO routine is common
	jnb	Encryted_Data, Not_Decrypting_The_Byte		; See if this function is using encrypted data
; TESTING - can more this code into here as its only used once here
#ifdef PRODUCTION
	lcall	Firmware_Translate_Byte_In_Acc	
#else
	lcall	Translate_Byte_In_Acc	
#endif
	
Not_Decrypting_The_Byte:
	
	
	ret

PutCharParityBit:
_PutCharParityBit:

push 	ar7
	mov	R7,a

_PutChar_Value_In_Acc:
PutChar_Value_In_Acc:

	push ar7						; store the char to be sent incase of resend

	mov	SBUF, ar7						; Write ACC directly to the Serial Buffer

	jnb	TI, $						; Only move on when the TI flag goes high
	clr	TI

	mov	a, ISOCON
	jnb	ACC.3, PutChar_Done				; If Serial Control.3 is set after tx complete a resend is required
	
	pop	ar7						; reload char value to be sent
	anl	ISOCON, #0F7h					; Reset RESEND bit
	ljmp	PutChar_Value_In_Acc				; Try again
PutChar_Done:	
	pop	ar7
	pop	ar7
	ret




GetChar:
	jnb	SCON.0, $
	mov	a, SBUF						; Read the byte received
	clr	SCON.0						; Clear the RxDone flag
	ret

#ifdef PRODUCTION	
cseg at 0x9D00
using 0
Other_Loader_Present:
#else
cseg at 0x0500
using 0
Other_Loader_Present:
#endif

end
