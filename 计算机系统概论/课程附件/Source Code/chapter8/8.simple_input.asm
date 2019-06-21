START  LDI     R1, A        ; Test for                               
       BRzp    START        ; character input
       LDI     R0, B 
       BRnzp   NEXT_TASK    ; Go to the next task
A      .FILL   xFE00        ; Address of KBSR
B      .FILL   xFE02        ; Address of KBDR
