;    Algorithm to pop the top of the stack, form its negative,
;    and push the result on the stack.
;
OpNeg        JSR    POP         ; Get the source operand
             ADD    R5,R5,#0    ; test for successful pop
             BRp    Exit        ; Branch if failure
             NOT    R0,R0
             ADD    R0,R0,#1    ; Form the negative of the source.
             JSR    PUSH        ; Push the result on the stack.
Exit         RET
