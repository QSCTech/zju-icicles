;
; This routine clears the stack by resetting the stack pointer (R6).
;
OpClear      LEA       R6,StackBase  ; Initialize the Stack.
             ADD       R6,R6,#1      ; R6 is stack pointer
             BRnzp     NewCommand
