/******************************************************************************
*
* Name:         Mass_Erase_UCM.c
* Description:  Contains function to erase the entire UCM area
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
* Function Name:      Mass_Erase_UCM
* Function Inputs:    void
* Function Outputs:   uint SW1SW2_OK  9000h
* Description:        Erases the whole UCM area not including those areas that
*                     have had their ROM attributes set (Set_Protect)
*
* APDU Syntax:        E5 32 00 00 00
* APDU Inputs:        None
* APDU Outputs:       None
*
* Example usage:      Erase the entire UCM area
* To Card             ->  E5 32 00 00 00
* ACK from Card       <-  32
* Response from Card  <-  90 00
*
******************************************************************************/
uint Mass_Erase_UCM (void)
{
    Firmware_MassEraseUCM (); /* Actual firmware API call */

    return SW1SW2_OK;

} /* End of function */
