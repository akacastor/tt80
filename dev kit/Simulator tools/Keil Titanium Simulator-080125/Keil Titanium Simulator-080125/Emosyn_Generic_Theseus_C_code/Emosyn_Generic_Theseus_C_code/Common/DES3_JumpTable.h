/******************************************************************************
*
* Name:         DES3_JumpTable.h
* Description:  Header file containing Triple DES (3DES) declarations
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
extern unsigned char TheseusPlatinum_DES3 (DES3_Parameters *DES3_Param);


/******************************************************************************
* Public Variables
******************************************************************************/ 
typedef struct 
{
    unsigned char xdata *Data_Starting_Address;
    unsigned char Data_Length;
    unsigned char xdata *ICV;
    unsigned char xdata *Padding;
    unsigned char Mode;
    unsigned char Encrypt_Decrypt;
    unsigned char xdata *Algo_XDATA_Buffer;
    unsigned char xdata *Key24;
    unsigned char idata *DES_Input;
} xdata DES3_Parameters;

