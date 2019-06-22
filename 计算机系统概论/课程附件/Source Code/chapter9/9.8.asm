             .ORIG   x04A0
START        ST      R7,SaveR7
             JSR     SaveReg
             LD      R2,Newline
             JSR     WriteChar
             LEA     R1,PROMPT
;
;
Loop         LDR     R2,R1,#0    ; Get next prompt char
             BRz     Input
             JSR     WriteChar
             ADD     R1,R1,#1
             BRnzp   Loop
; 
Input        JSR     ReadChar
             ADD     R2,R0,#0    ; Move char to R2 for writing
             JSR     WriteChar   ; Echo to monitor
;    
             LD      R2, Newline
             JSR     WriteChar
             JSR     RestoreReg
             LD      R7,SaveR7
             RET		      ; JMP R7 terminates 
;                                  the TRAP routine                       
SaveR7       .FILL   x0000
Newline      .FILL   x000A
Prompt       .STRINGZ  "Input a character>"
;
WriteChar    LDI     R3,DSR
             BRzp    WriteChar
             STI     R2,DDR
             RET		      ; JMP R7 terminates subroutine
DSR          .FILL   xFE04
DDR          .FILL   xFE06 
;
ReadChar     LDI     R3,KBSR
             BRzp    ReadChar
             LDI     R0,KBDR
             RET
KBSR         .FILL   xFE00
KBDR         .FILL   xFE02
;
SaveReg      ST      R1,SaveR1
             ST      R2,SaveR2
             ST      R3,SaveR3
             ST      R4,SaveR4
             ST      R5,SaveR5
             ST      R6,SaveR6
             RET
;
RestoreReg   LD      R1,SaveR1
             LD      R2,SaveR2
             LD      R3,SaveR3
             LD      R4,SaveR4
             LD      R5,SaveR5
             LD      R6,SaveR6
             RET
SaveR1       .FILL   x0000
SaveR2       .FILL   x0000
SaveR3       .FILL   x0000
SaveR4       .FILL   x0000
SaveR5       .FILL   x0000
SaveR6       .FILL   x0000
             .END
