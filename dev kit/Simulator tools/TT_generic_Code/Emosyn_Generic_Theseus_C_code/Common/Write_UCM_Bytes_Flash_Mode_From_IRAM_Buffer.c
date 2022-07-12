/******************************************************************************
*
* Name:         Write_UCM_Bytes_Flash_Mode_From_IRAM_Buffer.c
* Description:  Contains function to write to UCM using data held in IDATA
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
* $Author: amorris $ 
* $Date: 2005/10/25 16:58:26 $
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
* Function Name:      Write_UCM_Bytes_Flash_Mode_From_IRAM_Buffer
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or 6581h for failure
* Description:        Writes bytes from IDATA memory to UCM
*
* APDU Syntax:        E5 20 PARA1 PARA2 02
* APDU Inputs:        PARA1      High byte of the UCM address in XDATA space
*                     PARA2      Low byte of the UCM address in XDATA space
*                     DataByte1  IDATA source address of the Data to write
*                     DataByte2  Number of bytes to write
* APDU Outputs:       None
*
* Example usage:      Write 20h bytes to UCM (starting at 6000h in XDATA space)
*                     from IDATA starting at 40h
* To Card             ->  E5 20 60 00 02
* ACK from Card       <-  20
* Data to Card        ->  40 20
* Response from Card  <-  90 00
*
******************************************************************************/
uint Write_UCM_Bytes_Flash_Mode_From_IRAM_Buffer (void)
{
    if (PARA3 == 0x02)
    {
        /* Get the additional data bytes (address of Idata source and number of bytes to copy) */
        Serial_Receive_X_Bytes (0x02, &TEMP_BUF);

        /* Actual firmware API call */
        cRet_Val_Char = Firmware_WriteUCM (Conv_Two_Bytes_To_Int (PARA1, PARA2), TEMPVARIABLE1, TEMPVARIABLE2);

        if (MSB_SET & cRet_Val_Char) 
        {
            SW1SW2 = SW1SW2_MEMORY_ERROR;   /* If MSB of return value is set it */
        }                                   /* indicates a memory error */
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
