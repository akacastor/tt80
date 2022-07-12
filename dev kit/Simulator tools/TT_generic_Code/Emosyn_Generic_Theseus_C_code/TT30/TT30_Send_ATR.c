/******************************************************************************
*
* Name:         TT30_Send_ATR.c
* Description:  Contains function to output ATR string of chip
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
* $Author: rwilliams $ 
* $Date: 2006/06/16 23:58:05 $
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
   PutChar (0x3B); /* Direct Convention */


    PutChar (0x93); /* TA(1) present. TD(1) present. 3 Historical Bytes */ 

    PutChar (0x11); /* TA(1) - FiDi to give /372 */

    PutChar (0x00); /* TD(1) */

    PutChar (0x00); /* High byte of Chip type (0030) */

    PutChar (0x30); /* Low byte of Chip type (0030) */

    PutChar (Firmware_GetFirmwareVersion()); /* Chip firmware version */


/* Following is a specail test not to be released
 * This is a test to validate the functionality of the TT30 in a Phone 
 * If there is a long.... delay after the resistor is enabled 
 * the resistor should have a "Hold Time" of 1ms 
 * This was a successful test to allow the Enabled Pull Up
 * to turn on and become stable before the ATR
 * Needed because Phone Manuf. did not have internal Pull Up
 * Code Provided below for reference only
 * rw 6/16/05
	
	long  i;
    for (i = 0; i < 20; i++)
	{
			
	}

	// ATR is specific to the Phone Manufacturer

	PutChar(0x3B);
	PutChar(0x9D);
	PutChar(0x94);
	PutChar(0x00);
	PutChar(0x4D);
	PutChar(0x4D);
	PutChar(0x13);
	PutChar(0x81);
	PutChar(0x04);
	PutChar(0x54);
	PutChar(0x33);
	PutChar(0x30);
	PutChar(0x20);
	PutChar(0x06);
	PutChar(0x01);
	PutChar(0x90);
	PutChar(0x00);

*/

} /* End of function */
