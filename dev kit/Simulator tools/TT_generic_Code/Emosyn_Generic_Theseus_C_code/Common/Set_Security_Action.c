/******************************************************************************
*
* Name:         Set_Security_Action.c
* Description:  Contains function to change the way the chip reacts to security
*               faults that occur
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
* Function Name:      Set_Security_Action
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or 6581h for failure
* Description:        Sets the action the chip should follow (chip reset
*                     or cause interrupt) on security fault detection
*
* APDU Syntax:        E5 14 PARA1 PARA2 00
* APDU Inputs:        PARA1  0x00  Security faults cause a chip reset
*                            0x40  Security faults cause a chip interrupt
*                     PARA2  Temporary (0) or Persistent (1) setting
* APDU Outputs:       None
* Example usage:      Make security faults cause interrupts permanently
* To Card             ->  E5 14 40 01 00
* ACK from Card       <-  14
* Response from Card  <-  90 00
*
******************************************************************************/
uint Set_Security_Action (void)
{
    /* Actual firmware API call */
    cRet_Val_Char = Firmware_SetSecurityAction (PARA1, PARA2);

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
