/******************************************************************************
*
* Name:         Set_Pullup_Resistor.c
* Description:  Contains function to Set the pullup resistor status
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
* $Date: 2006/02/22 15:50:36 $
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
* Function Name:      Set_Pullup_Resistor
* Function Inputs:    None
* Function Outputs:   uint SW1SW2  9000h or 6581h on error
* Description:        Sets the value of PROGIO register (pullup resistor status)
*                     Can be set permanently (default status on bootup) or temporary
*
* APDU Syntax:        E5 F0 Para1 Para2 00
* APDU Inputs:        Para1  Value to set the IO Pull-Up Resistor to
*                     Para2  Set Temporary (00h) or Permanently (01h)
* APDU Outputs:       None
*
* Example usage:      Set the Pullup status to ENABLED permanently
* To Card             ->  E5 F0 01 01 00
* ACK from Card       <-  F0
* Response from Card  <-  90 00
*
******************************************************************************/
uint Set_Pullup_Resistor (void)
{
    /* Actual firmware API call */
    cRet_Val_Char = Firmware_Set_IO_Pullup (PARA1, PARA2);

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