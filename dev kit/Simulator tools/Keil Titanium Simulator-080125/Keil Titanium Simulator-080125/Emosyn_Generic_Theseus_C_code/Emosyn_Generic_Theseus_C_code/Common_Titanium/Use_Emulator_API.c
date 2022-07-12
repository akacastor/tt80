/******************************************************************************
*
* Name:         Use_Emulator_API.c
* Description:  Contains function to select whether to use the firmware emulator
*               API or to use direct access for NVFSM and IE usage.
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
* $Date: 2006/10/11 23:05:18 $
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
* Function Name:      Use_Emulator_API
* Function Inputs:    None
* Function Outputs:   uint SW1SW2  9000h or 6F00h on error
* Description:        Select whether to use the firmware emulator API or to use
*                     direct access for NVFSM and IE usage.  Primarily provided
*                     to allow testing the firmware emulator API.
*
* APDU Syntax:        E5 AA Para1 00 00
* APDU Inputs:        Para1  00 (use direct access) or 01 (emulator API)
* APDU Outputs:       None
*
* Example usage:      Use the emulator API.
* To Card             ->  E5 AA 01 00 00
* ACK from Card       <-  AA
* Response from Card  <-  90 00
*
******************************************************************************/
uint Use_Emulator_API (void)
{
    /* Firmware library call */
    cRet_Val_Char = Firmware_Use_Emulator_API (PARA1);

    /* Check the firmware call result */
    if (cRet_Val_Char != 0x00)
    {
        SW1SW2 = SW1SW2_GENERAL_ERROR;  /* Return value not zero, indicates an error */
    }
    else
    {
        SW1SW2 = SW1SW2_OK;
    }

    return SW1SW2;

} /* End of function */
