
/******************************************************************************
*
* Name:        BulkChecksum_32Bits_TT120.c
* Description:  
* 
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
* $Author :xquillien $ 
* $Date: 2006/07/12 02:40:31 $
******************************************************************************/

/******************************************************************************
* Header file inclusions
******************************************************************************/

#include "Firmware_API_JumpTable.h"

/******************************************************************************
* external functions declaration
******************************************************************************/




void CRC16 (unsigned char xdata * data_buf);

/******************************************************************************/
/*																			  */		
/* Function Name:      Calculate_Bulk_Memory_Chacksum_TT120					  */
/* Function Inputs: These functions calculate a complete CRC16 memory checksum*/
/* from address 1DE00h down to 803h				 							  */
/*																			  */
/* Function Outputs:   void													  */
/* Description: 															  */
/* Calculatiuon of CRC according to x^15+x^12+x^5+1							  */
/* Input:																	  */
/*	Voidt:																	  */
/*      result put into global variable:Actual_Bulk_CKS						*/
/*****************************************************************************/

unsigned int data * Actual_Bulk_CKS;
unsigned char data Actual_Bulk_CKS_Hi;
unsigned char data Actual_Bulk_CKS_Lo;

unsigned char xdata Checksum_Address _at_ 0x403 ; 

extern  unsigned int CRC16_m;
extern unsigned int   Data_Length;
void Calculate_Bulk_Memory_Checksum_TT40()
{


	// checksum from 0x0400 to 0x9BFF 
   	CRC16_m = 0;
    Data_Length = (unsigned int) 0x97FD;

   	CRC16((unsigned char xdata *) &Checksum_Address);
    
  
  // split the checksum result in 2 bytes as it makes life easier for assembly call

  Actual_Bulk_CKS_Lo = (unsigned char) (CRC16_m);
  Actual_Bulk_CKS_Hi = (unsigned char) ((CRC16_m)>>8);
  

}

