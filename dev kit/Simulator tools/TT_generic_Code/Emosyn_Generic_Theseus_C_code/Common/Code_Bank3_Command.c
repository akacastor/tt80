/******************************************************************************
*
* Name:         Code_Bank3_Command.c
* Description:  Contains function to call a function located in a code bank 3
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
extern void CommandInBank3 (void);


/******************************************************************************
* External variable declarations
******************************************************************************/


/******************************************************************************
*
* Function Name:      Code_Bank3_Command
* Function Inputs:    void
* Function Outputs:   uint SW1SW2_OK  9000h
* Description:        Calls a function located in code bank 3
*
* APDU Syntax:        E5 58 00 00 11
* APDU Inputs:        None
* APDU Outputs:       17 bytes of an example string

* Example usage:      Call the example code bank 3 function
* To Card             ->  E5 58 00 00 11
* ACK from Card       <-  58
* Data from Card      ->  43 6F 6D 6D 61 6E 64 20 69 6E 20 42 61 6E 6B 20 33
*                         "Command in Bank 3"
* Response from Card  <-  90 00
*
******************************************************************************/
uint Code_Bank3_Command (void) 
{
    CommandInBank3();

    return SW1SW2_OK;
}
