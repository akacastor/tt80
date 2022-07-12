/******************************************************************************
*
* Name:         Get_Set_Pullup_Resistor.c
* Description:  Contains function to get and set the pullup resistor status
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
* $Revision: 
* $Author:  
* $Date: 
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
* Function Name:      Get_Set_Pullup_Resistor
* Function Inputs:    None
* Function Outputs:   uint SW1SW2  0xXXXX returns
* Description:        For "Get" simply returns the value of PROGIO register and returns SW1SW2
*                     For "Set" enters the value of PARA 2 into the PROGIO register and returns SW1SW2
*
* APDU Syntax:        E5 EE PARA1 PARA2 (Get:PARA3 / Set:0x00)
* APDU Inputs:        PARA1: Get = 0x01, Set = 0x02
*                     PARA2: Pullup resistor disabled = 0x00, Pullup resistor enabled = 0x01
*                     PARA3: For "get" mode must be = 0x01 for "set" mode must be = 0x00 
* APDU Outputs:       SW1SW2 - 9000h  Get/Set succussful
*                              6F00h  Set was not successful
*
* Example usage:      Get Pullup status
* To Card             ->  E5 EE 01 00 01
* ACK from Card       <-  EE
* Data from Card      <-  Value of PROGIO
* Response from Card  <-  For Error: SW1SW2_WRONG_LE_LENGTH For success: SW1SW2_OK
*
* Example usage:      Set Pullup status to disable resistor
* To Card             ->  E5 EE 02 00 00
* ACK from Card       <-  EE
* Response from Card  <-  For error: SW1SW2_GENERAL_ERROR  For success: SW1SW2_OK
*
* Example usage:      Set Pullup status to enable resistor
* To Card             ->  E5 EE 02 01 00
* ACK from Card       <-  EE
* Response from Card  <-  For error: SW1SW2_GENERAL_ERROR  For success: SW1SW2_OK
******************************************************************************/
uint Get_Set_Pullup_Resistor (void)
{
	/* Assume an error until the code can prove a success */
	SW1SW2 = SW1SW2_GENERAL_ERROR; 

	/* If the user selects to get the pullup status, we need to return PROGIO */
	if(PARA1 == GET_PULLUP)
	{
		if(PARA3 == 0x01)
		{
			/* Output the status of the PROGIO register */
			PutChar(PULL_UP);
			SW1SW2 = SW1SW2_OK;
		}
		else
		{
		    SW1SW2 = SW1SW2_WRONG_LE_LENGTH;
		}
	}
	/* If the user selects to set the pullup status, we need to set the PROGIO and return */
	else if(PARA1 == SET_PULLUP)
	{
		/* Set PROGIO to the user requirements to enable of disable the resistor */
		PULL_UP = PARA2;

		/* Return success if the data was written correctly return */
		if(PULL_UP == PARA2) 
		{
			SW1SW2 = SW1SW2_OK;
		}
	}
		
    return SW1SW2;

} /* End of function */