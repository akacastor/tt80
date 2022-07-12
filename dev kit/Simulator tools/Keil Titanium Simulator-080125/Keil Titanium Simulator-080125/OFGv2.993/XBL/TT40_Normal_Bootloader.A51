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
; $Date: 2007/05/03 22:15:20 $
;********************************************************************************************************

$include (Bootloader.inc)

;*******************************************************************************
;       Public Definitions
;*******************************************************************************

Public Normal_Bootloader__Get_Command
Public Normal_Bootloader__Got_Command

Public Normal_Bootloader__Send_SW1_SW2_9000
Public Normal_Bootloader__Send_SW1_SW2_Acc_00
Public Normal_Bootloader__Load_Key_And_Generate_SBOX

Public Receive_X_Bytes

Public Normal_Bootloader__Mass_Erase_UCM__Bootloader_Safe

Public _Firmware_Init_Key_For_Encryption
Public _Firmware_Get_Key_Status
Public _Firmware_Set_Key
Extrn code (SendATR)
Extrn code (S_Algorithm_Write_Block)

Extrn code (Mass_Erase_UCM__Bootloader_Safe)


Extrn data (Data_Block_Size)
Extrn data (Actual_Bulk_CKS_Low)
Extrn data (Actual_Bulk_CKS_High)
Extrn data (Loop_Counter)
Extrn idata (Key_Buffer)


Extrn code (_Set_PPS)
Extrn code (ISO_Bootloader__Entry_Point)
Extrn code (GetChar)
Extrn code (PutCharParityBit)
Extrn code (Change_Divisor_Rate)

#ifdef SIMULATION
Extrn code (_Get_Key_Status)
Extrn code (Clear_SBOX_Offset)
Extrn code (Init_Key_For_Encryption)
Extrn code (_Set_key)
#endif



Extrn data (SW2)

Extrn data (APDU_CLA)
Extrn data (APDU_INS)
Extrn data (APDU_P1)
Extrn data (APDU_P2)
Extrn data (APDU_P3)
Extrn bit (Encryted_Data)


Extrn idata (Misc_Buffer)





;*******************************************************************************
; Bootloader Start
;*******************************************************************************
?PR?NORMAL_BOOTLOADER_SEGMENT?NORMAL_BOOTLOADER   SEGMENT CODE
	RSEG     ?PR?NORMAL_BOOTLOADER_SEGMENT?NORMAL_BOOTLOADER

using 0

#ifdef PRODUCTION
	lcall	Firmware_Clear_SBOX_Offset
#else
	lcall	Clear_SBOX_Offset

#endif
	mov	r7, #01h	; encryption key
#ifdef PRODUCTION
	lcall	Firmware_Get_Key_Status
#else
	lcall	_Get_Key_Status

#endif
	mov	a,r7
	cjne	a, #00h, Send_ATR_Normal_BL  ;FF: key not already loaded
	; here the key is loaded 


#ifdef PRODUCTION
	lcall Firmware_Init_Key_For_Encryption
#else
	lcall Init_Key_For_Encryption

#endif

Send_ATR_Normal_BL:
	lcall SendATR


	; the clock has not been set to 60Mhz yet:
	
	


	
	lcall 	GetChar						; Get the first byte...as we need to check for a PPS

; Non ISO readers will ignore the PTS request if they dont support it.


;**+ Is this a PTS
Is_This_A_PTS:

	cjne	a,#0FFh,Normal_Bootloader__Got_Command		; Is this the first byte of a PTS ?

; Set PPS 



RECEIVE_PPS:


        // get the last 3 bytes of the PPS
	lcall	GetChar  
	mov	APDU_P1,A
	lcall	GetChar  
	mov	APDU_P2,A
	lcall	GetChar
	mov	APDU_P3,A

	mov	r7,APDU_P2  ; move FiDi in first parameter of function call
	lcall _Set_PPS



Normal_Bootloader__Get_Command:
	lcall	GetChar
	


; check that the class is correct
; correct values: 


; XQ: this list has to be updated
;CLA_EMOSYN					equ	0E5h
;CMD_WRITE_UCM					equ	050h
;CMD_CHANGE_DIVIDOR_RATE			equ	012h
;CMD_MASS_ERASE_UCM_BOOTLOADER_SAFE		equ	030h
;CMD_CHANGE_BLOCK_SIZE				equ	051h
;CMD_CHANGE_TO_60MHZ				equ 	055h
;CMD_WRITE_UCM_ENCRYPTED			equ	060h
;CMD_RECEIVE_KEY				equ	065h
;CMD_SET_CLR_CD_BIT_IN_NVFSMCON			equ	059h

       


Normal_Bootloader__Got_Command:					; The ISO loader jumps here after sending the ATR
	;Now decide what command it is.



ISO_Cmd:
	cjne	a,#0E5h, Normal_Bootloader__S_Algorithm__Write_NVM_Block_Max256
	ljmp	ISO_Bootloader__Entry_Point


Normal_Bootloader__S_Algorithm__Write_NVM_Block_Max256:
	cjne	a,#CMD_WRITE_UCM,Normal_Bootloader__S_Algorithm__Write_Encrypted_NVM_Block_Max256

	; check if it is possible to load some data in clear
	; it is not possible if an encryption key is loaded.
	mov	r7, #01h	; encryption key = 01
#ifdef SIMULATION
	lcall _Get_Key_Status
