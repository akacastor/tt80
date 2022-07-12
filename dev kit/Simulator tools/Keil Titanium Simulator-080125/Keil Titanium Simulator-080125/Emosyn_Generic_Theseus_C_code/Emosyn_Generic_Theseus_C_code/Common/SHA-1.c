/******************************************************************************
*
* Name:         SHA-1.c
* Description:  Contains function to perform SHA process
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
* $Date: 2005/11/09 12:58:25 $
******************************************************************************/


/******************************************************************************
* Header file inclusions
******************************************************************************/
#include "Firmware_API_JumpTable.h"
#include "Emosyn_Helper_Functions.h"

#define S1(X) (((X)<<1) |((X)>>(32-1)))
#define S5(X) (((X)<<5) |((X)>>(32-5)))
#define S30(X) (((X)<<30)|((X)>>(32-30)))


/******************************************************************************
* External and local function declarations 
******************************************************************************/
ulong *SHA_1_Hash (uchar *ucpDataBytesPtr, uint uiNumberToHash);


/******************************************************************************
* External variable declarations
******************************************************************************/


/******************************************************************************
*
* Function Name:      Call_SHA1
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or
*                                  6C00h for wrong LE
* Description:        
*
* APDU Syntax:        E5 78 PARA1 PARA2 14
* APDU Inputs:        PARA1  Byte to hash
*                     PARA2  Number of times to hash PARA1
* APDU Outputs:       20 bytes of SHA hashed data
*
* Example usage:      SHA 1 hash 80h bytes of FFh
* To Card             ->  E5 78 FF 80 14
* ACK from Card       <-  78
* Data from Card      <-  CD 5B D2 0E 9A 0F 22 D7 36 7C C1 69 E2 84 4A 02 75 1C 7C 91
* Response from Card  <-  90 00
*
******************************************************************************/
uint Call_SHA1 (void)
{
    uchar *ucpSHA1_Hash_Output;

    if (PARA3 == 0x14)
    {
        /* Setup Pointer to point at XRAM start address */
        uchar xdata *ucPtr_Data_To_Hash = XDATA_START_ADDRESS;

        /* Write PARA2 bytes of PARA1 into XRAM starting XRAM start address */
        for (ucCount = 0; ucCount < PARA2; ucCount++)
        {
            *ucPtr_Data_To_Hash++ = PARA1;
        }

        ucPtr_Data_To_Hash = XDATA_START_ADDRESS; /* Reset Pointer */

        /* Call the SHA1 function */
        ucpSHA1_Hash_Output = (uchar *)SHA_1_Hash (ucPtr_Data_To_Hash, PARA2);

        for (ucCount = 0; ucCount < 20; ucCount++)  /* Output the Hash value */
        {
            PutChar (*(ucpSHA1_Hash_Output++));
        }

        SW1SW2 = SW1SW2_OK;
    }
    else
    {
        SW1SW2 = SW1SW2_WRONG_LE_LENGTH;
    }

    return SW1SW2;

} /* End of function */


