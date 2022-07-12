/******************************************************************************
*
* Name:         Conv_Two_Bytes_To_Int.c
* Description:  Contains function to converts 2 chars into an integer
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
* Function Name:      Conv_Two_Bytes_To_Int
* Function Inputs:    uchar ucHiByteAddr  High byte of the char to convert
*                     uchar ucLoByteAddr  Low byte of the char to convert
* Function Outputs:   int                 integer converted from two chars
* Description:        Converts two chars into an integer value
*
******************************************************************************/
uint Conv_Two_Bytes_To_Int (uchar ucHiByteAddr, uchar ucLoByteAddr)
{
    return ((int)(ucHiByteAddr << 8) | (int)ucLoByteAddr);

} /* End of function */
