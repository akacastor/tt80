/******************************************************************************
*
* Name:         Set_Protection_Status_4Bytes.c
* Description:  Contains function to set the ROM Protection bit on user
*               specified UCM memory blocks (takes 4 bytes for setting instead
*               of 2 unlike Set_Protection_Status())
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
* $Author: chin $ 
* $Date: 2005/10/25 11:11:37 $
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
* Function Name:      Set_Protection_Status_4Bytes.c
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or
*                                  6581h for memory failure or
*                                  6700h for wrong LC
* Description:        Set the protection flag on the user specified memory
*                     blocks, the code will be treated like ROM and not allow
*                     erasing or writing operations
*
* APDU Syntax:        E5 10 00 PARA2 04
* APDU Inputs:        PARA2      Temporary (0) or Persistent (1) setting
*                     DataByte1  1st byte of memory block(s) to be protected
*                     DataByte2  2nd byte of memory block(s) to be protected
*                     DataByte3  3rd byte of memory block(s) to be protected
*                     DataByte4  4th byte of memory block(s) to be protected
*                         See Device Reference guide for details of UCM blocks
* APDU Outputs:       None
*
* Example usage:      Set DC00 -> DFFF on the TP100-2 as protected, non permanent
* To Card             ->  E5 10 00 00 04
* ACK from Card       <-  10
* Data from Card      ->  00 01 00 00
* Response from Card  <-  90 00
*
******************************************************************************/
uint Set_Protection_Status_4Bytes (void)
{
    if (PARA3 == 0x04)
    {
        /* Get the additional data bytes */
        Serial_Receive_X_Bytes (0x04, &TEMPVARIABLE1);

        /* Actual firmware API call */
        cRet_Val_Char = Firmware_SetProtectStatus (&TEMPVARIABLE1, PARA2);

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
