/******************************************************************************
*
* Name:         Write_To_RAM.c
* Description:  Contains function to write input data to IDATA or XDATA RAM
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
* $Date: 2005/08/09 11:53:42 $
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
* Function Name:      Write_To_RAM
* Function Inputs:    void
* Function Outputs:   uint SW1SW2_OK  9000h
* Description:        Writes input data to IDATA or XDATA RAM
*
* APDU Syntax:        E5 8C PARA1 PARA2 PARA3
* APDU Inputs:        PARA1  High byte of the RAM address to write to
*                     PARA2  Low byte of the RAM address to write to
*                     PARA3  Number of bytes to output
* APDU Outputs:       (PARA3) number of RAM data bytes
*
* Example1 usage:     Write 11h 22h to IDATA address 40h
* To Card             ->  E5 8C F0 40 02
* ACK from Card       <-  8C
* Data from Card      ->  11 22
* Response from Card  <-  90 00
*
*                     The F0 (PARA1) above tells the code that we are writing
*                     to IDATA as the MSB is set
*
* Example1 usage:     Write 11h 22h to XDATA address 40h
* To Card             ->  E5 8C 00 40 02
* ACK from Card       <-  8C
* Data from Card      ->  11 22
* Response from Card  <-  90 00
*
*                     The 00 (PARA1) above tells the code that we are writing
*                     to XDATA as the MSB is NOT set
*
******************************************************************************/
unsigned int Write_To_RAM (void)
{
    if (PARA1 & 0x80) /* If MSB of Para1 is set it is an IDATA RAM write */
    {
        IDATA_PTR = PARA2; /* Point to IDATA location to write to */

        /* A DO-WHILE loop enables 256 bytes to be sent */
        /* User needs to set PARA3 = 00 for 256 byte output */
        do
        {
            *(IDATA_PTR++) =  GetChar();    /* Get the value to write to RAM */
        } while ((--PARA3) != 0);       /* Output byte until counter is zero */

    } /* End of IDATA RAM write */

    else /* If MSB of Para1 is NOT set it is an XDATA RAM write */
    {
        /* Point to XDATA location to write to */
        XDATA_PTR = (PARA1 << 8) + (PARA2);

        /* A DO-WHILE loop enables 256 bytes to be sent */
        /* User needs to set PARA3 = 00 for 256 byte output */
        do
        {
            *(XDATA_PTR++) =  GetChar();    /* Get the value to write to RAM */
        } while ((--PARA3) != 0);       /* Output byte until counter is zero */

    } /* End of XDATA RAM write */

    return SW1SW2_OK;

} /* End of function */
