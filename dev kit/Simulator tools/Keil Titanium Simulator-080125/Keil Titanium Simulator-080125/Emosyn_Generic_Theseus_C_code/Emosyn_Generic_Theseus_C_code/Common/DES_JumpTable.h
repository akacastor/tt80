/******************************************************************************
*
* Name:         DES_JumpTable.h
* Description:  Header file containing DES declarations
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
* $Author: chin $ 
* $Date: 2005/08/15 10:01:36 $
******************************************************************************/


/******************************************************************************
* Header file inclusions (#include)
******************************************************************************/


/******************************************************************************
* Definitions (#define)
******************************************************************************/


/******************************************************************************
* Public Function Prototypes
******************************************************************************/
extern void TheseusPlatinum_DES (unsigned char idata * Data_Starting_Address,
              unsigned char xdata * DES_buffer,unsigned char Encrypt_Decrypt); 

/* The DES routine output is hardwired to use 0x20~0x2F */
extern unsigned char idata Output[8];

 /* The DES routine looks for the key in a hardwired location - 0x20~0x2F */
extern unsigned char idata Key[8];


/******************************************************************************
* Public Variables
******************************************************************************/ 
