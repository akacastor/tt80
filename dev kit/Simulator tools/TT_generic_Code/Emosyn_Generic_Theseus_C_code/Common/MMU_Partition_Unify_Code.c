/******************************************************************************
*
* Name:         MMU_Partition_Unify_Code.c
* Description:  Contains function to unify and delete unified partitions
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
* Function Name:      Unify_PartitionX_Into_Data_Space_As_Partition0
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success and 0x6A86h for failure
* Description:        Unifies the partiton selected by user as parition 0
*                     This enables the memory space to be accessed in DATA space
*                     which is needed to write to UCM that only exits in CODE space
*
* APDU Syntax:        E5 36 PARA1 00 00
* APDU Inputs:        PARA1  Partition to be unified
* APDU Outputs:       None

* Example usage:      Unify Partition 3 so it appears in both CODE and DATA space
* To Card             ->  E5 36 03 00 00
* ACK from Card       <-  36
* Response from Card  <-  90 00
*
******************************************************************************/
uint Unify_PartitionX_Into_DATA_Space_As_Partition0 (void)
{
    uchar idata MMU_Settings[4];
    uchar MemoryType;
    uchar PartitionMemorySpace;

    /* Get the MMU settings of the desired Partition */
    Firmware_GetMMUSetting (PARA1, MMU_Settings);

    /* Mask the partition configuration data with 0x0C to get the memory type */
    MemoryType = MMU_Settings[3] & 0x0C;

    /* Mask the partition configuration data with 0xF0 to get the memory access */
    PartitionMemorySpace = MMU_Settings[3] & 0xF0;

    /* If the partition is already in DATA space then we dont need to unify it */
    if ((PartitionMemorySpace == 0x40) | (PartitionMemorySpace == 0x50))
    {	
        SW1SW2 = SW1SW2_OK;
//        SW1SW2 |= MemoryType;
    }
    else
    {
        /******************************************************************/
        /* Set the configuration for Partition0 as:                       */
        /*     unified with read/write/execute access (bit 5 & 6 - 0x60)  */
        /*     active in kernel mode (bit 0 - 0x01)                       */
        /******************************************************************/
        MMU_Settings[3] = MemoryType ^ 0x61;

        /* Actual firmware API call */
        Firmware_SetMMU (0, MMU_Settings);

        SW1SW2 = SW1SW2_OK;
//        SW1SW2 |= MemoryType;
    }

    return SW1SW2;

} /* End of function */

/******************************************************************************
*
* Function Name:      Removed_Unified_Partition0_From_DATA_Space
* Function Inputs:    void
* Function Outputs:   uint SW1SW2_OK
* Description:        Removes partiton 0
*
* APDU Syntax:        E5 38 00 00 00
* APDU Inputs:        None
* APDU Outputs:       None

* Example usage:      Remove Partition 0
* To Card             ->  E5 38 00 00 00
* ACK from Card       <-  38
* Response from Card  <-  90 00
*
******************************************************************************/
uint Removed_Unified_Partition0_From_DATA_Space (void)
{
    uchar idata MMU_Settings[4];

    MMU_Settings[0] = 0;
    MMU_Settings[1] = 0;
    MMU_Settings[2] = 0;
    MMU_Settings[3] = 0;

    /* Actual firmware API call */
    Firmware_SetMMU (0, MMU_Settings);

    return SW1SW2_OK;

} /* End of function */
