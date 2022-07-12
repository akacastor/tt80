/******************************************************************************
*
* Name:         Set_Clock.c
* Description:  Contains function to change the chip clock settings
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
* $Author: amorris $ 
* $Date: 2005/10/25 17:30:09 $
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
* Function Name:      Set_Clock
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or
*                                  6F00 for General error or
*                                  6A86 for wrong data value or
*                                  6700 for wrong LC
* Description:        Changes the clock settings for the chip
*
* APDU Syntax:        E5 18 00 00 03
* APDU Inputs:        DataByte1  Clock Source
*                     DataByte2  Clock Multiplier
*                     DataByte3  Clock Divider
*                         See Device Reference Guide for clock setting details
* APDU Outputs:       None
*
* Example usage:      Change system clock source to internal oscillator running at 60 MHz
* To Card             ->  E5 18 00 00 03
* ACK from Card       <-  18
* Data from Card      ->  00 (Clock Source) 00 (Multiplier) 0F (Divider)
* Response from Card  <-  90 00
*
******************************************************************************/
uint Set_Clock (void)
{
    if (PARA3 != 0x03)
    {
        SW1SW2 = SW1SW2_WRONG_LC_LENGTH;
    }
    else
    {
        /* Get the 3 data bytes containing the data */
        Serial_Receive_X_Bytes (0x03, &TEMP_BUF);

        /* Check clock source is not greater than 2 */
        /* & multiplier and divider are less than 0x0F */
        if ((TEMPVARIABLE1 > 2) || (TEMPVARIABLE2 & 0xF0) || (TEMPVARIABLE3 & 0xF0))
        {
            SW1SW2 = SW1SW2_INCORRECT_DATA;
        }
        else
        {
            /* Actual firmware API call */
            cRet_Val_Char = Firmware_SetClock (TEMPVARIABLE1, TEMPVARIABLE2, TEMPVARIABLE3);

            if (cRet_Val_Char != 0)
            {
                SW1SW2 = SW1SW2_GENERAL_ERROR; /* If MSB of return value set it */
            }                                  /* indicates a memory operation error */
            else
            {
                SW1SW2 = SW1SW2_OK; /* Firmware return value was 0 */
            }
        }
    }

    return SW1SW2;

} /* End of function */
