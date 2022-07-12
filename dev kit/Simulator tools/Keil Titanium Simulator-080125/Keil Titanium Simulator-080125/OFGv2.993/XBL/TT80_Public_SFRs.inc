;********************************************************************************************************
;
; Name:		TT80_Public_SFRs.inc
; Created By:	Mathew Key
; Copyright:	Emosyn Inc. 2004
; 
;********************************************************************************************************
; $Revision: 1.1 $
; $Author: xavier $ 
; $Date: 2006/07/12 02:40:31 $
;********************************************************************************************************
;
; Description:	Include file for the TT80 Public SFR's
;
;********************************************************************************************************

sfr	NvFsmCon		= 0x80			; NV Finite State Machine Control
sfr 	SP			= 0x81
sfr 	DPL			= 0x82
sfr 	DPH			= 0x83
sfr 	DPL0			= 0x82
sfr 	DPH0			= 0x83
sfr 	DPL1			= 0x84
sfr 	DPH1			= 0x85
sfr 	DPS			= 0x86
sfr 	PCON			= 0x87

sfr 	TCON			= 0x88
sfr 	TMOD			= 0x89
sfr 	TL0			= 0x8A
sfr 	TH0			= 0x8C

sfr 	SCON			= 0x98
sfr 	SBUF			= 0x99

sfr 	IE			= 0xA8	; not 0xA0
sfr	MPTR			= 0xA2

sfr 	SECURITYSTATUS		= 0xB0
sfr 	ISOCON			= 0xB2
sfr 	ISOTMR			= 0xB4
sfr	IP			= 0xB8

sfr 	PROGIO			= 0xC0
sfr	NvFsmMode		= 0xC9			; NV Finite State Machine Mode
; extended linear memory SFRs.
sfr	DPX0			= 0x93
sfr	DPX			= 0x93
sfr	DPX1			= 0x95

sfr 	PSW			= 0xD0


sfr 	ACC			= 0xE0

sfr 	B			= 0xF0

/*  SCON  */
sbit TI			= SCON^1;
sbit RI			= SCON^0;

