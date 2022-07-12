/******************************************************************************
*
* Name:         Get_Clock_Control.c
* Description:  Contains function to output the Clock Control SFR value
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
* $Revision: 1.2 $
* $Author: chin $ 
* $Date: 2005/10/25 16:48:34 $
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
*
* Function Name:      Get_Clock_Control
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or
*                                  6C00h for wrong LE
* Description:        Outputs the Clock Source Select SFR to the serial port
*
* APDU Syntax:        E5 0E 00 00 01
* APDU Inputs:        None
* APDU Outputs:       Value of the Clock control SFR
*
* Example usage:      Output the Clock Source conrol SFR value to the serial port
* To Card             ->  E5 0E 00 00 01
* ACK from Card       <-  0E
* Data from Card      <-  XX (value of the Clock Source control SFR)
* Response from Card  <-  90 00
*
******************************************************************************/
uint Get_Clock_Control (void)
{
    if (PARA3 == 0x01)
    {
       /* Output the Clock source control SFR value */
       PutChar (Firmware_GetClockControlSFR());
    
        SW1SW2 = SW1SW2_OK;
    }
    else
    {
        SW1SW2 = SW1SW2_WRONG_LE_LENGTH;
    }

    return SW1SW2;

} /* End of function */
