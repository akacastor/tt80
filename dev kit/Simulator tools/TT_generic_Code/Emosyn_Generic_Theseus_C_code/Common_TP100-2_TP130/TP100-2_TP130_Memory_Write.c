/******************************************************************************
*
* Name:         TP100-2_TP130_Memory_Write.c
* Description:  EEPROM writing functions
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
; $Revision: 1.4 $
; $Author: chin $
; $Date: 2005/10/25 11:23:02 $
******************************************************************************/

/* Header file inclusions */
#include "Firmware_API_JumpTable.h"
#include "Emosyn_Helper_Functions.h"

/* External and local function declarations */
char Theseus_EEPROM_Write (uint EEPROM_Address, uchar *Source_Address, uint Length, uchar Mode);

/* External and local variables  */

#define Memory_Buffer_Mode 0 /* Buffer contains bytes to write */
#define Fixed_Data_Mode 1    /* The same byte is to be written repetively */


/********************************************************************************************************
 * Note
 * ----
    The below code assumes that the EEPROM is mapped into DATA space. If you try and write to EEPROM in
    CODE space then the code will fail. The memory you want to write to HAS to be mapped into DATA space.
    If not, there are functions (commented out) below that will handle mapping the MMU partitions into
    DATA space so that you can write to the memory.
*********************************************************************************************************/


/******************************************************************************
*
* Function Name:      Write_X_Bytes_To_EEPROM
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or
*                                  6581h for memory failure or
*                                  6700h for wrong LC
* Description:        Writes an input stream to EEPROM, writes in Flash mode if
*                     possible, if not it handles the EEPROM page erases.
*                     Example call demonstrates the usage of the
*                     Theseus_EEPROM_Write function in memory buffer mode
*
* APDU Syntax:        E5 70 PARA1 PARA2 PARA3
* APDU Inputs:        PARA1  High byte of the EEPROM address space of data
*                     PARA2  Low byte of the EEPROM address space of data
*                     PARA3  Number of bytes to write
*                     DATAX  Bytes to write to EEPROM
* APDU Outputs:       None
*
* Example usage:      Write sequential sequence bytes to 6000h in EEPROM
* To Card             ->  E5 70 60 00 08
* ACK from Card       <-  70
* Data from Card      ->  01 02 03 04 05 06 07 08
* Response from Card  <-  90 00
*
******************************************************************************/
uint Write_X_Bytes_To_EEPROM (void)
{
    char cFunctionReturn = 0;
    uint  uiNumber_To_Write;
    uint  uiAddress;
    uchar ucTemp_Buffer[16];
    uchar ucCounter;

    if (PARA3 > 16) /* If the length of data expected is bigger than buffer exit with error */
    {
        SW1SW2 = SW1SW2_WRONG_LC_LENGTH;
    }

    else
    {
        uiAddress = PARA1 << 8;
        uiAddress = uiAddress | PARA2;

        uiNumber_To_Write = PARA3;

        for (ucCounter = 0; ucCounter < PARA3; ucCounter++)
        {
            ucTemp_Buffer[ucCounter] = GetChar();
        }

        cFunctionReturn = Theseus_EEPROM_Write (uiAddress, ucTemp_Buffer, uiNumber_To_Write, Memory_Buffer_Mode); 

        if (cFunctionReturn < 0x00)
        {
            SW1SW2 = SW1SW2_MEMORY_ERROR;
        }
        else
        {
            SW1SW2 = SW1SW2_OK;
        }
    }

    return SW1SW2;

} /* End of function */


