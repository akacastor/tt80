/******************************************************************************
*
* Name:         Set_Security_Status.c
* Description:  Contains function to set the Security status SFR
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
* Function Name:      Set_Security_Status
* Function Inputs:    void
* Function Outputs:   uint SW1SW2_OK  9000h
* Description:        Writes the user parameter to the Securuty Status SFR
*
* APDU Syntax:        E5 42 Para1 00 00
* APDU Inputs:        Para1  Desired value to write to SECSTA
* APDU Outputs:       None
*
* Example usage:      Write 33h to the SECSTA SFR
* To Card             ->  E5 42 33 00 00
* ACK from Card       <-  42
* Response from Card  <-  90 00
*
******************************************************************************/
uint Set_Security_Status (void)
{
    SECURITYSTATUS = PARA1; /* Write the input parameter ino the SFR */

    return SW1SW2_OK;       /* Return a status word of 9000h */

} /* End of function */
