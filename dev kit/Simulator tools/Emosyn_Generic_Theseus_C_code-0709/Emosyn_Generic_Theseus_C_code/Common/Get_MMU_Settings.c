/******************************************************************************
*
* Name:         Get_MMU_Settings.c
* Description:  Contains function to get the MMU settings for a partition
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
* $Revision: 1.1 $
* $Author: chin $ 
* $Date: 2005/08/09 11:53:42 $
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
* Function Name:      Get_MMU_Settings
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success and 0x6A86h for failure
* Description:        Gets the MMU settings for a specified partition
*
* APDU Syntax:        E5 2E PARA1 00 04
* APDU Inputs:        PARA1      Partiton to access
* APDU Outputs:       DataByte1  Physical address code
*                     DataByte2  Logical address code
*                     DataByte3  Size code
*                     DataByte4  Partition configuration

* Example usage:      Get the MMU settings of parition 1
* To Card             ->  E5 2E 01 00 04
* ACK from Card       <-  2E
* Data from Card      ->  4 byte MMU settings
* Response from Card  <-  90 00h
*
******************************************************************************/
uint Get_MMU_Settings(void)
{

    uchar idata ucMMU_Settings[4];

    /* Call the firmware function to retreive the data */
    if (Firmware_GetMMUSetting (PARA1, ucMMU_Settings) != 0)
    {
        SW1SW2 = SW1SW2_INCORRECT_PARA; /* Partition number > 7 */
    }
    else
    {
        SW1SW2 = SW1SW2_OK;
    }

    /* Send the MMU settings to the serial port */
	Serial_Transmit_X_Bytes (0x04, &ucMMU_Settings);

    return SW1SW2;

} /* End of function */
