/******************************************************************************
*
* Name:         TP62_MassEraseEE_Bootloader_Safe.c
* Description:  Contains function to erase entire EEPROM excluding the bootloader
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
* $Author: chin $ 
* $Date: 2005/10/25 11:26:11 $
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
* Function Name:      TheseusPlatinum_EE_MassErase_Bootloader_Safe
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or 6581h for failure
* Description:        Erases entire EEPROM excluding the bootloader
*
* APDU Syntax:        E5 8A 00 00 00
* APDU Inputs:        None
* APDU Outputs:       None
*
* Example usage:      Erase entire EEPROM excluding the bootloader
* To Card             ->  E5 8A 00 00 00
* ACK from Card       <-  8A
* Response from Card  <-  90 00
*
******************************************************************************/
uint TheseusPlatinum_EE_MassErase_Bootloader_Safe (void)
{
    /* Setup the result as pass */
    SW1SW2 = SW1SW2_OK;

    /* Loop round erasing 64 bytes of EEPROM until finished or erase failure */
    for (uiTemp_Address = 0x0800; uiTemp_Address < BOOTLOADER_START_ADDRESS; uiTemp_Address += 64)
    {
        if (Firmware_EraseEE64Bytes (uiTemp_Address) < 0)
        {
            SW1SW2 = SW1SW2_MEMORY_ERROR;
            break;
        }
    }

    return SW1SW2;

} /* End of function */
