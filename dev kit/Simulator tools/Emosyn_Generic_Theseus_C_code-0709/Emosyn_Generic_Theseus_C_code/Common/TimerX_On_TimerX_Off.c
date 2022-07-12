/******************************************************************************
*
* Name:         TimerX_On_TimerX_Off.c
* Description:  Contains function to set the configuration and enabling and 
*               disabling of the chip timers
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
* $Date: 2005/08/24 16:15:44 $
******************************************************************************/


/******************************************************************************
* Header file inclusions
******************************************************************************/
#include "Firmware_API_JumpTable.h"
#include "Emosyn_Helper_Functions.h"


/******************************************************************************
* External and local function declarations 
******************************************************************************/
void Timer0_Start (unsigned int wCounter, unsigned char bMode);
void Timer1_Start (unsigned int wCounter, unsigned char bMode);


/******************************************************************************
* External variable declarations
******************************************************************************/


/******************************************************************************
*
* Function Name:      Turn_On_Timer0
* Function Inputs:    void
* Function Outputs:   uint SW1SW2_OK  9000h
* Description:        Sets up timer0 and then starts it
*
* APDU Syntax:        E5 4A PARA1 PARA2 01
* APDU Inputs:        PARA1      High part of Counter Value
;                     PARA2      Low part of Counter Value
*                     DataByte1  Timer Mode
* APDU Outputs:       None

* Example usage:      Setup Timer 0 for maximum delay (0000) in Mode 1 
* To Card             ->  E5 4A 00 00 08
* ACK from Card       <-  4A
* Data from Card      ->  01
* Response from Card  <-  90 00
*
******************************************************************************/
uint Turn_On_Timer0 (void)
{
    /* Get Mode byte */
    uchar bTimerMode = GetChar();

    /* Get the high byte of counter */
    uint wTimerCounterValue = PARA1 << 8;

    /* Get the low byte of counter */
    wTimerCounterValue = wTimerCounterValue | PARA2;

    /* Call the Timer0 setup and start function */ 
    Timer0_Start (wTimerCounterValue, bTimerMode);

    /* Return status word 0f 9000h */
    return SW1SW2_OK;
}


/******************************************************************************
*
* Function Name:      Turn_On_Timer1
* Function Inputs:    void
* Function Outputs:   uint SW1SW2_OK  9000h
* Description:        Sets up timer1 and then starts it
*
* APDU Syntax:        E5 4C PARA1 PARA2 01
* APDU Inputs:        PARA1      High part of Counter Value
;                     PARA2      Low part of Counter Value
*                     DataByte1  Timer Mode
* APDU Outputs:       None

* Example usage:      Setup Timer 1 for maximum delay (0000) in Mode 1 
* To Card             ->  E5 4C 00 00 08
* ACK from Card       <-  4C
* Data from Card      ->  01
* Response from Card  <-  90 00
*
******************************************************************************/
uint Turn_On_Timer1 (void)
{
    /* Get Mode byte */
    uchar bTimerMode = GetChar();

    /* Get the high byte of counter */
    uint wTimerCounterValue = PARA1 << 8;

    /* Get the low byte of counter */
    wTimerCounterValue = wTimerCounterValue | PARA2;

    /* Call the Timer1 setup and start function */ 
    Timer1_Start (wTimerCounterValue, bTimerMode);

    /* Return status word 0f 9000h */
    return SW1SW2_OK;
}


/******************************************************************************
*
* Function Name:      Timer0_Start
* Function Inputs:    uint wCounter
*                     uchar bMode
* Function Outputs:   None
* Description:        Enabled Timer0 Interrupt
*                     Load Timer0 with wCounter and bMode
*                     Start Timer0
*
******************************************************************************/
void Timer0_Start (uint wCounter, uchar bMode)
{
    uchar TempIE;

    /* Get value of IE */
    TempIE = Firmware_GetInterruptEnable();

    /* Set bit ET0 */
    TempIE = TempIE | 0x02;

    /* Timer 0 overflow causes an interrupt */
    Firmware_SetInterruptEnable (TempIE);

    TR0 = 0;    /* Turn off Timer 0 */
    TF0 = 0;    /* Clear Timer 0 Overflow flag */

    TMOD = TMOD & 0xF0;     /* Do not interfere with Timer 1. Reset Timer 0 */
    TMOD = TMOD | bMode;    /* Set Timer 0 with parameter mode */

    TH0 = (wCounter & 0xFF00) >> 8;  /* Load in high value of counter */
    TL0 = wCounter & 0xFF;           /* Load in low value of counter */

    TR0 = 1;    /* Turn On Timer 0 */
}


/******************************************************************************
*
* Function Name:      Timer1_Start
* Function Inputs:    uint wCounter
*                     uchar bMode
* Function Outputs:   None
* Description:        Enabled Timer1 Interrupt
*                     Load Timer1 with wCounter and bMode
*                     Start Timer1
*
******************************************************************************/
void Timer1_Start (uint wCounter, uchar bMode)
{
    uchar TempIE;

    /* Get value of IE */
    TempIE = Firmware_GetInterruptEnable();

    /* Set bit ET1 */
    TempIE = TempIE | 0x08;

    /* Timer 0 overflow causes an interrupt */
    Firmware_SetInterruptEnable (TempIE);

    TR1 = 0;    /* Turn off Timer 1 */
    TF1 = 0;    /* Clear Timer 1 Overflow flag */

    TMOD = TMOD & 0x0F;             /* Do not interfere with Timer 0. Reset Timer 1 */
    TMOD = TMOD | (bMode << 8);     /* Setup Timer 1 with parameter mode */

    TH1 = (wCounter & 0xFF00) >> 8; /* Load in high value of counter */
    TL1 = wCounter & 0xFF;          /* Load in low value of counter */

    TR1 = 1;    /* Turn On Timer 1 */
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
    uchar TempIE;

    TempIE = Firmware_GetInterruptEnable;   /* Get value of IE */

    TempIE = TempIE & 0xFD;                 /* Clr bit ET0 */

    Firmware_SetInterruptEnable (TempIE);   /* Turn off Timer 0 interrupt */

    TR0 = 0;                                /* Turn off Timer 0 */

    /* Return status word 0f 9000h */
    return SW1SW2_OK;
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

* Example usage:      Turn off Timer0
* To Card             ->  E5 50 00 00 00
* ACK from Card       <-  50
* Response from Card  <-  90 00
*
******************************************************************************/
uint Timer1_Stop (void)
{
    uchar TempIE;

    TempIE = Firmware_GetInterruptEnable;   /* Get value of IE */

    TempIE = TempIE & 0xF7;                 /* Clr bit ET1 */

    Firmware_SetInterruptEnable (TempIE);   /* Turn off Timer 1 interrupt */

    TR1 = 0;                                /* Turn off Timer 1 */

    /* Return status word 0f 9000h */
    return SW1SW2_OK;
}