;********************************************************************************************************
;
; Name:		Bootloader.inc
; Description:	Include file for the TT80 bootloader
; Copyright:	Emosyn Inc. 2004
; 
;********************************************************************************************************
; The Example Code hereinbelow is provided "AS IS" and at your sole risk.  
; As to this Code, EMOSYN expressly disclaims all Warranties, including, but not limited to the implied 
; warranties of merchantability and fitness for a particular purpose. EMOSYN does not warrant that the 
; functions contained in this code will meet your requirements, or that the operation of the code will 
; be accurate, error-free, or non-infringing.  No oral or written information or advice given by EMOSYN 
; or an authorized representative shall create or affect any Warranty.
;********************************************************************************************************
; $Revision: 1.3 $
; $Author: dhunter $ 
; $Date: 2007/05/03 22:17:36 $
;********************************************************************************************************


;*******************************************************************************
;       Includes
;*******************************************************************************
$include (TT40_public_sfrs.inc)


DEVICE_ID_HIGH					equ	00h
DEVICE_ID_LOW					equ	80h


Firmware_Set_Clock_Trim				equ	0x01CE
Firmware_Erase_UCM_Blocks			equ	0x01D0
Firmware_Set_SecurityAction			equ	0x01D2
Firmware_Set_SecurityMask			equ	0x01D4
Firmware_Set_Execute_Only_Status		equ	0x01D6
Firmware_Set_Protection_Status			equ	0x01D8
Firmware_Get_Chip_ID				equ	0x01DA
Firmware_Get_Firmware_Version			equ	0x01DC
Firmware_Set_Clock				equ	0x01DE
_Firmware_Set_Clock				equ	0x01DE
Firmware_Get_ClockSource			equ	0x01E0
Firmware_Get_ClockControl			equ	0x01E2
Firmware_Erase_Page_UCM		equ 0x01EC
_Firmware_Set_Key				equ	0x01F4
Firmware_Set_key				equ	0x01F4
_Firmware_Get_Key_Status			equ	0x01F6
Firmware_Get_key_Status				equ	0x01F6
_Firmware_Init_Key_For_Encryption		equ	0x01F8
Firmware_Init_Key_For_Encryption		equ	0x01F8
_Firmware_Translate_Byte_In_Acc			equ	0x01FA
Firmware_Translate_Byte_In_Acc			equ	0x01FA
Firmware_Clear_SBOX_Offset			equ	0x01FC

DEFAULT_BLOCK_SIZE				equ	64

CLA_EMOSYN					equ	0E5h

CMD_WRITE_UCM					equ	050h
CMD_CHANGE_DIVIDOR_RATE				equ	012h
CMD_MASS_ERASE_UCM_BOOTLOADER_SAFE		equ	030h
CMD_CHANGE_BLOCK_SIZE				equ	051h
CMD_CHANGE_TO_60MHZ				equ 	055h
CMD_WRITE_UCM_ENCRYPTED				equ	060h
CMD_RECEIVE_KEY					equ	065h
CMD_SET_CLR_CD_BIT_IN_NVFSMCON			equ	059h

; ISO Specific
INS_CHANGE_DIVIDOR_RATE				equ	012h 
INS_WRITE_UCM_BLOCK				equ	0A0h 
INS_WRITE_UCM_BLOCK_ENCRYPTED			equ	0A6h 
INS_GET_FIRMWARE_VERSION			equ	032h
INS_MASS_ERASE_UCM_BOOTLOADER_SAFE		equ	030h
INS_GET_CHIP_ID					equ	034h 

INS_LOAD_KEY					equ	0A2h   
INS_SET_CLOCK					equ	056h 
INS_SET_CLR_CD_BIT_IN_NVFSMCON			equ	058h

INS_ERASE_UCM_PAGE_XDATA			equ	03Ch
INS_ERASE_UCM_PAGE_CODE				equ	036h
INS_BULK_MEMORY_CHECKSUM_CODE			equ	0A8h
INS_BULK_MEMORY_CHECKSUM_XDATA			equ	0A4h
INS_READ_UCM_PAGE_CODE				equ	038h
INS_READ_UCM_PAGE_XDATA				equ	03Ah
INS_BACKUP_CORE_BL				equ	03Fh
; Key Type
TRANSPORT_KEY					equ	00h
ENCRYPTION_KEY					equ	01h

#define PRODUCTION
;#define SIMULATION

;#de|-;#define DEBUG1  // for read commands.
