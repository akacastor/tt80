/******************************************************************************
*
* Name:         APDU_Command_Definition.h
* Description:  Header file containing Emosyn APDU CLA INS value definitions
*               for the TT120 chip
* Copyright:    Emosyn Inc. 2006
* The Example Code herein below is provided "AS IS" and at your sole risk.  
* As to this Code, EMOSYN expressly disclaims all warranties, including, but
* not limited to the implied warranties of merchantability and fitness for a
* particular purpose. EMOSYN does not warrant that the functions contained in
* this code will meet your requirements, or that the operation of the code will
* be accurate, error-free, or non-infringing. No oral or written information or
* advice given by EMOSYN or an authorized representative shall create or affect
* any Warranty.
*******************************************************************************
* $Revision: 1.4 $
; $Author: dhunter $
; $Date: 2006/09/07 21:26:00 $
******************************************************************************/

/******************************************************************************
* Header file inclusions (#include)
******************************************************************************/
#include <absacc.h>    /* Contains macro for FVAR */


/******************************************************************************
* Definitions (#define)
******************************************************************************/
typedef uint (*FUNC_PTR)(void);


/******************************************************************************
* Public Function Prototypes
******************************************************************************/

/*************************************************************/
/* Below is a list of functions that the INS commands access */
/*************************************************************/
uint Get_Chip_ID (void);
uint Get_Clock_Source (void);
uint Get_Clock_Control (void);
uint Set_Protection_Status (void);
uint Set_Execute_Only_Status (void);
uint Set_Security_Action (void);
uint Set_Security_Mask (void);
uint Set_Clock (void);
uint Set_Interrupt_Enable (void);
uint Get_Interrupt_Enable (void);
uint Get_Firmware_Version (void);

uint Mass_Erase_UCM_Leaving_Bootloader (void);
uint Mass_Erase_UCM (void);
uint Get_Random_Number (void);

uint Change_ISO_Speed (void);
uint Set_Security_Status (void);
uint Get_Security_Status (void);
uint Timer0_Start (void);
uint Timer1_Start (void);
uint Timer0_Stop (void);
uint Timer1_Stop (void);
uint Timer0_Read (void);
uint Erase_UCM_Blocks__R6R7_Passing (void);
uint Get_Diagnostic_Data (void);
uint Set_Idle_Mode (void);

uint Call_SHA1 (void);
uint CODE_Memory_Dump_Extended_Addressing (void);
uint IDATA_Memory_Dump (void);
uint XDATA_Memory_Dump_Extended_Addressing (void);

uint Create_CRC16_Hash_Of_XDATA (void);
uint Write_To_IRAM (void);
uint Get_OS_Version (void);

uint Write_Byte_UCM_Extended_Addressing (void);
uint Erase_256_UCM_Extended_Addressing (void);
uint Erase_512_UCM_Extended_Addressing (void);
uint Load_DPX (void);
uint Write_To_RAM_Extended_Addressing (void);

uint Get_Response (void);
uint Get_TCON (void);
uint Write_UCM_Bytes_From_IRAM_Buffer_Extended_Addressing (void);

uint Get_Idle_Mode (void);
uint Set_Pullup_Resistor (void);
uint Get_Pullup_Resistor (void);


/******************************************************************************
* Public Variables
******************************************************************************/

