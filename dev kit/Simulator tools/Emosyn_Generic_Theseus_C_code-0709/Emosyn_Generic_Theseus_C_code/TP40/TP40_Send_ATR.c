/******************************************************************************
*
* Name:         TT40_Send_ATR.c
* Description:  Contains function to output ATR string of chip
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
* Function Name:      Send_ATR
* Function Inputs:    void
* Function Outputs:   void
* Description:        Outputs the ATR string that identifies the chip
*
******************************************************************************/
void Send_ATR (void)
{
    PutChar (0x3B); /* Direct Convention */

    PutChar (0x93); /* TA(1) present. TD(1) present. 3 Historical Bytes  */ 

    PutChar (0x94); /* TA(1) - FiDi to give /64  */

    PutChar (0x00); /* TD(1) */

    PutChar (0x00); /* High byte of Chip type (0040) */

    PutChar (0x40); /* Low byte of Chip type (0040) */

    TEMPVARIABLE1 = Firmware_GetFirmwareVersion();

    PutChar (TEMPVARIABLE1); /* Chip firmware version  */

    return;

} /* End of function */
