/******************************************************************************
*
* Name:         Get_Pullup_Resistor.c
* Description:  Contains function to get the pullup resistor status
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
* $Date: 2006/02/22 15:50:05 $
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
* Function Name:      Get_Pullup_Resistor
* Function Inputs:    None
* Function Outputs:   uint 9000h for success or   
*   			   6C00h for wrong LE
* Description:        Returns the value of PROGIO register (pullup resistor status)
*
* APDU Syntax:        E5 F2 00 00 01
* APDU Inputs:        None
* APDU Outputs:       value of PROGIO register
*
* Example usage:      Get Pullup status
* To Card             ->  E5 F2 00 00 01
* ACK from Card       <-  F2
* Data from Card      <-  Value of PROGIO
* Response from Card  <-  90 00
*
******************************************************************************/
uint Get_Pullup_Resistor (void)
{
    if (PARA3 == 0x01)
    {
        /* Output the IO Pullup Resistor value held in the PROGIO SFR */
        PutChar (PULLUP_RES_STATE);

        SW1SW2 = SW1SW2_OK;
    }
    else
    {
        SW1SW2 = SW1SW2_WRONG_LE_LENGTH;    /* Only allow a LE of 1 */
    }

    return SW1SW2;

} /* End of function */