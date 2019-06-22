;  Service Routine for Keyboard Input
;
        .ORIG   x04A0
START   ST      R1,SaveR1       ; Save the values in the registers
        ST      R2,SaveR2       ; that are used so that they
        ST      R3,SaveR3       ; can be restored before RET
;
        LD      R2,Newline
L1      LDI     R3,DSR          ; Check DDR --  is it free?
        BRzp    L1
        STI     R2,DDR          ; Move cursor to new clean line
;
        LEA     R1,Prompt       ; Prompt is starting address 
                                ; of prompt string
Loop    LDR     R0,R1,#0        ; Get next prompt character
        BRz     Input           ; Check for end of prompt string
L2      LDI     R3,DSR
        BRzp    L2
        STI     R0,DDR          ; Write next character of 
                                ; prompt string
        ADD     R1,R1,#1        ; Increment Prompt pointer
        BRnzp   Loop
;
Input   LDI     R3,KBSR         ; Has a character been typed?
        BRzp    Input
        LDI     R0,KBDR         ; Load it into R0
L3      LDI     R3,DSR
        BRzp    L3
        STI     R0,DDR          ; Echo input character 
                                ; to the monitor
;
L4      LDI     R3,DSR
        BRzp    L4
        STI     R2,DDR          ; Move cursor to new clean line
        LD      R1,SaveR1       ; Service routine done, restore
        LD      R2,SaveR2       ; original values in registers.
        LD      R3,SaveR3
        RET                     ; Return from trap (i.e., JMP R7)
;
SaveR1  .BLKW   1
SaveR2  .BLKW   1
SaveR3  .BLKW   1
DSR     .FILL   xFE04
DDR     .FILL   xFE06
KBSR    .FILL   xFE00
KBDR    .FILL   xFE02
Newline .FILL   x000A           ; ASCII code for newline 
Prompt  .STRINGZ "Input a character>"
        .END