#else
	lcall Firmware_Get_Key_Status

#endif
	mov a, r7	; 00: key loaded
	cjne 	a, #01h, Load_UCM_OK
	
	mov	loop_Counter, Data_Block_Size
	; The loading of cards has not been allowed because a key is downloaded.                                                      
	lcall 	GetChar
	lcall 	GetChar
	lcall 	GetChar			
receive_all_bytes:
	lcall 	GetChar			
	djnz	Data_Block_Size,receive_all_bytes
	clr 	a 
	
	lcall 	PutCharParityBit
	lcall 	PutCharParityBit
	lcall 	PutCharParityBit
	lcall 	PutCharParityBit



Load_UCM_OK:
	clr	Encryted_Data					; Not Encrypted by default

S_Algorithm_Direct_Entry_Point:
	lcall	S_Algorithm_Write_Block
	sjmp	Normal_Bootloader__Get_Command



	
Normal_Bootloader__S_Algorithm__Write_Encrypted_NVM_Block_Max256:							; Empty command. Used to give patchability
	cjne	a,#CMD_WRITE_UCM_ENCRYPTED, Normal_Bootloader__Receive_Key		; Left as 0xFF so can be patched
	setb	Encryted_Data
	ajmp	S_Algorithm_Direct_Entry_Point



Normal_Bootloader__Receive_Key:
	cjne	a,#CMD_RECEIVE_KEY,Normal_Bootloader__Change_Divisor_Rate
Normal_Bootloader__Load_Key_And_Generate_SBOX:

	
	; receive the 10h bytes of the key and store it into the Xram 
	mov	r1, #010h
	mov	r0, #Key_Buffer
Load_Key_For_Normal_BL:	
	lcall	GetChar
	mov	@r0, a
	inc 	r0
	djnz	r1, Load_Key_For_Normal_BL




; This piece of code should be implemented but there are some timing issues to 
; fix in the simulator first.
	mov	r7, #01h	; encryption key
#ifdef PRODUCTION
	lcall	Firmware_Get_Key_Status
#else
	lcall	_Get_Key_Status
#endif
	mov	a,r7
	cjne	a, #0FFh, Exit_With_Error  ;00: key already loaded
					   ; here FF: key not loaded



	mov	r7, #01h	; encryption key selected.
	mov	R5, #Key_Buffer
	#ifdef PRODUCTION
	lcall 	Firmware_Set_key
	lcall	Firmware_Init_Key_For_Encryption

	#else
	lcall 	_Set_key
	lcall	Init_Key_For_Encryption

	#endif
	; receive the 0x10 bytes of the key.
	sjmp	Normal_Bootloader__Send_SW1_SW2_9000
		

Exit_With_Error:
	mov	a, #06Ah	; command not available as key already downloaded.
	mov	SW2, #082
	sjmp 	Normal_Bootloader__Send_SW1_SW2_Acc_00		


Normal_Bootloader__Change_Divisor_Rate:                  	; Change Baud Rate
	cjne	a,#CMD_CHANGE_DIVIDOR_RATE,Normal_Bootloader__Change_To_60_MHz
	lcall	Change_Divisor_Rate
	sjmp 	Normal_Bootloader__Get_Command


	
Normal_Bootloader__Change_To_60_MHz:
	cjne	a,#CMD_CHANGE_TO_60MHZ,Normal_Bootloader__Change_Data_Block_Size

	;Change the Clock source to the internal oscillator running at 60 MHz
	clr	a
	mov	r7,a
	mov	r5,a
      	mov	R3,#0ffh					; 60 MHz
	lcall	Firmware_Set_Clock

	ljmp	Normal_Bootloader__Get_Command



Normal_Bootloader__Change_Data_Block_Size:
	cjne	a,#CMD_CHANGE_BLOCK_SIZE,Normal_Bootloader__Mass_Erase_UCM
	lcall	GetChar
	mov	Data_Block_Size,a
	ljmp	Normal_Bootloader__Get_Command



Normal_Bootloader__Mass_Erase_UCM:                     		; Mass Erase UCM
	cjne	a,#CMD_MASS_ERASE_UCM_BOOTLOADER_SAFE,Wrong_Class
Normal_Bootloader__Mass_Erase_UCM__Bootloader_Safe:

	lcall	Mass_Erase_UCM__Bootloader_Safe



Normal_Bootloader__Send_SW1_SW2_9000:
	mov	a,#90h
	
Normal_Bootloader__Send_SW1_SW2_Acc_00:
	lcall	PutCharParityBit
	mov	a,SW2	
	lcall	PutCharParityBit
	
	mov	SW2,#0						; Reset SW2

	ljmp	Normal_Bootloader__Get_Command


Wrong_Class:  ; return class error 0x6E00

	lcall GetChar
	lcall GetChar
	lcall GetChar
	lcall GetChar
	clr	a
	mov	SW2, a
	mov 	a, #06Eh
	ajmp  Normal_Bootloader__Send_SW1_SW2_Acc_00













?PR?Receive_X_Bytes?TT40_Normal_Bootloader   SEGMENT CODE
	RSEG     ?PR?Receive_X_Bytes?TT40_Normal_Bootloader



Receive_X_Bytes:
; R7 is number of bytes;
; R0 is IDATA pointer to store them in
	lcall	GetChar

	mov	@r0,a
	inc	a
	inc	r0
	djnz 	r7,Receive_X_Bytes
	ret







end
