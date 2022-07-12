/******************************************************************************
*
* Name:         Chip_Init.c
* Description:  Contains function to initalise chip settings on start
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
* $Revision: 1.9 $
* $Author: dhunter $ 
* $Date: 2006/07/28 22:32:35 $
******************************************************************************/


/******************************************************************************
* Header file inclusions
******************************************************************************/
#include "Firmware_API_JumpTable.h"
#include "Emosyn_Helper_Functions.h"
#include "../common/Emosyn_Clock_Speeds.h"


/******************************************************************************
* External and local function declarations 
******************************************************************************/
extern void ISO_Select_Speed (uchar FiDi, uchar ucCommand_Type);


/******************************************************************************
* External variable declarations
******************************************************************************/


/******************************************************************************
*
* Function Name:     Chip_Init
* Function Inputs:   void
* Function Outputs:  void
* Description:       Initialises the chip settings for:
*                        Clock  
*                        Interrupt services
*                        PEME enabled
*                        ISO port speed
*                        Default idle mode
*
******************************************************************************/
void Chip_Init (void)
{
    /* Set the clock to internal oscillator, x1 multiplier & /3 divider ratio */
    /* This will make the internal oscillator run at 20MHz */
    Firmware_SetClock (INT_OSC, MULTIPLY_BY_01_RATIO, DIVIDE_BY_03_RATIO);

    /* Enable global interrupt bit */
#ifdef EMULATOR
    Firmware_SetInterruptEnable (0xB2); // Enable all interrupts on the TT80
#else
    IE = 0xB2; // Enable all interrupts on the TT80
#endif

    /* Enable Parity Error management */
    ISOCON = 0x04;

    /* Setup the ISO port speed to FiDi of 372 clocks per etu */
    ISO_Select_Speed (0x11, NO_RETURN_CMD);

    /* Select deep idle mode (internal oscillator turned off when idle) */
    IDLE_MODE = DEEP_IDLE_MODE;

} /* End of function */
