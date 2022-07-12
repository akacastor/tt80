/******************************************************************************
*
* Name:         Erase_UCM_Blocks__R6R7_Passing.c
* Description:  Contains function to erase user specified UCM blocks
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
* $Revision: 1.4 $
* $Author: chin $ 
* $Date: 2005/11/01 12:40:09 $
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
* Function Name:      Erase_UCM_Blocks__R6R7_Passing
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or 6581h for failure
* Description:        Erases the UCM blocks specified from the user parameters
*
* APDU Syntax:        E5 52 PARA1 PARA2 00
* APDU Inputs:        PARA1  High byte of UCM block codes
*                     PARA2  Low byte of UCM block codes
*                         See Device Reference guide for details of UCM block codes
* APDU Outputs:       None
*
* Example usage:      Erase UCM block 5000h -> 5FFFh and 6000h -> 67FFh
* To Card             ->  E5 52 00 28 00
* ACK from Card       <-  52
* Response from Card  <-  90 00
*
******************************************************************************/
uint Erase_UCM_Blocks__R6R7_Passing (void)
{
    /* Actual firmware API call */
    Firmware_EraseUCMBlock (Conv_Two_Bytes_To_Int (PARA1, PARA2));

    /* The firmware implementation of Erase_UCM_Blocks__R6R7_Passing */
    /* does not return a status value, it does not flag an error if the */
    /* attempted block erase was unsuccessful in the NVFSMCON sfr */

    return SW1SW2_OK;

} /* End of function */
