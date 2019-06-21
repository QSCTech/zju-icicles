;  This algorithm POPs a value from the stack and puts it in
;  R0 before returning to the calling program.  R5 is used to
;  report success (R5=0) or failure (R5=1) of the POP operation.
POP            LEA     R0,StackBase
               NOT     R0,R0
               ADD     R0,R0,#1       ; R0 = -addr.ofStackBase 
               ADD     R0,R0,R6       ; R6 = StackPointer
               BRz     Underflow
               LDR     R0,R6,#0       ; The actual POP 
               ADD     R6,R6,#1      ; Adjust StackPointer
               AND     R5,R5,#0       ; R5 <-- success
               RET 
Underflow      ST      R7,Save        ; TRAP/RET needs R7
               LEA     R0,UnderflowMsg
               PUTS                   ; Print error message.
               LD      R7,Save        ; Restore R7
               AND     R5,R5,#0  
               ADD     R5,R5,#1       ; R5 <-- failure
               RET
Save           .FILL   x0000
StackMax       .BLKW   9
StackBase      .FILL   x0000
UnderflowMsg   .FILL   x000A
               .STRINGZ "Error: Too Few Values on the Stack."
