/******************************************************************************
*
* Name:         Get_Interrupt_Enable.c
* Description:  Contains function to get the value of the IE register
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
* Function Name:      Get_Interrupt_enable
* Function Inputs:    void
* Function Outputs:   uint SW1SW2_OK  9000h
* Description:        Outputs the IE register value
*
* APDU Syntax:        E5 1C 00 00 01
* APDU Inputs:        None
* APDU Outputs:       IE sfr value
*
* Example usage:      Get IE value
* To Card             ->  E5 1C 00 00 01
* ACK from Card       <-  1C
* Data from Card      <-  Value of IE
* Response from Card  <-  90 00
*
******************************************************************************/
uint Get_Interrupt_Enable (void)
{
    /* Get the IE value with the firmware API call and output */
    PutChar (Firmware_GetInterruptEnable());

    return SW1SW2_OK;

} /* End of function */
