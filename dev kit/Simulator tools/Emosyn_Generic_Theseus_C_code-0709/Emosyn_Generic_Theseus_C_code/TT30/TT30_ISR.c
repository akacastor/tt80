/******************************************************************************
*
* Name:         TT30_ISR.c
* Description:  Contains Interrupt Service Routines for the TT30
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
* $Author: chin $ 
* $Date: 2005/08/09 11:53:42 $
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
* The saving of the ACC, B, DPTR, PSW and Banking registers are performed
* automatically by the compiler
******************************************************************************/


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
    PutChar (0x2B); /* Output 2Bh to identify ISR 2Bh has executed */

    PutChar (SECURITYSTATUS); /* Output the Security Status sfr */

    SECURITYSTATUS = 0; /* Clear the Security Status sfr */

} /* End of function */
