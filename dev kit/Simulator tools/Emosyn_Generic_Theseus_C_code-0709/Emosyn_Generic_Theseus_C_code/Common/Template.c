/******************************************************************************
*
* Name:         .c
* Description:  Contains function to
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
* Function Name:      
* Function Inputs:    
* Function Outputs:   
* Description:        
*
* APDU Syntax:        E5 INS PARA1 PARA2 PARA3
* APDU Inputs:        None
* APDU Outputs:       None

* Example usage:      
* To Card             ->  E5 INS PARA1 PARA2 PARA3
* ACK from Card       <-  
* Data from Card      ->  
* Response from Card  <-  
*
******************************************************************************/
unsigned int Dummy_C_Function (void)
{
    TEMPVARIABLE1 = GetChar(); /* Get the additional data byte (value to write into memory) */

    SW1SW2 = Firmware_WriteByteUCM (address, TEMPVARIABLE1); /* Actual firmware API call */

    return SW1SW2;

} /* End of function */
