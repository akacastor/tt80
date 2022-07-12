/******************************************************************************
*
* Name:         Main .c
* Description:  Contains main C entry function + additional supporting functions
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
* $Revision: 1.12 $
* $Author: chin $ 
* $Date: 2006/03/08 16:39:29 $
******************************************************************************/


/******************************************************************************
* Header file inclusions
******************************************************************************/
#include <intrins.h> /* Includes the _nop_() function for C code */
#include "Firmware_API_JumpTable.h"
#include "Emosyn_Helper_Functions.h"
#include "APDU_Command_Definition.h"
#include "Emosyn_Clock_Speeds.h"


/******************************************************************************
* External and local function declarations 
******************************************************************************/
extern void Chip_Init (void);
extern void Send_ATR (void);
extern void ISO_Select_Speed (uchar FiDi, uchar ucCommand_Type);

void Process_PPS_Command (void);
void Process_APDU_Command (void);
void Enter_Idle_Mode (uchar ucIdleMode);


/******************************************************************************
* External variable declarations
******************************************************************************/


/******************************************************************************
*
* Function Name:      main
* Function Inputs:    void
* Function Outputs:   void
* Description:        Main function calls chip initialistion & Send ATR function
*                     It then goes into idle mode. Chip wakes up on receving a
*                     char from the serial port, it then starts the process of
*                     decoding and executing the APDU command
*
*******************************************************************************/
void main (void)
{
    Chip_Init();                /* Initialises clock, serial port */

    Send_ATR();                 /* Transmit the chip specified ATR */

    Enter_Idle_Mode (IDLE_MODE);/* Go into idle mode until a char is received */

    /*******************************************************************/
    /* After the ATR has been sent always check the first APDU command */
    /* to see if it a PPS command (4 byte command), otherwise always   */
    /* get a standard 5 byte APDU command                              */
    /*******************************************************************/

    CLA = GetChar();            /* Get the first byte */

    if (CLA == PPS_CLA)         /* If 1st APDU byte is 0xFF it's a PPS command */
    {
        Process_PPS_Command();
    }
    else                        /* Else receive the rest of APDU command (4 bytes) */
    {
        Serial_Receive_X_Bytes (APDU_HEADER_LENGTH - 1, &INS);
        Process_APDU_Command();
    }

    /************************************************************/
    /* This is the main loop that waits in specific idle mode   */
    /* It wakes up and comes active when a character is received */
    /* It will then process the APDU command                    */
    /************************************************************/
    while (1)
    {
        /* Switch chip to normal idle or deep idle (use ISO clock) */
        Enter_Idle_Mode(IDLE_MODE);

        /* Get 5 byte APDU, should always do this after the 1st ever APDU command */
        Serial_Receive_X_Bytes (APDU_HEADER_LENGTH, &CLA);

        Process_APDU_Command();
	} /* Forever loop */

} /* End of main function */


/******************************************************************************
*
* Function Name:      Process_PPS_Command
* Function Inputs:    void
* Function Outputs:   void
* Description:        Processes PPS command, changing the timer when necessary
*
******************************************************************************/
 void Process_PPS_Command (void)
{
    /* Read in rest of PPS command (3 bytes), already got the CLA */
    Serial_Receive_X_Bytes (APDU_HEADER_LENGTH - 2, &INS);

    /* Call function to change ISO serial timer */
    ISO_Select_Speed (PARA1, PPS_BAUD_CMD);

} /* End of function */


