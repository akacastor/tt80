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
* $Revision: 1.1 $
* $Author: xavier $ 
* $Date: 2006/07/12 02:40:31 $
******************************************************************************/


/******************************************************************************
* Header file inclusions
******************************************************************************/

extern Firmware_SetClock (unsigned char, unsigned char, unsigned char); _at_ 0x1F8

extern unsigned char GetChar();
extern unsigned char data APDU_P1;
extern unsigned char data APDU_P2;
extern unsigned char data APDU_P3;



/******************************************************************************
* External and local function declarations 
******************************************************************************/
extern unsigned char GetChar();
extern unsigned char data APDU_P1;
extern unsigned char data APDU_P2;
extern unsigned char data APDU_P3;
extern unsigned char data SW2;



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
void Set_Clock (void)
{
    

unsigned char idata cRet_Val_Char=0;

    if (APDU_P2 != 0x00)
    {
    	// wrong P1P2
		ACC = 0x6A;
		SW2 = 0x86; 
    }

    else
    {
            /* Actual firmware API call */
            cRet_Val_Char = Firmware_SetClock (0, 0, APDU_P2);

			
            if (cRet_Val_Char != 0)
            {
				
				ACC = 0x6A;
				SW2 = 0x80;
            }
            else
            {
            	ACC = 0x90;
				SW2 = 0x00;            
        	}
    }

	} /* End of function */
