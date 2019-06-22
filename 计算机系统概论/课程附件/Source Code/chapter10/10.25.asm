;  This algorithm PUSHes on the stack the value stored in R0.
;  R5 is used to report success (R5=0) or failure (R5=1) of 
;  the PUSH operation.
;
PUSH           ST      R1,Save1      ; R1 is needed by this routine
               LEA     R1,StackMax
               NOT     R1,R1
               ADD     R1,R1,#1      ; R1 = - addr. of StackMax    
               ADD     R1,R1,R6      ; R6 = StackPointer
               BRz     Overflow
               ADD     R6,R6,#-1     ; Adjust StackPointer for PUSH
               STR     R0,R6,#0      ; The actual PUSH
               BRnzp   Success_exit
Overflow       ST      R7,Save
               LEA     R0,OverflowMsg
               PUTS
               LD      R7,Save
               LD      R1, Save1     ; Restore R1
               AND     R5,R5,#0    
               ADD     R5,R5,#1      ; R5 <-- failure
               RET
Success_exit   LD      R1,Save1      ; Restore R1
               AND     R5,R5,#0      ; R5 <-- success
               RET
Save           .FILL   x0000
Save1          .FILL   x0000
OverflowMsg    .STRINGZ "Error: Stack is Full."
