/******************************************************************************
*
* Name:         Write_UCM_Bytes_From_IRAM_Buffer_Extended_Addressing.c
* Description:  Contains function to write to UCM using data held in IDATA
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
* $Date: 2006/03/08 16:21:59 $
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
* Function Name:      Write_UCM_Bytes_From_IRAM_Buffer_Extended_Addressing
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or
*                                  6581h for memory failure or
*                                  6700h for wrong LC
* Description:        Writes bytes from IDATA memory to UCM
*
* APDU Syntax:        E5 D8 00 00 05
* APDU Inputs:        DataByte1  IDATA source address of the Data to write
*                     DataByte2  Number of bytes to write
*                     DataByte3  DPX address
*                     DataByte4  DPH address
*                     DataByte5  DPL address
* APDU Outputs:       None
*
* Example usage:      Write 20h bytes to UCM (starting at 010203h)
*                     from IDATA starting at 40h
* To Card             ->  E5 D8 00 00 05
* ACK from Card       <-  D8
* Data to Card        ->  40 20 01 02 03
* Response from Card  <-  90 00
*
******************************************************************************/
uint Write_UCM_Bytes_From_IRAM_Buffer_Extended_Addressing (void)
{
    if (PARA3 == 0x05)
    {
        /* Get the address of Idata source and number of bytes to copy) */
        Serial_Receive_X_Bytes (0x02, &TEMPVARIABLE1);

        /* Get 3 byte address */
        /* Need to pass pointer to first byte of far pointer */
        Serial_Receive_X_Bytes (0x03, (unsigned char idata*)&uc_Fptr);

        /* Actual firmware API call */
        cRet_Val_Char = Firmware_WriteUCM (TEMPVARIABLE1, TEMPVARIABLE2, uc_Fptr);

        if (MSB_SET & cRet_Val_Char) 
        {
            SW1SW2 = SW1SW2_MEMORY_ERROR;    /* If MSB of return value is set it */
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