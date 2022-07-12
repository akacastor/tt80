/******************************************************************************
*
* Name:         Emosyn_Clock_Speeds.h
* Description:  Defines the different speeds available for the internal clock &
*               ISO port
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
* $Author: xavier $ 
* $Date: 2006/07/12 02:40:31 $
******************************************************************************/


/******************************************************************************
* Header file inclusions (#include)
******************************************************************************/


/******************************************************************************
* Definitions (#define)
******************************************************************************/
#define DIVIDE_BY_01_RATIO 0x0F
#define DIVIDE_BY_02_RATIO 0x00
#define DIVIDE_BY_03_RATIO 0x01
#define DIVIDE_BY_04_RATIO 0x02
#define DIVIDE_BY_05_RATIO 0x03
#define DIVIDE_BY_06_RATIO 0x04
#define DIVIDE_BY_07_RATIO 0x05
#define DIVIDE_BY_08_RATIO 0x06
#define DIVIDE_BY_09_RATIO 0x07
#define DIVIDE_BY_10_RATIO 0x08
#define DIVIDE_BY_11_RATIO 0x09
#define DIVIDE_BY_12_RATIO 0x0A
#define DIVIDE_BY_13_RATIO 0x0B
#define DIVIDE_BY_14_RATIO 0x0C
#define DIVIDE_BY_15_RATIO 0x0D
#define DIVIDE_BY_16_RATIO 0x0E

#define MULTIPLY_BY_01_RATIO 0x00
#define MULTIPLY_BY_02_RATIO 0x01
#define MULTIPLY_BY_03_RATIO 0x02
#define MULTIPLY_BY_04_RATIO 0x03
#define MULTIPLY_BY_05_RATIO 0x04
#define MULTIPLY_BY_06_RATIO 0x05
#define MULTIPLY_BY_07_RATIO 0x06
#define MULTIPLY_BY_08_RATIO 0x07
#define MULTIPLY_BY_09_RATIO 0x08
#define MULTIPLY_BY_10_RATIO 0x09
#define MULTIPLY_BY_11_RATIO 0x0A
#define MULTIPLY_BY_12_RATIO 0x0B
#define MULTIPLY_BY_13_RATIO 0x0C
#define MULTIPLY_BY_14_RATIO 0x0D
#define MULTIPLY_BY_15_RATIO 0x0E
#define MULTIPLY_BY_16_RATIO 0x0F


/* Clock source settings for Firmware_SetClock API */
#define INT_OSC   0x00
#define PLL_CLOCK 0x01
#define ISO_CLOCK 0x02


/* Defines type of return value that will be returned for success or failure */
#define NO_RETURN_CMD 0x00
#define PPS_BAUD_CMD  0x01
#define APDU_BAUD_CMD 0x02


/******************************************************************************
* Public Function Prototypes
******************************************************************************/


/******************************************************************************
* Public Variables
******************************************************************************/
