/******************************************************************************
*
* Name:         TP40_TP62_Erase_Back_To_Factory_State.c
* Description:  Contains function to erase all of the EEPROM and UCM back to
*               factory state
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
* $Author: chin $ 
* $Date: 2005/08/09 11:53:42 $
******************************************************************************/


/******************************************************************************
* Header file inclusions
******************************************************************************/
#include "Firmware_API_JumpTable.h"
#include "Emosyn_Helper_Functions.h"


/******************************************************************************
* External and local function declarations 
******************************************************************************/
/* External and local function declarations */
extern uint TheseusPlatinum_EE_MassErase_Bootloader_Safe (void);


/******************************************************************************
* External variable declarations
******************************************************************************/


/* The array below holds the assembly instructions required */
/* to erase the UCM & return a SW1SW2 response */
unsigned char code Erase_Code_To_Go_Into_RAM[] = {
0x12, 0x03, 0xD4, /* lcall	Firmware_MassEraseUCM */
0x75, 0x99, 0x90, /* mov	SBUF, #90h  */
0x30, 0x99, 0xFD, /* jnb	SCON.1, $ */
0xC2, 0x99,       /* clr	SCON.1 */
0x75, 0x99, 0x00, /* mov	SBUF, #00h  */
0x30, 0x99, 0xFD, /* jnb	SCON.1, $  */
0xC2, 0x99,       /* clr	SCON.1  */
0x02, 0xFD, 0x00  /* ljmp	0xFD00  */
};


/******************************************************************************
*
* Function Name:      Erase_Back_To_Factory_State
* Function Inputs:    void
* Function Outputs:   uint SW1SW2_OK  9000h
* Description:        Clears all of the EEPROM and UCM back to factory state
*                     Sequence of memory erasing is:
*                         Call erase EEPROM command (excluding bootloader)
*                         Copy the UCM erase code (including SW1SW2 response)
*                             into XDATA RAM space (cannot run code from UCM
*                             while erasing it)
*                         Copy a infinite looping command into XDATA RAM space
*                              past the UCM erase code
*                         Call the UCM erase code located in XDATA RAM
*
* APDU Syntax:        E5 30 00 00 00
* APDU Inputs:        None
* APDU Outputs:       None
* Example usage:      Erase the EEPROM and the UCM back to factory delivered state
* To Card             ->  E5 30 00 00 00
* ACK from Card       <-  30
* Response from Card  <-  90 00
*
******************************************************************************/
unsigned int Erase_Back_To_Factory_State (void)
{
    /* function pointer to call the code held in XDATA RAM */
    void (*erase_fp)(void);

    /* Erase EEPROM excluding Bootloader */
    TheseusPlatinum_EE_MassErase_Bootloader_Safe();

    /* Point to array holding code to run in RAM */
    CODE_PTR = &Erase_Code_To_Go_Into_RAM;

    /* Address where the code will be copied to */
    XDATA_PTR = 0xFC00;

    /* Copy in the erase code into XDATA RAM at 0xFC00*/
    for (CODE_PTR = &Erase_Code_To_Go_Into_RAM;
         XDATA_PTR < (0xFC00 + sizeof(Erase_Code_To_Go_Into_RAM));
         CODE_PTR++, XDATA_PTR++)
    {
        *XDATA_PTR = *CODE_PTR;
    }

    /* This code will continuously loop forever */
    XDATA_PTR = 0xFD00;
    *XDATA_PTR++ = 0x02;
    *XDATA_PTR++ = 0xFD;
    *XDATA_PTR++ = 0x00;

    /* Reference the function pointer to the code held in XDATA RAM */
    erase_fp = 0xFC00;

    /* Call the function */
	erase_fp();

   	return SW1SW2_OK;

} /* End of function */
