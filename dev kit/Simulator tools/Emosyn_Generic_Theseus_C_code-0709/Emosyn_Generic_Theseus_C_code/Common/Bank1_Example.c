/******************************************************************************
*
* Name:         Bank1_Example.c
* Description:  Contains function to demonstrate code in code bank 1
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
* Function Name:      CommandInBank1
* Function Inputs:    void
* Function Outputs:   void
* Description:        Outputs a string to the serial port.
*                     The code is running from bank 1
*
******************************************************************************/
void CommandInBank1 (void) 
{
    char *szString0 = "Command in Bank 1";

    for (ucCount = 0; ucCount < 0x11; ucCount++)
       PutChar(szString0[ucCount]);
}
