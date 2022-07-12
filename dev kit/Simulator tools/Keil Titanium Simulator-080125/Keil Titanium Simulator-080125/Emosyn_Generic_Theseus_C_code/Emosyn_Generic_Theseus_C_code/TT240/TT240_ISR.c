/******************************************************************************
*
* Name:         TT240_ISR.c
* Description:  Contains Interrupt Service Routines for the TT240
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
* $Date: 2007/03/07 00:54:48 $
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
* Keil's C driven ISR use the "interrupt X" syntax at the end of the function
* declartion. X is the Keil specific interrupt number.
* Listed below is the interrupt number based on the interrupt vector address
*
* 0   0003h    8   0043h    16  0083h    24  00C3h
* 1   000Bh    9   004Bh    17  008Bh    25  00CBh
* 2   0013h    10  0053h    18  0093h    26  00D3h
* 3   001Bh    11  005Bh    19  009Bh    27  00DBh
* 4   0023h    12  0063h    20  00A3h    28  00E3h
* 5   002Bh    13  006Bh    21  00ABh    29  00EBh
* 6   0033h    14  0073h    22  00B3h    30  00F3h
* 7   003Bh    15  007Bh    23  00BBh    31  00FBh
*
* The saving of the ACC, B, DPTR, PSW and registers are performed automatically
* by the compiler
******************************************************************************/

/******************************************************************************
*
* Function Name:     Timer0_ISR
* Function Inputs:   void
* Function Outputs:  void
* Description:       Code that executes when the Timer0 interrupt occurs
*
******************************************************************************/
void Timer0_ISR (void) interrupt 1
{
	Timer0_Int_Count += 1;
} /* End of function */


/******************************************************************************
*
* Function Name:     Timer1_ISR
* Function Inputs:   void
* Function Outputs:  void
* Description:       Code that executes when the Timer1 interrupt occurs
*
******************************************************************************/
void Timer1_ISR (void) interrupt 2
{
	Timer1_Int_Count += 1;
} /* End of function */


/******************************************************************************
*
* Function Name:     Serial_ISR
* Function Inputs:   void
* Function Outputs:  void
* Description:       Code that executes when the serial receive interrupt occurs
*
******************************************************************************/
void Serial_ISR (void) interrupt 4
{

} /* End of function */


/******************************************************************************
*
* Function Name:     Security_Fault_ISR
* Function Inputs:   void
* Function Outputs:  void
* Description:       Code that executes when the security interrupt occurs
*
******************************************************************************/
void Security_Fault_ISR (void) interrupt 5
{
	/* The user can report the security fault via the IO in the following way */

    PutChar (0x2B);             /* Output 2Bh to show ISR 2Bh has occured */

    PutChar (SECURITYSTATUS);   /* Output the Security Status sfr */

    SECURITYSTATUS = 0x00;      /* Clear the Security Status sfr */


	/* The could also force a reset if a fatal error has occured */

//  SECURITYSTATUS = 0x00;         /* First clear the Security Status sfr */

	/* Set security action SFR to cause a reset instead of an interrupt */
//	Firmware_SetSecurityAction(0x8F, NOT_PERMANENT);  
	
	/* Set security action SFR to simulate a security fault */
//	SECURITYSTATUS = 0xFF;


} /* End of function */
