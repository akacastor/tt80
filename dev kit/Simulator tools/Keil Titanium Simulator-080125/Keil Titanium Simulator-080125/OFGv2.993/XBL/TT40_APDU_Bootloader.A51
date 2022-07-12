;********************************************************************************************************
;
; Name:		TT80_APDU_Bootloader.a51
; Description:	APDU compatible downloading algorithm
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
; $Date: 2007/05/03 22:15:44 $
;********************************************************************************************************


;*******************************************************************************
;       Includes
;*******************************************************************************
$include (Bootloader.inc)



;*******************************************************************************
;       Public Definitions
;*******************************************************************************
Public ISO_Bootloader__Entry_Point
Public Firmware_Set_key	; the location of this API is set in Bootloader.inc
;*******************************************************************************
;	Extern Definations
;*******************************************************************************
Extrn code (Normal_Bootloader__Send_SW1_SW2_9000)
Extrn code (Normal_Bootloader__Send_SW1_SW2_Acc_00)

Extrn code (GetChar)
Extrn code (PutCharParityBit)
;Extrn code (Load_Key)
Extrn code (Normal_Bootloader__Mass_Erase_UCM__Bootloader_Safe)
Extrn code (Receive_X_Bytes)
Extrn code (Write_Received_And_Possibly_Decrypted_Byte_To_NVM_And_Setup_For_Next_Loop)
Extrn data (Variable_For_Address_Checking)
Extrn code (Normal_Bootloader__Get_Command)
Extrn code (Normal_Bootloader__Got_Command)
Extrn code (Normal_Bootloader__Load_Key_And_Generate_SBOX)

Extrn code (Decrypt_Acc_If_Encryption_Selected)
;Extrn code (_eraseUCMPage)
Extrn code (Add_To_Serial_Checksum_Possibly_Decrypt)
Extrn code (Get_Byte__Possibly_Decrypt__Add_To_Receive_Checksum)

#ifdef SIMULATION
Extrn code (Clear_SBOX_Offset)
Extrn code (_Get_Key_Status)
Extrn code (Translate_Byte_In_Acc)
Extrn code (_Set_Key)
Extrn code (Init_Key_For_Encryption)
#endif

Extrn code (Calculate_Bulk_Memory_Checksum_TT40)
; status of the device: virgin or partially loaded


Extrn data (Desired_Serial_Checksum_Hi)
Extrn data (Desired_Serial_Checksum_Lo)
Extrn data (Variable_For_Length_Checking)
Extrn data (Serial_Checksum_Hi)
Extrn data (Serial_Checksum_Lo)
Extrn data (Desired_Memory_Value)

Extrn data (Loop_Counter)


Extrn data (SW2)



Extrn data (APDU_CLA)
Extrn data (APDU_INS)
Extrn data (APDU_P1)
Extrn data (APDU_P2)
Extrn data (APDU_P3)
Extrn data(Actual_Bulk_CKS_Lo)
Extrn data(Actual_Bulk_CKS_Hi)

Extrn bit (Encryted_Data)


Extrn idata (Misc_Buffer)


Extrn idata (Key_Buffer)


; As we are in an ISO algorithm, we dont need a Serial checksum....as if the serial fails, then the APDU wont execute correctly



IDATA_APDU_BL_Variables_Segment segment data
	rseg IDATA_APDU_BL_Variables_Segment

Initial_Address_Hi:	ds	1
Initial_Address_Lo:	ds	1


?PR?ISO_ALGORITHM_SEGMENT?TT40_APDU_BOOTLOADER   SEGMENT CODE
	RSEG     ?PR?ISO_ALGORITHM_SEGMENT?TT40_APDU_BOOTLOADER

using 0

ISO_Bootloader__Entry_Point:

	mov 	r0,#APDU_INS					; R0 will be indirect pointer to INS - 2nd byte in array
	mov 	r7,#4    					; 4 bytes more to receive
	call	Receive_X_Bytes					; Get the rest of the APDU.

	mov	a,APDU_INS  ; put the instruction into the acc for the lookup table




	
