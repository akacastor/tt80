/*
;********************************************************************************************************
;
; Name:         TP62_Send_ATR.c
; Description:	Send an ATR identifing this chip code
; Copyright:	Emosyn Inc. 2005
; 
;********************************************************************************************************
; The Example Code hereinbelow is provided "AS IS" and at your sole risk.  
; As to this Code, EMOSYN expressly disclaims all Warranties, including, but not limited to the implied 
; warranties of merchantability and fitness for a particular purpose. EMOSYN does not warrant that the 
; functions contained in this code will meet your requirements, or that the operation of the code will 
; be accurate, error-free, or non-infringing.  No oral or written information or advice given by EMOSYN 
; or an authorized representative shall create or affect any Warranty.
;********************************************************************************************************
; $Revision: 1.2 $
; $Author: chin $ 
; $Date: 2005/10/25 11:43:56 $
;********************************************************************************************************
;
; Inputs
;       None
;
; Outputs
;       None
;
;********************************************************************************************************
*/

/* Header file inclusions */
#include "Firmware_API_JumpTable.h"
#include "Emosyn_Helper_Functions.h"

/* External and local function declarations */

/* External variable declarations */

void Send_ATR (void)
{
    PutChar (0x3B); /* Direct Convention */

    PutChar (0x93); /* TA(1) present. TD(1) present. 3 Historical Bytes */ 

    PutChar (0x11); /* TA(1) - FiDi to give /372 */

    PutChar (0x00); /* TD(1) */

    PutChar (0x00); /* High byte of Chip type (0062) */

    PutChar (0x62); /* Low byte of Chip type (0062) */

    TEMPVARIABLE1 = Firmware_GetFirmwareVersion();

    PutChar (TEMPVARIABLE1); /* Chip firmware version */

    return;

} /* End of function */
