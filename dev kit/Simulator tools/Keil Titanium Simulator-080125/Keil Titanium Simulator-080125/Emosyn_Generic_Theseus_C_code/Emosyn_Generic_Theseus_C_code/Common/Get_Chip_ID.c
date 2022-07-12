/******************************************************************************
*
* Name:         Get_Chip_ID.c
* Description:  Contains function to output the chips unique 8 byte ID
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
* $Revision: 1.4 $
* $Author: chin $ 
* $Date: 2005/11/01 18:43:48 $
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
* Function Name:      Get_Chip_ID
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or 
*                                  6C00h for wrong LE
* Description:        Outputs the chips unique 8 byte ID to the serial port
*
* APDU Syntax:        E5 0A 00 00 08
* APDU Inputs:        None
* APDU Outputs:       8 byte chip ID
*
* Example usage:      Output the chips ID
* To Card             ->  E5 0A 00 00 08
* ACK from Card       <-  0A
* Data from card      <-  8 byte chip ID
* Response from Card  <-  90 00
*
******************************************************************************/
uint Get_Chip_ID (void)
{
    if (PARA3 == TEMP_BUFFER_SIZE) /* Only allow eight byte response */
    {	
	    for (ucCount = 0; ucCount < TEMP_BUFFER_SIZE; ucCount++)   /* Clear the buffer with 0x00 pattern */
	    {
	        TEMP_BUF[ucCount] = 0x00;
	    }
	
	    Firmware_GetChipID (&TEMP_BUF);     /* Actual firmware API call */
	
	    Serial_Transmit_X_Bytes (TEMP_BUFFER_SIZE, &TEMP_BUF);  /* Tranmsit the data */

		SW1SW2 = SW1SW2_OK;
    }

	else
    {
        SW1SW2 = SW1SW2_WRONG_LE_LENGTH;		
    }

    return SW1SW2;

} /* End of function */
