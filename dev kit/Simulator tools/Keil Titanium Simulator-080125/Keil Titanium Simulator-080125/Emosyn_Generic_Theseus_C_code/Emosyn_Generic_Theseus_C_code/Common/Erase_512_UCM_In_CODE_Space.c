/******************************************************************************
*
* Name:         Erase_512_UCM_In_CODE_Space.c
* Description:  Contains function to erase a specific 512 byte UCM page
*               specified by the input parameters in CODE space
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
* $Revision: 1.3 $
* $Author: amorris $ 
* $Date: 2005/10/26 09:40:36 $
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
* Function Name:      Erase_512_UCM_In_CODE_Space
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or 6581h for failure
* Description:        Erases a user specified 512 byte UCM page in CODE space
*                     It will need to set the CODE Map bit in NvFsmMode before
*                     the actual NVM operation and clear it on function exit
*
* APDU Syntax:        E5 DE PARA1 PARA2 00
* APDU Inputs:        PARA1  High byte of the UCM page address space
*                     PARA2  Low byte of the UCM page address space
* APDU Outputs:       None
*
* Example usage:      Erase a 512 byte UCM page starting at 8000h
* To Card             ->  E5 DE 80 00 00
* ACK from Card       <-  DE
* Response from Card  <-  90 00
*
******************************************************************************/
uint Erase_512_UCM_In_CODE_Space (void)
{
    /* Actual firmware API call */
    cRet_Val_Char = Firmware_EraseUCM512Bytes_In_CODE_Space (Conv_Two_Bytes_To_Int (PARA1, PARA2));

    /* Check the firmware call result */
    if (MSB_SET & cRet_Val_Char)
    {
        SW1SW2 = SW1SW2_MEMORY_ERROR;   /* If MSB of return value set it */
    }                                   /* indicates a memory operation error */
    else
    {
        SW1SW2 = SW1SW2_OK;         /* Firmware return value was 0 or the number */
    }                               /* of pulses required for memory operation */

    return SW1SW2;

} /* End of function */