/******************************************************************************
*
* Name:         XDATA_Memory_Dump.c
* Description:  Contains function to output data from XDATA space
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
* Function Name:      XDATA_Memory_Dump
* Function Inputs:    void
* Function Outputs:   uint SW1SW2_OK  9000h
* Description:        
*
* APDU Syntax:        E5 7E PARA1 PARA2 PARA3
* APDU Inputs:        PARA1  High byte of the CODE address space of data
*                     PARA2  Low byte of the CODE address space of data
                      PARA3  Number of bytes to output
* APDU Outputs:       (PARA3) number of XDATA data bytes
*
* Example usage:      Output 56h bytes starting from address 1234h in XDATA space
* To Card             ->  E5 7E 12 34 56
* ACK from Card       <-  7E
* Data from Card      ->  Byte1 Byte2 Byte3...ByteX
* Response from Card  <-  90 00
*
******************************************************************************/
uint XDATA_Memory_Dump (void)
{
    XDATA_PTR = (PARA1 << 8) + PARA2;

    /* A DO-WHILE loop enables 256 bytes to be sent */
    /* User needs to set PARA3 = 00 for 256 byte output */
    do
    {
        PutChar (*(XDATA_PTR++));
    } while ((--PARA3) != 0);   /* Output byte until counter is zero */

    return SW1SW2_OK;

} /* End of function */
