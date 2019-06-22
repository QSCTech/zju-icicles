 ;
 ;        Routine to pop the top two elements from the stack,
 ;        add them, and push the sum onto the stack.  R6 is
 ;        the stack pointer.
 ;
 OpAdd       JSR     POP             ; Get first source operand.
             ADD     R5,R5,#0        ; Test if POP was successful.
             BRp     Exit            ; Branch if not successful.
             ADD     R1,R0,#0        ; Make room for second operand
             JSR     POP             ; Get second source operand.
             ADD     R5,R5,#0        ; Test if POP was successful.
             BRp     Restore1        ; Not successful, put back first.
             ADD     R0,R0,R1        ; THE Add.
             JSR     RangeCheck      ; Check size of result.
             BRp     Restore2        ; Out of range, restore both.
             JSR     PUSH            ; Push sum on the stack.
             RET                     ; On to the next task...
Restore2     ADD     R6,R6,#-1       ; Decrement stack pointer.
Restore1     ADD     R6,R6,#-1       ; Decrement stack pointer.
Exit         RET
