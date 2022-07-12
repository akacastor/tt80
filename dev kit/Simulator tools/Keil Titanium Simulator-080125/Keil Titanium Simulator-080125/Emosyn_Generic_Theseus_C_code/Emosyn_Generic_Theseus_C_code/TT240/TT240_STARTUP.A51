;********************************************************************************************************
;
; Name:		TT240_Startup.A51
; Description:	Modified startup code based on Keil's Startup.a51
; Copyright:	Emosyn Inc. 2006
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
; $Date: 2007/03/07 00:54:48 $
;********************************************************************************************************

$include (Firmware_API_JumpTable.inc)				; External declarations for API Jumptable library

;
;------------------------------------------------------------------------------
;
;  User-defined Power-On Initialization of Memory
;
;  With the following EQU statements the initialization of memory
;  at processor reset can be defined:
;
;		; the absolute start-address of IDATA memory is always 0
IDATALEN	EQU	100H	; the length of IDATA memory in bytes.
;
XDATASTART	EQU	3D000H	; the absolute start-address of XDATA memory
XDATALEN	EQU	1000H	; the length of XDATA memory in bytes.
;
PDATASTART	EQU	0H	; the absolute start-address of PDATA memory
PDATALEN	EQU	0H	; the length of PDATA memory in bytes.
;
;  Notes:  The IDATA space overlaps physically the DATA and BIT areas of the
;          8051 CPU. At minimum the memory space occupied from the C51 
;          run-time routines must be set to zero.
;------------------------------------------------------------------------------
; 
;  Reentrant Stack Initilization
;
;  The following EQU statements define the stack pointer for reentrant
;  functions and initialized it:
;
;  Stack Space for reentrant functions in the SMALL model.
IBPSTACK	EQU	0	; set to 1 if small reentrant is used.
IBPSTACKTOP	EQU	0FFH+1	; set top of stack to highest location+1.
; 
;  Stack Space for reentrant functions in the LARGE model.	
XBPSTACK	EQU	0	; set to 1 if large reentrant is used.
XBPSTACKTOP	EQU	0FFFFH+1; set top of stack to highest location+1.
;
;  Stack Space for reentrant functions in the COMPACT model.	
PBPSTACK	EQU	0	; set to 1 if compact reentrant is used.
PBPSTACKTOP	EQU	0FFFFH+1; set top of stack to highest location+1.
;
;------------------------------------------------------------------------------
;
;  Page Definition for Using the Compact Model with 64 KByte xdata RAM
;
;  The following EQU statements define the xdata page used for pdata
;  variables. The EQU PPAGE must conform with the PPAGE control used
;  in the linker invocation.
;
PPAGEENABLE	EQU	0	; set to 1 if pdata object are used.
PPAGE		EQU	0	; define PPAGE number.
;
;------------------------------------------------------------------------------


		NAME	?C_STARTUP


; Declare C_C51STARTUP segment in code memory
?C_C51STARTUP	SEGMENT   CODE

; Declare STACK as a relocateable code segment of 15 bytes
?STACK		SEGMENT   IDATA	
		RSEG	?STACK
		DS	15

; Keil specific definition of main function
		EXTRN CODE (?C_START)

; Declare C_STARTUP in code segment at 0800h 
		PUBLIC	?C_STARTUP

		CSEG	AT	0800h
?C_STARTUP:	LJMP	STARTUP1

; Declare C_C51STARTUP as a reloacateable segment
		RSEG	?C_C51STARTUP

STARTUP1: ; Initialise IDATA, XDATA (SRAM) and PDATA to zero 
; Initialise iData to zero
IF IDATALEN <> 0
		MOV	R0,#IDATALEN - 1; Initialise R0 with the start address (0) + length of IDATA and clear backwards 
		CLR	A		; Clear the accumulator
IDATALOOP:	MOV	@R0,A 		; Copy 0 into the address where R0 is pointing and... 
		DJNZ	R0,IDATALOOP 	; ... decrement and jump to IDATALOOP if R0 is non zero
ENDIF

; Initialise the SRAM to zero
IF XDATALEN <> 0
		MOV	DPTR,#XDATASTART	; Initialise the data pointer with SRAM start address
		MOV	R7,#LOW (XDATALEN)	; Copy the low byte of XDATALEN into R7

; Convert e.g 0x101 to 0x201 to make the upcoming loop work correctly below 0x100
  IF (LOW (XDATALEN)) <> 0
		MOV	R6,#(HIGH XDATALEN) +1
  ELSE
		MOV	R6,#HIGH (XDATALEN)
  ENDIF

		CLR	A			; Clear the accumulator
XDATALOOP:	MOVX	@DPTR,A			; Clear the address pointed to by data pointer
		INC	DPTR			; Increment the data pointer
		DJNZ	R7,XDATALOOP		; Decrement R7 and jump to XDATALOOP if R7 is non zero 
		DJNZ	R6,XDATALOOP		; Decrement R6 and jump to XDATALOOP if R6 is non zero
ENDIF

; Assign the xData page used for pData variables if paged memroy is used 
IF PPAGEENABLE <> 0
		MOV	P2,#PPAGE
ENDIF

; Initialise page memory to zero
IF PDATALEN <> 0
		MOV	R0,#PDATASTART		; Copy PDATASTART into R0
		MOV	R7,#LOW (PDATALEN)	; Copy the low byte of PDATALEN into R7
		CLR	A			; Clear the accumulator
PDATALOOP:	MOVX	@R0,A			; Copy the contents of Accumulator into the address pointed to by R0
		INC	R0			; Increment R0 
		DJNZ	R7,PDATALOOP		; Decrement R7 and jump to PDATALOOP if R7 is non zero
ENDIF

; Initialise the iData stack
IF IBPSTACK <> 0
EXTRN DATA (?C_IBP)

		MOV	?C_IBP,#LOW IBPSTACKTOP
ENDIF

; Initialise the xData stack
IF XBPSTACK <> 0
EXTRN DATA (?C_XBP)

		MOV	?C_XBP,#HIGH XBPSTACKTOP
		MOV	?C_XBP+1,#LOW XBPSTACKTOP
ENDIF

; Initialise the pData stack
IF PBPSTACK <> 0
EXTRN DATA (?C_PBP)
		MOV	?C_PBP,#LOW PBPSTACKTOP
ENDIF

; Load the stack pointer and execute main
		MOV	SP,#?STACK-1
		LJMP	?C_START

		END