/*************************************************************/
/* Below is the function pointer table for the INS commands  */
/*************************************************************/
FUNC_PTR code INS_FPTR[]={
NO_ENTRY,                                      /* 0x00 */
NO_ENTRY,                                      /* 0x02 */
NO_ENTRY,                                      /* 0x04 */
NO_ENTRY,                                      /* 0x06 */
NO_ENTRY,                                      /* 0x08 */
Get_Chip_ID,                                   /* 0x0A */
Get_Clock_Source,                              /* 0x0C */
Get_Clock_Control,                             /* 0x0E */
Set_Protection_Status,                         /* 0x10 */
Set_Execute_Only_Status,                       /* 0x12 */
Set_Security_Action,                           /* 0x14 */
Set_Security_Mask,                             /* 0x16 */
Set_Clock,                                     /* 0x18 */
Set_Interrupt_Enable,                          /* 0x1A */
Get_Interrupt_Enable,                          /* 0x1C */
Get_Firmware_Version,                          /* 0x1E */
NO_ENTRY,                                      /* 0x20 */
NO_ENTRY,                                      /* 0x22 */
NO_ENTRY,                                      /* 0x24 */
NO_ENTRY,                                      /* 0x26 */
NO_ENTRY,                                      /* 0x28 */
NO_ENTRY,                                      /* 0x2A */
NO_ENTRY,                                      /* 0x2C */
NO_ENTRY,                                      /* 0x2E */
Mass_Erase_UCM_Leaving_Bootloader,             /* 0x30 */
Mass_Erase_UCM,                                /* 0x32 */
NO_ENTRY,                                      /* 0x34 */
NO_ENTRY,                                      /* 0x36 */
NO_ENTRY,                                      /* 0x38 */
Get_Random_Number,                             /* 0x3A */
NO_ENTRY,                                      /* 0x3C */
NO_ENTRY,                                      /* 0x3E */
Change_ISO_Speed,                              /* 0x40 */
Set_Security_Status,                           /* 0x42 */
Get_Security_Status,                           /* 0x44 */
NO_ENTRY,                                      /* 0x46 */
NO_ENTRY,                                      /* 0x48 */
Timer0_Start,                                  /* 0x4A */
NO_ENTRY,                                      /* 0x4C */
Timer0_Stop,                                   /* 0x4E */
NO_ENTRY,                                      /* 0x50 */
Erase_UCM_Blocks__R6R7_Passing,                /* 0x52 */
Get_Diagnostic_Data,                           /* 0x54 */
NO_ENTRY,                                      /* 0x56 */
NO_ENTRY,                                      /* 0x58 */
Set_Idle_Mode,                                 /* 0x5A */
Timer0_Read,                                   /* 0x5C */
NO_ENTRY,                                      /* 0x5E */
NO_ENTRY,                                      /* 0x60 */
NO_ENTRY,                                      /* 0x62 */
NO_ENTRY,                                      /* 0x64 */
NO_ENTRY,                                      /* 0x66 */
NO_ENTRY,                                      /* 0x68 */
NO_ENTRY,                                      /* 0x6A */
NO_ENTRY,                                      /* 0x6C */
NO_ENTRY,                                      /* 0x6E */
NO_ENTRY,                                      /* 0x70 */
NO_ENTRY,                                      /* 0x72 */
NO_ENTRY,                                      /* 0x74 */
NO_ENTRY,                                      /* 0x76 */
Call_SHA1,                                     /* 0x78 */
CODE_Memory_Dump_Extended_Addressing,          /* 0x7A */
IDATA_Memory_Dump,                             /* 0x7C */
XDATA_Memory_Dump_Extended_Addressing,         /* 0x7E */
NO_ENTRY,                                      /* 0x80 */
NO_ENTRY,                                      /* 0x82 */
NO_ENTRY,                                      /* 0x84 */
NO_ENTRY,                                      /* 0x86 */
Create_CRC16_Hash_Of_XDATA,                    /* 0x88 */
NO_ENTRY,                                      /* 0x8A */
Write_To_IRAM,                                 /* 0x8C */
Get_OS_Version,                                /* 0x8E */
NO_ENTRY,                                      /* 0x90 */
NO_ENTRY,                                      /* 0x92 */
NO_ENTRY,                                      /* 0x94 */
NO_ENTRY,                                      /* 0x96 */
NO_ENTRY,                                      /* 0x98 */
NO_ENTRY,                                      /* 0x9A */
NO_ENTRY,                                      /* 0x9C */
NO_ENTRY,                                      /* 0x9E */
NO_ENTRY,                                      /* 0xA0 */
NO_ENTRY,                                      /* 0xA2 */
NO_ENTRY,                                      /* 0xA4 */
NO_ENTRY,                                      /* 0xA6 */
Write_Byte_UCM_Extended_Addressing,            /* 0xA8 */
NO_ENTRY,                                      /* 0xAA */
NO_ENTRY,                                      /* 0xAC */
Erase_256_UCM_Extended_Addressing,             /* 0xAE */
Erase_512_UCM_Extended_Addressing,             /* 0xB0 */
Load_DPX,                                      /* 0xB2 */
Write_To_RAM_Extended_Addressing,              /* 0xB4 */
NO_ENTRY,                                      /* 0xB6 */
NO_ENTRY,                                      /* 0xB8 */
NO_ENTRY,                                      /* 0xBA */
NO_ENTRY,                                      /* 0xBC */
NO_ENTRY,                                      /* 0xBE */
Get_Response,                                  /* 0xC0 */
NO_ENTRY,                                      /* 0xC2 */
NO_ENTRY,                                      /* 0xC4 */
NO_ENTRY,                                      /* 0xC6 */
NO_ENTRY,                                      /* 0xC8 */
NO_ENTRY,                                      /* 0xCA */
NO_ENTRY,                                      /* 0xCC */
NO_ENTRY,                                      /* 0xCE */
Get_TCON,                                      /* 0xD0 */
NO_ENTRY,                                      /* 0xD2 */
NO_ENTRY,                                      /* 0xD4 */
NO_ENTRY,                                      /* 0xD6 */
Write_UCM_Bytes_From_IRAM_Buffer_Extended_Addressing, /* 0xD8 */
NO_ENTRY,                                      /* 0xDA */
NO_ENTRY,                                      /* 0xDC */
NO_ENTRY,                                      /* 0xDE */
NO_ENTRY,                                      /* 0xE0 */
NO_ENTRY,                                      /* 0xE2 */
NO_ENTRY,                                      /* 0xE4 */
NO_ENTRY,                                      /* 0xE6 */
Get_Idle_Mode,                                 /* 0xE8 */
NO_ENTRY,                                      /* 0xEA */
NO_ENTRY,                                      /* 0xEC */
NO_ENTRY,                                      /* 0xEE */
Set_Pullup_Resistor,                           /* 0xF0 */
Get_Pullup_Resistor,                           /* 0xF2 */
NO_ENTRY,                                      /* 0xF4 */
NO_ENTRY,                                      /* 0xF6 */
NO_ENTRY,                                      /* 0xF8 */
NO_ENTRY,                                      /* 0xFA */
NO_ENTRY,                                      /* 0xFC */
NO_ENTRY,                                      /* 0xFE */
};
