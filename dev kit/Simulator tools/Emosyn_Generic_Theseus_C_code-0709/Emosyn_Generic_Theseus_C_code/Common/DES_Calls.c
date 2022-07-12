/*
;********************************************************************************************************
;
; Name:			DES_Calls.c
; Description:	Commands to access the Emosyn DES and DES3 algorithm's
; Copyright:	Emosyn Inc. 2005
; 
;********************************************************************************************************
; The Example Code hereinbelow is provided "AS IS" and at your sole risk.  
; As to this Code, EMOSYN expressly disclaims all Warranties, including, but not limited to the implied 
; warranties of merchantability and fitness for a particular purpose. EMOSYN does not warrant that the 
; functions contained in this code will meet your requirements, or that the operation of the code will 
; be accurate, error-free, or non-infringing.  No oral or written information or advice given by EMOSYN 
; or an authorized representative shall create or affect any Warranty.
;********************************************************************************************************
; $Revision: 1.1 $
; $Author: chin $ 
; $Date: 2005/08/09 11:53:42 $
;********************************************************************************************************
*/

/* Header file inclusions */
#include "Firmware_API_JumpTable.h"
#include "Emosyn_Helper_Functions.h"

#include "DES_Jumptable.h"
#include "DES3_Jumptable.h"

/* External and local function declarations */

/* External and local variables  */

extern unsigned char xdata IO_Buffer[0x40];
extern unsigned char xdata Algo_XDATA_Buffer[128];

unsigned char idata Output[8] _at_ 0x28; /* The DES output uses IDATA addresses 0x28 -> 0x2F */
unsigned char idata Key[8] _at_ 0x20;    /* The DES Key uses IDATA addresses 0x20 -> 0x27 */
DES3_Parameters xdata DES3_Param;        /* Create a DES3_Parameters structure */

unsigned char idata Data_for_DES[8];

unsigned char xdata TDES_Key[24];
unsigned char xdata TDES_Padding[8]= {0x80, 0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00};
unsigned char xdata TDES_ICV3[8]; 

/********************************************************************************************************
; Function   : unsigned char Call_DES (void)
; Description: Read 8 bytes of data from the serial port
;            : encrypt/decrypt them using Single DES
;            : writes the result to the IO buffer
*********************************************************************************************************
;
; Command Syntax
;
;       E5 80 00 Para2 08
;
; Inputs
;       Para2			0x0E for DES encryption
;                       0x0D for DES decryption
;       DataByte 0~7    Data to encrypt/decrypt
;
; Outputs			
;       8 bytes of Encrypted/Decrypted data into Transmit buffer
;
; Example usage 1: Encrypt 00 00 00 00 00 00 00 00
;                : use preloaded DES key of 00 00 00 00 00 00 00 00 
; 
;       To Card           ->    E5 80 00 0E 08
;       ACK from Card     <-    80
;       Data to Card      ->    00 00 00 00 00 00 00 00
;       Data from Card    <-    61 08
;
;       Get Response cmd  ->    E5 C0 00 00 08
;       Data from Card    <-    8C A6 4D E9 C1 B1 23 A7
;       Data from Card    <-    90 00
;
;
; Example usage 2: Decrypt 8C A6 4D E9 C1 B1 23 A7
;                : use preloaded DES key of 00 00 00 00 00 00 00 00 
;
;       To Card           ->    E5 80 00 0D 08
;       ACK from Card     <-    80
;       Data to Card      ->    8C A6 4D E9 C1 B1 23 A7
;       Data from Card    <-    61 08
;
;       Get Response CMD  ->    E5 C0 00 00 08
;       Data from Card	  <-    00 00 00 00 00 00 00 00
;       Data from Card    <-    90 00
;
;********************************************************************************************************/
unsigned int Call_DES (void)
{
    TEMPVARIABLE1 = 0x00;

    for (TEMPVARIABLE1 = 0; TEMPVARIABLE1 < 8; TEMPVARIABLE1++)
		Data_for_DES[TEMPVARIABLE1] = GetChar(); /* Get the 8 bytes to process */

	  	TheseusPlatinum_DES (Data_for_DES, Algo_XDATA_Buffer, PARA2);

	for (TEMPVARIABLE1 = 0; TEMPVARIABLE1 < 8; TEMPVARIABLE1++)
		IO_Buffer[TEMPVARIABLE1] = Output[TEMPVARIABLE1]; /* Write the output to the Transmit buffer */

    return 0x6108;    
}


