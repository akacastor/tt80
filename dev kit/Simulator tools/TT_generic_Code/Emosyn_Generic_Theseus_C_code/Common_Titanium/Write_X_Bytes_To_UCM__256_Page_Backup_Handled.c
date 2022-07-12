/******************************************************************************
*
* Name:         Write_X_Bytes_To_UCM__256_Page_Backup_Handled.c
* Description:  Contains function that writes an input stream of data to UCM
*               Backing up data and page erasing is handled within this function
*               This function only works with UCM pages 256 bytes in size
*               This function uses backup pages defined in the
*               Firmware_API_JumpTable.h file in each individual chip directory
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
; $Revision: 1.2 $
; $Author: chin $
; $Date: 2006/02/22 15:51:21 $
******************************************************************************/

/* Header file inclusions */
#include "Firmware_API_JumpTable.h"
#include "Emosyn_Helper_Functions.h"

/* External and local function declarations */


/* External and local variables  */
char bdata ucTemp_Page_Status;              /*  Variable to hold status bits */

/* These bit variables state whether data needs to be backed up */
sbit bData_Present_Before_New_Data_Temp_Page1 = ucTemp_Page_Status^0;
sbit bData_Present_After_New_Data_Temp_Page1 = ucTemp_Page_Status^1;
sbit bData_Present_After_New_Data_Temp_Page2 = ucTemp_Page_Status^2;
sbit bTwo_Page_Erase_Needed = ucTemp_Page_Status^3;