/******************************************************************************
*
* Function Name:      Fill_EEPROM_With_Byte
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or
*                                  6581h for memory failure or
*                                  6700h for wrong LC
* Description:        Writes specified EEPROM area with byte
*
* APDU Syntax:        E5 76 PARA1 PARA2 PARA3
* APDU Inputs:        PARA1  High byte of the EEPROM address space of data
*                     PARA2  Low byte of the EEPROM address space of data
*                     PARA3  3 data bytes following
*                     DATA1  Byte to write to EEPROM
*                     DATA2  High byte of the EEPROM address to write to
*                     DATA3  Low byte of the length to write
* APDU Outputs:       None
*
* Example usage:      Write 55h pattern across EEPROM staring at 6000h to 6040h
*                     (0040h length)
* To Card             ->  E5 76 60 00 03
* ACK from Card       <-  76
* Data to Card        ->  55 00 40
* Response from Card  <-  90 00
*
******************************************************************************/
uint Fill_EEPROM_With_Byte (void)
{
    char cFunctionReturn = 0;
    uint  uiLength;
    uint  uiAddress;
    uchar ucByte_To_Fill_With;

    /* Check that only 3 data bytes are to be received otherwise exit with error */
    if (PARA3 > 3)
    {
        SW1SW2 = SW1SW2_WRONG_LC_LENGTH;
    }

    else
    {
        uiAddress = PARA1 << 8;
        uiAddress = uiAddress | PARA2;

        ucByte_To_Fill_With = GetChar();    /* 1st data byte */

        uiLength = GetChar();               /* 2nd data byte */
        uiLength = uiLength << 8;
        uiLength = uiLength + GetChar();    /* 3rd data byte */

        cFunctionReturn = Theseus_EEPROM_Write (uiAddress, &ucByte_To_Fill_With, uiLength, Fixed_Data_Mode);

        if (cFunctionReturn < 0x00)
        {
            SW1SW2 =  SW1SW2_MEMORY_ERROR;
        }
        else
        {
            SW1SW2 =  SW1SW2_OK;
        }
    }

    return SW1SW2;

} /* End of function */


