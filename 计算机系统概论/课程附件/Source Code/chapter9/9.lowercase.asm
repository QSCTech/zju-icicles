       .ORIG x3000
       LD    R2,TERM  ; Load -7
       LD    R3,ASCII ; Load ASCII difference
AGAIN  TRAP  x23      ; Request keyboard input
       ADD   R1,R2,R0 ; Test for terminating
       BRz   EXIT     ; character
       ADD   R0,R0,R3 ; Change to lowercase
       TRAP  x21      ; Output to the monitor
       BRnzp AGAIN    ; ... and do it again!
TERM   .FILL xFFC9    ; FFC9 = -7
ASCII  .FILL x0020
EXIT   TRAP  x25      ; Halt