ISO_Write_UCM_Block:

        
	cjne	a,#INS_WRITE_UCM_BLOCK, non_write_UCM_Command  
	mov	a, #00h  ; this will have to be compared to the Get Key status.
	push 	acc
	clr	Encryted_Data
	sjmp 	write_UCM_Command
non_write_UCM_Command:
	ljmp 	ISO_Write_Encrypted_UCM_Block 
write_UCM_Command:


#ifdef SIMULATION
	mov	r7, #01h	; encryption key
	lcall _Get_Key_Status
#else
	mov	r7, #01h	; encryption key
	lcall Firmware_Get_Key_Status
#endif
	pop acc

	cjne 	a, ar7, Data_Loading_Allowed 
	mov	loop_Counter, APDU_P3
	dec 	loop_Counter
	dec 	loop_Counter
	ljmp	Key_Download_Error


Data_Loading_Allowed:
	
	

ISO_Write_UCM_Block_Direct_Entry_Point:
	clr 	A						; Init the checksum variables
	mov 	Desired_Serial_Checksum_Hi,a
	mov 	Desired_Serial_Checksum_Lo,a
	mov 	Serial_Checksum_Hi,a
	mov 	Serial_Checksum_Lo,a
	mov	Desired_Memory_Value,a

	mov	Loop_Counter,APDU_P3

        
	; first byte is the DPS (0 for 8051 devices and high byte address for linear addressing devices
 	; the 2 last bytes are the checksum
	dec	 Loop_Counter
	dec	 Loop_Counter
        dec 	 Loop_Counter

		
write_data:



move_On:	
	mov	a,APDU_P1					; Address Hi
	lcall 	Add_To_Serial_Checksum_Possibly_Decrypt
	mov	DPH,a
;	mov	Initial_Address_Hi, a				; backup address in case of error	
   	
	mov	a,APDU_P2					; Address Lo
	lcall 	Add_To_Serial_Checksum_Possibly_Decrypt
;        mov	Initial_Address_Lo, a				; backup address in case of error
	mov	DPL,a

       	
	mov	NvFsmMode,#04h					; Byte Write selected in FSM


	;************************************************************************;
	;   check address							;
;	;************************************************************************;
;	mov	Variable_For_Length_Checking, Loop_Counter
;	dec	Variable_For_Length_Checking
;	mov	Variable_For_Address_Checking, Initial_Address_Hi
;	clr 	a
;	mov 	a, Initial_Address_Lo
;	add	a, Variable_For_Length_Checking 
;	jnc 	no_address_overflow
;	inc	Variable_For_Address_Checking
;no_address_overflow:
	
;	clr  a
;	cjne a, MovX_Addr_Space_Switch_0_XDATA_1_CODE, Check_Code_Address


	

;Check_xdata_Address:
	; check from 0800 to F600
	; check below 0800
;	mov a, Initial_Address_Hi
;	add a, #0F8h
;	jnc Address_Error
;Low_Xdata_Address_OK_Block1:
;	mov a, Variable_For_Address_Checking
;	add a, #52h
;	jc Check_High_Block

;	sjmp Address_Checking_OK
		
	; check high block
;Check_High_Block:	
;	mov a, Variable_For_Address_Checking
;	add a, #048h
;	jnc Address_Error
;	sjmp Address_Checking_OK

;Check_Code_Address:
;	mov a, Initial_Address_Hi
;	add a, #0F8h
;	jnc Address_Error
;Low_Code_Address_OK:
;	mov a, Variable_For_Address_Checking
;	add a, #0Ah
;	jc Address_Error

;Address_Checking_OK:	

	mov	a,APDU_INS  // echo back the ACK byte
	lcall	PutCharParityBit

	lcall 	GetChar
	lcall 	Add_To_Serial_Checksum_Possibly_Decrypt
	mov	DPX, a 	; this byte will always be 0 for 8051 deivces

ISO_Bootloader__Write_UCM_Block__Receiving_And_Writing_Loop:

	lcall	Write_Received_And_Possibly_Decrypted_Byte_To_NVM_And_Setup_For_Next_Loop
	; serial checksum is in  Serial_Checksum_Hi &  Serial_Checksum_Lo
	; value read from memory is located in a
	; value read from IO port possibly after decryption is located in r5

	jnb	NvFsmCon.5,Memory_Error					; check if writting is successfull
	
	djnz	Loop_Counter,ISO_Bootloader__Write_UCM_Block__Receiving_And_Writing_Loop
	sjmp	Get_Checksum



;Address_Error:

;	mov	a,APDU_INS  // echo back the ACK byte
;	lcall	PutCharParityBit
;	inc Loop_Counter ; increase loop counter as it will be decreased after.
;	; SW1SW2:  checksum error
	; this SW1SW2 can be overwritten by a serial checksum error
;	mov	a, #06Ah
;	push 	acc
;	mov	SW2, #82h
;	inc     Loop_Counter

;	sjmp 	Process_Error_code


Error_In_Checksums:

	mov 	a, #06Ah
	mov	SW2,#080h
	push 	acc
	Sjmp 	Process_Fault_Status_Word


Memory_Error:


	; SW1SW2:  checksum error
	; this SW1SW2 can be overwritten by a serial checksum error
	mov	a, #06Ah
	push 	acc
	mov	SW2, #81h
	
	sjmp 	Process_Error_code

Key_Download_Error:
	mov	a,APDU_INS  // echo back the ACK byte
	lcall	PutCharParityBit

	; SW1SW2:  checksum error
	; this SW1SW2 can be overwritten by a serial checksum error
	mov	a, #06Ah
	push 	acc
	mov	SW2, #84h
	; now receive the complete data field
	sjmp 	receive_remaining_Data_Memory_Data

Process_Error_code:
	; receive the rest of the command. The byte written with an error
	;  has already been receive and must be decreased from the counter.

	dec 	Loop_Counter
receive_remaining_Data_Memory_Data:	
	mov 	a, Loop_Counter	
	jz 	receive_CKS_Memory_Error

	lcall 	GetChar
	djnz	Loop_Counter,receive_remaining_Data_Memory_Data

receive_CKS_Memory_Error:
	; receive the 2 checksum bytes but don't do anything with them as there is a memory error
	lcall 	GetChar
	lcall 	GetChar
Process_Fault_Status_Word:

	; erase the first page of memory to ensure that it is always possible to recover the device
	mov r6, #04h
	mov r7, #00h
	lcall Firmware_Erase_Page_UCM	

		
	pop 	acc


	ljmp 	Normal_Bootloader__Send_SW1_SW2_Acc_00		; TESTING - change to 90 FF



Get_Checksum:
	; get checksum value from IO

	lcall 	GetChar
		
	mov	Desired_Serial_Checksum_Hi, a

	lcall 	GetChar

	mov	Desired_Serial_Checksum_Lo, a

	mov	a,Serial_Checksum_Hi			; Compare Desired Checksum with Actual checksum
	cjne	a,Desired_Serial_Checksum_Hi, Error_In_Checksums; If there is a difference then return 90FF

	mov	a,Serial_Checksum_Lo
	cjne	a,Desired_Serial_Checksum_Lo, Error_In_Checksums


	ljmp	Normal_Bootloader__Send_SW1_SW2_9000




ISO_Write_Encrypted_UCM_Block:
	cjne	a,#INS_WRITE_UCM_BLOCK_ENCRYPTED, ISO_Load_Key	; Left as 0xFF so can be patched

		; check device status 

	mov	a, #0FFh  ; this will have to be compared to the Get Key status.
	push acc

	setb	Encryted_Data
	ljmp	write_UCM_Command
ISO_Load_Key:

	cjne	a,#INS_LOAD_KEY, jump_To_Mass_Erase 
	sjmp Load_Key_CMD
jump_To_Mass_Erase:
	ljmp ISO_Mass_Erase_UCM

Load_Key_CMD:	
	clr a
	mov	Serial_Checksum_Hi, a
	mov	Serial_Checksum_Lo, a

	; move Data Length into r0 to save APDU_P3
	mov r0, APDU_P3
	mov 	a, APDU_P1
	add 	A,Serial_Checksum_Lo				; Add byte to Rx Checksum
	mov 	Serial_Checksum_Lo,A
	jnc 	Add_Key_Byte_To_Serial_Checksum_No_Overflow
	inc 	Serial_Checksum_Hi
Add_Key_Byte_To_Serial_Checksum_No_Overflow:
	
	mov 	a, APDU_P2
	add 	A,Serial_Checksum_Lo				; Add byte to Rx Checksum
	mov 	Serial_Checksum_Lo,A
	jnc 	Add_Key_Byte_To_Serial_Checksum_No_Overflow1
	inc 	Serial_Checksum_Hi
Add_Key_Byte_To_Serial_Checksum_No_Overflow1:

	mov	a,APDU_INS  // echo back the ACK byte

	lcall	PutCharParityBit

	; receive the key. Length can be 08 or 0A
	mov	R1, #Key_Buffer
	Receive_The_Key:
	lcall GetChar
	mov	@R1, a
	add 	A,Serial_Checksum_Lo				; Add byte to Rx Checksum
	mov 	Serial_Checksum_Lo,A
	jnc 	Add_Key_Byte_To_Serial_Checksum_No_Overflow2
	inc 	Serial_Checksum_Hi
Add_Key_Byte_To_Serial_Checksum_No_Overflow2:

	dec r0
	mov a, r0
	inc r1
	cjne  a, #02h, Receive_The_Key    


Receive_The_Key_Checksum:
	; receive the checksum hi
	lcall	GetChar
	cjne	a,Serial_Checksum_Hi, Checksum_error_Byte0	; If chksum byte1 is wrong get byte2 but ignore it
	lcall	GetChar
	cjne	a,Serial_Checksum_Lo, Checksum_error_Byte1      ; If chksum byte2 is wrong jump to error code
	ljmp	No_Checksum_Error				; If both chksums are correct jump to key status checking

Checksum_error_Byte0:
	lcall	GetChar						; Chksum byte1 wrong so get byte2
Checksum_error_Byte1:

	mov	a, #06Ah
	mov	SW2, #80h
	ljmp 	Normal_Bootloader__Send_SW1_SW2_Acc_00		

No_Checksum_Error:
/******************************************************************************/
#ifdef PRODUCTION        	
	; load r4r5 as parameter passed into Firmware_Set_Key
	mov	r5, #Key_Buffer
	
	mov a, APDU_P3
	cjne a, #012h, Load_Transport_Key

Load_Encryption_Key:
	mov r7, #01h
	lcall Firmware_Set_Key
	push ar7
	lcall	Firmware_Init_Key_For_Encryption
	pop ar7
	sjmp Key_Set	
Load_Transport_Key:

	mov r7, #00h
	lcall Firmware_Set_Key
Key_Set:
#else

	; load r4r5 as parameter passed into Firmware_Set_Key
	mov	r5, #Key_Buffer
	
	mov a, APDU_P3
	cjne a, #012h, Load_Transport_Key

Load_Encryption_Key:
	mov r7, #01h
	lcall _Set_Key
	push ar7
	lcall	Init_Key_For_Encryption
	pop ar7
sjmp Key_Set
Load_Transport_Key:

	mov r7, #00h
	lcall _Set_Key
Key_Set:
#endif


	mov	a, r7
	jnz Key_Loading_Not_Successfull
	ljmp	Normal_Bootloader__Send_SW1_SW2_9000

	; send Status word: 0x6A86


Key_Loading_Not_Successfull:
mov a, r7
cjne	a, #0AAh, Key_Error
mov a, #06Ah
mov SW2, #084h
ljmp 	Normal_Bootloader__Send_SW1_SW2_Acc_00		

Key_Error:
mov a, #06Ah
mov SW2, #082h
ljmp 	Normal_Bootloader__Send_SW1_SW2_Acc_00		






ISO_Mass_Erase_UCM:
	cjne	a,#INS_MASS_ERASE_UCM_BOOTLOADER_SAFE,ISO_Get_Chip_ID

#ifdef DEBUG
	mov	a,APDU_INS  // echo back the ACK byte
	lcall	PutCharParityBit
#endif

	ljmp	Normal_Bootloader__Mass_Erase_UCM__Bootloader_Safe			
								; This does the 90 00

ISO_Get_Chip_ID:
	cjne	a,#INS_GET_CHIP_ID,ISO_Checksum_Bulk_Memory_Code	
	mov	a,APDU_INS  // echo back the ACK byte
	lcall	PutCharParityBit


	mov	r7,#Misc_Buffer					; Set up the buffer
	lcall	Firmware_Get_Chip_ID
	mov	r1,#8						; 8 bytes in ID
	mov	r0,#Misc_Buffer					; Reset the buffer
Get_Chip_ID__Loop:
	mov	a,@r0						; Get the value
	lcall	PutCharParityBit						; Send to reaader
	inc	r0						; Point to next
	djnz	r1,Get_Chip_ID__Loop
	ljmp	Normal_Bootloader__Send_SW1_SW2_9000

ISO_Checksum_Bulk_Memory_Code:

	cjne	a,#INS_BULK_MEMORY_CHECKSUM_CODE,ISO_Change_Division_Rate

	
#ifdef DEBUG
	mov	a,APDU_INS  // echo back the ACK byte
	lcall	PutCharParityBit
#endif
	lcall Calculate_Bulk_Memory_Checksum_TT40


	mov a, Actual_Bulk_CKS_Hi
	cjne a, APDU_P1, Bulk_Memory_Error

	; compare MSB
	mov a, Actual_Bulk_CKS_Lo
	cjne a, APDU_P2, Bulk_Memory_Error

        ljmp	Normal_Bootloader__Send_SW1_SW2_9000

Bulk_Memory_Error:



; send Status word: 0x6A86
mov a, #06Ah
mov SW2, #086h
ljmp 	Normal_Bootloader__Send_SW1_SW2_Acc_00		





ISO_Change_Division_Rate:

	cjne	a,#CMD_CHANGE_DIVIDOR_RATE,ISO_Set_Clock
#ifdef DEBUG
	mov	a,APDU_INS  // echo back the ACK byte
	lcall	PutCharParityBit
#endif


	;// check the P1P2 is coded on 11  bits
	mov a, APDU_P1;
	;// mask the 3 last bits:

	mov a, #090h
	lcall PutCharParityBit
	mov a, #00h
	lcall PutCharParityBit

	mov r0, APDU_P1
	/* Load ISOTMR SFR with low part of desired value */
	mov a, APDU_P2
	mov ISOTMR, r0
	mov ISOTMR, a



	ljmp	Normal_Bootloader__Get_Command

ISO_Set_Clock:
	; change internal clock value. Refer to PRFG for allowed values
#ifdef DEBUG1
	cjne	a,#INS_SET_CLOCK,ISO_Read_UCM_Page
#else
	cjne	a,#INS_SET_CLOCK,APDU_Not_Present
#endif

#ifdef DEBUG
	mov	a,APDU_INS  // echo back the ACK byte
	lcall	PutCharParityBit
#endif


	mov r7, #00h
	mov r5, #00h
	mov r3, APDU_P1

	lcall Firmware_Set_Clock
	
	ljmp 	Normal_Bootloader__Send_SW1_SW2_9000

#ifdef DEBUG1

ISO_Read_UCM_Page:
	cjne	a,#INS_Read_UCM_Page,APDU_Not_Present
        
	
read_UCM_Page:
	mov	NvFsmMode,#04h					; Byte Write selected in FSM

	mov	a,APDU_INS  // echo back the ACK byte
	lcall	PutCharParityBit


   
	mov	Loop_Counter, #00h  ; loop counter for 100


	mov 	dph, APDU_P1
	mov	dpl, APDU_P2

Read_Page_Loop:
	clr 	a
	movx 	A,@dptr						; Read the byte we just programmed and add it to the memory checksum
	lcall	PutCharParityBit					; Send to reaader
	inc 	dptr
	djnz	Loop_Counter, Read_Page_Loop


ljmp 	Normal_Bootloader__Send_SW1_SW2_9000
	
#endif



APDU_Not_Present:
	mov	A,#06Bh						; #INS_Not_Supported XQ: value to verify
	ljmp	Normal_Bootloader__Send_SW1_SW2_Acc_00








end
