/******************************************************************************
*
* Name:         Set_Interrupt_Enable.c
* Description:  Contains function to set the interrupt register
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
* $Revision: 1.2 $
* $Author: chin $ 
* $Date: 2005/10/24 11:05:32 $
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
* Function Name:      Set_Interrupt_Enable
* Function Inputs:    void
* Function Outputs:   uint SW1SW2_OK  9000h
* Description:        Sets the interrupt register with the user input parameter
*
* APDU Syntax:        E5 1A PARA1 00 00
* APDU Inputs:        PARA1  Value to load IE with
* APDU Outputs:       None

* Example usage:      Load IE with 0x82
* To Card             ->  E5 1A 82 00 00
* ACK from Card       <-  Value to load IE with
* Response from Card  <-  90 00
*
******************************************************************************/
uint Set_Interrupt_Enable (void)
{
    /* Set the IE */
    Firmware_SetInterruptEnable (PARA1);

    return SW1SW2_OK;

} /* End of function */
