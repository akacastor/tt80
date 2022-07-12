/******************************************************************************
*
* Name:         Write_X_Bytes_To_UCM_CODE_Space.c
* Description:  Contains function to write X number of bytes to UCM CODE memory
* Copyright:    Emosyn Inc. 2006
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
* $Date: 2006/02/22 15:47:58 $
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
* Function Name:      Write_X_Bytes_To_UCM_CODE_Space
* Function Inputs:    void 
* Function Outputs:   uint SW1SW2  9000h for success or
*                                  6581h for memory failure or
* Description:        Writes X bytes to UCM CODE memory
*
* APDU Syntax:        E5 E2 PARA1 PARA2 PARA3
* APDU Inputs:        PARA1      High byte of the UCM address space
*                     PARA2      Low byte of the UCM address space
*                     PARA3      Number of bytes to write
*                     DataBytes  Data bytes to write
* APDU Outputs:       None
*
* Example usage:      Write 8 bytes to to UCM CODE address 1234h
* To Card             ->  E5 E2 12 34 08
* ACK from Card       <-  E2
* Data to Card        ->  01 02 03 04 05 06 07 08
* Response from Card  <-  90 00
*
******************************************************************************/
uint Write_X_Bytes_To_UCM_CODE_Space (void)
{
    SW1SW2 = SW1SW2_OK;  /* Initialise status word to OK */

    /* Convert passed in start address parameters into integer */
    uiTemp_Address = Conv_Two_Bytes_To_Int (PARA1, PARA2);

    do 
    {
        /* Actual firmware API call */
        cRet_Val_Char = Firmware_WriteByteUCM_In_CODE_Space (uiTemp_Address, GetChar());

        PARA3--;            /* If 00 is passed in it means write 256 bytes */
        uiTemp_Address++;   /* Point to the next memory location to write to */

        /* Check the firmware call result */
        if (MSB_SET & cRet_Val_Char)
        {
            SW1SW2 = SW1SW2_MEMORY_ERROR;   /* If MSB of return value set it */
        }                                   /* indicates a memory operation error */
    } while (PARA3 > 0); /* loop until PARA3 is zero */

    return SW1SW2;

} /* End of function */