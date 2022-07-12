/******************************************************************************
*
* Name:         Timer1_Functions.c
* Description:  Contains function to set the configuration and enabling and 
*               disabling of Timer1
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
* $Author: dhunter $ 
* $Date: 2007/05/10 00:00:53 $
******************************************************************************/


/******************************************************************************
* Header file inclusions
******************************************************************************/
#include "Firmware_API_JumpTable.h"
#include "Emosyn_Helper_Functions.h"


/******************************************************************************
* External and local function declarations 
******************************************************************************/
void Timer1_Setup (uint wCounter, uchar bMode);


/******************************************************************************
* External variable declarations
******************************************************************************/


/******************************************************************************
*
* Function Name:      Timer1_Start
* Function Inputs:    void
* Function Outputs:   uint SW1SW2_OK  9000h
* Description:        Sets up Timer1 and then starts it
*
* APDU Syntax:        E5 4C PARA1 PARA2 01
* APDU Inputs:        PARA1      High part of Counter Value
;                     PARA2      Low part of Counter Value
*                     DataByte1  Timer Mode
* APDU Outputs:       None

* Example usage:      Setup Timer 1 for maximum delay (0000) in Mode 1 
* To Card             ->  E5 4C 00 00 01
* ACK from Card       <-  4C
* Data to Card        ->  01
* Response from Card  <-  90 00
*
******************************************************************************/
uint Timer1_Start (void)
{
    /* Get Mode byte */
    uchar bTimerMode = GetChar();

    /* Get the high byte of counter */
    uint wTimerCounterValue = PARA1 << 8;

    /* Get the low byte of counter */
    wTimerCounterValue = wTimerCounterValue | PARA2;

    /* Call the Timer1 setup and start function */ 
    Timer1_Setup (wTimerCounterValue, bTimerMode);

    /* Return status word 0f 9000h */
    return SW1SW2_OK;
}


/******************************************************************************
*
* Function Name:      Timer1_Setup
* Function Inputs:    uint wCounter
*                     uchar bMode
* Function Outputs:   None
* Description:        Enabled Timer1 Interrupt
*                     Load Timer1 with wCounter and bMode
*                     Start Timer1
*
******************************************************************************/
void Timer1_Setup (uint wCounter, uchar bMode)
{
    TR1 = 0;                                /* Turn off Timer 1 */
    TF1 = 0;                                /* Clear Timer 1 Overflow flag */

    /* Set bit ET1 (Timer1 Interrupt Enable) */
    Firmware_SetInterruptEnable (Firmware_GetInterruptEnable() | 0x08);

    TMOD = TMOD & 0x0F;                     /* Reset Timer 1 */
    TMOD = TMOD | (bMode << 4);             /* Set Timer 1 with parameter mode */

    TH1 = (wCounter & 0xFF00) >> 8;         /* Load in high value of counter */
    TL1 = wCounter & 0xFF;                  /* Load in low value of counter */

    TR1 = 1;                                /* Turn On Timer 1 */
}


/******************************************************************************
*
* Function Name:      Timer1_Stop
* Function Inputs:    void
* Function Outputs:   uint SW1SW2_OK  0x9000
* Description:        Turns off Timer1 and disables the Timer1 Interrupt
*
* APDU Syntax:        E5 50 00 00 00
* APDU Inputs:        None
* APDU Outputs:       None

* Example usage:      Turn off Timer1
* To Card             ->  E5 50 00 00 00
* ACK from Card       <-  50
* Response from Card  <-  90 00
*
******************************************************************************/
uint Timer1_Stop( void)
{
    /* Clear bit ET1 (Timer1 Interrupt) */
    Firmware_SetInterruptEnable (Firmware_GetInterruptEnable() & ~0x08);

    TR1 = 0;                                /* Turn off Timer 1 */

    /* Return status word 0f 9000h */
    return SW1SW2_OK;
}

/******************************************************************************
*
* Function Name:      Timer1_Read
* Function Inputs:    void
* Function Outputs:   uint 9000h for success or
*		           6C00h for wrong LE
* Description:        Outputs status of Timer1 (SFR's, interrupt count)
*
* APDU Syntax:        E5 5E 00 00 05
* APDU Inputs:        None
* APDU Outputs:       5 bytes of data:
*                     Byte 0: TCON
*                     Byte 1: TMOD
*                     Byte 2: TL1
*                     Byte 3: TH1
*                     Byte 4: Timer1 interrupt counter

* Example usage:      Read Timer1 (after reset)
* To Card             ->  E5 5E 00 00 05
* ACK from Card       <-  5E
* Data from Card      <-  5 bytes of data
* Response from Card  <-  90 00
*
******************************************************************************/
uint Timer1_Read( void)
{
	/* Gather Timer1 status for output. */
	TEMPVARIABLE1 = TCON;
	TEMPVARIABLE2 = TMOD;
	TEMPVARIABLE3 = TL1;
	TEMPVARIABLE4 = TH1;
	TEMPVARIABLE5 = Timer1_Int_Count;

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

