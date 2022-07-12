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
* $Revision: 1.3 $
* $Author: chin $ 
* $Date: 2005/10/18 11:55:12 $
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
    /* Set the clock to internal oscillator, x1 multiplier & /1 divider ratio */
    /* This will make the internal oscillator run at 60MHz */
    Firmware_SetClock (INT_OSC, MULTIPLY_BY_01_RATIO, DIVIDE_BY_01_RATIO);

    /* Enable global interrupt bit */
    Firmware_SetInterruptEnable (0x80);

    /* Enable Parity Error management */
    ISOCON = 0x04;

    /* Setup the ISO port speed to FiDi of 372 */
    ISO_Select_Speed (0x11, NO_RETURN_CMD);

    /* Select deep idle mode (internal oscillator turned off when idle) */
    IDLE_MODE = 1;

} /* End of function */
