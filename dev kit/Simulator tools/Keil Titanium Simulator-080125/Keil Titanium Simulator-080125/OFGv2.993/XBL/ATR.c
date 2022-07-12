

/******************************************************************************
*
* Name:         ATR.c
* Description:  Contains the function that sends the ATR
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
* $Revision: 1.2 $
* $Author :xquillien $ 
* $Date: 2007/05/03 22:16:01 $
******************************************************************************/



/******************************************************************************
* Header file inclusions
******************************************************************************/

#include "Firmware_API_JumpTable.h"

/******************************************************************************
* External and local function declarations 
******************************************************************************/

// external functions declaration
extern code PutCharParityBit();
#define	TRANSPORT_KEY	0x00
#define	ENCRYPTION_KEY	0x01

#define ATR_LENGTH 11

extern Firmware_Set_Clock(unsigned char Clock_Type, unsigned char divisor, unsigned char multiplicator);
extern void Calculate_Bulk_Memory_Checksum_TT40();
#ifdef PRODUCTION
extern code unsigned char Firmware_Get_Key_Status(unsigned char key_type);

#else
extern code unsigned char Get_Key_Status(unsigned char key_Type);
#endif

extern unsigned char data Actual_Bulk_CKS_Hi;
extern unsigned char data Actual_Bulk_CKS_Lo;
extern unsigned char xdata Undo_Last_INS_Write;
extern unsigned char xdata Error_Code;
extern unsigned char xdata Device_Status;
extern unsigned char xdata Error_Code_Address_Hi ;
extern unsigned char xdata Error_Code_Address_Lo ;
extern unsigned char xdata Error_Code_DPX ;

// global variable function declaration

/******************************************************************************
*
* Function Name:      SendATR
* Function Inputs:    void
* Function Outputs:   void
* Description:        sends the ATR out. The first byte has already been sent at 
*				      the begginning of the core bootloader file
******************************************************************************/

/******************************************************************************
* External variable declarations
******************************************************************************/



void SendATR()
{
  unsigned char idata i;
  unsigned char idata AddHi = 0;
  unsigned char idata AddLo = 0;
  unsigned char idata ATR[] = {0x98, 0x96 /* FIDI: Fi max: 512 at 10Mhz Dimax:32*/, 0x00, 0xE5, 0x00, 0x40, 
							/* 2 bytes Device Version*/ 0x10, /*CSPEC nb*/ 0x00, 0x63, /* bootloader rev*/ 0x0A, 
							 /* Encryption Key status */ 0x00};


// T3: device status
// Virgin = 0;
// Partially loaded = 1

  // check device status with bulkmemory checksum
//  Calculate_Bulk_Memory_Checksum_TT40();
//  #ifdef PRODUCTION
//  if (Actual_Bulk_CKS_Hi!= 0xD1 || 	Actual_Bulk_CKS_Lo != 0xC6)
//  {
//    ATR[10] = 1;
//  }
//  #endif
  // encryption key status
 #ifdef PRODUCTION
  if(Firmware_Get_Key_Status(ENCRYPTION_KEY) == 0)
 #else
 if(Get_Key_Status(ENCRYPTION_KEY) == 0)
 #endif
  {
    // encryption key loaded
    ATR[10] = 1;
  }
  else
  {
     ATR[10] = 0;
  }



	ACC = ATR[0];
    PutCharParityBit();
    // Set the Frequency to 60 Mhz internal oscillator
    Firmware_Set_Clock(0x00, 0x00,0x0F);
  
  // Send the ATR string
  for(i=1; i<ATR_LENGTH; i++)
  {
    ACC = ATR[i];
    PutCharParityBit();
  }


}