/******************************************************************************
*
* Function Name:      SHA_1_Hash
* Function Inputs:    uchar *ucpDataBytesPtr  Pointer to data to hash
*                     uint  uiNumberToHash    Number of bytes ot hash
* Function Outputs:   ulong H                 Array of 5 long data variables
* Description:        Contains the actual SHA algorithm to hash the data
*
*******************************************************************************/
ulong *SHA_1_Hash (uchar *ucpDataBytesPtr, uint uiNumberToHash)
{	
    ulong H[5] ;
    ulong A, B, C, D, E;
    ulong idata W[16];
    ulong ulTEMP;
    uint uiBytesAlreadyHashed;
    uchar s;
    uchar t;
    uchar ucPaddingDone = 0;
	
    /*********************************************************************/
    /* Before processing any blocks, the {H[i]} are initialized as       */
    /* follows: in hex,                                                  */
    /* H[0] = 67452301                                                   */
    /* H[1] = EFCDAB89                                                   */
    /* H[2] = 98BADCFE                                                   */
    /* H[3] = 10325476                                                   */
    /* H[4] = C3D2E1F0.                                                  */
    /*********************************************************************/
	
    H[0] = 0x67452301;
    H[1] = 0xEFCDAB89;
    H[2] = 0x98BADCFE;
    H[3] = 0x10325476;
    H[4] = 0xC3D2E1F0;

    /*********************************************************************/
    /* Now M[1], M[2], ... , M[n] are processed.                         */
    /*********************************************************************/

    uiBytesAlreadyHashed = 0 ;
	
    /* now if we were to call this function...then the pointer to the data would be passed
     as well as the length */

    while (uiBytesAlreadyHashed <= uiNumberToHash || ucPaddingDone != 3)
    {
        for (t = 0; t<16; t++)
        {
            W[t]= 0;
        }

        t = 0;

        if (uiBytesAlreadyHashed < uiNumberToHash)
        {
            do
            {
                W[t / 4] =  W[t / 4] | ((ulong)*ucpDataBytesPtr << ( (3 -(t % 4)) * 8));
                ucpDataBytesPtr++;
                t++; 
            } while ((t % 0x40 !=0) && (t + uiBytesAlreadyHashed < uiNumberToHash));
        }
		
        if ((int)(uiNumberToHash - uiBytesAlreadyHashed) < 64)
        {
            t = 0;

            /* WE ENTER IN THE LAST BLOCK. /* MAKE THE PADDING */
		
            if (ucPaddingDone == 0)
            {
                s = (uiNumberToHash & 0x3F);
                /* ulTEMP indicates the bytes numbers in the last word. 0 <= ulTEMP < 4 */
                ulTEMP = s % 4;   
                /* t is used as a temporary variable, it indicates the number of "completly" filled words. */ 
				t = s / 4;

                if (ulTEMP == 0)
                {
                    /* write 0x80 after the last byte of data & ensure the following bytes are reset */
                    W[t] = 0x80000000;
                }
                else
                {
                    if (ulTEMP < 2)
                    {
                        /* write 0x80 after the last byte of data & ensure the following bytes are reset */
                        W[t] |= 0x800000;
                    }
                    else
                    {
                        if (ulTEMP < 3)
                        {
                            /* write 0x80 after the last byte of data & ensure the following bytes are reset */
                            W[t] |= 0x8000;
                        }
                        else
                        {
                            /* write 0x80 after the last byte of data & ensure the following bytes are reset */
                            W[t] |= 0x80;
                        }
                    }
                }

                ucPaddingDone = 1;
            }

            if (t < 14 && !(ucPaddingDone & 0x02))
            {
                W[15] = uiNumberToHash * 8;

                /* uiBytesAlreadyHashed is set to this value to exit the while loop */
                uiBytesAlreadyHashed = uiNumberToHash;
                ucPaddingDone|=2;
            }
        }

        /*********************************************************************/
        /* message block processing                                          */
        /*********************************************************************/

        /*********************************************************************/
        /* c. Let A = H[0], B = H[1], C = H[2], D = H[3], E = H[4].          */
        /*********************************************************************/

        A = H[0]; B = H[1]; C = H[2]; D = H[3]; E = H[4];

        for (t = 0; t < 80 ; t++)
        {
            s = t & 0x0f;
            ulTEMP = W[(ulong)((s + 13) & 0x0f)] ^ W[(ulong)((s + 8) & 0x0f)] ^ W[(ulong)((s + 2) & 0x0f)] ^ W[s];

            if (t > 15) 
            {
                W[s] = S1(ulTEMP);
            }
            if (t < 20)
            {
                ulTEMP = ((B & C)|((~B) & D)) + 0x5A827999;
            }
            else
            {
                if (t < 40)
                {
                    ulTEMP = (B ^ C ^ D) + 0x6ED9EBA1;
                }
                else
                {
                    if (t < 60)
                    {
                        ulTEMP = ((B & C) | (B & D) | (C & D)) + 0x8F1BBCDC;
                    }
	                else
                    {
                        ulTEMP = (B ^ C ^ D) + 0xCA62C1D6;
                    }
                }
            }

            ulTEMP = ulTEMP + S5(A) + E + W[s];

            E = D;
            D = C;
            C = S30(B);
            B = A;
            A = ulTEMP;

        } /* end of for loop */
        /*********************************************************************/
        /* e.g Let H[0] = H[0] + A, H[1] = H[1] + B, H[2]= H[2] + C,          */
        /*  H[3] = H[3] + D, H[4] = H[4] + E.                                */
        /*********************************************************************/

        H[0] = H[0] + A;
        H[1] = H[1] + B;
        H[2] = H[2] + C;
        H[3] = H[3] + D;
        H[4] = H[4] + E;

        uiBytesAlreadyHashed += 64;

    } /* end of while loop */

    /*********************************************************************/
    /* After processing M[n], the message digest is the 160-bit string   */
    /* represented by the 5 words                                        */
    /* H[0] H[1] H[2] H[3] H[4].                                         */
    /*********************************************************************/

    return H;

} /* End of function */
