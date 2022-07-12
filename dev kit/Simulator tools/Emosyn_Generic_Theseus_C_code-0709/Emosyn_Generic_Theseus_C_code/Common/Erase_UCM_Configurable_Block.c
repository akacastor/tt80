/******************************************************************************
*
* Name:         Erase_UCM_Configurable_Block.c
* Description:  Contains function to erase a 1K UCM configurable block on the
*               TP40, TP50 and TP62 chips
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
* Function Name:      Erase_UCM_Configurable_Block
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or 6581h for failure
* Description:        Erases a specified 1K UCM configurable block
*
* APDU Syntax:        E5 2A PARA1 PARA2 PARA3
* APDU Inputs:        PARA1  High byte of the UCM configurable block address
*                     PARA2  Low byte of the UCM configurable block address
* APDU Outputs:       None

* Example usage:      Erase the UCM configurable block starting at address A000h
* To Card             ->  E5 2A A0 00 00
* ACK from Card       <-  2A
* Response from Card  <-  90 00
*
******************************************************************************/
uint Erase_UCM_Configurable_Block (void)
{
    /* Actual firmware API call */
    cRet_Val_Char = Firmware_EraseConfigBlock (Conv_Two_Bytes_To_Int (PARA1, PARA2));

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
