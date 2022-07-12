/******************************************************************************
*
* Name:         Erase_UCM_Block.c
* Description:  Contains function to erase selected blocks of UCM memory
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
* $Date: 2005/10/25 16:55:40 $
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
* Function Name:      Erase_UCM_Block
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or
*                                  6581h for memory failure or
*                                  6700h for wrong LC
* Description:        Erases user selected blocks of UCM memory
*
* APDU Syntax:        E5 3C 00 00 04
* APDU Inputs:        PARA3     Number of bytes for the coded UCM blocks 
*                     DataByte1  1st byte of memory block(s) to be erased
*                     DataByte2  2nd byte of memory block(s) to be erased
*                     DataByte3  3rd byte of memory block(s) to be erased
*                     DataByte4  4th byte of memory block(s) to be erased
*                         See Device Reference guide for details of UCM blocks
* APDU Outputs:       None

* Example usage:      Erase blocks D800 -> DBFF & DC00 -> DFFF
* To Card             ->  E5 3C 00 00 04
* ACK from Card       <-  3C
* Data to Card        ->  80 01 00 00
* Response from Card  <-  90 00
*
******************************************************************************/
uint Erase_UCM_Blocks (void)
{
    if (PARA3 == 0x04)
    {
       /* Get the additional data bytes */
        Serial_Receive_X_Bytes (0x04, &TEMP_BUF);

        /* Actual firmware API call */
        cRet_Val_Char = Firmware_EraseUCMBlock (&TEMP_BUF);

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
