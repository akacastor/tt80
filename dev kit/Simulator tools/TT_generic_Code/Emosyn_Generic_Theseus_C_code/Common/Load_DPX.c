/******************************************************************************
*
* Name:         Load_DPX.c
* Description:  Sets the DPX register with the users input
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
* $Date: 2006/03/08 16:21:59 $
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
* Function Name:      Load_DPX
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h
* Description:        Loads the DPX SFR with users input value
*
* APDU Syntax:        E5 B2 Para1 00 00
* APDU Inputs:        Para1  DPX value
* APDU Outputs:       None
*
* Example usage:      Set DPX SFR to 01h
* To Card             ->  E5 B2 01 00 00
* ACK from Card       <-  B2
* Response from Card  <-  90 00
*
******************************************************************************/
uint Load_DPX (void)
{
    /* Save the users DPX specifed value */
    DPX_Addr = PARA1;   

    return SW1SW2_OK;

} /* End of function */
