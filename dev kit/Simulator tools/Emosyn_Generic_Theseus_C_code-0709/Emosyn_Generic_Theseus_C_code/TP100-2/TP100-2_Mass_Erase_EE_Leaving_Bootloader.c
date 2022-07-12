/******************************************************************************
*
* Name:         TP100-2_Mass_Erase_EE_Leaving_Bootloader.c
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
* $Revision: 1.2 $
* $Author: chin $ 
* $Date: 2005/08/24 16:16:28 $
******************************************************************************/


/******************************************************************************
* Header file inclusions
******************************************************************************/
#include "Firmware_API_JumpTable.h"
#include "Emosyn_Helper_Functions.h"


/******************************************************************************
* External and local function declarations 
******************************************************************************/
extern code uchar SetMMU (uchar Partition, uchar PADR, uchar LADR, uchar PSZ, uchar PARCFG);

/******************************************************************************
* External variable declarations
******************************************************************************/


/******************************************************************************
*
* Function Name:      TP100-2_Mass_Erase_EE_Leaving_Bootloader
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or 6581h for failure
* Description:        Erases entire EEPROM excluding the bootloader
*                     
*                     Since the memory map may not be the default TP100-2
*                     memory map the entire EEPROM will be mapped into
*                     partition 0 in XDATA. This will allow complete access to
*                     the EEPROM in just 1 area.
*                     Partition 0 settings:
*                         32K EEPROM in XDATA space
*                         Physical address = 0000h
*                         Logical address  = 6000h - DFFFh
*                         Size             = 32K
*                         Partition Config = Data Space, No access restriction,
*                                            EE, Active in Kernal Mode
*
*
* APDU Syntax:        E5 8A 00 00 00
* APDU Inputs:        None
* APDU Outputs:       None

* Example usage:      Erase entire EEPROM excluding the bootloader
* To Card             ->  E5 8A 00 00 00
* ACK from Card       <-  8A
* Response from Card  <-  90 00 
*
******************************************************************************/
uint Mass_Erase_EE_Leaving_Bootloader (void)
{
    /* Setup the status word return as success */
    SW1SW2 = SW1SW2_OK;

    /* Setup the entire EEPROM as Partition 0 in XDATA space */
    SetMMU (0x00, 0x00, 0x60, 0x7F, 0x49);			

    /* Loop round erasing 64 bytes of EEPROM until finished or erase failure */
    for (uiTemp_Address = 0x6000; uiTemp_Address < 0xD800; uiTemp_Address += 64)
    {
        if (Firmware_EraseEE64Bytes (uiTemp_Address) < 0)
        {
            SW1SW2 = SW1SW2_MEMORY_ERROR;
            break;
        }
    }

    return SW1SW2;
}






