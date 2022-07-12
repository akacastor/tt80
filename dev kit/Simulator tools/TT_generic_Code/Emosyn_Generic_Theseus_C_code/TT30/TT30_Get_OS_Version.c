/******************************************************************************
*
* Name:         TT30_Get_OS_Version.c
* Description:  Contains function to output OS version number
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
* $Date: 2005/11/01 18:31:40 $
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
* Function Name:      Get_OS_Version
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or
*                                  6C00h for wrong LE
* Description:        This function outputs the OS version number to the IO
*
* APDU Syntax:        E5 8E 00 00 02
* APDU Inputs:        None
* APDU Outputs:       Two byte OS version number
*
* Example usage:      Output the 2 byte version number
* To Card             ->  E5 8E 00 00 02
* ACK from Card       <-  8E
* Data from Card      <-  XX YY
* Response from Card  <-  90 00
*
******************************************************************************/
uint Get_OS_Version (void)
{
    if (PARA3 == 0x02)      /* Only allow a two byte response */
    {
        PutChar (0x00);     /* Output the hardcoded OS version number */
        PutChar (0x01);

        SW1SW2 = SW1SW2_OK; /* Return a status word of 9000h */
    }
	else
    {
        SW1SW2 = SW1SW2_WRONG_LE_LENGTH;		
    }

    return SW1SW2;

} /* End of function */
