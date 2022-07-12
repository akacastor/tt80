/******************************************************************************
*
* Name:         XDATA_Memory_Dump_Extended_Addressing.c
* Description:  Contains function to output data from XDATA space
* Copyright:    Emosyn Inc. 2006
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
* $Revision: 1.2 $
* $Author: chin $ 
* $Date: 2006/03/08 18:46:13 $
******************************************************************************/


/******************************************************************************
* Header file inclusions
******************************************************************************/
#include "Firmware_API_JumpTable.h"
#include "Emosyn_Helper_Functions.h"

#include <absacc.h>    /* Contains macro for FVAR and FCVAR */


/******************************************************************************
* External and local function declarations 
******************************************************************************/


/******************************************************************************
* External variable declarations
******************************************************************************/


/******************************************************************************
*
* Function Name:      XDATA_Memory_Dump_Extended_Addressing
* Function Inputs:    void
* Function Outputs:   uint SW1SW2_OK  9000h
* Description:        
*
* APDU Syntax:        E5 7E PARA1 PARA2 PARA3
* APDU Inputs:        PARA1  High byte of the CODE address space of data
*                     PARA2  Low byte of the CODE address space of data
                      PARA3  Number of bytes to output
* APDU Outputs:       (PARA3) number of XDATA data bytes
*
* Example usage:      Output 67h bytes starting from address 12345h in XDATA space
*                        (E5 B2 01 00 00) - Load DPX byte (This has to be performed first)
* To Card             ->  E5 7E 23 45 67
* ACK from Card       <-  7E
* Data from Card      ->  Byte1 Byte2 Byte3...ByteX
* Response from Card  <-  90 00
*
******************************************************************************/
uint XDATA_Memory_Dump_Extended_Addressing (void)
{
    /* Keil uses 0x01-0x7F to represent DPX values in XDATA space for */
    /* X:0x00:0000-X:0x7E:FFFF (See http://www.keil.com/support/docs/2226.htm) */
    
    /* Have to use a long variable to hold the address as you */
    /* cannot perform arithmetic operations on far pointers */
    /* See "http://www.keil.com/support/man/docs/c51/c51_le_far.htm" */
    /* Also see "http://www.keil.com/support/docs/2276.htm" */

    /* Convert the seperate address parameters into a long */
	IDATA_PTR = (uchar*)&ulTemp_Var;
    *(IDATA_PTR++) = 0x00;
    *(IDATA_PTR++) = DPX_Addr;
    *(IDATA_PTR++) = PARA1;
    *(IDATA_PTR++) = PARA2;

    /* A DO-WHILE loop enables 256 bytes to be sent */
    /* User needs to set PARA3 = 00 for 256 byte output */
    do
    {
          /* To access memory above 64K in C for CODE space use the FCVAR macro */
          /* See "http://www.keil.com/support/docs/1947.htm" */
          /* Also see "http://www.keil.com/support/docs/2276.htm" */
          PutChar (FVAR (char, ulTemp_Var++));

    } while ((--PARA3) != 0);   /* Output byte until counter is zero */

    return SW1SW2_OK;

} /* End of function */
