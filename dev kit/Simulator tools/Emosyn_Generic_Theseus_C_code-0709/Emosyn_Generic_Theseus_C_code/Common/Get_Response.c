
/******************************************************************************
*
* Name:         Get_Response.c
* Description:  Contains function to output values set in the IO buffer
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
* $Date: 2005/10/25 12:50:44 $
******************************************************************************/


/******************************************************************************
* Header file inclusions
******************************************************************************/
#include "Firmware_API_JumpTable.h"
#include "Emosyn_Helper_Functions.h"
#include "global_vars.h"

/******************************************************************************
* External and local function declarations 
******************************************************************************/


/******************************************************************************
* External variable declarations
******************************************************************************//*


/******************************************************************************
*
* Function Name:      Get_Response
* Function Inputs:    void
* Function Outputs:   uint SW1SW2_OK  9000h
* Description:        
*
* APDU Syntax:        E5 C0 00 00 PARA3
* APDU Inputs:        PARA3  Number of bytes form IO buffer to output
* APDU Outputs:       PARA3 number of bytes
*
* Example usage:       Read 8 bytes from IO buffer
* To Card             ->  E5 C0 00 00 08
* ACK from Card       <-  C0
* Data from Card      ->  11 22 33 44 55 66 77 88
* Response from Card  <-  9000
*
******************************************************************************/
uint Get_Response (void)
{
	if (PARA3 <= IO_BUFFER_SIZE)
	{
	   /* Keep outputting chars from the buffer until the PARA3 value is reached */
	    for (ucCount = 0; ucCount < PARA3; ucCount++) 
	    {
			PutChar (IO_Buffer[ucCount]);
		}
		SW1SW2 = SW1SW2_OK;
	}
	else
	{
		SW1SW2 = SW1SW2_WRONG_LE_LENGTH;
	}

    return SW1SW2;   /* Return a status word */

} /* End of function */
