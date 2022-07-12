/******************************************************************************
*
* Name:         Theseus_Titanium_Family.h
* Description:  Header file containing SFR declarations for the Theseus Titanium
*               family of smartcards
* Copyright:    Emosyn Inc. 2005
*
* The Example Code herein below is provided "AS IS" and at your sole risk.  
* As to this Code, EMOSYN expressly disclaims all warranties, including, but
* not limited to the implied warranties of merchantability and fitness for a
* particular purpose. EMOSYN does not warrant that the functions contained in
* this code will meet your requirements, or that the operation of the code will
* be accurate, error-free, or non-infringing. No oral or written information or
* advice given by EMOSYN or an authorized representative shall create or affect
* any Warranty.
*******************************************************************************
* $Revision: 1.1 $
* $Author: xavier $ 
* $Date: 2006/07/12 02:40:31 $
******************************************************************************/


/******************************************************************************
* Header file inclusions (#include)
******************************************************************************/


/******************************************************************************
* Definitions (#define)
******************************************************************************/
/******************/
/* BYTE Registers */
/******************/
sfr NVFSMCON       = 0x80;
sfr SP             = 0x81;
sfr DPL            = 0x82;
sfr DPH            = 0x83;
sfr DPL0           = 0x82;
sfr DPH0           = 0x83;
sfr DPL1           = 0x84;
sfr DPH1           = 0x85;
sfr DPS            = 0x86;
sfr PCON           = 0x87;
sfr TCON           = 0x88;
sfr TMOD           = 0x89;
sfr TL0            = 0x8A;
sfr TL1            = 0x8B;
sfr TH0            = 0x8C;
sfr TH1            = 0x8D;

/************************************************************/
/* Registers used for on Extended addressing Titanium parts */
/************************************************************/
sfr DPX            = 0x93;
sfr DPX0           = 0x93;
sfr DPX1           = 0x95;

/***********************************/
/* Registers used for serial comms */
/***********************************/
sfr SCON           = 0x98;
sfr SBUF           = 0x99;

sfr CBSL           = 0xA1;
sfr MPTR           = 0xA2;
sfr IE             = 0xA8;

sfr SECURITYSTATUS = 0xB0;
sfr ISOCON         = 0xB2;
sfr ISOTMR         = 0xB4;
sfr IP             = 0xB8;

sfr PROGIO         = 0xC0;

sfr NvFsmMode      = 0xC9;

sfr PSW            = 0xD0;
sfr SPSW           = 0xD8;

sfr ACC            = 0xE0;
sfr EPSW           = 0xE8;

sfr MPTRX          = 0xEA;

sfr B              = 0xF0;

/****************/
/* Memory Fault */
/****************/
sfr MFCON          = 0xF7;



/*****************/
/* BIT Registers */
/*****************/

/*******/
/* PSW */
/*******/
sbit CY            = PSW^7;
sbit AC            = PSW^6;
sbit F0            = PSW^5;
sbit RS1           = PSW^4;
sbit RS0           = PSW^3;
sbit OV            = PSW^2;

sbit P             = PSW^0; 

/********/
/* SCON */
/********/
sbit TI            = SCON^1;
sbit RI            = SCON^0;

/********/
/* TCON */
/********/
sbit TF1           = TCON^7;
sbit TR1           = TCON^6;
sbit TF0           = TCON^5;
sbit TR0           = TCON^4;
sbit MFLT          = TCON^3;
sbit SINT          = TCON^1;
sbit USINT         = TCON^1;
sbit SSINT         = TCON^0;

/********/
/* EPSW */
/********/
sbit AM            = EPSW^0;
sbit F1            = EPSW^1;


/*************/
/* NVFSMCON */
/*************/
sbit FSM_FINISH    = NVFSMCON^0;
sbit FSM_START     = NVFSMCON^1;
sbit FSM_RESULT    = NVFSMCON^5;


/******************************************************************************
* Public Function Prototypes
******************************************************************************/


/******************************************************************************
* Public Variables
******************************************************************************/
