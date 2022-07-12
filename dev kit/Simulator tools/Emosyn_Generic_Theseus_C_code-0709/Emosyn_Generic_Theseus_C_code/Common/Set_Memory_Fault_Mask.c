/******************************************************************************
*
* Name:         Set_Memory_Fault_Mask.c
* Description:  Contains function to set the memory faults to act upon
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
* Function Name:      Set_Memory_Fault_Mask
* Function Inputs:    void
* Function Outputs:   uint SW1SW2_OK  9000h
* Description:        Sets the memory mask so the chip can allow or ignore
*                     memory fault events. See Device Reference guide for
*                     details of memory masks
*
* APDU Syntax:        E5 28 PARA1 PARA2 00
* APDU Inputs:        PARA1  Memory Fault Mask value
*                     PARA2  Temporary (0) or Persistent (1) setting
* APDU Outputs:       None

* Example usage:      Set mask so illegal SFR accesses will cause an interrupt
*                     temporary status
* To Card             ->  E5 28 40 00 00
* ACK from Card       <-  28
* Response from Card  <-  90 00
*
******************************************************************************/
uint Set_Memory_Fault_Mask (void)
{
    Firmware_SetMemoryFaultMask (PARA1, PARA2);

    return SW1SW2_OK;
}