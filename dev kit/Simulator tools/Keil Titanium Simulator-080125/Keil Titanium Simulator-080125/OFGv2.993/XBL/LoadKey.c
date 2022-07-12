

/******************************************************************************
* Header file inclusions
******************************************************************************/
#include "Firmware_API_JumpTable.h"

/******************************************************************************
* External  function declarations 
******************************************************************************/

extern void GetChar();  // returns the value into the accumulator!
extern void PutCharParityBit();  // returns the value into the accumulator!

#ifdef SIMULATION

unsigned char Set_Key(unsigned char Key_Type, unsigned char idata * Key_Buffer);
unsigned char Get_Key_Status(unsigned char Key_Type);
#else
extern unsigned char Firmware_Set_Key(unsigned char Key_Type, unsigned char xdata * Key_Buffer);
extern void _Firmware_Init_Key_For_Encryption(void);

#endif

/******************************************************************************
* External variable declarations
******************************************************************************/

extern unsigned char data APDU_P1;
extern unsigned char data APDU_P2;
extern unsigned char data APDU_P3;
extern unsigned char data SW2;
extern unsigned char data SBOX_Offset_Hi;
extern unsigned char data SBOX_Offset_Lo;

/******************************************************************************
*
* Function Name:      Load_Key
* Function Inputs:    void
* Function Outputs:   uint SW1SW2  9000h for success or
*                                  6A80 Incorrect Checksum
*								   6A82 command not available or write key error
*                                  6A86 wrong P1P2
*                                  6700 for wrong LC
* Description:        Changes the clock settings for the chip
*
* APDU Syntax:        E5 A2 KeyType 00 0A  Key[0:7] Checksum[8:9]
* APDU Inputs:		  P1 = Transport Key 0
*	                  P1 = Encryption Key 1   
* APDU Outputs:       None
*
******************************************************************************/

/******************************************************************************
* External variable declarations
******************************************************************************/

unsigned char idata Key_Buffer[0x10];




#ifdef SIMULATION

// the functions below have to be moved once it is integrated to the firmware
unsigned char Set_Key(unsigned char Key_Type, unsigned char idata * Key_Buffer)
{
  unsigned char i;
  Key_Type = 0;
  i=0;
   Key_Buffer[0]=0;
  return i;
}




unsigned char Get_Key_Status(unsigned char Key_Type)
{
  unsigned char i;
 Key_Type = 0;
  i=0xFF;
  return i;
}

void Init_Key_For_Encryption()
{
unsigned char i;
i=0;
}

void Clear_SBOX_Offset(void)
{
	SBOX_Offset_Hi = 0;
	SBOX_Offset_Lo = 0;

}

void Translate_Byte_In_Acc()
{
    ACC = 0x50;
}

#endif
