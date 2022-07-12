/******************************************************************************
*
* Name:         Write_Byte_EE_Flash_Mode.c
* Description:  Contains function to write a byte to EEPROM memory
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
* $Date: 2005/10/26 09:41:11 $
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
* Function Name:      Write_Byte_EE_Flash_Mode
* Function Inputs:    void 
* Function Outputs:   uint SW1SW2  9000h for success or
*                                  6581h for memory failure or
*                                  6700h for wrong LC
* Description:        Writes a byte to EEPROM memory
*
* APDU Syntax:        E5 24 PARA1 PARA2 01
* APDU Inputs:        PARA1      High byte of the EEPROM address space
*                     PARA2      Low byte of the EEPROM address space
*                     DataByte1  Data byte to write
* APDU Outputs:       None
*
* Example usage:      Write 55h to EEPROM address 1234h
* To Card             ->  E5 24 12 34 01
* ACK from Card       <-  24
* Data from Card      ->  55
* Response from Card  <-  90 00
*
******************************************************************************/
uint Write_Byte_EE_Flash_Mode (void)
{
    if (PARA3 == 0x01)
    {
        /* Get the additional data byte (value to write into memory) */
        TEMPVARIABLE1 = GetChar();

        /* Actual firmware API call */
        cRet_Val_Char = Firmware_WriteByteEE (Conv_Two_Bytes_To_Int (PARA1, PARA2), TEMPVARIABLE1);

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
