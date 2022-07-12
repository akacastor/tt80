/******************************************************************************
*
* Name:         Write_Byte_UCM_Extended_Addressing.c
* Description:  Contains function to write a byte to UCM memory
*               This function allows byte writes over the normal 64k boundary
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
* $Author: chin $ 
* $Date: 2006/03/08 16:21:59 $
******************************************************************************/


/******************************************************************************
* Header file inclusions
******************************************************************************/
#include "Firmware_API_JumpTable.h"
#include "Emosyn_Helper_Functions.h"


/******************************************************************************
* External and local function declarations 
******************************************************************************/
#define CONFIGPAGE1		0x12000 //0xfc00

typedef struct {
	unsigned char	ConfigData[1024];//[512];

	}tCONFIGP1;
// Allocate the Config structure to the end of EEPROM...
tCONFIGP1 far gCONFIGP1 _at_ CONFIGPAGE1;

unsigned char idata ConfigWriteBuff[12];
void WriteConfig(unsigned long dest_addr,char idata *source_addr, char num_of_bytes);


/******************************************************************************
* External variable declarations
******************************************************************************/


/******************************************************************************
*
* Function Name:      Write_Byte_UCM_Extended_Addressing
* Function Inputs:    void 
* Function Outputs:   uint SW1SW2  9000h for success or
*                                  6581h for memory failure or
*                                  6700h for wrong LC
* Description:        Writes a byte to UCM memory
*
* APDU Syntax:        E5 A8 00 00 04
* APDU Inputs:        DataByte1  DPX address byte
*                     DataByte2  DPH address byte
*                     DataByte3  DPL address byte
*                     DataByte4  Byte to write
* APDU Outputs:       None
*
* Example usage:      Write 55h to UCM address 010203h
* To Card             ->  E5 A8 00 00 04
* ACK from Card       <-  A8
* Data to Card        ->  01 02 03 55
* Response from Card  <-  90 00
*
******************************************************************************/
uint Write_Byte_UCM_Extended_Addressing (void)
{




//    if (PARA3 == 0x04)
//    {
        /* Get 3 byte address */
        /* Need to pass pointer to first byte of far pointer */
//        Serial_Receive_X_Bytes (0x03, (unsigned char idata*)&uc_Fptr);

        /* Get actual byte to write */
//        ucByte_To_Write = GetChar();

        /* Actual firmware API call */
//        cRet_Val_Char = Firmware_WriteByteUCM (uc_Fptr, ucByte_To_Write);

        /* Check the firmware call result */
//        if (MSB_SET & cRet_Val_Char)
//        {
//            SW1SW2 = SW1SW2_MEMORY_ERROR;   /* If MSB of return value set it */
//        }                                   /* indicates a memory operation error */
//        else
//        {
//            SW1SW2 = SW1SW2_OK;         /* Firmware return value was 0 or the number */
//        }                               /* of pulses required for memory operation */
//    }

//    else
//    {
//        SW1SW2 = SW1SW2_WRONG_LC_LENGTH;    /* Wrong amount of input bytes */
//    }




		// Write MF vector table...
		ConfigWriteBuff[0] = 0x3F;
/*		HiByte(0x3f00);
		ConfigWriteBuff[1] = LoByte(0x3f00);
		ConfigWriteBuff[2] = HiByte(0xffff);
		ConfigWriteBuff[3] = LoByte(0xffff);
		ConfigWriteBuff[4] = HiByte((int)&gEEPROM.MFHeader);
		ConfigWriteBuff[5] = LoByte((int)&gEEPROM.MFHeader);
		 Write EFKi vector table...
		ConfigWriteBuff[6] = HiByte(0x3f00);
		ConfigWriteBuff[7] = LoByte(0x3f00);
		ConfigWriteBuff[8] = HiByte(gEEPROM.EFKiHeader.FileID);
		ConfigWriteBuff[9] = LoByte(gEEPROM.EFKiHeader.FileID);
		ConfigWriteBuff[10] = HiByte((int)&gEEPROM.EFKiHeader);
		ConfigWriteBuff[11] = LoByte((int)&gEEPROM.EFKiHeader);
  */
		WriteConfig((unsigned char *)&gCONFIGP1,
							ConfigWriteBuff,sizeof(ConfigWriteBuff));


    return SW1SW2;

} /* End of function */



/**************************************************************************************************
				Write to config( destination, source, length) 
***************************************************************************************************/
//void WriteConfig(int dest_addr,char idata *source_addr, char num_of_bytes)
void WriteConfig(unsigned long dest_addr,char idata *source_addr, char num_of_bytes)
{
unsigned char i;

#ifdef TT80
	for(i=0;i<num_of_bytes;i++) Firmware_WriteByteUCM(dest_addr+i,*(source_addr+i) );
#endif
	
#ifdef TT120
unsigned char far *uc_Fptr;
	
	for(i=0;i<num_of_bytes;i++)
	{
		uc_Fptr = (unsigned char far *)(dest_addr+i);
		Firmware_WriteByteUCM(uc_Fptr,*(source_addr+i) );
	}
#endif

}


