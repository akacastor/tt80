/******************************************************************************
*
* Name:         Get_TCON.c
* Description:  Contains function to output the TCON SFR
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
* $Revision: 1.1 $
* $Author: chin $ 
* $Date: 2006/03/08 16:34:35 $
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
* Function Name:      Get_TCON
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or
*                                  6C00h for wrong LE
* Description:        Outputs the value of the current TCON SFR
*
* APDU Syntax:        E5 D0 00 00 01
* APDU Inputs:        None
* APDU Outputs:       Value of the TCON sfr
*
* Example usage:      Outputs the value of the current TCON SFR
* To Card             ->  E5 D0 00 00 01
* ACK from Card       <-  D0
* Data from Card      <-  Value of the TCON sfr
* Response from Card  <-  90 00
*
******************************************************************************/
uint Get_TCON (void)
{
    if (PARA3 == 0x01)
    {
        PutChar (TCON);           /* Output the TCON SFR */

        SW1SW2 = SW1SW2_OK;
    }
    else
    {
        SW1SW2 = SW1SW2_WRONG_LE_LENGTH;    /* Only allow a LE of 1 */
    }

    return SW1SW2;


} /* End of function */
