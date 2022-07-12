/******************************************************************************
*
* Name:         Write_To_IRAM.c
* Description:  Contains function to write input data to IDATA RAM
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
* $Author: chin $ 
* $Date: 2006/03/08 16:21:59 $
******************************************************************************/


/******************************************************************************
* Header file inclusions
******************************************************************************/
#include "Firmware_API_JumpTable.h"
#include "Emosyn_Helper_Functions.h"


/******************************************************************************
* External and local function declarations 
******************************************************************************/


/******************************************************************************
* External variable declarations
******************************************************************************/


/******************************************************************************
*
* Function Name:      Write_To_IRAM
* Function Inputs:    void
* Function Outputs:   uint SW1SW2_OK  9000h
* Description:        Writes input data to IDATA
*
* APDU Syntax:        E5 8C 00 PARA2 PARA3
*                     PARA2  IRAM start address to write to
*                     PARA3  Number of bytes to write
* APDU Inputs:        (PARA3) number of RAM data bytes
* APDU Outputs:       None
* Example1 usage:     Write 2 bytes (11h 22h) to IDATA start address 40h
* To Card             ->  E5 8C 00 40 02
* ACK from Card       <-  8C
* Data to Card        ->  11 22
* Response from Card  <-  90 00
*
******************************************************************************/
uint Write_To_IRAM (void)
{
    IDATA_PTR = PARA2; /* Point to IDATA location to write to */

    /* A DO-WHILE loop enables 256 bytes to be sent */
    /* User needs to set PARA3 = 00 for 256 byte output */
    do
    {
        *(IDATA_PTR++) =  GetChar();    /* Get the value to write to RAM */
    } while ((--PARA3) != 0);       /* Output byte until counter is zero */

    return SW1SW2_OK;

} /* End of function */
