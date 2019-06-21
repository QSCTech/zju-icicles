; puts.asm
; This service routine writes a NULL-terminated string to the console.
;      It services the PUTS service call (TRAP x22). 
; Inputs: R0 is a pointer to the string to print.
; Context Information: R0, R1, and R3 are saved, and R7 is lost
;      in the jump to this routine
;
             .ORIG   x0450           ; Where this ISR resides
             ST      R7, SaveR7      ; Save R7 for later return
             ST      R0, SaveR0      ; Save other registers that
             ST      R1, SaveR1      ; Are needed by this routine 
             ST      R3, SaveR3      ;
;
; Loop through each character in the array
;
;
Loop         LDR     R1, R0, #0      ; Retrieve the character(s)
             BRz     Return          ; If it is 0, done
L2           LDI     R3,DSR
             BRzp    L2
             STI     R1, DDR         ; Write the character
             ADD     R0, R0, #1      ; Increment pointer
             BRnzp   Loop            ; Do it all over again
;
; Return from the request for service call
Return       LD      R3, SaveR3
             LD      R1, SaveR1
             LD      R0, SaveR0
             LD      R7, SaveR7
             RET
;
; Register locations
DSR          .FILL   xFE04
DDR          .FILL   xFE06
SaveR0       .FILL   x0000 
SaveR1       .FILL   x0000
SaveR3       .FILL   x0000
SaveR7       .FILL   x0000
             .END
