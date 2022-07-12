;********************************************************************************************************
;
; Name:		TP62_Startup.A51
; Description:	Modified startup code based on Keil's Startup.a51
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
; $Date: 2005/08/09 11:53:42 $
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
XDATASTART	EQU	0H	; the absolute start-address of XDATA memory
XDATALEN	EQU	400H	; the length of XDATA memory in bytes.
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


?C_C51STARTUP	SEGMENT   CODE

?STACK		SEGMENT   IDATA	

		RSEG	?STACK
		DS	15

		EXTRN CODE (?C_START)
		PUBLIC	?C_STARTUP

		CSEG	AT	6800h
?C_STARTUP:	LJMP	STARTUP1

		RSEG	?C_C51STARTUP

STARTUP1:

IF IDATALEN <> 0
		MOV	R0,#IDATALEN - 1
		CLR	A
IDATALOOP:	MOV	@R0,A
		DJNZ	R0,IDATALOOP
ENDIF

IF XDATALEN <> 0
		MOV	DPTR,#XDATASTART
		MOV	R7,#LOW (XDATALEN)
  IF (LOW (XDATALEN)) <> 0
		MOV	R6,#(HIGH XDATALEN) +1
  ELSE
		MOV	R6,#HIGH (XDATALEN)
  ENDIF
		CLR	A
XDATALOOP:	MOVX	@DPTR,A
		INC	DPTR
		DJNZ	R7,XDATALOOP
		DJNZ	R6,XDATALOOP
ENDIF

IF PPAGEENABLE <> 0
		MOV	P2,#PPAGE
ENDIF

IF PDATALEN <> 0
		MOV	R0,#PDATASTART
		MOV	R7,#LOW (PDATALEN)
		CLR	A
PDATALOOP:	MOVX	@R0,A
		INC	R0
		DJNZ	R7,PDATALOOP
ENDIF

IF IBPSTACK <> 0
EXTRN DATA (?C_IBP)

		MOV	?C_IBP,#LOW IBPSTACKTOP
ENDIF

IF XBPSTACK <> 0
EXTRN DATA (?C_XBP)

		MOV	?C_XBP,#HIGH XBPSTACKTOP
		MOV	?C_XBP+1,#LOW XBPSTACKTOP
ENDIF

IF PBPSTACK <> 0
EXTRN DATA (?C_PBP)
		MOV	?C_PBP,#LOW PBPSTACKTOP
ENDIF

		MOV	SP,#?STACK-1
		LJMP	?C_START

		END