/******************************************************************************
*
* Function Name:      Theseus_EEPROM_Write
* Function Inputs:    uint EEPROM_Address
*                     uchar *Source_Address
*                     uint Length
*                     uchar Mode
* Function Outputs:   char ReturnValue - Either success (0) or fail (<0)
* Description:        Write to EEPROM function
*                     Fills EEPROM with a byte or writes a memory buffer to EEPROM
*                     Write in Flash mode, if not it will handle the page erases
*
*******************************************************************************/
char Theseus_EEPROM_Write (uint EEPROM_Address, uchar *Source_Address, uint Length, uchar Mode)
{
    uint Temp_Counter = 0;
    uchar Temp_buffer[14];				/* Maximum of 14 bytes to back up as if we are writing 2 new */
                                        /* bytes that fall on a 2 page boundaries (16-2)  bytes remain */
    char ReturnValue;

    uint Temp_Address, Counter;
    uchar xdata *Temp_EEPROM_Address;
    uchar *Temp_Source_Address;
    uchar Input_Data = *Source_Address;

    uchar ExistingByte;
    uchar ByteToWrite;
    
	uchar Number_To_Backup_Before_New_Data;
    uchar Number_To_Backup_After_New_Data;
	
    uchar WeNeedToErasePageFirst = 0;

    uchar xdata *ucpTempPointer;

    /* We are using WriteByteEE instead of the WriteEE as WriteEE requires that */
    /* data to be written to be stored in IDATA. WriteByteEE has the byte to be */
    /* written passed in R5. This way C can pass any type of pointer into this function */

    Temp_EEPROM_Address = EEPROM_Address;
    Temp_Source_Address = Source_Address;


    /******************************************************************************/
    /* First check if there is any data to be written that will change the EEPROM */
    /* memory from a bit from 0 to 1                                              */	
    /* If any transistions are detected from 0 to 1 a page erase will be required */
    /* Otherwise the data can be written diretly with no page erases              */
    /******************************************************************************/
    for (Counter = 0; Counter < Length; Counter++)
    {
        ExistingByte = *Temp_EEPROM_Address++;
        ByteToWrite = *Temp_Source_Address++;

        if ((~ExistingByte) & ByteToWrite) /* 0 -> 1 transistions require page erase first */
        {
            WeNeedToErasePageFirst = 1;    /* Flag that a page erase is required to write the data */
            break;
        }
    }

    /* Here we know if we need to erase the memory prior to writing */
    /* If we need to erase (WeNeedToErasePageFirst==1) else WeNeedToErasePageFirst==0 */
    Temp_EEPROM_Address = EEPROM_Address;
    Temp_Source_Address = Source_Address;	

    /***************************************************************************************/
    /* The following for loop will write the data to EEPROM if no page erasing is required */
    /***************************************************************************************/
    if (!WeNeedToErasePageFirst)
    {
        for (Counter = 0; Counter < Length; Counter++)
        {
            if (Mode == Fixed_Data_Mode)   /* Write a block of the same data byte */
            {
                ReturnValue = Firmware_WriteByteEE (EEPROM_Address++, Input_Data);
            }
            else   /* Write from the buffer to memory */
            {
                ReturnValue = Firmware_WriteByteEE ((uint)Temp_EEPROM_Address + Counter, * Temp_Source_Address ++);
            }

            if (ReturnValue < 0x00) /* If the firmware write byte returned an error, exit now */
                break;
        }

        return (ReturnValue);
    }
    else
    {
        /**************************************************************************************
        * The code below is executed if any data to be written causes a bit 0 to 1 transistion
		* Data that is not changing needs to be backed up first, the page(s) can then be erased
        * The non-changing data and new data can then be written
        ***************************************************************************************/

        /*******************************************************************************************
        * Example Code usage.
        *
        * 4020h                           4028h
        *   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
        *   |                               |                               |
        *   |   Existing 8 Byte Page A      |   Existing 8 Byte Page B      |
        *   |   at address 4020h            |   at address 4028h            |
        *   |                               |                               |
        *   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
        *
        *         4022h
        *           |---|---|---|---|---|---|---|---|
        *           |                               |   Bytes at 4020h, 4021h (before new data) &
        *           |       New data to write       |   402Bh, 402Ch, 402D, 402Eh & 402Fh
        *           |       at address 4022->402A   |   (after new data)need to be backed up first
        *           |                               |
        *           |---|---|---|---|---|---|---|---|
        *
        * To backup the 2 existing pages correctly we need to know how many bytes of each to backup
        *******************************************************************************************/

        /* Calculate how much data we need to backup */
        Temp_Address = EEPROM_Address;

        /* Page align the EEPROM address. This gives us the start of data that needs to be backed up */
		Temp_EEPROM_Address = (Temp_Address & 0xFFF8);

        /* Find the number of bytes to backup BEFORE the start of the new data */
        /* In the example above this is 2. 4020h and 4021h will not change */
        Number_To_Backup_Before_New_Data = Temp_Address & 0x07;

        /* Find the number of bytes to backup AFTER the start of the new data */
        /* In the example above this is 6. 402Bh -> 402Fh will not change */
		Number_To_Backup_After_New_Data =(0x08 - ((Temp_Address + Length) & 0x07)) & 0x07;

        /* Backup all the necessary data */
        for (Counter = 0; Counter < (Number_To_Backup_Before_New_Data + Number_To_Backup_After_New_Data); Counter++)
        {
            if (Counter < Number_To_Backup_Before_New_Data) /* backup data in page before new data */
            {
                Temp_buffer[Counter] = *(Temp_EEPROM_Address + Counter);
            }
            else
            {   /* backup data in page after new data */ 
                ucpTempPointer = EEPROM_Address + Length + Temp_Counter++; 
                Temp_buffer[Counter] = *ucpTempPointer;
            }
        }

        Temp_Counter = 0;
        Temp_Source_Address = Source_Address;


        /*************************************************************
        * The code below loops round performing one of the following:
        *  : erase an EEPROM page
        *  : write data before new data
        *  : write data after new data
        *  : write new data
        *************************************************************/
        for (Counter = 0; Counter < (Length + Number_To_Backup_Before_New_Data + Number_To_Backup_After_New_Data); Counter++)
        {
            /* Do we need to erase a page of memory on this loop */
            if ((Counter % 8) == 0)
            {
                /* Erase the EEPROM page (8 bytes) */
                Firmware_EraseEE8Bytes ((uint)Temp_EEPROM_Address + Counter);
            }
            if (Counter < Number_To_Backup_Before_New_Data)
            {
                /* Write back the existing data thats before the new data */
                ReturnValue = Firmware_WriteByteEE((uint)Temp_EEPROM_Address + Counter, Temp_buffer[Counter]);
            }
            else if (Counter < Number_To_Backup_Before_New_Data + Length)
            {   /* Write the new data to EEPROM */
                if (Mode == Fixed_Data_Mode)
                {    /* Write a block of the same data byte */
                    ReturnValue = Firmware_WriteByteEE (EEPROM_Address++, Input_Data);
                }
                else
                {    /* Write from the buffer to memory */
                    ReturnValue = Firmware_WriteByteEE ((uint)Temp_EEPROM_Address + Counter, *Temp_Source_Address ++);
                }
            }
            else	
            {   /* Write back the existing data after the new data */
                ReturnValue = Firmware_WriteByteEE ((uint)Temp_EEPROM_Address + Counter, Temp_buffer[Number_To_Backup_Before_New_Data + Temp_Counter++]);
            }

            if (ReturnValue < 0x00)
                break;

        } /* End For loop */

        return ReturnValue;
    } /* End ELSE statement using erase */

} /* End of function */