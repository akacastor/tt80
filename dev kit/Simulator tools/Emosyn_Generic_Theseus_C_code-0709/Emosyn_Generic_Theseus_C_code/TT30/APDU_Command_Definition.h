/******************************************************************************
*
* Name:         APDU_Command_Definition.h
* Description:  Header file containing Emosyn APDU CLA INS value definitions
*               for the TT30 chip
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
* $Revision: 1.11 $
* $Author: chin $
* $Date: 2006/03/08 19:02:09 $
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


/*************************************************************/
/* Below is a list of functions that the INS commands access */
/*************************************************************/
unsigned int Get_Chip_ID (void);
unsigned int Get_Clock_Source (void);
unsigned int Get_Clock_Control (void);
unsigned int Set_Protection_Status (void);
unsigned int Set_Execute_Only_Status (void);
unsigned int Set_Security_Action (void);
unsigned int Set_Security_Mask (void);
unsigned int Set_Clock (void);
unsigned int Set_Interrupt_Enable (void);
unsigned int Get_Interrupt_Enable (void);
unsigned int Get_Firmware_Version (void);

unsigned int Write_UCM_Bytes_Flash_Mode_From_IRAM_Buffer (void);
unsigned int Write_Byte_UCM_Flash_Mode (void);
unsigned int Erase_256_UCM (void);
unsigned int Mass_Erase_UCM_Leaving_Bootloader (void);
unsigned int Mass_Erase_UCM (void);
unsigned int Erase_512_UCM  (void);

unsigned int Change_ISO_Speed (void);
unsigned int Set_Security_Status (void);
unsigned int Get_Security_Status (void);
unsigned int Erase_UCM_Blocks__R6R7_Passing (void);
unsigned int Get_Diagnostic_Data (void);
unsigned int Set_Idle_Mode (void);

unsigned int Call_SHA1 (void);
unsigned int CODE_Memory_Dump (void);
unsigned int IDATA_Memory_Dump (void);
unsigned int XDATA_Memory_Dump (void);

unsigned int Call_DES (void);
unsigned int Load_DES_Key (void);
unsigned int Load_DES3_ICV3 (void);
unsigned int Call_3DES (void);
unsigned int Create_CRC16_Hash_Of_XDATA (void);
unsigned int Write_To_IRAM (void);
unsigned int Get_OS_Version (void);

unsigned int Write_To_XRAM (void);

unsigned int Get_Response (void);

unsigned int Write_X_Bytes_To_UCM (void);
unsigned int Write_X_Bytes_To_UCM__256_Page_Backup_Handled (void);
unsigned int Get_Idle_Mode (void);

unsigned int Set_Pullup_Resistor (void);
unsigned int Get_Pullup_Resistor (void);

/******************************************************************************
* Public Variables
******************************************************************************/

/*************************************************************/
/* Below is the function pointer table for the INS commands  */
/*************************************************************/
code INS_FPTR[]={
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
Write_UCM_Bytes_Flash_Mode_From_IRAM_Buffer,   /* 0x20 */
NO_ENTRY,                                      /* 0x22 */
NO_ENTRY,                                      /* 0x24 */
Write_Byte_UCM_Flash_Mode,                     /* 0x26 */
NO_ENTRY,                                      /* 0x28 */
NO_ENTRY,                                      /* 0x2A */
Erase_256_UCM,                                 /* 0x2C */
NO_ENTRY,                                      /* 0x2E */
Mass_Erase_UCM_Leaving_Bootloader,             /* 0x30 */
Mass_Erase_UCM,                                /* 0x32 */
NO_ENTRY,                                      /* 0x34 */
NO_ENTRY,                                      /* 0x36 */
NO_ENTRY,                                      /* 0x38 */
NO_ENTRY,                                      /* 0x3A */
NO_ENTRY,                                      /* 0x3C */
Erase_512_UCM,                                 /* 0x3E */
Change_ISO_Speed,                              /* 0x40 */
Set_Security_Status,                           /* 0x42 */
Get_Security_Status,                           /* 0x44 */
NO_ENTRY,                                      /* 0x46 */
NO_ENTRY,                                      /* 0x48 */
NO_ENTRY,                                      /* 0x4A */
NO_ENTRY,                                      /* 0x4C */
NO_ENTRY,                                      /* 0x4E */
NO_ENTRY,                                      /* 0x50 */
Erase_UCM_Blocks__R6R7_Passing,                /* 0x52 */
Get_Diagnostic_Data,                           /* 0x54 */
NO_ENTRY,                                      /* 0x56 */
NO_ENTRY,                                      /* 0x58 */
Set_Idle_Mode,                                 /* 0x5A */
NO_ENTRY,                                      /* 0x5C */
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
CODE_Memory_Dump,                              /* 0x7A */
IDATA_Memory_Dump,                             /* 0x7C */
XDATA_Memory_Dump,                             /* 0x7E */
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
NO_ENTRY,                                      /* 0xA8 */
NO_ENTRY,                                      /* 0xAA */
NO_ENTRY,                                      /* 0xAC */
NO_ENTRY,                                      /* 0xAE */
NO_ENTRY,                                      /* 0xB0 */
NO_ENTRY,                                      /* 0xB2 */
Write_To_XRAM,                                 /* 0xB4 */
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
NO_ENTRY,                                      /* 0xD0 */
NO_ENTRY,                                      /* 0xD2 */
NO_ENTRY,                                      /* 0xD4 */
NO_ENTRY,                                      /* 0xD6 */
NO_ENTRY,                                      /* 0xD8 */
NO_ENTRY,                                      /* 0xDA */
NO_ENTRY,                                      /* 0xDC */
NO_ENTRY,                                      /* 0xDE */
Write_X_Bytes_To_UCM,                          /* 0xE0 */
NO_ENTRY,                                      /* 0xE2 */
Write_X_Bytes_To_UCM__256_Page_Backup_Handled, /* 0xE4 */
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
