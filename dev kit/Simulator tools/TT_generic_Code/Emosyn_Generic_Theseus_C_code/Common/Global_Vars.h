/******************************************************************************
*
* Name:         Global_Vars.h
* Description:  Header file containing declarations of variables that will be
*               made available to the project
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
* $Author: dhunter $ 
* $Date: 2006/09/07 21:26:00 $
******************************************************************************/
#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

/******************************************************************************
* Header file inclusions (#include)
******************************************************************************/


/******************************************************************************
* Definitions (#define)
******************************************************************************/
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

#define APDU_HEADER_LENGTH 5
#define TEMP_BUFFER_SIZE 8

#ifdef EXTENDED_ADDRESSING
    #define ADDR_LEN 3
#endif

#define IO_BUFFER_SIZE 0x40
#define EMOSYN_CLA 0xE5
#define PPS_CLA    0xFF

#define NORMAL_IDLE_MODE 0x00
#define DEEP_IDLE_MODE   0x01

#define NOT_PERMANENT    0x00
#define PERMANENT        0x01

#define GET_PULLUP       0x01
#define SET_PULLUP       0x02
#define PULLUP_DISABLED  0x00
#define PULLUP_ENABLED   0x01

#define NO_SW1SW2                0x0000
#define SW1SW2_OK                0x9000
#define SW1SW2_MEMORY_ERROR      0x6581
#define SW1SW2_WRONG_LC_LENGTH   0x6700
#define SW1SW2_INCORRECT_DATA    0x6A80
#define SW1SW2_INCORRECT_PARA    0x6A86
#define SW1SW2_WRONG_LE_LENGTH   0x6C00
#define SW1SW2_INS_NOT_SUPPORTED 0x6D00
#define SW1SW2_CLA_NOT_SUPPORTED 0x6E00
#define SW1SW2_GENERAL_ERROR     0x6F00
#define MSB_SET                  0x80

/* Individual elements of the APDU buffer can be accessed directly */
#define CLA APDU_CMD[0]
#define INS APDU_CMD[1]
#define PARA1 APDU_CMD[2]
#define PARA2 APDU_CMD[3]
#define PARA3 APDU_CMD[4]

/* Individual elements of the Temp buffer can be accessed directly */
#define TEMPVARIABLE1 TEMP_BUF[0]
#define TEMPVARIABLE2 TEMP_BUF[1]
#define TEMPVARIABLE3 TEMP_BUF[2]
#define TEMPVARIABLE4 TEMP_BUF[3]
#define TEMPVARIABLE5 TEMP_BUF[4]
#define TEMPVARIABLE6 TEMP_BUF[5]
#define TEMPVARIABLE7 TEMP_BUF[6]
#define TEMPVARIABLE8 TEMP_BUF[7]

#ifdef EXTENDED_ADDRESSING
     /* For NO_ENTRY it will place FFFFFFh in the 3 byte address space */
     /* To access memory above 64K in C use the FVAR macro */
    #define NO_ENTRY &FVAR(unsigned char, 0xFEFFFF)
#else
     /* For NO_ENTRY it will place FFFFh in the 2 byte address space */
    #define NO_ENTRY 0xFFFF
#endif


/******************************************************************************
* Public Function Prototypes
******************************************************************************/
extern uchar idata IDLE_MODE;
extern uint idata SW1SW2;

extern uchar code *CODE_PTR;
extern uchar xdata *XDATA_PTR;
extern uchar idata *IDATA_PTR;

extern uchar idata ucCount;
extern char idata cRet_Val_Char;
extern int idata iRet_Val_Int;
extern uint idata uiTemp_Address;
extern ulong idata ulTemp_Var;

extern uchar xdata IO_Buffer[IO_BUFFER_SIZE];

#ifdef EXTENDED_ADDRESSING
	extern uchar far *uc_Fptr;
    extern uchar idata DPX_Addr;
    extern uchar idata ucByte_To_Write;
#endif

extern uchar volatile idata Timer0_Int_Count;

/******************************************************************************
* Public Variables
******************************************************************************/
extern unsigned char idata APDU_CMD[APDU_HEADER_LENGTH];
extern unsigned char idata TEMP_BUF[TEMP_BUFFER_SIZE];

#endif // GLOBAL_VARS_H
