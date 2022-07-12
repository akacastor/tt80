/******************************************************************************
*
* Name:         Get_Random_Number.c
* Description:  Contains function to some randomly generated numbers
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
* Function Name:      Get_Random_Number
* Function Inputs:    void
* Function Outputs:   uint SW1SW2_OK  9000h
* Description:        
*
* APDU Syntax:        E5 3A 00 00 PARA3
* APDU Inputs:        PARA3  Number of random numbers to output
* APDU Outputs:       None
*
* Example usage:      Get 5 random numbers
* To Card             ->  E5 3A 00 00 05
* ACK from Card       <-  3A
* Data from Card      <-  5 bytes of random numbers
* Response from Card  <-  90 00
*
******************************************************************************/
uint Get_Random_Number (void)
{
    do
    {
        PutChar (Firmware_GetRandomNumber());
    } while ((--PARA3) != 0);

    return SW1SW2_OK;

} /* End of function */
