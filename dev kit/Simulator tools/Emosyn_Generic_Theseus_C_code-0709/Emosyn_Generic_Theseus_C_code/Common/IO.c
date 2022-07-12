/******************************************************************************
*
* Name:         IO.c
* Description:  Contains functions for the input and output serial routines
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
* $Revision: 1.3 $
* $Author: chin $ 
* $Date: 2006/02/22 15:46:04 $
******************************************************************************/


/******************************************************************************
* Header file inclusions
******************************************************************************/
#include "Firmware_API_JumpTable.h"
#include "Emosyn_Helper_Functions.h"


/******************************************************************************
* External and local function declarations 
******************************************************************************/


/******************************************************************************
* External variable declarations
******************************************************************************/


/******************************************************************************
*
* Function Name:      PutChar
* Function Inputs:    uchar  ByteToTx
* Function Outputs:   void
* Description:        Outputs a single char through the serial port
*                         Loads the char to send into the SBUF sfr
*                         waits until TI flag has been set to indicate char sent
*                         checks the resend bit to see if there was an error
*                             if resend bit is 0 the function exits
*                             if resend bit is 1 redo the transmit loop
*
******************************************************************************/
void PutChar (uchar ByteToTx)
{
    while (1)
    {
        SBUF = ByteToTx;        /* Put char to send into the Serial buffer */

        while (TI == 0);        /* Wait until TI has gone high */

        TI = 0;                 /* Reset the TI flag */

        if (!(ISOCON & 0x08))   /* If bit 3 (Resend) is 0 transmit successful */
		{
            break;              /* break out of this loop */
		}

        ISOCON &= 0xF7;         /* Reset resend bit & try to outputting again */
    }

} /* End of function */


/******************************************************************************
*
* Function Name:      GetChar
* Function Inputs:    void
* Function Outputs:   char  byte from SBUF
* Description:        Gets a char from the serial port
*                         Code waits for RI flag to be set indicating char received
*                         clears the RI flag
*                         returns the byte received
*
******************************************************************************/
uchar GetChar (void)
{
    while (RI == 0x00);     /* Wait until RI flag is set to indicated char received */

    RI = 0x00;              /* Reset the receive flag */

    return SBUF;            /* Return the char back to the calling function */

} /* End of function */


/******************************************************************************
*
* Function Name:      Serial_Receive_X_Bytes
* Function Inputs:    uchar Num_of_Bytes_To_RX  Number of bytes to receive
*                     uchar *Buffer_to_Fill     Pointer to buffer to fill
* Function Outputs:   void
* Description:        Routine to receive multiple bytes from serial port
*
******************************************************************************/
void Serial_Receive_X_Bytes (uchar Num_of_Bytes_To_RX, uchar idata *Buffer_to_Fill)
{
    while (Num_of_Bytes_To_RX > 0)      /* Only stop when there are no more bytes to get */
    {
        *Buffer_to_Fill = GetChar();    /* Get a single char and place it in the buffer */

        Buffer_to_Fill++;               /* Point to next element in buffer */

        Num_of_Bytes_To_RX--;           /* Decrement the number of bytes to receive */
    }

} /* End of function */


/******************************************************************************
*
* Function Name:      Serial_Transmit_X_Bytes
* Function Inputs:    uchar  Num_of_Bytes_To_TX  Number of bytes to transmit
*                     uchar  *Buffer_to_Send     Pointer to buffer with bytes to send
* Function Outputs:   void
* Description:        Routine to transmit multiple bytes to the serial port
*
******************************************************************************/
void Serial_Transmit_X_Bytes (uchar Num_of_Bytes_To_TX, uchar idata *Buffer_to_Send)
{
    while (Num_of_Bytes_To_TX > 0)      /* Only stop when there are no more bytes to get */
    {
        PutChar (*Buffer_to_Send);      /* Send a single char from the buffer */

        Buffer_to_Send++;               /* Point to next element in buffer to send */

        Num_of_Bytes_To_TX--;           /* Decrement the number of bytes to transmit */
    }

} /* End of function */
