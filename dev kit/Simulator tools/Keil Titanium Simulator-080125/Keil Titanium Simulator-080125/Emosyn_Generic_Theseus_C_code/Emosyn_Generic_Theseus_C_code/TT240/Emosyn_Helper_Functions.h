/******************************************************************************
*
* Name:         Emosyn_Helper_Functions.h
* Description:  Header file containing declaration for Emosyn provided functions
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
* $Author: dhunter $ 
* $Date: 2007/03/07 00:54:48 $
******************************************************************************/

/******************************************************************************
* Header file inclusions (#include)
******************************************************************************/
#include "../Common/Global_Vars.h"


/******************************************************************************
* Definitions (#define)
******************************************************************************/


/******************************************************************************
* Public Function Prototypes
******************************************************************************/
extern uint Conv_Two_Bytes_To_Int (uchar HiByteAddr, uchar LoByteAddr);
extern void PutChar (uchar Byte); /* Single byte IO transmisssion */
extern uchar GetChar(void);       /* Single byte IO reception */ 
extern void Serial_Receive_X_Bytes (uchar NumberToReceive, uchar idata *Buffer);
extern void Serial_Transmit_X_Bytes (uchar NumberToTransmit, uchar idata *Buffer);


/******************************************************************************
* Public Variables
******************************************************************************/