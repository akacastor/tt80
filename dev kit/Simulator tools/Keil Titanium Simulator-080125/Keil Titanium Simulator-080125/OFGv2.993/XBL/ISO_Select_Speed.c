/******************************************************************************
*
* Name:         ISO_Select_Speed.c
* Description:  Contains function to set IO serial clock speed from user input (FiDi)
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
#include "Firmware_API_JumpTable.h"
#include "Emosyn_Clock_Speeds.h"


/******************************************************************************
* External and local function declarations 
******************************************************************************/
extern code Select_FiDi(unsigned char, unsigned char);

/******************************************************************************
* External variable declarations
******************************************************************************/

extern unsigned char data Fh;
extern unsigned char data Fi;
extern unsigned char data D;



/******************************************************************************
*
* Function Name:      Set_PPS
* Function Inputs:    uchar FiDi            Byte containing Fi & Di value
* Function Outputs:   void
* Description:        Changes the ISOTMR based on FiDi
*                     ISOTMR value = (Frequency / Divider) - 1
*                     ISOTMR is an 11-bit counter loaded through the 8 bit
*                     ISOTMR SFR 
*                     It uses 2 register writes to load the 11 bits needed
*                     First write -  loads bits 11, 10 and 9 into the ISOTMR SFR
*                     Second write - loads bits 8, 7, 6, 5, 4, 3, 2, 1 and 0
*                     The second write does not overwrite the first bits loaded
*                     the SFR adjusts automatically
*
******************************************************************************/






void Set_PPS (unsigned char FiDi)
{
    unsigned int idata F = 372;
//	unsigned int idata D = 1;
    unsigned int idata ISO_Timer_Val = 371;
	unsigned int Fi;
	unsigned char Di;
	
	Fi= (char)(FiDi >> 4);
	Di= (char)(FiDi & 0x0F);

    Select_FiDi(Fi, Di);
 		
    /* Calculate the timer value based on the F and D values */
    ISO_Timer_Val = (F / D) - 1;

    /******************************************************************************
    * If the D value is supported it will return the confimration bytes if required
    * If the D value is not supported it will return the failure bytes based on
    * what type of baud change is calling this function (PPS, APDU or none)
    *******************************************************************************/


    // XQ: PPS response has to be changed according to ISO 7816-3 (8.2.2) spec
   	/* We only allow 9600 (D = 31) & 115K (D = 371) baud because of SwiftSIM limitations */ 
	/* Emosyn silicon is not limited to these speeds */
// XQ
// XQ	if((ISO_Timer_Val == 0x1F) || (ISO_Timer_Val == 0x173))
// XQ	{
// XQ        if (ucCommand_Type == PPS_BAUD_CMD)
// XQ        {
            /* Echo back the 4 byte command */
// XQ            Serial_Transmit_X_Bytes (APDU_HEADER_LENGTH - 1, &CLA);
// XQ        }

// XQ        if (ucCommand_Type == APDU_BAUD_CMD)
// XQ        {
// XQ            SW1SW2 = SW1SW2_OK;
// XQ            Serial_Transmit_X_Bytes (0x02, (uchar *)&SW1SW2);
// XQ        }

	    /* Load ISOTMR SFR with high part of desired value */
// XQ    	ISOTMR = ISO_Timer_Val >> 8;

    	/* Load ISOTMR SFR with low part of desired value */
// XQ    	ISOTMR = ISO_Timer_Val & 0xFF;
// XQ	}

// XQ    else
// XQ    {
// XQ        if (ucCommand_Type == PPS_BAUD_CMD)
// XQ        {
// XQ            PutChar (0xFF); /* Output an invalid PPS response */
// XQ        	PutChar (0x00);
// XQ        	PutChar (0xFF);
// XQ           	PutChar (0x00);
// XQ        }

// XQ        if (ucCommand_Type == APDU_BAUD_CMD)
// XQ        {
// XQ            SW1SW2 = SW1SW2_INCORRECT_PARA;
// XQ            Serial_Transmit_X_Bytes (0x02, (uchar *)&SW1SW2);
// XQ        }
// XQ    }
	
} /* End of function */
