/******************************************************************************
*
* Name:         Timer0_Functions.c
* Description:  Contains function to set the configuration and enabling and 
*               disabling of Timer0
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
* $Revision: 1.6 $
* $Author: dhunter $ 
* $Date: 2006/10/11 23:05:18 $
******************************************************************************/


/******************************************************************************
* Header file inclusions
******************************************************************************/
#include "Firmware_API_JumpTable.h"
#include "Emosyn_Helper_Functions.h"


/******************************************************************************
* External and local function declarations 
******************************************************************************/
void Timer0_Setup (uint wCounter, uchar bMode);


/******************************************************************************
* External variable declarations
******************************************************************************/


/******************************************************************************
*
* Function Name:      Timer0_Start
* Function Inputs:    void
* Function Outputs:   uint SW1SW2_OK  9000h
* Description:        Sets up Timer0 and then starts it
*
* APDU Syntax:        E5 4A PARA1 PARA2 01
* APDU Inputs:        PARA1      High part of Counter Value
;                     PARA2      Low part of Counter Value
*                     DataByte1  Timer Mode
* APDU Outputs:       None

* Example usage:      Setup Timer 0 for maximum delay (0000) in Mode 1 
* To Card             ->  E5 4A 00 00 08
* ACK from Card       <-  4A
* Data to Card        ->  01
* Response from Card  <-  90 00
*
******************************************************************************/
uint Timer0_Start (void)
{
    /* Get Mode byte */
    uchar bTimerMode = GetChar();

    /* Get the high byte of counter */
    uint wTimerCounterValue = PARA1 << 8;

    /* Get the low byte of counter */
    wTimerCounterValue = wTimerCounterValue | PARA2;

    /* Call the Timer0 setup and start function */ 
    Timer0_Setup (wTimerCounterValue, bTimerMode);

    /* Return status word 0f 9000h */
    return SW1SW2_OK;
}


/******************************************************************************
*
* Function Name:      Timer0_Setup
* Function Inputs:    uint wCounter
*                     uchar bMode
* Function Outputs:   None
* Description:        Enabled Timer0 Interrupt
*                     Load Timer0 with wCounter and bMode
*                     Start Timer0
*
******************************************************************************/
void Timer0_Setup (uint wCounter, uchar bMode)
{
    TR0 = 0;                                /* Turn off Timer 0 */
    TF0 = 0;                                /* Clear Timer 0 Overflow flag */

    /* Set bit ET0 (Timer0 Interrupt Enable) */
    Firmware_SetInterruptEnable (Firmware_GetInterruptEnable() | 0x02);

    TMOD = TMOD & 0xF0;                     /* Reset Timer 0 */
    TMOD = TMOD | bMode;                    /* Set Timer 0 with parameter mode */

    TH0 = (wCounter & 0xFF00) >> 8;         /* Load in high value of counter */
    TL0 = wCounter & 0xFF;                  /* Load in low value of counter */

    TR0 = 1;                                /* Turn On Timer 0 */
}


/******************************************************************************
*
* Function Name:      Timer0_Stop
* Function Inputs:    void
* Function Outputs:   uint SW1SW2_OK  0x9000
* Description:        Turns off Timer0 and disables the Timer0 Interrupt
*
* APDU Syntax:        E5 4E 00 00 00
* APDU Inputs:        None
* APDU Outputs:       None

* Example usage:      Turn off Timer0
* To Card             ->  E5 4E 00 00 00
* ACK from Card       <-  4E
* Response from Card  <-  90 00
*
******************************************************************************/
uint Timer0_Stop( void)
{
    /* Clear bit ET0 (Timer0 Interrupt) */
    Firmware_SetInterruptEnable (Firmware_GetInterruptEnable() & 0xFD);

    TR0 = 0;                                /* Turn off Timer 0 */

    /* Return status word 0f 9000h */
    return SW1SW2_OK;
}

/******************************************************************************
*
* Function Name:      Timer0_Read
* Function Inputs:    void
* Function Outputs:   uint 9000h for success or
*			   6C00h for wrong LE
* Description:        Outputs status of Timer0 (SFR's, interrupt count)
*
* APDU Syntax:        E5 5C 00 00 05
* APDU Inputs:        None
* APDU Outputs:       5 bytes of data:
*                     Byte 0: TCON
*                     Byte 1: TMOD
*                     Byte 2: TL0
*                     Byte 3: TH0
*                     Byte 4: Timer0 interrupt counter

* Example usage:      Read Timer0 (after reset)
* To Card             ->  E5 5C 00 00 05
* ACK from Card       <-  5C
* Data from Card      <-  5 bytes of data
* Response from Card  <-  90 00
*
******************************************************************************/
uint Timer0_Read( void)
{
	/* Gather Timer0 status for output. */
	TEMPVARIABLE1 = TCON;
	TEMPVARIABLE2 = TMOD;
	TEMPVARIABLE3 = TL0;
	TEMPVARIABLE4 = TH0;
	TEMPVARIABLE5 = Timer0_Int_Count;

    if (PARA3 == 0x05)
    {
		PutChar (TEMPVARIABLE1);
		PutChar (TEMPVARIABLE2);
		PutChar (TEMPVARIABLE3);
		PutChar (TEMPVARIABLE4);
		PutChar (TEMPVARIABLE5);

        SW1SW2 = SW1SW2_OK;
    }
    else
    {
        SW1SW2 = SW1SW2_WRONG_LE_LENGTH;    /* Only allow a LE of 5 */
    }

    return SW1SW2;
}

