/******************************************************************************
*
* Name:         CRC16.c
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
* $Revision: 1.2 $
* $Author :xquillien $ 
* $Date: 2007/05/03 22:17:01 $
******************************************************************************/


#include "Firmware_API_JumpTable.h"

 // fixed memory location for function CRC16
 unsigned int CRC16_m;
 unsigned int   Data_Length;

/****************************************************************/

/****************************************************************************************************/
/*																									*/		
/* Function Name:      CRC16																	    */
/* Function Inputs: fixed memory location:  														*/
/*					CRC16_m which is passed as initial value for CRC16 calculation 					*/
/*					* data_buf: pointer on buffer containing data to calculate						*/
/*		      	  unsigned int Data_length: length of  data -1: length 0 = CRC16 on 256 bytes   	*/
/* Function Outputs:   void																			*/
/* Description: 																					*/
/* Calculatiuon of CRC according to x^15+x^12+x^5+1													*/
/* Input:																							*/
/*	data_buf  - pointer to data buffer																*/
/*	data_len  - length of data -1. Max length 256 bytes.													 				*/
/* Output:																							*/
/*      unsigned short - CRC16 value																*/
/****************************************************************************************************/      
 


void CRC16 (unsigned char xdata * data_buf)
{
       // Current value of CRC
       unsigned int A;

       /* Cycle loop  */
       
       // Cycle loop
       do{
          CRC16_m = CRC16_m  ^ data_buf[--Data_Length];
          A = (CRC16_m ^ (CRC16_m <<4)) & 0x00FF;
          CRC16_m = (CRC16_m >> 8) ^ (A <<8) ^ (A<<3) ^ (A>>4);
        }
        while(Data_Length !=0);
       
}
         