/******************************************************************************
*
* Function Name:      Write_X_Bytes_To_UCM__Page_Backup_Handled
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or
*                                  6581h for memory failure or
* Description:        Writes an input stream to UCM space
*                     Function handles any data backup and page erases required
*
* APDU Syntax:        E5 E4 PARA1 PARA2 PARA3
* APDU Inputs:        PARA1  High byte of the UCM address to write to
*                     PARA2  Low byte of the UCM address to write to
*                     PARA3  Number of bytes to write
*                     DATAX  Bytes to write to UCM
* APDU Outputs:       None
*
* Example usage:      Write 16 bytes of data to 50F8h in UCM
* To Card             ->  E5 E4 5F F8 10
* ACK from Card       <-  E4
* Data from Card      ->  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
* Response from Card  <-  90 00
*
* Example Code usage.
*
* 5000h                           5100h                           5200h
*   |---------------------------------------------------------------|
*   |                               |                               |
*   |   Existing 256 Byte Page A    |   Existing 256 Byte Page B    |
*   |   at address 5000h            |   at address 5100h            |
*   |                               |                               |
*   |---------------------------------------------------------------|
*                    50F8h                      5107h  
*                      |--------------------------|
*                      |                          |
*    5000h -> 50F7h    |   New data to write      |  51080h -> 51FFh
*   must be backed up  | at address 50F8 -> 5107h | must be backed up
*                      |                          |
*                      |--------------------------|
*
* If the new data to be written to 50F8h -> 5108h differs from the current
* data held in that address range (e.g. there is a 0 -> 1 transision) it means
* data from 5000h -> 50F7h and 5108 ->51FF must be backed up.
* The chip can then erase the 2 256 byte pages (5000h and 5100h) and then copy
* back the backed up data and then the new data
*
* This function uses backup pages defined in the Firmware_API_JumpTable.h file
* in each individual chip directory
******************************************************************************/
uint Write_X_Bytes_To_UCM__256_Page_Backup_Handled (void)
{
    uint idata uiStart_Address;                     /* Variable to hold start address of new data */
    uint idata uiTemp_Page_Address;                 /* Variable to hold address in the backup page */ 
    uint idata uiEnd_Address;                       /* Variable to hold end address of the new data */
    uchar idata ucTemp_Page1_Before_Data_Count;     /* Variable to hold number of bytes to copy before new data in Page1 */
    uchar idata ucTemp_Page1_After_Data_Count;      /* Variable to hold number of bytes to copy after new data in Page1 */
    uchar idata ucTemp_Page2_After_Data_Count;      /* Variable to hold number of bytes to copy after new data in Page2 */
    uchar xdata *ucByte_To_Write_Data_Ptr;          /* Variable to hold data to write */
    uint idata uiCount;                             /* Variable to hold integer counter */

    ucTemp_Page_Status = 0x00;                      /* Initialisation of variables */
    cRet_Val_Char = 0x00;                           /* Declaed in global_vars.h */
    ucCount = 0x00;
    uiCount = 0x00;

    uiStart_Address = PARA1 << 8;                   /* Convert input address into an integer */
    uiStart_Address |= PARA2;

    uiTemp_Page_Address = uiStart_Address & 0x00FF; /* Find the address with offset in the backup page */
    uiTemp_Page_Address += PAGE1_BACKUP_START_ADDRESS;

    uiEnd_Address = uiStart_Address + PARA3;        /* Calculate the end address of the new data */


    /******************************/
    /* Clear out the backup pages */
    /******************************/
    cRet_Val_Char = Firmware_EraseUCM512Bytes (PAGE1_BACKUP_START_ADDRESS);


    /*****************************************************************************/
    /* Write the new data to the backup page(s)                                  */
    /*****************************************************************************/
    if (!(cRet_Val_Char & MSB_SET))
    {
        for (ucCount = 0; ucCount < PARA3; ucCount++)
        {
            /* Write the byte to the corresponding address in the backup page */
            cRet_Val_Char = Firmware_WriteByteUCM (uiTemp_Page_Address++, GetChar());

            if (cRet_Val_Char & MSB_SET)
            {
                break;
            }
	    }
    }


    /********************************************************************************/
    /* Calculate: whether the new data falls across the boundaries of 2 pages       */
    /*          : how much old data needs to be copied before the new data in Page1 */ 
    /*          : how much old data needs to be copied after the new data in Page1  */
    /*          : how much old data needs to be copied after the new data in Page2  */
    /********************************************************************************/

    if (!(cRet_Val_Char & MSB_SET))
    {
        /* Check if the new data covers memory in both page1 and page2 */
        if ((uiStart_Address + PARA3) > ((uiStart_Address + 0x100) & 0xFF00))
        {
            /* Check if the new data goes up to page2 end boundary */
            if ((uiStart_Address + PARA3) < ((uiStart_Address + 0x200) & 0xFF00))
            {    
                ucTemp_Page2_After_Data_Count = ((uiStart_Address + 0x200) & 0xFF00) - (uiStart_Address + PARA3);
                bData_Present_After_New_Data_Temp_Page2 = 1;
                bTwo_Page_Erase_Needed = 1;
            }
    	}

        /* Check if the new data starts after the page1 start boundary */
        if (uiStart_Address > (uiStart_Address & 0xFF00))
        {
            ucTemp_Page1_Before_Data_Count = uiStart_Address - (uiStart_Address & 0xFF00);
            bData_Present_Before_New_Data_Temp_Page1 = 1;
    	}

        /* Check if there is any old data to copy over in page1 at the end of the new data */
        if ((uiStart_Address + PARA3) < ((uiStart_Address + 0x100) & 0xFF00))
        {
            ucTemp_Page1_After_Data_Count = ((uiStart_Address + 0x100) & 0xFF00) - (uiStart_Address + PARA3);
            bData_Present_After_New_Data_Temp_Page1 = 1;
        }
    }

    /******************************************************************************/
    /* Copy across old data before and after the new data into the temp page(s)   */
    /******************************************************************************/

    if (!(cRet_Val_Char & MSB_SET))
    {
        /* Copy in old data from page1 before new data */
        if (bData_Present_Before_New_Data_Temp_Page1)
        {
            /* Reset start address to page1 start */
            ucByte_To_Write_Data_Ptr = uiStart_Address & 0xFF00;
            uiTemp_Page_Address = PAGE1_BACKUP_START_ADDRESS;

            /* Copy across unchanged old data that is before the new data into page1 */
            for (ucCount = 0; ucCount < ucTemp_Page1_Before_Data_Count; ucCount++)
            {
                cRet_Val_Char = Firmware_WriteByteUCM (uiTemp_Page_Address++, *ucByte_To_Write_Data_Ptr++);

                if (cRet_Val_Char & MSB_SET)
                {
                    break;
                }
            }
    	}
    }

    if (!(cRet_Val_Char & MSB_SET))
    {
        /* Copy in old data from page1 after the new data */
        if (bData_Present_After_New_Data_Temp_Page1)
        {
            /* Point the start address to the end of the new data */
            uiTemp_Page_Address = (uiEnd_Address & 0x00FF) + PAGE1_BACKUP_START_ADDRESS;
            ucByte_To_Write_Data_Ptr = uiEnd_Address;

            /* Copy across unchanged old data that is after the new data into page1 */
            for (ucCount = 0; ucCount < ucTemp_Page1_After_Data_Count; ucCount++)
            {
                cRet_Val_Char = Firmware_WriteByteUCM (uiTemp_Page_Address++, *ucByte_To_Write_Data_Ptr++);

                if (cRet_Val_Char & MSB_SET)
                {
                    break;
                }
            }
        }
    }

    if (!(cRet_Val_Char & MSB_SET))
    {
        /* Copy in old data from page2 after new data */
        if (bData_Present_After_New_Data_Temp_Page2)
        {
            /* Reset start address to page2 start address */
            uiTemp_Page_Address = (uiEnd_Address & 0x00FF) + PAGE2_BACKUP_START_ADDRESS;
            ucByte_To_Write_Data_Ptr = uiEnd_Address;

            /* Copy across unchanged old data that is after the new data into page2 */
            for (ucCount = 0; ucCount < ucTemp_Page2_After_Data_Count; ucCount++)
            {
                cRet_Val_Char = Firmware_WriteByteUCM (uiTemp_Page_Address++, *ucByte_To_Write_Data_Ptr++);

                if (cRet_Val_Char & MSB_SET)
                {
                    break;
                }
            }
        }
    }


    /******************************************************************************/
    /* Erase original UCM page(s)                                                 */
    /******************************************************************************/
    if (!(cRet_Val_Char & MSB_SET))
    {
        if (bTwo_Page_Erase_Needed)
        {
            cRet_Val_Char = Firmware_EraseUCM512Bytes (uiStart_Address & 0xFF00);
        }
        else    /* Just erase 1 page if the new data was all contained within a page */
        {
             cRet_Val_Char = Firmware_EraseUCM256Bytes (uiStart_Address & 0xFF00);
        }
    }

    /**********************************************************************************/
    /* Reset the address start to the start of the UCM page and point to the new data */
    /**********************************************************************************/
   	uiStart_Address &= 0xFF00;
    ucByte_To_Write_Data_Ptr = PAGE1_BACKUP_START_ADDRESS;

    if (!(cRet_Val_Char & MSB_SET))
    {
        /* Copy over page1 data (this includes old data and new data) */       
        for (uiCount = 0; uiCount < 0x100; uiCount++)
        {
            cRet_Val_Char = Firmware_WriteByteUCM (uiStart_Address++, *ucByte_To_Write_Data_Ptr++);
        }
    }

    if (!(cRet_Val_Char & MSB_SET))
    {
        /* Copy over page2 data (old data and new data) if requried */
        if (bTwo_Page_Erase_Needed)
        {
            /* Copy over page1 data (this includes old data and new data) */    
            for (uiCount = 0; uiCount < 0x100; uiCount++)
            {
                cRet_Val_Char = Firmware_WriteByteUCM (uiStart_Address++, *ucByte_To_Write_Data_Ptr++);
            }
        }
    }

    if (cRet_Val_Char & MSB_SET)
    {
        /* Report a memory error if any firmware functions failed */
        SW1SW2 = SW1SW2_MEMORY_ERROR;
    }
    else
    {
        SW1SW2 = SW1SW2_OK;
    }

    return SW1SW2;

} /* End of function */