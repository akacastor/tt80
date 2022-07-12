/******************************************************************************
*
* Name:         Set_MMU.c
* Description:  Contains function to set a memory partition using the MMU
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
* Function Name:      SetMMU
* Function Inputs:    uchar ucPartition  Partition to modify
*                     uchar ucPADR       Physical address code
*                     uchar ucLADR       Logical address code
*                     uchar ucPSZ        Size code
*                     char ucPARCFG      Partition configuration
* Function Outputs:   uchar              Number of write attempts or 0xFF
* Description:        
******************************************************************************/
uchar SetMMU (uchar ucPartition, uchar ucPADR, uchar ucLADR, uchar ucPSZ, uchar ucPARCFG)
{
    uchar idata ucMMU_Settings[4];

    ucMMU_Settings[0] = ucPADR;
    ucMMU_Settings[1] = ucLADR;
    ucMMU_Settings[2] = ucPSZ;
    ucMMU_Settings[3] = ucPARCFG;

   return (Firmware_SetMMU (ucPartition, &ucMMU_Settings));
}


/******************************************************************************
*
* Function Name:      Call_SetMMU
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or 6581h for failure
* Description:        Sets up a memory partition using the users MMU parameters
*
* APDU Syntax:        E5 34 PARA1 00 04
* APDU Inputs:        PARA1      Partition to modify
*                     DataByte1  Physical address code
*                     DataByte2  Logical address code
*                     DataByte3  Size code
*                     DataByte4  Partition configuration
* APDU Outputs:       None

* Example usage:      Setup Partition 1
*                     Physical address 0000h
*                     Logical address E000
*                     Partiton size 2K
*                     UCM0, Kernal Mode, DATA space
* To Card             ->  E5 34 01 00 04
* ACK from Card       <-  34
* Data from Card      ->  00 E0 07 41
* Response from Card  <-  90 00
*
******************************************************************************/
uint Call_SetMMU (void)
{
    uchar ucPartitionNumber, ucPhysicalAddr, ucLogicalAddr;
    uchar ucPartitionSize, ucPartitionConfig;

    ucPartitionNumber = PARA1;
    ucPhysicalAddr = GetChar();
    ucLogicalAddr = GetChar();
    ucPartitionSize = GetChar();
    ucPartitionConfig = GetChar();

    cRet_Val_Char = SetMMU (ucPartitionNumber, ucPhysicalAddr, ucLogicalAddr,
                            ucPartitionSize, ucPartitionConfig);

	
    /* Check the firmware call result */
    if (MSB_SET & cRet_Val_Char)
    {
        SW1SW2 = SW1SW2_MEMORY_ERROR;   /* If MSB of return value set it */
    }                                   /* indicates a memory operation error */
    else
    {
        SW1SW2 = SW1SW2_OK;         /* Firmware return value was 0 or the number */
    }                               /* of pulses required for memory operation */

    return SW1SW2;


}