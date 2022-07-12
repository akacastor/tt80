/******************************************************************************
*
* Name:         TT30_Set_Pullup_Resistor.c
* Description:  Contains function to set the pullup resistor status
*               The TT30 has no option of changing the bootup state of the
*               resistor, it can only change the state when the OS is running.
*               It will revert back to its intial default value on reset
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
* $Revision: 
* $Author:  
* $Date: 
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
* Function Outputs:   uint SW1SW2   9000h for success
* Description:        Sets the internal Pullp-Up resistor to value of PARA 1 into the PROGIO register
*
* APDU Syntax:        E5 EE PARA1 00 00
* APDU Inputs:        PARA1   0x00 = Disable Resistor, 0x01 = Enable Resistor
* APDU Outputs:       SW1SW2  9000h  Set succussful
*
* Example usage:      Set Pullup status to enable resistor
* To Card             ->  E5 EE 01 00 00
* ACK from Card       <-  EE
* Response from Card  <-  90 00
*
******************************************************************************/
uint Set_Pullup_Resistor (void)
{
    /* Set PROGIO to the user requirements to enable or disable the resistor */
    PULLUP_RES_STATE = PARA1 & 0x01;

    return SW1SW2_OK;

} /* End of function */