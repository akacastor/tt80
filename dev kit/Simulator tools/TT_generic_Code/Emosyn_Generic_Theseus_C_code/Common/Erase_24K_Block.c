/******************************************************************************
*
* Name:         Erase_24K_Block.c
* Description:  Contains function to erase the 24k UCM block on the TP40, TP52
*               and TP62
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
* Function Name:      Erase_24K_Block
* Function Inputs:    void 
* Function Outputs:   uint SW1SW2  9000h for success or 6581h for failure
* Description:        Erases the 24k UCM block
*
* APDU Syntax:        E5 22 00 00 00
* APDU Inputs:        None
* APDU Outputs:       None
*
* Example usage:      Erase the 24K UCM block
* To Card             ->  E5 22 00 00 00
* ACK from Card       <-  22
* Response from Card  <-  90 00
*
******************************************************************************/
uint Erase_24K_Block (void)
{
    /* Actual firmware API call */
    cRet_Val_Char = Firmware_Erase24K_OTP (); /* Actual firmware API call */
    /* Check the firmware call result */
    if (MSB_SET & cRet_Val_Char)
    {
        SW1SW2 = SW1SW2_MEMORY_ERROR;   /* If MSB of return value set it */
    }                                   /* indicates a memory operation error */
    else
    {
        SW1SW2 = SW1SW2_OK;         /* Firmware return value was 0 */
    }

    return SW1SW2;

} /* End of function */