/******************************************************************************
*
* Function Name:      Enter_Idle_Mode
* Function Inputs:    Idle mode type deep idle = 1; normal idle = 0
* Function Outputs:   void
* Description:        Puts chip into normal or deep idle (internal clock stopped)
*
******************************************************************************/
void Enter_Idle_Mode (uchar ucIdleMode)
{
    if (ucIdleMode == NORMAL_IDLE_MODE) 
    {
        PCON |= 0x01;   /* Set the SFR bit that puts the processor into idle mode */

        _nop_ ();
        _nop_ ();
        _nop_ ();
        _nop_ ();
        _nop_ ();
    }
    else if (ucIdleMode == DEEP_IDLE_MODE) 
    {
        /* Save the Clock multiplier and divider ratios currently used by the chip */
        /* This is so the Clock values can be restored after waking up from idle */
        TEMPVARIABLE2 = Firmware_GetClockControlSFR();

        TEMPVARIABLE1 = TEMPVARIABLE2 & 0x0F; /* Clock Divider (lower nibble)*/

        TEMPVARIABLE2 = (TEMPVARIABLE2 & 0xF0) >> 4; /* Clock Multiplier (upper nibble) */

        TEMPVARIABLE3 = Firmware_GetClockSourceSelectSFR(); /* Get the clock source */

        /***********************************************************
         * Note
         * The values for clock settings differ from 
         * Firmware_GetClockSourceSelectSFR to Firmware_SetClock
         *
         * Firmware_GetClockSourceSelectSFR    Firmware_SetClock
         * 00 - ISO Clock Source               00 - Int Clock Source
         * 01 - PLL Clock Source               01 - PLL Clock Source
         * 02 - Int Clock Source               02 - ISO Clock Source
         * So the conversion code below is necessary         
        ***********************************************************/

        if (TEMPVARIABLE3 & 0x02)       /* 0x00 = Int Osc for Firmware_SetClock */
        {
            TEMPVARIABLE3 = INT_OSC;
        }
        else if (TEMPVARIABLE3 & 0x01)  /* 0x01 = PLL for Firmware_SetClock */
        {
            TEMPVARIABLE3 = PLL_CLOCK;
        }
        else                            /* 0x02 = ISOCLK for Firmware_SetClock */
        {
            TEMPVARIABLE3 = ISO_CLOCK;
        }

        /* Run the processor from the ISO clock, no multiplier & no divisor value */
        Firmware_SetClock (ISO_CLOCK, MULTIPLY_BY_01_RATIO, DIVIDE_BY_01_RATIO);

        PCON |= 0x01;       /* Set the SFR that puts the processor into idle mode */

        _nop_ ();
        _nop_ ();
        _nop_ ();
        _nop_ ();
        _nop_ ();

        /* Restore all the previous clock values */
        Firmware_SetClock (TEMPVARIABLE3, TEMPVARIABLE2, TEMPVARIABLE1);

    } /* End of deep idle process */

}  /* End of function */


/******************************************************************************
*
* Function Name:      Process_APDU_Command
* Function Inputs:    void
* Function Outputs:   void
* Description:        APDU command functions are listed sequentially as
*                     addresses in an array. The index for the array is the
*                     INS value (divided by 2 as INS can only be even). If
*                     there is no address for the INS value index it means NO
*                     function is available for this INS value (it will have
*                     an 0xFFFF (NO_ENTRY) entry for its address)
*                     If a function address does exist for the APDU entry a
*                     function pointer refernces it
*
*                     See APDU_Command_Definition.h in the chip specfic
*                     directory for more detail
*
******************************************************************************/
void Process_APDU_Command (void)
{
    /* If not a valid CLA value return 0x6E00 */
    if (CLA != EMOSYN_CLA)
    {
        SW1SW2 = SW1SW2_CLA_NOT_SUPPORTED;
    }

    /* If INS value is an odd number return error */
    else if (INS & 0x01)
    {
        SW1SW2 = SW1SW2_INS_NOT_SUPPORTED;
    }

    /******************************************
     * INS values are even always even!
     * Array for APDU function addresses are 
     * organised sequentially
     * A division of the INS value by 2 is 
     * required to access the array entry for a
     * particular INS command
    ******************************************/

    /* Check if the function address value for this particular APDU INS */
    /* value in the INS_FPTR table is valid (not equal to 0xFFFF) */

#ifndef EXTENDED_ADDRESSING

    else if (INS_FPTR[INS / 2] != (uint)NO_ENTRY)

#else

    else if (INS_FPTR[INS / 2] != NO_ENTRY)

#endif
    {   
        /*************************************************************/
        /* The #ifdef below is designed to give the user the ability */
        /* to remove the ACK byte (INS) for APDU communications      */
        /* The example below does not return an ACK for the          */
        /* Erase_256_UCM command. To execute, insert the define in   */
        /* Project Options\C51\Preprocessor Symbols\Define           */
        /*************************************************************/
#ifdef NO_ACK_BYTE_RETURN

        if (INS != 0x2C)
        {
            PutChar (INS); /* Output the INS as an ack */
        }

#else

        PutChar (INS); /* Output the INS as an ack */

#endif        


        /* Call the function listed in the INS_FPTR table */
#ifndef EXTENDED_ADDRESSING

        /* Function pointer (2 bytes) referencing */
        SW1SW2 = ((uint (code*) (void)) INS_FPTR[INS / 2])();

#else

        /* Function pointer (3 bytes) referencing */
        SW1SW2 = ((uint (*) (void)) INS_FPTR[INS / 2])();

#endif
    }

    /* INS value has no function associated with it */    
    else
    {
        SW1SW2 = SW1SW2_INS_NOT_SUPPORTED;
    }

    /* Only output SW1SW2 if required, not required for Change_ISO_Speed() */
    if (SW1SW2 != NO_SW1SW2)
    {
        Serial_Transmit_X_Bytes (2, (uchar *)&SW1SW2);
    }

} /* End of function */
