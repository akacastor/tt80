/******************************************************************************
*
* Name:         Erase_UCM_Page.c
* Description:  Contains function to erase a UCM page
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
* Function Name:      Erase_UCM_Page
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or 6581h for failure
* Description:        Erases a UCM page
*
* APDU Syntax:        E5 2C PARA1 PARA2 00
* APDU Inputs:        PARA1  High byte of UCM address page
*                     PARA2  Low byte of UCM address page
* APDU Outputs:       None
*
* Example usage:      Erase UCM page at 8000h
* To Card             ->  E5 2C 80 00 00
* ACK from Card       <-  2C
* Response from Card  <-  90 00
*
******************************************************************************/
uint Erase_UCM_Page (void)
{
    /* Actual firmware API call */
    cRet_Val_Char = Firmware_ErasePageUCM (Conv_Two_Bytes_To_Int (PARA1, PARA2));

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
