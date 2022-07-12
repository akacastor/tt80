/******************************************************************************
*
* Name:         Set_Security_Mask.c
* Description:  Contains function to set the security faults to act upon
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
* Function Name:      Set_Security_Mask
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or 6581h for failure
* Description:        Sets the security mask so the chip can allow or ignore
*                     security fault events. See Device Reference guide for
*                     details of Security Masks
*
* APDU Syntax:        E5 16 PARA1 PARA2 00
* APDU Inputs:        PARA1  Security Mask
*                     PARA2  Temporary (0) or Persistent (1) setting
* APDU Outputs:       None
*
* Example usage:      Only enable Brown-out mask, permanently
* To Card             ->  E5 16 20 01 00
* ACK from Card       <-  16
* Response from Card  <-  90 00
*
******************************************************************************/
uint Set_Security_Mask (void)
{
    /* Actual firmware API call */
    cRet_Val_Char = Firmware_SetSecurityMask (PARA1, PARA2);

    /* Check the firmware call result */
    if (MSB_SET & cRet_Val_Char)
    {
        SW1SW2 = SW1SW2_MEMORY_ERROR;   /* If MSB of return value set it */
    }                                   /* indicates a memory operation error */
    else
    {
        SW1SW2 = SW1SW2_OK;         /* Firmware return value was 0 or the number */
    }                               /* of pulses required for memory operation */

    return SW1SW2;

} /* End of function */
