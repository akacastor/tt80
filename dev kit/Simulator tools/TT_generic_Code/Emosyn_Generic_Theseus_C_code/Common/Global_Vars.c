/******************************************************************************
*
* Name:         Global_Vars.c
* Description:  Contains variables that will be made available across the whole
*               project with the Global_Vars.h header file
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
* $Revision: 1.6 $
* $Author: dhunter $ 
* $Date: 2006/09/07 21:26:00 $
******************************************************************************/


/******************************************************************************
* Header file inclusions
******************************************************************************/
#include "global_vars.h"

/******************************************************************************
* External and local function declarations 
******************************************************************************/


/******************************************************************************
* External variable declarations
******************************************************************************/

uchar idata APDU_CMD[APDU_HEADER_LENGTH];     /* A buffer for the APDU input commands */ 

uchar idata TEMP_BUF[TEMP_BUFFER_SIZE];     /* A Temp buffer to store input parameters */

uchar idata IDLE_MODE;       /* A flag to store the idle mode setting */
uint idata SW1SW2;           /* A variable to store the status word return value */

uchar code *CODE_PTR;        /* A general purpose pointer to CODE space */
uchar xdata *XDATA_PTR;      /* A general purpose pointer to XDATA space */
uchar idata *IDATA_PTR;      /* A general purpose pointer to IDATA space (1 byte) */

uchar idata ucCount;         /* A general purpose counter variable */
char idata cRet_Val_Char;    /* A char variable to hold return value of char functions */
int idata iRet_Val_Int;      /* A int variable to hold the return value of int functions */
uint idata uiTemp_Address;   /* A general purpose variable to hold Address values (2 bytes) */

unsigned long idata ulTemp_Var; /* A general purpose long variable */

uchar xdata IO_Buffer[IO_BUFFER_SIZE]; /* An IO Buffer for DES/AES outputs */

#ifdef EXTENDED_ADDRESSING
uchar far *uc_Fptr;          /* A general purpose far pointer */
uchar idata DPX_Addr;        /* A temporary variable to hold the DPX value of an address */
uchar idata ucByte_To_Write; /* A variable to hold the byte the user wants to write */
#endif

uchar volatile idata Timer0_Int_Count = 0;

