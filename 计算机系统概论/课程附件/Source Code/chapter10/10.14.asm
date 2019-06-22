;   
;    Algorithm to pop two values from the stack, multiply them
;    and if their product is within the acceptable range, push
;    the result on the stack.  R6 is stack pointer.
;    
OpMult         AND    R3,R3,#0      ; R3 holds sign of multiplier.
               JSR    POP           ; Get first source from stack.
               ADD    R5,R5,#0      ; Test for successful POP
               BRp    Exit          ; Failure
               ADD    R1,R0,#0      ; Make room for next POP
               JSR    POP           ; Get second source operand
               ADD    R5,R5,#0      ; Test for successful POP
               BRp    Restore1      ; Failure; restore first POP
               ADD    R2,R0,#0      ; Moves multiplier, tests sign
               BRzp   PosMultiplier 
               ADD    R3,R3,#1      ; Sets FLAG: Multiplier is neg
               NOT    R2,R2
               ADD    R2,R2,#1      ; R2 contains -(multiplier)
PosMultiplier  AND    R0,R0,#0      ; Clear product register
               ADD    R2,R2,#0
               BRz    PushMult      ; Multiplier = 0, Done.
;
MultLoop       ADD    R0,R0,R1      ; THE actual "multiply"
               ADD    R2,R2,#-1     ; Iteration Control
               BRp    MultLoop
;
               JSR    RangeCheck
               ADD    R5,R5,#0      ; R5 contains success/failure
               BRp    Restore2
;
               ADD    R3,R3,#0      ; Test for negative multiplier
               BRz    PushMult
               NOT    R0,R0         ; Adjust for 
               ADD    R0,R0,#1      ; sign of result
PushMult       JSR    PUSH          ; Push product on the stack.
               RET
Restore2       ADD    R6,R6,#-1     ; Adjust stack pointer.
Restore1       ADD    R6,R6,#-1     ; Adjust stack pointer.
Exit           RET   
