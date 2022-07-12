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
* $Revision: 1.3 $
* $Author: amorris $ 
* $Date: 2005/10/25 10:20:26 $
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


/******************************************************************************
* External variable declarations
******************************************************************************/


/******************************************************************************
*
* Function Name:      ISO_Select_Speed
* Function Inputs:    uchar FiDi            Byte containing Fi & Di value
*                     uchar ucCommand_Type  Type of baud change
*                                           states if return value is needed
* Function Outputs:   void
* Description:        Changes the ISO serial clock if possible based on FiDi
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
void ISO_Select_Speed (uchar FiDi, uchar ucCommand_Type)
{
    uint idata F = 372;
	uint idata D = 1;
    uint idata ISO_Timer_Val = 371;
	
	switch (FiDi >> 4) /* Select the frequency nibble (upper nibble) */
    {
        case 0x02:  F = 558;  break;
        case 0x03:  F = 744;  break;
        case 0x04:  F = 1116; break;
        case 0x05:  F = 1488; break;
        case 0x06:  F = 1860; break;
        case 0x09:  F = 512;  break;
        case 0x0A:  F = 768;  break;
        case 0x0B:  F = 1024; break;
        case 0x0C:  F = 1536; break;
        case 0x0D:  F = 2048; break;
		default:    F = 372;  break;
    }

    switch (FiDi & 0x0F) /* Select the divider nibble (lower nibble) */
    {
        case 0x02:  D = 2;    break;
        case 0x03:  D = 4;    break;
        case 0x04:  D = 8;    break;
        case 0x05:  D = 16;   break;
        case 0x06:  D = 32;   break;
        case 0x08:  D = 12;   break;
        case 0x09:  D = 20;   break;
		default:    D = 1;    break;
    }

    /* Calculate the timer value based on the F and D values */
    ISO_Timer_Val = (F / D) - 1;

    /******************************************************************************
    * If the D value is supported it will return the confimration bytes if required
    * If the D value is not supported it will return the failure bytes based on
    * what type of baud change is calling this function (PPS, APDU or none)
    *******************************************************************************/

	/* We only allow 9600 (D = 31) & 115K (D = 371) baud because of SwiftSIM limitations */ 
	/* Emosyn silicon is not limited to these speeds */
	if((ISO_Timer_Val == 0x1F) || (ISO_Timer_Val == 0x173))
	{
        if (ucCommand_Type == PPS_BAUD_CMD)
        {
            /* Echo back the 4 byte command */
            Serial_Transmit_X_Bytes (APDU_HEADER_LENGTH - 1, &CLA);
        }

        if (ucCommand_Type == APDU_BAUD_CMD)
        {
            SW1SW2 = SW1SW2_OK;
            Serial_Transmit_X_Bytes (0x02, (uchar *)&SW1SW2);
        }

	    /* Load ISOTMR SFR with high part of desired value */
    	ISOTMR = ISO_Timer_Val >> 8;

    	/* Load ISOTMR SFR with low part of desired value */
    	ISOTMR = ISO_Timer_Val & 0xFF;
	}

    else
    {
        if (ucCommand_Type == PPS_BAUD_CMD)
        {
            PutChar (0xFF); /* Output an invalid PPS response */
        	PutChar (0x00);
        	PutChar (0xFF);
           	PutChar (0x00);
        }

        if (ucCommand_Type == APDU_BAUD_CMD)
        {
            SW1SW2 = SW1SW2_INCORRECT_PARA;
            Serial_Transmit_X_Bytes (0x02, (uchar *)&SW1SW2);
        }
    }
	
} /* End of function */
