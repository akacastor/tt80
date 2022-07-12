;********************************************************************************************************
;
; Name:		SelectFiDi.a51
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
; $Revision: 1.2 $
; $Author: xavier $ 
; $Date: 2006/07/15 01:14:12 $
;********************************************************************************************************
$include (TT40_Public_SFRs.inc)
;*******************************************************************************
;       Public Definitions
;*******************************************************************************

Public _Select_FiDi
Public Fh
Public Fl
Public D


/******************************************************************************
* Global variables declarations 
******************************************************************************/
IDATA_Variable_FiDi segment data
	rseg IDATA_Variable_FiDi
Fh:		ds 1			; Fh MSB Fi
Fl:			ds 1			; Fh LSB Fi
D:			ds 1			; Di





?PR?Set_PPS?PPS SEGMENT CODE
	RSEG     ?PR?Set_PPS?PPS


/******************************************************************************
*
* Function Name:      Select_FiDi
* Function Inputs:    unsigned char FI : FI parameter according to ISO 7816-3
*		      unsigned char DI : DI parameter according to ISO 7816-3
* Function Outputs:   void
* Description:        Based on FI and DI (refer to ISO7816), this function selects Fi and Di
*	              according to ISO7816-3 7.2.2
******************************************************************************/

_Select_FiDi:
Select_FiDi:


	mov a, r5	
	; if Di> 9, then set to default value
	addc a,	#0F6h
	jnc  	Get_The_Address_Of_Entry
	ljmp endFiDi


Get_The_Address_Of_Entry:

	mov	dptr,#Fi0
	Mov	A,r7				; Get Fi
	Mov	B,#09h				; mov(3 bytes) + mov(3 bytes) + ljmp(3 bytes) = 9 bytes
	Mul	AB				; result is in A
	Addc	A,Dpl				; Add on offset
	jnc	Fi_Select
	inc	Dph	

Fi_Select:
	mov 	dpl, a
	clr a
	Jmp	@A+DPTR


 Fi0:   
	mov 	Fh, #01h	; 372 = 174h default value
	mov	Fl, #074h
	ljmp	Di
 Fi1:   
	mov 	Fh, #01h	; 372 = 174h default value
	mov	Fl, #074h
	ljmp	Di
 Fi2:   
	mov 	Fh, #02h	; 558 = 22Eh
	mov	Fl, #02Eh
    	ljmp	Di
 Fi3:   
	mov 	Fh, #02h	; 744 = 2E8h
	mov	Fl, #0E8h
    	ljmp	Di
 Fi4:   
	mov 	Fh, #04h	; 1116 = 45Ch
	mov	Fl, #05Ch
    	ljmp	Di
 Fi5:   
	mov 	Fh, #05h	; 1488 = 5D0h
	mov	Fl, #0D0h
    	ljmp	Di
 Fi6:   
	mov 	Fh, #07h	; 1860 = 744h
	mov	Fl, #044h
    	ljmp	Di
 Fi7:   
	mov 	Fh, #01h	; 372 = 174h default value
	mov	Fl, #074h
    	ljmp	Di
 Fi8:   
	mov 	Fh, #01h	; 372 = 174h default value
	mov	Fl, #074h
    	ljmp	Di
 Fi9:   
	mov 	Fh, #02h	; 512 = 200h
	mov	Fl, #00h
    	ljmp	Di
 FiA:   
	mov 	Fh, #03h	; 768 = 300h
	mov	Fl, #00h
    	ljmp	Di
 FiB:   
	mov 	Fh, #04h	; 1024 = 400h
	mov	Fl, #00h
    	ljmp	Di
 FiC:   
	mov 	Fh, #06h	; 1536 = 600h
	mov	Fl, #000h
    	ljmp	Di
 FiD:   
	mov 	Fh, #08h	; 2048 = 800h
	mov	Fl, #000h
        

Di:
  
	mov	dptr,#Di0
	Mov	A,r5				; Get Di
	Mov	B,#06h				; mov(3 bytes) + ljmp(3 bytes) = 6 bytes
	Mul	AB				; result is in A
	Addc	a, DPL				; Add on offset
	jnc	Select_DI
	inc	Dph	

 Select_DI: 
	mov 	dpl, a
	clr a
	Jmp	@A+DPTR

 Di0:   
	mov	D, #01h   ; 1 = 1h default value
    	ljmp	endFiDi
 Di1:   
	mov	D, #01h   ; 1 = 1h default value
    	ljmp	endFiDi	
 Di2:   
	mov	D, #02h   ; 2
    	ljmp	endFiDi
 Di3:   
	mov	D, #04h   ; 4
    	ljmp	endFiDi
 Di4:   
	mov	D, #08h   ; 8
    	ljmp	endFiDi
 Di5:   
	mov	D, #010h   ; 16 = 10h
    	ljmp	endFiDi
 Di6:   
	mov	D, #020h   ; 32 = 20h
    	ljmp	endFiDi
 Di7:   
	mov	D, #01h   ; 1 = 1h default value
    	ljmp	endFiDi
 Di8:   
	mov 	D, #0Ch   ; 12 = 0Ch
	ljmp 	endFiDi
 Di9:   
	mov 	D, #014h   ; 20 = 14h
    	

 endFiDi:

ret

END
