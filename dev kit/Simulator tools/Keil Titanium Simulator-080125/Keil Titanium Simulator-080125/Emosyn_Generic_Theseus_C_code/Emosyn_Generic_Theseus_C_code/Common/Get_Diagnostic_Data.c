/******************************************************************************
*
* Name:         Get_Diagnostic_Data.c
* Description:  Contains function to output the diagnostic data in logged in
*               the firmware
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
* $Author: chin $ 
* $Date: 2005/11/01 18:43:58 $
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
* Function Name:      Get_Diagnostic_Data
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or
*                                  6C00h for wrong LE
* Description:        Outputs the diagnostic data from the firmware to the serial port
*
* APDU Syntax:        E5 54 00 00 08
* APDU Inputs:        None
* APDU Outputs:       8 bytes of diagnostic data
*
* Example usage:      Get the diagnostic data from the firmware
* To Card             ->  E5 54 00 00 08
* ACK from Card       <-  54
* Data from Card      <-  8 bytes of diagnostic data
* Response from Card  <-  90 00
*
******************************************************************************/
uint Get_Diagnostic_Data (void)
{
    if (PARA3 == TEMP_BUFFER_SIZE) /* Only allow eight byte response */
    {
	    for (ucCount = 0; ucCount < TEMP_BUFFER_SIZE; ucCount++)   /* Clear the buffer with 0x00 pattern */
	    {
	        TEMP_BUF[ucCount] = 0x00;
	    }
	
	    Firmware_GetDiagnosticData (&TEMP_BUF);     /* Actual firmware API call */
	
	    Serial_Transmit_X_Bytes (TEMP_BUFFER_SIZE, &TEMP_BUF);  /* Tranmsit the data */

		SW1SW2 = SW1SW2_OK;
    }
	else
    {
        SW1SW2 = SW1SW2_WRONG_LE_LENGTH;		
    }

    return SW1SW2;

} /* End of function */
