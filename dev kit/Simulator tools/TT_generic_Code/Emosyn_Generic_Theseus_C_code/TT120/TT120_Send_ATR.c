/******************************************************************************
*
* Name:         TT120_Send_ATR.c
* Description:  Contains function to output ATR string of chip
* Copyright:    Emosyn Inc. 2006
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
* $Date: 2006/03/08 18:50:14 $
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
    PutChar (0x3B);             /* Direct Convention */

    PutChar (0x93);             /* TA(1) present, TD(1) present, 3 Historical Bytes */ 

    PutChar (0x11);             /* TA(1) - FiDi to give /372  */

    PutChar (0x00);             /* TD(1) */

    PutChar (0x01);             /* High byte of chip type (0120) */

    PutChar (0x20);             /* Low byte of chip type (0120) */

    TEMPVARIABLE1 = Firmware_GetFirmwareVersion();

    PutChar (TEMPVARIABLE1);    /* Chip firmware version  */

} /* End of function */
