
Extrn idata (Cla, Ins, Para1, Para2, Para3)

Extrn data (Temp_Variable_Buffer)
Extrn data (TempVariable1, TempVariable2, TempVariable3, TempVariable4, TempVariable5, TempVariable6, TempVariable7)
Extrn data (Loop_Counter_Lo, Loop_Counter_Hi)
Extrn data (Deep_Idle_Enabled)
Extrn data (SavedDPX)						; Only used on Extended Linear addressing parts

Extrn idata (SW1SW2)

SW1_OK                equ 0x90
SW2_00                equ 0x00
SW1_MEMORY_ERROR      equ 0x65
SW2_MEMORY_ERROR      equ 0x81
SW1_WRONG_LC_LENGTH   equ 0x67
SW1_INCORRECT_DATA    equ 0x6A
SW2_INCORRECT_DATA    equ 0x80
SW1_INCORRECT_PARA    equ 0x6A
SW2_INCORRECT_PARA    equ 0x86
SW1_WRONG_LE_LENGTH   equ 0x6C
SW1_INS_NOT_SUPPORTED equ 0x6D
SW1_CLA_NOT_SUPPORTED equ 0x6E
SW1_GENERAL_ERROR     equ 0x6F
MSB_SET               equ 0x80


Extrn code (PutChar)
Extrn code (GetChar)
