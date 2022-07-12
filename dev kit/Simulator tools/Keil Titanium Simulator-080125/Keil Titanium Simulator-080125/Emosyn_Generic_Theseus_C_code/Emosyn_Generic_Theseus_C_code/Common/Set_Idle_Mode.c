/******************************************************************************
*
* Name:         Set_Idle_Mode.c
* Description:  Contains function to set and get the idle mode
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
* $Revision: 1.4 $
* $Author: chin $ 
* $Date: 2006/02/22 15:47:08 $
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
* Function Name:      Set_Idle_Mode
* Function Inputs:    void
* Function Outputs:   uint SW1SW2_OK  9000h
* Description:        Sets the mode bit that determines normal or deep idle
*                     during the waiting stage of receiving an APDU
*
* APDU Syntax:        E5 5A PARA1 00 00
* APDU Inputs:        PARA1  Deep Idle Mode On = 0x01; Normal Idle Mode = 0
* APDU Outputs:       None
*
* Example usage:      Enable Deep Idle mode
* To Card             ->  E5 5A 01 00 00
* ACK from Card       <-  5A
* Response from Card  <-  90 00
*
******************************************************************************/
uint Set_Idle_Mode (void)
{
    IDLE_MODE = PARA1 & 0x01; /* Copy bit zero into Idle mode varible */

    return SW1SW2_OK;

} /* End of function */


/******************************************************************************
*
* Function Name:      Get_Idle_Mode
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or
*                                  6C00h for wrong LE
* Description:        Outputs the variable that determines normal or deep idle
*                     during the waiting stage of receiving an APDU
*
* APDU Syntax:        E5 E8 00 00 01
* APDU Inputs:        None
* APDU Outputs:       Value of the IDLE mode variable
*
* Example usage:      Get the Idle mode value
* To Card             ->  E5 E8 00 00 01
* ACK from Card       <-  E8
* Data from Card      <-  01
* Response from Card  <-  90 00
*
******************************************************************************/
uint Get_Idle_Mode (void)
{
    if (PARA3 == 0x01)
    {
        PutChar (IDLE_MODE);                /* Output the idle mode variable */

        SW1SW2 = SW1SW2_OK;
    }
    else
    {
        SW1SW2 = SW1SW2_WRONG_LE_LENGTH;    /* Only allow a LE of 1 */
    }

    return SW1SW2;

} /* End of function */
