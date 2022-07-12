/******************************************************************************
*
* Name:         Set_PPS.c
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
* $Date: 
/******************************************************************************/


/******************************************************************************
* Header file inclusions
******************************************************************************/
#include "Firmware_API_JumpTable.h"
#include "Emosyn_Clock_Speeds.h"


/******************************************************************************
* External and local function declarations 
******************************************************************************/
extern void Select_FiDi(unsigned char Fi, unsigned char Di);
extern void PutCharParityBit();

/******************************************************************************
* External variable declarations
******************************************************************************/

extern unsigned char data Fh;
extern unsigned char data Fl;
extern unsigned char data D;
extern unsigned char data APDU_P1;
extern unsigned char data APDU_P2;
extern unsigned char data APDU_P3;



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
    unsigned int idata F = 0;
    unsigned int idata ISO_Timer_Val = 371;
	unsigned char Fi = (char)(FiDi >> 4);
	unsigned char Di = (char)(FiDi & 0x0F);
	

    Select_FiDi(Fi, Di);

	F = (unsigned int)(Fh<<8);
    F|=(unsigned int)(Fl);
 		
   	/* Calculate the timer value based on the F and D values */
   	ISO_Timer_Val = (F / D) - 1;


	// reflex the PPS

	// always echo back successfull PPS as all PPS values are supported.
	ACC = 0xFF;
	PutCharParityBit(); 
	ACC = APDU_P1;
	PutCharParityBit();
	ACC = APDU_P2;
	PutCharParityBit();
	ACC = APDU_P3;
	PutCharParityBit();	
	/* Load ISOTMR SFR with high part of desired value 		*/
   	ISOTMR = ISO_Timer_Val >> 8;

   	/* Load ISOTMR SFR with low part of desired value 		*/
   	ISOTMR = ISO_Timer_Val & 0xFF;

	
} /* End of function */