/********************************************************************************************************
; Function   : Call_3DES
; Description: Read X bytes of data from the serial port
;            : encrypt/decrypt bytes using Triple DES
;            : write the result to the IO buffer
;********************************************************************************************************
;
; Command Syntax
;
;       E5 86 Para1 Para2 XX 
;
; Inputs
;       Para1    0x0E for ECB mode
;                0x0C for CBC mode
;
;       Para2    0x0E for DES encryption
;                0x0D for DES decryption
;
;       DataByte 0->XX DataToEncryptOrDecrypt[XX]
;       Max(XX)= 0x40 due to IO_Buffer limitation
;
; Outputs			
;       61XX
;
;********************************************************************************************************/
unsigned int Call_3DES (void)
{
    if (PARA2 == 0x0E && PARA3 == 0)
    {
        SW1SW2 = SW1SW2_WRONG_LC_LENGTH; /* Cannot encrypt if no following data */
    }
    else
    {
        if (PARA2 == 0x0D && PARA3 % 0x08 != 0)
        {
            for (TEMPVARIABLE1 = 0;TEMPVARIABLE1 < PARA3; TEMPVARIABLE1++)
                IO_Buffer[TEMPVARIABLE1]= GetChar();

            SW1SW2 = SW1SW2_WRONG_LC_LENGTH;
        }
        else
        {
            for (TEMPVARIABLE1 = 0; TEMPVARIABLE1 < PARA3; TEMPVARIABLE1++)
                IO_Buffer[TEMPVARIABLE1] = GetChar();

            DES3_Param.Data_Starting_Address = IO_Buffer;     /* DES3 vector to encrypt or Decrypt */
            DES3_Param.Data_Length = PARA3;                   /* length of data to encrypt/Decrypt */
            DES3_Param.ICV = TDES_ICV3;                       /* ICV */
            DES3_Param.Padding = TDES_Padding;                /* Padding */
            DES3_Param.Mode = PARA1;                          /* ECB or CBC */
            DES3_Param.Encrypt_Decrypt = PARA2;               /* encrypt (ox0E) or decrypt (0x0D) */
            DES3_Param.Algo_XDATA_Buffer = Algo_XDATA_Buffer; /* 128 bytes xdata buffer */
            DES3_Param.Key24= TDES_Key;                       /* 24 bytes 3DES key */
            DES3_Param.DES_Input = Data_for_DES;

            TEMPVARIABLE1 = TheseusPlatinum_DES3 (&DES3_Param);
						
            SW1SW2 = 0x6100;
            SW1SW2 |= TEMPVARIABLE1;
        }
    }

    return SW1SW2;
} /* End of 3DES function */


/********************************************************************************************************
; Function   : Load DES_KEY
; Description: Load 8, 16 or 24 byte key for DES or Triple DES encryption/decryption
;********************************************************************************************************
;
; Command Syntax
;
;       E5 82 00 00 xx Key[xx]
;       XX = 0x08 or 0x10 or 0x18
;
; Inputs
;       Key to use for DES or 3DES encryption
;
; Outputs			
;       SW1SW2
;
;********************************************************************************************************/
unsigned int Load_DES_Key (void)
{
    if ((PARA3 != 0x08) && (PARA3 != 0x10) && (PARA3 != 0x18))
    {
        /* accept the data then report len error */
        for (TEMPVARIABLE1 = 0; TEMPVARIABLE1 < PARA3; TEMPVARIABLE1++)
            TDES_Key[TEMPVARIABLE1] = GetChar();

        SW1SW2 = SW1SW2_WRONG_LC_LENGTH;
    }
    else
    {
        if (PARA3 == 0x08)
        {
            for (TEMPVARIABLE1 = 0; TEMPVARIABLE1 < 8; TEMPVARIABLE1++)
                Key[TEMPVARIABLE1] = GetChar();
        }

        if (PARA3 == 0x10)
        {
            for (TEMPVARIABLE1 = 0; TEMPVARIABLE1 < 16; TEMPVARIABLE1++)
                TDES_Key[TEMPVARIABLE1] = GetChar();
	
            /* repeat 1st 8 bytes for last 8 bytes of 24 byte key */
            for (TEMPVARIABLE1 = 16; TEMPVARIABLE1 < 24; TEMPVARIABLE1++)
                TDES_Key[TEMPVARIABLE1] = TDES_Key[TEMPVARIABLE1 - 16];
        }

        if (PARA3 == 0x18)
        {
            for (TEMPVARIABLE1 = 0; TEMPVARIABLE1 < 24; TEMPVARIABLE1++)
                TDES_Key[TEMPVARIABLE1] = GetChar();
        }

        SW1SW2 = SW1SW2_OK;
	}

    return SW1SW2;
}


/********************************************************************************************************
; Function   : Load ICV
; Description: Load 8 bytes ICV for triple DES encryption
;********************************************************************************************************
;
; Command Syntax
;
;       E5 84 00 00 08 ICV[8]
;
; Inputs
;       DataBytes    Initial Chaining Vector to use for DES or 3DES encryption
; Outputs			
;       SW1SW2
;
;********************************************************************************************************/
unsigned int Load_DES3_ICV3 (void)
{
    if (PARA3 != 0x08)
    {
        SW1SW2 = SW1SW2_WRONG_LC_LENGTH; /* Incorrect length specified */
    }
    else
    {
        for (TEMPVARIABLE1 = 0; TEMPVARIABLE1 < 8; TEMPVARIABLE1++)
            TDES_ICV3[TEMPVARIABLE1] = GetChar();

        SW1SW2 = SW1SW2_OK;
    }

    return SW1SW2;
} 

