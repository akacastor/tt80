/******************************************************************************
*
* Name:         TT240_SRAM_Clear.c
* Description:  Clears one or both halves of SRAM to 0x00
* Copyright:    SST 2006
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
* $Author: dhunter $
* $Date: 2007/03/07 00:54:48 $
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
* Function Name:      TT240_SRAM_Clear
* Function Inputs:    None
* Function Outputs:   uint SW1SW2  9000h
* Description:        Clears one or both halves of SRAM to 0x00
*
* APDU Syntax:        E5 A6 Para1 00 00
* APDU Inputs:        Para1  SRAM Selection: 
*                            0x01 = first half, 0x02 = second half, 0x03 = all
* APDU Outputs:       None
*
* Example usage:      Clear the first half of SRAM
* To Card             ->  E5 A6 01 00 00
* ACK from Card       <-  A6
* Response from Card  <-  90 00
*
******************************************************************************/
uint TT240_SRAM_Clear (void)
{
    Firmware_SRAM_Clear (PARA1);

    return SW1SW2_OK;

} /* End of function */
