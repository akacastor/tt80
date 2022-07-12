/******************************************************************************
*
* Name:         Set_Execute_Only_Status.c
* Description:  Contains function to set the execute only flag on the user 
*               specified memory blocks
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
* $Revision: 1.5 $
* $Author: chin $ 
* $Date: 2005/10/31 10:02:29 $
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
* Function Name:      Set_Execute_Only_Status
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or
*                                  6581h for memory failure or
*                                  6700h for wrong LC
* Description:        Sets the execute only flag on the user specified memory
*                     blocks, this will allow the code to be executed but will
*                     not allow the code space to be read by the user
*
* APDU Syntax:        E5 12 00 PARA2 02
* APDU Inputs:        PARA2      Temporary (0) or Persistent (1) setting
*                     DataByte1  High byte of Set Protect Status memory block
*                     DataByte2	 Low byte of Set Protect Status memory block
* APDU Outputs:       None
*
* Example usage:      Set DC00 -> E7FF on the TP50 as Execute Only, (non permanent)
* To Card             ->  E5 12 00 00 02
* ACK from Card       <-  12
* Data to Card        ->  00 E0
* Response from Card  <-  90 00
*
******************************************************************************/
uint Set_Execute_Only_Status (void)
{
    if (PARA3 == 0x02) /* Only allow 2 bytes (LC) for input */
    {
        Serial_Receive_X_Bytes (0x02, &TEMP_BUF); /* Get the additional data bytes */

        /* Actual firmware API call */
        cRet_Val_Char = Firmware_SetExecuteOnlyStatus (Conv_Two_Bytes_To_Int (TEMPVARIABLE1, TEMPVARIABLE2), PARA2);

        /* Check the firmware call result */
        if (MSB_SET & cRet_Val_Char)
        {
            SW1SW2 = SW1SW2_MEMORY_ERROR;   /* If MSB of return value set it */
        }                                   /* indicates a memory operation error */
        else
        {
            SW1SW2 = SW1SW2_OK;         /* Firmware return value was 0 or the number */
        }                               /* of pulses required for memory operation */
    }

    else
    {
        SW1SW2 = SW1SW2_WRONG_LC_LENGTH;    /* Wrong amount of input bytes */
    }

    return SW1SW2;

} /* End of function */
