/******************************************************************************
*
* Name:         Change_Clock_Delay_Random.c
* Description:  Contains function to output an array of random numbers with
*               various delays to randomise the ouput
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
#include <intrins.h> /* Includes the _nop_() function for C code */
#include "Firmware_API_JumpTable.h"
#include "Emosyn_Helper_Functions.h"

#include "Emosyn_Clock_Speeds.h"


/******************************************************************************
* External and local function declarations 
******************************************************************************/


/******************************************************************************
* External variable declarations
******************************************************************************/


/******************************************************************************
*
* Function Name:      Change_Clock_Delay_Random
* Function Inputs:    void
* Function Outputs:   uint SW1SW2_OK  9000h
* Description:        This function differs from the normal Get_Random_number
*                     function as a user delay is used in between each call of
*                     the Firmware_GetRandomNumber function
*
* APDU Syntax:        E5 D0 PARA1 PARA2 PARA3
* APDU Inputs:        PARA1  Clock Divider
*                     PARA2  Read delay (number of NOP's)
*                     PARA3  Number of Random numbers to get
* APDU Outputs:       (PARA3) of random nuumbers

* Example usage:      Get 8 Random numbers
* To Card             ->  E5 D0 0F 22 08
* ACK from Card       <-  D0
* Data from Card      ->  8 random nuumbers
* Response from Card  <-  90 00
*
******************************************************************************/
uint Change_Clock_Delay_Random (void)
{
    /* Save the Clock multiplier and divider ratios currently used by the chip */
    /* This is so the Clock values can be restored after waking up from idle */
    TEMPVARIABLE2 = Firmware_GetClockControlSFR();

    TEMPVARIABLE1 = TEMPVARIABLE2 & 0x0F; /* Clock Divider (lower nibble)*/

    TEMPVARIABLE2 = (TEMPVARIABLE2 & 0xF0) >> 4; /* Clock Multiplier (upper nibble) */

    TEMPVARIABLE3 = Firmware_GetClockSourceSelectSFR(); /* Get the clock source */

    /***********************************************************
     * Note
     * The values for clock settings differ from 
     * Firmware_GetClockSourceSelectSFR to Firmware_SetClock
     *
     * Firmware_GetClockSourceSelectSFR    Firmware_SetClock
     * 00 - ISO Clock Source               00 - Int Clock Source
     * 01 - PLL Clock Source               01 - PLL Clock Source
     * 02 - Int Clock Source               02 - ISO Clock Source
     * So the conversion code below is necessary         
     ***********************************************************/

    if (TEMPVARIABLE3 & 0x02)       /* 0x00 = Int Osc for Firmware_SetClock */
    {
        TEMPVARIABLE3 = INT_OSC;
    }
    else if (TEMPVARIABLE3 & 0x01)  /* 0x01 = PLL for Firmware_SetClock */
    {
        TEMPVARIABLE3 = PLL_CLOCK;
    }
    else                            /* 0x02 = ISOCLK for Firmware_SetClock */
    {
        TEMPVARIABLE3 = ISO_CLOCK;
    }

    /* Run the chip from the internal oscillator, no multiplier & no divisor value */
    Firmware_SetClock (INT_OSC, MULTIPLY_BY_01_RATIO, PARA1);

    /* Set the number of user delays */
    TEMPVARIABLE4 = PARA2;

    do      /* First loop completes when number of user random numbers sent */
    {
        do  /* Second loop completes when number of user NOP delays completed */
        {
            _nop_  ();

        } while (--TEMPVARIABLE4 != 0);
        /* Loop until number of user delays has been reached */

        /* Get a random number and output it to the serial port */
        PutChar (Firmware_GetRandomNumber());

        /* Reset to the original number of user delays */
        TEMPVARIABLE4 = PARA2;

    } while (--PARA3 != 0);
    /* Keep looping until number of user specified random numbers has been sent */

    /* Restore all the previous clock values */
    Firmware_SetClock (TEMPVARIABLE3, TEMPVARIABLE2, TEMPVARIABLE1);

    return SW1SW2_OK;

} /* End of function */
